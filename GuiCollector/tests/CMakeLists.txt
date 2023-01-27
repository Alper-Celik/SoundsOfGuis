add_executable(Guicollector_lib_tests GuiCollector_tests.cpp)
target_link_libraries(Guicollector_lib_tests Catch2::Catch2WithMain
                      SOG::GuiCollector Qt5::Widgets Qt5::Qml Qt5::Core)

cmake_path(CONVERT "${CMAKE_CURRENT_SOURCE_DIR}/test_metarial"
           TO_NATIVE_PATH_LIST test_metarial)
target_compile_definitions(Guicollector_lib_tests
                           PRIVATE TEST_METARIAL_DIR="${test_metarial}")

catch_discover_tests(Guicollector_lib_tests)
