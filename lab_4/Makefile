all: create-build exe-runtime exe-comptime

exe-runtime: ./third_party/prime_numbers/include/calculate_prime_numbers.hpp ./third_party/gcf/include/calculate_gcf.hpp main.cpp lib_gcf lib_prime
	g++ main_runtime.cpp -fPIC -L./build -ldl -o ./build/main_runtime

exe-comptime: ./third_party/prime_numbers/include/calculate_prime_numbers.hpp ./third_party/gcf/include/calculate_gcf.hpp main.cpp lib_gcf lib_prime
	g++ main.cpp -fPIC -L./build -lgcf -lprime_numbers -o ./build/main

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