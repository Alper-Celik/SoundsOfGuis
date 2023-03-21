add_library(Utils_lib Terminate_handler.cpp point3.cpp)
target_include_directories(Utils_lib PUBLIC ./include)
target_link_libraries(
  Utils_lib
  PUBLIC Boost::boost libbacktrace_for_boost
  PRIVATE yaml-cpp)

add_library(SOG::Utils ALIAS Utils_lib)

if(enable_tests)
  add_subdirectory(tests)
endif()
