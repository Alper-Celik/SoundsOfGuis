#include "GuiElementAtspi2.hpp"

#include "AtspiMappings.hpp"
#include "MapUtils.hpp"
#include <memory>

#define MAGIC_ENUM_RANGE_MIN 0
#define MAGIC_ENUM_RANGE_MAX 256
#include <atspi/atspi.h>
#include <gsl/gsl_util>
#include <magic_enum.hpp>

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

GuiElementAtspi2::GuiElementAtspi2(AtspiAccessible *native_element)
    : native_element(native_element) {
  element_hash = get_gui_element_hash(get_handle());
};
GuiElementAtspi2::GuiElementAtspi2(GuiElementAtspi2 &&other)
    : native_element(other.native_element), element_hash(other.element_hash) {
  g_object_ref(native_element.get());
}
GuiElementAtspi2 &GuiElementAtspi2::operator=(GuiElementAtspi2 &&other) {
  std::swap(other.native_element, native_element);
  std::swap(other.element_hash, element_hash);
  return *this;
};

GuiElementAtspi2::GuiElementAtspi2(const GuiElementAtspi2 &other)
    : native_element(other.native_element), element_hash(other.element_hash) {
  g_object_ref(native_element.get());
}
GuiElementAtspi2 &GuiElementAtspi2::operator=(const GuiElementAtspi2 &other) {
  g_object_unref(native_element);
  native_element = other.native_element;
  element_hash = other.element_hash;
  g_object_ref(native_element.get());
  return *this;
}

std::unique_ptr<GuiElement> GuiElementAtspi2::get_parent() {
  auto element = atspi_accessible_get_parent(native_element, nullptr);
  if (element == nullptr)
    return nullptr;
  else
    return std::unique_ptr<GuiElement>(new GuiElementAtspi2(element));
}

element_type GuiElementAtspi2::get_type() // TODO: be smarter than map lookup
                                          // like first frame is window but
                                          // others are freme etc and take
                                          // toolkit into account if needed
{
  AtspiRole type = atspi_accessible_get_role(native_element, nullptr);

  {
    auto _parent = this->get_parent();
    auto parent = dynamic_cast<GuiElementAtspi2 *>(_parent.get());
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

std::string GuiElementAtspi2::get_native_element_type_name() {
  return std::string{atspi_accessible_get_role_name(native_element, nullptr)};
};

std::string GuiElementAtspi2::get_native_element_type_enum_name() {
  return std::string{magic_enum::enum_name(
      atspi_accessible_get_role(native_element, nullptr))};
}

gsl::not_null<GuiElementAtspi2::native_hadle_t>
GuiElementAtspi2::get_handle() const {
  return native_element;
}

bool GuiElementAtspi2::operator==(const GuiElement &_other) {
  auto other = dynamic_cast<const GuiElementAtspi2 &>(_other);

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

GuiElementAtspi2::~GuiElementAtspi2() { g_object_unref(native_element); }
} // namespace sog
