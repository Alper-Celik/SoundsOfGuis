#include "GuiCollector.hpp"

#include "ExceptionUtils.hpp"

#include <atspi/atspi.h>
#include <fmt/format.h>
#include <gsl/gsl_util>
#include <xdo.h>

/// TODO : add proper error handling of At-spi

namespace sog {

GuiElement::GuiElement(AtspiAccessible *native_element)
    : native_element(native_element){};
GuiElement::GuiElement(GuiElement &&other)
    : native_element(other.native_element) {
  g_object_ref(native_element.get());
}
GuiElement &GuiElement::operator=(GuiElement &&other) {
  std::swap(other.native_element, native_element);
  return *this;
};

GuiElement::GuiElement(const GuiElement &other)
    : native_element(other.native_element) {
  g_object_ref(native_element.get());
}
GuiElement &GuiElement::operator=(const GuiElement &other) {
  g_object_unref(native_element);
  native_element = other.native_element;
  g_object_ref(native_element.get());
  return *this;
}

std::optional<GuiElement> GuiElement::get_parent() {
  auto element = atspi_accessible_get_parent(native_element, nullptr);
  if (element == nullptr)
    return std::nullopt;
  else
    return element;
}

element_type GuiElement::get_type() {
  // TODO:
  return element_type::undefined;
}

bool GuiElement::operator==(const GuiElement &other) {
  gsl::not_null<gchar *> id_1_ptr =
      atspi_accessible_get_accessible_id(native_element, nullptr);
  auto free_id_1 = gsl::finally([&] { g_free(id_1_ptr); });

  gsl::not_null<gchar *> id_2_ptr =
      atspi_accessible_get_accessible_id(other.native_element, nullptr);
  auto free_id_2 = gsl::finally([&] { g_free(id_2_ptr); });

  std::string_view id_1{id_1_ptr}, id_2{id_2_ptr};

  return id_1 == id_2;
}

GuiElement::~GuiElement() { g_object_unref(native_element); }

GuiCollector::GuiCollector()
    : desktop(atspi_get_desktop(
          0) // atspi-2 curruntly doesn't implement virtual desktops
              ),
      xdo(xdo_new(nullptr)) {
  if (atspi_is_initialized() == false) {
    atspi_init();
  }
}

GuiCollector::~GuiCollector() {
  g_object_unref(desktop);
  xdo_free(static_cast<xdo_t *>(xdo.get()));
}

void GuiCollector::set_mouse_pos(point2<int> pos) {
  atspi_generate_mouse_event(pos.x, pos.y, "abs", nullptr);
}

point2<int> GuiCollector::get_mouse_pos() {
  int screen, x, y;
  xdo_get_mouse_location(static_cast<xdo_t *>(xdo.get()), &x, &y, &screen);
  return {x, y};
}
std::optional<GuiElement> GuiCollector::get_control_at_pos(point2<int> pos) {
  AtspiAccessible *elememt = atspi_component_get_accessible_at_point(
      atspi_accessible_get_component(
          desktop) /* TODO:porobaly not implementing compenent interface*/,
      pos.x, pos.y, ATSPI_COORD_TYPE_SCREEN, nullptr);
  if (elememt == nullptr)
    return std::nullopt;
  else
    return {elememt};
}
} // namespace sog
