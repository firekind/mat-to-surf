################################################################################
# Copyright (c) 2017-2021, NVIDIA CORPORATION.  All rights reserved.
#
# NVIDIA Corporation and its licensors retain all intellectual property
# and proprietary rights in and to this software, related documentation
# and any modifications thereto.  Any use, reproduction, disclosure or
# distribution of this software and related documentation without an express
# license agreement from NVIDIA Corporation is strictly prohibited.
#################################################################################

CUDA_VER?=
ifeq ($(CUDA_VER),)
  $(error "CUDA_VER is not set")
endif

CXX:= g++
SRCS:= gst/gstmattosurf.cpp
INCS:= $(wildcard *.h)
LIB:=libmattosurf.so

NVDS_VERSION:=6.0

CFLAGS+= -fPIC -std=c++14 -DDS_VERSION=\"6.0.1\" \
	 -I /usr/local/cuda-$(CUDA_VER)/include \
	 -I ./gst \
	 -I ../third_party/deepstream/sources/includes \

GST_INSTALL_DIR?=/usr/lib/aarch64-linux-gnu/gstreamer-1.0/

LIBS := -shared -Wl,-no-undefined \
	-L/usr/local/cuda-$(CUDA_VER)/lib64/ -lcudart

LIBS+= -L/opt/nvidia/deepstream/deepstream-6.0/lib -lnvdsgst_helper -lnvdsgst_meta -lnvds_meta \
       -lnvds_infer -lnvbufsurface -lnvbufsurftransform -ldl -lpthread \
       -lcuda

LIBS+= -lopencv_core -lopencv_imgproc -lopencv_imgcodecs

OBJS:= $(SRCS:.cpp=.o)

PKGS:= gstreamer-1.0 gstreamer-base-1.0 gstreamer-video-1.0
CFLAGS+=$(shell pkg-config --cflags $(PKGS))
LIBS+=$(shell pkg-config --libs $(PKGS))

MAIN_PKGS:= gstreamer-1.0 glib-2.0
MAIN_CFLAGS:=$(shell pkg-config --cflags $(PKGS))
MAIN_LIBS:=$(shell pkg-config --libs $(PKGS))

all: a.out

%.o: %.cpp $(INCS) Makefile
	$(CXX) -c -o $@ $(CFLAGS) $<

$(LIB): $(OBJS) $(DEP) Makefile
	$(CXX) -o $@ $(OBJS) $(LIBS)

a.out: main.cpp $(LIB)
	$(CXX) $< $(MAIN_CFLAGS) $(MAIN_LIBS) -o $@ 

install: $(LIB)
	cp -rv $(LIB) $(GST_INSTALL_DIR)

clean:
	rm -rf $(OBJS) $(LIB)