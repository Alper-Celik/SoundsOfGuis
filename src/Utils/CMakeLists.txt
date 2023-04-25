add_library(Utils_lib INTERFACE)
target_include_directories(Utils_lib INTERFACE ./include)

add_library(SOG::Utils ALIAS Utils_lib)

if(enable_tests)
  add_subdirectory(tests)
endif()
