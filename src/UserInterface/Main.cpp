#include "GetDirs.hpp"
#include "MainLoop.hpp"

#include "QtUiController.hpp"

#include <CLI/CLI.hpp>

int main(int argc, char *argv[]) {
  sog::QtUiController gui;
  CLI::App app{};

  while (true) {
    sog::MainLoop loop;
    loop.update_gui_tree();
    loop.update_sounds();

    std::vector<sog::ElementDisplayInfo> added_elements_info;
    for (auto &&added_element : loop.added_elements) {
      added_elements_info.push_back(sog::ElementDisplayInfo{
          .detected_type = added_element.get_type(),
          .native_type_name = added_element.get_native_element_type_name(),
          .native_type_enum_name =
              added_element.get_native_element_type_enum_name()});
    }

    gui.update_ui(added_elements_info, loop.removed_element_count);
  }
}
