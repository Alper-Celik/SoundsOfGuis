#include "_ParseConfig.hpp"

#include <magic_enum.hpp>
#include <toml++/toml.h>

namespace sog {
namespace fs = std::filesystem;
std::optional<fs::path>
find_sound_file(fs::path file,
                const std::deque<fs::path> &data_dirs); // TODO: implement

sog::CompleteElementInfo
get_element_info(toml::node_view<toml::node> table,
                 sog::CompleteElementInfo default_info,
                 const std::deque<fs::path> &data_dirs) {
  sog::CompleteElementInfo info = default_info;

  if (table.is_table()) {
    default_info.element_info.is_looping =
        table.value_or(default_info.element_info.is_looping);

    if (auto distance_to_other = table["distance_to_other"];
        distance_to_other.is_number()) {
      info.element_info.distance_to_other.x = *distance_to_other.value<float>();

    } else if (distance_to_other.is_table()) {

      Point3 default_distance = default_info.element_info.distance_to_other;
      info.element_info.distance_to_other = {
          .x = distance_to_other.value_or(default_distance.x),
          .y = distance_to_other.value_or(default_distance.y),
          .z = distance_to_other.value_or(default_distance.z)};
    }

    if (auto sound_file = table["sound_file"]; sound_file.is_string()) {
      info.sound_file =
          find_sound_file(*sound_file.value<fs::path>(), data_dirs);
    }
  }

  return info;
}

std::unordered_map<sog::element_type, sog::CompleteElementInfo>
parse_config(std::filesystem::path config_file,
             std::deque<std::filesystem::path> data_dirs,
             sog::CompleteElementInfo default_default_element_info) {
  toml::table config;

  try {
    config = toml::parse_file(std::filesystem::absolute(config_file).string());
  } catch (const std::filesystem::filesystem_error &err) {
    // TODO:o
  } catch (const toml::parse_error &err) {
    // TODO:
  }

  std::unordered_map<sog::element_type, sog::CompleteElementInfo> ret_val;

  for (auto [enum_value, enum_string] :
       magic_enum::enum_entries<sog::element_type>()) {
    sog::CompleteElementInfo element_info;

    toml::node_view<toml::node> element_config = config[enum_string];
    if (element_config.is_table()) {
    }
  }
  return {};
}
} // namespace sog
