#pragma once

#include "defs.h"
#include "point3.hpp"

#include <yaml-cpp/yaml.h>

#include <filesystem>
#include <optional>

namespace sog {
struct ElementInfo {
  Point3<float> distance_to_other = {0, 0, 0};
  bool is_looping = false;
};

struct CompleteElementInfo {
  ElementInfo element_info;
  std::optional<std::filesystem::path> sound_file;
  std::optional<std::filesystem::path>
      resolved_sound_file; // not encoded in yaml
};
} // namespace sog

namespace YAML {
template <> struct convert<sog::CompleteElementInfo> {
  static Node encode(const sog::CompleteElementInfo &rhs) {
    Node node;
    if (rhs.sound_file)
      node["sound_file"] = rhs.sound_file->string();
    node["looping"] = rhs.element_info.is_looping;
    node["distance_to_other"] =
        rhs.element_info.distance_to_other /
        sog::Point3<float>{distance_multiplier, distance_multiplier,
                           distance_multiplier};
    return node;
  }

  static bool decode(const Node &node, sog::CompleteElementInfo &rhs) {

    // verify
    if (not node.IsMap())
      return false;

    std::array<std::string, 3> value_names = {"sound_file", "looping",
                                              "distance_to_other"};
    for (auto i : node) {
      if (std::find(begin(value_names), end(value_names),
                    i.first.as<std::string>()) == end(value_names))
        return false;
    }

    // write
    if (auto sound_file = node["sound_file"]; sound_file)
      rhs.sound_file = sound_file.as<std::string>();

    if (auto looping = node["looping"]; looping)
      rhs.element_info.is_looping = looping.as<bool>();

    if (auto distance_to_other = node["distance_to_other"]; distance_to_other) {
      if (distance_to_other.IsMap())
        rhs.element_info.distance_to_other =
            distance_to_other.as<sog::Point3<float>>() *
            sog::Point3<float>{distance_multiplier, distance_multiplier,
                               distance_multiplier};
      else
        rhs.element_info.distance_to_other.x =
            distance_to_other.as<float>() * distance_multiplier;
    }

    return true;
  }
};
} // namespace YAML
