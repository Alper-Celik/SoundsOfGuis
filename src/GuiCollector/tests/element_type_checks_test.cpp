#include "GuiCollector.hpp"
#include "GuiCollector_tests_base.hpp"
#include "point2.hpp"

#include <catch2/catch_test_macros.hpp>
TEST_CASE_METHOD(Gui_test_fixture, "parent element") {
  auto list_item = collector.get_control_at_pos(list_item_pos);
  CHECK(list_item->get_type() == sog::element_type::list_item);
  CHECK(list_item->get_parent()->get_type() == sog::element_type::list);
  CHECK(list_item->get_parent()->get_parent()->get_type() ==
        sog::element_type::window);
}
