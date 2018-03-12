project (${WIKI}Shaders)

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

# Testing
set(KIT Shaders)
set(NEEDS_ARGS
  ColorByNormal
  CubeMap
  SphereMap
)

set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)
add_test(${KIT}-ColorByNormal ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestColorByNormal ${DATA}/Armadillo.ply)

add_test(${KIT}-CubeMap ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestCubeMap ${DATA}/horse.ply ${DATA}/skybox-px.jpg ${DATA}/skybox-nx.jpg ${DATA}/skybox-py.jpg ${DATA}/skybox-ny.jpg ${DATA}/skybox-pz.jpg ${DATA}/skybox-nz.jpg)

add_test(${KIT}-SphereMap ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestSphereMap ${DATA}/Bunny.vtp ${DATA}/wintersun.jpg)


include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
