#include "_GetDirs.hpp"

#include <gsl/gsl>

#include <catch2/catch_test_macros.hpp>

#include <cstdio>
#include <filesystem>
namespace fs = std::filesystem;

auto make_temp_dir() {
  fs::path path = fs::temp_directory_path() / std::tmpnam(nullptr);
  fs::create_directory(path);
  return std::make_pair(path, gsl::finally([path] { fs::remove_all(path); }));
}

TEST_CASE("make dir if not exists") {}
