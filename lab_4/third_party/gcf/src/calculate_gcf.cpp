#include "../include/calculate_gcf.hpp"

int gcf::euclid_GCF(int A, int B) {
  while (B != 0) {
    int temp = B;
    B = A % B;
    A = temp;
  }

  return A;
}

int gcf::naive_GCF(int A, int B) {
  int gcd = 1;

  for (int i = 2; i <= A && i <= B; ++i) {
    if (A % i == 0 && B % i == 0) {
      gcd = i;
    }
  }

  return gcd;
}

