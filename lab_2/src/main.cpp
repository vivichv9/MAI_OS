#include <iostream>

#include "../include/solution.hpp"

int main(int argc, char** argv) {
  std::vector<Point> vec{
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}, 
    {4, 1, 8},
    {9, 1, 4},
    {18, 2, 3}, 
    {12, 4, 5},
    {11, 1, 8},
    {13, 2, 4}
  };

  lab2::solution(vec, 1);

  return 0;
}