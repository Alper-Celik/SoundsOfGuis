if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  add_subdirectory(Linux)
endif()

if(enable_tests)
  add_subdirectory(tests)
endif()
