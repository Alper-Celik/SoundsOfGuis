#include <catch2/catch_test_macros.hpp>

#include "ExceptionUtils.hpp"
#include <iostream>
#include <stdexcept>
TEST_CASE("throw_with_trace", "[utils][exception]")
{
    try
    {
        sog::throw_with_trace(std::runtime_error("some error"));

        REQUIRE(false);
    }
    catch (const std::exception &e)
    {
        auto st = boost::get_error_info<sog::traced>(e);
        CHECK(st != nullptr);
    }
}
