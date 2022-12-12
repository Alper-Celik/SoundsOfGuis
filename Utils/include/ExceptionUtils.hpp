#pragma once
#include <boost/exception/all.hpp>
#include <boost/stacktrace.hpp>
namespace sog {
using traced =
    boost::error_info<struct tag_stacktrace, boost::stacktrace::stacktrace>;
template <class E> void throw_with_trace(const E &e) {
  throw boost::enable_error_info(e) << traced(boost::stacktrace::stacktrace());
}
} // namespace sog
