#include "gstmattosurf.hpp"

#include "opencv2/opencv.hpp"
#include "gstnvdsmeta.h"

#include "cudaEGL.h"

G_DEFINE_TYPE(GstMatToSurf, gst_mattosurf, GST_TYPE_BASE_TRANSFORM);
#define DEFAULT_GPU_ID 0
#define WIDTH 640
#define HEIGHT 480

#define PACKAGE "mattosurf"
#define PACKAGE_VERSION "0.0.1"
#define GST_LICENSE "LGPL"
#define GST_PACKAGE_NAME "mattosurf"
#define GST_PACKAGE_ORIGIN "<none>"

#define CHECK_CUDA_STATUS(cuda_status, error_str)                                      \
    do {                                                                               \
        if ((cuda_status) != cudaSuccess) {                                            \
            printf("Error: %s in %s at line %d (%s)\n", error_str, __FILE__, __LINE__, \
                   cudaGetErrorName(cuda_status));                                     \
            std::abort();                                                              \
        }                                                                              \
    } while (0)

#define ASSERT(condition, message)                                                       \
    do {                                                                                 \
        if (!(condition)) {                                                              \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ << " line " \
                      << __LINE__ << ": " << message << std::endl;                       \
            std::abort();                                                                \
        }                                                                                \
    } while (false)

enum { PROP_0, PROP_GPU_DEVICE_ID };

static GstStaticPadTemplate sink_template = GST_STATIC_PAD_TEMPLATE(
    "sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS(GST_VIDEO_CAPS_MAKE_WITH_FEATURES("memory:NVMM", "{ RGBA }")));

static GstStaticPadTemplate src_template = GST_STATIC_PAD_TEMPLATE(
    "src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS(GST_VIDEO_CAPS_MAKE_WITH_FEATURES("memory:NVMM", "{ RGBA }")));

static gboolean gst_mattosurf_start(GstBaseTransform* parent);

static GstFlowReturn gst_mattosurf_prepare_output_buffer(GstBaseTransform* parent,
                                                           GstBuffer* in_buf,
                                                           GstBuffer** out_buf);

static GstFlowReturn gst_mattosurf_transform(GstBaseTransform* parent,
                                               GstBuffer* in_buf,
                                               GstBuffer* out_buf);

static std::unique_ptr<cv::Mat> gst_mattosurf_get_mat_from_surf(GstMatToSurf* self, NvBufSurface* surface, uint32_t idx);

static void gst_mattosurf_fill_surf_from_mat(GstMatToSurf* self, NvBufSurface* surface, const cv::Mat* mat, uint32_t idx);

static GstBuffer* gst_mattosurf_create_surf_buffer(GstMatToSurf* self, NvBufSurfaceCreateParams* params, uint32_t batch_size);

static gboolean gst_mattosurf_stop(GstBaseTransform* parent);

static void gst_mattosurf_class_init(GstMatToSurfClass* klass) {
    GstBaseTransformClass* basetransform_class = GST_BASE_TRANSFORM_CLASS(klass);
    GstElementClass* element_class = GST_ELEMENT_CLASS(klass);

    basetransform_class->start = GST_DEBUG_FUNCPTR(gst_mattosurf_start);
    basetransform_class->prepare_output_buffer = GST_DEBUG_FUNCPTR(gst_mattosurf_prepare_output_buffer);
    basetransform_class->transform = GST_DEBUG_FUNCPTR(gst_mattosurf_transform);
    basetransform_class->stop = GST_DEBUG_FUNCPTR(gst_mattosurf_stop);

    gst_element_class_set_details_simple(element_class, "blah", "Filter/Video", "blah", "firekind");

    gst_element_class_add_pad_template(element_class, gst_static_pad_template_get(&src_template));
    gst_element_class_add_pad_template(element_class, gst_static_pad_template_get(&sink_template));
}

static void gst_mattosurf_init(GstMatToSurf* self) {}

static gboolean gst_mattosurf_start(GstBaseTransform* parent) {
    GstMatToSurf* self = GST_MATTOSURF(parent);

    NvBufSurfaceCreateParams create_params;
    create_params.gpuId = DEFAULT_GPU_ID;
    create_params.width = WIDTH;
    create_params.height = HEIGHT;
    create_params.size = 0;
    create_params.colorFormat = NVBUF_COLOR_FORMAT_RGBA;
    create_params.layout = NVBUF_LAYOUT_PITCH;
#ifdef __aarch64__
    create_params.memType = NVBUF_MEM_DEFAULT;
#else
    create_params.memType = NVBUF_MEM_CUDA_UNIFIED;
#endif

    ASSERT(NvBufSurfaceCreate(&self->intermediate_buffer, 1, &create_params) == 0,
           "Could not allocate internal buffer");
    CHECK_CUDA_STATUS(cudaSetDevice(DEFAULT_GPU_ID), "Unable to set cuda device");
    CHECK_CUDA_STATUS(cudaStreamCreate(&self->cuda_stream), "Unable to create cuda stream");

    return TRUE;
}

static GstFlowReturn gst_mattosurf_prepare_output_buffer(GstBaseTransform* parent,
                                                           GstBuffer* in_buf,
                                                           GstBuffer** out_buf) {
    NvBufSurfaceCreateParams create_params;
    create_params.gpuId = DEFAULT_GPU_ID;
    create_params.width = WIDTH;
    create_params.height = HEIGHT;
    create_params.size = 0;
    create_params.colorFormat = NVBUF_COLOR_FORMAT_RGBA;
    create_params.layout = NVBUF_LAYOUT_PITCH;
#ifdef __aarch64__
    create_params.memType = NVBUF_MEM_DEFAULT;
#else
    create_params.memType = NVBUF_MEM_CUDA_DEVICE;
#endif

    *out_buf = gst_mattosurf_create_surf_buffer(GST_MATTOSURF(parent), &create_params, 1);

    return GST_FLOW_OK;
}

static GstFlowReturn gst_mattosurf_transform(GstBaseTransform* parent,
                                               GstBuffer* in_buf,
                                               GstBuffer* out_buf) {
    GstMatToSurf* self = GST_MATTOSURF(parent);
    GstMapInfo in_map, out_map;

    gst_buffer_map(in_buf, &in_map, GST_MAP_READ);
    NvBufSurface* in_surface = (NvBufSurface*)in_map.data;
    NvDsBatchMeta* in_batch_meta = gst_buffer_get_nvds_batch_meta(in_buf);

    gst_buffer_map(out_buf, &out_map, GST_MAP_WRITE);
    NvBufSurface* out_surface = (NvBufSurface*)out_map.data;
    NvDsBatchMeta* out_batch_meta = gst_buffer_get_nvds_batch_meta(out_buf);

    NvDsFrameMeta* frame_meta = (NvDsFrameMeta*)in_batch_meta->frame_meta_list->data;
    std::unique_ptr<cv::Mat> frame = gst_mattosurf_get_mat_from_surf(self, in_surface, 0);
    
    cv::Mat final_img;
    cv::cvtColor(*frame, final_img, cv::COLOR_BGR2GRAY);
    cv::cvtColor(final_img, final_img, cv::COLOR_GRAY2RGBA);

    gst_mattosurf_fill_surf_from_mat(self, out_surface, &final_img, 0);
    NvDsFrameMeta* new_frame_meta = nvds_acquire_frame_meta_from_pool(out_batch_meta);
    nvds_copy_frame_meta(frame_meta, new_frame_meta);
    nvds_add_frame_meta_to_batch(out_batch_meta, new_frame_meta);

    gst_buffer_unmap(in_buf, &in_map);
    gst_buffer_unmap(out_buf, &out_map);

    return GST_FLOW_OK;
}

// from dsexample
static std::unique_ptr<cv::Mat> gst_mattosurf_get_mat_from_surf(GstMatToSurf* self, NvBufSurface* surface, uint32_t idx) {
    NvBufSurfTransform_Error err;
    NvBufSurfTransformConfigParams transform_config_params;
    NvBufSurfTransformParams transform_params;
    NvBufSurface ip_surf;
    cv::Mat intermediate_mat;
    std::unique_ptr<cv::Mat> final_mat = std::make_unique<cv::Mat>();

    ip_surf = *surface;

    ip_surf.numFilled = ip_surf.batchSize = 1;
    ip_surf.surfaceList = &(surface->surfaceList[idx]);

    transform_config_params.compute_mode = NvBufSurfTransformCompute_Default;
    transform_config_params.gpu_id = DEFAULT_GPU_ID;
    transform_config_params.cuda_stream = self->cuda_stream;

    err = NvBufSurfTransformSetSessionParams(&transform_config_params);
    ASSERT(err == NvBufSurfTransformError_Success, "NvBufSurfTransformSetSessionParams failed.");

    transform_params.transform_flag = NVBUFSURF_TRANSFORM_FILTER;
    transform_params.transform_filter = NvBufSurfTransformInter_Default;

    NvBufSurfaceMemSet(self->intermediate_buffer, 0, 0, 0);

    err = NvBufSurfTransform(&ip_surf, self->intermediate_buffer, &transform_params);
    ASSERT(err == NvBufSurfTransformError_Success, "NvBufSurfTransform failed.");

    ASSERT(NvBufSurfaceMap(self->intermediate_buffer, 0, 0, NVBUF_MAP_READ) == 0,
           "Could not map intermediate buffer.");

    if (self->intermediate_buffer->memType == NVBUF_MEM_SURFACE_ARRAY ||
        self->intermediate_buffer->memType == NVBUF_MEM_HANDLE) {
        NvBufSurfaceSyncForCpu(self->intermediate_buffer, 0, 0);
    }

    intermediate_mat = cv::Mat(HEIGHT, WIDTH, CV_8UC4,
                               self->intermediate_buffer->surfaceList[0].mappedAddr.addr[0],
                               self->intermediate_buffer->surfaceList[0].pitch);

#if (CV_MAJOR_VERSION >= 4)
    cv::cvtColor(intermediate_mat, *final_mat, cv::COLOR_RGBA2BGR);
#else
    cv::cvtColor(intermediate_mat, *final_mat, CV_RGBA2BGR);
#endif

    ASSERT(NvBufSurfaceUnMap(self->intermediate_buffer, 0, 0) == 0,
           "Could not unmap intermediate buffer");

    return final_mat;
}

static void gst_mattosurf_fill_surf_from_mat(GstMatToSurf* self, NvBufSurface* surface, const cv::Mat* mat, uint32_t idx) {
    ASSERT(
        (surface->memType == NVBUF_MEM_CUDA_DEVICE || surface->memType == NVBUF_MEM_SURFACE_ARRAY),
        "Unsupported NvBufSurface memType.");
    ASSERT(NvBufSurfaceMemSet(surface, idx, 0, 0) == 0, "Failed to memset NvBufSurface");

    void* data_ptr = NULL;
    CUgraphicsResource cuda_resource;
    CUeglFrame egl_frame;
    if (surface->memType == NVBUF_MEM_SURFACE_ARRAY) {
        ASSERT(NvBufSurfaceMapEglImage(surface, idx) == 0,
            "Could not map EglImage from NvBufSurface");
        ASSERT(cuGraphicsEGLRegisterImage(&cuda_resource,
                                        surface->surfaceList[idx].mappedAddr.eglImage,
                                        CU_GRAPHICS_MAP_RESOURCE_FLAGS_NONE) == CUDA_SUCCESS,
            "Failed to register EGLImage in cuda");
        ASSERT(cuGraphicsResourceGetMappedEglFrame(&egl_frame, cuda_resource, 0, 0) == CUDA_SUCCESS,
            "Failed to get mapped EGL frame");
        data_ptr = (char*)egl_frame.frame.pPitch[0];
    } else {
        data_ptr = surface->surfaceList[idx].dataPtr;
    }

    CHECK_CUDA_STATUS(cudaMemcpy2D(data_ptr, surface->surfaceList[idx].pitch, mat->ptr(), mat->step,
                                mat->step, mat->rows, cudaMemcpyHostToDevice),
                    "Could not copy mat to surface");

    if (surface->memType == NVBUF_MEM_SURFACE_ARRAY) {
        cuGraphicsUnregisterResource(cuda_resource);
        NvBufSurfaceUnMapEglImage(surface, idx);
    }

    surface->numFilled++;
}

static GstBuffer* gst_mattosurf_create_surf_buffer(GstMatToSurf* self, NvBufSurfaceCreateParams* params, uint32_t batch_size) {
    NvBufSurface* surface;
    GstBuffer* buffer;

    ASSERT(NvBufSurfaceCreate(&surface, batch_size, params) == 0, "Failed to create surface");
    buffer =
        gst_buffer_new_wrapped_full((GstMemoryFlags)0, (gpointer)surface, sizeof(NvBufSurface), 0,
                                    sizeof(NvBufSurface), (gpointer)surface, [](void* data) {
                                        if (data)
                                            NvBufSurfaceDestroy((NvBufSurface*)data);
                                    });
    ASSERT(buffer != NULL, "failed to create buffer");

    NvDsBatchMeta* batch_meta = nvds_create_batch_meta(batch_size);
    NvDsMeta* meta = gst_buffer_add_nvds_meta(buffer, batch_meta, NULL, nvds_batch_meta_copy_func,
                                              nvds_batch_meta_release_func);
    meta->meta_type = NVDS_BATCH_GST_META;
    batch_meta->base_meta.batch_meta = batch_meta;
    batch_meta->base_meta.copy_func = nvds_batch_meta_copy_func;
    batch_meta->base_meta.release_func = nvds_batch_meta_release_func;
    batch_meta->max_frames_in_batch = batch_size;

    return buffer;
}

static gboolean gst_mattosurf_stop(GstBaseTransform* parent) {
    GstMatToSurf* self = GST_MATTOSURF(parent);

    if (self->intermediate_buffer) {
        NvBufSurfaceDestroy(self->intermediate_buffer);
    }
    self->intermediate_buffer = NULL;

    if (self->cuda_stream) {
        cudaStreamDestroy(self->cuda_stream);
    }
    self->cuda_stream = NULL;

    return TRUE;
}

static gboolean plugin_init(GstPlugin* mattosurf) {
    if (!gst_element_register(mattosurf, "mattosurf", GST_RANK_NONE, GST_TYPE_MATTOSURF)) {
        return FALSE;
    }
    return TRUE;
}

GST_PLUGIN_DEFINE(GST_VERSION_MAJOR,
                  GST_VERSION_MINOR,
                  mattosurf,
                  "mattosurf",
                  plugin_init,
                  PACKAGE_VERSION,
                  GST_LICENSE,
                  GST_PACKAGE_NAME,
                  GST_PACKAGE_ORIGIN)