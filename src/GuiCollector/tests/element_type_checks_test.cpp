#include "GuiCollector.hpp"
#include "GuiCollector_tests_base.hpp"
#include "element_type.hpp"
#include "point2.hpp"

#include <catch2/catch_test_macros.hpp>
TEST_CASE_METHOD(Gui_test_fixture, "parent element") {
  auto list_item = collector->get_control_at_pos(list_item_pos);
  auto window = collector->get_control_at_pos(window_pos);
  CHECK(list_item->get_type() == sog::element_type::listitem);
  CHECK(list_item->get_parent()->get_type() == sog::element_type::list);
  CHECK(list_item->get_parent()->get_parent()->get_type() ==
        sog::element_type::window);
  CHECK(window->get_type() == sog::element_type::window);

  CHECK((*list_item->get_parent()->get_parent().get() == *window));
}
