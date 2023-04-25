#include "ParseConfig.hpp"

#include "GetDirs.hpp"

#include <boost/range/adaptor/reversed.hpp>
#include <iostream>
#include <magic_enum.hpp>
#include <toml++/toml.h>

namespace sog {

namespace fs = std::filesystem;
namespace yaml = YAML;

std::optional<sog::CompleteElementInfo>
get_element_info(yaml::Node table, std::deque<fs::path> data_dirs) {
  if (table) {
    try {
      auto info = table.as<sog::CompleteElementInfo>();
      if (info.sound_file.has_value()) {
        info.resolved_sound_file = find_file(*info.sound_file, data_dirs);
        std::cerr << *info.resolved_sound_file;
      }
      return info;
    } catch (YAML::TypedBadConversion<sog::CompleteElementInfo>) {
    }
  }
  return std::nullopt;
}

std::deque<fs::path> get_data_dirs(yaml::Node data_dirs_array) {
  std::deque<fs::path> data_dirs;
  for (auto &&additional_data_dir : data_dirs_array) {
    // TODO :error handling
    data_dirs.push_back(additional_data_dir.as<std::string>());
  }
  return data_dirs;
}

sog::config
parse_config(std::filesystem::path config_file,
             std::deque<std::filesystem::path> data_dirs,
             sog::CompleteElementInfo default_default_element_info) {
  sog::config ret_val;

  // TODO : error handling
  auto config = YAML::LoadFile(std::filesystem::absolute(config_file).string());
  fs::path base_config_dir = config_file.parent_path();
  auto config_sound_data_dirs = get_data_dirs(config["data_dirs"]);

  std::deque<fs::path> abslute_sound_data_dirs{};
  for (auto &&path : config_sound_data_dirs) {
    abslute_sound_data_dirs.emplace_back(base_config_dir / path);
  }

  sog::CompleteElementInfo undefined_element_info =
      get_element_info(config["undefined_element"], abslute_sound_data_dirs)
          .value_or(sog::CompleteElementInfo{});

  std::unordered_map<sog::element_type, sog::CompleteElementInfo> element_infos;

  for (auto [enum_value, enum_string] :
       magic_enum::enum_entries<sog::element_type>()) {
    sog::CompleteElementInfo element_info;

    element_infos[enum_value] =
        get_element_info(config[std::string{enum_string}],
                         abslute_sound_data_dirs)
            .value_or(undefined_element_info);
  }
  ret_val.element_infos = element_infos;
  ret_val.base_config_dir = base_config_dir;
  ret_val.data_dirs = config_sound_data_dirs;
  return ret_val;
}
} // namespace sog
