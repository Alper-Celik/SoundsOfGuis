add_library(Sounds_lib STATIC SoundCode.cpp _SoundSource.cpp)

target_include_directories(Sounds_lib PUBLIC ./include)
target_include_directories(Sounds_lib PRIVATE ./impl_include)

target_link_libraries(Sounds_lib SndFile::sndfile OpenAL::OpenAL fmt::fmt
                      SOG::Utils)

add_library(SOG::Sounds ALIAS Sounds_lib)

if(enable_tests)
  add_subdirectory(tests)
endif()
