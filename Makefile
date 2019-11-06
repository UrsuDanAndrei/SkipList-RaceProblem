.PHONY: build clean

CC = g++
CFLAGS = -Wall -Wextra -Wno-unused-parameter -std=c++11 -g

build: main.cpp
	${CC} ${CFLAGS} main.cpp -o exe

clean:
	rm -f exe
