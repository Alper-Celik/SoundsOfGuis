add_library(Sounds_lib STATIC test.cpp)
add_library(SOG::Sounds ALIAS Sounds_lib)

if(enable_tests)
  add_subdirectory(tests)
endif()
