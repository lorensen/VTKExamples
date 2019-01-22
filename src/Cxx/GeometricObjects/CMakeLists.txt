project (${WIKI}GeometricObjects)

if(NOT WikiExamples_BINARY_DIR)
  find_package(VTK REQUIRED)
  include(${VTK_USE_FILE})
endif()

set(KIT_LIBS ${VTK_LIBRARIES})

#
# Build all .cxx files in the directory
file(GLOB ALL_FILES *.cxx)

# VTK follows the C++03 standard but some examples require C++11
include(${WikiExamples_SOURCE_DIR}/CMake/RequiresCxxVersion.cmake)
Requires_CxxVersion(Cell3DDemonstration 11 ALL_FILES)
Requires_CxxVersion(GeometricObjectsDemo 11 ALL_FILES)
Requires_CxxVersion(Hexahedron 11 ALL_FILES)
Requires_CxxVersion(IsoparametricCellsDemo 11 ALL_FILES)
Requires_CxxVersion(OrientedArrow 11 ALL_FILES)
Requires_CxxVersion(OrientedCylinder 11 ALL_FILES)
Requires_CxxVersion(ParametricKuenDemo 11 ALL_FILES)
Requires_CxxVersion(ParametricObjects 11 ALL_FILES)
Requires_CxxVersion(ParametricObjectsDemo2 11 ALL_FILES)
Requires_CxxVersion(ParametricObjectsDemo 11 ALL_FILES)
Requires_CxxVersion(ParametricSuperEllipsoidDemo 11 ALL_FILES)
Requires_CxxVersion(ParametricSuperToroidDemo 11 ALL_FILES)
Requires_CxxVersion(Plane 11 ALL_FILES)
Requires_CxxVersion(PolyLine1 11 ALL_FILES)
Requires_CxxVersion(SourceObjectsDemo 11 ALL_FILES)

include(${WikiExamples_SOURCE_DIR}/CMake/RequiresVersion.cmake)
set(VERSION_MIN "7.0")
Requires_Version(ParametricKuenDemo ${VERSION_MIN} ALL_FILES)
Requires_Version(ParametricObjectsDemo2 ${VERSION_MIN} ALL_FILES)
Requires_Module(OpenVRCone vtkRenderingOpenVR)
Requires_Module(OpenVRCube vtkRenderingOpenVR)
Requires_Module(OpenVRCylinder vtkRenderingOpenVR)
Requires_Module(OpenVRFrustm vtkRenderingOpenVR)
Requires_Module(OpenVROrientedArrow vtkRenderingOpenVR)
Requires_Module(OpenVROrientedCylinder vtkRenderingOpenVR)
Requires_Module(OpenVRSphere vtkRenderingOpenVR)
Requires_Module(OpenVRTessellatedBoxSource vtkRenderingOpenVR)

Requires_Version(QuadraticHexahedronDemo "7.1.0" ALL_FILES)
Requires_Version(QuadraticTetraDemo "7.1.0" ALL_FILES)
Requires_Version(CellTypeSource "8.0.0" ALL_FILES)

foreach(SOURCE_FILE ${ALL_FILES})
  string(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  add_executable(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  target_link_libraries(${WIKI}${EXAMPLE} ${KIT_LIBS})
endforeach()

if (BUILD_TESTING)
# Testing
set(KIT GeometricObjects)
set(NEEDS_ARGS
    QuadraticHexahedron
    TessellatedBoxSource
)

add_test(${KIT}-QuadraticHexahedron ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestQuadraticHexahedron -E 30)

add_test(${KIT}-TessellatedBoxSource ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestTessellatedBoxSource -E 30)

include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
endif()
