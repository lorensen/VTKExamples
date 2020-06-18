# C++ Examples

These are fully independent, compilable examples. There is significant overlap in the examples, but they are each intended to illustrate a different concept and be fully stand alone compilable.

!!! info
    [This table](/Coverage/CxxVTKClassesUsed.md) shows the VTK classes covered by the examples.

!!! info
    [This table](/Coverage/CxxVTKClassesNotUsed.md) shows VTK classes that do not have an example. Please add examples in your area of expertise!

## Hello World

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[A hello world example](/Cxx/GeometricObjects/CylinderExample) | vtkPolyDataMapper vtkActor vtkRenderer vtkRenderWindow vtkRenderWindowInteractor | Cylinder example from the VTK Textbook and source code. A hello world example.

## Simple Operations

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | -------- |
[DistanceBetweenPoints](/Cxx/SimpleOperations/DistanceBetweenPoints) | vtkMath | Distance between two points.
[DistancePointToLine](/Cxx/SimpleOperations/DistancePointToLine) | vtkLine | Distance between a point and a line.
[FloatingPointExceptions](/Cxx/SimpleOperations/FloatingPointExceptions) | vtkFloatingPointExceptions | Floating Point Exceptions
[GaussianRandomNumber](/Cxx/SimpleOperations/GaussianRandomNumber) | vtkMath | Generates Gaussian random numbers.
[PerspectiveTransform](/Cxx/SimpleOperations/PerspectiveTransform) | vtkPerspectiveTransform | Apply a perspective transformation to a point.
[ProjectPointPlane](/Cxx/SimpleOperations/ProjectPointPlane) | vtkPlane | Project a point onto a plane.
[RandomSequence](/Cxx/SimpleOperations/RandomSequence) | vtkMinimalStandardRandomSequence | This is the preferred way to generate random numbers.
[UniformRandomNumber](/Cxx/SimpleOperations/UniformRandomNumber) | vtkMath | Generates uniform random numbers.

## Input and Output

### Graph Formats

### 3D File Formats

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | -------- |
[ConvertFile](/Cxx/IO/ConvertFile) |  | Convert a file from one type to another
[XGMLReader](/Cxx/InfoVis/XGMLReader) | vtkXGMLReader | Read a .gml file

#### Standard Formats

##### Input

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[DEMReader](/Cxx/IO/DEMReader) | vtkDEMReader | Read DEM (elevation map) files
[DelimitedTextReader](/Cxx/InfoVis/DelimitedTextReader) | vtkDelimitedTextReader | Read a delimited file into a polydata.
[DumpXMLFile](/Cxx/IO/DumpXMLFile) | vtkDataSetReader | Report the contents of a VTK XML or legacy file
[IndividualVRML](/Cxx/IO/IndividualVRML) | vtkVRMLImporter | This example is used to get each actor and object from a scene and verify axes correspondence
[ParticleReader](/Cxx/IO/ParticleReader) | vtkParticleReader | This example reads ASCII files where each line consists of points with its position (x,y,z) and (optionally) one scalar or binary files in RAW 3d file format.
[ReadAllPolyDataTypes](/Cxx/IO/ReadAllPolyDataTypes) | vtkBYUReader vtkOBJReader vtkPLYReader vtkPolyDataReader vtkSTLReader vtkXMLPolyDataReader | Read any VTK polydata file.
[ReadAllPolyDataTypesDemo](/Cxx/IO/ReadAllPolyDataTypesDemo) | vtkBYUReader vtkOBJReader vtkPLYReader vtkPolyDataReader vtkSTLReader vtkXMLPolyDataReader | Read all VTK polydata file types.
[ReadAllUnstructuredGridTypes](/Cxx/IO/ReadAllUnstructuredGridTypes) | vtkXMLUnstructuredGridReader vtkUnstructuredGridReader | Read any VTK unstructuredgrid file.
[ReadCML](/Cxx/IO/ReadCML) | vtkCMLMoleculeReader | Read Chemistry Markup Language files.
[ReadExodusData](/Cxx/IO/ReadExodusData) | vtkExodusIIReader | Read and view ExodusII data.
[ReadOBJ](/Cxx/IO/ReadOBJ) | vtkOBJReader | Read an OBJ (.obj) file.
[ReadPDB](/Cxx/IO/ReadPDB) | vtkPDBReader | Read Protein Data Bank Files.
[ReadPLOT3D](/Cxx/IO/ReadPLOT3D) | vtkPLOT3DReader | Read CFD (computational fluid dynamics) data produced by PLOT3D.
[ReadPLY](/Cxx/IO/ReadPLY) | vtkPLYReader | Read PLY (.ply) files
[ReadPlainTextTriangles](/Cxx/IO/ReadPlainTextTriangles) | vtkPolyData vtkSmartPointer vtkPoints vtkCellArray vtkXMLPolyDataWriter | Read a plain text file into a polydata.
[ReadSLC](/Cxx/IO/ReadSLC) | vtkSLCReader | Read VolVis file.
[ReadSTL](/Cxx/IO/ReadSTL) | vtkSTLReader | Read stereo lithography STL (.stl) files
[ReadTextFile](/Cxx/IO/ReadTextFile) | vtkPolyData | Read a plain text file into a polydata.
[SimplePointsReader](/Cxx/IO/SimplePointsReader) | vtkSimplePointsReader | Read a simple "xyz" file of points.

###### Importers

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[3DSImporter](/Cxx/IO/3DSImporter) | vtk3DSImporter | Import a 3D Studio scene that includes multiple actors.
[GLTFImporter](/Cxx/IO/GLTFImporter) | vtkGLTFImporter | Import a glTF scene.
[ImportPolyDataScene](/Cxx/IO/ImportPolyDataScene) | vtkXMLMultiBlockDataReader vtkDataObjectTreeIterator | Import a polydata scene using multiblock datasets.
[OBJImporter](/Cxx/IO/OBJImporter) | vtkOBJImporter | Import an OBJ scene that includes actors, materials and textures.
[VRMLImporter](/Cxx/IO/VRMLImporter) | vtkVRMLImporter | Import a VRML 2.0 (WRL) file.
[VRMLImporterDemo](/Cxx/IO/VRMLImporterDemo) | vtkVRMLImporter | Import a VRML 2.0 (WRL) file and add normals if necessary.

##### Output

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[DelimitedTextWriter](/Cxx/InfoVis/DelimitedTextWriter) | vtkDelimitedTextWriter | Write data to a delimited file
[SimplePointsWriter](/Cxx/IO/SimplePointsWriter) | vtkSimplePointsWriter | Write a simple ".xyz" file
[WritePLY](/Cxx/IO/WritePLY) | vtkPLYWriter | Write PLY (.ply) files
[WriteSTL](/Cxx/IO/WriteSTL) | vtkSTLWriter | Write stereo lithography STL (.stl) files

###### Exporters

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ExportPolyDataScene](/Cxx/IO/ExportPolyDataScene) | vtkXMLMultiBlockDataWriter | Export a polydata scene using multiblock datasets.

#### VTK Formats

##### Input

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ReadImageData](/Cxx/IO/ReadImageData) | vtkXMLImageDataReader | Read a image data (.vti) file
[ReadPolyData](/Cxx/IO/ReadPolyData) | vtkXMLPolyDataReader | Read a polygonal data (.vtp) file
[ReadRectilinearGrid](/Cxx/IO/ReadRectilinearGrid) | vtkXMLRectilinearGridReader | Read a rectilinear grid (.vtr) file
[ReadStructuredGrid](/Cxx/IO/ReadStructuredGrid) | vtkXMLStructuredGridReader | Read a structured grid (.vts) file
[ReadUnknownTypeXMLFile](/Cxx/IO/ReadUnknownTypeXMLFile) | vtkXMLGenericDataObjectReader | Read an XML file and later decide what kind it is
[ReadUnstructuredGrid](/Cxx/IO/ReadUnstructuredGrid) | vtkXMLUnstructuredGridReader | Read an unstructured grid (.vtu) file

##### Output

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ExodusIIWriter](/Cxx/Parallel/ExodusIIWriter) | vtkExodusIIWriter | Write a time varying ExodusII file.
[WriteVTI](/Cxx/IO/WriteVTI) | vtkXMLImageDataWriter | Write a .vti file. VTI is an "ImageData".
[WriteVTP](/Cxx/IO/WriteVTP) | vtkXMLPolyDataWriter | Write a .vtp file. VTP is a "PolyData". This format allows for the most complex geometric objects to be stored.
[WriteVTU](/Cxx/IO/WriteVTU) | vtkXMLUnstructuredGridWriter | Write a .vtu file. VTU is an "Unstructured Grid". This format allows for 3D data to be stored.
[XMLPImageDataWriter](/Cxx/IO/XMLPImageDataWriter) | vtkXMLPImageDataWriter | Write a .pvti file with 4 .vti pieces.
[XMLPUnstructuredGridWriter](/Cxx/IO/XMLPUnstructuredGridWriter) | vtkXMLPUnstructuredGridWriter | Write a .pvtu with 4 .vtu pieces.
[XMLStructuredGridWriter](/Cxx/IO/XMLStructuredGridWriter) | vtkXMLStructuredGridWriter | Write a .vts file from a vtkStructuredGrid.

#### Legacy VTK Formats

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[GenericDataObjectReader](/Cxx/IO/GenericDataObjectReader) | vtkGenericDataObjectReader | Read any type of legacy .vtk file.
[ReadLegacyUnstructuredGrid](/Cxx/IO/ReadLegacyUnstructuredGrid) | vtkUnstructuredGridReader | Read an unstructured grid that contains 11 linear cells.
[StructuredGridReader](/Cxx/IO/StructuredGridReader) | vtkStructuredGridReader | Read a structured grid (.vtk) file.
[StructuredPointsReader](/Cxx/IO/StructuredPointsReader) | vtkStructuredPointsReader | Read a structured points (.vtk) file.
[WriteLegacyLinearCells](/Cxx/IO/WriteLegacyLinearCells) | vtkUnstructuredGridWriter | Write each linear cell into a legacy UnstructuredGrid file.
[WriteXMLLinearCells](/Cxx/IO/WriteXMLLinearCells) | vtkXMLDataSetWriter | Write each linear cell into an XML UnstructuredGrid file (.vtu).

### Image Format

#### Input

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ImageReader2Factory](/Cxx/IO/ImageReader2Factory) | vtkImageReader2Factory | This class tries to find an appropriate reader. It is very convenient to use this when you don't know what kind of file to expect.
[JPEGReader](/Cxx/IO/JPEGReader) | vtkJPEGReader | Read a JPEG image.
[MetaImageReader](/Cxx/IO/MetaImageReader) | vtkMetaImageReader | Read .mha files.
[PNGReader](/Cxx/IO/PNGReader) | vtkPNGReader | Read a PNG image.
[ReadBMP](/Cxx/IO/ReadBMP) | vtkBMPReader | Read BMP (.bmp) files.
[ReadDICOM](/Cxx/IO/ReadDICOM) | vtkDICOMImageReader | Read DICOM file
[ReadDICOMSeries](/Cxx/IO/ReadDICOMSeries) | vtkDICOMImageReader | This example demonstrates how to read a series of DICOM images and scroll through slices
[ReadPNM](/Cxx/IO/ReadPNM) | vtkPNMReader | Read PNM (.pnm) files.
[ReadTIFF](/Cxx/IO/ReadTIFF) | vtkTIFFReader | Read TIFF (.tif) files.

#### Output

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ImageWriter](/Cxx/IO/ImageWriter) | vtkBMPWriter vtkJPEGWriter vtkPNMWriter vtkPostScriptWriter vtkTIFFWriter vtkPNGWriter vtkWindowToImageFilter | Write an imagefile based on the file extension.
[JPEGWriter](/Cxx/IO/JPEGWriter) | vtkJPEGWriter | Write a JPEG (.jpg) file.
[MetaImageWriter](/Cxx/IO/MetaImageWriter) | vtkMetaImageWriter | Write a .mha/.mhd + .raw file.
[PNGWriter](/Cxx/IO/PNGWriter) | vtkPNGWriter | Write a PNG (.png) file.
[WriteBMP](/Cxx/IO/WriteBMP) | vtkBMPWriter | Write a BMP (.bmp) file.
[WritePNM](/Cxx/IO/WritePNM) | vtkPNMWriter | Write a PNM (.pnm) file.
[WriteTIFF](/Cxx/IO/WriteTIFF) | vtkTIFFWriter | Write a TIFF (.tif) file.

## Geometric Objects

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Axes](/Cxx/GeometricObjects/Axes) | vtkAxesActor |
[ColoredLines](/Cxx/GeometricObjects/ColoredLines) | vtkCellData vtkLine |
[Cube](/Cxx/GeometricObjects/Cube) | vtkPolyData | Manually build a polygonal cube.
[Cube1](/Cxx/GeometricObjects/Cube1) | vtkCubeSource | A nice simple example that demonstrates the operation of the VTK pipeline.
[Dodecahedron](/Cxx/GeometricObjects/Dodecahedron) | vtkPolyhedron | Create a dodecahedron using vtkPolyhedron.
[EllipticalCylinder](/Cxx/GeometricObjects/EllipticalCylinder) | vtkLinearExtrusionFilter | Create an elliptical cylinder using extrusion.
[EllipticalCylinderDemo](/Cxx/GeometricObjects/EllipticalCylinderDemo) | vtkLinearExtrusionFilter | Show the base and extrusion vector.
[GeometricObjectsDemo](/Cxx/GeometricObjects/GeometricObjectsDemo) |  | A demonstration of all geometric objects that work the same way.
[OpenVRFrustm](/Cxx/GeometricObjects/OpenVRFrustm) |  | VTK + OpenVR Example.
[OpenVROrientedArrow](/Cxx/GeometricObjects/OpenVROrientedArrow) |  | VTK + OpenVR Example.
[OpenVROrientedCylinder](/Cxx/GeometricObjects/OpenVROrientedCylinder) |  | VTK + OpenVR Example.
[OpenVRTessellatedBoxSource](/Cxx/GeometricObjects/OpenVRTessellatedBoxSource) |  | VTK + OpenVR Example.
[Planes](/Cxx/GeometricObjects/Planes) | vtkPlanes |
[PlanesIntersection](/Cxx/GeometricObjects/PlanesIntersection) | vtkPlanesIntersection |
[PlaneSourceDemo](/Cxx/GeometricObjects/PlaneSourceDemo) | vtkPlaneSource | Display the instance variables that define a vtkPlaneSource.
[PolygonIntersection](/Cxx/GeometricObjects/PolygonIntersection) | vtkPolygon | Compute the intersection of a line segment with a polygon.
[ShrinkCube](/Cxx/GeometricObjects/ShrinkCube) | vtkCubeSource | Applying shrink filter to an object.
[SourceObjectsDemo](/Cxx/GeometricObjects/SourceObjectsDemo) | vtkSphereSource vtkConeSource vtkCylinderSource vtkCubeSource vtkPlaneSource vtkTextSource vtkPointSource vtkDiskSource vtkLineSource | Examples of source objects that procedurally generate polygonal models.  These nine images represent just some of the capability of VTK. From upper left in reading order: sphere, cone, cylinder, cube, plane, text, random point cloud, disk (with or without hole), and line source. Other polygonal source objects are available; check subclasses of vtkPolyDataAlgorithm.

### Cells

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Cell3DDemonstration](/Cxx/GeometricObjects/Cell3DDemonstration) | vtkHexagonalPrism vtkHexahedron vtkPentagonalPrism  vtkPolyhedron vtkPyramid vtkTetra vtkVoxel vtkWedge vtkUnstructuredGrid | Demonstrate the use of vtkCell3D to construct geometric objects. Sample objects are generated from the classes derived from vtkCell3D and displayed.
[CellTypeSource](/Cxx/GeometricObjects/CellTypeSource) | vtkCellTypeSource vtkTessellatorFilter | Generate tessellated cells.
[ConvexPointSet](/Cxx/GeometricObjects/ConvexPointSet) | vtkConvexPointSet | Generate a ConvexPointSetCell.
[Hexahedron](/Cxx/GeometricObjects/Hexahedron) | vtkHexahedron |
[LinearCellDemo](/Cxx/GeometricObjects/LinearCellDemo) | vtkCell vtkCell3D | Linear cell types in VTK.
[LongLine](/Cxx/GeometricObjects/LongLine) | vtkLine | Manually create a polyline.
[Point](/Cxx/GeometricObjects/Point) | vtkPoints |
[PolyLine](/Cxx/GeometricObjects/PolyLine) | vtkPolyLine |
[Polygon](/Cxx/GeometricObjects/Polygon) | vtkPolygon |
[Polyhedron](/Cxx/GeometricObjects/Polyhedron) |  | Create an unstructured grid representation of a polyhedron (cube) and write it out to a file.
[Pyramid](/Cxx/GeometricObjects/Pyramid) | vtkPyramid |
[Quad](/Cxx/GeometricObjects/Quad) | vtkQuad |
[Tetrahedron](/Cxx/GeometricObjects/Tetrahedron) | vtkTetra |
[Triangle](/Cxx/GeometricObjects/Triangle) | vtkTriangle |
[Triangle strip](/Cxx/GeometricObjects/TriangleStrip) | vtkTriangleStrip |
[Vertex](/Cxx/GeometricObjects/Vertex) | vtkVertex |

### Sources

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Arrow](/Cxx/GeometricObjects/Arrow) | vtkArrowSource |
[Cone](/Cxx/GeometricObjects/Cone) | vtkConeSource | Display a cone
[ConeDemo](/Cxx/GeometricObjects/ConeDemo) | vtkConeSource | Disolay four different resolution cones.
[Cylinder](/Cxx/GeometricObjects/Cylinder) | vtkCylinderSource |
[Disk](/Cxx/GeometricObjects/Disk) | vtkDiskSource | A circle with a hole in it.
[Frustum](/Cxx/GeometricObjects/Frustum) | vtkFrustumSource |
[Line](/Cxx/GeometricObjects/Line) | vtkLineSource |
[OrientedArrow](/Cxx/GeometricObjects/OrientedArrow) | vtkArrowSource | Orient an arrow along an arbitrary vector.
[OrientedCylinder](/Cxx/GeometricObjects/OrientedCylinder) | vtkCylinderSource | Orient a cylinder along an arbitrary vector.
[Plane](/Cxx/GeometricObjects/Plane) | vtkPlaneSource |
[PlatonicSolids](/Cxx/GeometricObjects/PlatonicSolids) | vtkPlatonicSolidSource |
[PolyLine1](/Cxx/GeometricObjects/PolyLine1) | vtkPolyLine | This example demonstrates how to create a polygon through several ordered points.
[RegularPolygonSource](/Cxx/GeometricObjects/RegularPolygonSource) | vtkRegularPolygonSource |
[Sphere](/Cxx/GeometricObjects/Sphere) | vtkSphereSource |
[TessellatedBoxSource](/Cxx/GeometricObjects/TessellatedBoxSource) | vtkTessellatedBoxSource | Generate a box with tessellated sides.
[TextActor](/Cxx/GeometricObjects/TextActor) | vtkTextActor | 2D "HUD-type" text

### Non Linear

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[IsoparametricCellsDemo](/Cxx/GeometricObjects/IsoparametricCellsDemo) | vtkNonLinearCell | Nonlinear isoparametric cell types in VTK.
[QuadraticHexahedron](/Cxx/GeometricObjects/QuadraticHexahedron) | vtkQuadraticHexahedron vtkTessellatorFilter | Create and tessellate a nonlinear cell.
[QuadraticHexahedronDemo](/Cxx/GeometricObjects/QuadraticHexahedronDemo) | vtkQuadraticHexahedron vtkTessellatorFilter | Interactively adjust chord error.
[QuadraticTetra](/Cxx/GeometricObjects/QuadraticTetra) | vtkQuadraticTetra vtkTessellatorFilter | Create and tessellate a nonlinear cell.
[QuadraticTetraDemo](/Cxx/GeometricObjects/QuadraticTetraDemo) | vtkQuadraticTetra vtkTessellatorFilter | Interactively adjust chord error.

### Parametric Objects

These examples demonstrate how to create an display one of the many vtkParametric objects. All of the classes listed can be used in an identical fashion.

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ParametricKuenDemo](/Cxx/GeometricObjects/ParametricKuenDemo) | vtkParametricKuen | Interactively change the parameters for a Kuen Surface.
[ParametricObjectsDemo](/Cxx/GeometricObjects/ParametricObjectsDemo) |  | Demonstrates the Parametric classes added by Andrew Maclean and additional classes added by Tim Meehan. The parametric spline is also included. Options are provided to display single objects, add backface, add normals and print out an image.
[ParametricSuperEllipsoidDemo](/Cxx/GeometricObjects/ParametricSuperEllipsoidDemo) | vtkParametricSuperEllipsoid | Interactively change the parameters for a SuperEllipsoid Surface.
[ParametricSuperToroidDemo](/Cxx/GeometricObjects/ParametricSuperToroidDemo) | vtkParametricSuperToroid | Interactively change the parameters for a SuperToroid Surface.

## Implicit Functions and Iso-surfaces

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[BandedPolyDataContourFilter](/Cxx/VisualizationAlgorithms/BandedPolyDataContourFilter) | vtkBandedPolyDataContourFilter | Create filled contours.
[BooleanOperationImplicitFunctions](/Cxx/ImplicitFunctions/BooleanOperationImplicitFunctions) | vtkImplicitBoolean | Demonstrate booleans of two different implicit functions
[ContourTriangulator](/Cxx/Modelling/ContourTriangulator) | vtkMarchingSquares vtkContourTriangulator | Create a contour from a structured point set (image) and triangulate it.
[CutWithCutFunction](/Cxx/VisualizationAlgorithms/CutWithCutFunction) | vtkCutter | Cut a surface with an implicit plane using vtkCutter.
[CutWithScalars](/Cxx/VisualizationAlgorithms/CutWithScalars) | vtkContourFilter | Cut a surface with scalars.
[DiscreteMarchingCubes](/Cxx/Modelling/DiscreteMarchingCubes) | vtkDiscreteMarchingCubes | Generate surfaces from labeled data.
[ExtractData](/Cxx/VisualizationAlgorithms/ExtractData) | vtkSampleFunction | Implicit functions used to select data: Two ellipsoids are combined using the union operation used to select voxels from a volume. Voxels are shrunk 50 percent.
[ExtractLargestIsosurface](/Cxx/Modelling/ExtractLargestIsosurface) | vtkPolyDataConnectivityFilter | Extract largest isosurface.
[FilledContours](/Cxx/VisualizationAlgorithms/FilledContours) | vtkContourFilter | Create filled contours (using vtkClipPolyData).
[Hello](/Cxx/VisualizationAlgorithms/Hello) | vtkImplicitModeller | Implicit modelling used to thicken a stroked font.
[IceCream](/Cxx/VisualizationAlgorithms/IceCream) | vtkImplicitBoolean vtkSampleFunction | How to use boolean combinations of implicit functions to create a model of an ice cream cone.
[ImplicitDataSet](/Cxx/ImplicitFunctions/ImplicitDataSet) | vtkImplicitDataSet | Convert an imagedata to an implicit function.
[ImplicitSphere](/Cxx/ImplicitFunctions/ImplicitSphere) | vtkSphere | An implicit representation of a sphere.
[IsoContours](/Cxx/ImplicitFunctions/IsoContours) | vtkContourFunction | Visualize different isocontours using a slider.
[Lorenz](/Cxx/Visualization/Lorenz) | vtkContourFilter | Visualizing a Lorenz strange attractor by integrating the Lorenz equations in a volume.
[MarchingCases](/Cxx/VisualizationAlgorithms/MarchingCases) | vtkMarchingCubes | Explore the Marching Cubes cases.
[MarchingCasesA](/Cxx/VisualizationAlgorithms/MarchingCasesA) | vtkMarchingCubes | The 256 possible cases have been reduced to 15 cases using symmetry.
[MarchingCasesB](/Cxx/VisualizationAlgorithms/MarchingCasesB) | vtkMarchingCubes | Marching cubes complementary cases. Cases 3c, 6c, 7c, 10c, 12c and 13c are displayed.
[MarchingCasesC](/Cxx/VisualizationAlgorithms/MarchingCasesC) | vtkMarchingCubes | Marching cubes, case 3 is rotated 90 degrees about the y-axis with no label.
[MarchingCasesD](/Cxx/VisualizationAlgorithms/MarchingCasesD) | vtkMarchingCubes | Marching cubes. Case 7 is rotated 180 degrees about the y-axis with no label.
[MarchingCubes](/Cxx/Modelling/MarchingCubes) | vtkMarchingCubes | Create a voxelized sphere.
[MarchingSquares](/Cxx/Modelling/MarchingSquares) | vtkMarchingSquares | Create a contour from a structured point set (image).
[ImplicitQuadric](/Cxx/ImplicitFunctions/ImplicitQuadric | vtkQuadric | Create an ellipsoid using an implicit quadric.
[SampleFunction](/Cxx/ImplicitFunctions/SampleFunction) | vtkSampleFunction | Sample and visualize an implicit function.
[ShepardInterpolation](/Cxx/Visualization/ShepardInterpolation) | vtkShepardMethod vtkProbeFilter vtkContourFilter | Interpolate scalar data.
[SmoothDiscreteMarchingCubes](/Cxx/Modelling/SmoothDiscreteMarchingCubes) | vtkDiscreteMarchingCubes vtkWindowedSincPolyDataFilter | Generate smooth surfaces from labeled data.
[ImplicitSphere1](/Cxx/ImplicitFunctions/ImplicitSphere1) | vtkSphere | Demonstrate sampling of a sphere implicit function.

## Working with 3D Data

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[AlignTwoPolyDatas](/Cxx/PolyData/AlignTwoPolyDatas) | vtkIterativeClosestPointTransform vtkLandmarkTransform vtkHausdorffDistancePointSetFilter | Align two vtkPolyData's.
[AlignFrames](/Cxx/PolyData/AlignFrames) | vtkLandmarkTransform | Align coordinate frames.
[AppendFilter](/Cxx/Filtering/AppendFilter) | vtkAppendFilter | Append different types of data,
[BooleanOperationPolyDataFilter](/Cxx/PolyData/BooleanOperationPolyDataFilter) | vtkBoleanOperationPolyDataFilter | Perform boolean operations on two vtkPolyData objects.
[Bottle](/Cxx/Modelling/Bottle) | vtkRotationalExtrusionFilter | Rotationally symmetric objects.
[CappedSphere](/Cxx/Modelling/CappedSphere) | vtkRotationalExtrusionFilter | Rotate an arc to create a capped sphere.
[CellCenters](/Cxx/PolyData/CellCenters) | vtkCellCenters | Compute points at the center of every cell.
[CellCentersDemo](/Cxx/PolyData/CellCentersDemo) | vtkCellCenters vtkGlyph3DMapper | Visualize points at the center of every cell.
[CellEdgeNeighbors](/Cxx/PolyData/CellEdgeNeighbors) | vtkPolyData::GetCellNeighbors | Determine which cells share an edge with a specific cell.
[CellPointNeighbors](/Cxx/PolyData/CellPointNeighbors) | vtkPolyData::GetCellNeighbors | Determine which cells share a single point with a specific cell.
[CellsInsideObject](/Cxx/PolyData/CellsInsideObject) | vtkSelectEnclosedPoints vtkMultiThreshold | Extract cells inside a closed surface.
[CenterOfMass](/Cxx/PolyData/CenterOfMass) | vtkCenterOfMass | Compute the center of mass of the points.
[Circle](/Cxx/GeometricObjects/Circle) | vtkCutter | Create a circle by cutting through a sphere.
[CleanPolyData](/Cxx/PolyData/CleanPolyData) | vtkCleanPolyData | Remove coincident points.
[ColorCells](/Cxx/PolyData/ColorCells) | vtkLookupTable | Color individual cells of a polydata with scalar index.
[ColorCellsWithRGB](/Cxx/PolyData/ColorCellsWithRGB) | vtkCellData | Color individual cells of a polydata with rgb colors.
[ColoredPoints](/Cxx/PolyData/ColoredPoints) | vtkUnsignedCharArray | Add three points to a polydata and associate a color with each of them.
[CombinePolyData](/Cxx/Filtering/CombinePolyData) | vtkAppendPolyData | Combine/Append PolyData.
[ConnectivityFilter](/Cxx/Filtering/ConnectivityFilter) | vtkConnectivityFilter | Color any dataset type based on connectivity.
[ConnectivityFilterDemo](/Cxx/Filtering/ConnectivityFilterDemo) | vtkPolyDataConnectivityFilter | Color any dataset type based on connectivity.
[ContoursFromPolyData](/Cxx/Filtering/ContoursFromPolyData) | vtkCutter | Create contours from PolyData.
[ContoursToSurface](/Cxx/PolyData/ContoursToSurface) | vtkVoxelContoursToSurfaceFilter | Convert contours to a surface.
[ConvexHull](/Cxx/PolyData/ConvexHull) | vtkHull | Convex hull using vtkHull.
[ConvexHullShrinkWrap](/Cxx/PolyData/ConvexHullShrinkWrap) | vtkSmoothPolyDataFilter | Convex hull using shrink wrapping.
[CopyAllArrays](/Cxx/PolyData/CopyAllArrays) | vtkPolyData | Copy all arrays from one vtkPolyData to another.
[CurvaturesDemo](/Cxx/PolyData/CurvaturesDemo) | vtkCurvatures  vtkColorTransferFunction | Demonstrates how to get the Gaussian and Mean curvatures of a surface.
[DataBounds](/Cxx/PolyData/DataBounds) | vtkPolyData::GetBounds | Get the minimum and maximum value in each dimension. (Axis aligned bounding box)
[DataSetSurfaceFilter](/Cxx/PolyData/DataSetSurfaceFilter) | vtkDataSetSurfaceFilter | Convert vtkUnstructuredGrid to vtkPolyData.
[DecimatePolyline](/Cxx/PolyData/DecimatePolyline) | vtkDecimatePolylineFilter | Decimate polyline.
[DeleteCells](/Cxx/PolyData/DeleteCells) | vtkPolyData | Delete a cell from a vtkPolyData
[DeletePoint](/Cxx/PolyData/DeletePoint) | vtkPoints vtkPolyData |
[DetermineArrayDataTypes](/Cxx/PolyData/DetermineArrayDataTypes) | vtkPolyData | Determine data types of arrays.
[DistancePolyDataFilter](/Cxx/PolyData/DistancePolyDataFilter) | vtkDistancePolyDataFilter | Compute the distance function from one vtkPolyData to another.
[EmbedPointsIntoVolume](/Cxx/PolyData/EmbedPointsIntoVolume) | vtkGaussianSplatter | Embed points into a volume.
[ExternalContour](/Cxx/PolyData/ExternalContour) | vtkWindowToImageFilter vtkContourFilter | Get the External Contour from Polydata.
[ExtractCellsUsingPoints](/Cxx/PolyData/ExtractCellsUsingPoints) | vtkExtractSelection vtkSelection vtkSelectionNode | Extract points but bring cells that are still complete with them.
[ExtractOutsideSurface](/Cxx/PolyData/ExtractOutsideSurface) | vtkPolyDataConnectivityFilter | Extract the outer surface of a multiple surface polydata.
[ExtractPolyLinesFromPolyData](/Cxx/PolyData/ExtractPolyLinesFromPolyData) | vtkPolyData | Extract polylines from polydata.
[ExtractSelectedIds](/Cxx/PolyData/ExtractSelectedIds) | vtkExtractSelectedIds | Extract selected points.
[ExtractSelection](/Cxx/PolyData/ExtractSelection) | vtkExtractSelection | Extract selection points.
[ExtractSelectionCells](/Cxx/PolyData/ExtractSelectionCells) | vtkExtractSelection | Extract selection cells.
[ExtractSelectionOriginalId](/Cxx/PolyData/ExtractSelectionOriginalId) | vtkExtractSelection | Extract selection and find correspondence between new and original Id.
[ExtractVisibleCells](/Cxx/Filtering/ExtractVisibleCells) | vtkHardwareSelector | Extract and highlight visible cells.
[FieldData](/Cxx/PolyData/FieldData) | vtkFieldData | Add Global Miscellaneous Data (FieldData) to a Polydata.
[Finance](/Cxx/Modelling/Finance) | vtkGaussianSplatter | Visualization of multidimensional financial data. The gray/wireframe surface represents the total data population. The red surface represents data points delinquent on loan payment.
[FinanceFieldData](/Cxx/Modelling/FinanceFieldData) | vtkGaussianSplatter | Visualization of multidimensional financial data. The yellow surface represents the total data population. The red surface represents data points delinquent on loan payment.
[FindAllArrayNames](/Cxx/IO/FindAllArrayNames) | vtkPolyData | Get the names of all of the data arrays.
[FitSplineToCutterOutput](/Cxx/PolyData/FitSplineToCutterOutput) | vtkKochanekSpline vtkSplineFilter vtkSpline | Fit a spline to cutter output.
[GeometryFilter](/Cxx/PolyData/GeometryFilter) | vtkGeometryFilter | Convert vtkUnstructuredGrid to vtkPolyData (another way).
[GetMiscCellData](/Cxx/PolyData/GetMiscCellData) | vtkCellData | Get Miscellaneous Data from Cells in a Polydata.
[GetMiscPointData](/Cxx/PolyData/GetMiscPointData) | vtkDoubleArray | Get Miscellaneous Data from Points in a Polydata.
[GradientFilter](/Cxx/PolyData/GradientFilter) | vtkGradientFilter | Compute the gradient of a scalar field on a data set.
[ImplicitBoolean](/Cxx/Filtering/ImplicitBoolean) | vtkImplicitBoolean | Operations include intersection and union.
[ImplicitBooleanDemo](/Cxx/Filtering/ImplicitBooleanDemo) | vtkImplicitBoolean | Demo Union, Difference and Intersection.
[ImplicitModeller](/Cxx/PolyData/ImplicitModeller) | vtkImplicitModeller | Compute the distance from an object to every point on a uniform grid.
[ImplicitPolyDataDistance](/Cxx/PolyData/ImplicitPolyDataDistance) | vtkImplicitPolyDataDistance | Compute the distance function in a space around a vtkPolyData.
[InterpolateMeshOnGrid](/Cxx/PolyData/InterpolateMeshOnGrid) | vtkProbeFilter | Interpolate a mesh over a grid.
[InterpolateTerrain](/Cxx/PolyData/InterpolateTerrain) | vtkProbeFilter | vtkProbeFilter Interpolate terrain.
[IntersectionPolyDataFilter](/Cxx/PolyData/IntersectionPolyDataFilter) | vtkIntersectionPolyDataFilter | Compute the intersection of two vtkPolyData objects.
[IterateOverLines](/Cxx/PolyData/IterateOverLines) | vtkCellArray | Iterate through the lines of a PolyData.
[KMeansClustering](/Cxx/InfoVis/KMeansClustering) | vtkKMeansStatistics | KMeans Clustering
[KochanekSpline](/Cxx/PolyData/KochanekSpline) | vtkKochanekSpline | Create an Kochanek spline on a set of points.
[KochanekSplineDemo](/Cxx/PolyData/KochanekSplineDemo) | vtkKochanekSpline | Interactively change the parameters of the Kochanek spline.
[LinearExtrusion](/Cxx/PolyData/LinearExtrusion) | vtkLinearExtrusionFilter | Extrude a shape.
[LoopBooleanPolyDataFilter](/Cxx/PolyData/LoopBooleanPolyDataFilter) | vtkLoopBooleanOpPolyDataFilter | Perform boolean operations on two vtkPolyData objects.
[MaskPoints](/Cxx/PolyData/MaskPoints) | vtkMaskPoints | Select a subset (mask) of a point set.
[MergePoints](/Cxx/PolyData/MergePoints) | vtkMergePoints | Remove duplicate (merge) points.
[MergeSelections](/Cxx/PolyData/MergeSelections) | vtkSelection  vtkSelectionNode | Merge selected points.
[MiscCellData](/Cxx/PolyData/MiscCellData) | vtkCellData | Add Miscellaneous Data to Cells in a Polydata.
[MiscPointData](/Cxx/PolyData/MiscPointData) | vtkPointData vtkFloatArray | Add Miscellaneous Data to Points in a Polydata.
[MultiBlockMergeFilter](/Cxx/PolyData/MultiBlockMergeFilter) | vtkMultiBlockMergeFilter vtkMultiBlockDataSet | Combine MultiBlockDataSets.
[NullPoint](/Cxx/PolyData/NullPoint) | vtkPointData | Set everything in PointData at a specified index to NULL
[Outline](/Cxx/PolyData/Outline) | vtkOutlineFilter | Draw the bounding box of the data
[PKMeansClustering](/Cxx/InfoVis/PKMeansClustering) | vtkPKMeansStatistics | Parallel KMeans Clustering.
[ParametricSpline](/Cxx/PolyData/ParametricSpline) | vtkCardinalSpline vtkParametricSpline vtkParametricFunctionSource | Create a Cardinal spline on a set of points.
[PerlinNoise](/Cxx/Filtering/PerlinNoise) | vtkPerlinNoise |
[PointCellIds](/Cxx/PolyData/PointCellIds) | vtkIdFilter | Generate point and cell id arrays.
[PointInsideObject](/Cxx/PolyData/PointInsideObject) | vtkSelectEnclosedPoints | Check if a point is inside an object.
[PointInsideObject2](/Cxx/PolyData/PointInsideObject2) | vtkDelaunay3D vtkPolyData::FindCell | This uses a Delaunay triangulation to compute a volume. This gives more of an "is inside convex hull" effect than an "is inside object".
[PointsProjectedHull](/Cxx/PolyData/PointsProjectedHull) | vtkPointsProjectedHull | Convex hull of points projected onto the coordinate planes.
[PolyDataCellNormals](/Cxx/PolyData/PolyDataCellNormals) | vtkCellData | Add/Get Normals to/from cells in a Polydata.
[PolyDataContourToImageData](/Cxx/PolyData/PolyDataContourToImageData) | vtkLinearExtrusionFilter vtkPolyDataToImageStencil | Generate a binarized image from a closed contour.
[PolyDataExtractNormals](/Cxx/PolyData/PolyDataExtractNormals) | vtkPolyDataNormals | Extract Normals from a Polydata.
[PolyDataGetPoint](/Cxx/PolyData/PolyDataGetPoint) | vtkPolyData | Get point locations/coordinates from a vtkPolyData.
[PolyDataIsoLines](/Cxx/PolyData/PolyDataIsoLines) | vtkBandedPolyDataContourFilter | Iso lines on the surface of a polydata
[PolyDataPointNormals](/Cxx/PolyData/PolyDataPointNormals) | vtkPointData | Add/Get Normals to/from points in a Polydata.
[PolyDataPointSampler](/Cxx/PolyData/PolyDataPointSampler) | vtkPolyDataPointSampler | Sample the edges or surfaces of a polydata.
[PolyDataToImageData](/Cxx/PolyData/PolyDataToImageData) | vtkPolyDataToImageStencil | Generate a binarized volume from a closed surface.
[ProcrustesAlignmentFilter](/Cxx/PolyData/ProcrustesAlignmentFilter) | vtkProcrustesAlignmentFilter | Align point sets.
[ProgrammableFilter](/Cxx/Filtering/ProgrammableFilter) | vtkProgrammableFilter | Create a custom filter without subclassing.
[ProgrammableSource](/Cxx/Filtering/ProgrammableSource) | vtkProgrammableSource | Create points using a programmable source. Generates points for a strange attractor.
[ProjectSphere](/Cxx/Visualization/ProjectSphere) | vtkProjectSphereFilter | Unroll a sphere or spherical-like model.
[QuantizePolyDataPoints](/Cxx/PolyData/QuantizePolyDataPoints) | vtkQuantizePolyDataPoints | Snap (quantize) points to a grid.
[Reflection](/Cxx/PolyData/Reflection) | vtkReflectionFilter | Mirror a DataSet.
[RemoveOutsideSurface](/Cxx/PolyData/RemoveOutsideSurface) | vtkConnectivityFilter | Remove the outer surface of a multiple surface polydata.
[RemoveVertices](/Cxx/PolyData/RemoveVertices) |  |
[ResampleAppendedPolyData](/Cxx/PolyData/ResampleAppendedPolyData) | vtkCellLocator vtkPlaneSource vtkAppendPolyData | Resample a flat terrain containing multiple objects.
[ResamplePolyLine](/Cxx/PolyData/ResamplePolyLine) |  |
[ReverseSense](/Cxx/PolyData/ReverseSense) | vtkReverseSense | Flip normals.
[RibbonFilter](/Cxx/PolyData/RibbonFilter) | vtkRibbonFilter |
[RotationAroundLine](/Cxx/PolyData/RotationAroundLine) | vtkTransform vtkTransformPolyDataFilter | Rotation around a line.
[RuledSurfaceFilter](/Cxx/PolyData/RuledSurfaceFilter) | vtkRuledSurfaceFilter | Create a surface between lines.
[SCurveSpline](/Cxx/InfoVis/SCurveSpline) | vtkSCurveSpline | Create an SCurve spline on a set of points.
[SelectVisiblePoints](/Cxx/PolyData/SelectVisiblePoints) | vtkSelectVisiblePoints | Select visible points.
[SelectionSource](/Cxx/Filtering/SelectionSource) | vtkSelectionSource vtkExtractSelection | Specify a selection.
[ShrinkPolyData](/Cxx/PolyData/ShrinkPolyData) | vtkShrinkPolyData | Move all items in a PolyData towards their centroid.
[Silhouette](/Cxx/PolyData/Silhouette) | vtkPolyDataSilhouette |
[Spring](/Cxx/Modelling/Spring) | vtkRotationalExtrusionFilter | Rotation in combination with linear displacement and radius variation.
[Stripper](/Cxx/PolyData/Stripper) | vtkStripper | Convert triangles to triangle strips.
[ThinPlateSplineTransform](/Cxx/PolyData/ThinPlateSplineTransform) | vtkThinPlateSplineTransform |
[ThresholdCells](/Cxx/PolyData/ThresholdCells) | vtkThreshold | Thresholding Cells.
[ThresholdPoints](/Cxx/PolyData/ThresholdPoints) | vtkThresholdPoints | Thresholding Points.
[TransformFilter](/Cxx/PolyData/TransformFilter) | vtkTransformFilter | Transform a data set.
[TransformOrderDemo](/Cxx/PolyData/TransformOrderDemo) | vtkTransformPolyDataFilter | Demonstrate how the order of applying transforms affects the result.
[TransformPipeline](/Cxx/PolyData/TransformPipeline) | vtkTransform | Combining the transformation, in order to manipulate a group of vtkActor. Shown in the example robot arm motion.
[TransformPolyData](/Cxx/Filtering/TransformPolyData) | vtkTransformPolyDataFilter | Apply a Transformation to a PolyData.
[TriangleArea](/Cxx/PolyData/TriangleArea) | vtkTriangle::TriangleArea | Compute the area of all triangles in a polydata.
[TriangleColoredPoints](/Cxx/PolyData/TriangleColoredPoints) | vtkUnsignedCharArray | Set the color of each point of a triangle. You will be able to interpolate the colors across the triangle.
[TriangleSolidColor](/Cxx/PolyData/TriangleSolidColor) | vtkUnsignedCharArray | Create a solid colored triangle.
[TubeFilter](/Cxx/PolyData/TubeFilter) | vtkTubeFilter | Give lines a thickness (produce a cylinder around lines.
[VectorFieldNonZeroExtraction](/Cxx/Filtering/VectorFieldNonZeroExtraction) | vtkExtractSelectedThresholds | Extract non-zero vectors from a vtkImageData.
[VertexConnectivity](/Cxx/PolyData/VertexConnectivity) | vtkPolyData::GetCellPoints | Get a list of vertices attached (through an edge) to a vertex.
[WarpScalar](/Cxx/PolyData/WarpScalar) | vtkWarpScalar | Move vertices along normals.
[WarpSurface](/Cxx/PolyData/WarpSurface) | vtkWarpVector | Warp a surface along its normal.
[WarpTo](/Cxx/Filtering/WarpTo) | vtkWarpTo | Bend an object.
[WarpVector](/Cxx/PolyData/WarpVector) | vtkWarpVector |

### Data Types

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[CompositePolyDataMapper](/Cxx/CompositeData/CompositePolyDataMapper) | vtkCompositePolyDataMapper |
[Generate2DAMRDataSetWithPulse](/Cxx/CompositeData/Generate2DAMRDataSetWithPulse) | vtkAMRBox vtkOverlappingAMR vtkUniformGrid vtkXMLHierarchicalBoxDataSetWriter | Generates sample 2-D AMR dataset.
[Generate3DAMRDataSetWithPulse](/Cxx/CompositeData/Generate3DAMRDataSetWithPulse) | vtkAMRBox vtkOverlappingAMR vtkUniformGrid vtkXMLHierarchicalBoxDataSetWriter | Generates sample 3-D AMR dataset.
[HierarchicalBoxPipeline](/Cxx/CompositeData/HierarchicalBoxPipeline) | vtkHierarchicalBoxDataSet | Demonstrates how hierarchical box (uniform rectilinear) AMR datasets can be processed using the new vtkHierarchicalBoxDataSet class.
[MultiBlockDataSet](/Cxx/CompositeData/MultiBlockDataSet) | vtkMultiBlockDataSet | Demonstrates how to make and use VTK's MultiBlock type data
[OverlappingAMR](/Cxx/CompositeData/OverlappingAMR) | vtkOverlappingAMR | Demonstrates how to create and populate a VTK's Overlapping AMR Grid type Data

### Data Type Conversions

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[PolyDataToUnstructuredGrid](/Cxx/PolyData/PolyDataToUnstructuredGrid) | vtkAppendFilter | Convert a vtkPolyData to a vtkUnstructuredGrid.

### Point Cloud Operations

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ColorIsosurface](/Cxx/VisualizationAlgorithms/ColorIsosurface) | vtkPolyDataMapper | Color an isosurcae with and Array Component.
[CompareExtractSurface](/Cxx/Points/CompareExtractSurface) | vtkExractSurface | Compare three extract surface algorithms.
[DensifyPoints](/Cxx/Points/DensifyPoints) | vtkDensifyPointCloudFilter | Add points to a point cloud.
[DownsamplePointCloud](/Cxx/PolyData/DownsamplePointCloud) | vtkCleanPolyData | Down sample a point cloud. Remove points so that there are no points within a tolerance of any point.
[ExtractClusters](/Cxx/Points/ExtractClusters) | vtkEuclideanClusterExtraction | From a set of randomly distributed spheres, extract connected clusters.
[ExtractEnclosedPoints](/Cxx/Points/ExtractEnclosedPoints) | vtkExtractEnclosedPoints | Extract points inside a vtkPolyData surface.
[ExtractPointsDemo](/Cxx/Points/ExtractPointsDemo) | vtkExtractPoints | Extract points inside an implicit function.
[ExtractSurface](/Cxx/Points/ExtractSurface) | vtkExtractSurface vtkPCANormalEstimation vtkSignedDistance | Create a surface from Unorganized Points using Point filters.
[ExtractSurfaceDemo](/Cxx/Points/ExtractSurfaceDemo) | vtkExtractSurface vtkPCANormalEstimation vtkSignedDistance | Create a surface from Unorganized Points using Point filters (DEMO).
[FitImplicitFunction](/Cxx/Points/FitImplicitFunction) | vtkFitImplicitFunction | Extract points within a distance to an implicit function.
[MaskPointsFilter](/Cxx/Points/MaskPointsFilter) | vtkMaskPointsFilter | Extract points within an image mask.
[NormalEstimation](/Cxx/Points/NormalEstimation) | vtkPCANormalEstimation | Estimate the normals of a random points that lie on a sphere.
[PointOccupancy](/Cxx/Points/PointOccupancy) | vtkPointOccupancyFilter | Show which voxels contain points.
[PointSource](/Cxx/PolyData/PointSource) | vtkPointSource | Generate a random point cloud.
[PoissonExtractSurface](/Cxx/Points/PoissonExtractSurface) |  | Create a surface from Unorganized Points using the PoissonReconstruction algorithm.
[PowercrustExtractSurface](/Cxx/Points/PowercrustExtractSurface) |  | Create a surface from Unorganized Points using the Powercrust algorithm.
[RadiusOutlierRemoval](/Cxx/Points/RadiusOutlierRemoval) | vtkRadiusOutlierRemoval | Remove outliers.
[SignedDistance](/Cxx/Points/SignedDistance) | vtkSignedDistance | Compute signed distance to a point cloud.
[UnsignedDistance](/Cxx/Points/UnsignedDistance) | vtkUnsignedDistance | Compute unsigned distance to a point cloud.

### Working with Meshes

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[AddCell](/Cxx/Meshes/AddCell) | vtkPolyData | Add a cell to an existing mesh.
[BoundaryEdges](/Cxx/Meshes/BoundaryEdges) | vtkFeatureEdges | Find the edges that are used by only one face.
[CellEdges](/Cxx/Meshes/CellEdges) | vtkCell | Get edges of cells.
[ClosedSurface](/Cxx/PolyData/ClosedSurface) | vtkFeatureEdges | Check if a surface is closed.
[ColorDisconnectedRegions](/Cxx/PolyData/ColorDisconnectedRegions) | vtkPolyDataConnectivityFilter | Color each disconnected region of a vtkPolyData a different color.
[ColorDisconnectedRegionsDemo](/Cxx/PolyData/ColorDisconnectedRegionsDemo) | vtkPolyDataConnectivityFilter | Color each disconnected region of a vtkPolyData a different color for any vtkPolyData.
[ColoredElevationMap](/Cxx/Meshes/ColoredElevationMap) | vtkLookupTable | Color a mesh by height.
[Curvatures](/Cxx/PolyData/Curvatures) | vtkCurvatures | Compute Gaussian, Mean, Min, and Max Curvatures.
[Decimation](/Cxx/Meshes/Decimation) | vtkDecimatePro | Reduce the number of triangles in a mesh.
[DeformPointSet](/Cxx/Meshes/DeformPointSet) | vtkDeformPointSet | Deform a point set with a control polyhedra.
[DelaunayMesh](/Cxx/Modelling/DelaunayMesh) | vtkDelaunay2D vtkMinimalStandardRandomSequence vtkExtractEdges vtkGlyph3D vtkTubeFilter | Two-dimensional Delaunay triangulation of a random set of points. Points and edges are shown highlighted with sphere glyphs and tubes.
[DijkstraGraphGeodesicPath](/Cxx/PolyData/DijkstraGraphGeodesicPath) | vtkDijkstraGraphGeodesicPath | Find the shortest path between two points on a mesh.
[ElevationFilter](/Cxx/Meshes/ElevationFilter) | vtkElevationFilter | Color a mesh by height.
[ExtractEdges](/Cxx/Meshes/ExtractEdges) | vtkExtractEdges |
[FillHoles](/Cxx/Meshes/FillHoles) | vtkFillHolesFilter | Close holes in a mesh.
[FitToHeightMap](/Cxx/Meshes/FitToHeightMap) | vtkFitToHeightMapFilter | Drape a polydata over an elevation map.
[GreedyTerrainDecimation](/Cxx/PolyData/GreedyTerrainDecimation) | vtkGreedyTerrainDecimation | Create a mesh from an ImageData
[HighlightBadCells](/Cxx/PolyData/HighlightBadCells) | vtkMeshQuality |
[IdentifyHoles](/Cxx/Meshes/IdentifyHoles) | vtkFillHolesFilter | Close holes in a mesh and identify the holes.
[InterpolateFieldDataDemo](/Cxx/Meshes/InterpolateFieldDataDemo) | vtkPointInterpolator vtkInterpolateDataSetAttributes | Resample a fine grid and interpolate field data.
[ImplicitSelectionLoop](/Cxx/PolyData/ImplicitSelectionLoop) | vtkImplicitSelectionLoop | Select a region of a mesh with an implicit function.
[LargestRegion](/Cxx/PolyData/PolyDataConnectivityFilter_LargestRegion) | vtkPolyDataConnectivityFilter | Extract the largest connected region in a polydata.
[MatrixMathFilter](/Cxx/Meshes/MatrixMathFilter) | vtkMatrixMathFilter | Compute various quantities on cell and points in a mesh.
[MeshQuality](/Cxx/PolyData/MeshQuality) | vtkMeshQuality |
[OBBDicer](/Cxx/Meshes/OBBDicer) | vtkOBBDicer | Breakup a mesh into pieces.
[PointInterpolator](/Cxx/Meshes/PointInterpolator) | vtkPointInterpolator | Plot a scalar field of points onto a PolyData surface.
[PolygonalSurfaceContourLineInterpolator](/Cxx/PolyData/PolygonalSurfaceContourLineInterpolator) | vtkPolygonalSurfaceContourLineInterpolator | Interactively find the shortest path between two points on a mesh.
[QuadricClustering](/Cxx/Meshes/QuadricClustering) | vtkQuadricClustering | Reduce the number of triangles in a mesh.
[QuadricDecimation](/Cxx/Meshes/QuadricDecimation) | vtkQuadricDecimation | Reduce the number of triangles in a mesh.
[SelectPolyData](/Cxx/PolyData/SelectPolyData) | vtkSelectPolyData | Select a region of a mesh.
[SimpleElevationFilter](/Cxx/Meshes/SimpleElevationFilter) | vtkSimpleElevationFilter | Color a mesh by dotting a vector from the origin to each point with a specified vector.
[SmoothPolyDataFilter](/Cxx/PolyData/SmoothPolyDataFilter) | vtkSmoothPolyDataFilter | Laplacian smoothing.
[SpecifiedRegion](/Cxx/PolyData/PolyDataConnectivityFilter_SpecifiedRegion) | vtkPolyDataConnectivityFilter | Extract a specific (specified) connected region in a polydata.
[SplitPolyData](/Cxx/Meshes/SplitPolyData) | vtkOBBDicer | Breakup a mesh into pieces and save the pieces into files
[Subdivision](/Cxx/Meshes/Subdivision) | vtkButterflySubdivisionFilter vtkLoopSubdivisionFilter vtkLinearSubdivisionFilter | Increase the number of triangles in a mesh.
[SubdivisionDemo](/Cxx/Meshes/SubdivisionDemo) | vtkButterflySubdivisionFilter vtkLoopSubdivisionFilter vtkLinearSubdivisionFilter | Subdivision of any vtkPolyData
[Triangulate](/Cxx/Meshes/Triangulate) | vtkTriangleFilter | Convert all polygons in a mesh to triangles.
[WeightedTransformFilter](/Cxx/PolyData/WeightedTransformFilter) | vtkWeightedTransformFilter |
[WindowedSincPolyDataFilter](/Cxx/Meshes/WindowedSincPolyDataFilter) | vtkWindowedSincPolyDataFilter | Smooth a mesh (windowed sinc filter).

#### Clipping

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[BoxClipStructuredPoints](/Cxx/Visualization/BoxClipStructuredPoints) | vtkBoxClipDataSet vtkStructuredPoints | Clip vtkStructuredPoints with a box. The results are unstructured grids with tetrahedra.
[BoxClipUnstructuredGrid](/Cxx/Visualization/BoxClipUnstructuredGrid) | vtkBoxClipDataSet vtkUnstructuredGrid | Clip a vtkUnstructuredGrid with a box. The results are unstructured grids with tetrahedra.
[CapClip](/Cxx/Meshes/CapClip) | vtkClipPolyData | Cap a clipped polydata with a polygon.
[ClipClosedSurface](/Cxx/Meshes/ClipClosedSurface) | vtkClipClosedSurface | Clip a surface with multiple planes.
[ClipDataSetWithPolyData](/Cxx/Meshes/ClipDataSetWithPolyData) | vtkClipDataSet vtkImplicitPolyDataDistance vtkRectilinearGrid | Clip a vtkRectilinearGrid with arbitrary polydata. In this example, use a vtkConeSource to generate polydata to slice the grid, resulting in an unstructured grid. Contrast this with the next example.
[ClipFrustum](/Cxx/Meshes/ClipFrustum) | vtkFrustumSource vtkClipPolyData | Clip a vtkPolyData with the vtkCamera's view frustum.
[GenericClip](/Cxx/Filtering/GenericClip) | vtkGenericClip vtkBridgeDataSet vtkGenericDataSet |
[ImplicitDataSetClipping](/Cxx/PolyData/ImplicitDataSetClipping) | vtkImplicitDataSet | Clip using an implicit data set.
[SolidClip](/Cxx/Meshes/SolidClip) | vtkClipPolyData | Create a "solid" clip. The "ghost" of the part clipped away is also shown.
[TableBasedClipDataSetWithPolyData](/Cxx/Meshes/TableBasedClipDataSetWithPolyData) | vtkTableBasedClipDataSet vtkImplicitPolyDataDistance vtkRectilinearGrid | Clip a vtkRectilinearGrid with arbitrary polydata. In this example, use a vtkConeSource to generate polydata to slice the grid, resulting in an unstructured grid. Contrast this with the previous example.
[TableBasedClipDataSetWithPolyData2](/Cxx/Meshes/TableBasedClipDataSetWithPolyData2) | vtkTableBasedClipDataSet vtkRectilinearGrid | Clip a vtkRectilinearGrid with a checkerboard pattern.

### Working with Structured 3D Data

This section includes vtkImageData vtkStructuredGrid and vtkRectilinearGrid.

"ImageData" is not the traditional "flat, 2D image" you are used to. It is a special VTK data structure in the collection of 3D data structures provided by VTK. [Here is an overview of these data structures](http://www.vtk.org/Wiki/VTK/Tutorials/3DDataTypes). Image data can represent at typical 2D image, but also, a 3D volume.

* [Demonstration of structured data types](/Cxx/Visualization/StructuredDataTypes)
* [Get the linear point id of a point in a grid](/Cxx/StructuredGrid/GetLinearPointId)

#### vtkImageData

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[CellIdFromGridCoordinates](/Cxx/ImageData/CellIdFromGridCoordinates) | vtkStructuredData | Get the id of a cell from its grid coordinates.
[ExtractVOI](/Cxx/ImageData/ExtractVOI) | vtkExtractVOI | Extract a volume of interest (subvolume).
[GetCellCenter](/Cxx/ImageData/GetCellCenter) | vtkImageData | Get the coordinates of the center of a cell.
[ClipVolume](/Cxx/ImageData/ClipVolume) | vtkClipVolume vtkImageData | Clip a volumeand produce a vtkUnhstructuredGrid.
[ImageIterator](/Cxx/ImageData/ImageIterator) | vtkImageIterator |
[ImageIteratorDemo](/Cxx/ImageData/ImageIteratorDemo) | vtkImageIterator | Demonstrate using an iterator to access pixels in a region.
[ImageNormalize](/Cxx/ImageData/ImageNormalize) | vtkImageNormalize | Normalize an image.
[ImageReslice](/Cxx/ImageData/ImageReslice) | vtkImageReslice | Resize a vtkImageData.
[ImageTranslateExtent](/Cxx/ImageData/ImageTranslateExtent) | vtkImageTranslateExtent | Change the extent of a vtkImageData.
[ImageWeightedSum](/Cxx/ImageData/ImageWeightedSum) | vtkImageWeightedSum | Add two or more images.
[IntersectLine](/Cxx/ImageData/IntersectLine) | vtkImageData | Intersect a line with all cells of a vtkImageData.
[IterateImageData](/Cxx/ImageData/IterateImageData) | vtkImageData | Iterating over a vtkImageData.

#### Conversions

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ImageDataGeometryFilter](/Cxx/ImageData/ImageDataGeometryFilter) | vtkImageDataGeometryFilter | Convert a vtkImageData to a vtkPolyData
[ImageDataToPointSet](/Cxx/ImageData/ImageDataToPointSet) | vtkImageDataToPointSet | Convert a vtkImageData to a vtkStructuredGrid.

#### vtkStructuredGrid

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[BlankPoint](/Cxx/StructuredGrid/BlankPoint) | vtkStructuredGrid | Blank a point of a vtkStructuredGrid.
[GetLinearPointId](/Cxx/StructuredGrid/GetLinearPointId) | vtkStructuredGrid | Get the linear point id of a point in a grid.
[SGrid](/Cxx/StructuredGrid/SGrid) | vtkStructuredGrid | Creating a structured grid dataset of a semi-cylinder. Vectors are created whose magnitude is proportional to radius and oriented in tangential direction.
[StructuredGrid](/Cxx/StructuredGrid/StructuredGrid) | vtkStructuredGrid vtkCellData vtkCellIterator | Reads and writes points into a structured grid. The grid is also colored by point data and how to iterate through the structured grid is demonstrated.
[StructuredGridOutline](/Cxx/StructuredGrid/StructuredGridOutline) | vtkStructuredGridOutlineFilter | Visualize the outline of a structured grid.
[VisualizeStructuredGrid](/Cxx/StructuredGrid/VisualizeStructuredGrid) | vtkStructuredGridGeometryFilter | Visualize the points of a structured grid.
[VisualizeStructuredGridCells](/Cxx/StructuredGrid/VisualizeStructuredGridCells) | vtkShrinkFilter | Visualize the cells of a structured grid.

#### vtkStructuredPoints

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[StructuredPointsToUnstructuredGrid](/Cxx/StructuredPoints/StructuredPointsToUnstructuredGrid) | vtkStructuredPoints vtkUnstructuredGrid | Convert a vtkStructuredPoints to a vtkUnstructuredGrid.
[Vol](/Cxx/StructuredPoints/Vol) | vtkStructuredPoints vtkContourFilter | Creating a image data dataset. Scalar data is generated from the equation for a sphere. Volume dimensions are 26 x 26 x 26.

#### vtkRectilinearGrid

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[RGrid](/Cxx/RectilinearGrid/RGrid) | vtkRectilinearGrid | Creating a rectilinear grid dataset. The coordinates along each axis are defined using an instance of vtkDataArray.
[RectilinearGrid](/Cxx/RectilinearGrid/RectilinearGrid) | vtkRectilinearGrid | Rectilinear grid
[RectilinearGridToTetrahedra](/Cxx/RectilinearGrid/RectilinearGridToTetrahedra) | vtkRectilinearGridToTetrahedra | Convert a vtkRectilinearGrid to a vtkUnstructuredGrid mesh
[VisualizeRectilinearGrid](/Cxx/RectilinearGrid/VisualizeRectilinearGrid) | vtkRectilinearGrid vtkShrinkFilter | Visualize the cells of a rectilinear grid

### Working with Unstructured 3D Data

This section includes vtkUnstructuredGrid.

#### vtkUnstructuredGrid

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ClipUnstructuredGridWithPlane](/Cxx/UnstructuredGrid/ClipUnstructuredGridWithPlane) | vtkTableBasedClipDataSet vtkUnstructuredGrid | Clip a UGrid with a plane.
[ClipUnstructuredGridWithPlane2](/Cxx/UnstructuredGrid/ClipUnstructuredGridWithPlane2) | vtkClipDataSet vtkUnstructuredGrid | Clip a UGrid with a plane.
[UGrid](/Cxx/UnstructuredGrid/UGrid) | vtkUnstructuredGrid | Creation of an unstructured grid.

### Registration

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[IterativeClosestPointsTransform](/Cxx/Filtering/IterativeClosestPointsTransform) | vtkIterativeClosestPointTransform | Iterative Closest Points (ICP) Transform.
[LandmarkTransform](/Cxx/Filtering/LandmarkTransform) | vtkLandmarkTransform | Landmark Transform.

### Medical

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[GenerateCubesFromLabels](/Cxx/Medical/GenerateCubesFromLabels) | vtkMetaImageReader vtkMaskFields | Create cubes from labeled volume data.
[GenerateModelsFromLabels](/Cxx/Medical/GenerateModelsFromLabels) | vtkDiscreteMarchingCubes vtkWindowedSincPolyDataFilter | Create models from labeled volume data (vtkDiscreteMarchingCubes).
[MedicalDemo1](/Cxx/Medical/MedicalDemo1) | vtkMarchingCubes | Create a skin surface from volume data
[MedicalDemo2](/Cxx/Medical/MedicalDemo2) | vtkMarchingCubes | Create a skin and bone surface from volume data
[MedicalDemo3](/Cxx/Medical/MedicalDemo3) | vtkMarchingCubes | Create skin, bone and slices from volume data
[MedicalDemo4](/Cxx/Medical/MedicalDemo4) | vtkFixedPointVolumeRayCastMapper | Create a volume rendering
[TissueLens](/Cxx/Medical/TissueLens) | vtkMarchingCubes vtkClipDataSet  vtkProbeFilter | Cut a volume with a sphere

### Surface reconstruction

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Delaunay3D](/Cxx/Modelling/Delaunay3D) | vtkDelaunay3D | Create a solid mesh from Unorganized Points.
[Delaunay3DDemo](/Cxx/Modelling/Delaunay3DDemo) | vtkDelaunay3D | Interactively adjust Alpha for Delaunay3D.
[ExtractSurface](/Cxx/Points/ExtractSurface) | vtkExtractSurface vtkPCANormalEstimation vtkSignedDistance | Create a surface from Unorganized Points using Point filters.
[ExtractSurfaceDemo](/Cxx/Points/ExtractSurfaceDemo) | vtkExtractSurface vtkPCANormalEstimation vtkSignedDistance | Create a surface from Unorganized Points using Point filters (DEMO).
[GaussianSplat](/Cxx/Filtering/GaussianSplat) | vtkGaussianSplatter | Create a surface from Unorganized Points (Gaussian Splat).
[SurfaceFromUnorganizedPoints](/Cxx/Filtering/SurfaceFromUnorganizedPoints) | vtkSurfaceReconstructionFilter | Create a surface from Unorganized Points.
[SurfaceFromUnorganizedPointsWithPostProc](/Cxx/Filtering/SurfaceFromUnorganizedPointsWithPostProc) | vtkSurfaceReconstructionFilter | Create a surface from Unorganized Points (with post processing).
[TriangulateTerrainMap](/Cxx/Filtering/TriangulateTerrainMap) | vtkDelaunay2D | Generate heights (z values) on a 10x10 grid (a terrain map) and then triangulate the points to form a surface.

## Utilities

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[BoundingBox](/Cxx/Utilities/BoundingBox) | vtkBoundingBox | Bounding Box construction.
[BoundingBoxIntersection](/Cxx/Utilities/BoundingBoxIntersection) | vtkBoundingBox | Box intersection and Inside tests.
[Box](/Cxx/Utilities/Box) | vtkBoundingBox | Intersect a box with a ray.
[BrownianPoints](/Cxx/Utilities/BrownianPoints) | vtkBrownianPoints | Produce a random vector at each point in a dataset.
[CardinalSpline](/Cxx/Utilities/CardinalSpline) | vtkCardinalSpline | Cardinal spline Interpolation.
[Casting](/Cxx/PolyData/Casting) | vtkObject::SafeDownCast | Casting VTK objects.
[CheckVTKVersion](/Cxx/Utilities/CheckVTKVersion) | vtkVersion | Check VTK Version.
[ColorLookupTable](/Cxx/Utilities/ColorLookupTable) | vtkLookupTable | Color Lookup Table.
[ColorTransferFunction](/Cxx/Utilities/ColorTransferFunction) | vtkColorTransferFunction | Color Transfer Function.
[CommandSubclass](/Cxx/Utilities/CommandSubclass) | vtkCommand | Instead of using a callback function, it is more powerful to subclass vtkCommand.
[ConstrainedDelaunay2D](/Cxx/Filtering/ConstrainedDelaunay2D) | vtkDelaunay2D | Perform a 2D Delaunay triangulation on a point set respecting a specified boundary.
[Coordinate](/Cxx/Utilities/Coordinate) | vtkCoordinate | Coordinate system conversions.
[DeepCopy](/Cxx/Utilities/DeepCopy) |  | Deep copy a VTK object.
[Delaunay2D](/Cxx/Filtering/Delaunay2D) | vtkDelaunay2D | Perform a 2D Delaunay triangulation on a point set.
[DetermineActorType](/Cxx/Utilities/DetermineActorType) | vtkActor vtkActorCollection | Determine the type of an actor.
[DiscretizableColorTransferFunction](/Cxx/Utilities/DiscretizableColorTransferFunction) | vtkDiscretizableColorTransferFunction | Discretizable Color Transfer Function.
[ExtractFaces](/Cxx/Utilities/ExtractFaces) | vtkCellIterator | Extract faces froam vtkUnstructuredGrid.
[FileOutputWindow](/Cxx/Utilities/FileOutputWindow) | vtkFileOutputWindow | Write errors to a log file  instead of the screen.
[FilenameFunctions](/Cxx/Utilities/FilenameFunctions) | vtkDirectory vtksys/SystemTools | Do things like get the file extension, strip the file extension, etc.
[FilterSelfProgress](/Cxx/Developers/FilterSelfProgress) |  | Monitor a filters progress.
[FrameRate](/Cxx/Utilities/FrameRate) |  | Get the frame rate of the rendering.
[FullScreen](/Cxx/Utilities/FullScreen) | vtkRenderWindow | Maximize/full screen a vtkRenderWindow.
[FunctionParser](/Cxx/Utilities/FunctionParser) | vtkFunctionParser | String function parser.
[GetClassName](/Cxx/Utilities/GetClassName) | GetClassName() | Determine the type of a VTK variable.
[GetDataRoot](/Cxx/Utilities/GetDataRoot) | vtkTesting | Find the path of VTK_DATA_ROOT.
[LUTUtilities](/Cxx/Utilities/LUTUtilities) | vtkLookupTable vtkColorSeries | A utility class for vtkLookupTable allowing you to output the table contents or to compare tables.
[MassProperties](/Cxx/Utilities/MassProperties) | vtkMassProperties | Compute volume and surface area of a closed, triangulated mesh.
[MultipleRenderWindows](/Cxx/Visualization/MultipleRenderWindows) | vtkRenderWindow | Multiple Render Windows
[MultipleViewports](/Cxx/Visualization/MultipleViewports) | vtkRenderer::SetViewPort | Multiple Viewports.
[OffScreenRendering](/Cxx/Utilities/OffScreenRendering) | vtkImagingFactory vtkGraphicsFactory | Off Screen Rendering.
[PCADemo](/Cxx/Utilities/PCADemo) | vtkPCAStatistics | Project 2D points onto the best 1D subspace (PCA Demo).
[PCAStatistics](/Cxx/Utilities/PCAStatistics) | vtkPCAStatistics | Compute Principal Component Analysis (PCA) values.
[PassThrough](/Cxx/InfoVis/PassThrough) | vtkPassThrough | Pass input along to outpu.
[PiecewiseFunction](/Cxx/Utilities/PiecewiseFunction) | vtkPiecewiseFunction | Interpolation using a piecewise function.
[PointInPolygon](/Cxx/Utilities/PointInPolygon) | vtkPolygon | Point inside polygon test.
[ReportRenderWindowCapabilities](/Cxx/Utilities/ReportRenderWindowCapabilities) | vtkRenderWindow | Report the capabilities of a render window.
[SaveSceneToFieldData](/Cxx/Utilities/SaveSceneToFieldData) | vtkCamera | Save a vtkCamera's state in a vtkDataSet's vtkFieldData and restore it.
[SaveSceneToFile](/Cxx/Utilities/SaveSceneToFile) | vtkCamera | Save a vtkCamera's state in a file and restore it.
[Screenshot](/Cxx/Utilities/Screenshot) | vtkWindowToImageFilter |
[ShallowCopy](/Cxx/Utilities/ShallowCopy) |  | Shallow copy a VTK object.
[ShareCamera](/Cxx/Utilities/ShareCamera) | vtkRenderer vtkCamera | Share a camera between multiple renderers.
[ShepardMethod](/Cxx/Utilities/ShepardMethod) | vtkShepardMethod | Shepard method interpolation.
[SideBySideViewports](/Cxx/Visualization/SideBySideViewports) | vtkRenderer::SetViewPort | Side by side viewports.
[TimeStamp](/Cxx/Utilities/TimeStamp) | vtkTimeStamp | Time stamp.
[Timer](/Cxx/Utilities/Timer) | vtkRenderWindowInteractor::CreateRepeatingTimer |
[TimerLog](/Cxx/Utilities/TimerLog) | vtkTimerLog | Timer log.
[Variant](/Cxx/Utilities/Variant) | vtkVariant | Convert between data types.
[Vector](/Cxx/Utilities/Vector) | vtkVector | Mathematical vector class.
[ViewportBorders](/Cxx/Utilities/ViewportBorders) |  | Draw a border around each viewport.
[VisualDebugging](/Cxx/Demos/VisualDebugging) |  | Update the screen from inside an algorithm.
[ZBuffer](/Cxx/Utilities/ZBuffer) | vtkRenderer | zbuffer.

### Arrays

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[2DArray](/Cxx/Utilities/2DArray) | vtkDenseArray | 2D Array.
[3DArray](/Cxx/Utilities/3DArray) | vtkDenseArray | 3D Array.
[ArrayCalculator](/Cxx/Utilities/ArrayCalculator) | vtkArrayCalculator | Perform in-place operations on arrays.
[ArrayLookup](/Cxx/Utilities/ArrayLookup) | vtkDataArray | Find the location of a value in a vtkDataArray.
[ArrayRange](/Cxx/Utilities/ArrayRange) | vtkFloatArray::GetRange | Get the bounds (min,max) of a vtk array.
[ArrayToTable](/Cxx/InfoVis/ArrayToTable) | vtkArrayToTable | Convert a vtkDenseArray to a vtkTable.
[ArrayWriter](/Cxx/Utilities/ArrayWriter) | vtkArrayWriter | Write a DenseArray or SparseArray to a file.
[ConstructTable](/Cxx/Utilities/ConstructTable) | vtkTable | A table is a 2D array of any type of elements. They do not all have to be the same type. This is achieved using vtkVariant.
[CustomDenseArray](/Cxx/Utilities/CustomDenseArray) | vtkDenseArray | Custom type Dense (2D) Array.
[DenseArrayRange](/Cxx/Utilities/DenseArrayRange) | vtkDenseArray vtkArrayRange | Get the bounds of a vtkDenseArray.
[ExtractArrayComponent](/Cxx/Utilities/ExtractArrayComponent) | vtkArrayCalculator | Extract a component of an array.
[KnownLengthArray](/Cxx/Utilities/KnownLengthArray) | vtkFloatArray | Known Length Array.
[SortDataArray](/Cxx/Utilities/SortDataArray) | vtkSortDataArray | Reorder array values based on an ordering (key) array.
[SparseArray](/Cxx/Utilities/SparseArray) | vtkSparseArray | Sparse Array.
[UnknownLengthArray](/Cxx/Utilities/UnknownLengthArray) | vtkFloatArray | Unknown Length Array.
[VectorArrayKnownLength](/Cxx/Utilities/VectorArrayKnownLength) | vtkFloatArray | Array of Vectors (Known Length).
[VectorArrayUnknownLength](/Cxx/Utilities/VectorArrayUnknownLength) | vtkFloatArray | Array of Vectors (Unknown Length).

### Events

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[CameraModifiedEvent](/Cxx/Utilities/CameraModifiedEvent) | vtkCameraWindow | Catch the camera modified event.
[ObserveError](/Cxx/Utilities/ObserveError) | vtkCommand | Catch errors and warnings.
[WindowModifiedEvent](/Cxx/Utilities/WindowModifiedEvent) | vtkRenderWindow | Catch the window modified event.

## CMake Techniques

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Check if a specific module is present](/Cxx/CMakeTechniques/CheckForModule) |  |

## Math Operations

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[1DTupleInterpolation](/Cxx/Math/1DTupleInterpolation) | vtkTupleInterpolator vtkCardinalSpline vtkKochanekSpline | A simple example demonstrating how functions defined by sparsely distributed supporting points can be interpolated at arbitrary positions.
[EigenSymmetric](/Cxx/Math/EigenSymmetric) | vtkMath::Jacobi | Compute eigenvalues and eigenvectors of a symmetric matrix.
[HomogeneousLeastSquares](/Cxx/Math/HomogeneousLeastSquares) | vtkMath::SolveHomogeneousLeastSquares | Homogeneous Least Squares.
[LUFactorization](/Cxx/Math/LUFactorization) | vtkMath | LU Factorization.
[LeastSquares](/Cxx/Math/LeastSquares) | vtkMath::SolveLeastSquares | Least Squares.
[MatrixInverse](/Cxx/Math/MatrixInverse) | vtkMatrix3x3 | Matrix inverse.
[MatrixTranspose](/Cxx/Math/MatrixTranspose) | vtkMatrix3x3 | Matrix transpose.
[NormalizeVector](/Cxx/Math/NormalizeVector) | vtkMath | Normalize a vector.
[PerpendicularVector](/Cxx/Math/PerpendicularVector) | vtkMath::Perpendiculars | Get a vector perpendicular to another vector.
[VectorDot](/Cxx/Math/VectorDot) | vtkVectorDot |
[VectorNorm](/Cxx/Math/VectorNorm) | vtkVectorNorm | Get the lengths of an array of vectors.

## Graphs

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[AdjacencyMatrixToEdgeTable](/Cxx/Graphs/AdjacencyMatrixToEdgeTable) | vtkAdjacencyMatrixToEdgeTable | Convert an adjacency matrix to an edge table.
[AdjacentVertexIterator](/Cxx/Graphs/AdjacentVertexIterator) | vtkAdjacentVertexIterator | Get all vertices connected to a specified vertex.
[BoostBreadthFirstSearchTree](/Cxx/Graphs/BoostBreadthFirstSearchTree) | vtkBoostBreadthFirstSearchTree | Breadth first search tree. Can also be used to convert a graph to a tree.
[BreadthFirstDistance](/Cxx/Graphs/BreadthFirstDistance) | vtkBoostBreadthFirstSearch | Distance from origin.
[ColorEdges](/Cxx/Graphs/ColorEdges) | vtkGraphLayoutView | Color edges.
[ColorVertexLabels](/Cxx/Graphs/ColorVertexLabels) | vtkGraphLayoutView vtkRenderedGraphRepresentation | Set the color of vertex labels.
[ColorVerticesLookupTable](/Cxx/Graphs/ColorVerticesLookupTable) | vtkGraphLayoutView | Color vertices.
[ConnectedComponents](/Cxx/Graphs/ConnectedComponents) | vtkBoostConnectedComponents | Find connected components of a graph.
[ConstructGraph](/Cxx/Graphs/ConstructGraph) | vtkMutableUndirectedGraph | Construct a graph.
[ConstructTree](/Cxx/Graphs/ConstructTree) | vtkTree vtkMutableDirectedGraph | Construct a tree.
[DepthFirstSearchAnimation](/Cxx/Graphs/DepthFirstSearchAnimation) | vtkTreeDFSIterator | Depth First Search Animation.
[DepthFirstSearchIterator](/Cxx/Graphs/DepthFirstSearchIterator) | vtkTreeDFSIterator | Depth First Search iterator.
[EdgeListIterator](/Cxx/Graphs/EdgeListIterator) | vtkEdgeListIterator | Iterate over edges of a graph.
[EdgeWeights](/Cxx/Graphs/EdgeWeights) | vtkGraph::GetEdgeData::AddArray | Edge weights.
[GraphPoints](/Cxx/InfoVis/GraphPoints) | vtkGraph::SetPoints, vtkPassThroughLayoutStrategy | Manually set coordinates of vertices in a graph.
[GraphToPolyData](/Cxx/Graphs/GraphToPolyData) | vtkGraphToPolyData | Convert a graph to a PolyData.
[InEdgeIterator](/Cxx/Graphs/InEdgeIterator) | vtkInEdgeIterator | Iterate over edges incoming to a vertex.
[LabelVerticesAndEdges](/Cxx/Graphs/LabelVerticesAndEdges) | vtkGraphLayoutView | Label vertices and edges.
[MinimumSpanningTree](/Cxx/Graphs/MinimumSpanningTree) | vtkBoostPrimMinimumSpanningTree | Minimum spanning tree of a graph.
[MutableGraphHelper](/Cxx/InfoVis/MutableGraphHelper) | vtkMutableGraphHelper | Create either a vtkMutableDirectedGraph or vtkMutableUndirectedGraph.
[NOVCAGraph](/Cxx/Graphs/NOVCAGraph) | vtkUnstructuredGrid vtkXMLUnstructuredGridWriter vtkPolyLine | Create a graph & visualize it in ParaView/VisIt.
[OutEdgeIterator](/Cxx/Graphs/OutEdgeIterator) | vtkOutEdgeIterator | Iterate over edges outgoing from a vertex.
[RandomGraphSource](/Cxx/Graphs/RandomGraphSource) | vtkRandomGraphSource | Create a random graph.
[RemoveIsolatedVertices](/Cxx/Graphs/RemoveIsolatedVertices) | vtkRemoveIsolatedVertices | Remove vertices of degree 0 from a vtkGraph.
[ScaleVertices](/Cxx/Graphs/ScaleVertices) | vtkGraphLayoutView vtkRenderedGraphRepresentation | Size/scale vertices based on a data array.
[SelectedVerticesAndEdges](/Cxx/Graphs/SelectedVerticesAndEdges) | vtkAnnotationLink | Get a list of selected vertices and edges.
[SelectedVerticesAndEdgesObserver](/Cxx/Graphs/SelectedVerticesAndEdgesObserver) | vtkAnnotationLink | Get a list of selected vertices and edges using an observer of AnnotationChangedEvent.
[ShortestPath](/Cxx/Graphs/ShortestPath) | vtkDijkstraGraphGeodesicPath | Find the shortest path on a graph.
[SideBySideGraphs](/Cxx/Graphs/SideBySideGraphs) | vtkGraphLayoutView | Display two graphs side by side.
[TreeBFSIterator](/Cxx/Graphs/TreeBFSIterator) | vtkTreeBFSIterator | Breadth First Search iterator.
[VertexSize](/Cxx/Graphs/VertexSize) | vtkGraphLayoutView vtkRenderedGraphRepresentation | Set the size of vertices.
[VisualizeDirectedGraph](/Cxx/Graphs/VisualizeDirectedGraph) | vtkGlyphSource2D | Visualize a directed graph.
[VisualizeGraph](/Cxx/Graphs/VisualizeGraph) | vtkGraphLayoutView vtkGraphLayoutStrategy vtkSimple2DLayoutStrategy | Visualize a graph.

### Graph Conversions

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[DirectedGraphToMutableDirectedGraph](/Cxx/Graphs/DirectedGraphToMutableDirectedGraph) | vtkMutableDirectedGraph vtkDirectedGraph | vtkDirectedGraph to vtkMutableDirectedGraph.
[MutableDirectedGraphToDirectedGraph](/Cxx/Graphs/MutableDirectedGraphToDirectedGraph) | vtkMutableDirectedGraph vtkDirectedGraph | vtkMutableDirectedGraph to vtkDirectedGraph.
[TreeToMutableDirectedGraph](/Cxx/Graphs/TreeToMutableDirectedGraph) | vtkMutableDirectedGraph vtkTree | vtkTree to vtkMutableDirectedGraph

## Data Structures

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[AttachAttributes](/Cxx/PolyData/AttachAttributes) | vtkInformation | Attach attributes to a VTK array
[CellLocator](/Cxx/PolyData/CellLocator) | vtkCellLocator | Project a point onto a mesh. Closest point on a mesh.Efficient 3D cell query.
[CellLocatorVisualization](/Cxx/PolyData/CellLocatorVisualization) | vtkCellLocator | Visualization of the tree of a vtkCellLocator.
[CellTreeLocator](/Cxx/PolyData/CellTreeLocator) | vtkCellTreeLocator | Points inside an object using vtkCellTreeLocator.
[PointLocator](/Cxx/PolyData/PointLocator) | vtkPointLocator | Efficient 3D point query.
[PointLocatorRadius](/Cxx/PolyData/PointLocatorRadius) | vtkPointLocator | Find all points within a radius of a specified point.
[PointLocatorVisualization](/Cxx/PolyData/PointLocatorVisualization) | vtkPointLocator | Visualization of the tree of a vtkPointLocator.

### Timing Demonstrations

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[KDTreeTimingDemo](/Cxx/DataStructures/KDTreeTimingDemo) | vtkKdTreePointLocator | Plot the runtime vs MaxLevel (doesn't seem correct)
[ModifiedBSPTreeTimingDemo](/Cxx/DataStructures/ModifiedBSPTreeTimingDemo) | vtkModifiedBSPTree | Plot the runtime vs MaxLevel
[OBBTreeTimingDemo](/Cxx/DataStructures/OBBTreeTimingDemo) | vtkOBBTree | Plot the runtime vs MaxLevel
[OctreeTimingDemo](/Cxx/DataStructures/OctreeTimingDemo) | vtkOctreePointLocator | Plot the runtime vs MaxPointsPerRegionOctree timing demo.

### KD-Tree

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[BuildLocatorFromKClosestPoints](/Cxx/DataStructures/BuildLocatorFromKClosestPoints) | vtkKdTree |
[ClosestNPoints](/Cxx/DataStructures/ClosestNPoints) | vtkKdTreePointLocator | Find the closest N points to a query point.
[DataStructureComparison](/Cxx/DataStructures/DataStructureComparison) | vtkKdTree vtkOBBTree vtkOctreePointLocator vtkModifiedBSPTree | Illustrates, side by side, the differences between several spatial data structures
[KDTreeAccessPoints](/Cxx/DataStructures/KDTreeAccessPoints) | vtkKdTree | Access the points of a KDTree.
[KDTreeFindPointsWithinRadius](/Cxx/DataStructures/KDTreeFindPointsWithinRadius) | vtkKdTreePointLocator | Find points within a specified radius of  a query point.
[KDTreeFindPointsWithinRadiusDemo](/Cxx/DataStructures/KDTreeFindPointsWithinRadiusDemo) | vtkKdTreePointLocator | Find points within a range of radii.
[KdTree](/Cxx/DataStructures/KdTree) | vtkKdTree |
[KdTreePointLocatorClosestPoint](/Cxx/DataStructures/KdTreePointLocatorClosestPoint) | vtkKdTreePointLocator | Find the closest point to a query point.
[OctreeFindPointsWithinRadiusDemo](/Cxx/DataStructures/OctreeFindPointsWithinRadiusDemo) | vtkKdTreePointLocator | Find points within a range of radii.
[PointLocatorFindPointsWithinRadiusDemo](/Cxx/DataStructures/PointLocatorFindPointsWithinRadiusDemo) | vtkdPointLocator | Find points within a range of radii.
[StaticLocatorFindPointsWithinRadiusDemo](/Cxx/DataStructures/StaticLocatorFindPointsWithinRadiusDemo) | vtkStaticPointLocator | Find points within a range of radii.
[VisualizeKDTree](/Cxx/DataStructures/VisualizeKDTree) | vtkKdTreePointLocator | Visualize levels of the tree.

### Oriented Bounding Box (OBB) Tree

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[OBBTreeExtractCells](/Cxx/DataStructures/OBBTreeExtractCells) | vtkOBBTree | Intersect a line with an OBB Tree and display all intersected cells.
[OBBTreeIntersectWithLine](/Cxx/DataStructures/OBBTreeIntersectWithLine) | vtkOBBTree | Intersect a line with a vtkOBBTree.
[VisualizeOBBTree](/Cxx/DataStructures/VisualizeOBBTree) | vtkOBBTree | Visualize levels of the tree.

### Octree

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[BuildOctree](/Cxx/DataStructures/BuildOctree) | vtkOctreePointLocator | Create an octree.
[IncrementalOctreePointLocator](/Cxx/DataStructures/IncrementalOctreePointLocator) | vtkIncrementalOctreePointLocator | Insert points into an octree without rebuilding it.
[OctreeClosestPoint](/Cxx/DataStructures/OctreeClosestPoint) | vtkOctreePointLocator | Find the closest point to a query point.
[OctreeFindPointsWithinRadius](/Cxx/DataStructures/OctreeFindPointsWithinRadius) | vtkOctreePointLocator | Find the points within a sphere of specified radius to a query point.
[OctreeKClosestPoints](/Cxx/DataStructures/OctreeKClosestPoints) | vtkOctreePointLocator | Find the K closest points to a query point.
[OctreeVisualize](/Cxx/DataStructures/OctreeVisualize) | vtkOctreePointLocator | Visualize levels of the tree.

### Modified BSP Tree

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ModifiedBSPTreeExtractCells](/Cxx/DataStructures/ModifiedBSPTreeExtractCells) | vtkModifiedBSPTree | Intersect a line with a modified BSP Tree and display all intersected cells.
[ModifiedBSPTreeIntersectWithLine](/Cxx/DataStructures/ModifiedBSPTreeIntersectWithLine) | vtkModifiedBSPTree | Intersect a line with a modified BSP Tree.
[VisualizeModifiedBSPTree](/Cxx/DataStructures/VisualizeModifiedBSPTree) | vtkModifiedBSPTree | Visualize levels of the tree.

### HyperTreeGrid

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[HyperTreeGridSource](/Cxx/HyperTreeGrid/HyperTreeGridSource) | vtkHyperTreeGridSource | Create a vtkHyperTreeGrid.

## VTK Concepts

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Scalars](/Cxx/VTKConcepts/Scalars) | VTKConcepts | Attach a scalar value to each point (PointData) or cell (CellData) in a data set.

## Rendering

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[AmbientSpheres](/Cxx/Rendering/AmbientSpheres) | vtkProperty | Demonstrates the effect of ambient lighting on spheres.
[CameraBlur](/Cxx/Rendering/CameraBlur) |  | Example of a scene rendered with focal depth.
[ColoredSphere](/Cxx/Rendering/ColoredSphere) | vtkSphereSource vtkElevationFilter | A simple sphere.
[Cone3](/Cxx/Rendering/Cone3) | vtkRenderWindow | Four frames of output, based on the VTK example Cone3.cxx.
[Cone4](/Cxx/Rendering/Cone4) | vtkRenderWindow | Modifying properties and transformation matrix based on the VTK example Cone4.cxx.
[DiffuseSpheres](/Cxx/Rendering/DiffuseSpheres) | vtkProperty | Demonstrates the effect of diffuse lighting on spheres.
[FlatVersusGouraud](/Cxx/Rendering/FlatVersusGouraud) | vtkProperty::SetInterpolationToFlat vtkProperty::SetInterpolationToGouraud | Flat and Gouraud shading. Different shading methods can dramatically improve the look of an object represented with polygons. On the top, flat shading uses a constant surface normal across each polygon. On the bottom, Gouraud shading interpolates normals from polygon vertices to give a smoother look.
[HiddenLineRemoval](/Cxx/Rendering/HiddenLineRemoval) | vtkProperty::UseHiddenLineRemovalOn | Hidden lines removed.
[Mace](/Cxx/Rendering/Mace) |  | An example of multiple inputs and outputs.
[Model](/Cxx/Rendering/Model) | vtkRenderer vtkRenderWindow vtkRenderWindowInteractor | Illustrative diagram of graphics objects.
[MotionBlur](/Cxx/Rendering/MotionBlur) | vtkRenderStepsPass vtkSimpleMotionBlurPass | Example of motion blur.
[PhysicallyBasedRendering](/Cxx/Rendering/PhysicallyBasedRendering) | vtkSkybox vtkTexture | Demonstrates physically based rendering, image based lighting, texturing and a skybox.
[Rainbow](/Cxx/Rendering/Rainbow) | vtkLookupTable | Use and manipulation of vtkLookupTables.
[Rotations](/Cxx/Rendering/Rotations) | vtkActor::RotateX,Y,Z vtkRenderer::EraseOff | Rotations of a cow about her axes.
[RotationsA](/Cxx/Rendering/RotationsA) | vtkActor::RotateX,Y,Z vtkRenderer::EraseOff | Perform six rotations of a cow about her x-axis (Figure 3-31a).
[RotationsB](/Cxx/Rendering/RotationsB) | vtkActor::RotateX,Y,Z vtkRenderer::EraseOff | Perform six rotations of a cow about her y-axis (Figure 3-31b).
[RotationsC](/Cxx/Rendering/RotationsC) | vtkActor::RotateX,Y,Z vtkRenderer::EraseOff | Perform six rotations of a cow about her z-axis (Figure 3-31c).
[RotationsD](/Cxx/Rendering/RotationsD) | vtkActor::RotateX,Y,Z vtkRenderer::EraseOff | First a rotation of a cow about her x-axis, then six rotations about her y-axis (Figure 3-31d).
[Shadows](/Cxx/Rendering/Shadows) | vtkCameraPass vtkRenderStepsPass vtkSequencePass vtkShadowMapBakerPass vtkShadowMapPass | Draw model with shadows.
[Skybox_PBR](/Cxx/Rendering/Skybox_PBR) | vtkSkybox vtkTexture | Demonstrates physically based rendering, image based lighting and a skybox.
[SpecularSpheres](/Cxx/Rendering/SpecularSpheres) | vtkProperty | Demonstrates the effect of specular lighting on spheres.
[StippledLine](/Cxx/Rendering/StippledLine) | vtkTexture | Draw a stippled line.
[StringToImageDemo](/Cxx/Rendering/StringToImageDemo) | vtkImageBlend vtkFreeTypeTools | Demonstrates how to generate images from strings.
[StripFran](/Cxx/Rendering/StripFran) | vtkDecimatePro vtkStripper | Triangle strip examples. (a) Structured triangle mesh consisting of 134 strips each of 390 triangles. (b) Unstructured triangle mesh consisting of 2227 strips of average length 3.94, longest strip 101 triangles. Images are generated by displaying every other triangle strip.
[TransformSphere](/Cxx/Rendering/TransformSphere) | vtkSphereSource vtkElevationFilter vtkTransform vkTransformFilter | The addition of a transform filter to [ColoredSphere](/Cxx/Rendering/ColoredSphere).
[TransparentBackground](/Cxx/Rendering/TransparentBackground) | vtkCallbackCommand vtkInteractorObserver vtkRendererCollection | Demonstrates the use of two renderers. Notice that the second (and subsequent) renderers will have a transparent background.
[WalkCow](/Cxx/Rendering/WalkCow) | vtkBYUReader vtkRenderWindow::EraseOff() vtkActor | This generates Figs. 3-32, 3-33 found in VTKTextbook.pdf.
[WalkCowA](/Cxx/Rendering/WalkCowA) | vtkBYUReader vtkRenderWindow::EraseOff() vtkActor | This generates Fig. 3-33a found in VTKTextbook.pdf.
[WalkCowB](/Cxx/Rendering/WalkCowB) | vtkBYUReader vtkRenderWindow::EraseOff() vtkActor | This generates Fig. 3-33b found in VTKTextbook.pdf.

## Lighting

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Light](/Cxx/Lighting/Light) | vtkLight | Add a directional light to a scene.
[LightActor](/Cxx/Lighting/LightActor) | vtkLightActor | Display the location and direction of a light.
[ShadowsLightsDemo](/Cxx/Visualization/ShadowsLightsDemo) | vtkLightActor vtkSequencePass vtkShadowMapBakerPass vtkShadowMapPass | Show lights casting shadows.
[ShadowsOpenGL](/Cxx/Visualization/ShadowsOpenGL) | vtkShadowMapPass | Create shadows with OpenGL backend.
[SpotLights](/Cxx/Lighting/SpotLights) | vtkLight | Create two positional(spot) lights.

## Shaders

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[BozoShader](/Cxx/Shaders/BozoShader) | vtkShaderProgram vtkOpenGLPolyDataMapper::AddShaderReplacement | Modify the shader to load and use noise functions for color selection.
[BozoShaderDemo](/Cxx/Shaders/BozoShaderDemo) | vtkShaderProgram vtkOpenGLPolyDataMapper::AddShaderReplacement | Show the bozo shader on a variety of polydata models.
[ColorByNormal](/Cxx/Shaders/ColorByNormal) | vtkOpenGLPolyDataMapper vtkTriangleMeshPointNormals | Modify the shader to color based on model normal.
[CubeMap](/Cxx/Shaders/CubeMap) | vtkShaderProgram vtkOpenGLPolyDataMapper | Modify the Vertex and Frament shaders to apply a 6-sided cube map.
[MarbleShader](/Cxx/Shaders/MarbleShader) | vtkShaderProgram vtkOpenGLPolyDataMapper::AddShaderReplacement | Modify the shader to load and use noise functions for color selection.
[MarbleShaderDemo](/Cxx/Shaders/MarbleShaderDemo) | vtkShaderProgram vtkOpenGLPolyDataMapper::AddShaderReplacement | Explore parameter space with sliders.
[SpatterShader](/Cxx/Shaders/SpatterShader) | vtkShaderProgram vtkOpenGLPolyDataMapper::AddShaderReplacement | Modify the shader to load and use noise functions for color selection.
[SphereMap](/Cxx/Shaders/SphereMap) | vtkShaderProgram vtkOpenGLPolyDataMapper | Modify the Vertex and Frament shaders to apply a spherical map.

## Annotation

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[MultiLineText](/Cxx/Annotation/MultiLineText) | vtkTextMapper | Display multiline text.
[TextOrigin](/Cxx/Annotation/TextOrigin) | vtkFollower | The 3D text always faces the active camera.
[XYPlot](/Cxx/Annotation/XYPlot) | vtkXYPlotActor vtkProbeFilter | Display line probes.

## Texture Mapping

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[AnimateVectors](/Cxx/Texture/AnimateVectors) | vtkTexture vtkGlyph3D | One frame from a vector field animation using texture maps ([animVectors.tcl](https://gitlab.kitware.com/vtk/vtk/blob/da314198bb8fbdab6f59e8a69b2d97f1611a05bd/graphics/examplesTcl/animVectors.tcl)).
[BackgroundTexture](/Cxx/Visualization/BackgroundTexture) | vtkRenderer vtkTexture | Use a texture for the background of a vtkRenderer.
[ClipArt](/Cxx/Visualization/ClipArt) | vtkTextureMapToPlane | Generate 3D clip art from an image.
[ProjectedTexture](/Cxx/Texture/ProjectedTexture) | vtkProjectedTexture | Project a texture onto ovtkPolyData.
[TextureCutQuadric](/Cxx/Texture/TextureCutQuadric) | vtkBooleanTexture vtkImplicitTextureCoords | Cut a quadric with boolean textures.
[TextureCutSphere](/Cxx/Texture/TextureCutSphere) | vtkImplicitTextureCoords | Cut a sphere using texture coordinates.
[TextureMapImageData](/Cxx/Visualization/TextureMapImageData) | vtkImageCanvasSource2D | Texture map an ImageData.
[TextureMapPlane](/Cxx/Visualization/TextureMapPlane) | vtkTextureMapToPlane | Texture map a plane.
[TextureMapQuad](/Cxx/Visualization/TextureMapQuad) | vtkPolygon vtkPolyData | Texture map a quad.
[TexturePlane](/Cxx/Texture/TexturePlane) | vtkTexture | Example of texture mapping.
[TextureThreshold](/Cxx/Texture/TextureThreshold) | vtkTexture vtkThresholdTextureCoords vtkStructuredGridGeometryFilter | Demonstrate the use of scalar thresholds to show values of flow density on three planes.
[TexturedSphere](/Cxx/Texture/TexturedSphere) | vtkTextureMapToSphere | Texture a sphere.

## Visualization

See [this tutorial](http://www.vtk.org/Wiki/VTK/Tutorials/3DDataTypes) for a brief explanation of the VTK terminology of mappers, actors, etc.

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[AlphaFrequency](/Cxx/Visualization/AlphaFrequency) | vtkLinearExtrusionFilter vtkVectorText | Linearly extrude fonts to show letter frequencies in text.
[AnatomicalOrientation](/Cxx/VisualizationAlgorithms/AnatomicalOrientation) | vtkAnnotatedCubeActor vtkAxesActor vtkOrientationMarkerWidget vtkTransform | Show a labelled set of anatomical planes transecting a human figure.
[AnnotatedCubeActor](/Cxx/Visualization/AnnotatedCubeActor) | vtkAnnotatedCubeActor | Annotated cube.
[Arbitrary3DCursor](/Cxx/Visualization/Arbitrary3DCursor) | vtkPointWidget | Track a 3D cursor.
[AssignCellColorsFromLUT](/Cxx/Visualization/AssignCellColorsFromLUT) | vtkNamedColors vtkPlaneSource vtkLookupTable vtkColorTransferFunction | Demonstrates how to assign colors to cells in a vtkPolyData structure using lookup tables.
[AxisActor](/Cxx/Visualization/AxisActor) | vtkAxisActor | Generate a single axis.
[BackfaceCulling](/Cxx/Visualization/BackfaceCulling) | vtkActor | Backface culling.
[BackgroundColor](/Cxx/Visualization/BackgroundColor) | vtkRenderer | Background color.
[BackgroundGradient](/Cxx/Visualization/BackgroundGradient) | vtkRenderer vtkRenderer | Background gradient.
[BillboardTextActor3D](/Cxx/Visualization/BillboardTextActor3D) | vtkBillboardTextActor3D | Label points with billboards.
[BlobbyLogo](/Cxx/Visualization/BlobbyLogo) | vtkImplicitModeller | Blobby logo from VTK textbook.
[Blow](/Cxx/Visualization/Blow) | vtkUnstructuredGridReader vtkWarpVector vtkConnectivityFilter | Ten frames from a blow molding finite element analysis.
[BluntStreamlines](/Cxx/VisualizationAlgorithms/BluntStreamlines) | vtkStructuredGridGeometryFilter vtkStreamTracer | Demonstrates airflow around a blunt fin using streamlines.
[Camera](/Cxx/Visualization/Camera) | vtkCamera | Positioning and aiming the camera.
[CameraActor](/Cxx/Visualization/CameraActor) | vtkCameraActor | Visualize a camera (frustum) in a scene.
[CameraModel1](/Cxx/Visualization/CameraModel1) | vtkCameraActor | Illustrate camera movement.
[CameraModel2](/Cxx/Visualization/CameraModel2) | vtkCameraActor | Illustrate camera movement.
[CaptionActor2D](/Cxx/Visualization/CaptionActor2D) | vtkCaptionActor2D | Draw a caption/bubble pointing to a particular point.
[CarotidFlow](/Cxx/VisualizationAlgorithms/CarotidFlow) | vtkStreamTracer vtkThresholdPoints | Visualizing blood flow in the human carotid arteries. Streamtubes of flow velocity are generated.
[CarotidFlowGlyphs](/Cxx/VisualizationAlgorithms/CarotidFlowGlyphs) | vtkGlyph3D vtkThresholdPoints | Visualizing blood flow in human carotid arteries. Cone glyphs indicate flow direction and magnitude.
[ChooseTextColor](/Cxx/Visualization/ChooseTextColor) | vtkTextActor vtkTextProperty::SetFontFamily vtkNamedColors | Choose a text color that contrasts with a background color.
[ChooseTextColorDemo](/Cxx/Visualization/ChooseTextColorDemo) | vtkTextActor vtkNamedColors | Create a grid of random colored viewpports and pick a good text color.
[ClipSphereCylinder](/Cxx/VisualizationAlgorithms/ClipSphereCylinder) | vtkImplicitBoolean vtkClipPolyData | A plane clipped with a sphere and an ellipse. The two transforms place each implicit function into the appropriate position. Two outputs are generated by the clipper.
[CloseWindow](/Cxx/Visualization/CloseWindow) | vtkRenderWindowInteractor vtkRenderWindow | Close a render window.
[CollisionDetection](/Cxx/Visualization/CollisionDetection) | vtkCollisionDetectionFilter | Collison between two spheres.
[ColorActorEdges](/Cxx/Visualization/ColorActorEdges) | vtkActor | Color the edges of an Actor.
[ColorAnActor](/Cxx/Visualization/ColorAnActor) | vtkActor | Color an Actor.
[ColoredAnnotatedCube](/Cxx/VisualizationAlgorithms/ColoredAnnotatedCube) | vtkAnnotatedCubeActor vtkAxesActor vtkCubeSource vtkPropAssembly vtkOrientationMarkerWidget | How to color the individual faces of an annotated cube.
[ColorGlyphs](/Cxx/Visualization/ColorGlyphs) | vtkGlyph3D vtkGlyph3D | Color glyphs.
[ColorSeriesPatches](/Cxx/Visualization/ColorSeriesPatches) | vtkColorSeries | Creates a HTML file called [VTKColorSeriesPatches](http://htmlpreview.github.com/?https://github.com/lorensen/VTKExamples/blob/master/src/Python/Visualization/VTKColorSeriesPatches.html)
[CombustorIsosurface](/Cxx/VisualizationAlgorithms/CombustorIsosurface) | vtkContourFilter | Marching cubes surface of flow density.
[ComplexV](/Cxx/Visualization/ComplexV) | vtkHedgeHog | ComplexV from the VTK Textbook.
[ContourQuadric](/Cxx/VisualizationAlgorithms/ContourQuadric) | vtkQuadric vtkSampleFunction vtkContourFilter | Contouring a quadric function.
[CornerAnnotation](/Cxx/Visualization/CornerAnnotation) | vtkCornerAnnotation | Write text in the corners of a window.
[CorrectlyRenderTranslucentGeometry](/Cxx/Visualization/CorrectlyRenderTranslucentGeometry) | vtkDepthSortPolyData | Correctly Rendering Translucent Geometry.
[CreateBFont](/Cxx/VisualizationAlgorithms/CreateBFont) | vtkClipPolyData vtkImageDataGeometryFilter | A scanned image clipped with a scalar value of 1/2 its maximum intensity produces a mixture of quadrilaterals and triangles.
[CreateColorSeriesDemo](/Cxx/Visualization/CreateColorSeriesDemo) | vtkColorSeries vtkLookupTable | Create a custom vtkColorSeries.
[CubeAxesActor](/Cxx/Visualization/CubeAxesActor) | vtkCubeAxesActor | Display three orthogonal axes with labels.
[CubeAxesActor2D](/Cxx/Visualization/CubeAxesActor2D) | vtkCubeAxesActor2D | This example uses the vtkCubeAxesActor2D to show your scene with axes to indicate the spatial extent of your data.
[Cursor3D](/Cxx/Visualization/Cursor3D) | vtkCursor3D |
[CursorShape](/Cxx/Visualization/CursorShape) | vtkRenderWindow | Change the shape of the cursor.
[CurvatureBandsWithGlyphs](/Cxx/Visualization/CurvatureBandsWithGlyphs) | vtkCurvatures vtkBandedPolyDataContourFilter vtkLookupTable vtkColorSeries vtkGlyph3D | Demonstrates the coloring of a surface by partitioning the gaussian curvature of a surface into bands and using arrows to display the normals on the surface.
[CurvedReformation](/Cxx/Visualization/CurvedReformation) | vtkProbeFilter | Sample a volume with a curved surface. In medical imaging, this is often called curved multi planar reformation.
[CutStructuredGrid](/Cxx/VisualizationAlgorithms/CutStructuredGrid) | vtkCutter | Cut through structured grid with plane. The cut plane is shown solid shaded. A computational plane of constant k value is shown in wireframe for comparison. The colors correspond to flow density. Cutting surfaces are not necessarily planes: implicit functions such as spheres, cylinders, and quadrics can also be used.
[Cutter](/Cxx/VisualizationAlgorithms/Cutter) | vtkCutter | How to use vtkCutter by cutting through a cube.
[DataSetSurface](/Cxx/VisualizationAlgorithms/DataSetSurface) | vtkDataSetSurfaceFilter | Cutting a hexahedron with a plane. The red line on the surface shows the cut.
[DecimateFran](/Cxx/VisualizationAlgorithms/DecimateFran) | vtkDecimatePro | Examples of decimation algorithm. (a) Decimation of laser digitizer data.
[DecimateHawaii](/Cxx/VisualizationAlgorithms/DecimateHawaii) | vtkDecimatePro | Examples of decimation algorithm. (b) Decimation of terrain data.
[DepthSortPolyData](/Cxx/Visualization/DepthSortPolyData) | vtkDepthSortPolyData | Poly Data Depth Sorting.
[DisplacementPlot](/Cxx/VisualizationAlgorithms/DisplacementPlot) | vtkColorTransferFunction vtkWarpVector vtkVectorDot | Show modal lines for a vibrating beam.
[DisplayCoordinateAxes](/Cxx/Visualization/DisplayCoordinateAxes) | vtkOrientationMarkerWidget | Display coordinate axes.
[DisplayQuadricSurfaces](/Cxx/Visualization/DisplayQuadricSurfaces) | vtkQuadric vtkSampleFunction vtkContourFilter | Display Quadric Surfaces.
[DistanceToCamera](/Cxx/Visualization/DistanceToCamera) | vtkDistanceToCamera |
[DrawText](/Cxx/Visualization/DrawText) | vtkTextActor vtkTextProperty | Display Text.
[EdgePoints](/Cxx/Visualization/EdgePoints) | vtkEdgePoints | Generate points along an edge.
[ElevationBandsWithGlyphs](/Cxx/Visualization/ElevationBandsWithGlyphs) | vtkBandedPolyDataContourFilter vtkLookupTable vtkColorSeries vtkGlyph3D | Demonstrates the coloring of a surface by partitioning the elevation into bands and using arrows to display the normals on the surface.
[ExponentialCosine](/Cxx/VisualizationAlgorithms/ExponentialCosine) | vtkWarpScalar | Carpet plots. Visualization of an exponential cosine function. Function values are indicated by surface displacement. Colors indicate derivative values.
[ExtrudePolyDataAlongLine](/Cxx/Visualization/ExtrudePolyDataAlongLine) | vtkRuledSurfaceFilter | Extrude a 2D polydata along a line in 3D space.
[FastSplatter](/Cxx/Visualization/FastSplatter) | vtkFastSplatter | Convolve a splat image with every point in an input image.
[FindCellIntersections](/Cxx/VisualizationAlgorithms/FindCellIntersections) | vtkCellLocator | Find the intersection of a line and the cells in an unstructured dataset
[FireFlow](/Cxx/VisualizationAlgorithms/FireFlow) | vtkPointSource vtkStreamTracer vtkContourFilter vtkVRMLImporter vtkXMLUnstructuredGridReader| Combine geometry from a VRML file and a solution from a vtkUnstructuredGrid file.
[FireFlowDemo](/Cxx/VisualizationAlgorithms/FireFlowDemo) | vtkPointSource vtkStreamTracer vtkContourFilter vtkVRMLImporter vtkXMLUnstructuredGridReader vtkSliderWidget| Combine geometry from a VRML file and a solution from a vtkUnstructuredGrid file (interactive).
[FlatShading](/Cxx/Visualization/FlatShading) | vtkActor |
[FlyingFrogSkinAndTissue](/Cxx/Visualization/FlyingFrogSkinAndTissue) | vtkMetaImageReader vtkFlyingEdges3D vtkWindowedSincPolyDataFilter vtkImageGaussianSmooth | All frog parts and translucent skin.
[FlyingFrogSkinAndTissueB](/Cxx/Visualization/FlyingFrogSkinAndTissueB) | vtkMetaImageReader vtkFlyingEdges3D vtkWindowedSincPolyDataFilter vtkImageGaussianSmooth | All frog parts and translucent skin.
[FlyingFrogSkinAndTissueC](/Cxx/Visualization/FlyingFrogSkinAndTissueC) | vtkMetaImageReader vtkFlyingEdges3D vtkWindowedSincPolyDataFilter vtkImageGaussianSmooth | All frog parts and translucent skin.
[FlyingHeadSlice](/Cxx/VisualizationAlgorithms/FlyingHeadSlice) | vtkFlyingEdges2D | Flying edges used to generate contour lines.
[Follower](/Cxx/Visualization/Follower) | vtkFollower | Draw text that stays right side up.
[FontFile](/Cxx/Visualization/FontFile) | vtkTextProperty | Use an external font.
[FrogSlice](/Cxx/Visualization/FrogSlice) | vtkMetaImageReader | Photographic slice of frog (upper left), segmented frog (upper right) and composite of photo and segmentation (bottom). The purple color represents the stomach and the kidneys are yellow.
[Glyph2D](/Cxx/Filtering/Glyph2D) | vtkGlyph2D |
[Glyph3D](/Cxx/Filtering/Glyph3D) | vtkGlyph3D |
[Glyph3DImage](/Cxx/Visualization/Glyph3DImage) | vtkGlyph3DMapper | Glyph the points in a vtkImageData.
[Glyph3DMapper](/Cxx/Visualization/Glyph3DMapper) | vtkGlyph3DMapper |
[Hanoi](/Cxx/Visualization/Hanoi) |  | Towers of Hanoi.
[HanoiInitial](/Cxx/Visualization/HanoiInitial) |  | Towers of Hanoi - Initial configuration.
[HanoiIntermediate](/Cxx/Visualization/HanoiIntermediate) |  | Towers of Hanoi - Intermediate configuration.
[Hawaii](/Cxx/Visualization/Hawaii) | vtkElevationFilter vtkColorSeries vtkLookupTable | Visualize elevations by coloring the scalar values with a lookup table.
[HeadBone](/Cxx/VisualizationAlgorithms/HeadBone) | vtkMarchingCubes | Marching cubes surface of human bone.
[HeadSlice](/Cxx/VisualizationAlgorithms/HeadSlice) | vtkContourFilter | Marching squares used to generate contour lines.
[HedgeHog](/Cxx/Visualization/HedgeHog) | vtkHedgeHog vtkStructuredGrid | Create oriented lines (hedgehogs) from vector data.
[HideActor](/Cxx/Visualization/HideActor) | vtkPropCollection vtkProp | visible
[HideAllActors](/Cxx/Visualization/HideAllActors) | vtkRenderer | Hide all actors.
[HyperStreamline](/Cxx/VisualizationAlgorithms/HyperStreamline) | vtkHyperStreamline | Example of hyperstreamlines, the four hyperstreamlines shown are integrated along the minor principle stress axis. A plane (colored with a different lookup table) is also shown.
[ImageMapper](/Cxx/Visualization/ImageMapper) | vtkImageMapper | Display an image in 2D.
[ImageOrder](/Cxx/Visualization/ImageOrder) | vtkRenderer | Determine the display order of a stack of images.
[ImageOrientation](/Cxx/Visualization/ImageOrientation) | vtkInteractorStyleImage | Orientation of the view of an image.
[ImageTransparency](/Cxx/Visualization/ImageTransparency) | vtkImageData | Set transparency of image pixels.
[InterpolateCamera](Cxx/Rendering/InterpolateCamera) | vtkInterpolateCamera | Move a camera along a path generated from multiple camera views.
[IronIsoSurface](/Cxx/VisualizationAlgorithms/IronIsoSurface) | vtkContourFilter | Marching cubes surface of iron-protein.
[IsosurfaceSampling](/Cxx/Visualization/IsosurfaceSampling) | vtkProbeFilter | Demonstrates how to create point data on an isosurface.
[Kitchen](/Cxx/Visualization/Kitchen) | vtkStreamTracer vtkStructuredGrid | Demonstrates stream tracing in a kitchen.
[KochSnowflake](/Cxx/Visualization/KochSnowflake) | vtkPolyData vtkPolyLine vtkTriangle vtkLookupTable | Use recursion to represent a Koch snowflake fractal.
[LODProp3D](/Cxx/Visualization/LODProp3D) | vtkLODProp3D | Level of detail rendering.
[LOx](/Cxx/VisualizationAlgorithms/LOx) | vtkStreamTracer vtkTubeFilter | Streamtubes created by using the computational grid just in front of the post as a source for seeds.
[LOxGrid](/Cxx/VisualizationAlgorithms/LOxGrid) | vtkStreamTracer vtkTubeFilter | Portion of computational grid for the LOx post.
[LOxSeeds](/Cxx/VisualizationAlgorithms/LOxSeeds) | vtkStreamTracer vtkTubeFilter | Streamlines seeded with spherical cloud of points. Four separate cloud positions are shown.
[LabelContours](/Cxx/Visualization/LabelContours) | vtkLabeledDataMapper | Label Contours.
[LabelPlacementMapper](/Cxx/Visualization/LabelPlacementMapper) | vtkPointSetToLabelHierarchy vtkLabelPlacementMapper | Display a non-overlapping text label at each point.
[LabeledDataMapper](/Cxx/Visualization/LabeledDataMapper) | vtkLabeledDataMapper | Display the point ID at each point.
[LabeledMesh](/Cxx/Visualization/LabeledMesh) | vtkLabeledDataMapper | Label Mesh.
[Legend](/Cxx/Visualization/Legend) | vtkLegendBoxActor |
[LegendScaleActor](/Cxx/Visualization/LegendScaleActor) | vtkLegendScaleActor | Display the scale of a scene.
[LineWidth](/Cxx/Visualization/LineWidth) | vtkActor vtkProperty | Change the width/thickness of lines in an actor.
[LoopShrink](/Cxx/Visualization/LoopShrink) |  | A network with a loop. VTK 5.0 does not allow you to execute a looping visualization network; this was possible in previous versions of VTK.
[Morph3D](/Cxx/Visualization/Morph3D) | vtkInterpolateDataSetAttributes vtkImplicitModeller vtkContourFilter | Interpolate between datasets.
[Motor](/Cxx/VisualizationAlgorithms/Motor) | vtkBYUReader vtkStructuredPointsReader vtkTexture vtkImplicitTextureCoords | Texture cut used to reveal internal structure of a motor. Two cut planes are used in combination with transparent texture.
[MovableAxes](/Cxx/Visualization/MovableAxes) | vtkFollower vtkAxesActor vtkAssembly | Movable axes.
[MoveActor](/Cxx/Visualization/MoveActor) | vtkInteractorStyleTrackballActor | Moving an Actor.
[MoveCamera](/Cxx/Visualization/MoveCamera) | vtkInteractorStyleTrackballCamera | Moving the Camera.
[MultipleActors](/Cxx/Visualization/MultipleActors) | vtkActor | Multiple Actors.
[NamedColorPatches](/Cxx/Visualization/NamedColorPatches) | vtkNamedColors | Creates a HTML file called [VTKNamedColorPatches](http://htmlpreview.github.com/?https://github.com/lorensen/VTKExamples/blob/master/src/Python/Visualization/VTKNamedColorPatches.html)
[NamedColors](/Cxx/Visualization/NamedColors) | vtkNamedColors | Demonstrate the use of the vtkNamedColors class.
[NoShading](/Cxx/Visualization/NoShading) | vtkActor |
[NormalsDemo](/Cxx/Visualization/NormalsDemo) | vtkPolyDataNormals | Demo different options to generate normals.
[Office](/Cxx/VisualizationAlgorithms/Office) | vtkPointSource vtkStreamTracer | Using random point seeds to create streamlines.
[OfficeA](/Cxx/VisualizationAlgorithms/OfficeA) | vtkPointSource vtkStreamTracer | Corresponds to Fig 9-47(a) in the VTK textbook.
[OfficeTube](/Cxx/VisualizationAlgorithms/OfficeTube) | vtkStreamTracer vtkTubeFilter | The stream polygon. Sweeping a polygon to form a tube.
[Opacity](/Cxx/Visualization/Opacity) | vtkActor | Transparency, transparent.
[OpenVRCone](/Cxx/Visualization/OpenVRCone) |  | VTK + OpenVR Cone rendering example.
[OpenVRCube](/Cxx/Visualization/OpenVRCube) |  | VTK + OpenVR Cube rendering example.
[OpenVRCylinder](/Cxx/Visualization/OpenVRCylinder) |  | VTK + OpenVR Cylinder rendering example.
[OpenVRSphere](/Cxx/Visualization/OpenVRSphere) |  | VTK + OpenVR Sphere rendering example.
[OrientedGlyphs](/Cxx/Visualization/OrientedGlyphs) | vtkGlyph3D | Create oriented glyphs from vector data.
[PineRootConnectivity](/Cxx/VisualizationAlgorithms/PineRootConnectivity) | vtkMCubesReader vtkPolyDataConnectivityFilter | Applying the connectivity filter to remove noisy isosurfaces.
[PineRootConnectivityA](/Cxx/VisualizationAlgorithms/PineRootConnectivityA) | vtkMCubesReader vtkPolyDataConnectivityFilter | The isosurface, with no connectivity filter applied.
[PineRootDecimation](/Cxx/VisualizationAlgorithms/PineRootDecimation) | vtkMCubesReader vtkDecimatePro vtkConnectivityFilter | Applying the decimation and connectivity filters to remove noisy isosurfaces and reduce data size.
[PlateVibration](/Cxx/VisualizationAlgorithms/PlateVibration) | vtkWarpVector vtkVectorDot | Demonstrates the motion of a vibrating beam.
[PointDataSubdivision](/Cxx/Visualization/PointDataSubdivision) | vtkLinearSubdivisionFilter vtkButterflySubdivisionFilter | Demonstrates the effect of applying these filters on various sources.
[ProteinRibbons](/Cxx/Visualization/ProteinRibbons) | vtkProteinRibbonFilter | Display pdb ribbons.
[PointSize](/Cxx/Visualization/PointSize) | vtkActor |
[ProbeCombustor](/Cxx/VisualizationAlgorithms/ProbeCombustor) | vtkProbeFilter | Probing data in a combustor.  Probes are regular arrays of 50 by 50 points that are then passed through a contouring filter.
[ProgrammableGlyphFilter](/Cxx/Visualization/ProgrammableGlyphFilter) | vtkProgrammableGlyphFilter | Generate a custom glyph at each point.
[PseudoVolumeRendering](/Cxx/VolumeRendering/PseudoVolumeRendering) | vtkCutter vtkContourFilter | 100 cut planes with opacity of 0.05. Rendered back-to-front to simulate volume rendering.
[QuadraticSurface](/Cxx/Visualization/QuadraticSurface) | vtkQuadric | Display a quadratic surface.
[QuadricLODActor](/Cxx/Visualization/QuadricLODActor) | vtkQuadricLODActor | Level of detail adjustment.
[QuadricVisualization](/Cxx/Visualization/QuadricVisualization) | vtkQuadric vtkSampleFunction vtkContourFilter | Visualizing a quadric function.
[RandomProbe](/Cxx/Visualization/RandomProbe) | vtkProbeFilter | Demonstrates how to probe a dataset with random points and select points inside the data set.
[RenderLargeImage](/Cxx/Visualization/RenderLargeImage) | vtkRenderLargeImage | Render a large image, larger than a window.
[RenderView](/Cxx/Views/RenderView) | vtkRenderView | A little bit easier rendering.
[ReverseAccess](/Cxx/Visualization/ReverseAccess) | vtkActor | Demonstrates how to access the source (e.g. vtkSphereSource) of an actor reversely.
[RotateActor](/Cxx/Visualization/RotateActor) | vtkActor | Rotate an Actor.
[ScalarBarActor](/Cxx/Visualization/ScalarBarActor) | vtkScalarBarActor | Display a color bar.
[ScalarBarActorColorSeries](/Cxx/Visualization/ScalarBarActorColorSeries) | vtkScalarBarActor vtkColorSeries | Display a color bar with a color series lookup table.
[ScalarVisibility](/Cxx/Visualization/ScalarVisibility) | vtkDataSetMapper | Switch between coloring the actor and coloring the data.
[ScaleGlyphs](/Cxx/Visualization/ScaleGlyphs) | vtkGlyph3D vtkGlyph3D | Scale glyphs.
[SceneBounds](/Cxx/Visualization/SceneBounds) | vtkRenderer | Get the bounds of the whole scene.
[SelectWindowRegion](/Cxx/Visualization/SelectWindowRegion) | vtkInteractorStyleRubberBand2D | Select a region of a window.
[SingleSplat](/Cxx/VisualizationAlgorithms/SingleSplat) | vtkGaussianSplatter | Elliptical splatting. (a) Single elliptical splat with eccentricity E=10.  Cone shows orientation of vector.
[SpikeFran](/Cxx/VisualizationAlgorithms/SpikeFran) | vtkGlyph3D | Glyphs indicate surface normals on model of human face. Glyph positions are randomly selected.
[SplatFace](/Cxx/VisualizationAlgorithms/SplatFace) | vtkGaussianSplatter | Elliptical splatting. (b) Surface reconstructed using elliptical splats into 100^3 volume followed by isosurface extraction. Points regularly subsampled and overlaid on original mesh.
[Stocks](/Cxx/VisualizationAlgorithms/Stocks) | vtkRibbonFilter vtkLinearExtrusionFilter | Two views from the stock visualization script. The top shows closing price over time; the bottom shows volume over time.
[StreamLines](/Cxx/Visualization/StreamLines) | vtkStreamTracer | Streamlines.
[StreamlinesWithLineWidget](/Cxx/VisualizationAlgorithms/StreamlinesWithLineWidget) | vtkCallbackCommand vtkLineWidget | Using the vtkLineWidget to produce streamlines in the combustor dataset.  The StartInteractionEvent turns the visibility of the streamlines on; the InteractionEvent causes the streamlines to regenerate themselves.
[StructuredDataTypes](/Cxx/Visualization/StructuredDataTypes) |  | Demonstration of structured data types.
[TensorAxes](/Cxx/VisualizationAlgorithms/TensorAxes) | vtkPointLoad vtkTensorGlyph | Display the scaled and oriented principal axes of the stress tensor.
[TensorEllipsoids](/Cxx/VisualizationAlgorithms/TensorEllipsoids) | vtkPointLoad vtkTensorGlyph | Display the scaled and oriented principal axes as tensor ellipsoids representing the stress tensor.
[TensorGlyph](/Cxx/Visualization/TensorGlyph) | vtkTensorGlyph | Draw a rotated/scaled glyph at each point.
[TextSource](/Cxx/Visualization/TextSource) | vtkTextSource | Display text.
[TransformActor](/Cxx/Visualization/TransformActor) | vtkActor | Transform an Actor.
[TransformActorCollection](/Cxx/Visualization/TransformActorCollection) | vtkActorCollection | Transform an actor collection.
[TubesFromSplines](/Cxx/VisualizationAlgorithms/TubesFromSplines) | vtkTubeFilter vtkParametricFunctionSource  vtkTupleInterpolator | Create tubes from interpolated points and scalars.
[TubesWithVaryingRadiusAndColors](/Cxx/VisualizationAlgorithms/TubesWithVaryingRadiusAndColors) | vtkTubeFilter | Create tubes with varying radius and colors.
[VectorField](/Cxx/Visualization/VectorField) | vtkGlyph2D vtkImageData |
[VectorOfActors](/Cxx/Visualization/VectorOfActors) | vtkActor | Multiple Actors in a Vector.
[VectorText](/Cxx/Visualization/VectorText) | vtkVectorText | Display high resolution text.
[VelocityProfile](/Cxx/VisualizationAlgorithms/VelocityProfile) | vtkMultiBlockPLOT3DReader vtkStructuredGridGeometryFilter vtkAppendPolyData vtkWarpVector | Warping the geometry of three planes to show flow momentum.
[VertexGlyphFilter](/Cxx/Filtering/VertexGlyphFilter) | vtkVertexGlyphFilter | Add a vertex to each point.
[ViewFrog](/Cxx/Visualization/ViewFrog) | vtkMetaImageReader vtkMarchingCubes vtkImageGaussianSmooth vtkWindowedSincPolyDataFilter | The complete frog without skin.
[ViewFrogA](/Cxx/Visualization/ViewFrogA) | vtkMetaImageReader vtkMarchingCubes vtkImageGaussianSmooth vtkWindowedSincPolyDataFilter | The complete frog without skin or skeleton.
[ViewFrogBoth](/Cxx/Visualization/ViewFrogBoth) | vtkMetaImageReader vtkMarchingCubes vtkImageGaussianSmooth vtkImageGaussianSmooth | The frog’s brain. Model extracted without smoothing (left) and with smoothing (right).
[ViewFrogSkinAndTissue](/Cxx/Visualization/ViewFrogSkinAndTissue) | vtkMetaImageReader vtkMarchingCubes vtkWindowedSincPolyDataFilter vtkImageGaussianSmooth | All frog parts and translucent skin.
[Visualize2DPoints](/Cxx/Visualization/Visualize2DPoints) | vtkPolyDataMapper2D vtkProperty2D | Visualize a 2D Set of Points.
[VisualizeImageData](/Cxx/Visualization/VisualizeImageData) | vtkDataSetMapper | Visualize the points of an ImageData.
[VisualizeVTP](/Cxx/Visualization/VisualizeVTP) | vtkXMLPolyDataReader vtkPolyDataMapper | Visualize a VTP File.
[VoxelsOnBoundary](/Cxx/ImageData/VoxelsOnBoundary) | vtkMultiThreshold vtkMetaImageReader | Extract voxels on the border of an isosurface.
[WarpCombustor](/Cxx/VisualizationAlgorithms/WarpCombustor) | vtkWarpScalar vtkMultiBlockPLOT3DReader | Carpet plots. Carpet plot of combustor flow energy in a structured grid. Colors and plane displacement represent energy values.
[WindowSize](/Cxx/Visualization/WindowSize) | vtkRenderWindow:SetSize | Change the size of a window.
[WindowTitle](/Cxx/Visualization/WindowTitle) | vtkRenderWindow | Change the title of a window.
[Wireframe](/Cxx/Visualization/Wireframe) | vtkActor |

## Volume Rendering

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[FixedPointVolumeRayCastMapperCT](/Cxx/VolumeRendering/FixedPointVolumeRayCastMapperCT) | vtkFixedPointVolumeRayCastMapper vtkColorTransferFunction vtkDICOMImageReader vtkMetaImageReader | Volume render DICOM or Meta volumes with various vtkColorTransferFunction's.
[HAVS](/Cxx/VolumeRendering/HAVSVolumeMapper) | vtkHAVSVolumeMapper |
[IntermixedUnstructuredGrid](/Cxx/VolumeRendering/IntermixedUnstructuredGrid) | vtkUnstructuredGridVolumeRayCastMapper vtkSLCReader | mix of poly data and unstructured grid volume mapper.
[MinIntensityRendering](/Cxx/VolumeRendering/MinIntensityRendering) | vtkFixedPointVolumeRayCastMapper | Min intensity rendering.
[RayCastIsosurface](/Cxx/VolumeRendering/RayCastIsosurface) | vtkOpenGLGPUVolumeRayCastMapper | Isosufaces produced by volume rendering.
[SimpleRayCast](/Cxx/VolumeRendering/SimpleRayCast) | vtkFixedPointVolumeRayCastMapper | Volume rendering of a high potential iron protein.
[SmartVolumeMapper](/Cxx/VolumeRendering/SmartVolumeMapper) | vtkSmartVolumeMapper | Smart volume mapper.

## User Interaction

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[AreaPicking](/Cxx/Picking/AreaPicking) | vtkAreaPicker | Area Picking.
[Assembly](/Cxx/Interaction/Assembly) | vtkAssembly | Combine/group actors into an assembly.
[CallBack](/Cxx/Interaction/CallBack) | vtkCallbackCommand vtkOrientationMarkerWidget | Setting up a callback with client data. Two different methods are demonstrated.
[CallData](/Cxx/Interaction/CallData) | vtkCommand | Pass an observer a value (via CallData).
[CellPicking](/Cxx/Picking/CellPicking) | vtkCellPicker | Cell Picking.
[ClientData](/Cxx/Interaction/ClientData) | vtkCommand | Give an observer access to an object (via ClientData).
[DoubleClick](/Cxx/Interaction/DoubleClick) | vtkInteractorStyleTrackballCamera | Catch a double click.
[EllipticalButton](/Cxx/Interaction/EllipticalButton) | vtkEllipticalButtonSource vtkButtonWidget | Create an elliptical button.
[Game](/Cxx/Interaction/Game) | vtkInteractorStyleTrackballActor | Move a cube into a sphere.
[HighlightPickedActor](/Cxx/Picking/HighlightPickedActor) | vtkPropPicker | Highlight a picked actor by changing its color.
[HighlightSelectedPoints](/Cxx/Picking/HighlightSelectedPoints) | vtkExtractGeometry | Highlight Selected Points.
[HighlightSelection](/Cxx/Picking/HighlightSelection) | vtkExtractPolyDataGeometry | Highlight selection.
[HighlightWithSilhouette](/Cxx/Picking/HighlightWithSilhouette) | vtkPropPicker vtkPolyDataSilhouette| Highlight a picked actor by adding a silhouette.
[ImageClip](/Cxx/Interaction/ImageClip) | vtkImageClip | Demonstrates how to interactively select and display a region of an image.
[ImageRegion](/Cxx/Interaction/ImageRegion) | vtkCommand | Select a region of an image.
[InteractorStyleTerrain](/Cxx/Interaction/InteractorStyleTerrain) | vtkInteractorStyleTerrain | Terrain mode.
[InteractorStyleUser](/Cxx/Interaction/InteractorStyleUser) | vtkInteractorStyleUser | Create a completely custom interactor style (no default functionality is provided)
[KeypressEvents](/Cxx/Interaction/KeypressEvents) | vtkInteractorStyleTrackballCamera | Handle keypress events.
[KeypressObserver](/Cxx/Interaction/KeypressObserver) | vtkCallbackCommand | This uses a callback function rather than a derived interactor class. Handle keypress events (lightweight).
[MouseEvents](/Cxx/Interaction/MouseEvents) | vtkInteractorStyleTrackballCamera | Subclass the interactor style. Handle mouse events.
[MouseEventsObserver](/Cxx/Interaction/MouseEventsObserver) | vtkCallbackCommand | Use an observer. Handle mouse events (light weight).
[MoveAGlyph](/Cxx/Interaction/MoveAGlyph) | vtkGlyph3D | Drag a glyph around.
[MoveAVertexUnstructuredGrid](/Cxx/Interaction/MoveAVertexUnstructuredGrid) | vtkPointPicker | Click and drag a vertex of a vtkUnstructuredGrid.
[ObserverMemberFunction](/Cxx/Interaction/ObserverMemberFunction) |  | Set observers to be class member functions.
[PickableOff](/Cxx/Interaction/PickableOff) | vtkActor | Disallow interaction with a specific actor.
[Picking](/Cxx/Interaction/Picking) | vtkPropPicker | Get the world coordinate of the mouse click (if you clicked an actor)
[PointPicker](/Cxx/Interaction/PointPicker) | vtkPointPicker | Get the coordinates of the closest point in the data set to the mouse click.
[RubberBand2D](/Cxx/Interaction/RubberBand2D) | vtkInteractorStyleRubberBand2D |
[RubberBand2DObserver](/Cxx/Interaction/RubberBand2DObserver) | vtkInteractorStyleRubberBand2D | RubberBand2D Observer.
[RubberBand3D](/Cxx/Interaction/RubberBand3D) | vtkInteractorStyleRubberBand3D |
[RubberBandPick](/Cxx/Interaction/RubberBandPick) | vtkInteractorStyleRubberBandPick |
[RubberBandZoom](/Cxx/Interaction/RubberBandZoom) | vtkInteractorStyleRubberBandZoom |
[SelectAVertex](/Cxx/Interaction/SelectAVertex) | vtkPointPicker | Click and drag a vertex of a vtkPolyData.
[SelectAnActor](/Cxx/Interaction/SelectAnActor) | vtkPropPicker | Select an actor.
[ShiftAndControl](/Cxx/Interaction/ShiftAndControl) | vtkRenderWindowInteractor | Hold/holding down a key. Check if shift or control is being held.
[StyleSwitch](/Cxx/Interaction/StyleSwitch) | vtkInteractorStyleSwitch | Choose between multiple interaction modes.
[TrackballActor](/Cxx/Interaction/TrackballActor) | vtkInteractorStyleTrackballActor | Trackball actor mode.
[TrackballCamera](/Cxx/Interaction/TrackballCamera) | vtkInteractorStyleTrackballCamera | Trackball camera mode.
[UserEvent](/Cxx/Interaction/UserEvent) |  | Simple observer. Create, invoke, and handle a custom event.
[WorldPointPicker](/Cxx/Interaction/WorldPointPicker) | vtkWorldPointPicker | Get world coordinates of mouse click.

## Working with Images

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Actor2D](/Cxx/Images/Actor2D) | vtkActor2D vtkMapper2D | 2D actor and mapper.
[BackgroundImage](/Cxx/Images/BackgroundImage) | vtkImageCanvasSource2D | Display an image as the background of a scene.
[BorderPixelSize](/Cxx/Images/BorderPixelSize) | vtkImageSliceMapper | Set the size of border pixels.
[CannyEdgeDetector](/Cxx/Images/CannyEdgeDetector) |  | Perform Canny edge detection on an image.
[Cast](/Cxx/Images/Cast) | vtkImageCast | Cast an image to a different type.
[DotProduct](/Cxx/Images/DotProduct) | vtkImageDotProduct | Compute the pixel-wise dot product of two vector images.
[DrawOnAnImage](/Cxx/Images/DrawOnAnImage) | vtkImageCanvasSource2D | Drawing on an image.
[DrawShapes](/Cxx/Images/DrawShapes) | vtkImageCanvasSource2D | Drawing shapes in an image.
[ExtractComponents](/Cxx/Images/ExtractComponents) | vtkImageExtractComponents | Extract components of an image. This can be used to get, for example, the red channel of an image.
[FillWindow](/Cxx/Images/FillWindow) | vtkCamera | Fit imageSetup the camera to fill the window with an image.
[ImageAccumulateGreyscale](/Cxx/Images/ImageAccumulateGreyscale) | vtkImageAccumulate vtkBarChartActor | Display a grey scale histogram.
[ImageCheckerboard](/Cxx/Images/ImageCheckerboard) | vtkImageCheckerboard | Visually Compare Two Images.
[ImageCityBlockDistance](/Cxx/Images/ImageCityBlockDistance) | vtkImageCityBlockDistance | Compute the Manhattan distance from every point to every black point in a binary image.
[ImageDilateErode3D](/Cxx/Images/ImageDilateErode3D) | vtkImageDilateErode3D | Dilate or erode an image.
[ImageExport](/Cxx/Images/ImageExport) | vtkImageExport | Export an image to a C array.
[ImageGridSource](/Cxx/Images/ImageGridSource) | vtkImageGridSource | Create a image of a grid.
[ImageHistogram](/Cxx/Images/ImageHistogram) | vtkImageHistogram | Compute the histogram of an image.
[ImageHybridMedian2D](/Cxx/Images/ImageHybridMedian2D) | vtkImageHybridMedian2D | Median filter an image.
[ImageIdealHighPass](/Cxx/Images/ImageIdealHighPass) | vtkImageIdealHighPass | High pass filter an image.
[ImageImport](/Cxx/Images/ImageImport) | vtkImageImport | Import an image from a C array.
[ImageIslandRemoval2D](/Cxx/Images/ImageIslandRemoval2D) | vtkImageIslandRemoval2D | Remove small patches from an image.
[ImageMagnify](/Cxx/Images/ImageMagnify) | vtkImageMagnify | Supersample and stretch an image.
[ImageMandelbrotSource](/Cxx/Images/ImageMandelbrotSource) | vtkImageMandelbrotSource | Create a Mandelbrot image.
[ImageMask](/Cxx/Images/ImageMask) | vtkImageMask | Mask a region of an image.
[ImageMathematics](/Cxx/Images/ImageMathematics) | vtkImageMathematics | Perform mathematical operations on an image.
[ImageMedian3D](/Cxx/Images/ImageMedian3D) | vtkImageMedian3D | Median filter a 3d or 2d image.
[ImageMirrorPad](/Cxx/Images/ImageMirrorPad) | vtkImageMirrorPad | Pad the edges of an extended image by mirror existing pixels.
[ImageNonMaximumSuppression](/Cxx/Images/ImageNonMaximumSuppression) | vtkImageNonMaximumSuppression | Find peaks in an image using non maximum suppression.
[ImageOpenClose3D](/Cxx/Images/ImageOpenClose3D) | vtkImageOpenClose3D | Open or close (morphologically) an image.
[ImageRFFT](/Cxx/Images/ImageRFFT) | vtkImageRFFT | Inverse FFT.
[ImageRange3D](/Cxx/Images/ImageRange3D) | vtkImageRange3D | Replace every pixel with the range of its neighbors according to a kernel.
[ImageRotate](/Cxx/Images/ImageRotate) | vtkImageSlice vtkImageResliceMapper | Rotate a 2D image. This is even more powerful than vtkImageSliceMapper. It can also do oblique slices.
[ImageSeparableConvolution](/Cxx/Images/ImageSeparableConvolution) | vtkImageSeparableConvolution | Convolve a separable kernel with an image.
[ImageShiftScale](/Cxx/Images/ImageShiftScale) | vtkImageShiftScale | Shift and scale an image.
[ImageSinusoidSource](/Cxx/Images/ImageSinusoidSource) | vtkImageSinusoidSource | Create a sinusoidal image.
[ImageSlice](/Cxx/Images/ImageSlice) | vtkImageSlice vtkImageResliceMapper | Visualize and interact with an image. This is even more powerful than vtkImageSliceMapper. It can also do oblique slices.
[ImageSliceMapper](/Cxx/Images/ImageSliceMapper) | vtkImageSlice vtkImageSliceMapper | Visualize and interact with an image. This is the new way to do this. It is much more powerful.
[ImageStack](/Cxx/Images/ImageStack) | vtkImageStack | Display layers of images.
[ImageStencil](/Cxx/Images/ImageStencil) | vtkImageStencil vtkImageToImageStencil | Copy one image into another image.
[ImageText](/Cxx/Images/ImageText) | vtkFreeTypeUtilities vtkImageBlend | Draw text in an image.
[ImageThreshold](/Cxx/Images/ImageThreshold) | vtkImageThreshold | Threshold an image.
[ImageToPolyDataFilter](/Cxx/Images/ImageToPolyDataFilter) | vtkImageToPolyDataFilter vtkImageQuantizeRGBToIndex | Convert a vtkImageData to a vtkPolyData.
[ImageToStructuredPoints](/Cxx/Images/ImageToStructuredPoints) | vtkImageToStructuredPoints | Convert a vtkImageData to a vtkStructuredPoints.
[InteractWithImage](/Cxx/Images/InteractWithImage) | vtkImageActor vtkInteractorStyleImage | Visualize and interact with an image.
[Interpolation](/Cxx/Images/Interpolation) | vtkImageSlice vtkImageProperty | Set the interpolation type for the display of an image. If pixels look blurry instead of sharp when zoomed in, change this.
[MarkKeypoints](/Cxx/Images/MarkKeypoints) | vtkVectorText vtkFollower | Mark keypoints in an image.
[NegativeIndices](/Cxx/Images/NegativeIndices) | vtkImageData | A very powerful feature of vtkImageData is that you can use negative indices.
[PickPixel](/Cxx/Images/PickPixel) | vtkPropPicker | Picking a pixel.
[PickPixel2](/Cxx/Images/PickPixel2) | vtkPropPicker | Picking a pixel 2 - modified version for exact pixel values.
[RTAnalyticSource](/Cxx/Images/RTAnalyticSource) | vtkRTAnalyticSource | An image source that can be used for regression testing
[StaticImage](/Cxx/Images/StaticImage) | vvtkImageViewer2 | This will display the image, but not allow you to interact with it.
[Transparency](/Cxx/Images/Transparency) | vtkImageMapToColors vtkLookupTable | Make part of an image transparent.

## Image Processing

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Attenuation](/Cxx/ImageProcessing/Attenuation) | vtkImageGaussianSmooth vtkImageMathematics vtkImageShiftScale | This MRI image illustrates attenuation that can occur due to sensor position.  The artifact is removed by dividing by the attenuation profile determined manually.
[CenterAnImage](/Cxx/Images/CenterAnImage) | vtkImageChangeInformation | Center an image.
[Colored2DImageFusion](/Cxx/Images/Colored2DImageFusion) | vtkImageMapToColors | Blending 2D images with different color maps.
[CombineImages](/Cxx/Images/CombineImages) | vtkImageBlend | Combine two images.
[CombiningRGBChannels](/Cxx/Images/CombiningRGBChannels) | vtkImageAppendComponents | Combine layers into an RGB image.
[EnhanceEdges](/Cxx/ImageProcessing/EnhanceEdges) | vtkImageLaplacian vtkImageMathematics | High-pass filters can extract and enhance edges in an image. Subtraction of the Laplacian (middle) from the original image (left) results in edge enhancement or a sharpening operation (right).
[Flip](/Cxx/Images/Flip) | vtkImageFlip | Flip an image.
[GaussianSmooth](/Cxx/ImageProcessing/GaussianSmooth) | vtkImageGaussianSmooth | Low-pass filters can be implemented as convolution with a Gaussian kernel.
[Gradient](/Cxx/Images/Gradient) | vtkImageGradient | Compute the gradient vector at every pixel.
[HybridMedianComparison](/Cxx/ImageProcessing/HybridMedianComparison) | vtkImageHybridMedian2D vtkImageMedian3D | Comparison of median and hybrid-median filters. The hybrid filter preserves corners and thin lines, better than the median filter.
[IdealHighPass](/Cxx/ImageProcessing/IdealHighPass) | vtkImageFFT vtkImageRFFT vtkImageIdealHighPass vtkImageButterworthHighPass | This figure shows two high-pass filters in the frequency domain. The Butterworth high-pass filter has a gradual attenuation that avoids ringing produced by the ideal high-pass filter with an abrupt transition.
[ImageAccumulate](/Cxx/Images/ImageAccumulate) | vtkImageAccumulate | Histogram
[ImageAnisotropicDiffusion2D](/Cxx/Images/ImageAnisotropicDiffusion2D) | vtkImageAnisotropicDiffusion2D | Anisotropic diffusion (2D).
[ImageContinuousDilate3D](/Cxx/Images/ImageContinuousDilate3D) | vtkImageContinuousDilate3D | Dilate an image.
[ImageContinuousErode3D](/Cxx/Images/ImageContinuousErode3D) | vtkImageContinuousErode3D | Erode an image.
[ImageConvolve](/Cxx/Images/ImageConvolve) | vtkImageConvolve | Convolve an image with a kernel.
[ImageCorrelation](/Cxx/Images/ImageCorrelation) | vtkImageCorrelation | Correlate two images.
[ImageDifference](/Cxx/Images/ImageDifference) | vtkImageDifference | Compute the difference image of two images.
[ImageDivergence](/Cxx/Images/ImageDivergence) | vtkImageDivergence | Divergence of a vector field.
[ImageEllipsoidSource](/Cxx/Images/ImageEllipsoidSource) | vtkImageEllipsoidSource | Create an image of an ellipsoid.
[ImageFFT](/Cxx/Images/ImageFFT) | vtkImageFFT | Compute the FFT of an image.
[ImageGaussianSmooth](/Cxx/Images/ImageGaussianSmooth) | vtkImageGaussianSmooth | Smooth an image.
[ImageGradient](/Cxx/VisualizationAlgorithms/ImageGradient) | vtkImageMagnify vtkImageGaussianSmooth vtkImageGradient vtkImageEuclideanToPolar vtkImageExtractComponents vtkImageHSVToRGB | Create an imaging pipeline to visualize gradient information.
[ImageGradientMagnitude](/Cxx/Images/ImageGradientMagnitude) | vtkImageGradientMagnitude | Compute the magnitude of the gradient at each pixel of an image.
[ImageLaplacian](/Cxx/Images/ImageLaplacian) | vtkImageLaplacian | Compute the Laplacian of an image.
[ImageLuminance](/Cxx/Images/ImageLuminance) | vtkImageLuminance | Convert RGB image to greyscale (luminance).
[ImageMagnitude](/Cxx/Images/ImageMagnitude) | vtkImageMagnitude | grayscaleConvert RGB image to grey scale.
[ImageMapToColors](/Cxx/Images/ImageMapToColors) | vtkImageMapToColors | Use a lookup table to map scalar (gray scale) values to colorsConvert grey scale image to RGB.
[ImageNoiseSource](/Cxx/Images/ImageNoiseSource) | vtkImageNoiseSource | Create an image of noise.
[ImagePermute](/Cxx/Images/ImagePermute) | vtkImagePermute | Switch axes of an image.
[ImageShrink3D](/Cxx/Images/ImageShrink3D) | vtkImageShrink3D | Resample an image.
[ImageSobel2D](/Cxx/Images/ImageSobel2D) | vtkImageSobel2D | Sobel edge detection 2D.
[ImageValueRange](/Cxx/Images/ImageValueRange) | vtkImageData | Get the range of image pixel values (min/max).
[ImageVariance3D](/Cxx/Images/ImageVariance3D) | vtkImageVariance3D | Construct a new image consisting of the variance of the input image at each pixel.
[ImageWarp](/Cxx/Images/ImageWarp) | vtkBMPReader vtkImageLuminance vtkWarpScalar vtkMergeFilter | Combine the imaging and visualization pipelines to deform an image in the z-direction. The vtkMergeFilter is used to combine the warped surface with the original color data.
[IsoSubsample](/Cxx/ImageProcessing/IsoSubsample) | vtkImageMarchingCubes vtkImageShrink3D vtkImageGaussianSmooth | This figure demonstrates aliasing that occurs when a high-frequency signal is subsampled. High frequencies appear as low frequency artifacts. The left image is an isosurface of a skull after subsampling. The right image used a low-pass filter before subsampling to reduce aliasing.
[MedianComparison](/Cxx/ImageProcessing/MedianComparison) | vtkImageGaussianSmooth vtkImageMedian3D vtkImageNoiseSource | Comparison of Gaussian and Median smoothing for reducing low-probability high-amplitude noise.
[MorphologyComparison](/Cxx/ImageProcessing/MorphologyComparison) | vtkImageDilateErode3D vtkImageSeedConnectivity | This figure demonstrates various binary filters that can alter the shape of segmented regions.
[Pad](/Cxx/ImageProcessing/Pad) | vtkImageConstantPad vtkImageMirrorPad | Convolution in frequency space treats the image as a periodic function. A large kernel can pick up features from both sides of the image. The lower-left image has been padded with zeros to eliminate wraparound during convolution. On the right, mirror padding has been used to remove artificial edges introduced by borders.
[RGBToHSI](/Cxx/Images/RGBToHSI) | vtkImageRGBToHSI | Convert RGB to HSI.
[RGBToHSV](/Cxx/Images/RGBToHSV) | vtkImageRGBToHSV | Convert RGB to HSV.
[RGBToYIQ](/Cxx/Images/RGBToYIQ) | vtkImageRGBToYIQ | Convert RGB to YIQ.
[RescaleAnImage](/Cxx/ImageProcessing/RescaleAnImage) | vtkImageShiftScale | Rescale an image
[ResizeImage](/Cxx/Images/ResizeImage) | vtkImageResize vtkImageSincInterpolator | Resize an image using a sinc interpolator.
[ResizeImageDemo](/Cxx/Images/ResizeImageDemo) | vtkImageResize vtkImageSincInterpolator | Demonstrate allsinc interpolators to resize an image.
[VTKSpectrum](/Cxx/ImageProcessing/VTKSpectrum) | vtkImageFFT vtkImageFourierCenter vtkImageLogarithmicScale vtkImageMagnitude | The discrete Fourier transform changes an image from the spatial domain into the frequency domain, where each pixel represents a sinusoidal function. This figure shows an image and its power spectrum displayed using a logarithmic transfer function.

## Widgets

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[AffineWidget](/Cxx/Widgets/AffineWidget) | vtkAffineWidget | Apply an affine transformation interactively.
[AngleWidget](/Cxx/Widgets/AngleWidget) | vtkAngleWidget |
[AngleWidget2D](/Cxx/Widgets/AngleWidget2D) | vtkAngleWidget vtkAngleRepresentation2D | vtkAngleWidget + vtkAngleRepresentation2D.
[BalloonWidget](/Cxx/Widgets/BalloonWidget) | vtkBalloonWidget |
[BiDimensionalWidget](/Cxx/Widgets/BiDimensionalWidget) | vtkBiDimensionalWidget | When would you use this?
[BorderWidget](/Cxx/Widgets/BorderWidget) | vtkBorderWidget | 2D selection, 2D box.
[BoxWidget](/Cxx/Widgets/BoxWidget) | vtkBoxWidget |
[BoxWidget2](/Cxx/Widgets/BoxWidget2) | vtkBoxWidget2 |
[CaptionWidget](/Cxx/Widgets/CaptionWidget) | vtkCaptionWidget |
[CheckerboardWidget](/Cxx/Widgets/CheckerboardWidget) | vtkCheckerboardWidget vtkCheckerboardRepresentation | Compare two images using a checkerboard.
[ContourWidget](/Cxx/Widgets/ContourWidget) | vtkContourWidget | Create a contour from a set of points and dynamically change the contour using the points as control points.
[Cursor2D](/Cxx/Visualization/Cursor2D) | vtkCursor2D |
[DistanceWidget](/Cxx/Widgets/DistanceWidget) | vtkDistanceWidget |
[HoverWidget](/Cxx/Widgets/HoverWidget) | vtkHoverWidget | How to detect a hover?
[ImagePlaneWidget](/Cxx/Widgets/ImagePlaneWidget) | vtkImagePlaneWidget |
[ImageTracerWidget](/Cxx/Widgets/ImageTracerWidget) | vtkImageTracerWidget | Scribble on an image.
[ImageTracerWidgetInsideContour](/Cxx/Widgets/ImageTracerWidgetInsideContour) | vtkImageTracerWidget | Highlight pixels inside a non-regular region scribbled on an image.
[ImageTracerWidgetNonPlanar](/Cxx/Widgets/ImageTracerWidgetNonPlanar) | vtkImageTracerWidget | Draw on a non-planar surface.
[ImplicitPlaneWidget2](/Cxx/Widgets/ImplicitPlaneWidget2) | vtkImplicitPlaneWidget2 | Clip polydata with an implicit plane.
[LineWidget2](/Cxx/Widgets/LineWidget2) | vtkLineWidget2 |
[LogoWidget](/Cxx/Widgets/LogoWidget) | vtkLogoWidget | Logo widget.
[OrientationMarkerWidget](/Cxx/Widgets/OrientationMarkerWidget) | vtkOrientationMarkerWidget | Display a polydata as an orientation icon.
[PlaneWidget](/Cxx/Widgets/PlaneWidget) | vtkPlaneWidget | Interact with a plane.
[PolygonalSurfacePointPlacer](/Cxx/PolyData/PolygonalSurfacePointPlacer) | vtkPolygonalSurfacePointPlacer | Used in conjunction with vtkContourWidget to draw curves on a surface.
[RectilinearWipeWidget](/Cxx/Widgets/RectilinearWipeWidget) | vtkImageRectilinearWipe vtkRectilinearWipeWidget vtkRectilinearWipeRepresentation | Compare two images.
[SeedWidget](/Cxx/Widgets/SeedWidget) | vtkSeedWidget | Seed widget.
[SeedWidgetImage](/Cxx/Widgets/SeedWidgetImage) | vtkImageViewer2 vtkSeedWidget | How to start the interaction?
[SeedWidgetWithCustomCallback](/Cxx/Widgets/SeedWidgetWithCustomCallback) | vtkCommand vtkPointHandleRepresentation2D | How to place points in a scene using a custom callback.
[Slider](/Cxx/Widgets/Slider) | vtkSliderWidget vtkSliderRepresentation3D | 3D Slider.
[Slider2D](/Cxx/Widgets/Slider2D) | vtkSliderWidget vtkSliderRepresentation2D | 2D Slider.
[SphereWidget](/Cxx/Widgets/SphereWidget) | vtkSphereWidget | Sphere widget.
[SphereWidget2](/Cxx/Widgets/SphereWidget2) | vtkSphereWidget2 |
[SphereWidgetEvents](/Cxx/Widgets/SphereWidgetEvents) | vtkSphereWidget | Sphere widget events.
[SplineWidget](/Cxx/Widgets/SplineWidget) | vtkSplineWidget |
[TextWidget](/Cxx/Widgets/TextWidget) | vtkSeedWidget  vtkTextWidget | Draw movable text.
[TexturedButtonWidget](/Cxx/Widgets/TexturedButtonWidget) | vtkButtonWidget vtkTexturedButtonRepresentation2D | Create a textured 2D button.

## Plotting

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[AreaPlot](/Cxx/Plotting/AreaPlot) | vtkPlotArea | Plot area between two curves.
[BarChart](/Cxx/Plotting/BarChart) | vtkChartXY | Bar chart.
[BoxChart](/Cxx/Plotting/BoxChart) | vtkChartBox | Box plot.
[ChartMatrix](/Cxx/Plotting/ChartMatrix) | vtkChartMatrix | Create a marix of plots.
[ChartsOn3DScene](/Cxx/Plotting/ChartsOn3DScene) | vtkChartXY | Draw a chart in a 3D scene.
[CompareRandomGeneratorsCxx](/Cxx/Plotting/CompareRandomGeneratorsCxx) | vtkBarChartActor | Compare STL random number generators.
[Diagram](/Cxx/Plotting/Diagram) | vtkContext vtkColorSeries | Draw a custom diagram.
[FunctionalBagPlot](/Cxx/Plotting/FunctionalBagPlot) | vtkPlotFunctionalBag vtkColorSeries | Functional Bag Plot.
[Histogram2D](/Cxx/Plotting/Histogram2D) | vtkChartHistogram2D | 2D Histogram of a vtkImageData.
[HistogramBarChart](/Cxx/Plotting/HistogramBarChart) | vtkBarChartActor | Histogram using bar chart.
[LinePlot](/Cxx/Plotting/LinePlot) | vtkChartXY | Line plot.
[LinePlot3D](/Cxx/Plotting/PlotLine3D) | vtkLinePlot3D | Line plot of 3d data..
[ParallelCoordinates](/Cxx/Plotting/ParallelCoordinates) | vtkChartParallelCoordinates | Parallel coordinates.
[PieChart](/Cxx/Plotting/PieChart) | vtkChartPie vtkPlotPie | Pie chart.
[PieChartActor](/Cxx/Plotting/PieChartActor) | vtkPieChartActor | Pie chart.
[ScatterPlot](/Cxx/Plotting/ScatterPlot) | vtkPlotPoints | Scatter plot.
[SpiderPlot](/Cxx/Plotting/SpiderPlot) | vtkSpiderPlotActor | Spider plot.
[StackedBar](/Cxx/Plotting/StackedBar) | vtkPlotBar | Stacked bar.
[StackedPlot](/Cxx/Plotting/StackedPlot) | vtkPlotStacked | Stacked plot.
[SurfacePlot](/Cxx/Plotting/SurfacePlot) | vtkPlotSurface | SurfacePlot.

## Animation

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[AnimateActors](/Cxx/Animation/AnimateActors) | vtkAnimationScene vtkAnimationCue | Animate actors.
[Animation](/Cxx/Utilities/Animation) | vtkRenderWindowInteractor | Move a sphere across a scene.
[AnimationScene](/Cxx/Utilities/AnimationScene) | vtkAnimationScene vtkAnimationCue | Animation (the right way). Zoom in on a sphere.
[DataAnimation](/Cxx/Utilities/DataAnimation) | vtkCallbackCommand vtkProgrammableFilter | Data Animation. Update points in a dataset every specified interval.
[DataAnimationSubclass](/Cxx/Utilities/DataAnimationSubclass) | vtkCommand vtkProgrammableFilter | Update points in a dataset every specified interval (using a vtkCommand subclass instead of a callback function.
[RotatingSphere](/Cxx/Animation/RotatingSphere) | vtkSphereSource | A rotating sphere.

## Geographic Visualization (Geovis)

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[CompassWidget](/Cxx/Geovis/CompassWidget) | vtkCompassWidget | Compass Widget.
[EarthSource](/Cxx/Geovis/EarthSource) | vtkEarthSource | Create the Earth.
[GeoAssignCoordinates](/Cxx/Geovis/GeoAssignCoordinates) | vtkGeoAssignCoordinates | Convert lat/long coordinates to world coordinates.
[GeoGraticle](/Cxx/Geovis/GeoGraticle) | vtkGeoGraticle | Show lat/long lines that have been distorted.

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ParallelCoordinatesView](/Cxx/InfoVis/ParallelCoordinatesView) | vtkParallelCoordinatesView | Parallel coordinates.
[TreeMapView](/Cxx/InfoVis/TreeMapView) | vtkTreeMapView | Tree map.
[WordCloud](/Cxx/InfoVis/WordCloud) | vtkFreeTypeTools vtkImageBlend vtkImageIterator | Create a word cloud.

## Qt

Click [here](http://www.vtk.org/Wiki/VTK/Tutorials/QtSetup) for a tutorial on how to setup Qt.

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[BorderWidgetQt](/Cxx/Qt/BorderWidgetQt) | vtkBorderWidget QApplication |
[EventQtSlotConnect](/Cxx/Qt/EventQtSlotConnect) | vtkEventQtSlotConnect | Connect a VTK event to a Qt slot.
[ImageDataToQImage](/Cxx/Qt/ImageDataToQImage) |  | Convert a vtkImageData to a QImage.
[QImageToImageSource](/Cxx/Qt/QImageToImageSource) | vtkQImageToImageSource | Convert a QImage to a vtkImageData.
[QtBarChart](/Cxx/Qt/QtBarChart) | vtkQtBarChart |
[RenderWindowNoUiFile](/Cxx/Qt/RenderWindowNoUiFile) | QVTKOpenGLWidget | This is a very basic example that shows how to create a Qt window. Typically, one would want to design a form in the QtDesigner (this is shown in [RenderWindowUIMultipleInheritance](/Cxx/Qt/RenderWindowUIMultipleInheritance)).
[RenderWindowUIMultipleInheritance](/Cxx/Qt/RenderWindowUIMultipleInheritance) | QMainWindow | Using a QVTKOpenGLWidget with the Qt Multiple Inheritance model.
[RenderWindowUISingleInheritance](/Cxx/Qt/RenderWindowUISingleInheritance) | QMainWindow | Using a QVTKOpenGLWidget with the Qt Single Inheritance model.
[ShareCameraQt](/Cxx/Qt/ShareCameraQt) |  | Share the camera between QVTKOpenGLWidgets.
[ShowEvent](/Cxx/Qt/ShowEvent) |  | Use QMainWindow::showEvent event to do things that you might want to do in the constructor
[SideBySideRenderWindowsQt](/Cxx/Qt/SideBySideRenderWindowsQt) | QApplication | Side by side render windows.

## Matlab

You must turn on VTK_USE_MATLAB_MEX to use these.

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[MatlabEngineFilter](/Cxx/Matlab/MatlabEngineFilter) | vtkMatlabEngineFilter |

## Databases

### SQL

If you have any trouble or errors with the following examples, please troubleshoot using [these instructions](http://www.vtk.org/Wiki/Tutorials/SQLSetup).

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ConnectAndRead](/Cxx/Databases/SQL/MySQL/ConnectAndRead) | vtkMySQLDatabase vtkSQLQuery | Connect to and read a MySQL database.
[CreateDatabase](/Cxx/Databases/SQL/MySQL/CreateDatabase) | vtkMySQLDatabase | Create a MySQL database.
[WriteToDatabase](/Cxx/Databases/SQL/MySQL/WriteToDatabase) | vtkSQLQuery vtkMySQLDatabase | Write to a MySQL database.

## RenderMan

RenderMan is a high quality rendering system created by [Pixar](https://renderman.pixar.com/view/renderman). VTK can export RenderMan RIB files for rendering by [prman](http://renderman.pixar.com/view/renderman-prman-the-rispec-and-renderman-studio). In the spring of 2015, Pixar released a [non-commercial version](http://renderman.pixar.com/view/PR-NCR) of its RenderMan products.

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[PolyDataRIB](/Cxx/RenderMan/PolyDataRIB) | vtkRIBExporter | Apply a RenderMan Shader to a PolyData.

## Remote Modules

Remote modules are user contributed code that is not distributed with VTK. A description of a remote module and the location of its repository is listed in the VTK/Remote directory with the extension .remote.cmake. Once enabled, a remote module is treated like any other VTK module. Each of the remote module examples describes how to enable the example. More information about remote modules is [here](http://www.vtk.org/Wiki/VTK/Remote_Modules).

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[FrenetSerretFrame](/Cxx/Remote/FrenetSerretFrame) | vtkFrenetSerretFrame | Compute tangent and normal vectors to a polyline.
[FrenetSerretFrameDemo](/Cxx/Remote/FrenetSerretFrameDemo) | vtkFrenetSerretFrame | Uses vtkSplineWidget to interact with a spline. Shows how to control a pipeline inside a callback.
