find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBXDO REQUIRED IMPORTED_TARGET libxdo)

add_library(libxdo::libxdo ALIAS PkgConfig::LIBXDO)
