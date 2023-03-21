#include "point3.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("point3 equality") {
  using namespace sog;
  CHECK(Point3<float>{1, 1, 1} == Point3<float>{1, 1, 1});
  CHECK_FALSE(Point3<float>{0, 1, 1} == Point3<float>{1, 1, 1});
  CHECK(Point3<float>{0, 1, 1} != Point3<float>{1, 1, 1});
}

TEST_CASE("point 3 addition") {
  using namespace sog;

  Point3<float> a{1, 2, 2}, b{1, 1, 2}, c{2, 3, 4};
  CHECK(c == a + b);
  CHECK(c == b + a);
  a += b;
  CHECK(c == a);
}
TEST_CASE("point 3 substraction") {
  using namespace sog;

  Point3<float> a{1, 2, 2}, b{1, 1, 2}, c{2, 3, 4};
  CHECK(b == c - a);
  c -= a;
  CHECK(b == c);
}
