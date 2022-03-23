cc_library(
    name = "meta",
    hdrs = [
        "sources/includes/gstnvdsmeta.h",
        "sources/includes/nvdsmeta.h",
        "sources/includes/nvll_osd_struct.h",
        "sources/includes/nvds_roi_meta.h",
        "sources/includes/nvds_audio_meta.h",
        "sources/includes/nvds_latency_meta.h",
        "sources/includes/nvbufaudio.h",
    ],
    srcs = [
        "lib/libnvdsgst_meta.so",
        "lib/libnvds_meta.so",
    ],
    deps = [
        "@gst_plugins_base//:video",
        "@glib"
    ],
    includes = [
        "sources/includes",
    ],
    strip_include_prefix = "sources/includes",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "nvbufsurface",
    srcs = [
        "lib/libnvbufsurface.so",
        "lib/libnvbufsurftransform.so",
    ],
    hdrs = [
        "sources/includes/nvbufsurface.h",
        "sources/includes/nvbufsurftransform.h"
    ],
    includes = [
        "sources/includes",
    ],
    linkopts = [
        "-Wl,--no-as-needed,-l:libnvbufsurface.so,--as-needed",
    ],
    strip_include_prefix = "sources/includes",
    visibility = ["//visibility:public"],
    deps = [
        "@gstreamer",
        "@glib"
    ]
)

cc_library(
    name = "custom_impl",
    hdrs = [
        "sources/includes/nvdsinfer_custom_impl.h"
    ],
    includes = [
        "sources/includes",
    ],
    deps = [
        ":nvinfer_api",
    ],
    strip_include_prefix = "sources/includes",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "nvinfer_api",
    hdrs = [
        "sources/includes/nvdsinfer.h",
        "sources/includes/gstnvdsinfer.h",
    ],
    includes = [
        "sources/includes",
    ],
    strip_include_prefix = "sources/includes",
    visibility = ["//visibility:public"],
)
