project (${WIKI}Widgets)

if(NOT VTK_BINARY_DIR)
  set(VTK_LIBRARIES "")
  find_package(VTK COMPONENTS
    vtkCommonColor
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonTransforms
    vtkFiltersCore
    vtkFiltersSources
    vtkIOImage
    vtkIOXML
    vtkImagingGeneral
    vtkImagingHybrid
    vtkImagingSources
    vtkImagingStatistics
    vtkImagingStencil
    vtkInteractionStyle
    vtkInteractionWidgets
    vtkRenderingAnnotation
    vtkRenderingCore
    vtkRenderingFreeType
    vtkRenderingOpenGL2
    OPTIONAL_COMPONENTS
    vtkTestingRendering
    )
endif()

set(KIT_LIBS ${VTK_LIBRARIES})

#
# Build all .cxx files in the directory
file(GLOB ALL_FILES *.cxx)
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
