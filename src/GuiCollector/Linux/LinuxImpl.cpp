#include "GuiCollector.hpp"

#include "AtspiMappings.hpp"
#include "ExceptionUtils.hpp"
#include "MapUtils.hpp"

#define MAGIC_ENUM_RANGE_MIN 0
#define MAGIC_ENUM_RANGE_MAX 256
#include <atspi/atspi.h>
#include <fmt/format.h>
#include <gsl/gsl_util>
#include <magic_enum.hpp>
#include <xdo.h>

#include <string_view>

/// TODO : add proper error handling of At-spi

namespace sog {
std::size_t get_gui_element_hash(AtspiAccessible *native_element) {
  std::unique_ptr<gchar, void (*)(gchar *)> accessible_id(
      atspi_accessible_get_accessible_id(native_element, nullptr),
      [](gchar *ptr) { g_free(ptr); });

  std::size_t h1 = 0;
  if (accessible_id != nullptr)
    h1 = std::hash<std::string_view>{}(std::string_view{accessible_id.get()});

  std::size_t h2 = std::hash<AtspiRole>{}(
      atspi_accessible_get_role(native_element, nullptr));

  return h1 + h2;
}

GuiElement::GuiElement(AtspiAccessible *native_element)
    : native_element(native_element) {
  element_hash = get_gui_element_hash(get_handle());
};
GuiElement::GuiElement(GuiElement &&other)
    : native_element(other.native_element), element_hash(other.element_hash) {
  g_object_ref(native_element.get());
}
GuiElement &GuiElement::operator=(GuiElement &&other) {
  std::swap(other.native_element, native_element);
  std::swap(other.element_hash, element_hash);
  return *this;
};

GuiElement::GuiElement(const GuiElement &other)
    : native_element(other.native_element), element_hash(other.element_hash) {
  g_object_ref(native_element.get());
}
GuiElement &GuiElement::operator=(const GuiElement &other) {
  g_object_unref(native_element);
  native_element = other.native_element;
  element_hash = other.element_hash;
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

  {
    auto parent = this->get_parent();
    if (this->get_handle()->role == ATSPI_ROLE_FRAME and parent and
        parent->get_handle()->role == ATSPI_ROLE_APPLICATION)
      return element_type::window;
  }

  {
    auto mapping = unordered_map_get_at(AtspiMapping, type);
    if (mapping)
      return mapping->get();
  }

  return element_type::unknown_element;
}

std::string GuiElement::get_native_element_type_name() {
  return std::string{atspi_accessible_get_role_name(native_element, nullptr)};
};

std::string GuiElement::get_native_element_type_enum_name() {
  return std::string{magic_enum::enum_name(
      atspi_accessible_get_role(native_element, nullptr))};
}

gsl::not_null<GuiElement::native_hadle_t> GuiElement::get_handle() const {
  return native_element;
}

bool GuiElement::operator==(const GuiElement &other) {

  if (element_hash != other.element_hash) {
    return false;
  }

  std::unique_ptr<AtspiRect> current_extents{atspi_component_get_extents(
      atspi_accessible_get_component_iface(this->get_handle()),
      ATSPI_COORD_TYPE_SCREEN, nullptr)};

  std::unique_ptr<AtspiRect> other_extents{atspi_component_get_extents(
      atspi_accessible_get_component_iface(other.get_handle()),
      ATSPI_COORD_TYPE_SCREEN, nullptr)};

  bool is_extents_same = current_extents->x == other_extents->x &&
                         current_extents->y == other_extents->y &&
                         current_extents->width == other_extents->width &&
                         current_extents->height == other_extents->height;
  return is_extents_same;
}

GuiElement::~GuiElement() { g_object_unref(native_element); }

GuiCollector::GuiCollector()
    : desktop(atspi_get_desktop(
          0) // atspi-2 curruntly doesn't implement virtual desktops
              ),
      xdo(xdo_new(nullptr)) {
  // TODO: enable accessiblity from dbus
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

  // NOTE: using reverse iteration for looping since it last app is likely what
  // we want
  for (int application_index = application_count - 1; 0 <= application_index;
       application_index--) {
    GuiElement application = atspi_accessible_get_child_at_index(
        desktop, application_index, nullptr);

    int window_count =
        atspi_accessible_get_child_count(application.get_handle(), nullptr);
    for (int window_index = 0; window_index < window_count;
         window_index++) { // NOTE: maybe do reverse iteration for getting last
                           // windpw
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
