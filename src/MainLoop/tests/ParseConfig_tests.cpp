#include "ParseConfig.hpp"

#include "GetDirs.hpp"

#include <magic_enum.hpp>

#include <catch2/catch_test_macros.hpp>

namespace fs = std::filesystem;
fs::path metarial_dir{TEST_METARIAL_DIR};

TEST_CASE("parse_config tests") {

  sog::config config = sog::parse_config(metarial_dir / "sog-config.yaml", {});

  for (sog::element_type element :
       magic_enum::enum_values<sog::element_type>()) {
    config.element_infos.at(element); // check every element exists
  }

  CHECK(config.base_config_dir == metarial_dir);

  // defined elements
  auto list_cfg = config.element_infos.at(sog::element_type::list);
  CHECK(list_cfg.sound_file == fs::path{"test"} / "list.wav");
  CHECK(list_cfg.element_info.is_looping == true);
  CHECK(list_cfg.element_info.distance_to_other ==
        sog::Point3<float>{.x = 1, .y = 2, .z = 0});

  // undefined elements
  auto window_cfg = config.element_infos.at(sog::element_type::window);
  CHECK(window_cfg.element_info.distance_to_other.x == .75f);

  // default values
  auto list_item_cfg = config.element_infos.at(sog::element_type::listitem);
  CHECK(list_item_cfg.element_info.distance_to_other.z == 0.0f);

  // setting only x axis
  CHECK(list_item_cfg.element_info.distance_to_other.x == 3);
}
