project (${WIKI}VisualizationAlgorithms)

if(NOT VTK_BINARY_DIR)
  set(VTK_LIBRARIES "")
  find_package(VTK COMPONENTS
    vtkCommonColor
    vtkCommonComputationalGeometry
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonMath
    vtkCommonTransforms
    vtkFiltersCore
    vtkFiltersExtraction
    vtkFiltersFlowPaths
    vtkFiltersGeneral
    vtkFiltersGeneric
    vtkFiltersGeometry
    vtkFiltersHybrid
    vtkFiltersModeling
    vtkFiltersSources
    vtkFiltersTexture
    vtkIOGeometry
    vtkIOImage
    vtkIOImport
    vtkIOLegacy
    vtkIOParallel
    vtkIOXML
    vtkImagingColor
    vtkImagingCore
    vtkImagingGeneral
    vtkImagingHybrid
    vtkInteractionImage
    vtkInteractionStyle
    vtkInteractionWidgets
    vtkRenderingAnnotation
    vtkRenderingCore
    vtkRenderingFreeType
    vtkRenderingLOD
    vtkRenderingOpenGL2
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

Requires_GitLfs(PineRootConnectivity ALL_FILES)
Requires_GitLfs(PineRootConnectivityA ALL_FILES)
Requires_GitLfs(PineRootDecimation ALL_FILES)
Requires_GitLfs(DecimateHawaii ALL_FILES)

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
  set(KIT VisualizationAlgorithms)
  set(NEEDS_ARGS
    AnatomicalOrientation
    BluntStreamlines
    CarotidFlow
    CarotidFlowGlyphs
    ColorIsosurface
    CombustorIsosurface
    CreateBFont
    CutStructuredGrid
    CutWithCutFunction
    CutWithScalars
    DecimateFran
    DecimateHawaii
    DisplacementPlot
    FilledContours
    FindCellIntersections
    FireFlow
    FireFlowDemo
    FlyingHeadSlice
    HeadBone
    HeadSlice
    Hello
    ImageGradient
    IronIsoSurface
    LOx
    LOxGrid
    LOxSeeds
    Motor
    MarchingCases
    MarchingCasesA
    MarchingCasesB
    MarchingCasesC
    MarchingCasesD
    PineRootConnectivity
    PineRootConnectivityA
    PineRootDecimation
    PlateVibration
    ProbeCombustor
    Office
    OfficeA
    OfficeTube
    SpikeFran
    SplatFace
    Stocks
    StreamlinesWithLineWidget
    VelocityProfile
    WarpCombustor
    )
  set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)

  add_test(${KIT}-AnatomicalOrientation ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestAnatomicalOrientation ${DATA}/Human.vtp)

  add_test(${KIT}-BluntStreamlines ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestBluntStreamlines ${DATA}/bluntfinxyz.bin ${DATA}/bluntfinq.bin)

  add_test(${KIT}-CarotidFlow ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestCarotidFlow ${DATA}/carotid.vtk -E 50)

  add_test(${KIT}-CarotidFlowGlyphs ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestCarotidFlowGlyphs ${DATA}/carotid.vtk -E 50)

  add_test(${KIT}-ColorIsosurface ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestColorIsosurface ${DATA}/combxyz.bin ${DATA}/combq.bin)

  add_test(${KIT}-CombustorIsosurface ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestCombustorIsosurface ${DATA}/combxyz.bin ${DATA}/combq.bin)

  add_test(${KIT}-CreateBFont ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestCreateBFont ${DATA}/B.pgm)

  add_test(${KIT}-CutStructuredGrid ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestCutStructuredGrid ${DATA}/combxyz.bin ${DATA}/combq.bin)

  add_test(${KIT}-CutWithCutFunction ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestCutWithCutFunction ${DATA}/Torso.vtp 20)

  add_test(${KIT}-CutWithScalars ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestCutWithScalars ${DATA}/Torso.vtp 20)

  add_test(${KIT}-DecimateFran ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestDecimateFran ${DATA}/fran_cut.vtk ${DATA}/fran_cut.png)

  add_test(${KIT}-DisplacementPlot ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestDisplacementPlot ${DATA}/plate.vtk)

  add_test(${KIT}-FilledContours ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestFilledContours ${DATA}/filledContours.vtp 10)

  add_test(${KIT}-FindCellIntersections ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestFindCellIntersections ${DATA}/Disc_BiQuadraticQuads_0_0.vtu)

  add_test(${KIT}-FireFlow ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestFireFlow ${DATA}/room_vis.wrl ${DATA}/fire_ug.vtu)

  add_test(${KIT}-FireFlowDemo ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestFireFlowDemo ${DATA}/room_vis.wrl ${DATA}/fire_ug.vtu)

  add_test(${KIT}-FlyingHeadSlice ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestFlyingHeadSlice ${DATA}/FullHead.mhd)

  add_test(${KIT}-HeadBone ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestHeadBone ${DATA}/FullHead.mhd)

  add_test(${KIT}-HeadSlice ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestHeadSlice ${DATA}/FullHead.mhd)

  add_test(${KIT}-Hello ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestHello ${DATA}/hello.vtk)

  add_test(${KIT}-ImageGradient ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestImageGradient ${DATA}/FullHead.mhd)

  add_test(${KIT}-IronIsoSurface ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestIronIsoSurface ${DATA}/ironProt.vtk)

  add_test(${KIT}-LOx ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestLOx ${DATA}/postxyz.bin ${DATA}/postq.bin)

  add_test(${KIT}-LOxGrid ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestLOxGrid ${DATA}/postxyz.bin ${DATA}/postq.bin)

  add_test(${KIT}-LOxSeeds ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestLOxSeeds ${DATA}/postxyz.bin ${DATA}/postq.bin)

  add_test(${KIT}-MarchingCases ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestMarchingCases 1 7)

  add_test(${KIT}-MarchingCasesA ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestMarchingCasesA 15 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14)

  add_test(${KIT}-MarchingCasesB ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestMarchingCasesB 6 -3 -6 -7 -10 -12 -13)

  add_test(${KIT}-MarchingCasesC ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestMarchingCasesC 1 3 1 0)

  add_test(${KIT}-MarchingCasesD ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestMarchingCasesD 1 7 2 0)

  add_test(${KIT}-Motor ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestMotor ${DATA}/texThres2.vtk ${DATA}/motor.g)

  add_test(${KIT}-PlateVibration ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestPlateVibration ${DATA}/plate.vtk -E 30)

  add_test(${KIT}-ProbeCombustor ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestProbeCombustor ${DATA}/combxyz.bin ${DATA}/combq.bin -E 50)

  add_test(${KIT}-Office ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestOffice ${DATA}/office.binary.vtk 3 -E 80)

  add_test(${KIT}-OfficeA ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestOfficeA ${DATA}/office.binary.vtk 0 -E 50)

  add_test(${KIT}-OfficeTube ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestOfficeTube ${DATA}/office.binary.vtk)

  add_test(${KIT}-SpikeFran ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestSpikeFran ${DATA}/fran_cut.vtk)

  add_test(${KIT}-SplatFace ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestSplatFace ${DATA}/fran_cut.vtk -E 50)

  add_test(${KIT}-Stocks ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestStocks ${DATA}/GE.vtk ${DATA}/GM.vtk ${DATA}/IBM.vtk ${DATA}/DEC.vtk 0)

  add_test(${KIT}-StreamlinesWithLineWidget ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestStreamlinesWithLineWidget ${DATA}/combxyz.bin ${DATA}/combq.bin 10 1 -E 20)

  add_test(${KIT}-VelocityProfile ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestVelocityProfile ${DATA}/combxyz.bin ${DATA}/combq.bin)

  add_test(${KIT}-WarpCombustor ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestWarpCombustor ${DATA}/combxyz.bin ${DATA}/combq.bin)

  if(GIT_LFS)
    add_test(${KIT}-DecimateHawaii ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
      TestDecimateHawaii ${DATA}/honolulu.vtk -E 50)

    add_test(${KIT}-PineRootConnectivity ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
      TestPineRootConnectivity ${DATA}/pine_root.tri -E 20)

    add_test(${KIT}-PineRootConnectivityA ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
      TestPineRootConnectivityA ${DATA}/pine_root.tri 1 -E 20)

    add_test(${KIT}-PineRootDecimation ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
      TestPineRootDecimation ${DATA}/pine_root.tri -E 20)
  endif()

  include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
endif()
