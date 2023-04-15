#pragma once
#include <functional>
#include <optional>
#include <unordered_map>
namespace sog {
template <typename T, typename K>
std::optional<std::reference_wrapper<K>>
unordered_map_get_at(std::unordered_map<T, K> &map, const T &key) {
  auto itr = map.find(key);
  if (itr == nullptr)
    return std::nullopt;
  return std::get<1>(*itr);
}
} // namespace sog
