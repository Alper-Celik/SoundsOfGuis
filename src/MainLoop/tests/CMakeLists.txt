add_executable(MainLoop_lib_tests GetDirs_tests.cpp ParseConfig_tests.cpp)
target_link_libraries(
  MainLoop_lib_tests PRIVATE Catch2::Catch2WithMain SOG::MainLoop SOG::Utils
                             magic_enum::magic_enum)

cmake_path(CONVERT "${CMAKE_CURRENT_SOURCE_DIR}/test_metarial"
           TO_NATIVE_PATH_LIST test_metarial)
target_compile_definitions(MainLoop_lib_tests
                           PRIVATE TEST_METARIAL_DIR="${test_metarial}")

catch_discover_tests(MainLoop_lib_tests)
