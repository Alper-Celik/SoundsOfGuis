#include "GetDirs.hpp"
#include "MainLoop.hpp"

#include "QtUiController.hpp"

#include <CLI/CLI.hpp>

#include <filesystem>

int main(int argc, char *argv[]) {
  sog::QtUiController gui; // TODO: pass args to qt app
                           // is that effects thread safety?

  std::filesystem::path config_file = sog::get_config_file();
  std::deque<std::filesystem::path> data_dirs = sog::get_data_dirs();
  CLI::App app{};
  app.add_option("--config-file,-c", config_file, "specify config file");
  app.add_option("--data-dirs,--data-dir,-d", data_dirs,
                 "set data dir(s) overrides XDG_DATA_HOME, ~/local/share/ and "
                 "XDG_DATA_DIRS");
  CLI11_PARSE(app, argc, argv);

  sog::MainLoop loop(config_file, data_dirs);
  while (true) {
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

    gui.update_gui(added_elements_info, loop.removed_element_count);
  }
}
