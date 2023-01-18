#pragma once
#include "point2.hpp"
#include <optional>
namespace sog {
enum class element_type { window, list, list_item };

class GuiElement {
public:
  ~GuiElement();
  GuiElement();
  std::optional<GuiElement> get_parent();
  element_type get_type();
  bool operator==(GuiElement &other);
  bool operator!=(GuiElement &other);
};

class GuiCollector {
public:
  ~GuiCollector();
  GuiCollector();
  point2<int> get_mouse_pos();
  void set_mouse_pos(point2<int> pos);
  GuiElement get_control_at_pos(point2<int> pos);
};
} // namespace sog
