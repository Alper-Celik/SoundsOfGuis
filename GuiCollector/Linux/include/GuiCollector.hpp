#pragma once
#include "point2.hpp"

#include <atspi/atspi.h>

#include <gsl/pointers>

#include <atomic>
#include <optional>
#include <thread>

namespace sog {
enum class element_type {
  undefined,
  window,
  list,
  list_item,
};

class GuiElement {
  gsl::not_null<AtspiAccessible *> native_element;

public:
  GuiElement(AtspiAccessible *native_element);

  ~GuiElement();
  GuiElement(GuiElement &&other);
  GuiElement &operator=(GuiElement &&other);

  GuiElement &operator=(const GuiElement &);
  GuiElement(const GuiElement &);

  std::optional<GuiElement> get_parent();
  element_type get_type();
  bool operator==(const GuiElement &other);
};

class GuiCollector {

  gsl::not_null<AtspiAccessible *> desktop;
  gsl::not_null<void *> xdo;

public:
  ~GuiCollector();
  GuiCollector();
  point2<int> get_mouse_pos();
  void set_mouse_pos(point2<int> pos);
  std::optional<GuiElement> get_control_at_pos(point2<int> pos);
};
} // namespace sog
