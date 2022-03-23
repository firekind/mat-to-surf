INCLUDE_PREFIX = "include/glib-2.0/"

cc_library(
    name = "sub_glib",
    hdrs = [
        INCLUDE_PREFIX + "glib.h",
    ] + glob([
        INCLUDE_PREFIX + "glib/**/*.h",
    ]),
    linkopts = [
        "-l:libglib-2.0.so.0",
    ],
    deps = [
        ":glibconfig",
    ],
    includes = [
        INCLUDE_PREFIX
    ],
    strip_include_prefix = INCLUDE_PREFIX
)

cc_library(
    name = "glibconfig",
    hdrs = [
        "lib/x86_64-linux-gnu/glib-2.0/include/glibconfig.h",
    ],
    includes = [
        "x86_64-linux-gnu/glib-2.0/include"
    ], 
    strip_include_prefix = "lib/x86_64-linux-gnu/glib-2.0/include"
)

cc_library(
    name = "gobject",
    hdrs = [
        INCLUDE_PREFIX + "glib-object.h",
    ] + glob([
        INCLUDE_PREFIX + "gobject/**/*.h",
    ]),
    linkopts = [
        "-l:libgobject-2.0.so.0",
    ],
    deps = [
        ":sub_glib",
    ],
    includes = [
        INCLUDE_PREFIX
    ],
    strip_include_prefix = INCLUDE_PREFIX
)

cc_library(
    name = "gmodule",
    hdrs = [
        INCLUDE_PREFIX + "gmodule.h",
    ],
    linkopts = [
        "-l:libgmodule-2.0.so.0",
    ],
    deps = [
        ":sub_glib",
    ],
    includes = [
        INCLUDE_PREFIX
    ],
    strip_include_prefix = INCLUDE_PREFIX,
)

cc_library(
    name = "gio-unix",
    hdrs = glob([
        "include/gio-unix-2.0/gio/**/*.h",
    ]),
    includes = [
        "include/gio-unix-2.0/gio",
    ],
    strip_include_prefix = "include/gio-unix-2.0/gio",
)

cc_library(
    name = "gio",
    hdrs = glob([
        INCLUDE_PREFIX + "gio/**/*.h",
    ]),
    linkopts = [
        "-l:libgio-2.0.so.0",
    ],
    deps = [
        ":gio-unix",
        ":sub_glib",
    ],
    includes = [
        INCLUDE_PREFIX
    ],
    strip_include_prefix = INCLUDE_PREFIX
)


cc_library(
    name = "glib",
    deps = [
        ":sub_glib",
        ":gobject",
        ":gmodule",
        ":gio",
    ],
    visibility = ["//visibility:public"],
)