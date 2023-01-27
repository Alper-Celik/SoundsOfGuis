#pragma once
#include "point2.hpp"
#include <atomic>
#include <optional>

#include "atspi/atspi.h"
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
  AtspiAccessible *desktop = nullptr;
  std::atomic<sog::point2<int>> point;

public:
  ~GuiCollector();
  GuiCollector();
  point2<int> get_mouse_pos();
  void set_mouse_pos(point2<int> pos);
  GuiElement get_control_at_pos(point2<int> pos);
};
} // namespace sog
