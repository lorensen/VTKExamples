project (${WIKI}GeometricObjects)

if(NOT VTK_BINARY_DIR)
  set(VTK_LIBRARIES "")
  find_package(VTK COMPONENTS
    vtkCommonColor
    vtkCommonComputationalGeometry
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonExecutionModel
    vtkCommonTransforms
    vtkFiltersCore
    vtkFiltersGeneral
    vtkFiltersModeling
    vtkFiltersSources
    vtkIOImage
    vtkIOXML
    vtkInteractionStyle
    vtkInteractionWidgets
    vtkRenderingAnnotation
    vtkRenderingCore
    vtkRenderingFreeType
    vtkRenderingLabel
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

set(VERSION_MIN "7.0")
Requires_Version(ParametricKuenDemo ${VERSION_MIN} ALL_FILES)
Requires_Version(ParametricObjectsDemo2 ${VERSION_MIN} ALL_FILES)
Requires_Module(OpenVRCone vtkRenderingOpenVR)
Requires_Module(OpenVRCube vtkRenderingOpenVR)
Requires_Module(OpenVRCylinder vtkRenderingOpenVR)
Requires_Module(OpenVRFrustm vtkRenderingOpenVR)
Requires_Module(OpenVROrientedArrow vtkRenderingOpenVR)
Requires_Module(OpenVROrientedCylinder vtkRenderingOpenVR)
Requires_Module(OpenVRSphere vtkRenderingOpenVR)
Requires_Module(OpenVRTessellatedBoxSource vtkRenderingOpenVR)

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
  set(KIT GeometricObjects)
  set(NEEDS_ARGS
    QuadraticHexahedron
    TessellatedBoxSource
    )

  add_test(${KIT}-QuadraticHexahedron ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestQuadraticHexahedron -E 30)

  add_test(${KIT}-TessellatedBoxSource ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestTessellatedBoxSource -E 30)

  include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
endif()
