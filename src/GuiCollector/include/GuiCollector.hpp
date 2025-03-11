#pragma once

#include "GuiElement.hpp"
#include "point2.hpp"
#include <memory>
namespace sog {
class GuiCollector {
public:
  virtual ~GuiCollector() {};

  virtual Point2<int> get_mouse_pos() = 0;
  virtual void set_mouse_pos(Point2<int> pos) = 0;
  virtual std::unique_ptr<GuiElement> get_control_at_pos(Point2<int> pos) = 0;
};
std::unique_ptr<GuiCollector> GetGuiCollector();
}; // namespace sog
