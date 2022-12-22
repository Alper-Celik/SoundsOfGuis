#pragma once

#include "impl/_SoundSource.hpp"
#include "point3.hpp"

#include <optional>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace sog {

struct element_info {
  point3 distance_to_other = {0, 0, 0};
  bool is_looping = false;
};
unsigned int load_sound(std::string path);
class SoundManager {
private:
  std::unordered_map<std::string,
                     std::pair<std::optional<unsigned int>, element_info>>
      sounds;
  std::vector<std::tuple<std::string, element_info, SoundSource>> elements;

public:
  void load_element(std::string name, element_info element_info,
                    std::optional<std::string> sound_file_path = std::nullopt);

  void add_element(std::string name);
  void remove_last();

  void refresh_sounds();
};
} // namespace sog
