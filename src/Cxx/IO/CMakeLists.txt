PROJECT (${WIKI}IO)

IF(NOT WikiExamples_BINARY_DIR)
FIND_PACKAGE(VTK REQUIRED)
IF(NOT VTK_USE_RENDERING)
  MESSAGE(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
ENDIF(NOT VTK_USE_RENDERING)
INCLUDE(${VTK_USE_FILE})
ENDIF(NOT WikiExamples_BINARY_DIR)

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  SET(KIT_LIBS vtkHybrid vtkGenericFiltering)
else()
  SET(KIT_LIBS ${VTK_LIBRARIES})
endif()
#
# Build all .cxx files in the directory
FILE(GLOB ALL_FILES *.cxx)
foreach(SOURCE_FILE ${ALL_FILES})
  STRING(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  STRING(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  ADD_EXECUTABLE(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  TARGET_LINK_LIBRARIES(${WIKI}${EXAMPLE} ${KIT_LIBS})
endforeach(SOURCE_FILE)

if (BUILD_TESTING)
# Testing
SET(KIT IO)
SET(NEEDS_ARGS
  ConvertFile
  DEMReader
  DumpXMLFile
  GenericDataObjectReader
  ImageReader2Factory
  IndividualVRML
  JPEGReader
  JPEGWriter
  MetaImageReader
  ParticleReader
  PNGReader
  PNGWriter
  ReadBMP
  ReadDICOM
  ReadDICOMSeries
  ReadImageData
  ReadOBJ
  ReadPDB
  ReadPlainTextTriangles
  ReadPLY
  ReadPLOT3D
  ReadPNM
  ReadPolyData
  ReadRectilinearGrid
  ReadSTL
  ReadStructuredGrid
  ReadTIFF
  ReadTextFile
  ReadUnknownTypeXMLFile
  ReadUnstructuredGrid
  SimplePointsReader
  StructuredPointsReader
  StructuredGridReader
  VRML
  WriteBMP
  WritePLY
  WritePNM
  WriteSTL
  WriteTIFF
  WriteVTI
  WriteVTU
)
 
SET(DATA ${WikiExamples_SOURCE_DIR}/Testing/Data)
SET(TEMP ${WikiExamples_BINARY_DIR}/Testing/Temporary)

ADD_TEST(${KIT}-ConvertFile ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestConvertFile ${DATA}/Bunny.vtp ${TEMP}/ConvertFile.ply)

ADD_TEST(${KIT}-DumpXMLFile ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestDumpXMLFile ${DATA}/Bunny.vtp)

ADD_TEST(${KIT}-GenericDataObjectReader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestGenericDataObjectReader ${DATA}/Bunny.vtp)

ADD_TEST(${KIT}-IndividualVRML ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestIndividualVRML ${DATA}/teapot.wrl teapot)

ADD_TEST(${KIT}-ImageReader2Factory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestImageReader2Factory ${DATA}/Gourds.png)

ADD_TEST(${KIT}-JPEGReader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestJPEGReader ${DATA}/Pileated.jpg)

ADD_TEST(${KIT}-JPEGWriter ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestJPEGWriter ${TEMP}/JPEGWriter.jpg)

ADD_TEST(${KIT}-MetaImageReader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestMetaImageReader ${DATA}/Gourds.mha)

ADD_TEST(${KIT}-ParticleReader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestParticleReader ${DATA}/Particles.raw)

ADD_TEST(${KIT}-PNGReader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestPNGReader ${DATA}/Gourds.png)

ADD_TEST(${KIT}-PNGWriter ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestPNGWriter ${TEMP}/PNGWriter.png)

ADD_TEST(${KIT}-ReadBMP ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadBMP ${DATA}/masonry.bmp)

ADD_TEST(${KIT}-DEMReader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestDEMReader ${DATA}/SainteHelens.dem)

ADD_TEST(${KIT}-ReadDICOM ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadDICOM ${DATA}/prostate.img)

ADD_TEST(${KIT}-ReadDICOMSeries ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadDICOMSeries ${DATA}/DICOMDirectory)

ADD_TEST(${KIT}-ReadImageData ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadImageData ${DATA}/vase.vti)

ADD_TEST(${KIT}-ReadOBJ ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadOBJ ${DATA}/trumpet.obj)

ADD_TEST(${KIT}-ReadPDB ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadPDB ${DATA}/lys.pdb)

ADD_TEST(${KIT}-ReadPLOT3D ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadPLOT3D ${DATA}/combxyz.bin ${DATA}/combq.bin)

ADD_TEST(${KIT}-ReadPLY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadPLY ${DATA}/shark.ply)

ADD_TEST(${KIT}-ReadPolyData ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadPolyData ${DATA}/Torso.vtp)

ADD_TEST(${KIT}-ReadPNM ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadPNM ${DATA}/Gourds.pnm)

ADD_TEST(${KIT}-ReadRectilinearGrid ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadRectilinearGrid ${DATA}/RectilinearGrid.vtr)

ADD_TEST(${KIT}-ReadSTL ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadSTL ${DATA}/42400-IDGH.stl)

ADD_TEST(${KIT}-ReadStructuredGrid ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadStructuredGrid ${DATA}/StructuredGrid.vts)

ADD_TEST(${KIT}-ReadPlainTextTriangles ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadPlainTextTriangles ${DATA}/Triangles.txt)

ADD_TEST(${KIT}-ReadUnknownTypeXMLFile ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadUnknownTypeXMLFile ${DATA}/Bunny.vtp)

ADD_TEST(${KIT}-ReadTIFF ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadTIFF ${DATA}/ColorCells.tif)

ADD_TEST(${KIT}-ReadTextFile ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadTextFile ${DATA}/TeapotPoints.txt)

ADD_TEST(${KIT}-ReadUnstructuredGrid ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadUnstructuredGrid ${DATA}/tetra.vtu)

ADD_TEST(${KIT}-SimplePointsReader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestSimplePointsReader ${DATA}/coords.txt)

ADD_TEST(${KIT}-StructuredPointsReader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestStructuredPointsReader ${DATA}/StructuredPoints.vtk)

ADD_TEST(${KIT}-StructuredGridReader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestStructuredGridReader ${DATA}/SampleStructGrid.vtk)

ADD_TEST(${KIT}-VRML ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestVRML ${DATA}/bridge.wrl)

ADD_TEST(${KIT}-WriteBMP ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestWriteBMP ${TEMP}/WriteBMP.bmp)

ADD_TEST(${KIT}-WritePNM ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestWritePNM ${TEMP}/WritePNM.pnm)

ADD_TEST(${KIT}-WritePLY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestWritePLY ${TEMP}/WritePLY.ply)

ADD_TEST(${KIT}-WriteSTL ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestWriteSTL ${TEMP}/WriteSTL.stl)

ADD_TEST(${KIT}-WriteTIFF ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestWriteTIFF ${TEMP}/WriteTIFF.tif)

ADD_TEST(${KIT}-WriteVTI ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestWriteVTI ${TEMP}/WriteVTI.vti)

ADD_TEST(${KIT}-WriteVTU ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestWriteVTU ${TEMP}/WriteVTU.vtu)

INCLUDE(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)

endif()
