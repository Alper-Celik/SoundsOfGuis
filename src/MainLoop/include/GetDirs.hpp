#pragma once

#include <deque>
#include <filesystem>
#include <optional>
#include <string_view>
namespace sog {

constexpr std::string_view program_name = "SoundsOfGuis";
constexpr std::string_view config_file_name = "sog-config";

std::optional<std::filesystem::path> find_file(
    std::filesystem::path file,
    const std::deque<std::filesystem::path> &data_dirs,
    std::filesystem::file_type file_type = std::filesystem::file_type::regular);

void make_dir_if_not_exists(const std::filesystem::path &dir);
void create_file_if_not_exists(const std::filesystem::path &file);

std::filesystem::path get_config_file();
std::deque<std::filesystem::path> get_data_dirs(); // TODO: implent

} // namespace sog
