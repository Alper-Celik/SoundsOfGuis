#include "GuiCollectorAtSpi2.hpp"

#include "AtspiMappings.hpp"
#include "ExceptionUtils.hpp"
#include "GuiElement.hpp"
#include "GuiElementAtspi2.hpp"
#include "MapUtils.hpp"
#include "point2.hpp"
#include <iostream>
#include <memory>
#include <xcb/xproto.h>

#define MAGIC_ENUM_RANGE_MIN 0
#define MAGIC_ENUM_RANGE_MAX 256
#include <atspi/atspi.h>
#include <fmt/format.h>
#include <gsl/util>
#include <magic_enum.hpp>
#include <xcb/xcb.h>
#include <xcb/xproto.h>

#include <string_view>

/// TODO : add proper error handling of At-spi
namespace sog {
GuiCollectorAtSpi2::GuiCollectorAtSpi2()
    : desktop(atspi_get_desktop(
          0) // atspi-2 curruntly doesn't implement virtual desktops
      ) {

  int xcb_preffered_screen_num;
  xcb_connection = xcb_connect(NULL, &xcb_preffered_screen_num);

  const auto xcb_setup = xcb_get_setup(xcb_connection);
  auto iter = xcb_setup_roots_iterator(xcb_setup);

  for (int i = 0; i < xcb_preffered_screen_num; i++) {
    xcb_screen_next(&iter);
  }
  xcb_default_screen = iter.data;

  // TODO: enable accessibility from dbus
  if (atspi_is_initialized() == false) {
    atspi_init();
  }
}

GuiCollectorAtSpi2::~GuiCollectorAtSpi2() {
  g_object_unref(desktop);
  xcb_disconnect(xcb_connection);
}

void GuiCollectorAtSpi2::set_mouse_pos(Point2<int> pos) {
  atspi_generate_mouse_event(pos.x, pos.y, "abs", nullptr);
}

Point2<int> GuiCollectorAtSpi2::get_mouse_pos() {
  auto cookie =
      xcb_query_pointer_unchecked(xcb_connection, xcb_default_screen->root);
  xcb_query_pointer_reply_t *pointer_info =
      xcb_query_pointer_reply(xcb_connection, cookie, NULL);

  return {pointer_info->root_x, pointer_info->root_y};
}

std::unique_ptr<GuiElement>
GuiCollectorAtSpi2::get_control_at_pos(Point2<int> pos) {
  int application_count = atspi_accessible_get_child_count(desktop, nullptr);

  // NOTE: using reverse iteration for looping since it last app is likely what
  // we want
  for (int application_index = application_count - 1; 0 <= application_index;
       application_index--) {
    GuiElementAtspi2 application = atspi_accessible_get_child_at_index(
        desktop, application_index, nullptr);

    int window_count =
        atspi_accessible_get_child_count(application.get_handle(), nullptr);
    for (int window_index = 0; window_index < window_count;
         window_index++) { // NOTE: maybe do reverse iteration for getting last
                           // window
      GuiElementAtspi2 window = atspi_accessible_get_child_at_index(
          application.get_handle(), window_index, nullptr);

      auto window_component =
          atspi_accessible_get_component_iface(window.get_handle());
      auto free_window_component =
          gsl::finally([&] { g_object_unref(window_component); });

      AtspiAccessible *element = atspi_component_get_accessible_at_point(
          window_component, pos.x, pos.y, ATSPI_COORD_TYPE_SCREEN, nullptr);

      if (element != nullptr) {
        return nullptr;
      } else if (atspi_component_contains(window_component, pos.x, pos.y,
                                          ATSPI_COORD_TYPE_SCREEN, nullptr)) {
        return std::unique_ptr<GuiElement>(
            new GuiElementAtspi2(std::move(window)));
      }
    }
  }

  return nullptr;
}
} // namespace sog
