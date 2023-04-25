add_subdirectory(QtUi)

add_executable(UserInterface Main.cpp Terminate_handler.cpp)
set_target_properties(UserInterface PROPERTIES OUTPUT_NAME "sounds-of-guis")

target_include_directories(Sounds_lib PUBLIC ./include)

target_link_libraries(
  UserInterface
  PRIVATE SOG::Utils
          SOG::MainLoop
          SOG::UI::QT
          CLI11::CLI11
          Boost::boost
          libbacktrace_for_boost
          yaml-cpp)
