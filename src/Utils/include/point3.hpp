#pragma once
namespace sog {
template <typename T> struct Point3 {
  T x = 0, y = 0, z = 0;
  Point3<T> &operator+=(const Point3<T> &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  };
  Point3<T> &operator-=(const Point3<T> &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  };
  Point3<T> operator+(const Point3<T> &other) {
    Point3<T> _out = *this;
    _out += other;
    return _out;
  };
  Point3<T> operator-(const Point3<T> &other) {
    Point3<T> _out = *this;
    _out -= other;
    return _out;
  };
  bool operator==(const Point3<T> &) const = default;
  bool operator!=(const Point3<T> &) const = default;
};
} // namespace sog
