#include "ParseConfig.hpp"

#include "GetDirs.hpp"

#include <boost/range/adaptor/reversed.hpp>
#include <magic_enum.hpp>
#include <toml++/toml.h>

namespace sog {

namespace fs = std::filesystem;
namespace yaml = YAML;

sog::CompleteElementInfo get_element_info(yaml::Node table) {
  auto info = table.as<sog::CompleteElementInfo>();

  return info;
}

std::deque<fs::path> get_data_dirs(const yaml::Node &data_dirs_array) {
  std::deque<fs::path> data_dirs;
  auto additional_data_dirs = data_dirs_array.as<std::vector<std::string>>();
  for (auto &&additional_data_dir :
       boost::adaptors::reverse(additional_data_dirs)) {

    data_dirs.push_front(additional_data_dir);
  }
  return data_dirs;
}

sog::config
parse_config(std::filesystem::path config_file,
             std::deque<std::filesystem::path> data_dirs,
             sog::CompleteElementInfo default_default_element_info) {
  sog::config ret_val;

  yaml::Node config;

  try {
    config = YAML::LoadFile(std::filesystem::absolute(config_file).string());
  } catch (const std::filesystem::filesystem_error &err) {
    // TODO:
    throw;
  } catch (const toml::parse_error &err) {
    // TODO:
    throw;
  }

  auto config_data_dirs = get_data_dirs(config["data_dirs"]);

  sog::CompleteElementInfo undefined_element_info =
      get_element_info(config["undefined_element"]);

  std::unordered_map<sog::element_type, sog::CompleteElementInfo> element_infos;

  for (auto [enum_value, enum_string] :
       magic_enum::enum_entries<sog::element_type>()) {
    sog::CompleteElementInfo element_info;

    if (config[std::string{enum_string}]) {
      element_infos[enum_value] =
          get_element_info(config[std::string{enum_string}]);
    } else {
      element_infos[enum_value] = undefined_element_info;
    }
  }
  ret_val.element_infos = element_infos;
  ret_val.base_config_dir = config_file.parent_path();
  ret_val.data_dirs = config_data_dirs;
  return ret_val;
}
} // namespace sog
