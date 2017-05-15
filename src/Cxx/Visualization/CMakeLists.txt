PROJECT (${WIKI}Visualization)

IF(NOT WikiExamples_BINARY_DIR)
FIND_PACKAGE(VTK REQUIRED)
IF(NOT VTK_USE_RENDERING)
  MESSAGE(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
ENDIF(NOT VTK_USE_RENDERING)
INCLUDE(${VTK_USE_FILE})
ENDIF(NOT WikiExamples_BINARY_DIR)

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  SET(KIT_LIBS vtkWidgets vtkRendering vtkHybrid)
else()
  SET(KIT_LIBS ${VTK_LIBRARIES})
endif()
#
# Build all .cxx files in the directory
FILE(GLOB ALL_FILES *.cxx)

include(${WikiExamples_SOURCE_DIR}/CMake/RequiresVersion.cmake)
include(${WikiExamples_SOURCE_DIR}/CMake/RequiresModule.cmake)
include(${WikiExamples_SOURCE_DIR}/CMake/RequiresSettingOff.cmake)

set(VERSION_MIN "6.0.0")
Requires_Version(AssignCellColorsFromLUT ${VERSION_MIN} ALL_FILES)
Requires_Version(NamedColors ${VERSION_MIN} ALL_FILES)
Requires_Version(NamedColorPatches ${VERSION_MIN} ALL_FILES)
Requires_Version(Legend ${VERSION_MIN} ALL_FILES)
Requires_Version(ElevationBandsWithGlyphs ${VERSION_MIN} ALL_FILES)
Requires_Version(CurvatureBandsWithGlyphs ${VERSION_MIN} ALL_FILES)
Requires_Version(ProjectSphere ${VERSION_MIN} ALL_FILES)
Requires_Version(BillboardTextActor3D "7.1.0" ALL_FILES)
Requires_Module(Shadows vtkRenderingOpenGL)
Requires_Setting_Off(StreamLines VTK_LEGACY_REMOVE)

foreach(SOURCE_FILE ${ALL_FILES})
  STRING(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  STRING(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  ADD_EXECUTABLE(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  TARGET_LINK_LIBRARIES(${WIKI}${EXAMPLE} ${KIT_LIBS})
endforeach(SOURCE_FILE)

if (BUILD_TESTING)
# Testing
SET(KIT Visualization)
SET(NEEDS_ARGS
  BackgroundTexture
  BoxClipStructuredPoints
  BoxClipUnstructuredGrid
  ClipArt
  CorrectlyRenderTranslucentGeometry
  CurvedReformation
  DataSetGradient
  DepthSortPolyData
  Glyph3DMapper
  HedgeHog
  RenderLargeImage
  SelectWindowRegion
  StreamLines
  TextureMapPlane
  TextureMapQuad
  VisualizeVTP
  Visualize2DPoints
)

SET(DATA ${WikiExamples_SOURCE_DIR}/Testing/Data)
SET(TEMP ${WikiExamples_BINARY_DIR}/Testing/Temporary)

ADD_TEST(${KIT}-BackgroundTexture ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestBackgroundTexture -E 30)

ADD_TEST(${KIT}-BoxClipStructuredPoints ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestBoxClipStructuredPoints ${DATA}/HeadMRVolume.mhd)

ADD_TEST(${KIT}-BoxClipUnstructuredGrid ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestBoxClipUnstructuredGrid ${DATA}/hexa.vtk)

ADD_TEST(${KIT}-ClipArt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestClipArt ${DATA}/stormy.jpg)

ADD_TEST(${KIT}-CorrectlyRenderTranslucentGeometry ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestCorrectlyRenderTranslucentGeometry 100 100 50 0.1 0 0)

ADD_TEST(${KIT}-CurvedReformation ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestCurvedReformation ${DATA}/HeadMRVolume.mhd ${DATA}/polyline.vtk 200)

ADD_TEST(${KIT}-DataSetGradient ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestDataSetGradient ${DATA}/hexa.vtk)

ADD_TEST(${KIT}-DepthSortPolyData ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestDepthSortPolyData 1 100 100 0)

ADD_TEST(${KIT}-Glyph3DMapper ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestGlyph3DMapper -E 40)

ADD_TEST(${KIT}-HedgeHog ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestHedgeHog -E 50)

ADD_TEST(${KIT}-RenderLargeImage ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestRenderLargeImage ${DATA}/Bunny.vtp ${TEMP}/Bunny.png 4)

ADD_TEST(${KIT}-SelectWindowRegion ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestSelectWindowRegion ${DATA}/Ox.jpg)

if (NOT VTK_LEGACY_REMOVE)
ADD_TEST(${KIT}-StreamLines ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestStreamLines ${DATA}/combxyz.bin ${DATA}/combq.bin)
endif()

ADD_TEST(${KIT}-TextureMapPlane ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestTextureMapPlane ${DATA}/Yinyang.jpg)

ADD_TEST(${KIT}-TextureMapQuad ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestTextureMapQuad ${DATA}/Yinyang.jpg)

ADD_TEST(${KIT}-VisualizeVTP ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestVisualizeVTP ${DATA}/Bunny.vtp)

ADD_TEST(${KIT}-Visualize2DPoints ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestVisualize2DPoints ${DATA}/Ring.vtp)

INCLUDE(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
endif()
