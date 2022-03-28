# NvBufSurface to cv Mat

Test repo for this [deepstream issue](https://forums.developer.nvidia.com/t/memory-leak-when-copying-opencv-mat-to-nvbufsurface-on-jetson/208941)

# Run

To run the application on jetson, first build the custom parser for centerface:

```
$ cd mat-to-surf/customparser/centerface
$ CUDA_VER=10.2 make
```

once done, build the application

```
$ cd ../../
$ CUDA_VER=10.2 make
```

then run the application 

```
$ ./a.out
```