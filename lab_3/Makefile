.PHONY: build

build: clean
	mkdir build
	cd ./build; cmake ..; cmake --build .

run:
	./build/*_main_exe

clean:
	rm -rf ./build/

strace:
	strace -f ./build/*_main_exe

unlink-shm:
	rm /dev/shm/*lab3*