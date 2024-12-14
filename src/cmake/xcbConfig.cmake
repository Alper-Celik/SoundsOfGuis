find_package(PkgConfig REQUIRED)
pkg_check_modules(XCB REQUIRED IMPORTED_TARGET xcb)

add_library(xcb::xcb ALIAS PkgConfig::XCB)
