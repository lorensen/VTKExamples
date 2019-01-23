project (${WIKI}Plotting)

if(NOT VTK_BINARY_DIR)
  set(VTK_LIBRARIES "")
  find_package(VTK COMPONENTS
    vtkChartsCore
    vtkCommonColor
    vtkCommonCore
    vtkCommonDataModel
    vtkFiltersSources
    vtkFiltersStatistics
    vtkIOImage
    vtkImagingCore
    vtkImagingStatistics
    vtkInteractionStyle
    vtkRenderingAnnotation
    vtkRenderingContext2D
    vtkRenderingContextOpenGL2
    vtkRenderingCore
    vtkRenderingFreeType
    vtkRenderingGL2PSOpenGL2
    vtkRenderingOpenGL2
    vtkTestingCore
    vtkTestingRendering
    vtkViewsContext2D
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
Requires_Version(BoxChart ${VERSION_MIN} ALL_FILES)
Requires_Version(StackedPlot ${VERSION_MIN} ALL_FILES)
Requires_Version(StackedBar ${VERSION_MIN} ALL_FILES)

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
  set(KIT Plotting)
  set(NEEDS_ARGS
    Diagram
    HistogramBarChart
    LinePlot
    )
  set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)

  add_test(${KIT}-Diagram ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestDiagram "Brewer Diverging Spectral (8)")

  add_test(${KIT}-HistogramBarChart ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestHistogramBarChart ${DATA}/Pileated.jpg)

  add_test(${KIT}-LinePlot ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestLinePlot -E 50)

  include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
endif()
