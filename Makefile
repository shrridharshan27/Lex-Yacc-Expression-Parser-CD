CC = gcc
CFLAGS = -std=c99 -Wall -Wextra

all: build/standalone_parser

build/standalone_parser: src/standalone_parser.c
	mkdir -p build
	$(CC) $(CFLAGS) src/standalone_parser.c -o build/standalone_parser

run: all
	./build/standalone_parser

clean:
	rm -rf build *.exe
