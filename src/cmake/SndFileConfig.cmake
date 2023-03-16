find_package(PkgConfig REQUIRED)
pkg_check_modules(SNDFILE REQUIRED IMPORTED_TARGET sndfile)

add_library(SndFile::sndfile ALIAS PkgConfig::SNDFILE)
