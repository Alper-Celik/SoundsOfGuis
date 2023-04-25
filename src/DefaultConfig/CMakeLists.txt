function(add_sounds)
  find_program(MUSESCORE mscore musescore mscore4portable MuseScore4.exe)
  foreach(SOUND ${ARGN})
    add_custom_command(
      DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${SOUND}.musicxml
      OUTPUT ${PROJECT_BINARY_DIR}/${SOUND}.wav
      COMMAND ${MUSESCORE} ${CMAKE_CURRENT_SOURCE_DIR}/${SOUND}.musicxml -o
              ${PROJECT_BINARY_DIR}/${SOUND}.wav)
    list(APPEND SOUND_RESULTS ${PROJECT_BINARY_DIR}/${SOUND}.wav)
  endforeach()
  set(SOUND_RESULTS
      ${SOUND_RESULTS}
      PARENT_SCOPE)
endfunction()
add_sounds(link)

add_custom_target(Sounds ALL DEPENDS ${SOUND_RESULTS})
# ${PROJECT_BINARY_DIR}/link.wav)
