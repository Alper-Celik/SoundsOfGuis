add_library(Sounds_lib STATIC SoundCode.cpp _SoundSource.cpp)

target_include_directories(Sounds_lib PUBLIC ./include)

target_link_libraries(
  Sounds_lib
  PRIVATE SndFile::sndfile fmt::fmt Microsoft.GSL::GSL
  PUBLIC SOG::Utils OpenAL::OpenAL)

add_library(SOG::Sounds ALIAS Sounds_lib)

if(enable_tests)
  add_subdirectory(tests)
endif()
