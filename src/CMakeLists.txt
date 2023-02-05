set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

option(enable_tests "enable building of tests" ON)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(PREPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(OpenAL CONFIG REQUIRED)
find_package(SndFile CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(Boost CONFIG REQUIRED)
find_package(Microsoft.GSL CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)

find_package(Qt5 CONFIG REQUIRED COMPONENTS Widgets Qml Core)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  find_package(Atspi-2 CONFIG REQUIRED)
  find_package(Gobject-2 CONFIG REQUIRED)

  find_package(libxdo CONFIG REQUIRED)
endif()

if(enable_tests)
  include(CTest)

  find_package(Catch2 3 REQUIRED)
  include(Catch)

  include(BoostLinux_libbacktrace)
endif()

add_subdirectory(Utils)
add_subdirectory(SoundCode)
add_subdirectory(GuiCollector)
add_subdirectory(MainLoop)
add_subdirectory(UserInterface)
