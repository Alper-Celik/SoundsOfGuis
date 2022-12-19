#include "static_initilizer.hpp"

#include <boost/stacktrace.hpp>

#include <cstdlib>
#include <exception>
#include <iostream>

 sog::static_init terminate_handler{[] {
  std::set_terminate([] {
    try {
      std::cerr << boost::stacktrace::stacktrace();
    } catch (...) {
      std::abort();
    }
  });
}};


