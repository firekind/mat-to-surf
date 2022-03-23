workspace(name = "mat_to_surf")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

new_local_repository(
    name = "glib",
    build_file = "//third_party:glib.BUILD",
    path = "/usr",
)

new_local_repository(
    name = "gstreamer",
    build_file = "//third_party:gstreamer.BUILD",
    path = "/usr",
)

new_local_repository(
    name = "gst_plugins_base",
    build_file = "//third_party:gst_plugins_base.BUILD",
    path = "/usr",
)

http_archive(
    name = "opencv_x86_64",
    url = "https://developer.nvidia.com/isaac/download/third_party/libopencv_4_1_2_x86_64-tar-xz",
    type = "tar.xz",
    build_file = "//third_party:opencv_x86_64.BUILD",
    sha256 = "9123df1c86180a920aea4469499aec372e4567e970eb0de7353c4e3e3eb30ec8",
)

http_archive(
    name = "opencv_aarch64",
    url = "https://developer.nvidia.com/isaac/download/third_party/libopencv_4_1_jetpack44-tar-xz",
    type = "tar.xz",
    build_file = "//third_party:opencv_aarch64.BUILD",
    sha256 = "e88582b4dd4b226f9eb17b9b9b616381ac20e75d2f62db3c05044e2f5d0d06dd",
)

new_local_repository(
    name = "cuda_x86_64",
    build_file = "//third_party:cuda_x86_64.BUILD",
    path = "/usr/local/cuda-11.4"
)

http_archive(
    name = "cuda_aarch64",
    build_file = "//third_party:cuda_aarch64.BUILD",
    sha256 = "53e0a2f45088878f00f3913070ab6d57efedc8b19fbf9d36564967c99a1dfe75",
    url = "https://developer.nvidia.com/isaac/download/third_party/cuda_10_2_cudnn_8_jp44_ga_hdr-tar-bz2",
    type = "tar.bz2",
)
