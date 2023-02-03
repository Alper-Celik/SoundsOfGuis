find_package(PkgConfig REQUIRED)
pkg_search_module(ATSPI2 REQUIRED IMPORTED_TARGET atspi-2)

add_library(atspi-2::atspi-2 ALIAS PkgConfig::ATSPI2)
