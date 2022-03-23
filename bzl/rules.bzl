def _pkgfy_impl(ctx):
    arg_compression = ""

    # Analyse desired compression
    if ctx.attr.extension:
        dotPos = ctx.attr.extension.find(".")
        if dotPos > 0:
            dotPos += 1
            suffix = ctx.attr.extension[dotPos:]
            if suffix == "gz":
                arg_compression = "--gzip"
            elif suffix == "bz2":
                arg_compression = "--bzip2"
            else:
                fail("Unsupported compression '%s'" % ctx.attr.extension)

    files = depset()

    # Collect all datafiles of all data
    for dep in ctx.attr.data:
        if hasattr(dep, "data_runfiles"):
            files = depset(transitive = [files, dep.data_runfiles.files])

    # Collect all runfiles of all dependencies
    for dep in ctx.attr.srcs:
        if hasattr(dep, "default_runfiles"):
            files = depset(transitive = [files, dep.default_runfiles.files])
    files = files.to_list()

    exc_files = depset()
    for dep in ctx.attr.excludes:
        if hasattr(dep, "default_runfiles"):
            exc_files = depset(transitive = [exc_files, dep.default_runfiles.files])
    exc_files = exc_files.to_list()

    for f in exc_files:
        if not f.is_source and f in files:
            files.remove(f)

    # Create a space-separate string with paths to all files
    file_list = " ".join([f.path for f in files])

    # Setup a rule to move files from bazel-out to the root folder
    bazel_out_rename = "--transform='flags=r;s|bazel-out/k8-opt/bin/||' " + \
                       "--transform='flags=r;s|bazel-out/k8-fastbuild/bin/||' " + \
                       "--transform='flags=r;s|bazel-out/aarch64-opt/bin/||' " + \
                       "--transform='flags=r;s|bazel-out/aarch64-fastbuild/bin/||' " + \
                       "--transform='flags=r;s|" + ctx.attr.strip_prefix + "||' "

    # Additional replacement rules
    for key, value in ctx.attr.remap_paths.items():
        bazel_out_rename += "--transform='flags=r;s|%s|%s|' " % (key, value)

    # Create the tar archive
    ctx.actions.run_shell(
        command = "tar --hard-dereference %s %s  -chf %s %s" %
                  (arg_compression, bazel_out_rename, ctx.outputs.out.path, file_list),
        inputs = files,
        outputs = [ctx.outputs.out],
        use_default_shell_env = True,
    )

# A rule which creates a tar package with the executable and all necessary runfiles compared to
# pkg_tar which needs manual dependency tracing.
pkgfy = rule(
    implementation = _pkgfy_impl,
    executable = False,
    attrs = {
        "srcs": attr.label_list(allow_files = True),
        "data": attr.label_list(allow_files = True),
        "extension": attr.string(default = "tar"),
        "strip_prefix": attr.string(default = ""),
        "remap_paths": attr.string_dict(),
        "excludes": attr.label_list(allow_files = True),
    },
    outputs = {
        "out": "%{name}.%{extension}",
    },
)
