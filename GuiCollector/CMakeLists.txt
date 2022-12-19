add_library(GuiCollector_lib GuiCollector.cpp)
target_include_directories(GuiCollector_lib PUBLIC ./include)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  add_subdirectory(Linux)
endif()

target_link_libraries(GuiCollector_lib GuiCollector_lib_impl)
