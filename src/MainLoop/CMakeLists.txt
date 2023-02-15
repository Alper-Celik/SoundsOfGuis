add_library(MainLoop_lib MainLoop.cpp _GetDirs.cpp _ParseConfig.cpp)
target_include_directories(MainLoop_lib PUBLIC ./include)
target_link_libraries(MainLoop_lib PUBLIC SOG::Sounds SOG::GuiCollector
                                          SOG::Utils)

add_library(SOG::MainLoop ALIAS MainLoop_lib)

if(enable_tests)
  add_subdirectory(tests)
endif()
