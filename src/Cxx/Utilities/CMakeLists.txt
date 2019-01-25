project (${WIKI}Utilities)

if(NOT VTK_BINARY_DIR)
  set(VTK_LIBRARIES "")
  find_package(VTK COMPONENTS
    vtkCommonColor
    vtkCommonComputationalGeometry
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonMisc
    vtkCommonSystem
    vtkCommonTransforms
    vtkFiltersCore
    vtkFiltersGeneral
    vtkFiltersModeling
    vtkFiltersProgrammable
    vtkFiltersSources
    vtkFiltersStatistics
    vtkIOCore
    vtkIOGeometry
    vtkIOImage
    vtkIOLegacy
    vtkIOPLY
    vtkIOXML
    vtkImagingCore
    vtkImagingHybrid
    vtkInteractionStyle
    vtkRenderingAnnotation
    vtkRenderingCore
    vtkRenderingFreeType
    vtkRenderingOpenGL2
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

Requires_Setting_On (GetDataRoot BUILD_TESTING)
Requires_Version(LUTUtilities "6.0.0" ALL_FILES)

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
  set(KIT Utilities)
  set(NEEDS_ARGS
    ExtractFaces
    SaveSceneToFieldData
    SaveSceneToFile
    ViewportBorders
    ZBuffer
    )
  set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)
  set(TEMP ${WikiExamples_BINARY_DIR}/Testing/Temporary)

  add_test(${KIT}-ExtractFaces ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestExtractFaces ${DATA}/Hexahedron.vtu ${DATA}/QuadraticPyramid.vtu ${DATA}/QuadraticTetra.vtu ${DATA}/QuadraticWedge.vtu ${DATA}/Tetrahedron.vtu ${DATA}/TriQuadraticHexahedron.vtu ${DATA}/Triangle.vtu ${DATA}/Wedge.vtu)

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
