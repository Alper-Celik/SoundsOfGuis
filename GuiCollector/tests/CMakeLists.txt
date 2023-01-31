macro(add_hacky_test file_name)
  add_executable(hacky_test_${file_name} ${file_name}.cpp)
  target_link_libraries(hacky_test_${file_name} Catch2::Catch2WithMain
                        SOG::GuiCollector Qt5::Widgets Qt5::Qml Qt5::Core)

  cmake_path(CONVERT "${CMAKE_CURRENT_SOURCE_DIR}/test_metarial"
             TO_NATIVE_PATH_LIST test_metarial)
  target_compile_definitions(hacky_test_${file_name}
                             PRIVATE TEST_METARIAL_DIR="${test_metarial}")

  catch_discover_tests(hacky_test_${file_name})

endmacro()

add_hacky_test(GuiCollector_tests)
add_hacky_test(testing)
