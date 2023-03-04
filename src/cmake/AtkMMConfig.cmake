find_package(PkgConfig REQUIRED)
pkg_check_modules(ATKMM REQUIRED IMPORTED_TARGET atkmm-2.36)

add_library(AtkMM::AtkMM ALIAS PkgConfig::ATKMM)
