add_executable(Sounds_lib_tests _SoundSource_tests.cpp)
target_link_libraries(Sounds_lib_tests PRIVATE Catch2::Catch2WithMain
                                               SOG::Sounds)
catch_discover_tests(Sounds_lib_tests)
