
CC=g++
CFLAGS=-lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
SOURCE=main.cpp

all:
	$(CC) $(SOURCE) $(CFLAGS)

