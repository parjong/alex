all: build test

cmake:
	mkdir cmake
	cd cmake && cmake ..

build: cmake
	cd cmake && make

test: cmake
	cd cmake && make test
