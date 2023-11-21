#include "../include/calculate_prime_numbers.hpp"

int prime::eratosthenes_prime_count(int A, int B) {
  std::vector<bool> isPrime(B + 1, true);

  isPrime[0] = isPrime[1] = false;

  for (int i = 2; i * i <= B; ++i) {
    if (isPrime[i]) {
      for (int j = i * i; j <= B; j += i) {
        isPrime[j] = false;
      }
    }
  }

  int count = 0;
  for (int i = A; i <= B; ++i) {
    if (isPrime[i]) {
      ++count;
    }
  }

  return count;
}

int prime::naive_prime_count(int A, int B) {
  int count = 0;

  for (int i = A; i <= B; ++i) {
    if (i == 1 || i == 0) {
      continue;
    }

    bool flag = true;
    for (int j = 2; j <= std::sqrt(i); ++j) {
      if (i % j == 0) {
        flag = false;
        break;
      }
    }

    if (flag == true) {
      ++count;
    }
  }

  return count;
}