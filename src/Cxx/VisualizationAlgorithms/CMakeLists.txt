PROJECT (${WIKI}VisualizationAlgorithms)

IF(NOT WikiExamples_BINARY_DIR)
FIND_PACKAGE(VTK REQUIRED)
IF(NOT VTK_USE_RENDERING)
  MESSAGE(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
ENDIF(NOT VTK_USE_RENDERING)
INCLUDE(${VTK_USE_FILE})
ENDIF(NOT WikiExamples_BINARY_DIR)

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  SET(KIT_LIBS vtkRendering vtkHybrid)
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
SET(KIT VisualizationAlgorithms)
SET(NEEDS_ARGS
  BluntStreamlines
  CombustorIsosurface
  CreateBFont
  CutWithCutFunction
  CutWithScalars
  DisplacementPlot
  FilledContours
  FindCellIntersections
  Hello
  LOx
  MarchingCases
  MarchingCasesA
  MarchingCasesB
  PlateVibration
  WarpCombustor
)
SET(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)

ADD_TEST(${KIT}-BluntStreamlines ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestBluntStreamlines ${DATA}/bluntfinxyz.bin ${DATA}/bluntfinq.bin)

ADD_TEST(${KIT}-CombustorIsosurface ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestCombustorIsosurface ${DATA}/combxyz.bin ${DATA}/combq.bin)

ADD_TEST(${KIT}-CreateBFont ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestCreateBFont ${DATA}/B.pgm)

ADD_TEST(${KIT}-CutWithCutFunction ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestCutWithCutFunction ${DATA}/Torso.vtp 20)

ADD_TEST(${KIT}-CutWithScalars ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestCutWithScalars ${DATA}/Torso.vtp 20)

ADD_TEST(${KIT}-DisplacementPlot ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestDisplacementPlot ${DATA}/plate.vtk)

ADD_TEST(${KIT}-FilledContours ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestFilledContours ${DATA}/filledContours.vtp 10)

ADD_TEST(${KIT}-FindCellIntersections ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestFindCellIntersections ${DATA}/Disc_BiQuadraticQuads_0_0.vtu)

ADD_TEST(${KIT}-Hello ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestHello ${DATA}/hello.vtk)

ADD_TEST(${KIT}-LOx ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestLOx ${DATA}/postxyz.bin ${DATA}/postq.bin)

ADD_TEST(${KIT}-MarchingCases ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestMarchingCases 7)

ADD_TEST(${KIT}-MarchingCasesA ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestMarchingCasesA 1 2 3 4 5 6 7 8 9 10 11 12 13 14)

ADD_TEST(${KIT}-MarchingCasesB ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestMarchingCasesB -3 -6 -7 -10 -12 -13)

ADD_TEST(${KIT}-PlateVibration ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestPlateVibration ${DATA}/plate.vtk)

ADD_TEST(${KIT}-WarpCombustor ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestWarpCombustor ${DATA}/combxyz.bin ${DATA}/combq.bin)

INCLUDE(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
endif()
