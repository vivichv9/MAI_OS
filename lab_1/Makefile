.PHONY: build run test clean strace

build: clean
	mkdir build
	cd ./build; cmake ..; make all

run:
	./build/*_sh

test:
	./build/*_test

clean:
	rm -rf ./build/

strace:
	cd ./build; strace ./*_sh 	