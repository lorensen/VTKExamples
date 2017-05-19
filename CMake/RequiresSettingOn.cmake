macro(Requires_Setting_On example setting)
  if(NOT ${setting})
    message(STATUS "VTKWikiExamples: ${example} requires the setting ${setting}:BOOL=ON and will not be built")
      string(REGEX REPLACE "[^;]*${example}.cxx"
             "" ALL_FILES "${ALL_FILES}")
      string(REGEX REPLACE "[^;]*${example}.ui"
             "" ALL_UI_FILES "${ALL_UI_FILES}")
  endif()
endmacro()
