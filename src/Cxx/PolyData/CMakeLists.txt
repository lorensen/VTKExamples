project (${WIKI}PolyData)

if(NOT VTK_BINARY_DIR)
  set(VTK_LIBRARIES "")
  find_package(VTK COMPONENTS
    vtkCommonColor
    vtkCommonComputationalGeometry
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonExecutionModel
    vtkCommonTransforms
    vtkFiltersCore
    vtkFiltersExtraction
    vtkFiltersGeneral
    vtkFiltersGeometry
    vtkFiltersHybrid
    vtkFiltersModeling
    vtkFiltersSources
    vtkFiltersVerdict
    vtkIOGeometry
    vtkIOImage
    vtkIOLegacy
    vtkIOPLY
    vtkIOXML
    vtkImagingCore
    vtkImagingHybrid
    vtkImagingSources
    vtkImagingStencil
    vtkInteractionStyle
    vtkInteractionWidgets
    vtkRenderingAnnotation
    vtkRenderingCore
    vtkRenderingFreeType
    vtkRenderingGL2PSOpenGL2
    vtkRenderingLOD
    vtkRenderingOpenGL2
    OPTIONAL_COMPONENTS
    #    vtkFiltersParallelStatistics
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

Requires_Version(Curvatures "6.0.0" ALL_FILES)
Requires_Version(AlignTwoPolyDatas "8.2" ALL_FILES)

foreach(SOURCE_FILE ${ALL_FILES})
  string(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  add_executable(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  target_link_libraries(${WIKI}${EXAMPLE} ${KIT_LIBS})
  if (VTK_VERSION VERSION_GREATER "8.8")
    vtk_module_autoinit(
      TARGETS ${WIKI}${EXAMPLE}
      MODULES ${VTK_LIBRARIES}
      )
  endif()
endforeach()

if (BUILD_TESTING)
  # Testing
  set(KIT PolyData)
  set(NEEDS_ARGS
    AlignTwoPolyDatas
    BooleanOperationPolyDataFilter
    CellCentersDemo
    CellLocatorVisualization
    CellsInsideObject
    ColorDisconnectedRegionsDemo
    ColoredPoints
    ConvexHull
    Curvatures
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
    LoopBooleanPolyDataFilter
    MiscPointData
    PointLocatorVisualization
    PolyDataIsoLines
    PolyDataPointSampler
    PolyDataToImageData
    RemoveVertices
    ShrinkPolyData
    Silhouette
    ThinPlateSplineTransform
    TriangleColoredPoints
    TriangleSolidColor
    WarpSurface
    )

  set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)
  set(TEMP ${WikiExamples_BINARY_DIR}/Testing/Temporary)

  add_test(${KIT}-AlignTwoPolyDatas ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestAlignTwoPolyDatas ${DATA}/thingiverse/Grey_Nurse_Shark.stl ${DATA}/shark.ply)

  add_test(${KIT}-BooleanOperationPolyDataFilter ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestBooleanOperationPolyDataFilter ${DATA}/Torso.vtp difference ${DATA}/ObliqueCone.vtp)

  add_test(${KIT}-LoopBooleanPolyDataFilter ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestLoopBooleanPolyDataFilter ${DATA}/Torso.vtp difference ${DATA}/ObliqueCone.vtp)

  add_test(${KIT}-CellCentersDemo ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestCellCentersDemo ${DATA}/cow.g)

  add_test(${KIT}-CellLocatorVisualization ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestCellLocatorVisualization -E 50)

  add_test(${KIT}-CellsInsideObject ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestCellsInsideObject ${DATA}/cow.g)

  add_test(${KIT}-ColorDisconnectedRegionsDemo ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestColorDisconnectedRegionsDemo ${DATA}/gears.stl)

  add_test(${KIT}-ColoredPoints ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestColoredPoints ${TEMP}/coloredpoints.vtp)

  add_test(${KIT}-ConvexHull ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestConvexHull ${DATA}/cowHead.vtp)

  add_test(${KIT}-Curvatures ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestCurvatures ${DATA}/cowHead.vtp -20 20)

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

  add_test(${KIT}-PolyDataToImageData ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestPolyDataToImageData ${DATA}/Torso.vtp)

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
