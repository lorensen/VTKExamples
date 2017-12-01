project (${WIKI}Modelling)

if(NOT WikiExamples_BINARY_DIR)
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
endif()

set(KIT_LIBS ${VTK_LIBRARIES})

#
# Build all .cxx files in the directory
file(GLOB ALL_FILES *.cxx)

include(${WikiExamples_SOURCE_DIR}/CMake/RequiresGitLfs.cmake)

Requires_GitLfs(ExtractLargestIsosurface ALL_FILES)

foreach(SOURCE_FILE ${ALL_FILES})
  string(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  add_executable(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  target_link_libraries(${WIKI}${EXAMPLE} ${KIT_LIBS})
endforeach()

if (BUILD_TESTING)
# Testing
set(KIT Modelling)
set(NEEDS_ARGS
  ContourTriangulator
  Delaunay3D
  Delaunay3DDemo
  ExtractLargestIsosurface
  Finance
  MarchingSquares
)

set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)
set(TEMP ${WikiExamples_BINARY_DIR}/Testing/Temporary)

add_test(${KIT}-Delaunay3D ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestDelaunay3D ${DATA}/Bunny.vtp)

add_test(${KIT}-Delaunay3DDemo ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestDelaunay3DDemo ${DATA}/Bunny.vtp)

add_test(${KIT}-MarchingSquares ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestMarchingSquares ${DATA}/fullhead15.png 500)

add_test(${KIT}-Finance ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestFinance ${DATA}/financial.txt)

add_test(${KIT}-ContourTriangulator ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestContourTriangulator ${DATA}/fullhead15.png 500)

if(GIT_LFS)
  add_test(${KIT}-ExtractLargestIsosurface ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestExtractLargestIsosurface ${DATA}/brain.vtk 50 1)
endif()

include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
endif()
