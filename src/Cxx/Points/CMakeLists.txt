project (${WIKI}Points)

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

set(VERSION_MIN "7.0")
Requires_Version(DensifyPoints ${VERSION_MIN} ALL_FILES)
Requires_Version(ExtractClusters ${VERSION_MIN} ALL_FILES)
Requires_Version(ExtractPointsDemo ${VERSION_MIN} ALL_FILES)
Requires_Version(ExtractSurface ${VERSION_MIN} ALL_FILES)
Requires_Version(ExtractSurfaceDemo ${VERSION_MIN} ALL_FILES)
Requires_Version(FitImplicitFunction ${VERSION_MIN} ALL_FILES)
Requires_Version(MaskPointsFilter ${VERSION_MIN} ALL_FILES)
Requires_Version(NormalEstimation ${VERSION_MIN} ALL_FILES)
Requires_Version(PointOccupancy ${VERSION_MIN} ALL_FILES)
Requires_Version(RadiusOutlierRemoval ${VERSION_MIN} ALL_FILES)
Requires_Version(SignedDistance ${VERSION_MIN} ALL_FILES)
Requires_Version(UnsignedDistance ${VERSION_MIN} ALL_FILES)
Requires_Module(PowercrustExtractSurface Powercrust)
Requires_Module(PoissonExtractSurface PoissonReconstruction)
Requires_Module(CompareExtractSurface Powercrust)
Requires_Module(CompareExtractSurface PoissonReconstruction)

foreach(SOURCE_FILE ${ALL_FILES})
  string(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  add_executable(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  target_link_libraries(${WIKI}${EXAMPLE} ${KIT_LIBS})
endforeach()

if (BUILD_TESTING)
# Testing
set(KIT Points)
set(NEEDS_ARGS
  CompareExtractSurface
  ExtractSurface
  ExtractSurfaceDemo
  DensifyPoints
  MaskPointsFilter
  PointOccupancy
  RadiusOutlierRemoval
  SignedDistance
  UnsignedDistance
)
set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)

if(Powercrust_LOADED AND PoissonReconstruction_LOADED)
  add_test(${KIT}-CompareExtractSurface ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
     TestCompareExtractSurface ${DATA}/horsePoints.vtp)
endif()

add_test(${KIT}-ExtractSurface ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
     TestExtractSurface ${DATA}/Armadillo.ply)
add_test(${KIT}-ExtractSurfaceDemo ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
     TestExtractSurfaceDemo ${DATA}/Armadillo.ply)
add_test(${KIT}-DensifyPoints ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
     TestDensifyPoints ${DATA}/Torso.vtp)
add_test(${KIT}-MaskPointsFilter ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
     TestMaskPointsFilter ${DATA}/FullHead.mhd)
add_test(${KIT}-PointOccupancy ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
     TestPointOccupancy ${DATA}/cowHead.vtp)
add_test(${KIT}-RadiusOutlierRemoval ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
     TestRadiusOutlierRemoval ${DATA}/cowHead.vtp)
add_test(${KIT}-SignedDistance ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
     TestSignedDistance ${DATA}/Armadillo.ply)
add_test(${KIT}-UnsignedDistance ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
     TestUnsignedDistance ${DATA}/Armadillo.ply)

include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
endif()
