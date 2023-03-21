#pragma once

#include "point3.hpp"
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
};
} // namespace sog
