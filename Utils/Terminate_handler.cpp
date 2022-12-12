
#include <boost/stacktrace.hpp>

#include <cstdlib>
#include <exception>
#include <iostream>
namespace sog {
void terminate_handler() {
  try {
    std::cerr << boost::stacktrace::stacktrace();
  } catch (...) {
    std::abort();
  }
}
struct SetTerminateHandler {
  SetTerminateHandler() { std::set_terminate(terminate_handler); }
};
SetTerminateHandler set_terminate_handler;
} // namespace sog
