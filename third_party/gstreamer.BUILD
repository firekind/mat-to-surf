package(default_visibility = ["//visibility:public"])

INCLUDE_PREFIX = "include/gstreamer-1.0/"

cc_library(
    name = "gst",
    hdrs = glob([
        INCLUDE_PREFIX + "gst/*.h",
    ]),
    deps = [
        "@glib",
    ],
    linkopts = [
        "-l:libgstreamer-1.0.so.0",
    ],
    includes = [
        INCLUDE_PREFIX
    ],
    strip_include_prefix = INCLUDE_PREFIX
)

cc_library(
    name = "base",
    hdrs = glob([
        INCLUDE_PREFIX + "gst/base/*.h",
    ]),
    linkopts = [
        "-l:libgstbase-1.0.so.0",
    ],
    deps = [
        ":gst",
        "@glib",
    ],
    includes = [
        INCLUDE_PREFIX,
    ],
    strip_include_prefix = INCLUDE_PREFIX
)

cc_library(
    name = "check",
    hdrs = glob([
        INCLUDE_PREFIX + "gst/check/*.h",
    ]),
    linkopts = [
        "-l:libgstcheck-1.0.so.0",
    ],
    deps = [
        ":gst",
        "@glib",
    ],
    includes = [
        INCLUDE_PREFIX,
    ],
    strip_include_prefix = INCLUDE_PREFIX
)

cc_library(
    name = "controller",
    hdrs = glob([
        INCLUDE_PREFIX + "gst/controller/*.h",
    ]),
    linkopts = [
        "-l:libgstcontroller-1.0.so.0",
    ],
    deps = [
        ":gst",
        "@glib",
    ],
    includes = [
        INCLUDE_PREFIX,
    ],
    strip_include_prefix = INCLUDE_PREFIX
)

cc_library(
    name = "net",
    hdrs = glob([
        INCLUDE_PREFIX + "gst/net/*.h",
    ]),
    linkopts = [
        "-l:libgstnet-1.0.so.0",
    ],
    deps = [
        ":gst",
        "@glib",
    ],
    includes = [
        INCLUDE_PREFIX,
    ],
    strip_include_prefix = INCLUDE_PREFIX
)

cc_library(
    name = "gstreamer",
    deps = [
        ":gst",
        ":base",
        ":check",
        ":controller",
        ":net",
    ],
)
