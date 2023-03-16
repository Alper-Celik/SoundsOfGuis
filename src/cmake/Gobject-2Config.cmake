find_package(PkgConfig REQUIRED)
pkg_check_modules(GOBJECT2 REQUIRED IMPORTED_TARGET gobject-2.0)

add_library(gobject-2::gobject-2 ALIAS PkgConfig::GOBJECT2)
