project (${WIKI}Filtering)

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
include(${WikiExamples_SOURCE_DIR}/CMake/RequiresSettingOn.cmake)

set(VERSION_MIN "6.0")
Requires_Version(GenericClip ${VERSION_MIN} ALL_FILES)
Requires_Setting_On (GenericClip BUILD_TESTING)


foreach(SOURCE_FILE ${ALL_FILES})
  string(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  add_executable(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  target_link_libraries(${WIKI}${EXAMPLE} ${KIT_LIBS})
endforeach()

if (BUILD_TESTING)
# Testing
set(KIT Filtering)
set(NEEDS_ARGS
  ConstrainedDelaunay2D
  ContoursFromPolyData
  ConstrainedDelaunay2D
  ICPRealData
  SurfaceFromUnorganizedPoints
)

set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)
add_test(${KIT}-ConstrainedDelaunay2D ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestConstrainedDelaunay2D -E 30)

add_test(${KIT}-Delaunay2D ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestDelaunay2D -E 30)

add_test(${KIT}-SurfaceFromUnorganizedPoints ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestSurfaceFromUnorganizedPoints ${DATA}/Bunny.vtp -E 30)

add_test(${KIT}-ContoursFromPolyData ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestContoursFromPolyData ${DATA}/Bunny.vtp  -E 30)
include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)

endif()
