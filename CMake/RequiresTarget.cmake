macro(Requires_Target target class)
  if (NOT TARGET ${target})
  message(STATUS "VTKWikiExamples: ${example} requires ${class} and will not be built")
  string(REGEX REPLACE "[^;]*${target}.cxx"
         "" ALL_FILES "${ALL_FILES}")
  endif()
endmacro()
