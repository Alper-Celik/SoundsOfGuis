#pragma once

#include "point3.hpp"
#include <filesystem>
#include <optional>

namespace sog {
struct element_info {
  point3 distance_to_other = {0, 0, 0};
  bool is_looping = false;
};

struct complete_element_info {
  element_info element_info;
  std::optional<std::filesystem::path> sound_file;
};
} // namespace sog
