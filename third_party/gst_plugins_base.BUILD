package(default_visibility = ["//visibility:public"])

INCLUDE_PREFIX = "include/gstreamer-1.0/"

cc_library(
    name = "video",
    hdrs = glob([
        INCLUDE_PREFIX + "gst/video/*.h",
    ]),
    linkopts = [
        "-l:libgstvideo-1.0.so.0",
    ],
    deps = [
        "@glib",
        "@gstreamer//:gst",
        "@gstreamer//:base",
    ],
    includes = [
        INCLUDE_PREFIX
    ],
    strip_include_prefix = INCLUDE_PREFIX
)
