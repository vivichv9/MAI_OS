.PHONY: build

build: clean
	mkdir build
	cd ./build; cmake ..; make all

run:
	./build/*_main_exe

clean:
	rm -rf ./build/

strace:
	strace -f ./build/*_main_exe

unlink-shm:
	chmod +x ./bash/unlink_mmf.sh
	./bash/unlink_mmf.sh