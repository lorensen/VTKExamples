project (${WIKI}Texture)

if(NOT VTK_BINARY_DIR)
  set(VTK_LIBRARIES "")
  find_package(VTK COMPONENTS
    vtkCommonColor
    vtkCommonCore
    vtkCommonDataModel
    vtkFiltersCore
    vtkFiltersGeometry
    vtkFiltersModeling
    vtkFiltersSources
    vtkFiltersTexture
    vtkIOGeometry
    vtkIOImage
    vtkIOLegacy
    vtkIOPLY
    vtkIOParallel
    vtkIOXML
    vtkImagingHybrid
    vtkInteractionStyle
    vtkRenderingContextOpenGL2
    vtkRenderingCore
    vtkRenderingFreeType
    vtkRenderingGL2PSOpenGL2
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
  set(KIT Texture)
  set(NEEDS_ARGS
    AnimateVectors
    ProjectedTexture
    TextureCutSphere
    TexturePlane
    TexturedSphere
    TextureThreshold
    )

  set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)
  set(TEMP ${WikiExamples_BINARY_DIR}/Testing/Temporary)

  add_test(${KIT}-AnimateVectors ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestAnimateVectors ${DATA}/carotid.vtk
    ${DATA}/VectorAnimation/vecAnim1.vtk
    ${DATA}/VectorAnimation/vecAnim2.vtk
    ${DATA}/VectorAnimation/vecAnim3.vtk
    ${DATA}/VectorAnimation/vecAnim4.vtk
    ${DATA}/VectorAnimation/vecAnim5.vtk
    ${DATA}/VectorAnimation/vecAnim6.vtk
    ${DATA}/VectorAnimation/vecAnim7.vtk
    ${DATA}/VectorAnimation/vecAnim8.vtk)

  add_test(${KIT}-ProjectedTexture ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestProjectedTexture ${DATA}/fran_cut.vtk ${DATA}/fran_cut.png)

  add_test(${KIT}-TextureCutSphere ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestTextureCutSphere ${DATA}/texThres.vtk)

  add_test(${KIT}-TexturePlane ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestTexturePlane ${DATA}/masonry.bmp)

  add_test(${KIT}-TexturedSphere ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestTexturedSphere ${DATA}/earth.ppm)

  add_test(${KIT}-TextureThreshold ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestTextureThreshold ${DATA}/bluntfinxyz.bin ${DATA}/bluntfinq.bin ${DATA}/texThres2.vtk)

  include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
endif()
