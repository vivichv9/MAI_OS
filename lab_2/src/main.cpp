#include <iostream>
#include <fstream>
#include <exception>
#include "../include/solution.hpp"

int main(int argc, char** argv) {
  std::ifstream data("/home/kirill/Desktop/study/MAI_OS/lab_2/files/input.txt");

  if (!data.is_open()) {
    throw std::runtime_error("File bad!");
  }

  std::vector<Point> vec;
  Point p;

  while (!data.eof()) {
    data >> p;
    vec.push_back(p);
  }
  
  lab2::solution(vec, std::atoi(argv[1]));

  return 0;
}