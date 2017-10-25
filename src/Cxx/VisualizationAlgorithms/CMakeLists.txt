project (${WIKI}VisualizationAlgorithms)

if(NOT WikiExamples_BINARY_DIR)
  find_package(VTK REQUIRED)
  include(${VTK_USE_FILE})
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
endforeach()

if (BUILD_TESTING)
# Testing
set(KIT VisualizationAlgorithms)
set(NEEDS_ARGS
  BluntStreamlines
  CarotidFlow
  CombustorIsosurface
  CreateBFont
  CutStructuredGrid
  CutWithCutFunction
  CutWithScalars
  DisplacementPlot
  FilledContours
  FindCellIntersections
  HeadBone
  HeadSlice
  Hello
  IronIsoSurface
  LOx
  MarchingCases
  MarchingCasesA
  MarchingCasesB
  PlateVibration
  ProbeCombustor
  SpikeFran
  VelocityProfile
  WarpCombustor
)
set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)

add_test(${KIT}-BluntStreamlines ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestBluntStreamlines ${DATA}/bluntfinxyz.bin ${DATA}/bluntfinq.bin)

add_test(${KIT}-CarotidFlow ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestCarotidFlow ${DATA}/carotid.vtk)

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

add_test(${KIT}-DisplacementPlot ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestDisplacementPlot ${DATA}/plate.vtk)

add_test(${KIT}-FilledContours ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestFilledContours ${DATA}/filledContours.vtp 10)

add_test(${KIT}-FindCellIntersections ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestFindCellIntersections ${DATA}/Disc_BiQuadraticQuads_0_0.vtu)

add_test(${KIT}-HeadBone ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestHeadBone ${DATA}/FullHead.mhd)

add_test(${KIT}-HeadSlice ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestHeadSlice ${DATA}/FullHead.mhd)

add_test(${KIT}-Hello ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestHello ${DATA}/hello.vtk)

add_test(${KIT}-IronIsoSurface ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestIronIsoSurface ${DATA}/ironProt.vtk)

add_test(${KIT}-LOx ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestLOx ${DATA}/postxyz.bin ${DATA}/postq.bin)

add_test(${KIT}-MarchingCases ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestMarchingCases 7)

add_test(${KIT}-MarchingCasesA ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestMarchingCasesA 1 2 3 4 5 6 7 8 9 10 11 12 13 14)

add_test(${KIT}-MarchingCasesB ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestMarchingCasesB -3 -6 -7 -10 -12 -13)

add_test(${KIT}-PlateVibration ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestPlateVibration ${DATA}/plate.vtk)

add_test(${KIT}-ProbeCombustor ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestProbeCombustor ${DATA}/combxyz.bin ${DATA}/combq.bin)

add_test(${KIT}-SpikeFran ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestSpikeFran ${DATA}/fran_cut.vtk)

add_test(${KIT}-VelocityProfile ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestVelocityProfile ${DATA}/combxyz.bin ${DATA}/combq.bin)

add_test(${KIT}-WarpCombustor ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestWarpCombustor ${DATA}/combxyz.bin ${DATA}/combq.bin)

include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
endif()
