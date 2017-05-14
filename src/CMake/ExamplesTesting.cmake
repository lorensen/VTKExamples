#
# Create tests for examples
#
if (BUILD_TESTING)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
SET(MyTests "")
foreach(SOURCE_FILE ${ALL_FILES})
  STRING(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  STRING(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  SET(MyTests ${MyTests} Test${EXAMPLE}.cxx)
  FILE(WRITE ${CMAKE_CURRENT_BINARY_DIR}/Test${EXAMPLE}.cxx
    "#define main Test${EXAMPLE}\n#include \"${EXAMPLE}.cxx\"\n")
  LIST(FIND NEEDS_ARGS ${EXAMPLE} SKIP_ADD)
  if(SKIP_ADD EQUAL -1)
    ADD_TEST(${KIT}-${EXAMPLE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests Test${EXAMPLE})
  endif(SKIP_ADD EQUAL -1)
  set_property(TEST ${KIT}-${EXAMPLE} PROPERTY LABELS WikiExamples)
endforeach(SOURCE_FILE)
SET(VTK_BINARY_DIR ${WikiExamples_BINARY_DIR})
SET(VTK_DATA_ROOT ${WikiExamples_SOURCE_DIR}/Testing)
INCLUDE(${WikiExamples_SOURCE_DIR}/CMake/vtkTestingObjectFactory.cmake)
ADD_EXECUTABLE(${KIT}CxxTests ${KIT}CxxTests.cxx
               ${MyTests})
TARGET_LINK_LIBRARIES(${KIT}CxxTests ${KIT_LIBS})
endif()