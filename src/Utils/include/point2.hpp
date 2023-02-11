#pragma once
namespace sog {
template <typename T = float> struct Point2 {
  T x = 0, y = 0;
  Point2<T> &operator+=(const Point2<T> &other) {
    x += other.x;
    y += other.y;
    return *this;
  };
  Point2<T> &operator-=(const Point2<T> &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  };
  friend Point2<T> &operator/=(Point2<T> &lhs, const Point2<T> &rhs) {
    lhs.x /= rhs.x;
    lhs.y /= rhs.y;
    return lhs;
  }
  Point2<T> operator+(const Point2<T> &other) {
    Point2<T> _out = *this;
    _out += other;
    return _out;
  };
  Point2<T> operator-(const Point2<T> &other) {
    Point2<T> _out = *this;
    _out -= other;
    return _out;
  };

  friend Point2<T> operator/(const Point2<T> &lhs, const Point2<T> &rhs) {
    Point2<T> out = lhs;
    out /= rhs;
    return out;
  }
  bool operator==(const Point2<T> &) const = default;
  bool operator!=(const Point2<T> &) const = default;
};
} // namespace sog
