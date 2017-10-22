project (${WIKI}GeometricObjects)

if(NOT WikiExamples_BINARY_DIR)
find_package(VTK REQUIRED)
if(NOT VTK_USE_RENDERING)
  message(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
endif()
include(${VTK_USE_FILE})
endif()

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  set(KIT_LIBS vtkRendering vtkHybrid vtkWidgets)
else()
  set(KIT_LIBS ${VTK_LIBRARIES})
endif()
#
# Build all .cxx files in the directory
file(GLOB ALL_FILES *.cxx)

include(${WikiExamples_SOURCE_DIR}/CMake/RequiresVersion.cmake)
set(VERSION_MIN "7.0")
Requires_Version(ParametricKuenDemo ${VERSION_MIN} ALL_FILES)
Requires_Version(ParametricObjectsDemo2 ${VERSION_MIN} ALL_FILES)

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
