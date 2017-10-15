PROJECT (${WIKI}Rendering)

IF(NOT WikiExamples_BINARY_DIR)
FIND_PACKAGE(VTK REQUIRED)
IF(NOT VTK_USE_RENDERING)
  MESSAGE(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
ENDIF(NOT VTK_USE_RENDERING)
INCLUDE(${VTK_USE_FILE})
ENDIF(NOT WikiExamples_BINARY_DIR)

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  SET(KIT_LIBS vtkHybrid vtkWidgets)
else()
  SET(KIT_LIBS ${VTK_LIBRARIES})
endif()
#
# Build all .cxx files in the directory
FILE(GLOB ALL_FILES *.cxx)
foreach(SOURCE_FILE ${ALL_FILES})
  STRING(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  STRING(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  ADD_EXECUTABLE(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  TARGET_LINK_LIBRARIES(${WIKI}${EXAMPLE} ${KIT_LIBS})
endforeach(SOURCE_FILE)

if (BUILD_TESTING)
# Testing
SET(KIT Rendering)
SET(NEEDS_ARGS
  Rainbow
  Rotations
  WalkCow
  WalkCowA
  WalkCowB
)
SET(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)
SET(TEMP ${WikiExamples_BINARY_DIR}/Testing/Temporary)

ADD_TEST(${KIT}-Rotations ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestRotations ${DATA}/cow.obj)

ADD_TEST(${KIT}-Rainbow ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestRainbow ${DATA}/combxyz.bin ${DATA}/combq.bin)

ADD_TEST(${KIT}-WalkCow ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestWalkCow ${DATA}/cow.g)

ADD_TEST(${KIT}-WalkCowA ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestWalkCowA ${DATA}/cow.g 1)

ADD_TEST(${KIT}-WalkCowB ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestWalkCowB ${DATA}/cow.g 2)

INCLUDE(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)

endif()
