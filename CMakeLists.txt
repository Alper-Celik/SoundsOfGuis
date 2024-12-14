cmake_minimum_required(VERSION 3.20)
project("Sounds of GUIs" VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

option(enable_tests "enable building of tests" ON)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/cmake)
list(PREPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/cmake)

find_package(OpenAL CONFIG REQUIRED)
find_package(SndFile CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(Boost CONFIG REQUIRED)
find_package(Microsoft.GSL CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)
find_package(CLI11 CONFIG REQUIRED)

find_package(tomlplusplus CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)

find_package(Qt6 CONFIG REQUIRED COMPONENTS Widgets Qml Quick Core)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
add_compile_definitions(
  $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  find_package(Atspi-2 CONFIG REQUIRED)
  find_package(Gobject-2 CONFIG REQUIRED)

  find_package(xcb CONFIG REQUIRED)

  find_package(libbacktrace_hack CONFIG REQUIRED)
endif()

if(enable_tests)
  include(CTest)

  find_package(Catch2 3 REQUIRED)
  include(Catch)
endif()

add_subdirectory(src)
