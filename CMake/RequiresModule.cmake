macro(Requires_Module example module)
  if (VTK_VERSION VERSION_LESS "8.90.0")
    if(NOT ${module}_LOADED)
      message(STATUS "VTKWikiExamples: ${example} requires VTK module ${module} and will not be built")
      string(REGEX REPLACE "[^;]*${example}.cxx"
             "" ALL_FILES "${ALL_FILES}")
      string(REGEX REPLACE "[^;]*${example}.ui"
             "" ALL_UI_FILES "${ALL_UI_FILES}")
     endif()
  else()
    string(REGEX REPLACE "vtk" "" _module ${module})
    list(FIND VTK_AVAILABLE_COMPONENTS ${_module} _found) 
    if(_found EQUAL -1)
      message(STATUS "VTKWikiExamples: ${example} requires VTK module ${_module} and will not be built")
      string(REGEX REPLACE "[^;]*${example}.cxx"
             "" ALL_FILES "${ALL_FILES}")
      string(REGEX REPLACE "[^;]*${example}.ui"
             "" ALL_UI_FILES "${ALL_UI_FILES}")
     endif()
  endif()
endmacro()
