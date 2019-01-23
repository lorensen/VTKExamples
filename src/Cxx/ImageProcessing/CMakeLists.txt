project (${WIKI}ImageProcessing)

if(NOT VTK_BINARY_DIR)
  set(VTK_LIBRARIES "")
  find_package(VTK COMPONENTS
    vtkCommonColor
    vtkCommonCore
    vtkCommonDataModel
    vtkFiltersGeneral
    vtkIOImage
    vtkImagingColor
    vtkImagingCore
    vtkImagingFourier
    vtkImagingGeneral
    vtkImagingHybrid
    vtkImagingMath
    vtkImagingMorphological
    vtkImagingSources
    vtkInteractionStyle
    vtkRenderingCore
    vtkRenderingFreeType
    vtkRenderingGL2PSOpenGL2
    vtkRenderingOpenGL2
    OPTIONAL_COMPONENTS
    vtkTestingRendering
    QUIET
    )
  if (VTK_VERSION VERSION_LESS "8.90.0")
    include(${VTK_USE_FILE})
  endif()
endif()

set(KIT ImageProcessing)
set(KIT_LIBS ${VTK_LIBRARIES})

#
# Build all .cxx files in the directory
file(GLOB ALL_FILES *.cxx)

foreach(SOURCE_FILE ${ALL_FILES})
  string(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  add_executable(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  target_link_libraries(${WIKI}${EXAMPLE} ${KIT_LIBS})
  if (VTK_VERSION VERSION_GREATER "8.8")
    vtk_module_autoinit(
      TARGETS ${WIKI}${EXAMPLE}
      MODULES ${VTK_LIBRARIES}
      )
  endif()
endforeach()

if (BUILD_TESTING)
  # Testing
  set(NEEDS_ARGS
    Attenuation
    EnhanceEdges
    GaussianSmooth
    HybridMedianComparison
    IdealHighPass
    IsoSubsample
    MedianComparison
    MorphologyComparison
    Pad
    VTKSpectrum
    )

  set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)
  set(TEMP ${WikiExamples_BINARY_DIR}/Testing/Temporary)

  add_test(${KIT}-Attenuation ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestAttenuation ${DATA}/AttenuationArtifact.pgm)

  add_test(${KIT}-EnhanceEdges ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestEnhanceEdges ${DATA}/FullHead.mhd)

  add_test(${KIT}-GaussianSmooth ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestGaussianSmooth ${DATA}/Gourds.png)

  add_test(${KIT}-IdealHighPass ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestIdealHighPass ${DATA}/fullhead15.png)

  add_test(${KIT}-HybridMedianComparison ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestHybridMedianComparison ${DATA}/TestPattern.png)

  add_test(${KIT}-MedianComparison ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestMedianComparison ${DATA}/FullHead.mhd)

  add_test(${KIT}-MorphologyComparison ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestMorphologyComparison ${DATA}/binary.pgm)

  add_test(${KIT}-IsoSubsample ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestIsoSubsample ${DATA}/FullHead.mhd)

  add_test(${KIT}-Pad ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestPad ${DATA}/FullHead.mhd)

  add_test(${KIT}-VTKSpectrum ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestVTKSpectrum ${DATA}/vtks.pgm)

  include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
endif()
