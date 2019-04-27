project (${WIKI}VolumeRendering)

if(NOT WikiExamples_BINARY_DIR)
  set(VTK_LIBRARIES "")
  find_package(VTK COMPONENTS
    vtkCommonColor
    vtkCommonCore
    vtkCommonDataModel
    vtkFiltersCore
    vtkFiltersExtraction
    vtkFiltersGeneral
    vtkIOImage
    vtkIOLegacy
    vtkIOParallel
    vtkIOXML
    vtkImagingCore
    vtkImagingHybrid
    vtkInteractionStyle
    vtkInteractionWidgets
    vtkRenderingContextOpenGL2
    vtkRenderingCore
    vtkRenderingFreeType
    vtkRenderingGL2PSOpenGL2
    vtkRenderingOpenGL2
    vtkRenderingVolume
    vtkRenderingVolumeOpenGL2
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

if (VTK_RENDERING_BACKEND STREQUAL "OpenGL2")
  list(REMOVE_ITEM ALL_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/SmartVolumeMapper.cxx)
  list(REMOVE_ITEM ALL_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/HAVSVolumeMapper.cxx)
endif()

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
  set(KIT VolumeRendering)
  if (VTK_RENDERING_BACKEND STREQUAL "OpenGL2")
    set(NEEDS_ARGS
      PseudoVolumeRendering
      MinIntensityRendering
      IntermixedUnstructuredGrid
      FixedPointVolumeRayCastMapperCT
      RayCastIsosurface
      SimpleRayCast
      )
  else()
    set(NEEDS_ARGS
      HAVSVolumeMapper
      MinIntensityRendering
      IntermixedUnstructuredGrid
      )
  endif()

  set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)
  set(TEMP ${WikiExamples_BINARY_DIR}/Testing/Temporary)

  if (VTK_RENDERING_BACKEND STREQUAL "OpenGL2")
    add_test(${KIT}-MinIntensityRendering ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
      TestMinIntensityRendering ${DATA}/ironProt.vtk)
    add_test(${KIT}-FixedPointVolumeRayCastMapperCT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
      TestFixedPointVolumeRayCastMapperCT -MHA ${DATA}/FullHead.mhd -CT_Bone)
  else()
    add_test(${KIT}-HAVSVolumeMapper ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
      TestHAVSVolumeMapper ${DATA}/ironProt.vtk ${DATA}/neghip.slc)

    add_test(${KIT}-MinIntensityRendering ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
      TestMinIntensityRendering ${DATA}/ironProt.vtk)
  endif()

  add_test(${KIT}-RayCastIsosurface ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestRayCastIsosurface ${DATA}/FullHead.mhd 500 1150)

  add_test(${KIT}-SimpleRayCast ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestSimpleRayCast ${DATA}/ironProt.vtk)

  add_test(${KIT}-PseudoVolumeRendering ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestPseudoVolumeRendering ${DATA}/combxyz.bin ${DATA}/combq.bin)

  add_test(${KIT}-IntermixedUnstructuredGrid ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestIntermixedUnstructuredGrid ${DATA}/ironProt.vtk ${DATA}/neghip.slc)

  include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)

endif()
