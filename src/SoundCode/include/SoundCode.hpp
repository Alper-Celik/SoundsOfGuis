#pragma once

#include "impl/_SoundSource.hpp"

#include "element_info.hpp"
#include "element_type.hpp"
#include "point3.hpp"

#include <optional>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace sog {

unsigned int load_sound(std::string path);
class SoundManager {
public:
  SoundManager() noexcept(false);
  ~SoundManager() = default;

  SoundManager(const SoundManager &) = delete;
  SoundManager &operator=(const SoundManager &) = delete;
  SoundManager(SoundManager &&) = default;
  SoundManager &operator=(SoundManager &&) = default;

private:
  std::unordered_map<sog::element_type,
                     std::pair<std::optional<unsigned int>, ElementInfo>>
      sounds;
  std::vector<std::tuple<sog::element_type, ElementInfo, SoundSource>> elements;

public:
  void load_element(sog::element_type type, ElementInfo element_info,
                    std::optional<std::string> sound_file_path = std::nullopt);

  void add_element(sog::element_type type);
  void remove_last();

  void refresh_sounds();
};
} // namespace sog
