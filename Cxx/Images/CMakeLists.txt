PROJECT (${WIKI}Images)

IF(NOT WikiExamples_BINARY_DIR)
FIND_PACKAGE(VTK REQUIRED)
IF(NOT VTK_USE_RENDERING)
  MESSAGE(FATAL_ERROR "VTKWikiExamples: Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
ENDIF(NOT VTK_USE_RENDERING)
INCLUDE(${VTK_USE_FILE})
ENDIF(NOT WikiExamples_BINARY_DIR)

SET(KIT Images)
if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  SET(KIT_LIBS vtkHybrid vtkRendering vtkWidgets)
else()
  SET(KIT_LIBS ${VTK_LIBRARIES})
endif()

#
# Build all .cxx files in the directory
FILE(GLOB ALL_FILES *.cxx)

if(NOT VTK_USE_SYSTEM_FREETYPE)
  message(STATUS "VTKWikiExamples: ImageText requires VTK_USE_SYSTEM_FREETYPE and will not be built")
  string(REGEX REPLACE "[^;]*ImageText.cxx"
         "" ALL_FILES "${ALL_FILES}")
endif()

foreach(SOURCE_FILE ${ALL_FILES})
  STRING(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  STRING(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  ADD_EXECUTABLE(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  TARGET_LINK_LIBRARIES(${WIKI}${EXAMPLE} ${KIT_LIBS})
endforeach(SOURCE_FILE)

if (BUILD_TESTING)
# Testing
SET(NEEDS_ARGS
#  HistogramBarChart
#  HistogramXYPlot
  CannyEdgeDetector
  Cast
  CenterAnImage
  Colored2DImageFusion
  CombineImages
  DrawOnAnImage
  ExtractComponents
  Flip
  ImageAccumulateGreyscale
  ImageAnisotropicDiffusion2D
  ImageCheckerboard
  ImageCityBlockDistance
  ImageContinuousDilate3D
  ImageContinuousErode3D
  ImageDilateErode3D
  ImageHybridMedian2D
  ImageMagnify
  ImageNonMaximumSuppression
  ImageOpenClose3D
  ImageRange3D
  ImageRotate
  ImageSeparableConvolution
  ImageToPolyDataFilter
  ImageToStructuredPoints
  Transparency
  InteractWithImage
  PickPixel
  PickPixel2
  RGBToHSV
  RTAnalyticSource
  ResizeImage
  StaticImage
)

SET(DATA ${WikiExamples_SOURCE_DIR}/Testing/Data)
SET(TEMP ${WikiExamples_BINARY_DIR}/Testing/Temporary)

ADD_TEST(${KIT}-CannyEdgeDetector ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestCannyEdgeDetector ${DATA}/Gourds.png)

ADD_TEST(${KIT}-Cast ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestCast  ${DATA}/Ox.jpg ${TEMP}/Cast.jpg)

ADD_TEST(${KIT}-CenterAnImage ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestCenterAnImage  ${DATA}/Ox.jpg)

ADD_TEST(${KIT}-Colored2DImageFusion ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestColored2DImageFusion  ${DATA}/Ox.jpg ${DATA}/Gourds2.jpg)

ADD_TEST(${KIT}-CombineImages ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestCombineImages  ${DATA}/Ox.jpg ${DATA}/Gourds2.jpg)

ADD_TEST(${KIT}-DrawOnAnImage ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestDrawOnAnImage  ${DATA}/Gourds2.jpg)

ADD_TEST(${KIT}-ExtractComponents ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestExtractComponents  ${DATA}/Gourds2.jpg)

ADD_TEST(${KIT}-Flip ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestFlip  ${DATA}/Gourds2.jpg ${TEMP}/Flip.jpg )

#ADD_TEST(${KIT}-HistogramBarChart ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
#  TestHistogramBarChart ${DATA}/Gourds2.jpg)

#ADD_TEST(${KIT}-HistogramXYPlot ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
#  TestHistogramXYPlot  ${DATA}/Gourds2.jpg)

ADD_TEST(${KIT}-ImageAccumulateGreyscale ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestImageAccumulateGreyscale  ${DATA}/Ox.jpg)

ADD_TEST(${KIT}-ImageAnisotropicDiffusion2D ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestImageAnisotropicDiffusion2D  ${DATA}/cake_easy.jpg)

ADD_TEST(${KIT}-ImageCheckerboard ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestImageCheckerboard  ${DATA}/Ox.jpg ${DATA}/Gourds2.jpg)

ADD_TEST(${KIT}-ImageCityBlockDistance ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestImageCityBlockDistance ${DATA}/Yinyang.jpg -E 15)

ADD_TEST(${KIT}-ImageContinuousDilate3D ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestImageContinuousDilate3D ${DATA}/Gourds.png)

ADD_TEST(${KIT}-ImageContinuousErode3D ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestImageContinuousErode3D ${DATA}/Gourds.png)

ADD_TEST(${KIT}-ImageDilateErode3D ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestImageDilateErode3D ${DATA}/Yinyang.png -E 25)

ADD_TEST(${KIT}-ImageHybridMedian2D ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestImageHybridMedian2D ${DATA}/Gourds.png)

ADD_TEST(${KIT}-ImageMagnify ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestImageMagnify ${DATA}/Gourds.png)

# The ImageNoiseSource is inherently random
ADD_TEST(${KIT}-ImageNoiseSource ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestImageNoiseSource -E 999999)

ADD_TEST(${KIT}-ImageNonMaximumSuppression ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestImageNonMaximumSuppression -E 20)

ADD_TEST(${KIT}-ImageOpenClose3D ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestImageOpenClose3D ${DATA}/Yinyang.png -E 25)

ADD_TEST(${KIT}-InteractWithImage ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestInteractWithImage ${DATA}/Ox.jpg)

ADD_TEST(${KIT}-ImageToPolyDataFilter ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestImageToPolyDataFilter ${DATA}/Gourds.png)

ADD_TEST(${KIT}-ImageRotate ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestImageRotate ${DATA}/Gourds.png 45)

ADD_TEST(${KIT}-ImageSeparableConvolution ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestImageSeparableConvolution ${DATA}/Yinyang.png -E 25)
  
ADD_TEST(${KIT}-ImageToStructuredPoints ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestImageToStructuredPoints -E 25)

ADD_TEST(${KIT}-Transparency ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestTransparency  ${DATA}/Ox.jpg)

ADD_TEST(${KIT}-PickPixel ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestPickPixel  ${DATA}/Gourds2.jpg)

ADD_TEST(${KIT}-PickPixel2 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestPickPixel2  ${DATA}/ColorCells.tif)

ADD_TEST(${KIT}-ImageRange3D ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestImageRange3D  ${DATA}/Gourds2.jpg)

ADD_TEST(${KIT}-RGBToHSV ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestRGBToHSV ${DATA}/Gourds2.jpg)

ADD_TEST(${KIT}-StaticImage ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestStaticImage ${DATA}/Ox.jpg)

ADD_TEST(${KIT}-Transparency ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestTransparency ${DATA}/Gourds2.jpg)

ADD_TEST(${KIT}-RTAnalyticSource ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestRTAnalyticSource -E 20)

ADD_TEST(${KIT}-ResizeImage ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestResizeImage ${DATA}/Gourds2.jpg 640 480 1)

INCLUDE(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
endif()
