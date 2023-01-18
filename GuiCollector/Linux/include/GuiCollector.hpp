#pragma once
#include <IGuiCollector.hpp>
namespace sog {
class PlatformGuiCollector : public IGuiCollector {
  virtual ~PlatformGuiCollector() override;
  PlatformGuiCollector();
  virtual point2<int> get_mouse_pos() override;
  virtual void set_mouse_pos(point2<int> pos) override;
  virtual IGuiElement get_control_at_pos(point2<int> pos) override;
};
} // namespace sog
