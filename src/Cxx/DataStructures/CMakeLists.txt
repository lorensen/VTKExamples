project (${WIKI}DataStructures)

if(NOT WikiExamples_BINARY_DIR)
find_package(VTK REQUIRED)
if(NOT VTK_USE_RENDERING)
  message(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
endif()
include(${VTK_USE_FILE})
endif()

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 6.0)
  set(KIT_LIBS vtkHybrid vtkRendering vtkWidgets vtkCharts)
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
set(KIT DataStructures)
set(NEEDS_ARGS
  DataStructureComparison
  VisualizeKDTree
  VisualizeOBBTree
  KDTreeTimingDemo
  ModifiedBSPTreeTimingDemo
  OBBTreeTimingDemo
  OctreeTimingDemo
  OctreeVisualize
)
set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)

add_test(${KIT}-DataStructureComparison ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestDataStructureComparison ${DATA}/Bunny.vtp -E 20)

add_test(${KIT}-VisualizeKDTree ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestVisualizeKDTree -E 40)
add_test(${KIT}-VisualizeOBBTree ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestVisualizeOBBTree -E 40)

# These tests will generate different output each time they run.
# To avoid regression failures, set the error tolerance to a large number. 
add_test(${KIT}-KDTreeTimingDemo ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestKDTreeTimingDemo -E 999999)
add_test(${KIT}-ModifiedBSPTreeTimingDemo ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestModifiedBSPTreeTimingDemo -E 999999)
add_test(${KIT}-OBBTreeTimingDemo ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestOBBTreeTimingDemo -E 999999)
add_test(${KIT}-OctreeTimingDemo ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestOctreeTimingDemo -E 999999)

add_test(${KIT}-OctreeVisualize ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestOctreeVisualize -E 40)

include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)

add_subdirectory(ModifiedBSPTree)

endif()
