PROJECT (${WIKI}Medical)

IF(NOT WikiExamples_BINARY_DIR)
FIND_PACKAGE(VTK REQUIRED)
IF(NOT VTK_USE_RENDERING)
  MESSAGE(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
ENDIF(NOT VTK_USE_RENDERING)
INCLUDE(${VTK_USE_FILE})
ENDIF(NOT WikiExamples_BINARY_DIR)

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  SET(KIT_LIBS vtkFiltering vtkHybrid vtkVolumeRendering)
else()
  SET(KIT_LIBS ${VTK_LIBRARIES})
endif()
#
# Build all .cxx files in the directory
FILE(GLOB ALL_FILES *.cxx)
foreach(SOURCE_FILE ${ALL_FILES})
  STRING(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  STRING(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  ADD_EXECUTABLE(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  TARGET_LINK_LIBRARIES(${WIKI}${EXAMPLE} ${KIT_LIBS})
endforeach(SOURCE_FILE)

if (BUILD_TESTING)
# Testing
SET(KIT Medical)
SET(NEEDS_ARGS
  GenerateCubesFromLabels
  GenerateModelsFromLabels
  MedicalDemo1
  MedicalDemo2
  MedicalDemo3
  MedicalDemo4
  TissueLens
)
SET(DATA ${WikiExamples_SOURCE_DIR}/Testing/Data)

ADD_TEST(${KIT}-GenerateCubesFromLabels ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestGenerateCubesFromLabels ${DATA}/frogtissue.mhd 1 29)

ADD_TEST(${KIT}-GenerateModelsFromLabels ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestGenerateModelsFromLabels ${DATA}/frogtissue.mhd 1 29)

ADD_TEST(${KIT}-MedicalDemo1 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestMedicalDemo1 ${DATA}/FullHead.mhd)

ADD_TEST(${KIT}-MedicalDemo2 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestMedicalDemo2 ${DATA}/FullHead.mhd)

ADD_TEST(${KIT}-MedicalDemo3 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestMedicalDemo3 ${DATA}/FullHead.mhd -E 30)

ADD_TEST(${KIT}-MedicalDemo4 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestMedicalDemo4 ${DATA}/FullHead.mhd)

ADD_TEST(${KIT}-TissueLens ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestTissueLens ${DATA}/FullHead.mhd)

INCLUDE(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)

endif()
