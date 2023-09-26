.PHONY: build run clean strace

build: clean
	mkdir build
	cd ./build; cmake ..; make all

run:
	./build/*_main_exe

clean:
	rm -rf ./build/

strace:
	strace -f ./build/*_main_exe 	