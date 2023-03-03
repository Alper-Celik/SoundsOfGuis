find_package(PkgConfig REQUIRED)
pkg_search_module(ATKMM REQUIRED IMPORTED_TARGET libxdo)

add_library(AtkMM::AtkMM ALIAS PkgConfig::ATKMM)
