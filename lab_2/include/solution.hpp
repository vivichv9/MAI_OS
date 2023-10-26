#ifndef SOLUTION_HPP_INCLUDED
#define SOLUTION_HPP_INCLUDED

#include "Point.hpp"

#include <iostream>
#include <cmath>
#include <tuple>
#include <cstdint>

namespace lab2 {

struct WorkerResult {
  std::vector<uint64_t> indexes;
  double square;
};

struct MessageToThread {
  std::vector<Point>* vec;
  std::vector<WorkerResult>* res_vec;
  size_t left;
  size_t right;
};

using vector_coords = std::tuple<double, double, double>;

void solution(std::vector<Point>& arr, uint32_t threads_count);

double calculate_triangle_square(const Point& p1, const Point& p2, const Point& p3);

vector_coords calc_vector_coords(const Point& point1, const Point& point2);

vector_coords calc_vectors_product(const vector_coords& v1, const vector_coords& v2);

double calc_vector_norm(const vector_coords& v);

void* worker_func(void* args);

} // lab2

#endif // SOLUTION_HPP_INCLUDED