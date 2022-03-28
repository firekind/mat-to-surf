# nvcr.io/nvidia/deepstream-l4t:6.0.1-base
FROM nvcr.io/nvidia/deepstream-l4t@sha256:c9ca4d742c0d142db6db4e84ed0192f94cf4a883e3e4f75c4da40c5704b56a5a

RUN apt update && \
    apt install -y --no-install-recommends \
        libopencv-dev \
        libgstreamer1.0-dev \
        libgstreamer-plugins-base1.0-dev
