project (${WIKI}Visualization)

if(NOT VTK_BINARY_DIR)
  set(optional "")
  Add_Optional_If_In_Library(SplineDrivenImageSlicer "${VTK_AVAILABLE_COMPONENTS}" optional)
  set(VTK_LIBRARIES "")
  find_package(VTK COMPONENTS
  vtkCommonColor
  vtkCommonComputationalGeometry
  vtkCommonCore
  vtkCommonDataModel
  vtkCommonExecutionModel
  vtkCommonMath
  vtkCommonSystem
  vtkCommonTransforms
  vtkDomainsChemistry
  vtkDomainsChemistryOpenGL2
  vtkFiltersCore
  vtkFiltersFlowPaths
  vtkFiltersGeneral
  vtkFiltersGeometry
  vtkFiltersHybrid
  vtkFiltersModeling
  vtkFiltersProgrammable
  vtkFiltersSources
  vtkFiltersTexture
  vtkIOGeometry
  vtkIOImage
  vtkIOLegacy
  vtkIOPLY
  vtkIOParallel
  vtkIOXML
  vtkImagingColor
  vtkImagingCore
  vtkImagingGeneral
  vtkImagingHybrid
  vtkImagingMorphological
  vtkImagingSources
  vtkInteractionImage
  vtkInteractionStyle
  vtkInteractionWidgets
  vtkRenderingAnnotation
  vtkRenderingContextOpenGL2
  vtkRenderingCore
  vtkRenderingFreeType
  vtkRenderingGL2PSOpenGL2
  vtkRenderingLOD
  vtkRenderingLabel
  vtkRenderingOpenGL2
  vtkTestingRendering
  ${optional}  
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

set(VERSION_MIN "6.0.0")
Requires_Version(AssignCellColorsFromLUT ${VERSION_MIN} ALL_FILES)
Requires_Version(NamedColors ${VERSION_MIN} ALL_FILES)
Requires_Version(NamedColorPatches ${VERSION_MIN} ALL_FILES)
Requires_Version(Legend ${VERSION_MIN} ALL_FILES)
Requires_Version(ElevationBandsWithGlyphs ${VERSION_MIN} ALL_FILES)
Requires_Module(ExtrudePolyDataAlongLine SplineDrivenImageSlicer)
Requires_Version(CurvatureBandsWithGlyphs ${VERSION_MIN} ALL_FILES)
Requires_Version(PointDataSubdivision ${VERSION_MIN} ALL_FILES)
Requires_Version(ProjectSphere ${VERSION_MIN} ALL_FILES)
Requires_Version(BillboardTextActor3D "7.1.0" ALL_FILES)
Requires_Module(ShadowsOpenGL vtkRenderingOpenGL)
#Requires_Setting_Off(StreamLines VTK_LEGACY_REMOVE)
Requires_GitLfs(Hawaii ALL_FILES)
Requires_GitLfs(FlyingFrogSkinAndTissue ALL_FILES)
Requires_GitLfs(FlyingFrogSkinAndTissueB ALL_FILES)
Requires_GitLfs(FlyingFrogSkinAndTissueC ALL_FILES)
Requires_GitLfs(FrogSlice ALL_FILES)
Requires_GitLfs(ViewFrog ALL_FILES)
Requires_GitLfs(ViewFrogA ALL_FILES)
Requires_GitLfs(ViewFrogBoth ALL_FILES)
Requires_GitLfs(ViewFrogSkinAndTissue ALL_FILES)

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
  set(KIT Visualization)
  set(NEEDS_ARGS
    AlphaFrequency
    Arbitrary3DCursor
    BackgroundTexture
    Blow
    BlobbyLogo
    BoxClipStructuredPoints
    BoxClipUnstructuredGrid
    ChooseTextColor
    ChooseTextColorDemo
    ClipArt
    ComplexV
    CorrectlyRenderTranslucentGeometry
    CreateColorSeriesDemo
    CurvedReformation
    DepthSortPolyData
    EdgePoints
    ExtrudePolyDataAlongLine
    FlyingFrogSkinAndTissue
    FlyingFrogSkinAndTissueB
    FlyingFrogSkinAndTissueC
    FontFile
    FrogSlice
    Glyph3DImage
    Glyph3DMapper
    HanoiInitial
    HanoiIntermediate
    Hawaii
    HedgeHog
    Kitchen
    NormalsDemo
    PointDataSubdivision
    ProteinRibbons
    RenderLargeImage
    SelectWindowRegion
    ShepardInterpolation
    StreamLines
    TextureMapPlane
    TextureMapQuad
    ViewFrog
    ViewFrogA
    ViewFrogBoth
    ViewFrogSkinAndTissue
    VisualizeVTP
    Visualize2DPoints
    )

  set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)
  set(TEMP ${WikiExamples_BINARY_DIR}/Testmake rebuing/Temporary)

  add_test(${KIT}-AlphaFrequency ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestAlphaFrequency ${DATA}/Gettysburg.txt)

  add_test(${KIT}-Arbitrary3DCursor ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestArbitrary3DCursor ${DATA}/Bunny.vtp)

  add_test(${KIT}-BackgroundTexture ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestBackgroundTexture -E 30)

  add_test(${KIT}-Blow ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestBlow ${DATA}/blow.vtk)

  add_test(${KIT}-BlobbyLogo ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestBlobbyLogo ${DATA}/v.vtk ${DATA}/t.vtk ${DATA}/k.vtk)

  add_test(${KIT}-BoxClipStructuredPoints ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestBoxClipStructuredPoints ${DATA}/HeadMRVolume.mhd)

  add_test(${KIT}-BoxClipUnstructuredGrid ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestBoxClipUnstructuredGrid ${DATA}/hexa.vtk)

  add_test(${KIT}-ComplexV ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestComplexV ${DATA}/carotid.vtk)

  add_test(${KIT}-ClipArt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestClipArt ${DATA}/stormy.jpg)

  add_test(${KIT}-ChooseTextColor ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestChooseTextColor ${DATA}/Canterbury.ttf Pink  MintCream SaddleBrown)

  add_test(${KIT}-ChooseTextColorDemo ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestChooseTextColorDemo .8 mintcream ivoryblack)

  add_test(${KIT}-CorrectlyRenderTranslucentGeometry ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestCorrectlyRenderTranslucentGeometry 100 100 50 0.1 0 0)

  add_test(${KIT}-CreateColorSeriesDemo ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestCreateColorSeriesDemo Yellow)

  add_test(${KIT}-CurvedReformation ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestCurvedReformation ${DATA}/HeadMRVolume.mhd ${DATA}/polyline.vtk 200)

  add_test(${KIT}-EdgePoints ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestEdgePoints ${DATA}/FullHead.mhd 500)

  add_test(${KIT}-DepthSortPolyData ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestDepthSortPolyData 1 100 100 0)

  if (TARGET ExtrudePolyDataAlongLine)
    add_test(${KIT}-ExtrudePolyDataAlongLine ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
      TestExtrudePolyDataAlongLine ${DATA}/a.vtp)
  endif()

  add_test(${KIT}-FontFile ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestFontFile ${DATA}/CopyPaste.ttf)

  add_test(${KIT}-Glyph3DImage ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestGlyph3DImage ${DATA}/emote.jpg)

  add_test(${KIT}-Glyph3DMapper ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestGlyph3DMapper -E 40)

  add_test(${KIT}-HanoiInitial ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestHanoiInitial -c 1)

  add_test(${KIT}-HanoiIntermediate ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestHanoiIntermediate -c 2)

  if(GIT_LFS)
    add_test(${KIT}-FlyingFrogSkinAndTissue ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
      TestFlyingFrogSkinAndTissue ${DATA}/Frog/frog.mhd ${DATA}/Frog/frogtissue.mhd)
    add_test(${KIT}-FlyingFrogSkinAndTissueB ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
      TestFlyingFrogSkinAndTissueB ${DATA}/Frog/frog.mhd ${DATA}/Frog/frogtissue.mhd 1)
    add_test(${KIT}-FlyingFrogSkinAndTissueC ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
      TestFlyingFrogSkinAndTissueC ${DATA}/Frog/frog.mhd ${DATA}/Frog/frogtissue.mhd 1 1)
    add_test(${KIT}-FrogSlice ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
      TestFrogSlice ${DATA}/Frog/frog.mhd ${DATA}/Frog/frogtissue.mhd)
    add_test(${KIT}-Hawaii ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
      TestHawaii ${DATA}/honolulu.vtk)
    add_test(${KIT}-ViewFrog ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
      TestViewFrog ${DATA}/Frog/frogtissue.mhd blood brain duodenum eyeRetina eyeWhite heart ileum kidney intestine liver lung nerve skeleton spleen stomach)
    add_test(${KIT}-ViewFrogA ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
      TestViewFrogA ${DATA}/Frog/frogtissue.mhd blood brain duodenum eyeRetina eyeWhite heart ileum kidney intestine liver lung nerve spleen stomach)
    add_test(${KIT}-ViewFrogBoth ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
      TestViewFrogBoth ${DATA}/Frog/frogtissue.mhd brain)
    add_test(${KIT}-ViewFrogSkinAndTissue ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
      TestViewFrogSkinAndTissue ${DATA}/Frog/frog.mhd ${DATA}/Frog/frogtissue.mhd)
  endif()

  add_test(${KIT}-HedgeHog ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestHedgeHog -E 50)

  add_test(${KIT}-Kitchen ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestKitchen ${DATA}/kitchen.vtk)

  add_test(${KIT}-NormalsDemo ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestNormalsDemo ${DATA}/42400-IDGH.stl)

  add_test(${KIT}-PointDataSubdivision ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestPointDataSubdivision 2)

  add_test(${KIT}-ProteinRibbons ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestProteinRibbons ${DATA}/2j6g.pdb)

  add_test(${KIT}-RenderLargeImage ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestRenderLargeImage ${DATA}/Bunny.vtp ${TEMP}/Bunny.png 4)

  add_test(${KIT}-SelectWindowRegion ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestSelectWindowRegion ${DATA}/Ox.jpg)

  add_test(${KIT}-ShepardInterpolation ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestShepardInterpolation ${DATA}/cowHead.vtp 100)

  add_test(${KIT}-StreamLines ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestStreamLines ${DATA}/combxyz.bin ${DATA}/combq.bin)

  add_test(${KIT}-TextureMapPlane ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestTextureMapPlane ${DATA}/Yinyang.jpg)

  add_test(${KIT}-TextureMapQuad ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestTextureMapQuad ${DATA}/Yinyang.jpg)

  add_test(${KIT}-VisualizeVTP ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestVisualizeVTP ${DATA}/Bunny.vtp)

  add_test(${KIT}-Visualize2DPoints ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestVisualize2DPoints ${DATA}/Ring.vtp)

  include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
endif()
