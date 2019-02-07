project (${WIKI}CompositeData)

if(NOT VTK_BINARY_DIR)
  set(VTK_LIBRARIES "")
  find_package(VTK COMPONENTS
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonExecutionModel
    vtkFiltersCore
    vtkFiltersExtraction
    vtkFiltersGeneral
    vtkFiltersGeometry
    vtkFiltersModeling
    vtkFiltersSources
    vtkIOLegacy
    vtkIOXML
    vtkInteractionStyle
    vtkRenderingCore
    vtkRenderingFreeType
    vtkRenderingOpenGL2
    vtkTestingRendering
    OPTIONAL_COMPONENTS
    vtkRenderingGL2PSOpenGL2
    QUIET
    )
  if (VTK_VERSION VERSION_LESS "8.90.0")
    include(${VTK_USE_FILE})
  endif()
endif()

set(KIT CompositeData)
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
  set(KIT CompositeData)
  set(NEEDS_ARGS
    OverlappingAMR
    )

  # This has been moved to Cxx/Untested/HasBugs/CompositeData.
  # set (EXCLUDE_TEST
  #   HierarchicalBoxPipeline
  #   )

  add_test(${KIT}-OverlappingAMR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestOverlappingAMR -E 35)
  add_test(${KIT}-CompositePolyDataMapper ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestCompositePolyDataMapper)
  add_test(${KIT}-MultiBlockDataSet ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestMultiBlockDataSet)

  include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)

endif()
