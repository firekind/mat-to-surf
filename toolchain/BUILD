package(default_visibility = ["//visibility:public"])

load(":cc_toolchain_config.bzl", "cc_toolchain_config")
load("@rules_cc//cc:defs.bzl", "cc_toolchain", "cc_toolchain_suite")

filegroup(
    name = "empty",
    srcs = [],
)

# This is the entry point for --crosstool_top.  Toolchains are found
# by lopping off the name of --crosstool_top and searching for
# the "${CPU}" entry in the toolchains attribute.
cc_toolchain_suite(
    name = "toolchain",
    toolchains = {
        "k8": ":cc-compiler-k8",
        "aarch64": ":cc-compiler-aarch64",
    },
)

cc_toolchain(
    name = "cc-compiler-k8",
    toolchain_identifier = "local",
    toolchain_config = ":local",
    all_files = ":empty",
    ar_files = ":empty",
    as_files = ":empty",
    compiler_files = ":empty",
    dwp_files = ":empty",
    linker_files = ":empty",
    objcopy_files = ":empty",
    strip_files = ":empty",
    supports_param_files = 1,
)

cc_toolchain_config(
    name = "local",
    cpu = "k8",
    compiler = "compiler",
    toolchain_identifier = "local",
    host_system_name = "local",
    target_system_name = "local",
    target_libc = "local",
    abi_version = "local",
    abi_libc_version = "local",
    cxx_builtin_include_directories = [
        "/usr/lib/llvm-15/lib/clang/15.0.0/include",
        "/usr/local/include",
        "/usr/include/x86_64-linux-gnu",
        "/usr/include",
        "/usr/lib/llvm-15/lib/clang/15.0.0/share",
        "/usr/include/c++/7",
        "/usr/include/x86_64-linux-gnu/c++/7",
        "/usr/include/c++/7/backward",
        "/usr/lib/clang/15.0.0/include",
    ],
    tool_paths = {
        "ar": "/usr/bin/ar",
        "ld": "/usr/bin/ld",
        "cpp": "/usr/bin/clang-15",
        "gcc": "/usr/bin/clang-15",
        "dwp": "/usr/bin/dwp",
        "gcov": "/usr/bin/gcov",
        "nm": "/usr/bin/nm",
        "objcopy": "/usr/bin/objcopy",
        "objdump": "/usr/bin/objdump",
        "strip": "/usr/bin/strip"
    },
    compile_flags = [
        "-U_FORTIFY_SOURCE",
        "-fstack-protector",
        "-Wall",
        "-Wthread-safety",
        "-Wself-assign",
        "-Wunused-but-set-parameter",
        "-Wno-unused-but-set-variable",
        "-Wno-free-nonheap-object",
        "-fcolor-diagnostics",
        "-fno-omit-frame-pointer"
    ],
    opt_compile_flags = [
        "-g0",
        "-O2",
        "-D_FORTIFY_SOURCE=1",
        "-DNDEBUG",
        "-ffunction-sections",
        "-fdata-sections"
    ],
    dbg_compile_flags = ["-g"],
    cxx_flags = ["-std=c++14"],
    link_flags = [
        "-fuse-ld=/usr/bin/ld.gold",
        "-Wl,-z,relro,-z,now",
        "-B/usr/bin",
        "-lstdc++",
        "-lm"
    ],
    link_libs = [],
    opt_link_flags = ["-Wl,--gc-sections"],
    unfiltered_compile_flags = [
        "-no-canonical-prefixes",
        "-Wno-builtin-macro-redefined",
        "-D__DATE__=\"redacted\"",
        "-D__TIMESTAMP__=\"redacted\"",
        "-D__TIME__=\"redacted\""
    ],
    coverage_compile_flags = ["--coverage"],
    coverage_link_flags = ["--coverage"],
    supports_start_end_lib = True,
)

cc_toolchain(
    name = "cc-compiler-aarch64",
    toolchain_identifier = "aarch64",
    toolchain_config = ":jetson-config",
    all_files = ":empty",
    ar_files = ":empty",
    as_files = ":empty",
    compiler_files = ":empty",
    dwp_files = ":empty",
    linker_files = ":empty",
    objcopy_files = ":empty",
    strip_files = ":empty",
    supports_param_files = 1,
)

cc_toolchain_config(
    name = "jetson-config",
    cpu = "aarch64",
    compiler = "aarch64",
    toolchain_identifier = "aarch64",
    host_system_name = "local",
    target_system_name = "aarch64",
    target_libc = "aarch64",
    abi_version = "aarch64",
    abi_libc_version = "aarch64",
    cxx_builtin_include_directories = [
        "/usr/lib/llvm-15/lib/clang/15.0.0/include",
        "/usr/aarch64-linux-gnu/include",
        "/usr/include/aarch64-linux-gnu",
        "/usr/aarch64-linux-gnu/include/c++/7",
        "/usr/lib/gcc-cross/aarch64-linux-gnu/7/include",
        "/usr/lib/gcc-cross/aarch64-linux-gnu/7/include-fixed",
        "/usr/aarch64-linux-gnu/include/c++/7/backward",
        "/usr/aarch64-linux-gnu/include",
        "/usr/lib/llvm-15/lib/clang/15.0.0/share",
        "/usr/lib/clang/15.0.0/include",
        "/usr/include",
    ],
    tool_paths = {
        "ar": "/usr/bin/aarch64-linux-gnu-ar",
        "ld": "/usr/bin/aarch64-linux-gnu-ld",
        "cpp": "/usr/bin/clang-15",
        "gcc": "/usr/bin/clang-15",
        "dwp": "/usr/bin/aarch64-linux-gnu-dwp",
        "gcov": "/usr/bin/aarch64-linux-gnu-gcov",
        "nm": "/usr/bin/aarch64-linux-gnu-nm",
        "objcopy": "/usr/bin/aarch64-linux-gnu-objcopy",
        "objdump": "/usr/bin/aarch64-linux-gnu-objdump",
        "strip": "/usr/bin/aarch64-linux-gnu-strip"
    },
    compile_flags = [
        "-U_FORTIFY_SOURCE",
        "-fstack-protector",
        "-Wall",
        "-Werror",
        "-Wunused-but-set-parameter",
        "-Wno-unused-but-set-variable",
        "-Wno-free-nonheap-object",
        "-fno-omit-frame-pointer"
    ],
    opt_compile_flags = [
        "-g0",
        "-O2",
        "-D_FORTIFY_SOURCE=1",
        "-DNDEBUG",
        "-ffunction-sections",
        "-fdata-sections"
    ],
    dbg_compile_flags = ["-g"],
    cxx_flags = ["-std=c++14"],
    link_flags = [
        "-Wl,--dynamic-linker=/lib/ld-linux-aarch64.so.1",
        "-Wl,-no-as-needed,-lstdc++,-as-needed",
        "-Wl,-z,relro,-z,now",
    ],
    link_libs = [],
    opt_link_flags = [
        "-Wl,--gc-sections",
    ],
    unfiltered_compile_flags = [
        "-Wno-builtin-macro-redefined",
        "-D__DATE__=\"redacted\"",
        "-D__TIMESTAMP__=\"redacted\"",
        "-D__TIME__=\"redacted\""
    ],
    supports_start_end_lib = False,
)
