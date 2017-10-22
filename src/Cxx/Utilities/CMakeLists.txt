project (${WIKI}Utilities)

if(NOT WikiExamples_BINARY_DIR)
find_package(VTK REQUIRED)
if(NOT VTK_USE_RENDERING)
  message(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
endif(NOT VTK_USE_RENDERING)
include(${VTK_USE_FILE})
endif(NOT WikiExamples_BINARY_DIR)

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  set(KIT_LIBS vtkRendering vtkHybrid vtkInfovis)
else()
  set(KIT_LIBS ${VTK_LIBRARIES})
endif()
#
# Build all .cxx files in the directory
file(GLOB ALL_FILES *.cxx)

include(${WikiExamples_SOURCE_DIR}/CMake/RequiresSettingOn.cmake)
Requires_Setting_On (GetDataRoot BUILD_TESTING)

include(${WikiExamples_SOURCE_DIR}/CMake/RequiresVersion.cmake)
Requires_Version(LUTUtilities "6.0.0" ALL_FILES)

foreach(SOURCE_FILE ${ALL_FILES})
  string(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  add_executable(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  target_link_libraries(${WIKI}${EXAMPLE} ${KIT_LIBS})
endforeach(SOURCE_FILE)

if (BUILD_TESTING)
# Testing
set(KIT Utilities)
set(NEEDS_ARGS
  SaveSceneToFieldData
  SaveSceneToFile
  ViewportBorders
  ZBuffer
)
set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)
set(TEMP ${WikiExamples_BINARY_DIR}/Testing/Temporary)

add_test(${KIT}-SaveSceneToFile ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestSaveSceneToFile ${DATA}/Armadillo.ply ${TEMP}/Armadillo.txt)

add_test(${KIT}-SaveSceneToFieldData ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestSaveSceneToFieldData ${DATA}/Armadillo.ply)

add_test(${KIT}-ViewportBorders ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestViewportBorders ${DATA}/v.vtk ${DATA}/t.vtk ${DATA}/k.vtk)

add_test(${KIT}-ZBuffer ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestZBuffer ${DATA}/Bunny.vtp ${TEMP}/ZBuffer.bmp)

include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)

endif()
