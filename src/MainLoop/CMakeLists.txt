add_library(MainLoop_lib MainLoop.cpp)
target_include_directories(MainLoop_lib PUBLIC ./include)
target_link_libraries(MainLoop_lib PUBLIC SOG::Sounds SOG::GuiCollector
                                          SOG::Utils)
