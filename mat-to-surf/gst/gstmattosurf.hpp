#pragma once

#include "gst/gst.h"
#include "gst/base/gstbasetransform.h"

#include "nvbufsurface.h"
#include "nvbufsurftransform.h"
#include "cuda_runtime.h"

G_BEGIN_DECLS

#define GST_TYPE_MATTOSURF (gst_mattosurf_get_type())
G_DECLARE_FINAL_TYPE(GstMatToSurf, gst_mattosurf, GST, MATTOSURF, GstBaseTransform)

struct _GstMatToSurf {
    GstBaseTransform parent;

    cudaStream_t cuda_stream;
    NvBufSurface* intermediate_buffer;
};

G_END_DECLS
