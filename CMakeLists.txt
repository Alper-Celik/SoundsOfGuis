cmake_minimum_required(VERSION 3.20)
project(SoundsOfGUIs)
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

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  find_package(Atspi-2 CONFIG REQUIRED)
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
