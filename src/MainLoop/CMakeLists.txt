add_library(MainLoop_lib MainLoop.cpp GetDirs.cpp ParseConfig.cpp)
target_include_directories(MainLoop_lib PUBLIC ./include)
target_link_libraries(MainLoop_lib PUBLIC SOG::SoundCode SOG::GuiCollector
                                          SOG::Utils)

add_library(SOG::MainLoop ALIAS MainLoop_lib)

if(enable_tests)
  add_subdirectory(tests)
endif()
