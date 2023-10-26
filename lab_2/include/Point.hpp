#ifndef POINT_HPP_INCLUDED
#define POINT_HPP_INCLUDED

#include <vector>
#include <iostream>

class Point {
private:
  double x = 0;
  double y = 0;
  double z = 0;

public:
  Point() = default;
  Point(double x, double y, double z) noexcept;
  Point(const std::initializer_list<double>& lst);

  double get_x() const noexcept;
  double get_y() const noexcept;
  double get_z() const noexcept;
  void set_x(double x) noexcept;
  void set_y(double y) noexcept;
  void set_z(double z) noexcept;    

  double calculate_sum() const noexcept;

  std::vector<double> get_all_coords();
};

#endif // POINT_HPP_INCLUDED