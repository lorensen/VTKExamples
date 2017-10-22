project (${WIKI}Meshes)

if(NOT WikiExamples_BINARY_DIR)
find_package(VTK REQUIRED)
if(NOT VTK_USE_RENDERING)
  message(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
endif()
include(${VTK_USE_FILE})
endif()

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  set(KIT_LIBS vtkRendering vtkHybrid)
else()
  set(KIT_LIBS ${VTK_LIBRARIES})
endif()

#
# Build all .cxx files in the directory
file(GLOB ALL_FILES *.cxx)

include(${WikiExamples_SOURCE_DIR}/CMake/RequiresVersion.cmake)
include(${WikiExamples_SOURCE_DIR}/CMake/RequiresModule.cmake)

set(VERSION_MIN "6.0")
Requires_Version(DeformPointSet ${VERSION_MIN} ALL_FILES)

foreach(SOURCE_FILE ${ALL_FILES})
  string(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  add_executable(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  target_link_libraries(${WIKI}${EXAMPLE} ${KIT_LIBS})
endforeach()

if (BUILD_TESTING)
# Testing
set(KIT Meshes)
set(NEEDS_ARGS
  ClipFrustum
  ClipDataSetWithPolyData
  Decimation
  FillHoles
  IdentifyHoles
  MatrixMathFilter
  OBBDicer
  QuadricClustering
  QuadricDecimation
  SplitPolyData
  TableBasedClipDataSetWithPolyData
)
set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)

add_test(${KIT}-ClipFrustum ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestClipFrustum ${DATA}/Armadillo.ply)

add_test(${KIT}-Decimation ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestDecimation ${DATA}/Torso.vtp)

add_test(${KIT}-QuadricDecimation ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestQuadricDecimation ${DATA}/Torso.vtp)

add_test(${KIT}-QuadricClustering ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestQuadricClustering ${DATA}/Torso.vtp)

add_test(${KIT}-ClipDataSetWithPolyData ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestClipDataSetWithPolyData -E 25)

add_test(${KIT}-FillHoles ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestFillHoles ${DATA}/Torso.vtp)

add_test(${KIT}-IdentifyHoles ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestIdentifyHoles ${DATA}/Torso.vtp)

add_test(${KIT}-OBBDicer ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestOBBDicer ${DATA}/Bunny.vtp)

add_test(${KIT}-MatrixMathFilter ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestMatrixMathFilter ${DATA}/tensors.vtk)

add_test(${KIT}-SplitPolyData ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestSplitPolyData ${DATA}/cowHead.vtp)

add_test(${KIT}-TableBasedClipDataSetWithPolyData ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestTableBasedClipDataSetWithPolyData -E 25)

include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
endif()
