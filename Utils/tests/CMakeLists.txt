add_executable(Utils_lib_tests ExceptionUtils_tests.cpp)
target_link_libraries(Utils_lib_tests PRIVATE Catch2::Catch2WithMain SOG::Utils)
catch_discover_tests(Utils_lib_tests)
