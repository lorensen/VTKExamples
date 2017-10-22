project (${WIKI}CompositeData)

if(NOT WikiExamples_BINARY_DIR)
find_package(VTK REQUIRED)
if(NOT VTK_USE_RENDERING)
  message(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
endif()
include(${VTK_USE_FILE})
endif()

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  set(KIT_LIBS vtkFiltering vtkHybrid)
else()
  set(KIT_LIBS ${VTK_LIBRARIES})
endif()
#
# Build all .cxx files in the directory
file(GLOB ALL_FILES *.cxx)
foreach(SOURCE_FILE ${ALL_FILES})
  string(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  add_executable(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  target_link_libraries(${WIKI}${EXAMPLE} ${KIT_LIBS})
endforeach()

if (BUILD_TESTING)
# Testing
set(KIT CompositeData)
set(NEEDS_ARGS
  OverlappingAMR
)

set (EXCLUDE_TEST
  HierarchicalBoxPipeline
  Generate3DAMRDataSetWithPulse
)

add_test(${KIT}-OverlappingAMR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestOverlappingAMR -E 35)
add_test(${KIT}-CompositePolyDataMapper ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestCompositePolyDataMapper)
add_test(${KIT}-MultiBlockDataSet ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestMultiBlockDataSet)

include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)

endif()
