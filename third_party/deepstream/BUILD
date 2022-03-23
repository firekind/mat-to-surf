package(default_visibility = [ "//visibility:public" ])

alias(
    name = "meta",
    actual = select({
        "//bzl:x86_64": "//third_party/deepstream/x86_64:meta",
        "//bzl:aarch64": "//third_party/deepstream/aarch64:meta",
    })
)

alias(
    name = "nvbufsurface",
    actual = select({
        "//bzl:x86_64": "//third_party/deepstream/x86_64:nvbufsurface",
        "//bzl:aarch64": "//third_party/deepstream/aarch64:nvbufsurface",
    })
)

alias(
    name = "custom_impl",
    actual = select({
        "//bzl:x86_64": "//third_party/deepstream/x86_64:custom_impl",
        "//bzl:aarch64": "//third_party/deepstream/aarch64:custom_impl",
    })
)
