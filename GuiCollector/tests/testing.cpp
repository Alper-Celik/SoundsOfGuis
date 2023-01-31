

#include <atspi/atspi.h>
#include <catch2/catch_test_macros.hpp>
#include <fmt/core.h>
#include <gsl/pointers>

using fmt::print;
using gsl::not_null;

TEST_CASE() {
  atspi_init();

  not_null<AtspiAccessible *> desktop = atspi_get_desktop(0);
  not_null<AtspiAccessible *> application =
      atspi_accessible_get_child_at_index(desktop, 0, nullptr);
  not_null<AtspiAccessible *> window =
      atspi_accessible_get_child_at_index(application, 0, nullptr);
  print("{}", atspi_accessible_get_accessible_id(window, nullptr));
  not_null<AtspiComponent *> window_comp =
      atspi_accessible_get_component_iface(window);

  auto b = atspi_component_get_accessible_at_point(
      window_comp, 100, 100, ATSPI_COORD_TYPE_SCREEN, nullptr);
  CHECK(b != nullptr);

  auto c = atspi_component_get_accessible_at_point( // NOTE: wierd if element is
                                                    // itself returns nullptr
                                                    //
                                                    // could look into extents
                                                    // of it if nullptr
      window_comp, 100, 500, ATSPI_COORD_TYPE_SCREEN, nullptr);

  CHECK(c == nullptr);
}
