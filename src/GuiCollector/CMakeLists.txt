add_library(GuiCollector_lib GetDriver.cpp)
target_include_directories(GuiCollector_lib PUBLIC ./include)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  add_subdirectory(Linux)
  target_link_libraries(GuiCollector_lib
                        PRIVATE SOG::GuiCollector::Linux::AtSpi2)
endif()

if(enable_tests)
  # add_subdirectory(tests)
endif()

add_library(SOG::GuiCollector ALIAS GuiCollector_lib)
