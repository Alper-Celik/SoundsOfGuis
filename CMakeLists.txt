cmake_minimum_required(VERSION 3.10)
project(SoundsOfGUIs)

option(enable_tests "enable building of tests" ON)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_subdirectory(SoundCode)
