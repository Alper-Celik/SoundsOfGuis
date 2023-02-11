#pragma once
namespace sog {
struct Point3 {
  float x = 0, y = 0, z = 0;
  Point3 &operator+=(const Point3 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  };
  Point3 &operator-=(const Point3 &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  };
  Point3 operator+(const Point3 &other) {
    Point3 _out = *this;
    _out += other;
    return _out;
  };
  Point3 operator-(const Point3 &other) {
    Point3 _out = *this;
    _out -= other;
    return _out;
  };
  bool operator==(const Point3 &) const = default;
  bool operator!=(const Point3 &) const = default;
};
} // namespace sog
