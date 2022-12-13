#pragma once

#include "_SoundSource.hpp"

#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace sog {
void init_sound_system();

struct element_info {
  int temp = 0;
};

class SoundManager {

  std::unordered_map<std::string, unsigned int> sounds;
  std::vector<std::tuple<std::string, element_info, SoundSource>> elements;

public:
  void load_sound(std::string name, std::string path);
  void add_element(std::string name);
};
} // namespace sog
