find_package(PkgConfig REQUIRED)
pkg_search_module(SNDFILE REQUIRED IMPORTED_TARGET sndfile)
add_library(SndFile::sndfile ALIAS PkgConfig::SNDFILE)
