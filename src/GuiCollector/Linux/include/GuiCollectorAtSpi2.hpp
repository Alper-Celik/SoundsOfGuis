#pragma once
#include "GuiCollector.hpp"
#include "point2.hpp"

#include <atspi/atspi.h>
#include <gsl/pointers>
#include <xcb/xcb.h>
namespace sog {
class GuiCollectorAtSpi2 : public GuiCollector {

  gsl::not_null<AtspiAccessible *> desktop;
  xcb_connection_t *xcb_connection;
  xcb_screen_t *xcb_default_screen;

public:
  ~GuiCollectorAtSpi2();
  GuiCollectorAtSpi2();
  Point2<int> get_mouse_pos() override;
  void set_mouse_pos(Point2<int> pos) override;
  std::unique_ptr<GuiElement> get_control_at_pos(Point2<int> pos) override;
};
} // namespace sog
