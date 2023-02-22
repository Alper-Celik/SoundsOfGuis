#pragma once
#include "element_type.hpp"
#include "point2.hpp"

#include <atspi/atspi.h>

#include <gsl/pointers>

#include <atomic>
#include <optional>
#include <thread>

namespace sog {
class GuiElement {
public:
  using native_hadle_t = AtspiAccessible *;

private:
  gsl::not_null<native_hadle_t> native_element;

public:
  GuiElement(AtspiAccessible *native_element);

  ~GuiElement();
  GuiElement(GuiElement &&other);
  GuiElement &operator=(GuiElement &&other);

  GuiElement &operator=(const GuiElement &);
  GuiElement(const GuiElement &);

  std::optional<GuiElement> get_parent();
  element_type get_type();
  std::string get_native_element_type_name();
  std::string get_native_element_type_enum_name();
  gsl::not_null<native_hadle_t> get_handle() const;
  bool operator==(const GuiElement &other);
};

class GuiCollector {

  gsl::not_null<AtspiAccessible *> desktop;
  gsl::not_null<void *> xdo;

public:
  ~GuiCollector();
  GuiCollector();
  Point2<int> get_mouse_pos();
  void set_mouse_pos(Point2<int> pos);
  std::optional<GuiElement> get_control_at_pos(Point2<int> pos);
};
} // namespace sog
