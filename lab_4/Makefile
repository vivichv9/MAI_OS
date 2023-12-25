all: create-build exe-runtime exe-comptime

exe-runtime: comp lib_gcf lib_prime
	g++ ./build/main_runtime.o -fPIC -L./build -ldl -o ./build/main_runtime

exe-comptime: comp lib_gcf lib_prime
	g++ ./build/main.o -fPIC -L./build -lgcf -lprime_numbers -o ./build/main

lib_gcf: ./third_party/gcf/include/calculate_gcf.hpp ./third_party/gcf/src/calculate_gcf.cpp 
	g++ -shared ./third_party/gcf/src/calculate_gcf.cpp -fPIC -o ./build/libgcf.so

lib_prime: ./third_party/prime_numbers/include/calculate_prime_numbers.hpp ./third_party/prime_numbers/src/calculate_prime_numbers.cpp
	g++ -shared ./third_party/prime_numbers/src/calculate_prime_numbers.cpp -fPIC -o ./build/libprime_numbers.so

create-build:
	mkdir -p ./build

run-runtime:
	cd build; ./main_runtime $(mode) $(a) $(b)

run-comptime:
	cd build; ./main $(mode) $(a) $(b)

clean:
	rm -rf build

comp: ./third_party/prime_numbers/include/calculate_prime_numbers.hpp ./third_party/gcf/include/calculate_gcf.hpp main.cpp
	cd build; g++ -c ../main_runtime.cpp ../main.cpp