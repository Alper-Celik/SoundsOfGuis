#include "MainLoop.hpp"

#include "ExceptionUtils.hpp"
#include "GetDirs.hpp"
#include "ParseConfig.hpp"

#include <boost/predef.h>

#include <deque>
#include <fstream>
#include <iostream>

namespace sog {

MainLoop::MainLoop(std::filesystem::path config_file,
                   std::deque<std::filesystem::path> data_dirs) {
  sog::config config = parse_config(config_file, data_dirs);

  for (auto [type, info] : config.element_infos) {
    sound_manger.load_element(type, info.element_info,
                              info.resolved_sound_file);
    if (info.resolved_sound_file)
      std::cerr << *info.resolved_sound_file;
  }
}

void MainLoop::update_gui_tree() {
  Point2<int> mouse_pos = gui_collector.get_mouse_pos();
  std::optional<GuiElementAtspi2> element_under_cursor =
      gui_collector.get_control_at_pos(mouse_pos);

  std::deque<sog::GuiElementAtspi2>
      new_added_elements; // create new deque to protect classes
                          // integrity in case of exception

  for (auto last_element = element_under_cursor; last_element.has_value();
       last_element = last_element->get_parent()) {
    auto match_iter = std::find(begin(old_element_tree), end(old_element_tree),
                                *last_element);
    if (match_iter == end(old_element_tree)) // does not contains
    {
      new_added_elements.push_front(*last_element);
    } else {
      auto old_last_element_iter = end(old_element_tree) - 1;
      removed_element_count = old_last_element_iter - match_iter;
      goto subtree;
    }
  }

  removed_element_count = old_element_tree.size(); // all elements removed
subtree:
  added_elements = new_added_elements;

  for (int i = 0; i < removed_element_count; i++) {
    old_element_tree.pop_back();
  }

  old_element_tree.insert(end(old_element_tree), begin(added_elements),
                          std::end(added_elements));
};

void MainLoop::update_sounds() {
  for (size_t i = 0; i < removed_element_count; i++) {
    sound_manger.remove_last();
  }

  for (auto &&added_element : added_elements) {
    sound_manger.add_element(added_element.get_type());
  }
  sound_manger.refresh_sounds();
}

} // namespace sog
