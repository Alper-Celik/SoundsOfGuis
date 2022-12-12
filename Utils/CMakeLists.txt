add_library(Utils_lib Terminate_handler.cpp)
target_include_directories(Utils_lib PUBLIC ./include)

add_library(SOG::Utils ALIAS Utils_lib)

if(enable_tests)
  add_subdirectory(tests)
endif()
