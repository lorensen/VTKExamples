project (${WIKI}Geovis)

if(NOT VTK_BINARY_DIR)
  set(VTK_LIBRARIES "")
  find_package(VTK COMPONENTS
    vtkCommonColor
    vtkCommonCore
    vtkCommonDataModel
    vtkFiltersGeneral
    vtkFiltersHybrid
    vtkFiltersSources
    vtkGeovisCore
    vtkIOXML
    vtkInteractionStyle
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
set(DEPRC_SRCS)
if(VTK_LEGACY_REMOVE OR NOT (VTK_VERSION VERSION_LESS "8.90.0"))
  list(APPEND DEPRC_SRCS
    GeoGraticle.cxx
    GeoAssignCoordinates.cxx
    )
endif()
file(GLOB ALL_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cxx)
if (DEPRC_SRCS)
  list(REMOVE_ITEM ALL_FILES ${DEPRC_SRCS})
endif()

if((NOT VTK_LEGACY_REMOVE) AND (VTK_VERSION VERSION_LESS "8.90.0"))
  Requires_Module(GeoGraticle vtkViewsGeovis)
endif()

foreach(SOURCE_FILE ${ALL_FILES})
  string(REPLACE ".cxx" "" EXAMPLE ${SOURCE_FILE})
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
  set(KIT Geovis)
  if((NOT VTK_LEGACY_REMOVE) AND (VTK_VERSION VERSION_LESS "8.90.0"))
    set(NEEDS_ARGS
      GeoGraticule
      )
    if (vtkViewsGeovis_LOADED)
      add_test(${KIT}-GeoGraticle ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
        TestGeoGraticle ${DATA}/political.vtp)
    endif()
  endif()
  include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
endif()
