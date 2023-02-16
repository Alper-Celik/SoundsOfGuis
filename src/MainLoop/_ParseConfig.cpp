#include "_ParseConfig.hpp"

#include "_GetDirs.hpp"

#include <boost/range/adaptor/reversed.hpp>
#include <magic_enum.hpp>
#include <toml++/toml.h>

namespace sog {
namespace fs = std::filesystem;

sog::CompleteElementInfo
get_element_info(toml::node_view<toml::node> table,
                 sog::CompleteElementInfo default_info,
                 const std::deque<fs::path> &data_dirs) {
  sog::CompleteElementInfo info = default_info;

  if (table.is_table()) {
    info.element_info.is_looping =
        table["looping"].value_or(default_info.element_info.is_looping);

    if (auto distance_to_other = table["distance_to_other"];
        distance_to_other.is_number()) {
      info.element_info.distance_to_other.x = *distance_to_other.value<float>();

    } else if (distance_to_other.is_table()) {

      Point3 default_distance = default_info.element_info.distance_to_other;
      info.element_info.distance_to_other = {
          .x = distance_to_other["x"].value_or(default_distance.x),
          .y = distance_to_other["y"].value_or(default_distance.y),
          .z = distance_to_other["z"].value_or(default_distance.z)};
    }

    if (auto sound_file = table["sound_file"]; sound_file.is_string()) {
      info.sound_file = find_file(*sound_file.value<std::string>(), data_dirs);
    }
  }

  return info;
}

void update_data_dirs(toml::node_view<toml::node> data_dirs_array,
                      fs::path base_dir, std::deque<fs::path> &data_dirs) {
  auto additional_data_dirs = data_dirs_array.as_array();
  if (additional_data_dirs != nullptr) {
    for (auto &&additional_data_dir_cfg :
         boost::adaptors::reverse(*additional_data_dirs)) {

      std::optional<std::string> additional_data_dir =
          additional_data_dir_cfg.value<std::string>();
      if (additional_data_dir.has_value()) {
        data_dirs.push_front(base_dir / *additional_data_dir);
      } else {
        // TODO: log invalid input
      }
    }
  }
}

std::unordered_map<sog::element_type, sog::CompleteElementInfo>
parse_config(std::filesystem::path config_file,
             std::deque<std::filesystem::path> data_dirs,
             sog::CompleteElementInfo default_default_element_info) {
  toml::table config;

  try {
    config = toml::parse_file(std::filesystem::absolute(config_file).string());
  } catch (const std::filesystem::filesystem_error &err) {
    // TODO:
    throw;
  } catch (const toml::parse_error &err) {
    // TODO:
    throw;
  }

  update_data_dirs(config["additional_data_dirs"], config_file.parent_path(),
                   data_dirs);

  sog::CompleteElementInfo default_element_info = get_element_info(
      config["default"], default_default_element_info, data_dirs);

  sog::CompleteElementInfo undefined_element_info = get_element_info(
      config["undefined_element"], default_element_info, data_dirs);

  std::unordered_map<sog::element_type, sog::CompleteElementInfo> ret_val;

  for (auto [enum_value, enum_string] :
       magic_enum::enum_entries<sog::element_type>()) {
    sog::CompleteElementInfo element_info;

    toml::node_view<toml::node> element_config = config[enum_string];
    if (element_config.is_table()) {
      ret_val[enum_value] =
          get_element_info(element_config, default_element_info, data_dirs);
    } else {
      ret_val[enum_value] = undefined_element_info;
    }
  }
  return ret_val;
}
} // namespace sog
