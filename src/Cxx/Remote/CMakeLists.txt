project (${WIKI}Remote)

if(NOT VTK_BINARY_DIR)
  set(optional "")
  Add_Optional_If_In_Library(SplineDrivenImageSlicer "${VTK_AVAILABLE_COMPONENTS}" optional)
  set(VTK_LIBRARIES "")
  find_package(VTK COMPONENTS
    vtkCommonComputationalGeometry
    vtkCommonCore
    vtkCommonDataModel
    vtkFiltersCore
    vtkFiltersSources
    vtkInteractionStyle
    vtkInteractionWidgets
    vtkRenderingContextOpenGL2
    vtkRenderingCore
    vtkRenderingFreeType
    vtkRenderingGL2PSOpenGL2
    vtkRenderingOpenGL2
    ${optional}
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

Requires_Module(FrenetSerretFrame SplineDrivenImageSlicer)
Requires_Module(FrenetSerretFrameDemo SplineDrivenImageSlicer)

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
  set(KIT Remote)
  set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)

  include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
endif()
