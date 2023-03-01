add_library(GuiCollector_lib LinuxImpl.cpp)
target_link_libraries(
  GuiCollector_lib
  PUBLIC atspi-2::atspi-2 SOG::Utils
  PRIVATE gobject-2::gobject-2 libxdo::libxdo magic_enum::magic_enum fmt::fmt)

target_include_directories(GuiCollector_lib PUBLIC ./include ../include)

add_library(SOG::GuiCollector ALIAS GuiCollector_lib)
