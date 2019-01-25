project (${WIKI}Medical)

if(NOT VTK_BINARY_DIR)
  set(VTK_LIBRARIES "")
  find_package(VTK COMPONENTS
    vtkCommonColor
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonTransforms
    vtkFiltersCore
    vtkFiltersGeneral
    vtkFiltersGeometry
    vtkFiltersModeling
    vtkFiltersSources
    vtkIOImage
    vtkIOXML
    vtkImagingCore
    vtkImagingStatistics
    vtkInteractionStyle
    vtkRenderingCore
    vtkRenderingFreeType
    vtkRenderingOpenGL2
    vtkRenderingVolume
    vtkRenderingVolumeOpenGL2
    OPTIONAL_COMPONENTS
    vtkTestingRendering
    QUIET
    )
  if (VTK_VERSION VERSION_LESS "8.90.0")
    include(${VTK_USE_FILE})
  endif()
endif()

set(KIT_LIBS ${VTK_LIBRARIES})

#
# Build all .cxx files in the directory
file(GLOB ALL_FILES *.cxx)

Requires_GitLfs(GenerateModelsFromLabels ALL_FILES)
Requires_GitLfs(GenerateCubesFromLabels ALL_FILES)

foreach(SOURCE_FILE ${ALL_FILES})
  string(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  add_executable(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  target_link_libraries(${WIKI}${EXAMPLE} ${KIT_LIBS})
  if (NOT VTK_VERSION VERSION_LESS "8.90.0")
    vtk_module_autoinit(
      TARGETS ${WIKI}${EXAMPLE}
      MODULES ${VTK_LIBRARIES}
      )
  endif()
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

  if(GIT_LFS)
    add_test(${KIT}-GenerateCubesFromLabels ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
      TestGenerateCubesFromLabels ${DATA}/Frog/frogtissue.mhd 1 29)

    add_test(${KIT}-GenerateModelsFromLabels ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
      TestGenerateModelsFromLabels ${DATA}/Frog/frogtissue.mhd 1 29)
  endif()

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
