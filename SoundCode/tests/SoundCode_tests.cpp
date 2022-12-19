#include "impl/_ErrorHelper.hpp"

#include "ExceptionUtils.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <filesystem>
#include <iostream>

#define private public // for tests
#include "SoundCode.hpp"

std::filesystem::path metarial_dir{TEST_METARIAL_DIR};
TEST_CASE("mono channel sound load", "[soundcode]") {
  auto sound_file_path = metarial_dir / "mono_sound.wav";
  sog::SoundManager sounds{};

  sounds.load_sound("test", sound_file_path.string());
  sounds.sounds.at("test");
}
TEST_CASE("stereo channel sound load", "[soundcode]") {
  auto sound_file_path = metarial_dir / "stereo_sound.wav";
  sog::SoundManager sounds{};

  REQUIRE_THROWS_WITH(sounds.load_sound("test", sound_file_path.string()),
                      Catch::Matchers::ContainsSubstring(
                          "contains more than 1 channel which is unsupported"));
}
