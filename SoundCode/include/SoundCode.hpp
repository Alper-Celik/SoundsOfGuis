#pragma once
#include <al.h>
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
  using buffer_handle_t = unsigned int;
  using source_handle_t = unsigned int;

  std::unordered_map<std::string, buffer_handle_t> sounds;
  std::vector<std::tuple<std::string, element_info, source_handle_t>> elements;

public:
  void load_sound(std::string name, std::string path);
  void add_element(std::string name);
};
} // namespace sog
