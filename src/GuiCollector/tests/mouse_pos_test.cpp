
#include "GuiCollector.hpp"

#include <catch2/catch_test_macros.hpp>
#include <gsl/gsl_util>
TEST_CASE("mouse pos tests") {
  sog::GuiCollector collector;

  auto pre_test_pos = collector.get_mouse_pos();
  auto clean = gsl::finally([&] {
    collector.set_mouse_pos(pre_test_pos);
  }); // make it less annoying while developing

  collector.set_mouse_pos({10, 10});
  CHECK(collector.get_mouse_pos() == sog::point2<int>{10, 10});
};
