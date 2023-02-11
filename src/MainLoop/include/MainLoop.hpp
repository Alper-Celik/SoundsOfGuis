#pragma once
#include "GuiCollector.hpp"
#include "SoundCode.hpp"

#include <deque>
#include <filesystem>
namespace sog {
class MainLoop {
  sog::GuiCollector gui_collector;
  sog::SoundManager sound_manger;

public:
  std::deque<sog::GuiElement> old_element_tree;
  std::deque<sog::GuiElement> added_elements;
  int removed_element_count{0};

  MainLoop();
  ~MainLoop() = default;
  MainLoop(const MainLoop &) = delete;
  MainLoop &operator=(const MainLoop &) = delete;
  MainLoop &operator=(MainLoop &&) = default;
  MainLoop(MainLoop &&) = default;

  std::filesystem::path get_config_file();
  std::vector<std::filesystem::path> get_data_dirs();
  void update_gui_tree();
  void update_sounds();
};
} // namespace sog
