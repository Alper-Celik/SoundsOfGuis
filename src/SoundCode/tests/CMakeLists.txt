add_executable(Sounds_lib_tests _SoundSource_tests.cpp SoundCode_tests.cpp)
target_link_libraries(
  Sounds_lib_tests PRIVATE OpenAL::OpenAL Catch2::Catch2WithMain SOG::SoundCode)
cmake_path(CONVERT "${CMAKE_CURRENT_SOURCE_DIR}/test_metarial"
           TO_NATIVE_PATH_LIST test_metarial)
target_compile_definitions(Sounds_lib_tests
                           PRIVATE TEST_METARIAL_DIR="${test_metarial}")
catch_discover_tests(Sounds_lib_tests)
