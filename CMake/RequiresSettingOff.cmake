macro(Requires_Setting_Off example setting)
  if(${setting})
    message(STATUS "VTKWikiExamples: ${example} requires the setting ${setting}:BOOL=OFF and will not be built")
      string(REGEX REPLACE "[^;]*${example}.cxx"
             "" ALL_FILES "${ALL_FILES}")
      string(REGEX REPLACE "[^;]*${example}.ui"
             "" ALL_UI_FILES "${ALL_UI_FILES}")
  endif()
endmacro()
