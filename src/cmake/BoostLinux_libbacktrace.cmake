if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  # use libbactrace on linux for getting line numbers in boost stacktrace
  find_package(Backtrace)
  if("${Backtrace_LIBRARY}" STREQUAL "")
    link_libraries(backtrace)
  endif()
  link_libraries(${Backtrace_LIBRARY})
  include_directories(${Backtrace_INCLUDE_DIR})
  add_compile_definitions(BOOST_STACKTRACE_USE_BACKTRACE)
  if(NOT $ENV{libbacktrace_header} STREQUAL "")
    add_compile_definitions(
      "BOOST_STACKTRACE_BACKTRACE_INCLUDE_FILE=<$ENV{libbacktrace_header}>")
  endif()
endif()
