load("//bzl:rules.bzl", "pkgfy")

filegroup(
    name = "data",
    srcs = [
        "pipeline.txt",
        "//mat-to-surf/config",
        "//mat-to-surf/model",
        "//mat-to-surf/customparser",
    ],
    visibility = [ "//visibility:public" ]
)

cc_binary(
    name = "mat-to-surf",
    srcs = [
        "main.cpp"
    ],
    deps = [
        "@gstreamer"
    ],
    data = [
        ":data",
        "//mat-to-surf/gst:libgstmattosurf.so",
    ],
    linkopts = [
        "-pthread",
    ],
)

pkgfy(
    name = "pkg",
    srcs = [
        ":mat-to-surf",
    ],
)
