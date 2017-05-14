PROJECT (${WIKI}InfoVis)

IF(NOT WikiExamples_BINARY_DIR)
FIND_PACKAGE(VTK REQUIRED)
IF(NOT VTK_USE_INFOVIS)
  MESSAGE(FATAL_ERROR "VTKWikiExamples: Example ${PROJECT_NAME} requires VTK_USE_INFOVIS.")
ENDIF(NOT VTK_USE_INFOVIS)
INCLUDE(${VTK_USE_FILE})
ENDIF(NOT WikiExamples_BINARY_DIR)

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  SET(KIT_LIBS vtkWidgets vtkRendering vtkHybrid vtkViews vtkInfovis)
else()
  SET(KIT_LIBS ${VTK_LIBRARIES})
endif()
#
# Build all .cxx files in the directory
FILE(GLOB ALL_FILES *.cxx)

include(${WikiExamples_SOURCE_DIR}/CMake/RequiresModule.cmake)
include(${WikiExamples_SOURCE_DIR}/CMake/RequiresSettingOn.cmake)

include(${WikiExamples_SOURCE_DIR}/CMake/RequiresVersion.cmake)
set(VERSION_MIN "6.0")
Requires_Version(TreeMapView ${VERSION_MIN} ALL_FILES)
Requires_Setting_On (TreeMapView BUILD_TESTING)

if(NOT VTK_USE_PARALLEL)
  set(SKIP PKMeansClustering)
  message(STATUS "VTKWikiExamples: ${SKIP} requires VTK_PARALLEL and will not be built")
  string(REGEX REPLACE "[^;]*${SKIP}.cxx"
         "" ALL_FILES "${ALL_FILES}")
endif()

foreach(SOURCE_FILE ${ALL_FILES})
  STRING(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  STRING(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  ADD_EXECUTABLE(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  TARGET_LINK_LIBRARIES(${WIKI}${EXAMPLE} ${KIT_LIBS})
endforeach(SOURCE_FILE)

if (BUILD_TESTING)
# Testing
SET(KIT InfoVis)

SET(DATA ${WikiExamples_SOURCE_DIR}/Testing/Data)

SET(NEEDS_ARGS
  DelimitedTextReader
  DelimitedTextWriter
  XGMLReader
)
if ("${ALL_FILES}" MATCHES ".*TreeMapView.*")
  SET(NEEDS_ARGS "${NEEDS_ARGS};TreeMapView")
  ADD_TEST(${KIT}-TreeMapView ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestTreeMapView ${DATA}/Infovis-XML-vtkclasses.xml ${DATA}/Infovis-XML-vtklibrary.xml)
endif()

SET(DATA ${WikiExamples_SOURCE_DIR}/Testing/Data)
SET(TEMP ${WikiExamples_BINARY_DIR}/Testing/Temporary)

ADD_TEST(${KIT}-DelimitedTextReader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestDelimitedTextReader ${DATA}/DelimitedData.txt)

ADD_TEST(${KIT}-DelimitedTextWriter ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestDelimitedTextWriter ${TEMP}/foo.txt)

ADD_TEST(${KIT}-XGMLReader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestXGMLReader ${DATA}/fsm.gml)

INCLUDE(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)

endif()
