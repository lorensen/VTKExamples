macro(Requires_CxxVersion example version_min)
  if ((CMAKE_CXX_STANDARD EQUAL 11) OR (CMAKE_CXX_STANDARD GREATER 11))
    # Compile this example
  else()
    # If variable is not set or less than 11:
    message(STATUS "VTKWikiExamples: ${example} requires C++${version_min} or newer")
    string(REGEX REPLACE "[^;]*${example}.cxx"
           "" ALL_FILES "${ALL_FILES}")
    string(REGEX REPLACE "[^;]*${example}.ui"
           "" ALL_UI_FILES "${ALL_UI_FILES}")
  endif()
endmacro()
