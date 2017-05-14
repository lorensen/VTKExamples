PROJECT (${WIKI}VolumeRendering)

IF(NOT WikiExamples_BINARY_DIR)
FIND_PACKAGE(VTK REQUIRED)
IF(NOT VTK_USE_RENDERING)
  MESSAGE(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
ENDIF(NOT VTK_USE_RENDERING)
INCLUDE(${VTK_USE_FILE})
ENDIF(NOT WikiExamples_BINARY_DIR)

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  SET(KIT_LIBS vtkRendering vtkVolumeRendering vtkHybrid)
else()
  SET(KIT_LIBS ${VTK_LIBRARIES})
endif()
#
# Build all .cxx files in the directory
FILE(GLOB ALL_FILES *.cxx)

if (VTK_RENDERING_BACKEND STREQUAL "OpenGL2")
  list(REMOVE_ITEM ALL_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/SmartVolumeMapper.cxx)
  list(REMOVE_ITEM ALL_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/HAVSVolumeMapper.cxx)
endif()

foreach(SOURCE_FILE ${ALL_FILES})
  STRING(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  STRING(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  ADD_EXECUTABLE(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  TARGET_LINK_LIBRARIES(${WIKI}${EXAMPLE} ${KIT_LIBS})
endforeach(SOURCE_FILE)

if (BUILD_TESTING)
# Testing
SET(KIT VolumeRendering)
if (VTK_RENDERING_BACKEND STREQUAL "OpenGL2")
  SET(NEEDS_ARGS
    MinIntensityRendering
  )
else()
  SET(NEEDS_ARGS
    HAVSVolumeMapper
    MinIntensityRendering
  )
endif()

SET(DATA ${WikiExamples_SOURCE_DIR}/Testing/Data)
SET(TEMP ${WikiExamples_BINARY_DIR}/Testing/Temporary)

if (VTK_RENDERING_BACKEND STREQUAL "OpenGL2")
ADD_TEST(${KIT}-MinIntensityRendering ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestMinIntensityRendering ${DATA}/ironProt.vtk)
else()
ADD_TEST(${KIT}-HAVSVolumeMapper ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestHAVSVolumeMapper ${DATA}/ironProt.vtk ${DATA}/neghip.slc)

ADD_TEST(${KIT}-MinIntensityRendering ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestMinIntensityRendering ${DATA}/ironProt.vtk)
endif()

INCLUDE(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)

endif()
