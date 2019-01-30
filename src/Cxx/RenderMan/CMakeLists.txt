project (${WIKI}RenderMan)

if(NOT VTK_BINARY_DIR)
  set(VTK_LIBRARIES "")
  if (VTK_VERSION VERSION_LESS "8.90.0")
    set(components "vtkIOExportOpenGL2")
  endif()

  set(VTK_LIBRARIES "")
  find_package(VTK COMPONENTS
    vtkCommonCore
    vtkFiltersCore
    vtkIOExport
    vtkIOExportPDF
    vtkIOXML
    vtkInteractionStyle
    vtkRenderingContextOpenGL2
    vtkRenderingCore
    vtkRenderingFreeType
    ${components}
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

foreach(SOURCE_FILE ${ALL_FILES})
 string(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  add_executable(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  target_link_libraries(${WIKI}${EXAMPLE} PRIVATE ${KIT_LIBS})
  if (NOT VTK_VERSION VERSION_LESS "8.90.0")
    vtk_module_autoinit(
      TARGETS ${WIKI}${EXAMPLE}
      MODULES ${VTK_LIBRARIES}
      )
  endif()
endforeach()

if (BUILD_TESTING)
  # Testing
  set(KIT RenderMan)
  set(NEEDS_ARGS
    PolyDataRIB
    )
  set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)
  add_test(${KIT}-PolyDataRIB ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestPolyDataRIB ${DATA}/Torso.vtp .01)

  include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
endif()
