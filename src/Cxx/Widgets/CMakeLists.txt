project (${WIKI}Widgets)

if(NOT WikiExamples_BINARY_DIR)
find_package(VTK REQUIRED)
if(NOT VTK_USE_RENDERING)
  message(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
endif()
include(${VTK_USE_FILE})
endif()

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 6.0)
  set(KIT_LIBS vtkHybrid vtkWidgets)
else()
  set(KIT_LIBS ${VTK_LIBRARIES})
endif()
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
set(KIT Widgets)

set(NEEDS_ARGS
  CheckerboardWidget
  OrientationMarkerWidget
  Slicer2D
  RectilinearWipeWidget
)

set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)
add_test(${KIT}-OrientationMarkerWidget ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestOrientationMarkerWidget ${DATA}/Bunny.vtp)

add_test(${KIT}-RectilinearWipeWidget ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestRectilinearWipeWidget ${DATA}/Gourds2.jpg ${DATA}/Ox.jpg)

add_test(${KIT}-CheckerboardWidget ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestCheckerboardWidget ${DATA}/Gourds2.jpg ${DATA}/Ox.jpg)

add_test(${KIT}-Slider2D ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestSlider2D -E 25)
include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)

endif()
