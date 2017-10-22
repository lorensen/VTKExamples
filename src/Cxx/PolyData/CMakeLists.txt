project (${WIKI}PolyData)

if(NOT WikiExamples_BINARY_DIR)
find_package(VTK REQUIRED)
if(NOT VTK_USE_RENDERING)
  message(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
endif(NOT VTK_USE_RENDERING)
include(${VTK_USE_FILE})
endif(NOT WikiExamples_BINARY_DIR)

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  set(KIT_LIBS vtkWidgets vtkHybrid vtkCharts)
else()
  set(KIT_LIBS ${VTK_LIBRARIES})
endif()
#
# Build all .cxx files in the directory
file(GLOB ALL_FILES *.cxx)

include(${WikiExamples_SOURCE_DIR}/CMake/RequiresVersion.cmake)

set(VERSION_MIN "5.9.20111206")
Requires_Version(LoopBooleanPolyDataFilter ${VERSION_MIN} ALL_FILES)
Requires_Version(BooleanOperationPolyDataFilter ${VERSION_MIN} ALL_FILES)
Requires_Version(DistancePolyDataFilter ${VERSION_MIN} ALL_FILES)
Requires_Version(ImplicitPolyDataDistance ${VERSION_MIN} ALL_FILES)
Requires_Version(IntersectionPolyDataFilter ${VERSION_MIN} ALL_FILES)
Requires_Version(Curvatures "6.0.0" ALL_FILES)

foreach(SOURCE_FILE ${ALL_FILES})
  string(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  add_executable(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  target_link_libraries(${WIKI}${EXAMPLE} ${KIT_LIBS})
endforeach(SOURCE_FILE)

if (BUILD_TESTING)
# Testing
set(KIT PolyData)
set(NEEDS_ARGS
  BooleanOperationPolyDataFilter
  LoopBooleanPolyDataFilter
  CellLocatorVisualization
  ColoredPoints
  ConvexHull
  DetermineArrayDataTypes
  DijkstraGraphGeodesicPath	
  EmbedPointsIntoVolume
  ExternalContour
  GetMiscCellData
  GetMiscPointData
  GradientFilter
  GreedyTerrainDecimation
  HighlightBadCells
  Hull
  ImplicitModeller
  MiscPointData
  PointLocatorVisualization
  PolyDataIsoLines
  PolyDataPointSampler
  RemoveVertices
  Silhouette
  ShrinkPolyData
  ThinPlateSplineTransform
  TriangleColoredPoints
  TriangleSolidColor
  WarpSurface
)
if(NOT ${VTK_VERSION} VERSION_LESS "6")
  list(APPEND NEEDS_ARGS Curvatures)
endif()

set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)
set(TEMP ${WikiExamples_BINARY_DIR}/Testing/Temporary)

add_test(${KIT}-BooleanOperationPolyDataFilter ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestBooleanOperationPolyDataFilter ${DATA}/Torso.vtp difference ${DATA}/ObliqueCone.vtp)

add_test(${KIT}-LoopBooleanPolyDataFilter ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestLoopBooleanPolyDataFilter ${DATA}/Torso.vtp difference ${DATA}/ObliqueCone.vtp)

add_test(${KIT}-CellLocatorVisualization ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestCellLocatorVisualization -E 50)

add_test(${KIT}-ColoredPoints ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestColoredPoints ${TEMP}/coloredpoints.vtp)

add_test(${KIT}-ConvexHull ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestConvexHull ${DATA}/cowHead.vtp)

if(NOT ${VTK_VERSION} VERSION_LESS "6")
  add_test(${KIT}-Curvatures ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestCurvatures ${DATA}/cowHead.vtp -20 20)
endif()

add_test(${KIT}-DijkstraGraphGeodesicPath ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestDijkstraGraphGeodesicPath	-E 20)

add_test(${KIT}-EmbedPointsIntoVolume ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestEmbedPointsIntoVolume ${DATA}/Bunny.vtp )

add_test(${KIT}-ExternalContour ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestExternalContour ${DATA}/Bunny.vtp -E 80 )

add_test(${KIT}-DetermineArrayDataTypes ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestDetermineArrayDataTypes ${DATA}/foilledContours.vtp)

add_test(${KIT}-GetMiscCellData ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestGetMiscCellData ${DATA}/SuperQuadric.vtp Nromals)

add_test(${KIT}-GetMiscPointData ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestGetMiscPointData ${DATA}/cowHead.vtp Gauss_Curvature)

add_test(${KIT}-GradientFilter ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestGradientFilter ${DATA}/uGridEx.vtk)

add_test(${KIT}-GreedyTerrainDecimation ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestGreedyTerrainDecimation -E 55)

add_test(${KIT}-HighlightBadCells ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestHighlightBadCells -E 20)

add_test(${KIT}-ImplicitModeller ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestImplicitModeller ${DATA}/Bunny.vtp)

add_test(${KIT}-MiscPointData ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestMiscPointData ${DATA}/cowHead.vtp)

add_test(${KIT}-PointLocatorVisualization ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestPointLocatorVisualization -E 50)

add_test(${KIT}-PolyDataIsoLines ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestPolyDataIsoLines ${DATA}/cowHead.vtp)

add_test(${KIT}-PolyDataPointSampler ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestPolyDataPointSampler ${DATA}/Torso.vtp)

add_test(${KIT}-RemoveVertices ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestRemoveVertices ${DATA}/Bunny.vtp)

add_test(${KIT}-Silhouette ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestSilhouette ${DATA}/cowHead.vtp)

add_test(${KIT}-ShrinkPolyData ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestShrinkPolyData ${DATA}/cowHead.vtp -E 30)

add_test(${KIT}-ThinPlateSplineTransform ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestThinPlateSplineTransform ${DATA}/masonry.bmp)

add_test(${KIT}-TriangleColoredPoints ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestTriangleColoredPoints -E 15)

add_test(${KIT}-TriangleSolidColor ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestTriangleSolidColor -E 25)

add_test(${KIT}-WarpSurface ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestWarpSurface ${DATA}/cowHead.vtp .1)

include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)

endif()
