#pragma once
namespace sog {
struct point3 {
  float x = 0, y = 0, z = 0;
  point3 &operator+=(const point3 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  };
  point3 &operator-=(const point3 &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  };
  point3 operator+(const point3 &other) {
    point3 _out = *this;
    _out += other;
    return _out;
  };
  point3 operator-(const point3 &other) {
    point3 _out = *this;
    _out -= other;
    return _out;
  };
  bool operator==(const point3 &) const = default;
  bool operator!=(const point3 &) const = default;
};
} // namespace sog
