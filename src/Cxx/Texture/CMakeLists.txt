project (${WIKI}Texture)

if(NOT WikiExamples_BINARY_DIR)
find_package(VTK REQUIRED)
  include(${VTK_USE_FILE})
endif()

set(KIT_LIBS ${VTK_LIBRARIES})

#
# Build all .cxx files in the directory
file(GLOB ALL_FILES *.cxx)

include(${WikiExamples_SOURCE_DIR}/CMake/RequiresVersion.cmake)
include(${WikiExamples_SOURCE_DIR}/CMake/RequiresGitLfs.cmake)
Requires_GitLfs(TextureThreshold ALL_FILES)

foreach(SOURCE_FILE ${ALL_FILES})
  string(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  add_executable(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  target_link_libraries(${WIKI}${EXAMPLE} ${KIT_LIBS})
endforeach()

if (BUILD_TESTING)
# Testing
set(KIT Texture)
set(NEEDS_ARGS
  ProjectedTexture
  TextureCutSphere
  TexturedSphere
  TextureThreshold
)

set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)
set(TEMP ${WikiExamples_BINARY_DIR}/Testing/Temporary)

add_test(${KIT}-ProjectedTexture ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestProjectedTexture ${DATA}/fran_cut.vtk ${DATA}/fran_cut.png)

add_test(${KIT}-TextureCutSphere ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestTextureCutSphere ${DATA}/texThres.vtk)

add_test(${KIT}-TexturedSphere ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestTexturedSphere ${DATA}/earth.ppm)

message(STATUS "GIT_LFS ${GIT_LFS}")
if(GIT_LFS)
  add_test(${KIT}-TextureThreshold ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestTextureThreshold ${DATA}/bluntfinxyz.bin ${DATA}/bluntfinq.bin ${DATA}/texThres2.vtk)
endif()

include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
endif()
