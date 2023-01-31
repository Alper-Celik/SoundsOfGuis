#include "point3.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("point3 equality")
{
    using namespace sog;
    CHECK(point3{1, 1, 1} == point3{1, 1, 1});
    CHECK_FALSE(point3{0, 1, 1} == point3{1, 1, 1});
    CHECK(point3{0, 1, 1} != point3{1, 1, 1});
}

TEST_CASE("point 3 addition")
{
    using namespace sog;

    point3 a{1, 2, 2}, b{1, 1, 2}, c{2, 3, 4};
    CHECK(c == a + b);
    CHECK(c == b + a);
    a += b;
    CHECK(c == a);
}
TEST_CASE("point 3 substraction")
{
    using namespace sog;

    point3 a{1, 2, 2}, b{1, 1, 2}, c{2, 3, 4};
    CHECK(b == c - a);
    c -= a;
    CHECK(b == c);
}
