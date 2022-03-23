cc_library(
    name = "core",
    srcs = [
        "lib/libopencv_core.so",
        "lib/libopencv_core.so.4.1",
        "lib/libopencv_core.so.4.1.2",
    ],
    hdrs = glob([
        "include/**/*.h",
        "include/**/*.hpp",
    ]),
    linkopts = [
        "-Wl,--no-as-needed," +
        "-l:libopencv_core.so.4.1," +
        "--as-needed",
    ],
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "imgproc",
    srcs = [
        "lib/libopencv_imgproc.so",
        "lib/libopencv_imgproc.so.4.1",
        "lib/libopencv_imgproc.so.4.1.2",
    ],
    hdrs = glob([
        "include/**/*.h",
        "include/**/*.hpp",
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
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "imgcodecs",
    srcs = [
        "lib/libopencv_imgcodecs.so",
        "lib/libopencv_imgcodecs.so.4.1",
        "lib/libopencv_imgcodecs.so.4.1.2",
    ],
    hdrs = glob([
        "include/**/*.h",
        "include/**/*.hpp",
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
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "highgui",
    srcs = [
        "lib/libopencv_highgui.so",
        "lib/libopencv_highgui.so.4.1",
        "lib/libopencv_highgui.so.4.1.2",
    ],
    hdrs = glob([
        "include/**/*.h",
        "include/**/*.hpp",
    ]),
    deps = [
        ":core",
        ":imgproc",
    ],
    linkopts = [
        "-Wl,--no-as-needed," +
        "-l:libopencv_highgui.so.4.1," +
        "-l:libopencv_imgproc.so.4.1," +
        "-l:libopencv_core.so.4.1," +
        "--as-needed",
    ],
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "flann",
    srcs = glob([
        "lib/libopencv_flann.so*"
    ]),
    hdrs = glob([
        "include/**/*.h",
        "include/**/*.hpp",
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
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "features2d",
    srcs = glob([
        "lib/libopencv_features2d.so*"
    ]),
    hdrs = glob([
        "include/**/*.h",
        "include/**/*.hpp",
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
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "calib3d",
    srcs = glob([
        "lib/libopencv_calib3d.so*"
    ]),
    hdrs = glob([
        "include/**/*.h",
        "include/**/*.hpp",
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
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)


cc_library(
    name = "objdetect",
    srcs = glob([
        "lib/libopencv_objdetect.so*"
    ]),
    hdrs = glob([
        "include/**/*.h",
        "include/**/*.hpp",
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
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)
