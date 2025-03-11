#include "GuiCollector.hpp"
#include "GuiCollector_tests_base.hpp"
#include "point2.hpp"

#include <catch2/catch_test_macros.hpp>
TEST_CASE_METHOD(Gui_test_fixture, "element comparission") {
  // TODO: test comaprrission for another gui element with same type
  // also check with same depth at gui tree
  auto list_item = collector->get_control_at_pos(list_item_pos);
  REQUIRE(list_item.get() != nullptr);

  CHECK((*list_item == *collector->get_control_at_pos(list_item_pos)));
}
