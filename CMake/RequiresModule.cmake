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
    string(REGEX REPLACE "vtk" "VTK::" _module "${module}")
    if(NOT TARGET ${_module})
      message(STATUS "VTKWikiExamples: ${example} requires VTK module ${_module} and will not be built")
      string(REGEX REPLACE "[^;]*${example}.cxx"
             "" ALL_FILES "${ALL_FILES}")
      string(REGEX REPLACE "[^;]*${example}.ui"
             "" ALL_UI_FILES "${ALL_UI_FILES}")
     endif()
  endif()
endmacro()
