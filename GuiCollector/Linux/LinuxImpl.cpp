#include "GuiCollector.hpp"

#include "ExceptionUtils.hpp"

#include <atspi/atspi.h>
#include <fmt/format.h>
#include <gsl/gsl_util>
#include <xdo.h>

/// TODO : add proper error handling of At-spi

namespace sog {
GuiCollector::GuiCollector() {
  if (atspi_is_initialized() == false) {
    atspi_init();
    desktop = atspi_get_desktop(
        0); // atspi-2 curruntly doesn't implement virtual desktops
  }

  auto xdo_tmp = xdo_new(nullptr);
  if (xdo_tmp != nullptr) {
    xdo = xdo_tmp;
  }
}
GuiCollector::~GuiCollector() {
  g_object_unref(desktop);
  if (xdo.has_value()) {
    xdo_free(static_cast<xdo_t *>(*xdo));
  }
}

void GuiCollector::set_mouse_pos(point2<int> pos) {
  atspi_generate_mouse_event(pos.x, pos.y, "abs", nullptr);
}

point2<int> GuiCollector::get_mouse_pos() {
  int screen, x, y;
  xdo_get_mouse_location(static_cast<xdo_t *>(*xdo), &x, &y, &screen);
  return {x, y};
}
} // namespace sog
