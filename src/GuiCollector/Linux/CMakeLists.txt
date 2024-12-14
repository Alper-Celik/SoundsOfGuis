add_library(GuiCollector_Linux_AtSpi2 GuiElementAtSpi2.cpp
                                      GuiCollectorAtSpi2.cpp)
target_link_libraries(
  GuiCollector_Linux_AtSpi2
  PUBLIC atspi-2::atspi-2 SOG::Utils
  PRIVATE gobject-2::gobject-2 xcb::xcb magic_enum::magic_enum fmt::fmt)

target_include_directories(
  GuiCollector_Linux_AtSpi2
  PUBLIC ./include
  PRIVATE ../include)

add_library(SOG::GuiCollector::Linux::AtSpi2 ALIAS GuiCollector_Linux_AtSpi2)
