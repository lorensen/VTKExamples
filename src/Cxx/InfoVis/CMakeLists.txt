project (${WIKI}InfoVis)

if(NOT WikiExamples_BINARY_DIR)
find_package(VTK REQUIRED)
if(NOT VTK_USE_INFOVIS)
  message(FATAL_ERROR "VTKWikiExamples: Example ${PROJECT_NAME} requires VTK_USE_INFOVIS.")
endif(NOT VTK_USE_INFOVIS)
include(${VTK_USE_FILE})
endif(NOT WikiExamples_BINARY_DIR)

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  set(KIT_LIBS vtkWidgets vtkRendering vtkHybrid vtkViews vtkInfovis)
else()
  set(KIT_LIBS ${VTK_LIBRARIES})
endif()
#
# Build all .cxx files in the directory
file(GLOB ALL_FILES *.cxx)

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
  string(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  add_executable(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  target_link_libraries(${WIKI}${EXAMPLE} ${KIT_LIBS})
endforeach(SOURCE_FILE)

if (BUILD_TESTING)
# Testing
set(KIT InfoVis)

set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)

set(NEEDS_ARGS
  DelimitedTextReader
  DelimitedTextWriter
  XGMLReader
)
if ("${ALL_FILES}" MATCHES ".*TreeMapView.*")
  set(NEEDS_ARGS "${NEEDS_ARGS};TreeMapView")
  add_test(${KIT}-TreeMapView ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestTreeMapView ${DATA}/Infovis-XML-vtkclasses.xml ${DATA}/Infovis-XML-vtklibrary.xml)
endif()

set(TEMP ${WikiExamples_BINARY_DIR}/Testing/Temporary)

add_test(${KIT}-DelimitedTextReader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestDelimitedTextReader ${DATA}/DelimitedData.txt)

add_test(${KIT}-DelimitedTextWriter ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestDelimitedTextWriter ${TEMP}/foo.txt)

add_test(${KIT}-XGMLReader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestXGMLReader ${DATA}/fsm.gml)

include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)

endif()
