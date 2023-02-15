#include "_ParseConfig.hpp"

#include "_GetDirs.hpp"

#include <magic_enum.hpp>

#include <catch2/catch_test_macros.hpp>

std::filesystem::path metarial_dir{TEST_METARIAL_DIR};

TEST_CASE("parse_config tests") {

  std::unordered_map<sog::element_type, sog::CompleteElementInfo> config =
      sog::parse_config(metarial_dir / "sog-config.toml", {});

  for (sog::element_type element :
       magic_enum::enum_values<sog::element_type>()) {
    config.at(element); // check every element exists
  }

  // defined elements
  auto list_cfg = config.at(sog::element_type::list);
  CHECK(list_cfg.sound_file == metarial_dir / "sounds" / "test" / "list.wav");
  CHECK(list_cfg.element_info.is_looping == true);
  CHECK(list_cfg.element_info.distance_to_other.x == 1);
  CHECK(list_cfg.element_info.distance_to_other.y == 2);
  CHECK(list_cfg.element_info.distance_to_other.z == 0);

  // undefined elements
  auto window_cfg = config.at(sog::element_type::window);
  CHECK(window_cfg.element_info.distance_to_other.x == 0.05f);
}
