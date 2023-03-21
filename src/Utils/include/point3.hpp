#pragma once
#include <yaml-cpp/yaml.h>
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

namespace YAML {
template <typename T> struct convert<sog::Point3<T>> {
  static Node encode(const sog::Point3<T> &rhs) {
    Node node;
    node["x"] = rhs.x;
    node["y"] = rhs.y;
    node["z"] = rhs.z;
    return node;
  }

  static bool decode(const Node &node, sog::Point3<T> &rhs) {

    // verify
    if (not node.IsMap() and node.size() != 3)
      return false;

    std::array<std::string, 3> valid_ids{"x", "y", "z"};
    for (auto i : node) {
      if (std::find(begin(valid_ids), end(valid_ids),
                    i.first.as<std::string>()) == end(valid_ids))
        return false;
    }

    // write
    rhs.x = node["x"];
    rhs.y = node["y"];
    rhs.z = node["z"];
    return true;
  }
};
} // namespace YAML
