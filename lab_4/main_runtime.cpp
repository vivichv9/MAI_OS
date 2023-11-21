#include <iostream>
#include <dlfcn.h>

int (*euclid_GCF)(int, int);
int (*naive_GCF)(int, int);
int (*naive_prime_count)(int, int);
int (*eratosthenes_prime_count)(int, int);

bool init_lib() {
  void* hdl_gcf_lib = dlopen("/home/kirill/Desktop/study/MAI_OS/lab_4/build/libgcf.so", RTLD_LAZY);
  void* hdl_prime_lib = dlopen("/home/kirill/Desktop/study/MAI_OS/lab_4/build/libprime_numbers.so", RTLD_LAZY);

  if (nullptr == hdl_prime_lib) {
    std::cerr << "hdl_prime_lib is nullptr" << std::endl;
    return false;
  }

  if (nullptr == hdl_gcf_lib) {
    std::cerr << "hdl_gcf_lib is nullptr" << std::endl;
    return false;
  }

  euclid_GCF = (int (*)(int, int)) dlsym(hdl_gcf_lib, "_ZN3gcf10euclid_GCFEii");
  naive_GCF = (int (*)(int, int)) dlsym(hdl_gcf_lib, "_ZN3gcf9naive_GCFEii");
  naive_prime_count = (int (*)(int, int)) dlsym(hdl_prime_lib, "_ZN5prime17naive_prime_countEii");
  eratosthenes_prime_count = (int (*)(int, int)) dlsym(hdl_prime_lib, "_ZN5prime24eratosthenes_prime_countEii");
  
  if (euclid_GCF == nullptr) {
    std::cerr << "euclid_GCF is nullptr" << std::endl;
    return false;
  }

  if (naive_GCF == nullptr) {
    std::cerr << "naive_GCF is nullptr" << std::endl;
    return false;
  }

  if (naive_prime_count == nullptr) {
    std::cerr << "naive_prime_count is nullptr" << std::endl;
    return false;
  }

  if (eratosthenes_prime_count == nullptr) {
    std::cerr << "eratosthenes_prime_count is nullptr" << std::endl;
    return false;
  }

  return true;
}



int main(int argc, char** argv) {
  if (argc != 4) {
    std::cerr << "invalid arguments!" << std::endl;
    return -1;
  }

  bool check_flag = init_lib();
  if (check_flag == false) {
    std::cerr << "Error with open libs" << std::endl;
    return -1;
  }

  int mode = std::atoi(argv[1]);
  int a = std::atoi(argv[2]);
  int b = std::atoi(argv[3]);
  int impl_flag = 0;

  switch (mode) {
    case 2:
    std::cout << "Input implementation flag(0 - naive, oth - euclid): ";
      std::cin >> impl_flag;
      
      if (impl_flag == 0) {
        std::cout << "naive gcf implementation: ";
        std::cout << naive_GCF(a, b) << std::endl;
      } else {
        std::cout << "euclid gcf implementation: ";
        std::cout << euclid_GCF(a, b) << std::endl;
      }

    break;

    case 1:
      std::cout << "Input implementation flag(0 - naive, oth - eratosthenes): ";
      std::cin >> impl_flag;
      
      if (impl_flag == 0) {
        std::cout << "naive primes count implementation: ";
        std::cout << naive_prime_count(a, b) << std::endl;
      } else {
        std::cout << "eratosthenes primes count implementation: ";
        std::cout << eratosthenes_prime_count(a, b) << std::endl;
      }
      break;

  default:
    std::cerr << "Invalid flag of mode!" << std::endl;
    break;
  }

  return 0;
}