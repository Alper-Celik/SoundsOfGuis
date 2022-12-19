add_library(GuiCollector_lib_impl LinuxImpl.cpp)
target_link_libraries(GuiCollector_lib_impl atspi-2::atspi-2 SOG::Utils)
target_include_directories(GuiCollector_lib_impl PUBLIC ./include)

target_include_directories(GuiCollector_lib_impl PRIVATE ../include)
