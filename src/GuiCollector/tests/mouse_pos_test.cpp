
#include "GuiCollector.hpp"

#include <catch2/catch_test_macros.hpp>
TEST_CASE("mouse pos tests")
{
    sog::GuiCollector collector;
    collector.set_mouse_pos({10, 10});
    CHECK(collector.get_mouse_pos() == sog::point2<int>{10, 10});
};
