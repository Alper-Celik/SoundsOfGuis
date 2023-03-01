add_library(libbacktrace_for_boost INTERFACE)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  # use libbactrace on linux for getting line numbers in boost stacktrace
  find_package(Backtrace)
  if("${Backtrace_LIBRARY}" STREQUAL "")
    target_link_libraries(libbacktrace_for_boost INTERFACE backtrace)
  endif()
  target_link_libraries(libbacktrace_for_boost INTERFACE ${Backtrace_LIBRARY})
  target_include_directories(libbacktrace_for_boost
                             INTERFACE ${Backtrace_INCLUDE_DIR})
  target_compile_definitions(libbacktrace_for_boost
                             INTERFACE BOOST_STACKTRACE_USE_BACKTRACE)
  if(NOT $ENV{libbacktrace_header} STREQUAL "")
    target_compile_definitions(
      libbacktrace_for_boost
      INTERFACE
        "BOOST_STACKTRACE_BACKTRACE_INCLUDE_FILE=<$ENV{libbacktrace_header}>")
  endif()
endif()
