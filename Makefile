
CC=g++
CFLAGS=-lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
CPPOUT=out/a.out
WASMCOMP=em++
WASMFLAGS=-std=c++17 -O2 -s ALLOW_MEMORY_GROWTH=1 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2 -s USE_LIBPNG=1 -s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=4 --emrun
WASMOUT=out/out.html
SOURCE=main.cpp

all:
	$(CC) $(SOURCE) $(CFLAGS)

wasm:
	$(WASMCOMP) $(WASMFLAGS) $(SOURCE) -o $(WASMOUT)
