#include "_GetDirs.hpp"

#include <boost/predef.h>
#include <gsl/gsl>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <cstdio>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

auto make_temp_dir() {
  fs::path path = fs::temp_directory_path() / std::tmpnam(nullptr);
  fs::create_directory(path);
  return std::make_pair(path, gsl::finally([path] { fs::remove_all(path); }));
}

TEST_CASE("make_dir_if_not_exists") {
  auto [tmp_dir, clear] = make_temp_dir();
  tmp_dir /= "tmp";

  SECTION("not exists") {
    CHECK_FALSE(fs::is_directory(tmp_dir));
    sog::make_dir_if_not_exists(tmp_dir);
    CHECK(fs::is_directory(tmp_dir));
  }

  SECTION("dir exists") {
    CHECK_FALSE(fs::is_directory(tmp_dir));
    fs::create_directory(tmp_dir);
    CHECK(fs::is_directory(tmp_dir));
    sog::make_dir_if_not_exists(tmp_dir);
    CHECK(fs::is_directory(tmp_dir));
  }

  SECTION("not a dir") {
    CHECK_FALSE(fs::is_directory(tmp_dir));
    sog::create_file_if_not_exists(tmp_dir);
    CHECK_FALSE(fs::is_directory(tmp_dir));
    CHECK(fs::is_regular_file(tmp_dir));
    CHECK_THROWS_WITH(sog::make_dir_if_not_exists(tmp_dir),
                      Catch::Matchers::ContainsSubstring("not a dir"));
  }
}

TEST_CASE("create_file_if_not_exists") {
  auto [tmp_dir, clear] = make_temp_dir();
  tmp_dir /= "tmp";
  SECTION("not exists") {
    CHECK_FALSE(fs::is_regular_file(tmp_dir));
    sog::create_file_if_not_exists(tmp_dir);
    CHECK(fs::is_regular_file(tmp_dir));
  }
  SECTION("exists") {
    std::ofstream create_file{tmp_dir};
    CHECK(fs::is_regular_file(tmp_dir));
    sog::create_file_if_not_exists(tmp_dir);
    CHECK(fs::is_regular_file(tmp_dir));
  }
  SECTION("not a file") {
    CHECK_FALSE(fs::is_regular_file(tmp_dir));
    fs::create_directory(tmp_dir);
    CHECK(fs::is_directory(tmp_dir));

    CHECK_THROWS_WITH(sog::create_file_if_not_exists(tmp_dir),
                      Catch::Matchers::ContainsSubstring("is not a file"));
  }
}

#ifdef BOOST_OS_LINUX
TEST_CASE("get config file linux") {
  auto old_XDG_CONFIG_HOME = getenv("XDG_CONFIG_HOME");
  unsetenv("XDG_CONFIG_HOME");
  auto restore_XDG_CONFIG_HOME = gsl::finally(
      [&] { setenv("XDG_CONFIG_HOME", old_XDG_CONFIG_HOME, true); });

  // TODO: config_dirs_version

  auto old_home = std::getenv("HOME");
  unsetenv("HOME");
  auto restore_Home = gsl::finally([&] { setenv("HOME", old_home, true); });

  auto [tmp_dir, clear] = make_temp_dir();

  // TODO: DRY it
  SECTION("XDG_CONFIG_HOME") {
    auto config_dir = tmp_dir / "cfg";
    setenv("XDG_CONFIG_HOME", config_dir.string().c_str(), true);
    fs::create_directory(config_dir);
    auto program_config_dir = config_dir / sog::program_name;
    auto program_config_file =
        program_config_dir / (std::string(sog::config_file_name) + ".toml");
    SECTION("with file") {
      fs::create_directory(program_config_dir);
      sog::create_file_if_not_exists(program_config_file);
      CHECK(sog::get_config_file() == program_config_file);
    }

    SECTION("without file") {
      CHECK(sog::get_config_file() == program_config_file);
    }
  }
  SECTION("HOME/.config") {
    setenv("HOME", tmp_dir.string().c_str(), true);
    auto config_dir = tmp_dir / ".config";
    fs::create_directory(config_dir);
    auto program_config_dir = config_dir / sog::program_name;
    auto program_config_file =
        program_config_dir / (std::string(sog::config_file_name) + ".toml");

    SECTION("with file") {
      fs::create_directory(program_config_dir);
      sog::create_file_if_not_exists(program_config_file);
      CHECK(sog::get_config_file() == program_config_file);
    }

    SECTION("without file") {
      CHECK(sog::get_config_file() == program_config_file);
    }
  }
}
#endif
