cc_library(
    name = "core",
    srcs = [
        "usr/lib/aarch64-linux-gnu/libopencv_core.so",
        "usr/lib/aarch64-linux-gnu/libopencv_core.so.4.1",
        "usr/lib/aarch64-linux-gnu/libopencv_core.so.4.1.1",
    ],
    hdrs = glob([
        "usr/include/**/*.h",
        "usr/include/**/*.hpp",
    ]),
    linkopts = [
        "-Wl,--no-as-needed," +
        "-l:libopencv_core.so.4.1," +
        "--as-needed",
    ],
    strip_include_prefix = "usr/include/opencv4",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "imgproc",
    srcs = [
        "usr/lib/aarch64-linux-gnu/libopencv_imgproc.so",
        "usr/lib/aarch64-linux-gnu/libopencv_imgproc.so.4.1",
        "usr/lib/aarch64-linux-gnu/libopencv_imgproc.so.4.1.1",
    ],
    hdrs = glob([
        "usr/include/**/*.h",
        "usr/include/**/*.hpp",
    ]),
    deps = [
        ":core",
    ],
    linkopts = [
        "-Wl,--no-as-needed," +
        "-l:libopencv_imgproc.so.4.1," +
        "-l:libopencv_core.so.4.1," +
        "--as-needed",
    ],
    strip_include_prefix = "usr/include/opencv4",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "imgcodecs",
    srcs = [
        "usr/lib/aarch64-linux-gnu/libopencv_imgcodecs.so",
        "usr/lib/aarch64-linux-gnu/libopencv_imgcodecs.so.4.1",
        "usr/lib/aarch64-linux-gnu/libopencv_imgcodecs.so.4.1.1",
    ],
    hdrs = glob([
        "usr/include/**/*.h",
        "usr/include/**/*.hpp",
    ]),
    deps = [
        ":core",
        ":imgproc",
    ],
    linkopts = [
        "-Wl,--no-as-needed," +
        "-l:libopencv_imgcodecs.so.4.1," +
        "-l:libopencv_imgproc.so.4.1," +
        "-l:libopencv_core.so.4.1," +
        "--as-needed",
    ],
    strip_include_prefix = "usr/include/opencv4",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "highgui",
    srcs = [
        "usr/lib/aarch64-linux-gnu/libopencv_highgui.so",
        "usr/lib/aarch64-linux-gnu/libopencv_highgui.so.4.1",
        "usr/lib/aarch64-linux-gnu/libopencv_highgui.so.4.1.1",
    ],
    hdrs = glob([
        "usr/include/**/*.h",
        "usr/include/**/*.hpp",
    ]),
    deps = [
        ":core",
        ":imgproc",
        ":imgcodecs",
    ],
    linkopts = [
        "-Wl,--no-as-needed," +
        "-l:libopencv_highgui.so.4.1," +
        "-l:libopencv_imgcodecs.so.4.1," +
        "-l:libopencv_imgproc.so.4.1," +
        "-l:libopencv_core.so.4.1," +
        "--as-needed",
    ],
    strip_include_prefix = "usr/include/opencv4",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "flann",
    srcs = glob([
        "usr/lib/aarch64-linux-gnu/libopencv_flann.so*"
    ]),
    hdrs = glob([
        "usr/include/**/*.h",
        "usr/include/**/*.hpp",
    ]),
    deps = [
        ":core",
    ],
    linkopts = [
        "-Wl,--no-as-needed," +
        "-l:libopencv_flann.so," +
        "-l:libopencv_core.so.4.1," + 
        "--as-needed",
    ],
    strip_include_prefix = "usr/include/opencv4",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "features2d",
    srcs = glob([
        "usr/lib/aarch64-linux-gnu/libopencv_features2d.so*"
    ]),
    hdrs = glob([
        "usr/include/**/*.h",
        "usr/include/**/*.hpp",
    ]),
    deps = [
        ":core",
        ":imgproc",
        ":flann",
    ],
    linkopts = [
        "-Wl,--no-as-needed," +
        "-l:libopencv_features2d.so," +
        "-l:libopencv_core.so.4.1," + 
        "-l:libopencv_imgproc.so.4.1," +
        "-l:libopencv_flann.so," +
        "--as-needed",
    ],
    strip_include_prefix = "usr/include/opencv4",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "calib3d",
    srcs = glob([
        "usr/lib/aarch64-linux-gnu/libopencv_calib3d.so*"
    ]),
    hdrs = glob([
        "usr/include/**/*.h",
        "usr/include/**/*.hpp",
    ]),
    deps = [
        ":core",
        ":imgproc",
        ":features2d",
        ":flann",
    ],
    linkopts = [
        "-Wl,--no-as-needed," +
        "-l:libopencv_calib3d.so," +
        "-l:libopencv_core.so.4.1," + 
        "-l:libopencv_imgproc.so.4.1," +
        "-l:libopencv_features2d.so," +
        "-l:libopencv_flann.so," +
        "--as-needed",
    ],
    strip_include_prefix = "usr/include/opencv4",
    visibility = ["//visibility:public"],
)


cc_library(
    name = "objdetect",
    srcs = glob([
        "usr/lib/aarch64-linux-gnu/libopencv_objdetect.so*"
    ]),
    hdrs = glob([
        "usr/include/**/*.h",
        "usr/include/**/*.hpp",
    ]),
    deps = [
        ":core",
        ":imgproc",
        ":calib3d",
    ],
    linkopts = [
        "-Wl,--no-as-needed," +
        "-l:libopencv_objdetect.so," +
        "-l:libopencv_core.so.4.1," + 
        "-l:libopencv_imgproc.so.4.1," +
        "-l:libopencv_calib3d.so," +
        "--as-needed",
    ],
    strip_include_prefix = "usr/include/opencv4",
    visibility = ["//visibility:public"],
)
