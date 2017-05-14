PROJECT (${WIKI}Points)

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

foreach(SOURCE_FILE ${ALL_FILES})
  STRING(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  STRING(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  ADD_EXECUTABLE(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  TARGET_LINK_LIBRARIES(${WIKI}${EXAMPLE} ${KIT_LIBS})
endforeach(SOURCE_FILE)

if (BUILD_TESTING)
# Testing
SET(KIT Points)
SET(NEEDS_ARGS
  ExtractSurface
  ExtractSurfaceDemo
  DensifyPoints
  MaskPointsFilter
  PointOccupancy
  RadiusOutlierRemoval
  SignedDistance
  UnsignedDistance
)
SET(DATA ${WikiExamples_SOURCE_DIR}/Testing/Data)

if (vtkFiltersPoints_LOADED)
   ADD_TEST(${KIT}-ExtractSurface ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
     TestExtractSurface ${DATA}/Armadillo.ply)
   ADD_TEST(${KIT}-ExtractSurfaceDemo ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
     TestExtractSurfaceDemo ${DATA}/Armadillo.ply)
   ADD_TEST(${KIT}-DensifyPoints ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
     TestDensifyPoints ${DATA}/Torso.vtp)
   ADD_TEST(${KIT}-MaskPointsFilter ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
     TestMaskPointsFilter ${DATA}/FullHead.mhd)
   ADD_TEST(${KIT}-PointOccupancy ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
     TestPointOccupancy ${DATA}/cowHead.vtp)
   ADD_TEST(${KIT}-RadiusOutlierRemoval ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
     TestRadiusOutlierRemoval ${DATA}/cowHead.vtp)
   ADD_TEST(${KIT}-SignedDistance ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
     TestSignedDistance ${DATA}/Armadillo.ply)
   ADD_TEST(${KIT}-UnsignedDistance ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
     TestUnsignedDistance ${DATA}/Armadillo.ply)
endif()

INCLUDE(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
endif()
