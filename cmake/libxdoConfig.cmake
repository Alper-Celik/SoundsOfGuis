find_package(PkgConfig REQUIRED)
pkg_search_module(LIBXDO REQUIRED IMPORTED_TARGET libxdo)

add_library(libxdo::libxdo ALIAS PkgConfig::LIBXDO)
