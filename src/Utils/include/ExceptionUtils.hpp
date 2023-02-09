#pragma once
#include <boost/exception/all.hpp>
#include <boost/stacktrace.hpp>
#include <fmt/core.h>

#include <sstream>

// TODO: add error types for better error handling
namespace sog
{
using traced =
    boost::error_info<struct tag_stacktrace, boost::stacktrace::stacktrace>;
template <class E> void throw_with_trace(const E &e)
{
    throw boost::enable_error_info(e)
        << traced(boost::stacktrace::stacktrace());
}
inline void get_exception_with_stacktrace(const std::exception &exception)
{

    auto st = boost::get_error_info<sog::traced>(exception);
    std::stringstream s;
    s << *st;
    throw std::runtime_error{fmt::format(
        "stacktrace :\n{}\nexception message:\n{}", s.str(), exception.what())};
}
} // namespace sog
