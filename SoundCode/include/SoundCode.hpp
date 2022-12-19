#pragma once

#include "impl/_SoundSource.hpp"

#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace sog {

struct element_info {
  int temp = 0;
};

class SoundManager {
private:
  std::unordered_map<std::string, unsigned int> sounds;
  std::vector<std::tuple<std::string, element_info, SoundSource>> elements;

public:
  void load_sound(std::string name, std::string path);
  void add_element(std::string name);
};
} // namespace sog
