macro(Requires_Module example module)
  if(${VTK_VERSION} VERSION_GREATER "3")
    if(NOT ${module}_LOADED)
      message(STATUS "VTKWikiExamples: ${example} requires VTK module ${module} and will not be built")
      string(REGEX REPLACE "[^;]*${example}.cxx"
             "" ALL_FILES "${ALL_FILES}")
      string(REGEX REPLACE "[^;]*${example}.ui"
             "" ALL_UI_FILES "${ALL_UI_FILES}")
     endif()
  endif()
endmacro()
