#include <iostream>
#include "third_party/prime_numbers/include/calculate_prime_numbers.hpp"
#include "third_party/gcf/include/calculate_gcf.hpp"

int main(int argc, char** argv) {
  if (argc != 4) {
    std::cerr << "Invalid input data!\nExample:\nmake mode=1 a=1 b=1\nor\nmake run mode=2 a=1 b=1" << std::endl;
    return -1;
  }

  int mode = std::atoi(argv[1]);

  if (mode != 1 && mode != 2) {
    std::cerr << "Invalid data!\nValid value of variable \"mode\" is 1 or 2" << std::endl;
    return -1;
  }

  int a = std::atoi(argv[2]);
  int b = std::atoi(argv[3]);

  switch (mode) {
    case 1:
      std::cout << "Your choice: primes count" << std::endl;
      std::cout << "Naive implement: " << prime::naive_prime_count(a, b) << std::endl;
      std::cout << "Eratosthenes method: " << prime::eratosthenes_prime_count(a, b) << std::endl;
      return 0;
    
    case 2:
      std::cout << "Your choice: GCF" << std::endl;
      std::cout << "Naive implement: " << gcf::naive_GCF(a, b) << std::endl;
      std::cout << "Euclid method: " << gcf::euclid_GCF(a, b) << std::endl;
      return 0;
  }
}