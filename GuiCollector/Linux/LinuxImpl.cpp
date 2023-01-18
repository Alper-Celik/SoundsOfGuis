
#include "GuiCollector.hpp"

#include "ExceptionUtils.hpp"

#define CHECK_EROR(x, y)                                                       \
  if (auto err = x; err != y)                                                  \
  throw_with_trace(std::runtime_error(                                         \
      fmt::format("{} is failed with \"{}\" expected : \"{}\"", #x, err, y)))

#include <atspi/atspi.h>
// namespace sog {
// GuiCollector::GuiCollector() {
//   if (atspi_is_initialized() == false) {
//     CHECK_EROR(atspi_init(), 0);
//     data.Desktop = atspi_get_desktop(
//         0); // atspi-2 curruntly doesn't implement virtual desktops
//     // TODO : Mouse point callbacks
//   }
// }
// } // namespace sog
