#include "_GetDirs.hpp"

#include "ExceptionUtils.hpp"

#include <filesystem>
#include <fstream>
#include <optional>

namespace fs = std::filesystem;
namespace sog {

void make_dir_if_not_exists(const fs::path &dir) {
  if (not fs::exists(dir)) {
    fs::create_directory(dir);
    return;
  }
  if (not fs::is_directory(dir)) {
    sog::throw_with_trace(std::runtime_error(
        fmt::format("\"{}\" is not a directory or not exists", dir.string())));
  }
  return;
}
void create_file_if_not_exists(const fs::path &file) {
  if (not fs::exists(file)) {
    {
      {
        try {
          std::ofstream create_file{file};
        } catch (const std::ios_base::failure &err) {
          sog::throw_with_trace(std::runtime_error(
              fmt::format("cannot create file at \"{}\"\n"
                          "with error code: {}\n"
                          "with low level message: {}\n"
                          "with high level message: {}",
                          file.string(), err.code().value(),
                          err.code().message(), err.what())));
        }
      }
      if (fs::is_regular_file(file)) {
        return;
      } else {
        sog::throw_with_trace(std::runtime_error(
            fmt::format("cannot create file at \"{}\"", file.string())));
      }
    }
  }
  if (not fs::is_regular_file(file)) {
    sog::throw_with_trace(std::runtime_error(
        fmt::format("\"{}\" is not a file or not exists", file.string())));
  }
}
fs::path get_config_file() {
  if (BOOST_OS_LINUX) {
    std::optional<fs::path> default_config_file;

    auto xdg_config_dir_ptr = std::getenv("XDG_CONFIG_HOME");
    if (xdg_config_dir_ptr != nullptr and
        std::string_view(xdg_config_dir_ptr) != "") {
      fs::path xdg_config_dir{xdg_config_dir_ptr};

      if (not fs::exists(xdg_config_dir)) {
        sog::throw_with_trace(
            std::runtime_error("$XDG_CONFIG_HOME does not exist"));
      }
      if (not fs::is_directory(xdg_config_dir)) {
        sog::throw_with_trace(
            std::runtime_error("$XDG_CONFIG_HOME is not a directinoary"));
      }

      make_dir_if_not_exists(xdg_config_dir / sog::program_name);

      fs::path config_file = xdg_config_dir / sog::program_name /
                             (std::string(sog::config_file_name) + ".toml");

      create_file_if_not_exists(config_file);
      return config_file;
    }

    // TODO: implment multiple dir version of xdg base dir

    char *home_dir_ptr = std::getenv("HOME");
    if (home_dir_ptr == nullptr) {
      sog::throw_with_trace(
          std::runtime_error("$HOME enviroment variable is not set"));
    } else {
      fs::path config_dir = fs::path{home_dir_ptr} / ".config";
      make_dir_if_not_exists(config_dir);
      make_dir_if_not_exists(config_dir / sog::program_name);

      fs::path config_file = config_dir / sog::program_name /
                             (std::string(sog::config_file_name) + ".toml");
      create_file_if_not_exists(config_file);
      return config_file;
    }
  }

  std::terminate();
}
} // namespace sog
