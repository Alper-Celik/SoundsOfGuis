add_subdirectory(QtUi)

add_executable(UserInterface Main.cpp)
set_target_properties(UserInterface PROPERTIES OUTPUT_NAME "sounds-of-guis")

target_include_directories(Sounds_lib PUBLIC ./include)

target_link_libraries(UserInterface PRIVATE SOG::MainLoop SOG::UI::QT
                                            CLI11::CLI11)
