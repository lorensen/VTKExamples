project (${WIKI}DataStructures)

if(NOT VTK_BINARY_DIR)
  set(VTK_LIBRARIES "")
  find_package(VTK COMPONENTS
 vtkChartsCore
  vtkCommonColor
  vtkCommonCore
  vtkCommonDataModel
  vtkCommonSystem
  vtkFiltersExtraction
  vtkFiltersFlowPaths
  vtkFiltersGeneral
  vtkFiltersSources
  vtkIOGeometry
  vtkIOLegacy
  vtkIOPLY
  vtkIOXML
  vtkInteractionStyle
  vtkInteractionWidgets
  vtkRenderingContext2D
  vtkRenderingContextOpenGL2
  vtkRenderingCore
  vtkRenderingFreeType
  vtkRenderingGL2PSOpenGL2
  vtkRenderingOpenGL2
  vtkViewsContext2D
  OPTIONAL_COMPONENTS
  vtkTestingRendering
  QUIET
   )
  if (VTK_VERSION VERSION_LESS "8.90.0")
    include(${VTK_USE_FILE})
  endif()
endif()

set(KIT_LIBS ${VTK_LIBRARIES})

#
# Build all .cxx files in the directory
file(GLOB ALL_FILES *.cxx)
foreach(SOURCE_FILE ${ALL_FILES})
  string(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  add_executable(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  target_link_libraries(${WIKI}${EXAMPLE} ${KIT_LIBS})
  if (NOT VTK_VERSION VERSION_LESS "8.90.0")
    vtk_module_autoinit(
      TARGETS ${WIKI}${EXAMPLE}
      MODULES ${VTK_LIBRARIES}
      )
  endif()
endforeach()

if (BUILD_TESTING)
  # Testing
  set(KIT DataStructures)
  set(NEEDS_ARGS
    DataStructureComparison
    KDTreeFindPointsWithinRadiusDemo
    KDTreeTimingDemo
    ModifiedBSPTreeTimingDemo
    OBBTreeTimingDemo
    OctreeFindPointsWithinRadiusDemo
    OctreeTimingDemo
    OctreeVisualize
    PointLocatorFindPointsWithinRadiusDemo
    StaticLocatorFindPointsWithinRadiusDemo
    VisualizeKDTree
    VisualizeModifiedBSPTree
    VisualizeOBBTree
    )
  set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)

  add_test(${KIT}-DataStructureComparison ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestDataStructureComparison ${DATA}/Bunny.vtp -E 20)

  add_test(${KIT}-VisualizeKDTree ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestVisualizeKDTree ${DATA}/shark.ply)
  add_test(${KIT}-VisualizeOBBTree ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestVisualizeOBBTree ${DATA}/shark.ply)
  add_test(${KIT}-VisualizeModifiedBSPTree ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestVisualizeModifiedBSPTree ${DATA}/shark.ply)

  add_test(${KIT}-KDTreeFindPointsWithinRadiusDemo ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestKDTreeFindPointsWithinRadiusDemo ${DATA}/dragon.ply 10)

  add_test(${KIT}-OctreeFindPointsWithinRadiusDemo ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestOctreeFindPointsWithinRadiusDemo ${DATA}/dragon.ply 10)

  add_test(${KIT}-PointLocatorFindPointsWithinRadiusDemo ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestPointLocatorFindPointsWithinRadiusDemo ${DATA}/dragon.ply 10)

  add_test(${KIT}-StaticLocatorFindPointsWithinRadiusDemo ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestStaticLocatorFindPointsWithinRadiusDemo ${DATA}/dragon.ply 10)

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

endif()
