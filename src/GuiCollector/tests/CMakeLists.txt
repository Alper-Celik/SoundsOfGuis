macro(add_catch_test file_name)
  add_executable(${file_name} ${file_name}.cpp)
  target_link_libraries(
    ${file_name}
    Catch2::Catch2WithMain
    SOG::GuiCollector
    Qt5::Widgets
    Qt5::Qml
    Qt5::Core)

  cmake_path(CONVERT "${CMAKE_CURRENT_SOURCE_DIR}/test_metarial"
             TO_NATIVE_PATH_LIST test_metarial)
  target_compile_definitions(${file_name}
                             PRIVATE TEST_METARIAL_DIR="${test_metarial}")

  catch_discover_tests(${file_name})

endmacro()

add_catch_test(element_comparission_test)
add_catch_test(parent_element_test)
add_catch_test(element_type_checks_test)
add_catch_test(mouse_pos_test)
