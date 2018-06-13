project (${WIKI}Geovis)

if(NOT WikiExamples_BINARY_DIR)
  find_package(VTK REQUIRED)
  include(${VTK_USE_FILE})
endif()

set(KIT_LIBS ${VTK_LIBRARIES})

#
# Build all .cxx files in the directory
set(DEPRC_SRCS)
if(VTK_LEGACY_REMOVE)
  list(APPEND DEPRC_SRCS
    GeoGraticule.cxx
    GeoAssignCoordinates.cxx
  )
endif()
file(GLOB ALL_FILES *.cxx)
if (DEPRC_SRCS)
  list(REMOVE_ITEM ALL_FILES ${DEPRC_SRCS})
endif()

if(NOT VTK_LEGACY_REMOVE)
  include(${WikiExamples_SOURCE_DIR}/CMake/RequiresModule.cmake)
  Requires_Module(GeoGraticle vtkViewsGeovis)
endif()

foreach(SOURCE_FILE ${ALL_FILES})
  string(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  add_executable(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  target_link_libraries(${WIKI}${EXAMPLE} ${KIT_LIBS})
endforeach()

if (BUILD_TESTING)
# Testing
set(KIT Geovis)
if(NOT VTK_LEGACY_REMOVE)
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
