project (${WIKI}Medical)

if(NOT WikiExamples_BINARY_DIR)
find_package(VTK REQUIRED)
if(NOT VTK_USE_RENDERING)
  message(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
endif()
include(${VTK_USE_FILE})
endif()

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  set(KIT_LIBS vtkFiltering vtkHybrid vtkVolumeRendering)
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
set(KIT Medical)
set(NEEDS_ARGS
  GenerateCubesFromLabels
  GenerateModelsFromLabels
  MedicalDemo1
  MedicalDemo2
  MedicalDemo3
  MedicalDemo4
  TissueLens
)
set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)

add_test(${KIT}-GenerateCubesFromLabels ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestGenerateCubesFromLabels ${DATA}/frogtissue.mhd 1 29)

add_test(${KIT}-GenerateModelsFromLabels ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestGenerateModelsFromLabels ${DATA}/frogtissue.mhd 1 29)

add_test(${KIT}-MedicalDemo1 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestMedicalDemo1 ${DATA}/FullHead.mhd)

add_test(${KIT}-MedicalDemo2 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestMedicalDemo2 ${DATA}/FullHead.mhd)

add_test(${KIT}-MedicalDemo3 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestMedicalDemo3 ${DATA}/FullHead.mhd -E 30)

add_test(${KIT}-MedicalDemo4 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestMedicalDemo4 ${DATA}/FullHead.mhd)

add_test(${KIT}-TissueLens ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestTissueLens ${DATA}/FullHead.mhd)

include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)

endif()
