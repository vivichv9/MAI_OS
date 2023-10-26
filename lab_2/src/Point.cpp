#include "../include/Point.hpp"

Point::Point(double x, double y, double z) noexcept : x(x), y(y), z(z) {}

Point::Point(const std::initializer_list<double>& lst) {
  if (lst.size() != 3) {
    throw std::invalid_argument("incorrect size of initializer list!");
  }

  auto it = lst.begin();
  x = *it;
  y = *(++it);
  z = *(++it);
}

void Point::set_x(double x) noexcept {
  this->x = x;
}

void Point::set_y(double y) noexcept {
  this->y = y;
}

void Point::set_z(double z) noexcept {
  this->z = z;
}

double Point::get_x() const noexcept {
  return x;
}

double Point::get_y() const noexcept {
  return y;
}

double Point::get_z() const noexcept {
  return z;
}

double Point::calculate_sum() const noexcept {
  return x + y + z;
}

std::vector<double> Point::get_all_coords() {
  return std::vector<double>{x, y, z};
}

std::istream& operator>>(std::istream& is, Point& rhs) {
  is >> rhs.x >> rhs.y >> rhs.z;
  return is;
}