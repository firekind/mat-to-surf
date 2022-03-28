CUDA_VER?=
ifeq ($(CUDA_VER),)
  $(error "CUDA_VER is not set")
endif

CC:= g++

CFLAGS:= -Wall -std=c++14

CFLAGS+= -shared -fPIC

CFLAGS+= -I../../../third_party/deepstream/sources/includes \
		-I/usr/local/cuda-$(CUDA_VER)/include

LIBS:= -L/opt/nvidia/deepstream/deepstream-6.0/lib -lnvinfer -lnvparsers
LFLAGS:= -Wl,--start-group $(LIBS) -Wl,--end-group

SRCFILES:=  centerfaceparser.cpp
TARGET_LIB:= libcenterfaceparser.so

all: $(TARGET_LIB)

$(TARGET_LIB) : $(SRCFILES)
	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)

clean:
	rm -rf $(TARGET_LIB)