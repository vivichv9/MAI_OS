.PHONY: build run clean strace

build: clean
	mkdir build
	cd ./build; cmake ..; make all

run:
	./build/*_sh

clean:
	rm -rf ./build/

strace:
	cd ./build; strace ./*_sh 	