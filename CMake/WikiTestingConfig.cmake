option(BUILD_TESTING "Build the testing tree." OFF)

if(BUILD_TESTING)
  enable_testing()
  include(CTest)
  configure_file(
    ${WikiExamples_SOURCE_DIR}/CMake/SampleBuildTest.cmake.in
    ${WikiExamples_BINARY_DIR}/SampleBuildTest.cmake @ONLY)
  message(STATUS "VTKWikiExamples: Tests will be built with label \"WikiExamples\"")
else()
  message(STATUS "VTKWikiExamples: Tests will not be built")
endif()
