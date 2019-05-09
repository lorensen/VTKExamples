project (${WIKI}InfoVis)

if(NOT VTK_BINARY_DIR)
  set(VTK_LIBRARIES "")
  find_package(VTK COMPONENTS
    vtkCommonColor
    vtkCommonComputationalGeometry
    vtkCommonCore
    vtkCommonDataModel
    vtkFiltersGeneral
    vtkFiltersSources
    vtkFiltersStatistics
    vtkImagingCore
    vtkImagingSources
    vtkIOCore
    vtkIOInfovis
    vtkIOXML
    vtkInfovisCore
    vtkInfovisLayout
    vtkInteractionImage
    vtkInteractionStyle
    vtkRenderingCore
    vtkRenderingFreeType
    vtkRenderingGL2PSOpenGL2
    vtkRenderingOpenGL2
    vtkRenderingContextOpenGL2
    vtkTestingCore
    vtkTestingRendering
    vtkViewsCore
    vtkViewsInfovis
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
Requires_Version(TreeMapView ${VERSION_MIN} ALL_FILES)
Requires_Setting_On (TreeMapView BUILD_TESTING)

if(NOT VTK_USE_PARALLEL)
  set(SKIP PKMeansClustering)
  message(STATUS "VTKWikiExamples: ${SKIP} requires VTK_PARALLEL and will not be built")
  string(REGEX REPLACE "[^;]*${SKIP}.cxx"
    "" ALL_FILES "${ALL_FILES}")
endif()

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
  set(KIT InfoVis)

  set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)

  set(NEEDS_ARGS
    DelimitedTextReader
    DelimitedTextWriter
    WordCloud
    XGMLReader
    )
  if ("${ALL_FILES}" MATCHES ".*TreeMapView.*")
    set(NEEDS_ARGS "${NEEDS_ARGS};TreeMapView")
    add_test(${KIT}-TreeMapView ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
      TestTreeMapView ${DATA}/Infovis-XML-vtkclasses.xml ${DATA}/Infovis-XML-vtklibrary.xml)
  endif()

  set(TEMP ${WikiExamples_BINARY_DIR}/Testing/Temporary)

  add_test(${KIT}-DelimitedTextReader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestDelimitedTextReader ${DATA}/DelimitedData.txt)

  add_test(${KIT}-DelimitedTextWriter ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestDelimitedTextWriter ${TEMP}/foo.txt)

  add_test(${KIT}-WordCloud ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestWordCloud ${DATA}/Gettysburg.txt --dpi 150 --fontFile ${DATA}/Canterbury.ttf)

  add_test(${KIT}-XGMLReader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestXGMLReader ${DATA}/fsm.gml)

  include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)

endif()
