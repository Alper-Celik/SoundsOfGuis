#include "GuiCollector.hpp"

#include "AtspiMappings.hpp"
#include "ExceptionUtils.hpp"

#define MAGIC_ENUM_RANGE_MIN 0
#define MAGIC_ENUM_RANGE_MAX 256
#include <atspi/atspi.h>
#include <fmt/format.h>
#include <gsl/gsl_util>
#include <magic_enum.hpp>
#include <xdo.h>

/// TODO : add proper error handling of At-spi

namespace sog {

GuiElement::GuiElement(AtspiAccessible *native_element)
    : native_element(native_element){}; // TODO: enable accessiblity from dbus
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

element_type GuiElement::get_type() // TODO: be smarter than map lookup
                                    // like first frame is window but others are
                                    // freme etc and take toolkit into account
                                    // if needed
{
  AtspiRole type = atspi_accessible_get_role(native_element, nullptr);
  fmt::print("{}\n", magic_enum::enum_name<AtspiRole>(type));

  return sog::AtspiMapping.at(type);
}

std::string GuiElement::get_native_element_type_name() {
  return std::string{atspi_accessible_get_role_name(native_element, nullptr)};
};

std::string GuiElement::get_native_element_type_enum_name() {
  return std::string{magic_enum::enum_name(
      atspi_accessible_get_role(native_element, nullptr))};
}

gsl::not_null<GuiElement::native_hadle_t> GuiElement::get_handle() {
  return native_element;
}

bool GuiElement::operator==(
    const GuiElement &other) // FIXME: id's might not be unique
                             //  and some toolkits might not expose it
                             //  NOTE: looks like only QT exposes id
                             //  NOTE: use extents of it to compere maybe
{
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

void GuiCollector::set_mouse_pos(Point2<int> pos) {
  atspi_generate_mouse_event(pos.x, pos.y, "abs", nullptr);
}

Point2<int> GuiCollector::get_mouse_pos() {
  int screen, x, y;
  xdo_get_mouse_location(static_cast<xdo_t *>(xdo.get()), &x, &y, &screen);
  return {x, y};
}
std::optional<GuiElement> GuiCollector::get_control_at_pos(Point2<int> pos) {
  int application_count = atspi_accessible_get_child_count(desktop, nullptr);

  for (int application_index = 0; application_index < application_count;
       application_index++) {
    GuiElement application = atspi_accessible_get_child_at_index(
        desktop, application_index, nullptr);

    int window_count =
        atspi_accessible_get_child_count(application.get_handle(), nullptr);
    for (int window_index = 0; window_index < window_count; window_index++) {
      GuiElement window = atspi_accessible_get_child_at_index(
          application.get_handle(), window_index, nullptr);

      auto window_component =
          atspi_accessible_get_component_iface(window.get_handle());
      auto free_window_component =
          gsl::finally([&] { g_object_unref(window_component); });

      AtspiAccessible *element = atspi_component_get_accessible_at_point(
          window_component, pos.x, pos.y, ATSPI_COORD_TYPE_SCREEN, nullptr);

      if (element != nullptr) {
        return element;
      } else if (atspi_component_contains(window_component, pos.x, pos.y,
                                          ATSPI_COORD_TYPE_SCREEN, nullptr)) {
        return std::move(window);
      }
    }
  }

  return std::nullopt;
}
} // namespace sog
