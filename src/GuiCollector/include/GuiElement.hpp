#pragma once

#include "element_type.hpp"
#include <memory>
#include <string>

namespace sog {
class GuiElement {
public:
  virtual ~GuiElement(){};

  virtual std::unique_ptr<GuiElement> get_parent() = 0;
  virtual element_type get_type() = 0;
  virtual std::string get_native_element_type_name() = 0;
  virtual std::string get_native_element_type_enum_name() = 0;
  virtual bool operator==(const GuiElement &other) = 0;
};

}; // namespace sog
