macro(Requires_Version example version_min)
  if(${VTK_VERSION} VERSION_LESS "${version_min}")
  message(STATUS "VTKWikiExamples: ${example} requires VTK version ${version_min} or newer but the current version is ${VTK_VERSION}")
  string(REGEX REPLACE "[^;]*${example}.cxx"
         "" ALL_FILES "${ALL_FILES}")
  endif()
endmacro()
