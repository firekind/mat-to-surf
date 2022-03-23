# nvcr.io/nvidia/deepstream:6.0.1-devel
FROM nvcr.io/nvidia/deepstream@sha256:a825db4ef06341d1c90f67d243f471a27ee29ae28bc39f92a555ca3daa67d8e8

# adding llvm sources list
RUN echo "deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic main\n"\
         "deb-src http://apt.llvm.org/bionic/ llvm-toolchain-bionic main\n"\
         "deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic-13 main\n"\
         "deb-src http://apt.llvm.org/bionic/ llvm-toolchain-bionic-13 main\n"\
         "deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic-14 main\n"\
         "deb-src http://apt.llvm.org/bionic/ llvm-toolchain-bionic-14 main\n"\
    > /etc/apt/sources.list.d/llvm.list && \
    wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -

# installing clang-15
RUN apt update && \
    apt install -y --no-install-recommends software-properties-common && \
    add-apt-repository -y ppa:ubuntu-toolchain-r/test && \
    apt install -y --no-install-recommends clang-15

# adding arm64 architecture to apt and updating sources list
RUN dpkg --add-architecture arm64 && \
    sed -i 's/^deb\(.*$\)/deb [arch=amd64,i386]\1'/ /etc/apt/sources.list && \
    echo "deb [arch=arm64] http://ports.ubuntu.com/ bionic main restricted\n"\
         "deb [arch=arm64] http://ports.ubuntu.com/ bionic-updates main restricted\n"\
         "deb [arch=arm64] http://ports.ubuntu.com/ bionic universe\n"\
         "deb [arch=arm64] http://ports.ubuntu.com/ bionic-updates universe\n"\
         "deb [arch=arm64] http://ports.ubuntu.com/ bionic multiverse\n"\
         "deb [arch=arm64] http://ports.ubuntu.com/ bionic-updates multiverse\n"\
         "deb [arch=arm64] http://ports.ubuntu.com/ bionic-backports main restricted universe multiverse\n"\
    > /etc/apt/sources.list.d/arm-cross-compile-sources.list

# installing deps
RUN apt update && \
    apt install -y --no-install-recommends \
    curl \
    unzip \
    clang-format \
    gcc-aarch64-linux-gnu \
    g++-aarch64-linux-gnu \
    git-lfs \
    rsync \
    ssh \
    ca-certificates \
    libudev-dev \
    gstreamer1.0-plugins-base:arm64

# removing cyclic symlink since bazel doesnt like it
RUN rm /usr/local/cuda-11.4/cuda-11.4