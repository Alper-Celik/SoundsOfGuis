add_library(GuiCollector_lib LinuxImpl.cpp)
target_link_libraries(GuiCollector_lib atspi-2::atspi-2 SOG::Utils)

target_include_directories(GuiCollector_lib PUBLIC ./include ../include)

add_library(SOG::GuiCollector ALIAS GuiCollector_lib)
