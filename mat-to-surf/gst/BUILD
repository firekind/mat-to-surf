package(default_visibility = [ "//visibility:public" ])
cc_binary(
    name = "libgstmattosurf.so",
    srcs = [
        "gstmattosurf.cpp",
        "gstmattosurf.hpp",
    ],
    deps = [
        "@gstreamer",
        "@gst_plugins_base//:video",
    ] + select({
        "//bzl:x86_64": [
            "@cuda_x86_64//:cudart",
            "@opencv_x86_64//:core",
            "@opencv_x86_64//:imgproc",
            "@opencv_x86_64//:imgcodecs",
            "//third_party/deepstream/x86_64:nvbufsurface",
            "//third_party/deepstream/x86_64:meta",
        ],
        "//bzl:aarch64": [
            "@cuda_aarch64//:cudart",
            "@opencv_aarch64//:core",
            "@opencv_aarch64//:imgproc",
            "@opencv_aarch64//:imgcodecs",
            "//third_party/deepstream/aarch64:nvbufsurface",
            "//third_party/deepstream/aarch64:meta",
        ]
    }),
    linkshared = True,
)
