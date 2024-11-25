#pragma once
#include "GuiCollector.hpp"
#include "point2.hpp"

#include <atspi/atspi.h>
#include <gsl/pointers>
namespace sog {
class GuiCollectorAtSpi2 : public GuiCollector {

  gsl::not_null<AtspiAccessible *> desktop;
  gsl::not_null<void *> xdo;

public:
  ~GuiCollectorAtSpi2();
  GuiCollectorAtSpi2();
  Point2<int> get_mouse_pos() override;
  void set_mouse_pos(Point2<int> pos) override;
  std::unique_ptr<GuiElement> get_control_at_pos(Point2<int> pos) override;
};
} // namespace sog
