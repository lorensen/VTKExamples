project (${WIKI}IO)

if(NOT VTK_BINARY_DIR)
  set(VTK_LIBRARIES "")
  find_package(VTK COMPONENTS
    vtkChartsCore
    vtkCommonColor
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonSystem
    vtkCommonTransforms
    vtkDomainsChemistry
    vtkDomainsChemistryOpenGL2
    vtkFiltersCore
    vtkFiltersExtraction
    vtkFiltersGeneral
    vtkFiltersGeometry
    vtkFiltersModeling
    vtkFiltersSources
    vtkIOExodus
    vtkIOGeometry
    vtkIOImage
    vtkIOImport
    vtkIOLegacy
    vtkIOPLY
    vtkIOParallel
    vtkIOParallelXML
    vtkIOXML
    vtkImagingCore
    vtkImagingSources
    vtkInteractionImage
    vtkInteractionStyle
    vtkRenderingAnnotation
    vtkRenderingContext2D
    vtkRenderingContextOpenGL2
    vtkRenderingCore
    vtkRenderingFreeType
    vtkRenderingLOD
    vtkRenderingLabel
    vtkRenderingOpenGL2
    vtkViewsContext2D
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

Requires_GitLfs(DEMReader ALL_FILES)
Requires_GitLfs(GLTFImporter ALL_FILES)
Requires_GitLfs(ReadSLC ALL_FILES)

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
  set(KIT IO)
  set(NEEDS_ARGS
    3DSImporter
    ConvertFile
    DEMReader
    DumpXMLFile
    ExportPolyDataScene
    GenericDataObjectReader
    GLTFImporter
    ImageReader2Factory
    ImportPolyDataScene
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
    ReadAllUnstructuredGridTypes
    ReadBMP
    ReadCML
    ReadDICOM
    ReadDICOMSeries
    ReadExodusData
    ReadImageData
    ReadLegacyUnstructuredGrid
    ReadOBJ
    ReadPDB
    ReadPlainTextTriangles
    ReadPLY
    ReadPLOT3D
    ReadPNM
    ReadPolyData
    ReadRectilinearGrid
    ReadSTL
    ReadSLC
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

  add_test(${KIT}-ExportPolyDataScene ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestExportPolyDataScene ${DATA}/Bunny.vtp)

  add_test(${KIT}-ImportPolyDataScene ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestImportPolyDataScene ${DATA}/ExportBunny.vtp)

  add_test(${KIT}-GenericDataObjectReader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestGenericDataObjectReader ${DATA}/Bunny.vtp)

  if(GIT_LFS)
    add_test(${KIT}-GLTFImporter ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
      TestGLTFImporter ${DATA}/gltf/FlightHelmet/glTF/FlightHelmet.gltf)
    endif()
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

  add_test(${KIT}-ReadAllUnstructuredGridTypes ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestReadAllUnstructuredGridTypes ${DATA}/blow.vtk)

  add_test(${KIT}-ReadBMP ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestReadBMP ${DATA}/masonry.bmp)

  add_test(${KIT}-ReadCML ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestReadCML ${DATA}/porphyrin.cml)

  add_test(${KIT}-ReadDICOM ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestReadDICOM ${DATA}/prostate.img)

  add_test(${KIT}-ReadDICOMSeries ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestReadDICOMSeries ${DATA}/DICOMDirectory)

  add_test(${KIT}-ReadExodusData ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestReadExodusData ${DATA}/mug.e convected)

  add_test(${KIT}-ReadImageData ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestReadImageData ${DATA}/vase.vti)

  add_test(${KIT}-ReadLegacyUnstructuredGrid ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
    TestReadLegacyUnstructuredGrid ${DATA}/VTKCellTypes.vtk)

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

  # These tests use git large file system data
  if(GIT_LFS)
    add_test(${KIT}-DEMReader ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
      TestDEMReader ${DATA}/SainteHelens.dem)
    add_test(${KIT}-ReadSLC ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
      TestReadSLC ${DATA}/vw_knee.slc 72.0)
  endif()

  include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
endif()
