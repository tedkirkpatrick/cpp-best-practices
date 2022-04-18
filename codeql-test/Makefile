# Build example for CodeQL testing

sanitizers=-fsanitize=address,undefined
warnings= -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wimplicit-fallthrough -Werror
debug=-g -O0
std=-std=c++20

.PHONY: all
all: test


test:	test.cpp
	g++ $(sanitizers) $(warnings) $(debug) $(std) test.cpp -o test
