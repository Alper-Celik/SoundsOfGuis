#pragma once
#include "element_info.hpp"
#include "element_type.hpp"

#include <deque>
#include <unordered_map>
namespace sog {
std::unordered_map<sog::element_type, sog::CompleteElementInfo>
parse_config(std::filesystem::path config_file,
             std::deque<std::filesystem::path> data_dirs,
             sog::CompleteElementInfo default_default_element_info = {});
}
