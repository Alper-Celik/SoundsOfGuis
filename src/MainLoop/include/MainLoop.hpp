#pragma once
#include "GetDirs.hpp"
#include "GuiCollector.hpp"
#include "SoundCode.hpp"

#include <deque>
#include <filesystem>
namespace sog {
class MainLoop {
  std::unique_ptr<sog::GuiCollector> gui_collector;
  sog::SoundManager sound_manger;

public:
  std::deque<std::shared_ptr<sog::GuiElement>> old_element_tree;
  std::deque<std::shared_ptr<sog::GuiElement>> added_elements;
  int removed_element_count{0};

  MainLoop(std::unique_ptr<sog::GuiCollector> guiCollector,
           std::filesystem::path config_file = get_config_file(),
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
