#pragma once
#include "GetDirs.hpp"
#include "GuiCollector.hpp"
#include "SoundCode.hpp"

#include <deque>
#include <filesystem>
namespace sog {
class MainLoop {
  sog::GuiCollector gui_collector;
  sog::SoundManager sound_manger;

public:
  std::deque<sog::GuiElementAtspi2> old_element_tree;
  std::deque<sog::GuiElementAtspi2> added_elements;
  int removed_element_count{0};

  MainLoop(std::filesystem::path config_file = get_config_file(),
           std::deque<std::filesystem::path> data_dirs = get_data_dirs());
  ~MainLoop() = default;
  MainLoop(const MainLoop &) = delete;
  MainLoop &operator=(const MainLoop &) = delete;
  MainLoop &operator=(MainLoop &&) = default;
  MainLoop(MainLoop &&) = default;

  void update_gui_tree();
  void update_sounds();
};
} // namespace sog
