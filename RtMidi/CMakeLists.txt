
add_library(RtMidi RtMidi.cpp)

if(WIN32)
  target_link_libraries(RtMidi PUBLIC winmm)
elseif(APPLE)
  target_link_libraries(RtMidi PUBLIC "-framework CoreMIDI" "-framework CoreFoundation" "-framework CoreAudio")
elseif(UNIX)
  target_link_libraries(RtMidi PUBLIC asound pthread)
endif()


target_include_directories(RtMidi INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
