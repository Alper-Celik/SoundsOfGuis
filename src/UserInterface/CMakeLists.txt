add_subdirectory(QtUi)

add_executable(UI Main.cpp)

target_include_directories(Sounds_lib PUBLIC ./include)

target_link_libraries(UI PUBLIC SOG::MainLoop SOG::UI::QT CLI11::CLI11)
