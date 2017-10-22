project (${WIKI}IO)

if(NOT WikiExamples_BINARY_DIR)
find_package(VTK REQUIRED)
if(NOT VTK_USE_RENDERING)
  message(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
endif(NOT VTK_USE_RENDERING)
include(${VTK_USE_FILE})
endif(NOT WikiExamples_BINARY_DIR)

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  set(KIT_LIBS vtkHybrid vtkGenericFiltering)
else()
  set(KIT_LIBS ${VTK_LIBRARIES})
endif()
#
# Build all .cxx files in the directory
file(GLOB ALL_FILES *.cxx)
foreach(SOURCE_FILE ${ALL_FILES})
  string(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  add_executable(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  target_link_libraries(${WIKI}${EXAMPLE} ${KIT_LIBS})
endforeach(SOURCE_FILE)

if (BUILD_TESTING)
# Testing
set(KIT IO)
set(NEEDS_ARGS
  3DSImporter
  ConvertFile
  DEMReader
  DumpXMLFile
  GenericDataObjectReader
  ImageReader2Factory
  IndividualVRML
  JPEGReader
  JPEGWriter
  MetaImageReader
  OBJImporter
  ParticleReader
  PNGReader
  PNGWriter
  ReadAllPolyDataTypes
  ReadAllPolyDataTypesDemo
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
  VRMLImporter
  VRMLImporterDemo
  WriteBMP
  WritePLY
  WritePNM
  WriteSTL
  WriteTIFF
  WriteVTI
  WriteVTU
)
 
set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)
set(TEMP ${WikiExamples_BINARY_DIR}/Testing/Temporary)

add_test(${KIT}-3DSImporter ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  Test3DSImporter ${DATA}/iflamingo.3ds)

add_test(${KIT}-ConvertFile ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestConvertFile ${DATA}/Bunny.vtp ${TEMP}/ConvertFile.ply)

add_test(${KIT}-DumpXMLFile ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestDumpXMLFile ${DATA}/Bunny.vtp)

add_test(${KIT}-GenericDataObjectReader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestGenericDataObjectReader ${DATA}/Bunny.vtp)

add_test(${KIT}-IndividualVRML ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestIndividualVRML ${DATA}/teapot.wrl teapot)

add_test(${KIT}-ImageReader2Factory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestImageReader2Factory ${DATA}/Gourds.png)

add_test(${KIT}-JPEGReader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestJPEGReader ${DATA}/Pileated.jpg)

add_test(${KIT}-JPEGWriter ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestJPEGWriter ${TEMP}/JPEGWriter.jpg)

add_test(${KIT}-MetaImageReader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestMetaImageReader ${DATA}/Gourds.mha)

add_test(${KIT}-OBJImporter ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestOBJImporter ${DATA}/doorman/doorman.obj ${DATA}/doorman/doorman.mtl ${DATA}/doorman)

add_test(${KIT}-ParticleReader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestParticleReader ${DATA}/Particles.raw)

add_test(${KIT}-PNGReader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestPNGReader ${DATA}/Gourds.png)

add_test(${KIT}-PNGWriter ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestPNGWriter ${TEMP}/PNGWriter.png)

add_test(${KIT}-ReadAllPolyDataTypes ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadAllPolyDataTypes ${DATA}/horse.ply)

add_test(${KIT}-ReadAllPolyDataTypesDemo ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestReadAllPolyDataTypesDemo ${DATA}/teapot.g ${DATA}/cowHead.vtp ${DATA}/horse.ply ${DATA}/trumpet.obj ${DATA}/42400-IDGH.stl ${DATA}/v.vtk)

add_test(${KIT}-ReadBMP ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadBMP ${DATA}/masonry.bmp)

add_test(${KIT}-DEMReader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestDEMReader ${DATA}/SainteHelens.dem)

add_test(${KIT}-ReadDICOM ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadDICOM ${DATA}/prostate.img)

add_test(${KIT}-ReadDICOMSeries ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadDICOMSeries ${DATA}/DICOMDirectory)

add_test(${KIT}-ReadImageData ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadImageData ${DATA}/vase.vti)

add_test(${KIT}-ReadOBJ ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadOBJ ${DATA}/trumpet.obj)

add_test(${KIT}-ReadPDB ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadPDB ${DATA}/lys.pdb)

add_test(${KIT}-ReadPLOT3D ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadPLOT3D ${DATA}/combxyz.bin ${DATA}/combq.bin)

add_test(${KIT}-ReadPLY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadPLY ${DATA}/shark.ply)

add_test(${KIT}-ReadPolyData ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadPolyData ${DATA}/Torso.vtp)

add_test(${KIT}-ReadPNM ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadPNM ${DATA}/Gourds.pnm)

add_test(${KIT}-ReadRectilinearGrid ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadRectilinearGrid ${DATA}/RectilinearGrid.vtr)

add_test(${KIT}-ReadSTL ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadSTL ${DATA}/42400-IDGH.stl)

add_test(${KIT}-ReadStructuredGrid ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadStructuredGrid ${DATA}/StructuredGrid.vts)

add_test(${KIT}-ReadPlainTextTriangles ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadPlainTextTriangles ${DATA}/Triangles.txt)

add_test(${KIT}-ReadUnknownTypeXMLFile ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadUnknownTypeXMLFile ${DATA}/Bunny.vtp)

add_test(${KIT}-ReadTIFF ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadTIFF ${DATA}/ColorCells.tif)

add_test(${KIT}-ReadTextFile ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadTextFile ${DATA}/TeapotPoints.txt)

add_test(${KIT}-ReadUnstructuredGrid ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestReadUnstructuredGrid ${DATA}/tetra.vtu)

add_test(${KIT}-SimplePointsReader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestSimplePointsReader ${DATA}/coords.txt)

add_test(${KIT}-StructuredPointsReader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestStructuredPointsReader ${DATA}/StructuredPoints.vtk)

add_test(${KIT}-StructuredGridReader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestStructuredGridReader ${DATA}/SampleStructGrid.vtk)

add_test(${KIT}-VRMLImporter ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestVRMLImporter ${DATA}/sextant.wrl -E 30)

add_test(${KIT}-VRMLImporterDemo ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestVRMLImporterDemo ${DATA}/grasshop.wrl)

add_test(${KIT}-WriteBMP ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestWriteBMP ${TEMP}/WriteBMP.bmp)

add_test(${KIT}-WritePNM ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestWritePNM ${TEMP}/WritePNM.pnm)

add_test(${KIT}-WritePLY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestWritePLY ${TEMP}/WritePLY.ply)

add_test(${KIT}-WriteSTL ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestWriteSTL ${TEMP}/WriteSTL.stl)

add_test(${KIT}-WriteTIFF ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestWriteTIFF ${TEMP}/WriteTIFF.tif)

add_test(${KIT}-WriteVTI ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestWriteVTI ${TEMP}/WriteVTI.vti)

add_test(${KIT}-WriteVTU ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
  TestWriteVTU ${TEMP}/WriteVTU.vtu)

include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)

endif()
