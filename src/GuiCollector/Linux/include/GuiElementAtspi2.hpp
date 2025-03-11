#pragma once
#include "GuiElement.hpp"
#include "element_type.hpp"

#include <atspi/atspi.h>

#include <gsl/pointers>

#include <memory>

namespace sog {
class GuiElementAtspi2 : public GuiElement {
public:
  using native_hadle_t = AtspiAccessible *;

private:
  gsl::not_null<native_hadle_t> native_element;
  std::size_t
      element_hash; // NOTE: if same, does not guarantee elements being same.
                    //  only use it for not equals and do more tests for
                    //  equality
public:
  GuiElementAtspi2(AtspiAccessible *native_element);

  ~GuiElementAtspi2();
  GuiElementAtspi2(GuiElementAtspi2 &&other);
  GuiElementAtspi2 &operator=(GuiElementAtspi2 &&other);

  GuiElementAtspi2 &operator=(const GuiElementAtspi2 &);
  GuiElementAtspi2(const GuiElementAtspi2 &);

  std::unique_ptr<GuiElement> get_parent() override;
  element_type get_type() override;
  std::string get_native_element_type_name() override;
  std::string get_native_element_type_enum_name() override;
  bool operator==(const GuiElement &other) override;

  gsl::not_null<native_hadle_t> get_handle() const;
};

} // namespace sog
