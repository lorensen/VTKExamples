macro(Requires_GitLfs example)
  file(READ "${WikiExamples_SOURCE_DIR}/src/Testing/Data/GitLfsInstalled" data)
  if (NOT data STREQUAL "GitLfsNotInstalled")
    message(STATUS "VTKWikiExamples: ${example} requires git lfs to be installed and will not be built")
    string(REGEX REPLACE "[^;]*${example}.cxx"
           "" ALL_FILES "${ALL_FILES}")
    string(REGEX REPLACE "[^;]*${example}.ui"
           "" ALL_UI_FILES "${ALL_UI_FILES}")
  endif()
endmacro()
