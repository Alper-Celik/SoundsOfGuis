#include "GuiCollector.hpp"
#ifdef __unix__
#include <GuiCollectorAtSpi2.hpp>
#endif

namespace sog {
std::unique_ptr<GuiCollector> GetGuiCollector() {
#ifdef __unix__
  return std::unique_ptr<GuiCollector>(new GuiCollectorAtSpi2());
#endif

  return nullptr;
};
} // namespace sog
