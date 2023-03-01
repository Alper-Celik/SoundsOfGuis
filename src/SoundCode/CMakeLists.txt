add_library(Sounds_lib STATIC SoundCode.cpp _SoundSource.cpp)

target_include_directories(Sounds_lib PUBLIC ./include)

target_link_libraries(
  Sounds_lib
  PRIVATE SndFile::sndfile fmt::fmt Microsoft.GSL::GSL OpenAL::OpenAL
  PUBLIC SOG::Utils)

add_library(SOG::SoundCode ALIAS Sounds_lib)

if(enable_tests)
  add_subdirectory(tests)
endif()
