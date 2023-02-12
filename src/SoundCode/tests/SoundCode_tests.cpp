#include "impl/_ErrorHelper.hpp"

#include "ExceptionUtils.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <filesystem>
#include <iostream>

#define private public // for tests
#include "SoundCode.hpp"
namespace {
std::filesystem::path metarial_dir{TEST_METARIAL_DIR};
}
TEST_CASE("mono channel sound load", "[SoundCode][load_element]") {
  auto sound_file_path = metarial_dir / "mono_sound.wav";
  sog::SoundManager sounds{};

  sounds.load_element(sog::element_type::unknown_element, {},
                      sound_file_path.string());
  sounds.sounds.at(sog::element_type::unknown_element);
}
TEST_CASE("stereo channel sound load", "[SoundCode][load_element]") {
  auto sound_file_path = metarial_dir / "stereo_sound.wav";
  sog::SoundManager sounds{};

  CHECK_THROWS_WITH(sounds.load_element(sog::element_type::unknown_element, {},
                                        sound_file_path.string()),
                    Catch::Matchers::ContainsSubstring(
                        "contains more than 1 channel which is unsupported"));
}
TEST_CASE("soundless sound load", "[SoundCode][load_element]") {
  sog::SoundManager sounds{};
  sounds.load_element(sog::element_type::unknown_element, {});
  auto [buffer, info] = sounds.sounds.at(sog::element_type::unknown_element);

  CHECK_FALSE(buffer.has_value());
}

TEST_CASE("add remove elements", "[SoundCode]") {

  sog::SoundManager sounds{};
  sounds.load_element(sog::element_type::unknown_element, {1, 1, 1});
  sounds.add_element(sog::element_type::unknown_element);
  sounds.add_element(sog::element_type::unknown_element);
  auto &[type2, info2, source2] = sounds.elements.at(1);

  CHECK(sounds.elements.size() == 2);
  CHECK(type2 == sog::element_type::unknown_element);
  CHECK(info2.distance_to_other == sog::Point3{1, 1, 1});
  sounds.remove_last();

  CHECK(sounds.elements.size() == 1);
  sounds.remove_last();

  CHECK(sounds.elements.empty());
  CHECK_THROWS_WITH(sounds.remove_last(),
                    Catch::Matchers::ContainsSubstring("empty"));
}

TEST_CASE("refresh sounds", "[SoundCode]") {
  using namespace sog;
  sog::SoundManager sounds{};
  sounds.load_element(sog::element_type::window,
                      {.distance_to_other = {1, 2, 3}, .is_looping = true});
  sounds.load_element(sog::element_type::list,
                      {.distance_to_other = {2, 3, 4}});
  sounds.load_element(sog::element_type::list_item, {});

  sounds.add_element(sog::element_type::window);
  sounds.add_element(sog::element_type::list);
  sounds.add_element(sog::element_type::list_item);
  sounds.refresh_sounds();
  auto &[type_list_item, info_list_item, source_list_item] =
      sounds.elements.at(2);
  auto &[type_list, info_list, source_list] = sounds.elements.at(1);
  auto &[type_window, info_window, source_window] = sounds.elements.at(0);

  CHECK(source_window.is_looping());

  CHECK(source_list_item.get_position() == Point3{0, 0, 0});
  CHECK(source_list.get_position() == info_list_item.distance_to_other);
  CHECK(source_window.get_position() ==
        info_list_item.distance_to_other + info_list.distance_to_other);

  for (sog::SoundSource *_s :
       {&source_list_item, &source_list, &source_window}) {
    auto &s = *_s;

    CHECK_FALSE(s.is_initial());
  }
}
