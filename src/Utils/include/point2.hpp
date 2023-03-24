#pragma once
// #include <yaml-cpp/yaml.h>

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
//
// namespace YAML {
// template <typename T> struct convert<sog::Point2<T>> {
//   static Node encode(const sog::Point2<T> &rhs) {
//     Node node;
//     node["x"] = rhs.x;
//     node["y"] = rhs.y;
//     return node;
//   }
//
//   static bool decode(const Node &node, sog::Point2<T> &rhs) {
//
//     // verify
//     if (not node.IsMap() and node.size() != 2)
//       return false;
//
//     if (not(node["x"] and node["y"]))
//       return false;
//
//     // write
//     rhs.x = node["x"];
//     rhs.y = node["y"];
//     return true;
//   }
// };
// }; // namespace YAML
