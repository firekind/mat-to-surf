package(default_visibility = ["//visibility:public"])

INCLUDE_PREFIX = "usr/local/cuda-10.2/targets/aarch64-linux/include/"
LIB_PATH = "usr/local/cuda-10.2/targets/aarch64-linux/lib"

cc_library(
    name = "cudart",
    hdrs = glob([
        INCLUDE_PREFIX + "*.h",
        INCLUDE_PREFIX + "*.hpp",
        INCLUDE_PREFIX + "CL/*.h",
        INCLUDE_PREFIX + "crt/*",
    ])
    srcs = glob([
        "usr/local/cuda-10.2/targets/aarch64-linux/lib/libcudart.so*"
    ])
    linkopts = [
        "-lcudart",
    ],
    strip_include_prefix = INCLUDE_PREFIX,
)
