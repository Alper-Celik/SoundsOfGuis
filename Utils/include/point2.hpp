#pragma once
namespace sog {
struct point2 {
  float x = 0, y = 0;
  point2 &operator+=(const point2 &other) {
    x += other.x;
    y += other.y;
    return *this;
  };
  point2 &operator-=(const point2 &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  };
  point2 operator+(const point2 &other) {
    point2 _out = *this;
    _out += other;
    return _out;
  };
  point2 operator-(const point2 &other) {
    point2 _out = *this;
    _out -= other;
    return _out;
  };
  bool operator==(const point2 &) const = default;
  bool operator!=(const point2 &) const = default;
};
} // namespace sog
