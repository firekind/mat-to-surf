# NvBufSurface to cv Mat

Test repo for this [deepstream issue](https://forums.developer.nvidia.com/t/memory-leak-when-copying-opencv-mat-to-nvbufsurface-on-jetson/208941)

# Run

run the application with the following command:

```
$ bazel run //mat-to-surf
```

To package it for jetson, run 

```
$ bazel build --config aarch64 //mat-to-surf:pkg
```

this will create a tar file in `bazel-bin/mat-to-surf/pkg.tar`. The app can be run on the docker image: nvcr.io/nvidia/deepstream-l4t:6.0.1-base (sha256:c9ca4d742c0d142db6db4e84ed0192f94cf4a883e3e4f75c4da40c5704b56a5a). Run `apt install libtbb2` before running the application. You'll have to update the paths in `mat-to-surf/pipeline.txt` and in `mat-to-surf/config/centerface.txt`
