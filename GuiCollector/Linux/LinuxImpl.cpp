
#include "GuiCollector.hpp"

#include "ExceptionUtils.hpp"

/// FIXME : add proper error handling of At-spi

#include <atspi/atspi.h>
namespace sog {
GuiCollector::GuiCollector() {
  if (atspi_is_initialized() == false) {
    atspi_init();
    desktop = atspi_get_desktop(
        0); // atspi-2 curruntly doesn't implement virtual desktops
    // TODO : Mouse point callbacks
  }
}
GuiCollector::~GuiCollector() { g_object_unref(desktop); }

void GuiCollector::set_mouse_pos(point2<int> pos) {
  atspi_generate_mouse_event(pos.x, pos.y, "abs", nullptr);
}
} // namespace sog
