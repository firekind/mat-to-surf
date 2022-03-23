package(default_visibility = [ "//visibility:public" ])

cc_library(
    name = "nvinfer",
    hdrs = [
        "includes/NvInfer.h",
        "includes/NvInferImpl.h",
        "includes/NvInferRuntime.h",
        "includes/NvInferRuntimeCommon.h",
        "includes/NvInferVersion.h",
        "includes/NvInferLegacyDims.h",
    ],
    includes = [
        "includes",
    ],
    deps = [
        "@cuda_aarch64//:cudart",
    ],
)

cc_library(
    name = "parser",
    hdrs = [
        "includes/NvCaffeParser.h",
        "includes/NvUffParser.h",
    ],
    deps = [
        ":nvinfer",
    ],
    includes = [
        "includes",
    ],
)
