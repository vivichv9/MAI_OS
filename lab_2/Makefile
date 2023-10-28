.PHONY: build run clean strace gen-data

build: clean
	mkdir build
	cd ./build; cmake ..; make all

run:
	./build/*_exe $(threads)

clean:
	rm -rf ./build/

strace:
	strace -f ./build/*_exe 16

gen-data:
	python3 ./generator/generator.py

show-stat:
	python3 ./analytics/create_graphic.py