#pragma once
#include "point2.hpp"
#include <optional>
namespace sog {

enum class element_type { window, list, list_item };
class IGuiElement {
public:
  virtual ~IGuiElement(){};
  virtual element_type get_element_type() = 0;
  virtual std::optional<IGuiElement> get_parent() = 0;
  virtual bool operator==(IGuiElement &other) = 0;
  virtual bool operator!=(IGuiElement &other) = 0;
};

class IGuiCollector {
public:
  virtual ~IGuiCollector(){};
  virtual point2<int> get_mouse_pos() = 0;
  virtual void set_mouse_pos(point2<int> pos) = 0;
  virtual IGuiElement get_control_at_pos(point2<int> pos) = 0;
};
} // namespace sog
