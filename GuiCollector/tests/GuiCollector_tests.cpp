#include "GuiCollector.hpp"
#include "GuiCollector_tests_base.hpp"
#include "point2.hpp"

#include <catch2/catch_test_macros.hpp>
#include <qdesktopwidget.h>
#include <qscreen.h>
#include <thread>

TEST_CASE("mouse pos tests")
{
    sog::GuiCollector collector;
    collector.set_mouse_pos({10, 10});
    CHECK(collector.get_mouse_pos() == sog::point2<int>{10, 10});
};

;
TEST_CASE_METHOD(Gui_test_fixture)
{

    SECTION("element comparission")
    {
    }
    //
    // SECTION("parent element") {
    //   auto list_item = collector.get_control_at_pos(list_item_pos);
    //   auto list = collector.get_control_at_pos(list_pos);
    //   CHECK((list.value() == list_item->get_parent().value()));
    // }
    //
    // SECTION("element type checks") {
    //
    //   auto list_item = collector.get_control_at_pos(list_item_pos);
    //   CHECK(list_item->get_type() == sog::element_type::list_item);
    //   CHECK(list_item->get_parent()->get_type() == sog::element_type::list);
    //   CHECK(list_item->get_parent()->get_parent()->get_type() ==
    //         sog::element_type::window);
    // }
}
