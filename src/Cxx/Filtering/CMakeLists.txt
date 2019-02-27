project (${WIKI}Filtering)

if(NOT VTK_BINARY_DIR)
  set(VTK_LIBRARIES "")
  find_package(VTK COMPONENTS
    vtkCommonColor
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonMath
    vtkCommonTransforms
    vtkFiltersCore
    vtkFiltersExtraction
    vtkFiltersGeneral
    vtkFiltersGeneric
    vtkFiltersModeling
    vtkFiltersProgrammable
    vtkFiltersSources
    vtkIOGeometry
    vtkIOPLY
    vtkIOXML
    vtkImagingHybrid
    vtkImagingMath
    vtkInteractionStyle
    vtkRenderingCore
    vtkRenderingFreeType
    vtkRenderingOpenGL2
    vtkTestingGenericBridge
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

set(VERSION_MIN "6.0")
Requires_Version(GenericClip ${VERSION_MIN} ALL_FILES)
Requires_Setting_On (GenericClip BUILD_TESTING)

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
  set(KIT Filtering)
  set(NEEDS_ARGS
    ConnectivityFilterDemo
    ConstrainedDelaunay2D
    ContoursFromPolyData
    ConstrainedDelaunay2D
    ICPRealData
    SurfaceFromUnorganizedPoints
    )

  set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)

  add_test(${KIT}-ConnectivityFilterDemo ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestConnectivityFilterDemo ${DATA}/fsu/stratocaster.ply)

  add_test(${KIT}-ConstrainedDelaunay2D ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestConstrainedDelaunay2D -E 30)

  add_test(${KIT}-Delaunay2D ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestDelaunay2D -E 30)

  add_test(${KIT}-SurfaceFromUnorganizedPoints ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestSurfaceFromUnorganizedPoints ${DATA}/Bunny.vtp -E 30)

  add_test(${KIT}-ContoursFromPolyData ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestContoursFromPolyData ${DATA}/Bunny.vtp  -E 30)
  include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)

endif()
