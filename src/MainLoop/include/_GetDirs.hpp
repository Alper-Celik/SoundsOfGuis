#pragma once

#include <deque>
#include <filesystem>
#include <string_view>
namespace sog {

constexpr std::string_view program_name = "SoundsOfGuis";
constexpr std::string_view config_file_name = "sog-config";

void make_dir_if_not_exists(const std::filesystem::path &dir);
void create_file_if_not_exists(const std::filesystem::path &file);

std::filesystem::path get_config_file();
std::deque<std::filesystem::path> get_data_dirs(); // TODO: implent

} // namespace sog
