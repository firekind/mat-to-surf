alias(
    name = "centerface",
    actual = ":libcenterfaceparser.so",
    visibility = [ "//visibility:public" ],
)

cc_binary(
    name = "libcenterfaceparser.so",
    srcs = [
        "centerfaceparser.cpp",
    ],
    deps = [
        "//third_party/deepstream:custom_impl",
    ],
    copts = [
        "-Wno-non-c-typedef-for-linkage",
        "-Wno-unneeded-internal-declaration",
        "-Wno-infinite-recursion",
    ],
    linkshared = True, 
    visibility = [ "//visibility:public" ],
)
