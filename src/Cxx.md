# C++ Examples

These are fully independent, compilable examples. There is significant overlap in the examples, but they are each intended to illustrate a different concept and be fully stand alone compilable.

Please add examples in your areas of expertise!

## Hello World

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[A hello world example](/Cxx/Rendering/CylinderRenderingProperties)  | [vtkPolyDataMapper](http://www.vtk.org/doc/nightly/html/classvtkPolyDataMapper.html#details) [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html#details) [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html#details) [vtkRenderWindow](http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html#details) [vtkRenderWindowInteractor](http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html#details)| Cylinder example from the VTK Textbook and source code.

## Simple Operations

| Example Name | Classes Demonstrated | Description |  Image |
|--------------|----------------------|-------------|--------|
[DistanceBetweenPoints](/Cxx/SimpleOperations/DistanceBetweenPoints)   | [vtkMath](http://www.vtk.org/doc/nightly/html/classvtkMath.html#details)| Distance between two points.
[DistancePointToLine](/Cxx/SimpleOperations/DistancePointToLine)   | [vtkLine](http://www.vtk.org/doc/nightly/html/classvtkLine.html#details) |Distance between a point and a line.
[FloatingPointExceptions](/Cxx/SimpleOperations/FloatingPointExceptions) | [vtkFloatingPointExceptions](http://www.vtk.org/doc/nightly/html/classvtkFloatingPointExceptions.html#details) | Floating Point Exceptions
[GaussianRandomNumber](/Cxx/SimpleOperations/GaussianRandomNumber)  | [vtkMath](http://www.vtk.org/doc/nightly/html/classvtkMath.html#details) | Generates Gaussian random numbers.
[UniformRandomNumber](/Cxx/SimpleOperations/UniformRandomNumber)   | [vtkMath](http://www.vtk.org/doc/nightly/html/classvtkMath.html#details) | Generates uniform random numbers.
[RandomSequence](/Cxx/SimpleOperations/RandomSequence) | [vtkMinimalStandardRandomSequence](http://www.vtk.org/doc/nightly/html/classvtkMinimalStandardRandomSequence.html#details) | This is the preferred way to generate random numbers.
[ProjectPointPlane](/Cxx/SimpleOperations/ProjectPointPlane) | [vtkPlane](http://www.vtk.org/doc/nightly/html/classvtkPlane.html#details) | Project a point onto a plane.
[PerspectiveTransform](/Cxx/SimpleOperations/PerspectiveTransform) | [vtkPerspectiveTransform](http://www.vtk.org/doc/nightly/html/classvtkPerspectiveTransform.html#details) |Apply a perspective transformation to a point.


## Input and Output
### Graph Formats

### 3D File Formats

| Example Name | Classes Demonstrated | Description |  Image |
|--------------|----------------------|-------------|--------|
[ConvertFile](/Cxx/IO/ConvertFile)   |  |Convert a file from oane type to another
[XGMLReader](/Cxx/InfoVis/XGMLReader)   | [vtkXGMLReader](http://www.vtk.org/doc/nightly/html/classvtkXGMLReader.html#details) |Read a .gml file


#### Standard Formats
##### Input

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[DelimitedTextReader](/Cxx/InfoVis/DelimitedTextReader)   | [vtkDelimitedTextReader](http://www.vtk.org/doc/nightly/html/classvtkDelimitedTextReader.html#details) |Read a delimited file into a polydata.
[DEMReader](/Cxx/IO/DEMReader)   | [vtkDEMReader](http://www.vtk.org/doc/nightly/html/classvtkDEMReader.html#details) | Read DEM (elevation map) files
[DumpXMLFile](/Cxx/IO/DumpXMLFile) | [vtkDataSetReader](http://www.vtk.org/doc/nightly/html/classvtkDataSetReader.html#details) |Report the contents of a VTK XML or legacy file
[IndividualVRML](/Cxx/IO/IndividualVRML) | [vtkVRMLImporter](http://www.vtk.org/doc/nightly/html/classvtkVRMLImporter.html#details) | This example is used to get each actor and object from a scene and verify axes correspondence 
[ParticleReader](/Cxx/IO/ParticleReader) | [vtkParticleReader](http://www.vtk.org/doc/nightly/html/classvtkParticleReader.html#details) | This example reads ascii files where each line consists of points with its position (x,y,z) and (optionally) one scalar or binary files in RAW 3d file format.
[ReadDICOMSeries](/Cxx/IO/ReadDICOMSeries)   | [vtkDICOMImageReader](http://www.vtk.org/doc/nightly/html/classvtkDICOMImageReader.html#details) | This example demonstrates how to read a series of DICOM images and scroll through slices
[ReadDICOM](/Cxx/IO/ReadDICOM)   | [vtkDICOMImageReader](http://www.vtk.org/doc/nightly/html/classvtkDICOMImageReader.html#details) |Read DICOM file
[ReadOBJ](/Cxx/IO/ReadOBJ)   | [vtkOBJReader](http://www.vtk.org/doc/nightly/html/classvtkOBJReader.html#details) |Read an OBJ (.obj) file.
[ReadPDB](/Cxx/IO/ReadPDB)   | [vtkPDBReader](http://www.vtk.org/doc/nightly/html/classvtkPDBReader.html#details) | Read Protein Data Bank Files.
[ReadPLOT3D](/Cxx/IO/ReadPLOT3D)   | [vtkPLOT3DReader](http://www.vtk.org/doc/nightly/html/classvtkPLOT3DReader.html#details) | Read CFD (computational fluid dynamics) data produced by PLOT3D.
[ReadPLY](/Cxx/IO/ReadPLY)   | [vtkPLYReader](http://www.vtk.org/doc/nightly/html/classvtkPLYReader.html#details) |Read PLY (.ply) files
[ReadPlainTextTriangles](/Cxx/IO/ReadPlainTextTriangles)   | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details) [vtkSmartPointer](http://www.vtk.org/doc/nightly/html/classvtkSmartPointer.html#details) [vtkPoints](http://www.vtk.org/doc/nightly/html/classvtkPoints.html#details) [vtkCellArray](http://www.vtk.org/doc/nightly/html/classvtkCellArray.html#details) [vtkXMLPolyDataWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLPolyDataWriter.html#details) | Read a plain text file into a polydata.
[ReadTextFile](/Cxx/IO/ReadTextFile)   | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details) | Read a plain text file into a polydata.
[ReadSTL](/Cxx/IO/ReadSTL)   | [vtkSTLReader](http://www.vtk.org/doc/nightly/html/classvtkSTLReader.html#details) |Read stereo lithography STL (.stl) files
[SimplePointsReader ](/Cxx/IO/SimplePointsReader)  | [vtkSimplePointsReader](http://www.vtk.org/doc/nightly/html/classvtkSimplePointsReader.html#details) |Read a simple "xyz" file of points.
[VRML](/Cxx/IO/VRML) | [vtkVRMLImporter](http://www.vtk.org/doc/nightly/html/classvtkVRMLImporter.html#details) |Read a VRML (WRL) file.


##### Output

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[DelimitedTextWriter](/Cxx/InfoVis/DelimitedTextWriter)   | [vtkDelimitedTextWriter](http://www.vtk.org/doc/nightly/html/classvtkDelimitedTextWriter.html#details) |Write data to a delimited file
[SimplePointsWriter](/Cxx/IO/SimplePointsWriter)   | [vtkSimplePointsWriter](http://www.vtk.org/doc/nightly/html/classvtkSimplePointsWriter.html#details) |Write a simple ".xyz" file
[WritePLY](/Cxx/IO/WritePLY)   | [vtkPLYWriter](http://www.vtk.org/doc/nightly/html/classvtkPLYWriter.html#details) | Write PLY (.ply) files
[WriteSTL](/Cxx/IO/WriteSTL)   | [vtkSTLWriter](http://www.vtk.org/doc/nightly/html/classvtkSTLWriter.html#details) |Write stereo lithography STL (.stl) files


#### VTK Formats
##### Input


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ReadImageData](/Cxx/IO/ReadImageData) | [vtkXMLImageDataReader](http://www.vtk.org/doc/nightly/html/classvtkXMLImageDataReader.html#details) |Read a image data (.vti) file
[ReadPolyData](/Cxx/IO/ReadPolyData) | [vtkXMLPolyDataReader](http://www.vtk.org/doc/nightly/html/classvtkXMLPolyDataReader.html#details) |Read a polygonal data (.vtp) file
[ReadRectilinearGrid](/Cxx/IO/ReadRectilinearGrid) | [vtkXMLRectilinearGridReader](http://www.vtk.org/doc/nightly/html/classvtkXMLRectilinearGridReader.html#details) |Read a rectilinear grid (.vtr) file
[ReadStructuredGrid](/Cxx/IO/ReadStructuredGrid) | [vtkXMLStructuredGridReader](http://www.vtk.org/doc/nightly/html/classvtkXMLStructuredGridReader.html#details) |Read a structured grid (.vts) file
[ReadUnknownTypeXMLFile](/Cxx/IO/ReadUnknownTypeXMLFile) | [vtkXMLGenericDataObjectReader](http://www.vtk.org/doc/nightly/html/classvtkXMLGenericDataObjectReader.html#details) |Read an XML file and later decide what kind it is
[ReadUnstructuredGrid](/Cxx/IO/ReadUnstructuredGrid) | [vtkXMLUnstructuredGridReader](http://www.vtk.org/doc/nightly/html/classvtkXMLUnstructuredGridReader.html#details) |Read an unstructured grid (.vtu) file


##### Output


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Write an ExodusII file](/Cxx/Parallel/ExodusIIWriter)   | [vtkExodusIIWriter](http://www.vtk.org/doc/nightly/html/classvtkExodusIIWriter.html#details) | Write a time varying ExodusII file.
[Write an image file to parallel files](/Cxx/IO/XMLPImageDataWriter) | [vtkXMLPImageDataWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLPImageDataWriter.html#details) | Write a .pvti file with 4 .vti pieces.
[Write an unstructured grid to parallel files](/Cxx/IO/XMLPUnstructuredGridWriter) | [vtkXMLPUnstructuredGridWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLPUnstructuredGridWriter.html#details) | Write a .pvtu with 4 .vtu pieces.
[WriteVTI](/Cxx/IO/WriteVTI) | [vtkXMLImageDataWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLImageDataWriter.html#details) | Write a .vti file. VTI is an "ImageData".
[WriteVTP](/Cxx/IO/WriteVTP) | [vtkXMLPolyDataWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLPolyDataWriter.html#details) | Write a .vtp file. VTP is a "PolyData". This format allows for the most complex geometric objects to be stored.
[WriteVTU](/Cxx/IO/WriteVTU) | [vtkXMLUnstructuredGridWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLUnstructuredGridWriter.html#details) | Write a .vtu file. VTU is an "Unstructured Grid". This format allows for 3D data to be stored.
[XMLStructuredGridWriter](/Cxx/IO/XMLStructuredGridWriter) | [vtkXMLStructuredGridWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLStructuredGridWriter.html#details) | Write a .vts file from a [vtkStructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkStructuredGrid.html#details).

#### Legacy VTK Formats


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[GenericDataObjectReader](/Cxx/IO/GenericDataObjectReader) | [vtkGenericDataObjectReader](http://www.vtk.org/doc/nightly/html/classvtkGenericDataObjectReader.html#details) |Read any type of legacy .vtk file.
[StructuredGridReader](/Cxx/IO/StructuredGridReader) | [vtkStructuredGridReader](http://www.vtk.org/doc/nightly/html/classvtkStructuredGridReader.html#details) |Read a structured grid (.vtk) file.
[StructuredPointsReader](/Cxx/IO/StructuredPointsReader)   | [vtkStructuredPointsReader](http://www.vtk.org/doc/nightly/html/classvtkStructuredPointsReader.html#details) |Read a structured points (.vtk) file.


### Image Format

#### Input

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ImageReader2Factory](/Cxx/IO/ImageReader2Factory) | [vtkImageReader2Factory](http://www.vtk.org/doc/nightly/html/classvtkImageReader2Factory.html#details) | This class tries to find an appropriate reader. It is very convenient to use this when you don't know what kind of file to expect.
[JPEGReader](/Cxx/IO/JPEGReader) |[vtkJPEGReader](http://www.vtk.org/doc/nightly/html/classvtkJPEGReader.html#details)|Read a JPG image.
[MetaImageReader](/Cxx/IO/MetaImageReader) | [vtkMetaImageReader](http://www.vtk.org/doc/nightly/html/classvtkMetaImageReader.html#details) |Read .mha files.
[PNGReader](/Cxx/IO/PNGReader) | [vtkPNGReader](http://www.vtk.org/doc/nightly/html/classvtkPNGReader.html#details)|Read a PNG image.
[ReadBMP](/Cxx/IO/ReadBMP) |[vtkBMPReader](http://www.vtk.org/doc/nightly/html/classvtkBMPReader.html#details) | Read BMP (.bmp) files.
[ReadPNM](/Cxx/IO/ReadPNM) | [vtkPNMReader](http://www.vtk.org/doc/nightly/html/classvtkPNMReader.html#details) |Read PNM (.pnm) files.
[ReadTIFF](/Cxx/IO/ReadTIFF) | [vtkTIFFReader](http://www.vtk.org/doc/nightly/html/classvtkTIFFReader.html#details) |Read TIFF (.tif) files.

#### Output


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[JPEGWriter](/Cxx/IO/JPEGWriter)   | [vtkJPEGWriter](http://www.vtk.org/doc/nightly/html/classvtkJPEGWriter.html#details) |Write a JPEG (.jpg) file.
[MetaImageWriter](/Cxx/IO/MetaImageWriter)   | [vtkMetaImageWriter](http://www.vtk.org/doc/nightly/html/classvtkMetaImageWriter.html#details) |Write a .mha/.mhd + .raw file.
[PNGWriter](/Cxx/IO/PNGWriter)   | [vtkPNGWriter](http://www.vtk.org/doc/nightly/html/classvtkPNGWriter.html#details) |Write a PNG (.png) file.
[WriteBMP](/Cxx/IO/WriteBMP)   | [vtkBMPWriter](http://www.vtk.org/doc/nightly/html/classvtkBMPWriter.html#details) |Write a BMP (.bmp) file.
[WritePNM](/Cxx/IO/WritePNM)   | [vtkPNMWriter](http://www.vtk.org/doc/nightly/html/classvtkPNMWriter.html#details) |Write a PNM (.pnm) file.
[WriteTIFF](/Cxx/IO/WriteTIFF)   | [vtkTIFFWriter](http://www.vtk.org/doc/nightly/html/classvtkTIFFWriter.html#details) |Write a TIFF (.tif) file.


## Geometric Objects

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Arrow](/Cxx/GeometricObjects/Arrow) | [vtkArrowSource](http://www.vtk.org/doc/nightly/html/classvtkArrowSource.html#details) |
[Axes](/Cxx/GeometricObjects/Axes)  | [vtkAxesActor](http://www.vtk.org/doc/nightly/html/classvtkAxesActor.html#details) |
[Cell3DDemonstration](/Cxx/GeometricObjects/Cell3DDemonstration) | [vtkHexagonalPrism](http://www.vtk.org/doc/nightly/html/classvtkHexagonalPrism.html#details) [vtkHexahedron](http://www.vtk.org/doc/nightly/html/classvtkHexahedron.html#details) [vtkPentagonalPrism](http://www.vtk.org/doc/nightly/html/classvtkPentagonalPrism.html#details)  [vtkPolyhedron](http://www.vtk.org/doc/nightly/html/classvtkPolyhedron.html#details) [vtkPyramid](http://www.vtk.org/doc/nightly/html/classvtkPyramid.html#details) [vtkTetra](http://www.vtk.org/doc/nightly/html/classvtkTetra.html#details) [vtkVoxel](http://www.vtk.org/doc/nightly/html/classvtkVoxel.html#details) [vtkWedge](http://www.vtk.org/doc/nightly/html/classvtkWedge.html#details) [vtkUnstructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html#details) |  Demonstrate the use of [vtkCell3D](http://www.vtk.org/doc/nightly/html/classvtkCell3D.html#details) to construct geometric objects. Sample objects are generated from the classes derived from [vtkCell3D](http://www.vtk.org/doc/nightly/html/classvtkCell3D.html#details) and displayed.
[Colored Lines](/Cxx/GeometricObjects/ColoredLines)   | [vtkCellData](http://www.vtk.org/doc/nightly/html/classvtkCellData.html#details) [vtkLine](http://www.vtk.org/doc/nightly/html/classvtkLine.html#details) |
[Cone](/Cxx/GeometricObjects/Cone)   | [vtkConeSource](http://www.vtk.org/doc/nightly/html/classvtkConeSource.html#details) |
[Cube](/Cxx/GeometricObjects/Cube)   | [vtkCubeSource](http://www.vtk.org/doc/nightly/html/classvtkCubeSource.html#details) |
[Cylinder](/Cxx/GeometricObjects/Cylinder)   | [vtkCylinderSource](http://www.vtk.org/doc/nightly/html/classvtkCylinderSource.html#details) |
[Disk](/Cxx/GeometricObjects/Disk)   | [vtkDiskSource](http://www.vtk.org/doc/nightly/html/classvtkDiskSource.html#details) | A circle with a hole in it.
[Dodecahedron](/Cxx/GeometricObjects/Dodecahedron)   | [vtkPolyhedron](http://www.vtk.org/doc/nightly/html/classvtkPolyhedron.html#details) | Create a dodecahedron using [vtkPolyhedron](http://www.vtk.org/doc/nightly/html/classvtkPolyhedron.html#details)
[Frustum](/Cxx/GeometricObjects/Frustum)   | [vtkFrustumSource](http://www.vtk.org/doc/nightly/html/classvtkFrustumSource.html#details) |
[GeometricObjectsDemo](/Cxx/GeometricObjects/GeometricObjectsDemo) |  | A demonstration of all geometric objects that work the same way.
[Hexahedron](/Cxx/GeometricObjects/Hexahedron)  | [vtkHexahedron](http://www.vtk.org/doc/nightly/html/classvtkHexahedron.html#details) |
[Line](/Cxx/GeometricObjects/Line)   | [vtkLineSource](http://www.vtk.org/doc/nightly/html/classvtkLineSource.html#details) |
[LongLine](/Cxx/GeometricObjects/LongLine) | [vtkLine](http://www.vtk.org/doc/nightly/html/classvtkLine.html#details) | Manually create a polyline
[Oriented Arrow](/Cxx/GeometricObjects/OrientedArrow)   | [vtkArrowSource](http://www.vtk.org/doc/nightly/html/classvtkArrowSource.html#details) | Orient an arrow along an arbitrary vector
[Oriented Cylinder](/Cxx/GeometricObjects/OrientedCylinder)   | [vtkCylinderSource](http://www.vtk.org/doc/nightly/html/classvtkCylinderSource.html#details) | Orient a cylinder along an arbitrary vector
[Plane](/Cxx/GeometricObjects/Plane)  | [vtkPlaneSource](http://www.vtk.org/doc/nightly/html/classvtkPlaneSource.html#details) |
[PlanesIntersection](/Cxx/GeometricObjects/PlanesIntersection)  | [vtkPlanesIntersection](http://www.vtk.org/doc/nightly/html/classvtkPlanesIntersection.html#details) |
[Planes](/Cxx/GeometricObjects/Planes)  | [vtkPlanes](http://www.vtk.org/doc/nightly/html/classvtkPlanes.html#details) |
[PlatonicSolid](/Cxx/GeometricObjects/PlatonicSolid)   | [vtkPlatonicSolidSource](http://www.vtk.org/doc/nightly/html/classvtkPlatonicSolidSource.html#details) |
[Point](/Cxx/GeometricObjects/Point)   | [vtkPoints](http://www.vtk.org/doc/nightly/html/classvtkPoints.html#details) |
[PolyLine](/Cxx/GeometricObjects/PolyLine)   | [vtkPolyLine](http://www.vtk.org/doc/nightly/html/classvtkPolyLine.html#details) |
[PolygonIntersection](/Cxx/GeometricObjects/PolygonIntersection) | [vtkPolygon](http://www.vtk.org/doc/nightly/html/classvtkPolygon.html#details) |  Compute the intersection of a line segment with a polygon.
[Polygon](/Cxx/GeometricObjects/Polygon)   | [vtkPolygon](http://www.vtk.org/doc/nightly/html/classvtkPolygon.html#details) |
[Polyhedron](/Cxx/GeometricObjects/Polyhedron)   | [vtkPolyhedron](http://www.vtk.org/doc/nightly/html/classvtkPolyhedron.html#details) |
[Pyramid](/Cxx/GeometricObjects/Pyramid)   | [vtkPyramid](http://www.vtk.org/doc/nightly/html/classvtkPyramid.html#details) |
[Quad](/Cxx/GeometricObjects/Quad)   | [vtkQuad](http://www.vtk.org/doc/nightly/html/classvtkQuad.html#details) |
[Regular Polygon](/Cxx/GeometricObjects/RegularPolygonSource)   | [vtkRegularPolygonSource](http://www.vtk.org/doc/nightly/html/classvtkRegularPolygonSource.html#details) |
[Sphere](/Cxx/GeometricObjects/Sphere)   | [vtkSphereSource](http://www.vtk.org/doc/nightly/html/classvtkSphereSource.html#details) |
[Tetrahedron](/Cxx/GeometricObjects/Tetrahedron)   | [vtkTetra](http://www.vtk.org/doc/nightly/html/classvtkTetra.html#details) |
[Triangle strip](/Cxx/GeometricObjects/TriangleStrip) | [vtkTriangleStrip](http://www.vtk.org/doc/nightly/html/classvtkTriangleStrip.html#details) | 
[Triangle](/Cxx/GeometricObjects/Triangle)   | [vtkTriangle](http://www.vtk.org/doc/nightly/html/classvtkTriangle.html#details) |
[Vertex](/Cxx/GeometricObjects/Vertex)   | [vtkVertex](http://www.vtk.org/doc/nightly/html/classvtkVertex.html#details) |

### NonLinear

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[QuadraticHexahedron](/Cxx/GeometricObjects/QuadraticHexahedron) | [vtkQuadraticHexahedron](http://www.vtk.org/doc/nightly/html/classvtkQuadraticHexahedron.html#details) [vtkTessellatorFilter](http://www.vtk.org/doc/nightly/html/classvtkTessellatorFilter.html#details) | Create and tessellate a nonlinear cell.
[QuadraticTetra](/Cxx/GeometricObjects/QuadraticTetra) | [vtkTetra](http://www.vtk.org/doc/nightly/html/classvtkTetra.html#details) [vtkTessellatorFilter](http://www.vtk.org/doc/nightly/html/classvtkTessellatorFilter.html#details) | Create and tessellate a nonlinear cell.

### Parametric Objects

These examples demonstrate how to create an display one of the many [vtkParametric](http://www.vtk.org/doc/nightly/html/classvtkParametric.html#details) objects. All of the classes listed can be used in an identical fashion.


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ParametricObjects](/Cxx/GeometricObjects/ParametricObjects)   |  | Create and display a parametric object. Uncomment the object that you wish to be displayed.
[ParametricObjectsDemo](/Cxx/GeometricObjects/ParametricObjectsDemo)   | [vtkParametricBoy](http://www.vtk.org/doc/nightly/html/classvtkParametricBoy.html#details) [vtkParametricConicSpiral](http://www.vtk.org/doc/nightly/html/classvtkParametricConicSpiral.html#details) [vtkParametricCrossCap](http://www.vtk.org/doc/nightly/html/classvtkParametricCrossCap.html#details) [vtkParametricDini](http://www.vtk.org/doc/nightly/html/classvtkParametricDini.html#details) [vtkParametricEllipsoid](http://www.vtk.org/doc/nightly/html/classvtkParametricEllipsoid.html#details) [vtkParametricEnneper](http://www.vtk.org/doc/nightly/html/classvtkParametricEnneper.html#details) [vtkParametricFigure8Klein](http://www.vtk.org/doc/nightly/html/classvtkParametricFigure8Klein.html#details) [vtkParametricKlein](http://www.vtk.org/doc/nightly/html/classvtkParametricKlein.html#details) [vtkParametricMobius](http://www.vtk.org/doc/nightly/html/classvtkParametricMobius.html#details) [vtkParametricRandomHills](http://www.vtk.org/doc/nightly/html/classvtkParametricRandomHills.html#details) [vtkParametricRoman](http://www.vtk.org/doc/nightly/html/classvtkParametricRoman.html#details) [vtkParametricSpline](http://www.vtk.org/doc/nightly/html/classvtkParametricSpline.html#details) [vtkParametricSuperEllipsoid](http://www.vtk.org/doc/nightly/html/classvtkParametricSuperEllipsoid.html#details) [vtkParametricSuperToroid](http://www.vtk.org/doc/nightly/html/classvtkParametricSuperToroid.html#details) [vtkParametricTorus](http://www.vtk.org/doc/nightly/html/classvtkParametricTorus.html#details) | Demonstration of of the vtkParametric* classes added by Andrew Maclean. All the objects are displayed in a 4X4 array.
[ParametricObjectsDemo2](/Cxx/GeometricObjects/ParametricObjectsDemo2)   | [vtkParametricBohemianDome](http://www.vtk.org/doc/nightly/html/classvtkParametricBohemianDome.html#details) [vtkParametricBour](http://www.vtk.org/doc/nightly/html/classvtkParametricBour.html#details) [vtkParametricCatalanMinimal](http://www.vtk.org/doc/nightly/html/classvtkParametricCatalanMinimal.html#details) [vtkParametricHenneberg](http://www.vtk.org/doc/nightly/html/classvtkParametricHenneberg.html#details) [vtkParametricKuen](http://www.vtk.org/doc/nightly/html/classvtkParametricKuen.html#details) [vtkParametricPluckerConoid](http://www.vtk.org/doc/nightly/html/classvtkParametricPluckerConoid.html#details) [vtkParametricPseudosphere](http://www.vtk.org/doc/nightly/html/classvtkParametricPseudosphere.html#details) | Demonstration of additional vtkParametric* classes added by  Tim Meehan. All the objects are displayed in a 4X2 array.
[ParametricKuenDemo](/Cxx/GeometricObjects/ParametricKuenDemo)|[vtkParametricKuen](http://www.vtk.org/doc/nightly/html/classvtkParametricKuen.html#details)|Interactively change the parameters for a Kuen Surface.
[ParametricSuperEllipsoidDemo](/Cxx/GeometricObjects/ParametricSuperEllipsoidDemo) | [vtkParametricSuperEllipsoid](http://www.vtk.org/doc/nightly/html/classvtkParametricSuperEllipsoid.html#details) | Interactively change the parameters for a SuperEllipsoid Surface.
[ParametricSuperToroidDemo](/Cxx/GeometricObjects/ParametricSuperToroidDemo)   | [vtkParametricSuperToroid](http://www.vtk.org/doc/nightly/html/classvtkParametricSuperToroid.html#details)| Interactively change the parameters for a SuperToroid Surface.

## Implicit Functions and Iso-surfaces


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[BandedPolyDataContourFilter](/Cxx/VisualizationAlgorithms/BandedPolyDataContourFilter) | [vtkBandedPolyDataContourFilter](http://www.vtk.org/doc/nightly/html/classvtkBandedPolyDataContourFilter.html#details) | Create filled contours.
[ContourTriangulator](/Cxx/Modelling/ContourTriangulator) | [vtkMarchingSquares](http://www.vtk.org/doc/nightly/html/classvtkMarchingSquares.html#details) [vtkContourTriangulator](http://www.vtk.org/doc/nightly/html/classvtkContourTriangulator.html#details) | Create a contour from a structured point set (image) and triangulate it.
[CutWithCutFunction](/Cxx/VisualizationAlgorithms/CutWithCutFunction) | [vtkCutter](http://www.vtk.org/doc/nightly/html/classvtkCutter.html#details) | Cut a surface with an implicit plane using [vtkCutter](http://www.vtk.org/doc/nightly/html/classvtkCutter.html#details).
[CutWithScalars](/Cxx/VisualizationAlgorithms/CutWithScalars) | [vtkContourFilter](http://www.vtk.org/doc/nightly/html/classvtkContourFilter.html#details) | Cut a surface with scalars.
[DiscreteMarchingCubes](/Cxx/Modelling/DiscreteMarchingCubes) | [vtkDiscreteMarchingCubes](http://www.vtk.org/doc/nightly/html/classvtkDiscreteMarchingCubes.html#details) | Generate surfaces from labelled data.
[ExtractLargestIsosurface](/Cxx/Modelling/ExtractLargestIsosurface) | [vtkPolyDataConnectivityFilter](http://www.vtk.org/doc/nightly/html/classvtkPolyDataConnectivityFilter.html#details) | Extract largest isosurface.
[FilledContours](/Cxx/VisualizationAlgorithms/FilledContours) | [vtkContourFilter](http://www.vtk.org/doc/nightly/html/classvtkContourFilter.html#details) |Create filled contours (using [vtkClipPolyData](http://www.vtk.org/doc/nightly/html/classvtkClipPolyData.html#details)).
[ImplicitDataSet](/Cxx/ImplicitFunctions/ImplicitDataSet) | [vtkImplicitDataSet](http://www.vtk.org/doc/nightly/html/classvtkImplicitDataSet.html#details) | Convert an imagedata to an implicit function.
[ImplicitSphere](/Cxx/ImplicitFunctions/ImplicitSphere) | [vtkSphere](http://www.vtk.org/doc/nightly/html/classvtkSphere.html#details) | An implicit representation of a sphere.
[IsoContours](/Cxx/ImplicitFunctions/IsoContours) | [vtkContourFunction](http://www.vtk.org/doc/nightly/html/classvtkContourFunction.html#details) | Visualize different isocontours using a slider.
[MarchingCubes](/Cxx/Modelling/MarchingCubes) | [vtkMarchingCubes](http://www.vtk.org/doc/nightly/html/classvtkMarchingCubes.html#details) | Create a voxelized sphere.
[MarchingCases](/Cxx/VisualizationAlgorithms/MarchingCases) | [vtkMarchingCubes](http://www.vtk.org/doc/nightly/html/classvtkMarchingCubes.html#details) | Explore the Marching Cubes cases.
[MarchingSquares](/Cxx/Modelling/MarchingSquares) | [vtkMarchingSquares](http://www.vtk.org/doc/nightly/html/classvtkMarchingSquares.html#details) | Create a contour from a structured point set (image).
[SampleFunction](/Cxx/ImplicitFunctions/SampleFunction) | [vtkSampleFunction](http://www.vtk.org/doc/nightly/html/classvtkSampleFunction.html#details) |Sample and visualize an implicit function.
[SmoothDiscreteMarchingCubes](/Cxx/Modelling/SmoothDiscreteMarchingCubes) | [vtkDiscreteMarchingCubes](http://www.vtk.org/doc/nightly/html/classvtkDiscreteMarchingCubes.html#details) [vtkWindowedSincPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkWindowedSincPolyDataFilter.html#details) | Generate smooth surfaces from labelled data.


## Working with 3D Data

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[AlignFrames](/Cxx/PolyData/AlignFrames) | [vtkLandmarkTransform](http://www.vtk.org/doc/nightly/html/classvtkLandmarkTransform.html#details) | Align coordinate frames.
[AppendFilter](/Cxx/Filtering/AppendFilter) | [vtkAppendFilter](http://www.vtk.org/doc/nightly/html/classvtkAppendFilter.html#details) | Append different types of data,
[BooleanOperationPolyDataFilter](/Cxx/PolyData/BooleanOperationPolyDataFilter) | [vtkBooleanOperationPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkBooleanOperationPolyDataFilter.html#details)|Perform boolean operations on two [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details) objects.
[CellCenters](/Cxx/PolyData/CellCenters) | [vtkCellCenters](http://www.vtk.org/doc/nightly/html/classvtkCellCenters.html#details) |Compute points at the center of every cell.
[CellEdgeNeighbors](/Cxx/PolyData/CellEdgeNeighbors) | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details)::GetCellNeighbors |Determine which cells share an edge with a specific cell.
[CellPointNeighbors](/Cxx/PolyData/CellPointNeighbors) | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details)::GetCellNeighbors | Determine which cells share a single point with a specific cell.
[CenterOfMass](/Cxx/PolyData/CenterOfMass) | [vtkCenterOfMass](http://www.vtk.org/doc/nightly/html/classvtkCenterOfMass.html#details)|Compute the center of mass of the points.
[Circle](/Cxx/GeometricObjects/Circle) | [vtkCutter](http://www.vtk.org/doc/nightly/html/classvtkCutter.html#details) | Create a circle by cutting through a sphere.
[CleanPolyData](/Cxx/PolyData/CleanPolyData) | [vtkCleanPolyData](http://www.vtk.org/doc/nightly/html/classvtkCleanPolyData.html#details) |Remove coincident points.
[ColorCellsWithRGB](/Cxx/PolyData/ColorCellsWithRGB) |[vtkCellData](http://www.vtk.org/doc/nightly/html/classvtkCellData.html#details) | Color individual cells of a polydata with rgb colors.
[ColorCells](/Cxx/PolyData/ColorCells) | [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html#details) | Color individual cells of a polydata with scalar index.
[Colored Points](/Cxx/PolyData/ColoredPoints) | [vtkUnsignedCharArray](http://www.vtk.org/doc/nightly/html/classvtkUnsignedCharArray.html#details) | Add three points to a polydata and associate a color with each of them.
[CombinePolyData](/Cxx/Filtering/CombinePolyData) | [vtkAppendPolyData](http://www.vtk.org/doc/nightly/html/classvtkAppendPolyData.html#details) | Combine/Append PolyData.
[ConnectivityFilter](/Cxx/Filtering/ConnectivityFilter) | [vtkConnectivityFilter](http://www.vtk.org/doc/nightly/html/classvtkConnectivityFilter.html#details) | Color any dataset type based on connectivity.
[ContoursFromPolyData](/Cxx/Filtering/ContoursFromPolyData) | [vtkCutter](http://www.vtk.org/doc/nightly/html/classvtkCutter.html#details) | Create contours from PolyData.
[ContoursToSurface](/Cxx/PolyData/ContoursToSurface) | [vtkVoxelContoursToSurfaceFilter](http://www.vtk.org/doc/nightly/html/classvtkVoxelContoursToSurfaceFilter.html#details) | Convert contours to a surface.
[ConvexHull](/Cxx/PolyData/ConvexHull) | [vtkHull](http://www.vtk.org/doc/nightly/html/classvtkHull.html#details) |Convex hull using [vtkHull](http://www.vtk.org/doc/nightly/html/classvtkHull.html#details).
[ConvexHullShrinkWrap](/Cxx/PolyData/ConvexHullShrinkWrap) | [vtkSmoothPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkSmoothPolyDataFilter.html#details) | Convex hull using shrink wrapping.
[CopyAllArrays](/Cxx/PolyData/CopyAllArrays)| [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details) |Copy all arrays from one [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details) to another.
[Data Bounds](/Cxx/PolyData/DataBounds) | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details)::GetBounds | Get the minimum and maximum value in each dimension. (Axis aligned bounding box)
[DataSetSurfaceFilter](/Cxx/PolyData/DataSetSurfaceFilter) | [vtkDataSetSurfaceFilter](http://www.vtk.org/doc/nightly/html/classvtkDataSetSurfaceFilter.html#details) |Convert [vtkUnstructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html#details) to [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details).
[DecimatePolyline](/Cxx/PolyData/DecimatePolyline) | [vtkDecimatePolylineFilter](http://www.vtk.org/doc/nightly/html/classvtkDecimatePolylineFilter.html#details) |Decimate polyline.
[DeleteCells](/Cxx/PolyData/DeleteCells) | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details) | Delete a cell from a [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details)
[DeletePoint](/Cxx/PolyData/DeletePoint) | [vtkPoints](http://www.vtk.org/doc/nightly/html/classvtkPoints.html#details) [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details) |
[DetermineArrayDataTypes](/Cxx/PolyData/DetermineArrayDataTypes)| [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details) |Determine data types of arrays.
[DistancePolyDataFilter](/Cxx/PolyData/DistancePolyDataFilter) | [vtkDistancePolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkDistancePolyDataFilter.html#details)|Compute the distance function from one [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details) to another.
[EmbedPointsIntoVolume](/Cxx/PolyData/EmbedPointsIntoVolume)| [vtkGaussianSplatter](http://www.vtk.org/doc/nightly/html/classvtkGaussianSplatter.html#details) |Embed points into a volume.
[ExternalContour](/Cxx/PolyData/ExternalContour) | [vtkWindowToImageFilter](http://www.vtk.org/doc/nightly/html/classvtkWindowToImageFilter.html#details) [vtkContourFilter](http://www.vtk.org/doc/nightly/html/classvtkContourFilter.html#details) |Get the External Contour from Polydata.
[ExtractCellsUsingPoints](/Cxx/PolyData/ExtractCellsUsingPoints) | [vtkExtractSelection](http://www.vtk.org/doc/nightly/html/classvtkExtractSelection.html#details) [vtkSelection](http://www.vtk.org/doc/nightly/html/classvtkSelection.html#details) [vtkSelectionNode](http://www.vtk.org/doc/nightly/html/classvtkSelectionNode.html#details) |Extract points but bring cells that are still complete with them.
[ExtractOutsideSurface](/Cxx/PolyData/ExtractOutsideSurface) | [vtkPolyDataConnectivityFilter](http://www.vtk.org/doc/nightly/html/classvtkPolyDataConnectivityFilter.html#details) | Extract the outer surface of a multiple surface polydata.
[ExtractPolyLinesFromPolyData](/Cxx/PolyData/ExtractPolyLinesFromPolyData) | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details) |Extract polylines from polydata.
[ExtractSelectedIds](/Cxx/PolyData/ExtractSelectedIds) | [vtkExtractSelectedIds](http://www.vtk.org/doc/nightly/html/classvtkExtractSelectedIds.html#details) | Extract selected points.
[ExtractSelectionCells](/Cxx/PolyData/ExtractSelectionCells) | [vtkExtractSelection](http://www.vtk.org/doc/nightly/html/classvtkExtractSelection.html#details) | Extract selection cells.
[ExtractSelectionOriginalId](/Cxx/PolyData/ExtractSelectionOriginalId) | [vtkExtractSelection](http://www.vtk.org/doc/nightly/html/classvtkExtractSelection.html#details) |Extract selection and find correspondence between new and original Id.
[ExtractSelection](/Cxx/PolyData/ExtractSelection) | [vtkExtractSelection](http://www.vtk.org/doc/nightly/html/classvtkExtractSelection.html#details) |Extract selection points.
[ExtractVisibleCells](/Cxx/Filtering/ExtractVisibleCells) | [vtkHardwareSelector](http://www.vtk.org/doc/nightly/html/classvtkHardwareSelector.html#details) |Extract and highlight visible cells.
[FieldData](/Cxx/PolyData/FieldData) | [vtkFieldData](http://www.vtk.org/doc/nightly/html/classvtkFieldData.html#details) | Add Global Miscellaneous Data (FieldData) to a Polydata.
[FindAllArrayNames](/Cxx/IO/FindAllArrayNames) | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details) | Get the names of all of the data arrays.
[FitSplineToCutterOutput](/Cxx/PolyData/FitSplineToCutterOutput) | [vtkKochanekSpline](http://www.vtk.org/doc/nightly/html/classvtkKochanekSpline.html#details) [vtkSplineFilter](http://www.vtk.org/doc/nightly/html/classvtkSplineFilter.html#details) [vtkSpline](http://www.vtk.org/doc/nightly/html/classvtkSpline.html#details) |Fit a spline to cutter output.
[GeometryFilter](/Cxx/PolyData/GeometryFilter) | [vtkGeometryFilter](http://www.vtk.org/doc/nightly/html/classvtkGeometryFilter.html#details) |Convert [vtkUnstructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html#details) to [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details) (another way).
[GetMiscCellData](/Cxx/PolyData/GetMiscCellData) | [vtkCellData](http://www.vtk.org/doc/nightly/html/classvtkCellData.html#details) |Get Miscellaneous Data from Cells in a Polydata.
[GetMiscPointData](/Cxx/PolyData/GetMiscPointData) | [vtkDoubleArray](http://www.vtk.org/doc/nightly/html/classvtkDoubleArray.html#details) |Get Miscellaneous Data from Points in a Polydata.
[GradientFilter](/Cxx/PolyData/GradientFilter) | [vtkGradientFilter](http://www.vtk.org/doc/nightly/html/classvtkGradientFilter.html#details) |Compute the gradient of a scalar field on a data set.
[ImplicitBoolean](/Cxx/Filtering/ImplicitBoolean) | [vtkImplicitBoolean](http://www.vtk.org/doc/nightly/html/classvtkImplicitBoolean.html#details) | Operations include intersection and union.
[ImplicitBooleanDemo](/Cxx/Filtering/ImplicitBooleanDemo) | [vtkImplicitBoolean](http://www.vtk.org/doc/nightly/html/classvtkImplicitBoolean.html#details) | Demo Union, Difference and Intersection.
[ImplicitModeller](/Cxx/PolyData/ImplicitModeller) | [vtkImplicitModeller](http://www.vtk.org/doc/nightly/html/classvtkImplicitModeller.html#details) |Compute the distance from an object to every point on a uniform grid.
[ImplicitPolyDataDistance](/Cxx/PolyData/ImplicitPolyDataDistance) | [vtkImplicitPolyDataDistance](http://www.vtk.org/doc/nightly/html/classvtkImplicitPolyDataDistance.html#details)|Compute the distance function in a space around a [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details).
[InterpolateMeshOnGrid](/Cxx/PolyData/InterpolateMeshOnGrid) | [vtkProbeFilter](http://www.vtk.org/doc/nightly/html/classvtkProbeFilter.html#details) | Interpolate a mesh over a grid.
[InterpolateTerrain](/Cxx/PolyData/InterpolateTerrain) | [vtkProbeFilter](http://www.vtk.org/doc/nightly/html/classvtkProbeFilter.html#details) | [http://[vtk](http://www.vtk.org/doc/nightly/html/classvtk.html#details) [vtkProbeFilter](http://www.vtk.org/doc/nightly/html/classvtkProbeFilter.html#details) Interpolate terrain.
[IntersectionPolyDataFilter](/Cxx/PolyData/IntersectionPolyDataFilter) | [vtkIntersectionPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkIntersectionPolyDataFilter.html#details)|Compute the intersection of two [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details) objects.
[IterateOverLines](/Cxx/PolyData/IterateOverLines) | [vtkCellArray](http://www.vtk.org/doc/nightly/html/classvtkCellArray.html#details) | Iterate through the lines of a PolyData.
[KMeansClustering](/Cxx/InfoVis/KMeansClustering) | [vtkKMeansStatistics](http://www.vtk.org/doc/nightly/html/classvtkKMeansStatistics.html#details) |KMeans Clustering
[KochanekSpline](/Cxx/PolyData/KochanekSpline) | [vtkKochanekSpline](http://www.vtk.org/doc/nightly/html/classvtkKochanekSpline.html#details) |Create an Kochanek spline on a set of points.
[LinearExtrusion](/Cxx/PolyData/LinearExtrusion) | [vtkLinearExtrusionFilter](http://www.vtk.org/doc/nightly/html/classvtkLinearExtrusionFilter.html#details) | Extrude a shape.
[MaskPoints](/Cxx/PolyData/MaskPoints) | [vtkMaskPoints](http://www.vtk.org/doc/nightly/html/classvtkMaskPoints.html#details) |Select a subset (mask) of a point set.
[MergePoints](/Cxx/PolyData/MergePoints) | [vtkMergePoints](http://www.vtk.org/doc/nightly/html/classvtkMergePoints.html#details) | Remove duplicate (merge) points.
[MiscCellData](/Cxx/PolyData/MiscCellData) | [vtkCellData](http://www.vtk.org/doc/nightly/html/classvtkCellData.html#details) |Add Miscellaneous Data to Cells in a Polydata.
[MiscPointData](/Cxx/PolyData/MiscPointData) | [vtkPointData](http://www.vtk.org/doc/nightly/html/classvtkPointData.html#details) [vtkFloatArray](http://www.vtk.org/doc/nightly/html/classvtkFloatArray.html#details) |Add Miscellaneous Data to Points in a Polydata.
[MultiBlockMergeFilter](/Cxx/PolyData/MultiBlockMergeFilter) | [vtkMultiBlockMergeFilter](http://www.vtk.org/doc/nightly/html/classvtkMultiBlockMergeFilter.html#details) [vtkMultiBlockDataSet](http://www.vtk.org/doc/nightly/html/classvtkMultiBlockDataSet.html#details) | Combine MultiBlockDataSets.
[NullPoint](/Cxx/PolyData/NullPoint) | [vtkPointData](http://www.vtk.org/doc/nightly/html/classvtkPointData.html#details) | Set everything in PointData at a specified index to NULL
[Outline](/Cxx/PolyData/Outline) | [vtkOutlineFilter](http://www.vtk.org/doc/nightly/html/classvtkOutlineFilter.html#details) | Draw the bounding box of the data
[PKMeansClustering](/Cxx/InfoVis/PKMeansClustering) | [vtkPKMeansStatistics](http://www.vtk.org/doc/nightly/html/classvtkPKMeansStatistics.html#details) |Parallel KMeans Clustering.
[ParametricSpline](/Cxx/PolyData/ParametricSpline) | [vtkCardinalSpline](http://www.vtk.org/doc/nightly/html/classvtkCardinalSpline.html#details) [vtkParametricSpline](http://www.vtk.org/doc/nightly/html/classvtkParametricSpline.html#details) [vtkParametricFunctionSource](http://www.vtk.org/doc/nightly/html/classvtkParametricFunctionSource.html#details) |Create a Cardinal spline on a set of points.
[Perlin Noise](/Cxx/Filtering/PerlinNoise) | [vtkPerlinNoise](http://www.vtk.org/doc/nightly/html/classvtkPerlinNoise.html#details) |
[PointCellIds](/Cxx/PolyData/PointCellIds) | [vtkIdFilter](http://www.vtk.org/doc/nightly/html/classvtkIdFilter.html#details) |Generate point and cell id arrays.
[PointInsideObject2](/Cxx/PolyData/PointInsideObject2) | [vtkDelaunay3D](http://www.vtk.org/doc/nightly/html/classvtkDelaunay3D.html#details) [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details)::FindCell | This uses a Delaunay triangulation to compute a volume. This gives more of an "is inside convex hull" effect than an "is inside object".
[PointInsideObject](/Cxx/PolyData/PointInsideObject) | [vtkSelectEnclosedPoints](http://www.vtk.org/doc/nightly/html/classvtkSelectEnclosedPoints.html#details) | Check if a point is inside an object.
[PointsProjectedHull](/Cxx/PolyData/PointsProjectedHull) | [vtkPointsProjectedHull](http://www.vtk.org/doc/nightly/html/classvtkPointsProjectedHull.html#details) |Convex hull of points projected onto the coordinate planes.
[PolyDataCellNormals](/Cxx/PolyData/PolyDataCellNormals) | [vtkCellData](http://www.vtk.org/doc/nightly/html/classvtkCellData.html#details) |Add/Get Normals to/from cells in a Polydata.
[PolyDataContourToImageData](/Cxx/PolyData/PolyDataContourToImageData) | [vtkLinearExtrusionFilter](http://www.vtk.org/doc/nightly/html/classvtkLinearExtrusionFilter.html#details) [vtkPolyDataToImageStencil](http://www.vtk.org/doc/nightly/html/classvtkPolyDataToImageStencil.html#details) |Generate a binarized image from a closed contour.
[PolyDataExtractNormals](/Cxx/PolyData/PolyDataExtractNormals) | [vtkPolyDataNormals](http://www.vtk.org/doc/nightly/html/classvtkPolyDataNormals.html#details) |Extract Normals from a Polydata.
[PolyDataGetPoint](/Cxx/PolyData/PolyDataGetPoint) | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details) | Get point locations/coordinates from a [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details).
[PolyDataIsoLines](/Cxx/PolyData/PolyDataIsoLines) | [vtkBandedPolyDataContourFilter](http://www.vtk.org/doc/nightly/html/classvtkBandedPolyDataContourFilter.html#details) |Iso lines on the surface of a polydata
[PolyDataPointNormals](/Cxx/PolyData/PolyDataPointNormals) | [vtkPointData](http://www.vtk.org/doc/nightly/html/classvtkPointData.html#details) |Add/Get Normals to/from points in a Polydata.
[PolyDataPointSampler](/Cxx/PolyData/PolyDataPointSampler) | [vtkPolyDataPointSampler](http://www.vtk.org/doc/nightly/html/classvtkPolyDataPointSampler.html#details) | Sample the edges or surfaces of a polydata.
[PolyDataToImageData](/Cxx/PolyData/PolyDataToImageData) | [vtkPolyDataToImageStencil](http://www.vtk.org/doc/nightly/html/classvtkPolyDataToImageStencil.html#details) |Generate a binarized volume from a closed surface.
[ProcrustesAlignmentFilter](/Cxx/PolyData/ProcrustesAlignmentFilter) | [vtkProcrustesAlignmentFilter](http://www.vtk.org/doc/nightly/html/classvtkProcrustesAlignmentFilter.html#details) |Align point sets.
[ProgrammableFilter](/Cxx/Filtering/ProgrammableFilter) | [vtkProgrammableFilter](http://www.vtk.org/doc/nightly/html/classvtkProgrammableFilter.html#details) | Create a custom filter without subclassing.
[ProgrammableSource](/Cxx/Filtering/ProgrammableSource) |[vtkProgrammableSource](http://www.vtk.org/doc/nightly/html/classvtkProgrammableSource.html#details) |Create points using a programmable source. Generates points for a strange attractor.
[ProjectSphere](/Cxx/Visualization/ProjectSphere) |[vtkProjectSphereFilter](http://www.vtk.org/doc/nightly/html/classvtkProjectSphereFilter.html#details) |Unroll a sphere or spherical-like model.
[QuantizePolyDataPoints](/Cxx/PolyData/QuantizePolyDataPoints) | [vtkQuantizePolyDataPoints](http://www.vtk.org/doc/nightly/html/classvtkQuantizePolyDataPoints.html#details) |Snap (quantize) points to a grid.
[Reflection](/Cxx/PolyData/Reflection) | [vtkReflectionFilter](http://www.vtk.org/doc/nightly/html/classvtkReflectionFilter.html#details) |Mirror a DataSet.
[ReverseSense](/Cxx/PolyData/ReverseSense) | [vtkReverseSense](http://www.vtk.org/doc/nightly/html/classvtkReverseSense.html#details) |Flip normals.
[RibbonFilter](/Cxx/PolyData/RibbonFilter) | [vtkRibbonFilter](http://www.vtk.org/doc/nightly/html/classvtkRibbonFilter.html#details) |
[RotationAroundLine](/Cxx/PolyData/RotationAroundLine) | [vtkTransform](http://www.vtk.org/doc/nightly/html/classvtkTransform.html#details) [vtkTransformPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkTransformPolyDataFilter.html#details) |Rotation around a line.
[RuledSurfaceFilter](/Cxx/PolyData/RuledSurfaceFilter) | [vtkRuledSurfaceFilter](http://www.vtk.org/doc/nightly/html/classvtkRuledSurfaceFilter.html#details) |Create a surface between lines.
[SCurveSpline](/Cxx/InfoVis/SCurveSpline) | [vtkSCurveSpline](http://www.vtk.org/doc/nightly/html/classvtkSCurveSpline.html#details) |Create an SCurve spline on a set of points.
[SelectVisiblePoints](/Cxx/PolyData/SelectVisiblePoints) | [vtkSelectVisiblePoints](http://www.vtk.org/doc/nightly/html/classvtkSelectVisiblePoints.html#details) |Select visible points.
[SelectionSource](/Cxx/Filtering/SelectionSource) | [vtkSelectionSource](http://www.vtk.org/doc/nightly/html/classvtkSelectionSource.html#details) [vtkExtractSelection](http://www.vtk.org/doc/nightly/html/classvtkExtractSelection.html#details) | Specify a selection.
[ShrinkPolyData](/Cxx/PolyData/ShrinkPolyData) | [vtkShrinkPolyData](http://www.vtk.org/doc/nightly/html/classvtkShrinkPolyData.html#details)|Move all items in a PolyData towards their centroid.
[Silhouette](/Cxx/PolyData/Silhouette) | [vtkPolyDataSilhouette](http://www.vtk.org/doc/nightly/html/classvtkPolyDataSilhouette.html#details) |
[Stripper](/Cxx/PolyData/Stripper) | [vtkStripper](http://www.vtk.org/doc/nightly/html/classvtkStripper.html#details) |Convert triangles to triangle strips.
[ThinPlateSplineTransform](/Cxx/PolyData/ThinPlateSplineTransform) | [vtkThinPlateSplineTransform](http://www.vtk.org/doc/nightly/html/classvtkThinPlateSplineTransform.html#details) |
[ThresholdCells](/Cxx/PolyData/ThresholdCells) | [vtkThreshold](http://www.vtk.org/doc/nightly/html/classvtkThreshold.html#details) |Thresholding Cells.
[ThresholdPoints](/Cxx/PolyData/ThresholdPoints) | [vtkThresholdPoints](http://www.vtk.org/doc/nightly/html/classvtkThresholdPoints.html#details) |Thresholding Points.
[TransformFilter](/Cxx/PolyData/TransformFilter) | [vtkTransformFilter](http://www.vtk.org/doc/nightly/html/classvtkTransformFilter.html#details) |Transform a data set.
[TransformOrderDemo](/Cxx/PolyData/TransformOrderDemo) | [vtkTransformPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkTransformPolyDataFilter.html#details) |Demonstrate how the order of applying transforms affects the result.
[TransformPipeline](/Cxx/PolyData/TransformPipeline) | [vtkTransform](http://www.vtk.org/doc/nightly/html/classvtkTransform.html#details) |Combining the transformation, in order to manipulate a group of [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html#details). Shown in the example robot arm motion.
[TransformPolyData](/Cxx/Filtering/TransformPolyData) | [vtkTransformPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkTransformPolyDataFilter.html#details) | Apply a Transformation to a PolyData.
[TriangleArea](/Cxx/PolyData/TriangleArea) | [vtkTriangle](http://www.vtk.org/doc/nightly/html/classvtkTriangle.html#details)::TriangleArea | Compute the area of all triangles in a polydata.
[TriangleColoredPoints](/Cxx/PolyData/TriangleColoredPoints) | [vtkUnsignedCharArray](http://www.vtk.org/doc/nightly/html/classvtkUnsignedCharArray.html#details) | Set the color of each point of a triangle. You will be able to interpolate the colors across the triangle.
[TriangleSolidColor](/Cxx/PolyData/TriangleSolidColor) | [vtkUnsignedCharArray](http://www.vtk.org/doc/nightly/html/classvtkUnsignedCharArray.html#details) | Create a solid colored triangle.
[TubeFilter](/Cxx/PolyData/TubeFilter) | [vtkTubeFilter](http://www.vtk.org/doc/nightly/html/classvtkTubeFilter.html#details) | Give lines a thickness (produce a cylinder around lines.
[VectorFieldNonZeroExtraction](/Cxx/Filtering/VectorFieldNonZeroExtraction) | [vtkExtractSelectedThresholds](http://www.vtk.org/doc/nightly/html/classvtkExtractSelectedThresholds.html#details)| Extract non-zero vectors from a [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html#details).
[VertexConnectivity](/Cxx/PolyData/VertexConnectivity) | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details)::GetCellPoints |Get a list of vertices attached (through an edge) to a vertex.
[WarpScalar](/Cxx/PolyData/WarpScalar) | [vtkWarpScalar](http://www.vtk.org/doc/nightly/html/classvtkWarpScalar.html#details) |Move vertices along normals.
[WarpSurface](/Cxx/PolyData/WarpSurface) | [vtkWarpVector](http://www.vtk.org/doc/nightly/html/classvtkWarpVector.html#details)|Warp a surface along its normal.
[WarpTo](/Cxx/Filtering/WarpTo) | [vtkWarpTo](http://www.vtk.org/doc/nightly/html/classvtkWarpTo.html#details) | Bend an object.
[WarpVector](/Cxx/PolyData/WarpVector) | [vtkWarpVector](http://www.vtk.org/doc/nightly/html/classvtkWarpVector.html#details) | 


### Data Types

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[CompositePolyDataMapper](/Cxx/CompositeData/CompositePolyDataMapper) | [vtkCompositePolyDataMapper](http://www.vtk.org/doc/nightly/html/classvtkCompositePolyDataMapper.html#details) |
[MultiBlockDataSet](/Cxx/CompositeData/MultiBlockDataSet) | [vtkMultiBlockDataSet](http://www.vtk.org/doc/nightly/html/classvtkMultiBlockDataSet.html#details) | Demonstrates how to make and use VTK's MultiBlock type data
[OverlappingAMR](/Cxx/CompositeData/OverlappingAMR) | [vtkOverlappingAMR](http://www.vtk.org/doc/nightly/html/classvtkOverlappingAMR.html#details) |Demonstrates how to create and populate a VTK's Overlapping AMR Grid type Data


### Data Type Conversions


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[PolyDataToUnstructuredGrid](/Cxx/PolyData/PolyDataToUnstructuredGrid) | [vtkAppendFilter](http://www.vtk.org/doc/nightly/html/classvtkAppendFilter.html#details) |Convert a [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details) to a [vtkUnstructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html#details).


### Point cloud operations


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[DensifyPoints](/Cxx/Points/DensifyPoints) | [vtkDensifyPointCloudFilter](http://www.vtk.org/doc/nightly/html/classvtkDensifyPointCloudFilter.html#details) | Add points to a point cloud.
[DownsamplePointCloud](/Cxx/PolyData/DownsamplePointCloud) | [vtkCleanPolyData](http://www.vtk.org/doc/nightly/html/classvtkCleanPolyData.html#details) | Downsample a point cloud. Remove points so that there are no points within a tolerance of any point.
[ExtractClusters](/Cxx/Points/ExtractClusters) | [vtkEuclideanClusterExtraction](http://www.vtk.org/doc/nightly/html/classvtkEuclideanClusterExtraction.html#details) | From a set of randomly distributed spheres, extract connected clusters.
[ExtractPointsDemo](/Cxx/Points/ExtractPointsDemo) | [vtkExtractPoints](http://www.vtk.org/doc/nightly/html/classvtkExtractPoints.html#details) |Extract points inside an implicit function.
[ExtractSurfaceDemo](/Cxx/Points/ExtractSurfaceDemo) | [vtkExtractSurface](http://www.vtk.org/doc/nightly/html/classvtkExtractSurface.html#details) [vtkPCANormalEstimation](http://www.vtk.org/doc/nightly/html/classvtkPCANormalEstimation.html#details) [vtkSignedDistance](http://www.vtk.org/doc/nightly/html/classvtkSignedDistance.html#details) |Create a surface from Unorganized Points using Point filters (DEMO).
[ExtractSurface](/Cxx/Points/ExtractSurface) | [vtkExtractSurface](http://www.vtk.org/doc/nightly/html/classvtkExtractSurface.html#details) [vtkPCANormalEstimation](http://www.vtk.org/doc/nightly/html/classvtkPCANormalEstimation.html#details) [vtkSignedDistance](http://www.vtk.org/doc/nightly/html/classvtkSignedDistance.html#details) |Create a surface from Unorganized Points using Point filters.
[FitImplicitFunction](/Cxx/Points/FitImplicitFunction) | [vtkFitImplicitFunction](http://www.vtk.org/doc/nightly/html/classvtkFitImplicitFunction.html#details) | Extract points within a distance to an implicit function.
[MaskPointsFilter](/Cxx/Points/MaskPointsFilter) | [vtkMaskPointsFilter](http://www.vtk.org/doc/nightly/html/classvtkMaskPointsFilter.html#details) |Extract points within an image mask.
[NormalEstimation](/Cxx/Points/NormalEstimation) | [vtkPCANormalEstimation](http://www.vtk.org/doc/nightly/html/classvtkPCANormalEstimation.html#details) | Estimate the normals of a random points that lie on a sphere.
[PointOccupancy](/Cxx/Points/PointOccupancy) | [vtkPointOccupancy](http://www.vtk.org/doc/nightly/html/classvtkPointOccupancy.html#details) |Show which voxels contain points.
[PointSource](/Cxx/PolyData/PointSource) | [vtkPointSource](http://www.vtk.org/doc/nightly/html/classvtkPointSource.html#details) |Generate a random point cloud.
[RadiusOutlierRemoval](/Cxx/Points/RadiusOutlierRemoval) | [vtkRadiusOutlierRemoval](http://www.vtk.org/doc/nightly/html/classvtkRadiusOutlierRemoval.html#details) |Remove outliers.
[SignedDistance](/Cxx/Points/SignedDistance) | [vtkSignedDistance](http://www.vtk.org/doc/nightly/html/classvtkSignedDistance.html#details) |Compute signed distance to a point cloud.
[UnsignedDistance](/Cxx/Points/UnsignedDistance) | [vtkUnsignedDistance](http://www.vtk.org/doc/nightly/html/classvtkUnsignedDistance.html#details) |Compute unsigned distance to a point cloud.


### Working with Meshes


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[AddCell](/Cxx/Meshes/AddCell) | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details) | Add a cell to an existing mesh.
[BoundaryEdges](/Cxx/Meshes/BoundaryEdges) | [vtkFeatureEdges](http://www.vtk.org/doc/nightly/html/classvtkFeatureEdges.html#details) | Find the edges that are used by only one face.
[CellEdges](/Cxx/Meshes/CellEdges) | [vtkCell](http://www.vtk.org/doc/nightly/html/classvtkCell.html#details) |Get edges of cells.
[ClosedSurface](/Cxx/PolyData/ClosedSurface) | [vtkFeatureEdges](http://www.vtk.org/doc/nightly/html/classvtkFeatureEdges.html#details) |Check if a surface is closed.
[ColorDisconnectedRegions](/Cxx/PolyData/ColorDisconnectedRegions) | [vtkPolyDataConnectivityFilter](http://www.vtk.org/doc/nightly/html/classvtkPolyDataConnectivityFilter.html#details) | Color each disconnected region of a [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details) a different color.
[ColoredElevationMap](/Cxx/Meshes/ColoredElevationMap)| [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html#details) |Color a mesh by height.
[Curvatures](/Cxx/PolyData/Curvatures) | [vtkCurvatures](http://www.vtk.org/doc/nightly/html/classvtkCurvatures.html#details) |Compute Gaussian, Mean, Min, and Max Curvatures.
[Decimation](/Cxx/Meshes/Decimation) | [vtkDecimatePro](http://www.vtk.org/doc/nightly/html/classvtkDecimatePro.html#details) | Reduce the number of triangles in a mesh.
[DeformPointSet](/Cxx/Meshes/DeformPointSet) | [vtkDeformPointSet](http://www.vtk.org/doc/nightly/html/classvtkDeformPointSet.html#details) | Deform a point set with a control polyhedra.
[DijkstraGraphGeodesicPath](/Cxx/PolyData/DijkstraGraphGeodesicPath) | [vtkDijkstraGraphGeodesicPath](http://www.vtk.org/doc/nightly/html/classvtkDijkstraGraphGeodesicPath.html#details) |Find the shortest path between two points on a mesh.
[ElevationFilter](/Cxx/Meshes/ElevationFilter) | [vtkElevationFilter](http://www.vtk.org/doc/nightly/html/classvtkElevationFilter.html#details) |Color a mesh by height.
[ExtractEdges](/Cxx/Meshes/ExtractEdges) | [vtkExtractEdges](http://www.vtk.org/doc/nightly/html/classvtkExtractEdges.html#details) |
[FillHoles](/Cxx/Meshes/FillHoles) | [vtkFillHolesFilter](http://www.vtk.org/doc/nightly/html/classvtkFillHolesFilter.html#details) | Close holes in a mesh.
[GreedyTerrainDecimation](/Cxx/PolyData/GreedyTerrainDecimation)  | [vtkGreedyTerrainDecimation](http://www.vtk.org/doc/nightly/html/classvtkGreedyTerrainDecimation.html#details) | Create a mesh from an ImageData 
[HighlightBadCells](/Cxx/PolyData/HighlightBadCells) | [vtkMeshQuality](http://www.vtk.org/doc/nightly/html/classvtkMeshQuality.html#details) |
[IdentifyHoles](/Cxx/Meshes/IdentifyHoles) | [vtkFillHolesFilter](http://www.vtk.org/doc/nightly/html/classvtkFillHolesFilter.html#details) | Close holes in a mesh and identify the holes.
[ImplicitSelectionLoop](/Cxx/PolyData/ImplicitSelectionLoop) | [vtkImplicitSelectionLoop](http://www.vtk.org/doc/nightly/html/classvtkImplicitSelectionLoop.html#details) |Select a region of a mesh with an implicit function.
[LargestRegion](/Cxx/PolyData/PolyDataConnectivityFilter_LargestRegion)  | [vtkPolyDataConnectivityFilter](http://www.vtk.org/doc/nightly/html/classvtkPolyDataConnectivityFilter.html#details) |  Extract the largest connected region in a polydata.
[MatrixMathFilter](/Cxx/Meshes/MatrixMathFilter) | [vtkMatrixMathFilter](http://www.vtk.org/doc/nightly/html/classvtkMatrixMathFilter.html#details) | Compute various quantities on cell and points in a mesh.
[MeshQuality](/Cxx/PolyData/MeshQuality) | [vtkMeshQuality](http://www.vtk.org/doc/nightly/html/classvtkMeshQuality.html#details) |
[OBBDicer](/Cxx/Meshes/OBBDicer) | [vtkOBBDicer](http://www.vtk.org/doc/nightly/html/classvtkOBBDicer.html#details) | Breakup a mesh into pieces.
[PolygonalSurfaceContourLineInterpolator](/Cxx/PolyData/PolygonalSurfaceContourLineInterpolator) | [vtkPolygonalSurfaceContourLineInterpolator](http://www.vtk.org/doc/nightly/html/classvtkPolygonalSurfaceContourLineInterpolator.html#details) |Interactively find the shortest path between two points on a mesh.
[QuadricClustering](/Cxx/Meshes/QuadricClustering) | [vtkQuadricClustering](http://www.vtk.org/doc/nightly/html/classvtkQuadricClustering.html#details) | Reduce the number of triangles in a mesh.
[QuadricDecimation](/Cxx/Meshes/QuadricDecimation) | [vtkQuadricDecimation](http://www.vtk.org/doc/nightly/html/classvtkQuadricDecimation.html#details) | Reduce the number of triangles in a mesh.
[SelectPolyData](/Cxx/PolyData/SelectPolyData) | [vtkSelectPolyData](http://www.vtk.org/doc/nightly/html/classvtkSelectPolyData.html#details) |Select a region of a mesh.
[SimpleElevationFilter](/Cxx/Meshes/SimpleElevationFilter) | [vtkSimpleElevationFilter](http://www.vtk.org/doc/nightly/html/classvtkSimpleElevationFilter.html#details) |Color a mesh by dotting a vector from the origin to each point with a specified vector.
[SmoothPolyDataFilter](/Cxx/PolyData/SmoothPolyDataFilter) | [vtkSmoothPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkSmoothPolyDataFilter.html#details) |Laplacian smoothing.
[SpecifiedRegion](/Cxx/PolyData/PolyDataConnectivityFilter_SpecifiedRegion) | [vtkPolyDataConnectivityFilter](http://www.vtk.org/doc/nightly/html/classvtkPolyDataConnectivityFilter.html#details) | Extract a specific (specified) connected region in a polydata.
[SplitPolyData](/Cxx/Meshes/SplitPolyData) | [vtkOBBDicer](http://www.vtk.org/doc/nightly/html/classvtkOBBDicer.html#details) | Breakup a mesh into pieces and save the pieces into files
[Subdivision](/Cxx/Meshes/Subdivision) | [vtkButterflySubdivisionFilter](http://www.vtk.org/doc/nightly/html/classvtkButterflySubdivisionFilter.html#details) [vtkLoopSubdivisionFilter](http://www.vtk.org/doc/nightly/html/classvtkLoopSubdivisionFilter.html#details) [vtkLinearSubdivisionFilter](http://www.vtk.org/doc/nightly/html/classvtkLinearSubdivisionFilter.html#details) | Increase the number of triangles in a mesh.
[Triangluate](/Cxx/Meshes/Triangulate) | [vtkTriangleFilter](http://www.vtk.org/doc/nightly/html/classvtkTriangleFilter.html#details) | Convert all polygons in a mesh to triangles.
[WeightedTransformFilter ](/Cxx/PolyData/WeightedTransformFilter)  | [vtkWeightedTransformFilter](http://www.vtk.org/doc/nightly/html/classvtkWeightedTransformFilter.html#details) |
[WindowedSincPolyDataFilter](/Cxx/Meshes/WindowedSincPolyDataFilter) | [vtkWindowedSincPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkWindowedSincPolyDataFilter.html#details) | Smooth a mesh (windowed sinc filter).

#### Clipping

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[BoxClipStructuredPoints](/Cxx/Visualization/BoxClipStructuredPoints) | [vtkBoxClipDataSet](http://www.vtk.org/doc/nightly/html/classvtkBoxClipDataSet.html#details) [vtkStructuredPoints](http://www.vtk.org/doc/nightly/html/classvtkStructuredPoints.html#details) |Clip [vtkStructuredPoints](http://www.vtk.org/doc/nightly/html/classvtkStructuredPoints.html#details) with a box. The results are unstructured grids with tetrahedra.
[BoxClipUnstructuredGrid](/Cxx/Visualization/BoxClipUnstructuredGrid) | [vtkBoxClipDataSet](http://www.vtk.org/doc/nightly/html/classvtkBoxClipDataSet.html#details) [vtkUnstructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html#details) |Clip a [vtkUnstructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html#details) with a box. The results are unstructured grids with tetrahedra.
[CapClip](/Cxx/Meshes/CapClip) | [vtkClipPolyData](http://www.vtk.org/doc/nightly/html/classvtkClipPolyData.html#details) |Cap a clipped polydata with a polygon.
[ClipClosedSurface](/Cxx/Meshes/ClipClosedSurface) | [vtkClipClosedSurface](http://www.vtk.org/doc/nightly/html/classvtkClipClosedSurface.html#details) |Clip a surface with multiple planes.
[ClipDataSetWithPolyData](/Cxx/Meshes/ClipDataSetWithPolyData) | [vtkClipDataSet](http://www.vtk.org/doc/nightly/html/classvtkClipDataSet.html#details) [vtkImplicitPolyDataDistance](http://www.vtk.org/doc/nightly/html/classvtkImplicitPolyDataDistance.html#details) [vtkRectilinearGrid](http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html#details) |Clip a [vtkRectilinearGrid](http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html#details) with arbitrary polydata. In this example, use a [vtkConeSource](http://www.vtk.org/doc/nightly/html/classvtkConeSource.html#details) to generate polydata to slice the grid, resulting in an unstructured grid. Contrast this with the next example.
[GenericClip](/Cxx/Filtering/GenericClip) | [vtkGenericClip](http://www.vtk.org/doc/nightly/html/classvtkGenericClip.html#details) [vtkBridgeDataSet](http://www.vtk.org/doc/nightly/html/classvtkBridgeDataSet.html#details) [vtkGenericDataSet](http://www.vtk.org/doc/nightly/html/classvtkGenericDataSet.html#details) | 
[ImplicitDataSetClipping](/Cxx/PolyData/ImplicitDataSetClipping) | [vtkImplicitDataSet](http://www.vtk.org/doc/nightly/html/classvtkImplicitDataSet.html#details) |Clip using an implicit data set.
[SolidClip](/Cxx/Meshes/SolidClip) | [vtkClipPolyData](http://www.vtk.org/doc/nightly/html/classvtkClipPolyData.html#details) |Create a "solid" clip.
[TableBasedClipDataSetWithPolyData](/Cxx/Meshes/TableBasedClipDataSetWithPolyData) | [vtkTableBasedClipDataSet](http://www.vtk.org/doc/nightly/html/classvtkTableBasedClipDataSet.html#details) [vtkImplicitPolyDataDistance](http://www.vtk.org/doc/nightly/html/classvtkImplicitPolyDataDistance.html#details) [vtkRectilinearGrid](http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html#details) |Clip a [vtkRectilinearGrid](http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html#details) with arbitrary polydata. In this example, use a [vtkConeSource](http://www.vtk.org/doc/nightly/html/classvtkConeSource.html#details) to generate polydata to slice the grid, resulting in an unstructured grid. Contrast this with the previous example.


### Working with Structured 3D Data
This section includes [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html#details) [vtkStructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkStructuredGrid.html#details) and [vtkRectilinearGrid](http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html#details).

"ImageData" is not the traditional "flat, 2D image" you are used to. It is a special VTK data structure in the collection of 3D data structures provided by VTK. [Here is an overview of these data structures](http://www.vtk.org/Wiki/VTK/Tutorials/3DDataTypes). Image data can represent at typical 2D image, but also, a 3D volume.

* [[/Cxx/Visualization/StructuredDataTypes|Demonstration of structured data types]]
* [[/Cxx/StructuredData/GetLinearPointId|Get the linear point id of a point in a grid]]

#### [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html#details)

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[GetCellCenter](/Cxx/ImageData/GetCellCenter) | [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html#details)|Get the coordinates of the center of a cell.
[CellIdFromGridCoordinates](/Cxx/ImageData/CellIdFromGridCoordinates) | [vtkStructuredData](http://www.vtk.org/doc/nightly/html/classvtkStructuredData.html#details)|Get the id of a cell from its grid coordinates.
[IterateImageData](/Cxx/ImageData/IterateImageData) | [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html#details) | Iterating over a [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html#details).
[ImageNormalize](/Cxx/ImageData/ImageNormalize) | [vtkImageNormalize](http://www.vtk.org/doc/nightly/html/classvtkImageNormalize.html#details) |Normalize an image.
[ExtractVOI](/Cxx/ImageData/ExtractVOI) | [vtkExtractVOI](http://www.vtk.org/doc/nightly/html/classvtkExtractVOI.html#details) | Extract a volume of interest (subvolume).
[ImageWeightedSum](/Cxx/ImageData/ImageWeightedSum) | [vtkImageWeightedSum](http://www.vtk.org/doc/nightly/html/classvtkImageWeightedSum.html#details) |Add two or more images.
[ImageReslice](/Cxx/ImageData/ImageReslice) | [vtkImageReslice](http://www.vtk.org/doc/nightly/html/classvtkImageReslice.html#details) |Resize a [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html#details).
[ImageTranslateExtent](/Cxx/ImageData/ImageTranslateExtent) | [vtkImageTranslateExtent](http://www.vtk.org/doc/nightly/html/classvtkImageTranslateExtent.html#details) |Change the extent of a [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html#details).
[IntersectLine](/Cxx/ImageData/IntersectLine) | [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html#details) |Intersect a line with all cells of a [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html#details).
[ImageIterator](/Cxx/ImageData/ImageIterator)| [vtkImageIterator](http://www.vtk.org/doc/nightly/html/classvtkImageIterator.html#details) |


#### Conversions

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ImageDataGeometryFilter](/Cxx/ImageData/ImageDataGeometryFilter) | [vtkImageDataGeometryFilter](http://www.vtk.org/doc/nightly/html/classvtkImageDataGeometryFilter.html#details) |Convert a [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html#details) to a [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details)
[ImageDataToPointSet](/Cxx/ImageData/ImageDataToPointSet) | [vtkImageDataToPointSet](http://www.vtk.org/doc/nightly/html/classvtkImageDataToPointSet.html#details) |Convert a [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html#details) to a [vtkStructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkStructuredGrid.html#details).

#### [vtkStructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkStructuredGrid.html#details)


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[BlankPoint](/Cxx/StructuredGrid/BlankPoint) | [vtkStructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkStructuredGrid.html#details) |Blank a point of a [vtkStructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkStructuredGrid.html#details).
[StructuredGridOutline](/Cxx/StructuredGrid/StructuredGridOutline) | [vtkStructuredGridOutlineFilter](http://www.vtk.org/doc/nightly/html/classvtkStructuredGridOutlineFilter.html#details) |Visualize the outline of a structured grid.
[StructuredGrid](/Cxx/StructuredGrid/StructuredGrid) | [vtkStructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkStructuredGrid.html#details) |Structured Grid.
[VisualizeStructuredGridCells](/Cxx/StructuredGrid/VisualizeStructuredGridCells) | [vtkShrinkFilter](http://www.vtk.org/doc/nightly/html/classvtkShrinkFilter.html#details) |Visualize the cells of a structured grid.
[VisualizeStructuredGrid](/Cxx/StructuredGrid/VisualizeStructuredGrid) | [vtkStructuredGridGeometryFilter](http://www.vtk.org/doc/nightly/html/classvtkStructuredGridGeometryFilter.html#details) |Visualize the points of a structured grid.

#### [vtkStructuredPoints](http://www.vtk.org/doc/nightly/html/classvtkStructuredPoints.html#details)


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[StructuredPointsToUnstructuredGrid](/Cxx/StructuredPoints/StructuredPointsToUnstructuredGrid) | [vtkStructuredPoints](http://www.vtk.org/doc/nightly/html/classvtkStructuredPoints.html#details) [vtkUnstructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html#details)|Convert a [vtkStructuredPoints](http://www.vtk.org/doc/nightly/html/classvtkStructuredPoints.html#details) to a [vtkUnstructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html#details).


#### [vtkRectilinearGrid](http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html#details)


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[RectilinearGridToTetrahedra](/Cxx/RectilinearGrid/RectilinearGridToTetrahedra) | [vtkRectilinearGridToTetrahedra](http://www.vtk.org/doc/nightly/html/classvtkRectilinearGridToTetrahedra.html#details) |Convert a [vtkRectilinearGrid](http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html#details) to a [vtkUnstructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html#details) mesh
[RectilinearGrid](/Cxx/RectilinearGrid/RectilinearGrid) | [vtkRectilinearGrid](http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html#details) |Rectilinear grid
[VisualizeRectilinearGrid](/Cxx/RectilinearGrid/VisualizeRectilinearGrid) | [vtkRectilinearGrid](http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html#details) [vtkShrinkFilter](http://www.vtk.org/doc/nightly/html/classvtkShrinkFilter.html#details)|Visualize the cells of a rectilinear grid

### Registration

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[IterativeClosestPointsTransform](/Cxx/Filtering/IterativeClosestPointsTransform) | [vtkIterativeClosestPointTransform](http://www.vtk.org/doc/nightly/html/classvtkIterativeClosestPointTransform.html#details) | Iterative Closest Points (ICP) Transform.
[LandmarkTransform](/Cxx/Filtering/LandmarkTransform) | [vtkLandmarkTransform](http://www.vtk.org/doc/nightly/html/classvtkLandmarkTransform.html#details) |Landmark Transform.

### Medical

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[MedicalDemo1](/Cxx/Medical/MedicalDemo1) | [vtkMarchingCubes](http://www.vtk.org/doc/nightly/html/classvtkMarchingCubes.html#details) |Create a skin surface from volume data
[MedicalDemo2](/Cxx/Medical/MedicalDemo2) | [vtkMarchingCubes](http://www.vtk.org/doc/nightly/html/classvtkMarchingCubes.html#details) |Create a skin and bone surface from volume data
[MedicalDemo3](/Cxx/Medical/MedicalDemo3) | [vtkMarchingCubes](http://www.vtk.org/doc/nightly/html/classvtkMarchingCubes.html#details) |Create skin, bone and slices from volume data
[MedicalDemo4](/Cxx/Medical/MedicalDemo4) | [vtkFixedPointVolumeRayCastMapper](http://www.vtk.org/doc/nightly/html/classvtkFixedPointVolumeRayCastMapper.html#details) |Create a volume rendering
[TissueLens](/Cxx/Medical/TissueLens) | [vtkMarchingCubes](http://www.vtk.org/doc/nightly/html/classvtkMarchingCubes.html#details) [vtkClipDataSet](http://www.vtk.org/doc/nightly/html/classvtkClipDataSet.html#details)  [vtkProbeFilter](http://www.vtk.org/doc/nightly/html/classvtkProbeFilter.html#details) |Cut a volume with a sphere


### Surface reconstruction

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Delaunay3D](/Cxx/Modelling/Delaunay3D) | [vtkDelaunay3D](http://www.vtk.org/doc/nightly/html/classvtkDelaunay3D.html#details) | Create a solid mesh from Unorganized Points (Delaunay3D).
[ExtractSurfaceDemo](/Cxx/Points/ExtractSurfaceDemo) | [vtkExtractSurface](http://www.vtk.org/doc/nightly/html/classvtkExtractSurface.html#details) [vtkPCANormalEstimation](http://www.vtk.org/doc/nightly/html/classvtkPCANormalEstimation.html#details) [vtkSignedDistance](http://www.vtk.org/doc/nightly/html/classvtkSignedDistance.html#details) |Create a surface from Unorganized Points using Point filters (DEMO).
[ExtractSurface](/Cxx/Points/ExtractSurface) | [vtkExtractSurface](http://www.vtk.org/doc/nightly/html/classvtkExtractSurface.html#details) [vtkPCANormalEstimation](http://www.vtk.org/doc/nightly/html/classvtkPCANormalEstimation.html#details) [vtkSignedDistance](http://www.vtk.org/doc/nightly/html/classvtkSignedDistance.html#details) |Create a surface from Unorganized Points using Point filters.
[GaussianSplat](/Cxx/Filtering/GaussianSplat) | [vtkGaussianSplatter](http://www.vtk.org/doc/nightly/html/classvtkGaussianSplatter.html#details) |Create a surface from Unorganized Points (Gaussian Splat).
[GenerateCubesFromLabels](/Cxx/Medical/GenerateCubesFromLabels) | [vtkMetaImageReader](http://www.vtk.org/doc/nightly/html/classvtkMetaImageReader.html#details) [vtkMaskFields](http://www.vtk.org/doc/nightly/html/classvtkMaskFields.html#details) |Create cubes from labeled volume data.
[GenerateModelsFromLabels](/Cxx/Medical/GenerateModelsFromLabels) | [vtkDiscreteMarchingCubes](http://www.vtk.org/doc/nightly/html/classvtkDiscreteMarchingCubes.html#details) |Create models from labeled volume data (Discrete MarchingCubes).
[SurfaceFromUnorganizedPointsWithPostProc](/Cxx/Filtering/SurfaceFromUnorganizedPointsWithPostProc) | [vtkSurfaceReconstructionFilter](http://www.vtk.org/doc/nightly/html/classvtkSurfaceReconstructionFilter.html#details) |Create a surface from Unorganized Points (with post processing).
[SurfaceFromUnorganizedPoints](/Cxx/Filtering/SurfaceFromUnorganizedPoints) | [vtkSurfaceReconstructionFilter](http://www.vtk.org/doc/nightly/html/classvtkSurfaceReconstructionFilter.html#details) |Create a surface from Unorganized Points.
[TriangulateTerrainMap](/Cxx/Filtering/TriangulateTerrainMap) | [vtkDelaunay2D](http://www.vtk.org/doc/nightly/html/classvtkDelaunay2D.html#details) | Generate heights (z values) on a 10x10 grid (a terrain map) and then triangulate the points to form a surface.

## Utilities

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[BoundingBoxIntersection](/Cxx/Utilities/BoundingBoxIntersection) | [vtkBoundingBox](http://www.vtk.org/doc/nightly/html/classvtkBoundingBox.html#details) |Box intersection and Inside tests.
[BoundingBox](/Cxx/Utilities/BoundingBox) | [vtkBoundingBox](http://www.vtk.org/doc/nightly/html/classvtkBoundingBox.html#details) |Bounding Box construction.
[BrownianPoints](/Cxx/Utilities/BrownianPoints) | [vtkBrownianPoints](http://www.vtk.org/doc/nightly/html/classvtkBrownianPoints.html#details) |Produce a random vector at each point in a dataset.
[CardinalSpline](/Cxx/Utilities/CardinalSpline) | [vtkCardinalSpline](http://www.vtk.org/doc/nightly/html/classvtkCardinalSpline.html#details) |Cardinal spline Interpolation.
[Casting](/Cxx/PolyData/Casting)| [vtkObject](http://www.vtk.org/doc/nightly/html/classvtkObject.html#details)::SafeDownCast | Casting VTK objects.
[CheckVTKVersion](/Cxx/Utilities/CheckVTKVersion) | [vtkVersion](http://www.vtk.org/doc/nightly/html/classvtkVersion.html#details) | Check VTK Version.
[ColorLookupTable](/Cxx/Utilities/ColorLookupTable) | [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html#details) |Color Lookup Table.
[ColorTransferFunction](/Cxx/Utilities/ColorTransferFunction) | [vtkColorTransferFunction](http://www.vtk.org/doc/nightly/html/classvtkColorTransferFunction.html#details) |Color Transfer Function.
[CommandSubclass](/Cxx/Utilities/CommandSubclass) | [vtkCommand](http://www.vtk.org/doc/nightly/html/classvtkCommand.html#details) | Instead of using a callback function, it is more powerful to subclass [vtkCommand](http://www.vtk.org/doc/nightly/html/classvtkCommand.html#details).
[ConstrainedDelaunay2D](/Cxx/Filtering/ConstrainedDelaunay2D) |  [vtkDelaunay2D](http://www.vtk.org/doc/nightly/html/classvtkDelaunay2D.html#details) | Perform a 2D Delaunay triangulation on a point set respecting a specified boundary.
[Coordinate](/Cxx/Utilities/Coordinate)| [vtkCoordinate](http://www.vtk.org/doc/nightly/html/classvtkCoordinate.html#details) |Coordinate system conversions.
[DeepCopy](/Cxx/Utilities/DeepCopy) |  | Deep copy a VTK object.
[Delaunay2D](/Cxx/Filtering/Delaunay2D) | [vtkDelaunay2D](http://www.vtk.org/doc/nightly/html/classvtkDelaunay2D.html#details) | Perform a 2D Delaunay triangulation on a point set.
[DetermineActorType](/Cxx/Utilities/DetermineActorType) | [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html#details) [vtkActorCollection](http://www.vtk.org/doc/nightly/html/classvtkActorCollection.html#details) |Determine the type of an actor.
[DiscretizableColorTransferFunction](/Cxx/Utilities/DiscretizableColorTransferFunction) | [vtkDiscretizableColorTransferFunction](http://www.vtk.org/doc/nightly/html/classvtkDiscretizableColorTransferFunction.html#details) |Discretizable Color Transfer Function.
[FileOutputWindow](/Cxx/Utilities/FileOutputWindow) | [vtkFileOutputWindow](http://www.vtk.org/doc/nightly/html/classvtkFileOutputWindow.html#details) | Write errors to a log file instead of the screen.
[FilenameFunctions](/Cxx/Utilities/FilenameFunctions) | [vtkDirectory](http://www.vtk.org/doc/nightly/html/classvtkDirectory.html#details) [vtksys](http://www.vtk.org/doc/nightly/html/classvtksys.html#details)/SystemTools | Do things like get the file extension, strip the file extension, etc.
[FilterSelfProgress](/Cxx/Developers/FilterSelfProgress) |  |Monitor a filters progress.
[FrameRate](/Cxx/Utilities/FrameRate) | | Get the frame rate of the rendering.
[FullScreen](/Cxx/Utilities/FullScreen) | [vtkRenderWindow](http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html#details) | Maximize/full screen a [vtkRenderWindow](http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html#details).
[FunctionParser](/Cxx/Utilities/FunctionParser) | [vtkFunctionParser](http://www.vtk.org/doc/nightly/html/classvtkFunctionParser.html#details) |String function parser.
[GetClassName](/Cxx/Utilities/GetClassName) | GetClassName() |Determine the type of a VTK variable.
[GetDataRoot](/Cxx/Utilities/GetDataRoot) | [vtkTesting](http://www.vtk.org/doc/nightly/html/classvtkTesting.html#details) | Find the path of VTK_DATA_ROOT.
[LUTUtilities](/Cxx/Utilities/LUTUtilities) | [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html#details) [vtkColorSeries](http://www.vtk.org/doc/nightly/html/classvtkColorSeries.html#details) | A utility class for [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html#details) allowing you to output the table contents or to compare tables.
[MultipleRenderWindows](/Cxx/Visualization/MultipleRenderWindows) | [vtkRenderWindow](http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html#details) | Multiple Render Windows
[MultipleViewports](/Cxx/Visualization/MultipleViewports) | [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html#details)::SetViewPort |Multiple Viewports.
[OffScreenRendering](/Cxx/Utilities/OffScreenRendering) | [vtkImagingFactory](http://www.vtk.org/doc/nightly/html/classvtkImagingFactory.html#details) [vtkGraphicsFactory](http://www.vtk.org/doc/nightly/html/classvtkGraphicsFactory.html#details) |Off Screen Rendering.
[PCADemo](/Cxx/Utilities/PCADemo) | [vtkPCAStatistics](http://www.vtk.org/doc/nightly/html/classvtkPCAStatistics.html#details) |Project 2D points onto the best 1D subspace (PCA Demo).
[PCAStatistics](/Cxx/Utilities/PCAStatistics) | [vtkPCAStatistics](http://www.vtk.org/doc/nightly/html/classvtkPCAStatistics.html#details) |Compute Principal Component Analysis (PCA) values.
[PassThrought](/Cxx/InfoVis/PassThrough) | [vtkPassThrough](http://www.vtk.org/doc/nightly/html/classvtkPassThrough.html#details) |Pass input along to outpu.
[PiecewiseFunction](/Cxx/Utilities/PiecewiseFunction) | [vtkPiecewiseFunction](http://www.vtk.org/doc/nightly/html/classvtkPiecewiseFunction.html#details) |Interpolation using a piecewise function.
[PointInPolygon](/Cxx/Utilities/PointInPolygon) | [vtkPolygon](http://www.vtk.org/doc/nightly/html/classvtkPolygon.html#details) | Point inside polygon test.
[ReportRenderWindowCapabilities](/Cxx/Utilities/ReportRenderWindowCapabilities) | [vtkRenderWindow](http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html#details) | Report the capabilities of a render window.
[Screenshot](/Cxx/Utilities/Screenshot) | [vtkWindowToImageFilter](http://www.vtk.org/doc/nightly/html/classvtkWindowToImageFilter.html#details) |
[ShallowCopy](/Cxx/Utilities/ShallowCopy) |  | Shallow copy a VTK object.
[ShareCamera](/Cxx/Utilities/ShareCamera) | [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html#details) [vtkCamera](http://www.vtk.org/doc/nightly/html/classvtkCamera.html#details) | Share a camera between multiple renderers.
[ShepardMethod](/Cxx/Utilities/ShepardMethod) | [vtkShepardMethod](http://www.vtk.org/doc/nightly/html/classvtkShepardMethod.html#details) |Shepard method interpolation.
[SideBySideViewports](/Cxx/Visualization/SideBySideViewports) | [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html#details)::SetViewPort | Side by side viewports.
[TimeStamp](/Cxx/Utilities/TimeStamp) | [vtkTimeStamp](http://www.vtk.org/doc/nightly/html/classvtkTimeStamp.html#details) |Time stamp.
[TimerLog](/Cxx/Utilities/TimerLog) | [vtkTimerLog](http://www.vtk.org/doc/nightly/html/classvtkTimerLog.html#details) |Timer log.
[Timer](/Cxx/Utilities/Timer) | [vtkRenderWindowInteractor](http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html#details)::CreateRepeatingTimer |
[Variant](/Cxx/Utilities/Variant) | [vtkVariant](http://www.vtk.org/doc/nightly/html/classvtkVariant.html#details) |Convert between data types.
[Vector](/Cxx/Utilities/Vector) | [vtkVector](http://www.vtk.org/doc/nightly/html/classvtkVector.html#details) |Mathematical vector class.
[VersionMacros](/Cxx/Utilities/VersionMacros) | Macro/#define's | Check VTK Version.
[VisualDebugging](/Cxx/Demos/VisualDebugging) | | Update the screen from inside an algorithm.
[ZBuffer](/Cxx/Utilities/ZBuffer) | [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html#details) | zbuffer.

### Arrays

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[2DArray](/Cxx/Utilities/2DArray) | [vtkDenseArray](http://www.vtk.org/doc/nightly/html/classvtkDenseArray.html#details) |2D Array.
[3DArray](/Cxx/Utilities/3DArray) | [vtkDenseArray](http://www.vtk.org/doc/nightly/html/classvtkDenseArray.html#details) |3D Array.
[ArrayCalculator](/Cxx/Utilities/ArrayCalculator) | [vtkArrayCalculator](http://www.vtk.org/doc/nightly/html/classvtkArrayCalculator.html#details) | Perform in-place operations on arrays.
[ArrayLookup](/Cxx/Utilities/ArrayLookup) | [vtkDataArray](http://www.vtk.org/doc/nightly/html/classvtkDataArray.html#details) | Find the location of a value in a [vtkDataArray](http://www.vtk.org/doc/nightly/html/classvtkDataArray.html#details).
[ArrayRange](/Cxx/Utilities/ArrayRange) | [vtkFloatArray](http://www.vtk.org/doc/nightly/html/classvtkFloatArray.html#details)::GetRange |Get the bounds (min,max) of a [vtk](http://www.vtk.org/doc/nightly/html/classvtk.html#details) array.
[ArrayToTable](/Cxx/InfoVis/ArrayToTable) | [vtkArrayToTable](http://www.vtk.org/doc/nightly/html/classvtkArrayToTable.html#details) |Convert a [vtkDenseArray](http://www.vtk.org/doc/nightly/html/classvtkDenseArray.html#details) to a [vtkTable](http://www.vtk.org/doc/nightly/html/classvtkTable.html#details).
[ArrayWriter](/Cxx/Utilities/ArrayWriter) | [vtkArrayWriter](http://www.vtk.org/doc/nightly/html/classvtkArrayWriter.html#details)| Write a DenseArray or SparseArray to a file.
[ConcatenateArray](/Cxx/TextAnalysis/ConcatenateArray) | [vtkConcatenateArray](http://www.vtk.org/doc/nightly/html/classvtkConcatenateArray.html#details) |Concatenate two arrays.
[ConstructTable](/Cxx/Utilities/ConstructTable) | [vtkTable](http://www.vtk.org/doc/nightly/html/classvtkTable.html#details) | A table is a 2D array of any type of elements. They do not all have to be the same type. This is achieved using [vtkVariant](http://www.vtk.org/doc/nightly/html/classvtkVariant.html#details).
[CustomDenseArray](/Cxx/Utilities/CustomDenseArray) | [vtkDenseArray](http://www.vtk.org/doc/nightly/html/classvtkDenseArray.html#details) |Custom type Dense (2D) Array.
[DenseArrayRange](/Cxx/Utilities/DenseArrayRange) | [vtkDenseArray](http://www.vtk.org/doc/nightly/html/classvtkDenseArray.html#details) [vtkArrayRange](http://www.vtk.org/doc/nightly/html/classvtkArrayRange.html#details) |Get the bounds of a [vtkDenseArray](http://www.vtk.org/doc/nightly/html/classvtkDenseArray.html#details).
[ExtractArrayComponent](/Cxx/Utilities/ExtractArrayComponent) | [vtkArrayCalculator](http://www.vtk.org/doc/nightly/html/classvtkArrayCalculator.html#details) |Extract a component of an array.
[KnownLengthArray](/Cxx/Utilities/KnownLengthArray) | [vtkFloatArray](http://www.vtk.org/doc/nightly/html/classvtkFloatArray.html#details) |Known Length Array.
[SortDataArray](/Cxx/Utilities/SortDataArray) | [vtkSortDataArray](http://www.vtk.org/doc/nightly/html/classvtkSortDataArray.html#details) | Reorder array values based on an ordering (key) array.
[SparseArray](/Cxx/Utilities/SparseArray) | [vtkSparseArray](http://www.vtk.org/doc/nightly/html/classvtkSparseArray.html#details) |Sparse Array.
[UnknownLengthArray](/Cxx/Utilities/UnknownLengthArray) | [vtkFloatArray](http://www.vtk.org/doc/nightly/html/classvtkFloatArray.html#details) |Unknown Length Array.
[VectorArrayKnownLength](/Cxx/Utilities/VectorArrayKnownLength) | [vtkFloatArray](http://www.vtk.org/doc/nightly/html/classvtkFloatArray.html#details) |Array of Vectors (Known Length).
[VectorArrayUnknownLength](/Cxx/Utilities/VectorArrayUnknownLength) | [vtkFloatArray](http://www.vtk.org/doc/nightly/html/classvtkFloatArray.html#details) |Array of Vectors (Unknown Length).

### Events

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[CameraModifiedEvent](/Cxx/Utilities/CameraModifiedEvent) | [vtkCameraWindow](http://www.vtk.org/doc/nightly/html/classvtkCameraWindow.html#details) | Catch the camera modified event.
[ObserveError](/Cxx/Utilities/ObserveError) | [vtkCommand](http://www.vtk.org/doc/nightly/html/classvtkCommand.html#details) | Catch errors and warnings.
[WindowModifiedEvent](/Cxx/Utilities/WindowModifiedEvent) | [vtkRenderWindow](http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html#details) | Catch the window modified event.

## CMake Techniques

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Check if a specific module is present](/Cxx/CMakeTechniques/CheckForModule) |  |
[Check VTK Version in CMake](/Cxx/Utilities/CMakeVTKVersionCheck) | |  | 


## Math Operations

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[EigenSymmetric](/Cxx/Math/EigenSymmetric)| [vtkMath](http://www.vtk.org/doc/nightly/html/classvtkMath.html#details)::Jacobi |Compute eigenvalues and eigenvectors of a symmetric matrix.
[HomogeneousLeastSquares](/Cxx/Math/HomogeneousLeastSquares)| [vtkMath](http://www.vtk.org/doc/nightly/html/classvtkMath.html#details)::SolveHomogeneousLeastSquares |Homogeneous Least Squares.
[1DTupleInterpolation](/Cxx/Math/1DTupleInterpolation)|[vtkTupleInterpolator](http://www.vtk.org/doc/nightly/html/classvtkTupleInterpolator.html#details) [vtkCardinalSpline](http://www.vtk.org/doc/nightly/html/classvtkCardinalSpline.html#details) [vtkKochanekSpline](http://www.vtk.org/doc/nightly/html/classvtkKochanekSpline.html#details) | A simple example demonstrating how functions defined by sparsely distributed supporting points can be interpolated at arbitrary positions.
[LUFactorization](/Cxx/Math/LUFactorization)| [vtkMath](http://www.vtk.org/doc/nightly/html/classvtkMath.html#details) |LU Factorization.
[LeastSquares](/Cxx/Math/LeastSquares)| [vtkMath](http://www.vtk.org/doc/nightly/html/classvtkMath.html#details)::SolveLeastSquares |Least Squares.
[MatrixInverse](/Cxx/Math/MatrixInverse)| [vtkMatrix3x3](http://www.vtk.org/doc/nightly/html/classvtkMatrix3x3.html#details) |Matrix inverse.
[MatrixTranspose](/Cxx/Math/MatrixTranspose)| [vtkMatrix3x3](http://www.vtk.org/doc/nightly/html/classvtkMatrix3x3.html#details) |Matrix transpose.
[NormalizeVector](/Cxx/Math/NormalizeVector)| [vtkMath](http://www.vtk.org/doc/nightly/html/classvtkMath.html#details) |Normalize a vector.
[PerpendicularVector](/Cxx/Math/PerpendicularVector) | [vtkMath](http://www.vtk.org/doc/nightly/html/classvtkMath.html#details)::Perpendiculars |Get a vector perpendicular to another vector.
[PowerWeighting](/Cxx/TextAnalysis/PowerWeighting)| [vtkPowerWeighting](http://www.vtk.org/doc/nightly/html/classvtkPowerWeighting.html#details) |Raise all elements in an array to a power.
[VectorDot](/Cxx/Math/VectorDot)| [vtkVectorDot](http://www.vtk.org/doc/nightly/html/classvtkVectorDot.html#details) |
[VectorNorm](/Cxx/Math/VectorNorm) |[vtkVectorNorm](http://www.vtk.org/doc/nightly/html/classvtkVectorNorm.html#details) |Get the lengths of an array of vectors.


## Graphs

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[AdjacencyMatrixToEdgeTable](/Cxx/Graphs/AdjacencyMatrixToEdgeTable)| [vtkAdjacencyMatrixToEdgeTable](http://www.vtk.org/doc/nightly/html/classvtkAdjacencyMatrixToEdgeTable.html#details) | Convert an adjacency matrix to an edge table.
[AdjacentVertexIterator](/Cxx/Graphs/AdjacentVertexIterator)| [vtkAdjacentVertexIterator](http://www.vtk.org/doc/nightly/html/classvtkAdjacentVertexIterator.html#details) |Get all vertices connected to a specified vertex.
[BoostBreadthFirstSearchTree](/Cxx/Graphs/BoostBreadthFirstSearchTree)| [vtkBoostBreadthFirstSearchTree](http://www.vtk.org/doc/nightly/html/classvtkBoostBreadthFirstSearchTree.html#details) | Breadth first search tree. Can also be used to convert a graph to a tree.
[BreadthFirstDistance](/Cxx/Graphs/BreadthFirstDistance)| [vtkBoostBreadthFirstSearch](http://www.vtk.org/doc/nightly/html/classvtkBoostBreadthFirstSearch.html#details) |Distance from origin.
[ColorEdges](/Cxx/Graphs/ColorEdges)| [vtkGraphLayoutView](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html#details) |Color edges.
[ColorVertexLabels](/Cxx/Graphs/ColorVertexLabels)| [vtkGraphLayoutView](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html#details) [vtkRenderedGraphRepresentation](http://www.vtk.org/doc/nightly/html/classvtkRenderedGraphRepresentation.html#details) |Set the color of vertex labels.
[ColorVerticesLookupTable](/Cxx/Graphs/ColorVerticesLookupTable)| [vtkGraphLayoutView](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html#details) |Color vertices.
[ConnectedComponents](/Cxx/Graphs/ConnectedComponents)| [vtkBoostConnectedComponents](http://www.vtk.org/doc/nightly/html/classvtkBoostConnectedComponents.html#details) |Find connected components of a graph.
[ConstructGraph](/Cxx/Graphs/ConstructGraph)| [vtkMutableUndirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkMutableUndirectedGraph.html#details) |Construct a graph.
[ConstructTree](/Cxx/Graphs/ConstructTree)| [vtkTree](http://www.vtk.org/doc/nightly/html/classvtkTree.html#details) [vtkMutableDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html#details)  |Construct a tree.
[DepthFirstSearchAnimation](/Cxx/Graphs/DepthFirstSearchAnimation)| [vtkTreeDFSIterator](http://www.vtk.org/doc/nightly/html/classvtkTreeDFSIterator.html#details) |Depth First Search Animation.
[DepthFirstSearchIterator](/Cxx/Graphs/DepthFirstSearchIterator)| [vtkTreeDFSIterator](http://www.vtk.org/doc/nightly/html/classvtkTreeDFSIterator.html#details) |Depth First Search iterator.
[EdgeListIterator](/Cxx/Graphs/EdgeListIterator)| [vtkEdgeListIterator](http://www.vtk.org/doc/nightly/html/classvtkEdgeListIterator.html#details) |Iterate over edges of a graph.
[EdgeWeights](/Cxx/Graphs/EdgeWeights)| [vtkGraph](http://www.vtk.org/doc/nightly/html/classvtkGraph.html#details)::GetEdgeData::AddArray |Edge weights.
[GraphPoints](/Cxx/InfoVis/GraphPoints)| [vtkGraph](http://www.vtk.org/doc/nightly/html/classvtkGraph.html#details)::SetPoints, [vtkPassThroughLayoutStrategy](http://www.vtk.org/doc/nightly/html/classvtkPassThroughLayoutStrategy.html#details) |Manually set coordinates of vertices in a graph.
[GraphToPolyData](/Cxx/Graphs/GraphToPolyData)| [vtkGraphToPolyData](http://www.vtk.org/doc/nightly/html/classvtkGraphToPolyData.html#details) |Convert a graph to a PolyData.
[InEdgeIterator](/Cxx/Graphs/InEdgeIterator)| [vtkInEdgeIterator](http://www.vtk.org/doc/nightly/html/classvtkInEdgeIterator.html#details) |Iterate over edges incoming to a vertex.
[LabelVerticesAndEdges](/Cxx/Graphs/LabelVerticesAndEdges)| [vtkGraphLayoutView](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html#details) |Label vertices and edges.
[MinimumSpanningTree](/Cxx/Graphs/MinimumSpanningTree)| [vtkBoostPrimMinimumSpanningTree](http://www.vtk.org/doc/nightly/html/classvtkBoostPrimMinimumSpanningTree.html#details) |Minimum spanning tree of a graph.
[MutableGraphHelper](/Cxx/InfoVis/MutableGraphHelper)| [vtkMutableGraphHelper](http://www.vtk.org/doc/nightly/html/classvtkMutableGraphHelper.html#details) |Create either a [vtkMutableDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html#details) or [vtkMutableUndirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkMutableUndirectedGraph.html#details).
[NOVCAGraph](/Cxx/Graphs/NOVCAGraph)| [vtkUnstructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html#details) [vtkXMLUnstructuredGridWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLUnstructuredGridWriter.html#details) [vtkPolyLine](http://www.vtk.org/doc/nightly/html/classvtkPolyLine.html#details)|Create a graph & visualize it in ParaView/VisIt.
[OutEdgeIterator](/Cxx/Graphs/OutEdgeIterator)| [vtkOutEdgeIterator](http://www.vtk.org/doc/nightly/html/classvtkOutEdgeIterator.html#details) |Iterate over edges outgoing from a vertex.
[RandomGraphSource](/Cxx/Graphs/RandomGraphSource)| [vtkRandomGraphSource](http://www.vtk.org/doc/nightly/html/classvtkRandomGraphSource.html#details) |Create a random graph.
[RemoveIsolatedVertices](/Cxx/Graphs/RemoveIsolatedVertices)| [vtkRemoveIsolatedVertices](http://www.vtk.org/doc/nightly/html/classvtkRemoveIsolatedVertices.html#details) |Remove vertices of degree 0 from a [vtkGraph](http://www.vtk.org/doc/nightly/html/classvtkGraph.html#details).
[ScaleVertices](/Cxx/Graphs/ScaleVertices)| [vtkGraphLayoutView](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html#details) [vtkRenderedGraphRepresentation](http://www.vtk.org/doc/nightly/html/classvtkRenderedGraphRepresentation.html#details) |Size/scale vertices based on a data array.
[SelectedVerticesAndEdges ](/Cxx/Graphs/SelectedVerticesAndEdges)| [vtkAnnotationLink](http://www.vtk.org/doc/nightly/html/classvtkAnnotationLink.html#details) |Get a list of selected vertices and edges.
[SelectedVerticesAndEdgesObserver](/Cxx/Graphs/SelectedVerticesAndEdgesObserver)| [vtkAnnotationLink](http://www.vtk.org/doc/nightly/html/classvtkAnnotationLink.html#details) |Get a list of selected vertices and edges using an observer of AnnotationChangedEvent.
[ShortestPath](/Cxx/Graphs/ShortestPath)| [vtkDijkstraGraphGeodesicPath](http://www.vtk.org/doc/nightly/html/classvtkDijkstraGraphGeodesicPath.html#details) |Find the shortest path on a graph.
[SideBySideGraphs](/Cxx/Graphs/SideBySideGraphs)| [vtkGraphLayoutView](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html#details) |Display two graphs side by side.
[TreeBFSIterator](/Cxx/Graphs/TreeBFSIterator)| [vtkTreeBFSIterator](http://www.vtk.org/doc/nightly/html/classvtkTreeBFSIterator.html#details) |Breadth First Search iterator.
[VertexSize](/Cxx/Graphs/VertexSize)| [vtkGraphLayoutView](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html#details) [vtkRenderedGraphRepresentation](http://www.vtk.org/doc/nightly/html/classvtkRenderedGraphRepresentation.html#details) | Set the size of vertices.
[VisualizeDirectedGraph](/Cxx/Graphs/VisualizeDirectedGraph)| [vtkGlyphSource2D](http://www.vtk.org/doc/nightly/html/classvtkGlyphSource2D.html#details) |Visualize a directed graph.
[VisualizeGraph](/Cxx/Graphs/VisualizeGraph)| [vtkGraphLayoutView](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html#details) [vtkGraphLayoutStrategy](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutStrategy.html#details) [vtkSimple2DLayoutStrategy](http://www.vtk.org/doc/nightly/html/classvtkSimple2DLayoutStrategy.html#details)|Visualize a graph.

### Graph Conversions

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[DirectedGraphToMutableDirectedGraph](/Cxx/Graphs/Conversions/DirectedGraphToMutableDirectedGraph)| [vtkMutableDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html#details) [vtkDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkDirectedGraph.html#details) | [vtkDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkDirectedGraph.html#details) to [vtkMutableDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html#details).
[MutableDirectedGraphToDirectedGraph](/Cxx/Graphs/Conversions/MutableDirectedGraphToDirectedGraph)| [vtkMutableDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html#details) [vtkDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkDirectedGraph.html#details) |[vtkMutableDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html#details) to [vtkDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkDirectedGraph.html#details).
[TreeToMutableDirectedGraph](/Cxx/Graphs/Conversions/TreeToMutableDirectedGraph)| [vtkMutableDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html#details) [vtkTree](http://www.vtk.org/doc/nightly/html/classvtkTree.html#details) | [vtkTree](http://www.vtk.org/doc/nightly/html/classvtkTree.html#details) to [vtkMutableDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html#details)

## Data Structures

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[AttachAttributes](/Cxx/PolyData/AttachAttributes)| [vtkInformation](http://www.vtk.org/doc/nightly/html/classvtkInformation.html#details) | Attach attributes to a VTK array
[CellLocatorVisualization](/Cxx/PolyData/CellLocatorVisualization)| [vtkCellLocator](http://www.vtk.org/doc/nightly/html/classvtkCellLocator.html#details) |Visualization of the tree of a [vtkCellLocator](http://www.vtk.org/doc/nightly/html/classvtkCellLocator.html#details).
[CellLocator](/Cxx/PolyData/CellLocator)| [vtkCellLocator](http://www.vtk.org/doc/nightly/html/classvtkCellLocator.html#details) | Project a point onto a mesh. Closest point on a mesh.Efficient 3D cell query.
[CellTreeLocator](/Cxx/PolyData/CellTreeLocator)| [vtkCellTreeLocator](http://www.vtk.org/doc/nightly/html/classvtkCellTreeLocator.html#details) |Points inside an object using [vtkCellTreeLocator](http://www.vtk.org/doc/nightly/html/classvtkCellTreeLocator.html#details).
[PointLocatorVisualization](/Cxx/PolyData/PointLocatorVisualization)| [vtkPointLocator](http://www.vtk.org/doc/nightly/html/classvtkPointLocator.html#details) |Visualization of the tree of a [vtkPointLocator](http://www.vtk.org/doc/nightly/html/classvtkPointLocator.html#details).
[PointLocator](/Cxx/PolyData/PointLocator)| [vtkPointLocator](http://www.vtk.org/doc/nightly/html/classvtkPointLocator.html#details) |Efficient 3D point query.
[PointLocatorRadius](/Cxx/PolyData/PointLocatorRadius)| [vtkPointLocator](http://www.vtk.org/doc/nightly/html/classvtkPointLocator.html#details) |Find all points within a radius of a specified point.


### Timing Demonstrations

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[KDTreeTimingDemo](/Cxx/DataStructures/KDTreeTimingDemo)| [vtkKdTreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkKdTreePointLocator.html#details) | Plot the runtime vs MaxLevel (doesn't seem correct)
[ModifiedBSPTreeTimingDemo](/Cxx/DataStructures/ModifiedBSPTreeTimingDemo)| [vtkModifiedBSPTree](http://www.vtk.org/doc/nightly/html/classvtkModifiedBSPTree.html#details) | Plot the runtime vs MaxLevel
[OBBTreeTimingDemo](/Cxx/DataStructures/OBBTreeTimingDemo)| [vtkOBBTree](http://www.vtk.org/doc/nightly/html/classvtkOBBTree.html#details) | Plot the runtime vs MaxLevel
[OctreeTimingDemo](/Cxx/DataStructures/OctreeTimingDemo)| [vtkOctreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkOctreePointLocator.html#details) | Plot the runtime vs MaxPointsPerRegionOctree timing demo.

### KD-Tree


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[BuildLocatorFromKClosestPoints](/Cxx/DataStructures/BuildLocatorFromKClosestPoints)| [vtkKdTree](http://www.vtk.org/doc/nightly/html/classvtkKdTree.html#details) |
[ClosestNPoints](/Cxx/DataStructures/KdTreePointLocator/ClosestNPoints)| [vtkKdTreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkKdTreePointLocator.html#details) |Find the closest N points to a query point.
[DataStructureComparison](/Cxx/DataStructures/DataStructureComparison)| [vtkKdTree](http://www.vtk.org/doc/nightly/html/classvtkKdTree.html#details) [vtkOBBTree](http://www.vtk.org/doc/nightly/html/classvtkOBBTree.html#details) [vtkOctreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkOctreePointLocator.html#details) [vtkModifiedBSPTree](http://www.vtk.org/doc/nightly/html/classvtkModifiedBSPTree.html#details) | Illustrates, side by side, the differences between several spatial data structures
[KDTreeAccessPoints](/Cxx/DataStructures/KDTreeAccessPoints)| [vtkKdTree](http://www.vtk.org/doc/nightly/html/classvtkKdTree.html#details) |Access the points of a KDTree.
[KDTreeFindPointsWithinRadius](/Cxx/DataStructures/KDTreeFindPointsWithinRadius) | [vtkKdTreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkKdTreePointLocator.html#details) |Find points within a specified radius of  a query point.
[KdTreePointLocatorClosestPoint](/Cxx/DataStructures/KdTreePointLocatorClosestPoint)| [vtkKdTreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkKdTreePointLocator.html#details) |Find the closest point to a query point.
[KdTree](/Cxx/DataStructures/KdTree)| [vtkKdTree](http://www.vtk.org/doc/nightly/html/classvtkKdTree.html#details) |
[VisualizeKDTree](/Cxx/DataStructures/VisualizeKDTree)| [vtkKdTreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkKdTreePointLocator.html#details) |Visualize levels of the tree.


### Oriented Bounding Box (OBB) Tree


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[OBBTreeIntersectWithLine](/Cxx/DataStructures/OBBTreeIntersectWithLine)| [vtkOBBTree](http://www.vtk.org/doc/nightly/html/classvtkOBBTree.html#details) |Intersect a line with a [vtkOBBTree](http://www.vtk.org/doc/nightly/html/classvtkOBBTree.html#details).
[OBBTreeExtractCells](/Cxx/DataStructures/OBBTreeExtractCells)| [vtkOBBTree](http://www.vtk.org/doc/nightly/html/classvtkOBBTree.html#details) |Intersect a line with an OBB Tree and display all intersected cells.
[VisualizeOBBTree](/Cxx/DataStructures/VisualizeOBBTree) | [vtkOBBTree](http://www.vtk.org/doc/nightly/html/classvtkOBBTree.html#details) |Visualize levels of the tree.

### Octree

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[BuildOctree](/Cxx/DataStructures/BuildOctree)| [vtkOctreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkOctreePointLocator.html#details) |Create an octree.
[OctreeFindPointsWithinRadius](/Cxx/DataStructures/OctreeFindPointsWithinRadius)| [vtkOctreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkOctreePointLocator.html#details) |Find the points within a sphere of specified radius to a query point.
[IncrementalOctreePointLocator](/Cxx/DataStructures/IncrementalOctreePointLocator)|[vtkIncrementalOctreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkIncrementalOctreePointLocator.html#details) | Insert points into an octree without rebuilding it.
[OctreeKClosestPoints](/Cxx/DataStructures/OctreeKClosestPoints)| [vtkOctreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkOctreePointLocator.html#details) |Find the K closest points to a query point.
[OctreeClosestPoint](/Cxx/DataStructures/OctreeClosestPoint)| [vtkOctreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkOctreePointLocator.html#details) |Find the closest point to a query point.
[OctreeVisualize](/Cxx/DataStructures/OctreeVisualize)|[vtkOctreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkOctreePointLocator.html#details) |Visualize levels of the tree.


### Modified BSP Tree


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ModifiedBSPTreeIntersectWithLine](/Cxx/DataStructures/ModifiedBSPTreeIntersectWithLine)| [vtkModifiedBSPTree](http://www.vtk.org/doc/nightly/html/classvtkModifiedBSPTree.html#details) |Intersect a line with a modified BSP Tree.
[ModifiedBSPTreeExtractCells](/Cxx/DataStructures/ModifiedBSPTreeExtractCells)| [vtkModifiedBSPTree](http://www.vtk.org/doc/nightly/html/classvtkModifiedBSPTree.html#details) |Intersect a line with a modified BSP Tree and display all intersected cells.
[VisualizeModifiedBSPTree](/Cxx/DataStructures/ModifiedBSPTree/VisualizeModifiedBSPTree)| [vtkModifiedBSPTree](http://www.vtk.org/doc/nightly/html/classvtkModifiedBSPTree.html#details) |Visualize levels of the tree.


## VTK Concepts


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Scalars](/Cxx/VTKConcepts/Scalars) | [VTKConcepts](http://www.vtk.org/doc/nightly/html/classVTKConcepts.html#details) | Attach a scalar value to each point (PointData) or cell (CellData) in a data set.


## Rendering

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[AmbientSpheres](/Cxx/Rendering/AmbientSpheres)| [vtkProperty](http://www.vtk.org/doc/nightly/html/classvtkProperty.html#details) |Demonstrates the effect of ambient lighting on spheres.
[CylinderRenderingProperties](/Cxx/Rendering/CylinderRenderingProperties)| [vtkProperty](http://www.vtk.org/doc/nightly/html/classvtkProperty.html#details) |Change the properties of a cylinder.
[DiffuseSpheres](/Cxx/Rendering/DiffuseSpheres)| [vtkProperty](http://www.vtk.org/doc/nightly/html/classvtkProperty.html#details) |Demonstrates the effect of diffuse lighting on spheres.
[SpecularSpheres](/Cxx/Rendering/SpecularSpheres)| [vtkProperty](http://www.vtk.org/doc/nightly/html/classvtkProperty.html#details) |Demonstrates the effect of specular lighting on spheres.


## Lighting


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[LightActor](/Cxx/Lighting/LightActor)| [vtkLightActor](http://www.vtk.org/doc/nightly/html/classvtkLightActor.html#details) |Display the location and direction of a light.
[Light](/Cxx/Lighting/Light)| [vtkLight](http://www.vtk.org/doc/nightly/html/classvtkLight.html#details) |Add a directional light to a scene.
[Shadows](/Cxx/Visualization/Shadows)| [vtkShadowMapPass](http://www.vtk.org/doc/nightly/html/classvtkShadowMapPass.html#details) |Create shadows.


## Texture Mapping
| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[BackgroundTexture](/Cxx/Visualization/BackgroundTexture)| [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html#details) [vtkTexture](http://www.vtk.org/doc/nightly/html/classvtkTexture.html#details) |Use a texture for the background of a [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html#details).
[ClipArt ](/Cxx/Visualization/ClipArt) | [vtkTextureMapToPlane](http://www.vtk.org/doc/nightly/html/classvtkTextureMapToPlane.html#details) | Generate 3D clip art from an image.
[TextureCutQuadric](/Cxx/Texture/TextureCutQuadric)| [vtkBooleanTexture](http://www.vtk.org/doc/nightly/html/classvtkBooleanTexture.html#details) [vtkImplicitTextureCoords](http://www.vtk.org/doc/nightly/html/classvtkImplicitTextureCoords.html#details) | Cut a quadric with boolean textures.
[TextureCutSphere](/Cxx/Texture/TextureCutSphere)| [vtkImplicitTextureCoords](http://www.vtk.org/doc/nightly/html/classvtkImplicitTextureCoords.html#details) | Cut a sphere using texture coordinates.
[TextureMapImageData ](/Cxx/Visualization/TextureMapImageData) | [vtkImageCanvasSource2D](http://www.vtk.org/doc/nightly/html/classvtkImageCanvasSource2D.html#details) | Texture map an ImageData.
[TextureMapPlane](/Cxx/Visualization/TextureMapPlane)| [vtkTextureMapToPlane](http://www.vtk.org/doc/nightly/html/classvtkTextureMapToPlane.html#details) |Texture map a plane.
[TextureMapQuad](/Cxx/Visualization/TextureMapQuad)| [vtkPolygon](http://www.vtk.org/doc/nightly/html/classvtkPolygon.html#details) [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details) |Texture map a quad.
[TexturedSphere](/Cxx/Texture/TexturedSphere)| [vtkTextureMapToSphere](http://www.vtk.org/doc/nightly/html/classvtkTextureMapToSphere.html#details) | Texture a sphere.

## Visualization
See [this tutorial](http://www.vtk.org/Wiki/VTK/Tutorials/3DDataTypes) for a brief explanation of the VTK terminology of mappers, actors, etc.


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Arbitrary3DCursor](/Cxx/Visualization/Arbitrary3DCursor)| [vtkPointWidget](http://www.vtk.org/doc/nightly/html/classvtkPointWidget.html#details) |Track a 3D cursor.
[AssignCellColorsFromLUT](/Cxx/Visualization/AssignCellColorsFromLUT)| [vtkNamedColors](http://www.vtk.org/doc/nightly/html/classvtkNamedColors.html#details) [vtkPlaneSource](http://www.vtk.org/doc/nightly/html/classvtkPlaneSource.html#details) [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html#details) [vtkColorTransferFunction](http://www.vtk.org/doc/nightly/html/classvtkColorTransferFunction.html#details) | Demonstrates how to assign colors to cells in a [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details) structure using lookup tables.
[BackfaceCulling](/Cxx/Visualization/BackfaceCulling)| [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html#details) | Backface culling.
[BackgroundColor ](/Cxx/Visualization/BackgroundColor) | [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html#details) | Background color.
[BackgroundGradient ](/Cxx/Visualization/BackgroundGradient) | [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html#details) [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html#details) | Background gradient.
[BillboardTextActor3D](/Cxx/Visualization/BillboardTextActor3D) | [vtkBillboardTextActor3D](http://www.vtk.org/doc/nightly/html/classvtkBillboardTextActor3D.html#details) | Label points with billboards.
[BlobbyLogo](/Cxx/Visualization/BlobbyLogo) | [vtkImplicitModeller](http://www.vtk.org/doc/nightly/html/classvtkImplicitModeller.html#details) | Blobby logo from VTK textbook.
[CameraActor](/Cxx/Visualization/CameraActor) | [vtkCameraActor](http://www.vtk.org/doc/nightly/html/classvtkCameraActor.html#details) | Visualize a camera (frustum) in a scene.
[CameraModel1](/Cxx/Visualization/CameraModel1) | [vtkCameraActor](http://www.vtk.org/doc/nightly/html/classvtkCameraActor.html#details) | Illustrate camera movement.
[CameraModel2](/Cxx/Visualization/CameraModel2) | [vtkCameraActor](http://www.vtk.org/doc/nightly/html/classvtkCameraActor.html#details) | Illustrate camera movement.
[Camera](/Cxx/Visualization/Camera)| [vtkCamera](http://www.vtk.org/doc/nightly/html/classvtkCamera.html#details) |Positioning and aiming the camera.
[CaptionActor2D](/Cxx/Visualization/CaptionActor2D)| [vtkCaptionActor2D](http://www.vtk.org/doc/nightly/html/classvtkCaptionActor2D.html#details) |Draw a caption/bubble pointing to a particular point.
[CloseWindow](/Cxx/Visualization/CloseWindow)| [vtkRenderWindowInteractor](http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html#details) [vtkRenderWindow](http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html#details) |Close a render window.
[ColorActorEdges ](/Cxx/Visualization/ColorActorEdges) | [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html#details) | Color the edges of an Actor.
[ColorAnActor ](/Cxx/Visualization/ColorAnActor) | [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html#details) | Color an Actor.
[ColorGlyphs](/Cxx/Visualization/ColorGlyphs)| [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html#details) [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html#details) |Color glyphs.
[ComplexV](/Cxx/Visualization/ComplexV) | [vtkHedgeHog](http://www.vtk.org/doc/nightly/html/classvtkHedgeHog.html#details) | ComplexV from the VTK Textbook.
[CornerAnnotation](/Cxx/Visualization/CornerAnnotation)| [vtkCornerAnnotation](http://www.vtk.org/doc/nightly/html/classvtkCornerAnnotation.html#details) | Write text in the corners of a window.
[CorrectlyRenderTranslucentGeometry](/Cxx/Visualization/CorrectlyRenderTranslucentGeometry)| [vtkDepthSortPolyData](http://www.vtk.org/doc/nightly/html/classvtkDepthSortPolyData.html#details) |Correctly Rendering Translucent Geometry.
[CubeAxesActor2D](/Cxx/Visualization/CubeAxesActor2D)| [vtkCubeAxesActor2D](http://www.vtk.org/doc/nightly/html/classvtkCubeAxesActor2D.html#details) | This example uses the [vtkCubeAxesActor2D](http://www.vtk.org/doc/nightly/html/classvtkCubeAxesActor2D.html#details) to show your scene with axes to indicate the spatial extent of your data.
[CubeAxesActor](/Cxx/Visualization/CubeAxesActor)| [vtkCubeAxesActor](http://www.vtk.org/doc/nightly/html/classvtkCubeAxesActor.html#details) |Display three orthogonal axes with labels.
[Cursor3D](/Cxx/Visualization/Cursor3D)| [vtkCursor3D](http://www.vtk.org/doc/nightly/html/classvtkCursor3D.html#details) |
[CursorShape](/Cxx/Visualization/CursorShape)| [vtkRenderWindow](http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html#details) |Change the shape of the cursor.
[CurvatureBandsWithGlyphs](/Cxx/Visualization/CurvatureBandsWithGlyphs)| [vtkCurvatures](http://www.vtk.org/doc/nightly/html/classvtkCurvatures.html#details) [vtkBandedPolyDataContourFilter](http://www.vtk.org/doc/nightly/html/classvtkBandedPolyDataContourFilter.html#details) [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html#details) [vtkColorSeries](http://www.vtk.org/doc/nightly/html/classvtkColorSeries.html#details) [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html#details) | Demonstrates the coloring of a surface by partitioning the gaussian curvature of a surface into bands and using arrows to display the normals on the surface.
[CurvedReformation ](/Cxx/Visualization/CurvedReformation) | [vtkProbeFilter](http://www.vtk.org/doc/nightly/html/classvtkProbeFilter.html#details)| Sample a volume with a curved surface. In medical imaging, this is often called curved multi planar reformation.
[Cutter](/Cxx/VisualizationAlgorithms/Cutter)| [vtkCutter](http://www.vtk.org/doc/nightly/html/classvtkCutter.html#details) |
[DepthSortPolyData](/Cxx/Visualization/DepthSortPolyData)| [vtkDepthSortPolyData](http://www.vtk.org/doc/nightly/html/classvtkDepthSortPolyData.html#details) |Poly Data Depth Sorting.
[DisplayCoordinateAxes](/Cxx/Visualization/DisplayCoordinateAxes)| [vtkOrientationMarkerWidget](http://www.vtk.org/doc/nightly/html/classvtkOrientationMarkerWidget.html#details) |Display coordinate axes.
[DisplayQuadricSurfaces](/Cxx/Visualization/DisplayQuadricSurfaces)| [vtkQuadric](http://www.vtk.org/doc/nightly/html/classvtkQuadric.html#details) [vtkSampleFunction](http://www.vtk.org/doc/nightly/html/classvtkSampleFunction.html#details) [vtkContourFilter](http://www.vtk.org/doc/nightly/html/classvtkContourFilter.html#details) |Display Quadric Surfaces.
[DistanceToCamera](/Cxx/Visualization/DistanceToCamera) | [vtkDistanceToCamera](http://www.vtk.org/doc/nightly/html/classvtkDistanceToCamera.html#details) |
[DrawText](/Cxx/Visualization/DrawText)| [vtkTextActor](http://www.vtk.org/doc/nightly/html/classvtkTextActor.html#details) [vtkTextProperty](http://www.vtk.org/doc/nightly/html/classvtkTextProperty.html#details) |Display Text.
[ElevationBandsWithGlyphs](/Cxx/Visualization/ElevationBandsWithGlyphs)| [vtkBandedPolyDataContourFilter](http://www.vtk.org/doc/nightly/html/classvtkBandedPolyDataContourFilter.html#details) [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html#details) [vtkColorSeries](http://www.vtk.org/doc/nightly/html/classvtkColorSeries.html#details) [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html#details) | Demonstrates the coloring of a surface by partitioning the elevation into bands and using arrows to display the normals on the surface.
[ExtrudePolyDataAlongLine](/Cxx/Visualization/ExtrudePolyDataAlongLine) | [vtkRuledSurfaceFilter](http://www.vtk.org/doc/nightly/html/classvtkRuledSurfaceFilter.html#details) | Extrude a 2D polydata along a line in 3D space.
[FastSplatter](/Cxx/Visualization/FastSplatter)| [vtkFastSplatter](http://www.vtk.org/doc/nightly/html/classvtkFastSplatter.html#details) |Convolve a splat image with every point in an input image.
[FindCellIntersections](/Cxx/VisualizationAlgorithms/FindCellIntersections) | [vtkCellLocator](http://www.vtk.org/doc/nightly/html/classvtkCellLocator.html#details) | Find the intersection of a line and the cells in an unstructured dataset
[FlatShading](/Cxx/Visualization/FlatShading) | [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html#details) |
[Follower ](/Cxx/Visualization/Follower) | [vtkFollower](http://www.vtk.org/doc/nightly/html/classvtkFollower.html#details) | Draw text that stays right side up.
[Glyph2D ](/Cxx/Filtering/Glyph2D) | [vtkGlyph2D](http://www.vtk.org/doc/nightly/html/classvtkGlyph2D.html#details)|
[Glyph3D ](/Cxx/Filtering/Glyph3D) | [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html#details)|
[Glyph3DMapper](/Cxx/Visualization/Glyph3DMapper)| [vtkGlyph3DMapper](http://www.vtk.org/doc/nightly/html/classvtkGlyph3DMapper.html#details) |
[HedgeHog](/Cxx/Visualization/HedgeHog)| [vtkHedgeHog](http://www.vtk.org/doc/nightly/html/classvtkHedgeHog.html#details) [vtkStructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkStructuredGrid.html#details) |Create oriented lines (hedgehogs) from vector data.
[Hide an actor](/Cxx/Visualization/HideActor)| [vtkPropCollection](http://www.vtk.org/doc/nightly/html/classvtkPropCollection.html#details) [vtkProp](http://www.vtk.org/doc/nightly/html/classvtkProp.html#details) | visible
[HideAllActors](/Cxx/Visualization/HideAllActors)| [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html#details) |Hide all actors.
[ImageMapper](/Cxx/Visualization/ImageMapper)| [vtkImageMapper](http://www.vtk.org/doc/nightly/html/classvtkImageMapper.html#details) | Display an image in 2D.
[ImageOrder](/Cxx/Visualization/ImageOrder)| [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html#details) |Determine the display order of a stack of images.
[ImageOrientation ](/Cxx/Visualization/ImageOrientation) | [vtkInteractorStyleImage](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleImage.html#details) |Orientation of the view of an image.
[ImageTransparency](/Cxx/Visualization/ImageTransparency)| [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html#details)|Set transparency of image pixels.
[IsosurfaceSampling ](/Cxx/Visualization/IsosurfaceSampling) | [vtkProbeFilter](http://www.vtk.org/doc/nightly/html/classvtkProbeFilter.html#details)|Demonstrates how to create point data on an isosurface.
[LODProp3D ](/Cxx/Visualization/LODProp3D) | [vtkLODProp3D](http://www.vtk.org/doc/nightly/html/classvtkLODProp3D.html#details) | Level of detail rendering.
[LabelContours](/Cxx/Visualization/LabelContours)| [vtkLabeledDataMapper](http://www.vtk.org/doc/nightly/html/classvtkLabeledDataMapper.html#details) |Label Contours.
[LabelPlacementMapper](/Cxx/Visualization/LabelPlacementMapper)| [vtkPointSetToLabelHierarchy](http://www.vtk.org/doc/nightly/html/classvtkPointSetToLabelHierarchy.html#details) [vtkLabelPlacementMapper](http://www.vtk.org/doc/nightly/html/classvtkLabelPlacementMapper.html#details) | Display a non-overlapping text label at each point.
[LabeledDataMapper](/Cxx/Visualization/LabeledDataMapper)| [vtkLabeledDataMapper](http://www.vtk.org/doc/nightly/html/classvtkLabeledDataMapper.html#details) |Display the point ID at each point.
[LabeledMesh ](/Cxx/Visualization/LabeledMesh) | [vtkLabeledDataMapper](http://www.vtk.org/doc/nightly/html/classvtkLabeledDataMapper.html#details) | Label Mesh.
[LegendScaleActor](/Cxx/Visualization/LegendScaleActor)| [vtkLegendScaleActor](http://www.vtk.org/doc/nightly/html/classvtkLegendScaleActor.html#details) |Display the scale of a scene.
[Legend](/Cxx/Visualization/Legend) | [vtkLegendBoxActor](http://www.vtk.org/doc/nightly/html/classvtkLegendBoxActor.html#details) |
[LineWidth](/Cxx/Visualization/LineWidth)| [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html#details) [vtkProperty](http://www.vtk.org/doc/nightly/html/classvtkProperty.html#details) |Change the width/thickness of lines in an actor.
[MovableAxes ](/Cxx/Visualization/MovableAxes) | [vtkFollower](http://www.vtk.org/doc/nightly/html/classvtkFollower.html#details) [vtkAxesActor](http://www.vtk.org/doc/nightly/html/classvtkAxesActor.html#details) [vtkAssembly](http://www.vtk.org/doc/nightly/html/classvtkAssembly.html#details) | Movable axes.
[MoveActor](/Cxx/Visualization/MoveActor)| [vtkInteractorStyleTrackballActor](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballActor.html#details) |Moving an Actor.
[MoveCamera](/Cxx/Visualization/MoveCamera)| [vtkInteractorStyleTrackballCamera](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballCamera.html#details) |Moving the Camera.
[MultipleActors](/Cxx/Visualization/MultipleActors)| [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html#details) |Multiple Actors.
[NamedColorPatches ](/Cxx/Visualization/NamedColorPatches) | [vtkNamedColors](http://www.vtk.org/doc/nightly/html/classvtkNamedColors.html#details) | Creates a HTML file called [VTKNamedColorPatches](http://htmlpreview.github.com/?https://github.com/lorensen/VTKExamples/blob/master/src/Python/Visualization/VTKNamedColorPatches.html) showing the available colors in the vtkNamedColors class.
[NamedColors ](/Cxx/Visualization/NamedColors) | [vtkNamedColors](http://www.vtk.org/doc/nightly/html/classvtkNamedColors.html#details) | Demonstrates how to use the [vtkNamedColor](http://www.vtk.org/doc/nightly/html/classvtkNamedColor.html#details) class.
[NoShading](/Cxx/Visualization/NoShading) | [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html#details) [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html#details) [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html#details) |
[NormalsDemo](/Cxx/Visualization/NormalsDemo)| [vtkPolyDataNormals](http://www.vtk.org/doc/nightly/html/classvtkPolyDataNormals.html#details) | Demo different ooption to generate normals.
[Opacity](/Cxx/Visualization/Opacity)| [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html#details) | Transparency, transparent.
[OrientedGlyphs](/Cxx/Visualization/OrientedGlyphs)| [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html#details)|Create oriented glyphs from vector data.
[PointDataSubdivision](/Cxx/Visualization/PointDataSubdivision) | [vtkLinearSubdivisionFilter](http://www.vtk.org/doc/nightly/html/classvtkLinearSubdivisionFilter.html#details) [vtkButterflySubdivisionFilter](http://www.vtk.org/doc/nightly/html/classvtkButterflySubdivisionFilter.html#details) | Demonstrates the effect of applying these filters on various sources.
[PointSize](/Cxx/Visualization/PointSize) | [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html#details) |
[ProgrammableGlyphFilter](/Cxx/Visualization/ProgrammableGlyphFilter)| [vtkProgrammableGlyphFilter](http://www.vtk.org/doc/nightly/html/classvtkProgrammableGlyphFilter.html#details) |Generate a custom glyph at each point.
[QuadraticSurface](/Cxx/Visualization/QuadraticSurface)| [vtkQuadric](http://www.vtk.org/doc/nightly/html/classvtkQuadric.html#details) |Display a quadratic surface.
[QuadricLODActor](/Cxx/Visualization/QuadricLODActor)| [vtkQuadricLODActor](http://www.vtk.org/doc/nightly/html/classvtkQuadricLODActor.html#details) | Level of detail adjustment.
[RandomProbe](/Cxx/Visualization/RandomProbe)| [vtkProbeFilter](http://www.vtk.org/doc/nightly/html/classvtkProbeFilter.html#details)|Demonstrates how to probe a dataset with random points and select points inside the data set.
[RenderLargeImage](/Cxx/Visualization/RenderLargeImage)| [vtkRenderLargeImage](http://www.vtk.org/doc/nightly/html/classvtkRenderLargeImage.html#details) |Render a large image, larger than a window.
[RenderView](/Cxx/Views/RenderView)| [vtkRenderView](http://www.vtk.org/doc/nightly/html/classvtkRenderView.html#details) |A little bit easier rendering.
[ReverseAccess ](/Cxx/Visualization/ReverseAccess) | [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html#details)|Demonstrates how to access the source (e.g. [vtkSphereSource](http://www.vtk.org/doc/nightly/html/classvtkSphereSource.html#details)) of an actor reversely.
[RotateActor](/Cxx/Visualization/RotateActor)| [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html#details) |Rotate an Actor.
[ScalarBarActor](/Cxx/Visualization/ScalarBarActor)| [vtkScalarBarActor](http://www.vtk.org/doc/nightly/html/classvtkScalarBarActor.html#details) | Display a color bar.
[ScalarVisibility](/Cxx/Visualization/ScalarVisibility)| [vtkDataSetMapper](http://www.vtk.org/doc/nightly/html/classvtkDataSetMapper.html#details) | Switch between coloring the actor and coloring the data.
[ScaleGlyphs](/Cxx/Visualization/ScaleGlyphs)| [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html#details) [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html#details) |Scale glyphs.
[SceneBounds](/Cxx/Visualization/SceneBounds)| [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html#details) |Get the bounds of the whole scene.
[SelectWindowRegion](/Cxx/Visualization/SelectWindowRegion)|[vtkInteractorStyleRubberBand2D](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleRubberBand2D.html#details) |Select a region of a window.
[StreamLines](/Cxx/Visualization/StreamLines) | [vtkStreamTracer](http://www.vtk.org/doc/nightly/html/classvtkStreamTracer.html#details) | Streamlines.
[TensorGlyph](/Cxx/Visualization/TensorGlyph)| [vtkTensorGlyph](http://www.vtk.org/doc/nightly/html/classvtkTenorGlyph.html#details) | Draw a rotated/scaled glyph at each point.
[TextSource](/Cxx/Visualization/TextSource)| [vtkTextSource](http://www.vtk.org/doc/nightly/html/classvtkTextSource.html#details) |Display text.
[TransformActorCollection](/Cxx/Visualization/TransformActorCollection)| [vtkActorCollection](http://www.vtk.org/doc/nightly/html/classvtkActorCollection.html#details) |Transform an actor collection.
[TransformActor](/Cxx/Visualization/TransformActor)| [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html#details) |Transform an Actor.
[TubesFromSplines](/Cxx/VisualizationAlgorithms/TubesFromSplines)| [vtkTubeFilter](http://www.vtk.org/doc/nightly/html/classvtkTubeFilter.html#details) [vtkParametricFunctionSource](http://www.vtk.org/doc/nightly/html/classvtkParametricFunctionSource.html#details)  [vtkTupleInterpolator](http://www.vtk.org/doc/nightly/html/classvtkTupleInterpolator.html#details)|Create tubes from interpolated points and scalars.
[TubesWithVaryingRadiusAndColors](/Cxx/VisualizationAlgorithms/TubesWithVaryingRadiusAndColors)| [vtkTubeFilter](http://www.vtk.org/doc/nightly/html/classvtkTubeFilter.html#details) |Create tubes with varying radius and colors.
[VectorOfActors](/Cxx/Visualization/VectorOfActors)| [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html#details) |Multiple Actors in a Vector.
[VectorText](/Cxx/Visualization/VectorText)| [vtkVectorText](http://www.vtk.org/doc/nightly/html/classvtkVectorText.html#details) |Display high resolution text.
[VertexGlyphFilter ](/Cxx/Filtering/VertexGlyphFilter) | [vtkVertexGlyphFilter](http://www.vtk.org/doc/nightly/html/classvtkVertexGlyphFilter.html#details) | Add a vertex to each point.
[Visualize2DPoints](/Cxx/Visualization/Visualize2DPoints)| [vtkPolyDataMapper2D](http://www.vtk.org/doc/nightly/html/classvtkPolyDataMapper2D.html#details) [vtkProperty2D](http://www.vtk.org/doc/nightly/html/classvtkProperty2D.html#details) |Visualize a 2D Set of Points.
[VisualizeImageData](/Cxx/Visualization/VisualizeImageData)| [vtkDataSetMapper](http://www.vtk.org/doc/nightly/html/classvtkDataSetMapper.html#details) |Visualize the points of an ImageData.
[VisualizeVTP](/Cxx/Visualization/VisualizeVTP)| [vtkXMLPolyDataReader](http://www.vtk.org/doc/nightly/html/classvtkXMLPolyDataReader.html#details) [vtkPolyDataMapper](http://www.vtk.org/doc/nightly/html/classvtkPolyDataMapper.html#details) |Visualize a VTP File.
[WindowSize](/Cxx/Visualization/WindowSize)| [vtkRenderWindow](http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html#details):SetSize | Change the size of a window.
[WindowTitle](/Cxx/Visualization/WindowTitle)| [vtkRenderWindow](http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html#details) | Change the title of a window.
[Wireframe](/Cxx/Visualization/Wireframe)| [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html#details) |
[a KochSnowflake](/Cxx/Visualization/KochSnowflake) | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details) [vtkPolyLine](http://www.vtk.org/doc/nightly/html/classvtkPolyLine.html#details) [vtkTriangle](http://www.vtk.org/doc/nightly/html/classvtkTriangle.html#details) [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html#details)| Use recursion to represent a Koch snowflake fractal.

## Volume Rendering


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[HAVS](/Cxx/VolumeRendering/HAVSVolumeMapper)| [vtkHAVSVolumeMapper](http://www.vtk.org/doc/nightly/html/classvtkHAVSVolumeMapper.html#details) |
[MinIntensityRendering](/Cxx/VolumeRendering/MinIntensityRendering)| [vtkFixedPointVolumeRayCastMapper](http://www.vtk.org/doc/nightly/html/classvtkFixedPointVolumeRayCastMapper.html#details) |Min intensity rendering.
[SmartVolumeMapper](/Cxx/VolumeRendering/SmartVolumeMapper)| [vtkSmartVolumeMapper](http://www.vtk.org/doc/nightly/html/classvtkSmartVolumeMapper.html#details) |Smart volume mapper.


## User Interaction

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[AreaPicking](/Cxx/Picking/AreaPicking)| [vtkAreaPicker](http://www.vtk.org/doc/nightly/html/classvtkAreaPicker.html#details) |Area Picking.
[Assembly](/Cxx/Interaction/Assembly)| [vtkAssembly](http://www.vtk.org/doc/nightly/html/classvtkAssembly.html#details) | Combine/group actors into an assembly.
[CallData](/Cxx/Interaction/CallData)| [vtkCommand](http://www.vtk.org/doc/nightly/html/classvtkCommand.html#details) | Pass an observer a value (via CallData).
[CellPicking](/Cxx/Picking/CellPicking)| [vtkCellPicker](http://www.vtk.org/doc/nightly/html/classvtkCellPicker.html#details) | Cell Picking.
[ClientData](/Cxx/Interaction/ClientData)| [vtkCommand](http://www.vtk.org/doc/nightly/html/classvtkCommand.html#details) | Give an observer access to an object (via ClientData).
[DoubleClick](/Cxx/Interaction/DoubleClick)| [vtkInteractorStyleTrackballCamera](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballCamera.html#details) |Catch a double click.
[Game](/Cxx/Interaction/Game)| [vtkInteractorStyleTrackballActor](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballActor.html#details) | Move a cube into a sphere.
[EllipticalButton](/Cxx/Interaction/EllipticalButton)| [vtkEllipticalButtonSource](http://www.vtk.org/doc/nightly/html/classvtkEllipticalButtonSource.html#details) [vtkButtonWidget](http://www.vtk.org/doc/nightly/html/classvtkButtonWidget.html#details) |Create an elliptical button.
[HighlightPickedActor](/Cxx/Picking/HighlightPickedActor)| [vtkPropPicker](http://www.vtk.org/doc/nightly/html/classvtkPropPicker.html#details) |Highlight a picked actor.
[HighlightSelectedPoints](/Cxx/Picking/HighlightSelectedPoints)| [vtkExtractGeometry](http://www.vtk.org/doc/nightly/html/classvtkExtractGeometry.html#details) |Highlight Selected Points.
[HighlightSelection](/Cxx/Picking/HighlightSelection)| [vtkExtractPolyDataGeometry](http://www.vtk.org/doc/nightly/html/classvtkExtractPolyDataGeometry.html#details) |Highlight selection.
[ImageClip](/Cxx/Interaction/ImageClip)| [vtkImageClip](http://www.vtk.org/doc/nightly/html/classvtkImageClip.html#details) | Demonstrates how to interactively select and display a region of an image.
[ImageRegion](/Cxx/Interaction/ImageRegion)| [vtkCommand](http://www.vtk.org/doc/nightly/html/classvtkCommand.html#details) |Select a region of an image.
[InteractorStyleTerrain](/Cxx/Interaction/InteractorStyleTerrain)| [vtkInteractorStyleTerrain](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTerrain.html#details) |Terrain mode.
[InteractorStyleUser](/Cxx/Interaction/InteractorStyleUser)| [vtkInteractorStyleUser](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleUser.html#details) | Create a completely custom interactor style (no default functionality is provided)
[KeypressEvents](/Cxx/Interaction/KeypressEvents)| [vtkInteractorStyleTrackballCamera](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballCamera.html#details) |Handle keypress events.
[KeypressObserver ](/Cxx/Interaction/KeypressObserver) | [vtkCallbackCommand](http://www.vtk.org/doc/nightly/html/classvtkCallbackCommand.html#details) | This uses a callback function rather than a derived interactor class. Handle keypress events (lightweight).
[MouseEvents ](/Cxx/Interaction/MouseEvents) | [vtkInteractorStyleTrackballCamera](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballCamera.html#details) | Subclass the interactor style. Handle mouse events.
[MouseEventsObserver ](/Cxx/Interaction/MouseEventsObserver) | [vtkCallbackCommand](http://www.vtk.org/doc/nightly/html/classvtkCallbackCommand.html#details) | Use an observer. Handle mouse events (light weight).
[MoveAGlyph](/Cxx/Interaction/MoveAGlyph)| [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html#details) | Drag a glyph around.
[MoveAVertexUnstructuredGrid](/Cxx/Interaction/MoveAVertexUnstructuredGrid)| [vtkPointPicker](http://www.vtk.org/doc/nightly/html/classvtkPointPicker.html#details) | Click and drag a vertex of a [vtkUnstructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html#details).
[ObserverMemberFunction](/Cxx/Interaction/ObserverMemberFunction)|  | Set observers to be class member functions.
[PickableOff](/Cxx/Interaction/PickableOff)| [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html#details) |Disallow interaction with a specific actor.
[Picking](/Cxx/Interaction/Picking)| [vtkPropPicker](http://www.vtk.org/doc/nightly/html/classvtkPropPicker.html#details) | Get the world coordinate of the mouse click (if you clicked an actor)
[PointPicker](/Cxx/Interaction/PointPicker)| [vtkPointPicker](http://www.vtk.org/doc/nightly/html/classvtkPointPicker.html#details) | Get the coordinates of the closest point in the data set to the mouse click.
[RubberBand2DObserver](/Cxx/Interaction/RubberBand2DObserver)| [vtkInteractorStyleRubberBand2D](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleRubberBand2D.html#details) |RubberBand2D Observer.
[RubberBand2D](/Cxx/Interaction/RubberBand2D)| [vtkInteractorStyleRubberBand2D](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleRubberBand2D.html#details) |
[RubberBand3D](/Cxx/Interaction/RubberBand3D)| [vtkInteractorStyleRubberBand3D](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleRubberBand3D.html#details) |
[RubberBandPick](/Cxx/Interaction/RubberBandPick)| [vtkInteractorStyleRubberBandPick](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleRubberBandPick.html#details) |
[RubberBandZoom](/Cxx/Interaction/RubberBandZoom)| [vtkInteractorStyleRubberBandZoom](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleRubberBandZoom.html#details) |
[SelectAnActor](/Cxx/Interaction/SelectAnActor)| [vtkPropPicker](http://www.vtk.org/doc/nightly/html/classvtkPropPicker.html#details) |Select an actor.
[SelectAVertex](/Cxx/Interaction/SelectAVertex)| [vtkPointPicker](http://www.vtk.org/doc/nightly/html/classvtkPointPicker.html#details) | Click and drag a vertex of a [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details).
[ShiftAndControl](/Cxx/Interaction/ShiftAndControl)| [vtkRenderWindowInteractor](http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html#details) | Hold/holding down a key. Check if shift or control is being held.
[StyleSwitch](/Cxx/Interaction/StyleSwitch)| [vtkInteractorStyleSwitch](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleSwitch.html#details) |Choose between multiple interaction modes.
[TrackballActor](/Cxx/Interaction/TrackballActor)| [vtkInteractorStyleTrackballActor](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballActor.html#details) |Trackball actor mode.
[TrackballCamera](/Cxx/Interaction/TrackballCamera)| [vtkInteractorStyleTrackballCamera](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballCamera.html#details) |Trackball camera mode.
[UserEvent](/Cxx/Interaction/UserEvent)|  | Simple observer. Create, invoke, and handle a custom event.
[WorldPointPicker](/Cxx/Interaction/WorldPointPicker)| [vtkWorldPointPicker](http://www.vtk.org/doc/nightly/html/classvtkWorldPointPicker.html#details) |Get world coordinates of mouse click.


## Working with Images

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Actor2D](/Cxx/Images/Actor2D)| [vtkActor2D](http://www.vtk.org/doc/nightly/html/classvtkActor2D.html#details) [vtkMapper2D](http://www.vtk.org/doc/nightly/html/classvtkMapper2D.html#details) |2D actor and mapper.
[BackgroundImage](/Cxx/Images/BackgroundImage)|  [vtkImageCanvasSource2D](http://www.vtk.org/doc/nightly/html/classvtkImageCanvasSource2D.html#details) |Display an image as the background of a scene.
[BorderPixelSize](/Cxx/Images/BorderPixelSize)| [vtkImageSliceMapper](http://www.vtk.org/doc/nightly/html/classvtkImageSliceMapper.html#details) |Set the size of border pixels.
[CannyEdgeDetector](/Cxx/Images/CannyEdgeDetector)| | Perform Canny edge detection on an image.
[Cast](/Cxx/Images/Cast)| [vtkImageCast](http://www.vtk.org/doc/nightly/html/classvtkImageCast.html#details) |Cast an image to a different type.
[DotProduct](/Cxx/Images/DotProduct)| [vtkImageDotProduct](http://www.vtk.org/doc/nightly/html/classvtkImageDotProduct.html#details) | Compute the pixel-wise dot product of two vector images.
[DrawOnAnImage](/Cxx/Images/DrawOnAnImage)| [vtkImageCanvasSource2D](http://www.vtk.org/doc/nightly/html/classvtkImageCanvasSource2D.html#details) |Drawing on an image.
[DrawShapes](/Cxx/Images/DrawShapes)| [vtkImageCanvasSource2D](http://www.vtk.org/doc/nightly/html/classvtkImageCanvasSource2D.html#details) |Drawing shapes in an image.
[ExtractComponents](/Cxx/Images/ExtractComponents)| [vtkImageExtractComponents](http://www.vtk.org/doc/nightly/html/classvtkImageExtractComponents.html#details) |  Extract components of an image. This can be used to get, for example, the red channel of an image.
[FillWindow](/Cxx/Images/FillWindow)| [vtkCamera](http://www.vtk.org/doc/nightly/html/classvtkCamera.html#details) | Fit imageSetup the camera to fill the window with an image.
[ImageAccumulateGreyscale](/Cxx/Images/ImageAccumulateGreyscale)| [vtkImageAccumulate](http://www.vtk.org/doc/nightly/html/classvtkImageAccumulate.html#details) [vtkBarChartActor](http://www.vtk.org/doc/nightly/html/classvtkBarChartActor.html#details) | Display a greyscale histogram.
[ImageCheckerboard](/Cxx/Images/ImageCheckerboard)| [vtkImageCheckerboard](http://www.vtk.org/doc/nightly/html/classvtkImageCheckerboard.html#details) |Visually Compare Two Images.
[ImageCityBlockDistance](/Cxx/Images/ImageCityBlockDistance)| [vtkImageCityBlockDistance](http://www.vtk.org/doc/nightly/html/classvtkImageCityBlockDistance.html#details) | Compute the Manhattan distance from every point to every black point in a binary image.
[ImageDilateErode3D](/Cxx/Images/ImageDilateErode3D)| [vtkImageDilateErode3D](http://www.vtk.org/doc/nightly/html/classvtkImageDilateErode3D.html#details) | Dilate or erode an image.
[ImageExport ](/Cxx/Images/ImageExport) | [vtkImageExport](http://www.vtk.org/doc/nightly/html/classvtkImageExport.html#details) | Export an image to a C array.
[ImageGridSource](/Cxx/Images/ImageGridSource)| [vtkImageGridSource](http://www.vtk.org/doc/nightly/html/classvtkImageGridSource.html#details) |Create a image of a grid.
[ImageHybridMedian2D](/Cxx/Images/ImageHybridMedian2D)| [vtkImageHybridMedian2D](http://www.vtk.org/doc/nightly/html/classvtkImageHybridMedian2D.html#details) | Median filter an image.
[ImageIdealHighPass](/Cxx/Images/ImageIdealHighPass)| [vtkImageIdealHighPass](http://www.vtk.org/doc/nightly/html/classvtkImageIdealHighPass.html#details) |High pass filter an image.
[ImageImport ](/Cxx/Images/ImageImport) | [vtkImageImport](http://www.vtk.org/doc/nightly/html/classvtkImageImport.html#details) | Import an image from a C array.
[ImageIslandRemoval2D](/Cxx/Images/ImageIslandRemoval2D)| [vtkImageIslandRemoval2D](http://www.vtk.org/doc/nightly/html/classvtkImageIslandRemoval2D.html#details) | Remove small patches from an image.
[ImageMagnify](/Cxx/Images/ImageMagnify)| [vtkImageMagnify](http://www.vtk.org/doc/nightly/html/classvtkImageMagnify.html#details) | Supersample and stretch an image.
[ImageMandelbrotSource](/Cxx/Images/ImageMandelbrotSource)| [vtkImageMandelbrotSource](http://www.vtk.org/doc/nightly/html/classvtkImageMandelbrotSource.html#details) |Create a Mandelbrot image.
[ImageMask](/Cxx/Images/ImageMask)| [vtkImageMask](http://www.vtk.org/doc/nightly/html/classvtkImageMask.html#details) |Mask a region of an image.
[ImageMathematics](/Cxx/Images/ImageMathematics)| [vtkImageMathematics](http://www.vtk.org/doc/nightly/html/classvtkImageMathematics.html#details) |Perform mathematical operations on an image.
[ImageMedian3D](/Cxx/Images/ImageMedian3D)| [vtkImageMedian3D](http://www.vtk.org/doc/nightly/html/classvtkImageMedian3D.html#details) | Median filter a 3d or 2d image.
[ImageMirrorPad](/Cxx/Images/ImageMirrorPad)| [vtkImageMirrorPad](http://www.vtk.org/doc/nightly/html/classvtkImageMirrorPad.html#details) | Pad the edges of an extended image by mirror existing pixels.
[ImageNonMaximumSuppression](/Cxx/Images/ImageNonMaximumSuppression)| [vtkImageNonMaximumSuppression](http://www.vtk.org/doc/nightly/html/classvtkImageNonMaximumSuppression.html#details) |Find peaks in an image using non maximum suppression.
[ImageOpenClose3D](/Cxx/Images/ImageOpenClose3D)| [vtkImageOpenClose3D](http://www.vtk.org/doc/nightly/html/classvtkImageOpenClose3D.html#details) | Open or close (morphologically) an image.
[ImageRFFT](/Cxx/Images/ImageRFFT)| [vtkImageRFFT](http://www.vtk.org/doc/nightly/html/classvtkImageRFFT.html#details) | Inverse FFT.
[ImageRange3D](/Cxx/Images/ImageRange3D)| [vtkImageRange3D](http://www.vtk.org/doc/nightly/html/classvtkImageRange3D.html#details) | Replace every pixel with the range of its neighbors according to a kernel.
[ImageRotate](/Cxx/Images/ImageRotate)| [vtkImageSlice](http://www.vtk.org/doc/nightly/html/classvtkImageSlice.html#details) [vtkImageResliceMapper](http://www.vtk.org/doc/nightly/html/classvtkImageResliceMapper.html#details) | Rotate a 2D image. This is even more powerful than [vtkImageSliceMapper](http://www.vtk.org/doc/nightly/html/classvtkImageSliceMapper.html#details). It can also do oblique slices.
[ImageSeparableConvolution](/Cxx/Images/ImageSeparableConvolution)| [vtkImageSeparableConvolution](http://www.vtk.org/doc/nightly/html/classvtkImageSeparableConvolution.html#details) | Convolve a separable kernel with an image.
[ImageShiftScale](/Cxx/Images/ImageShiftScale)| [vtkImageShiftScale](http://www.vtk.org/doc/nightly/html/classvtkImageShiftScale.html#details) | Shift and scale an image.
[ImageSinusoidSource](/Cxx/Images/ImageSinusoidSource)| [vtkImageSinusoidSource](http://www.vtk.org/doc/nightly/html/classvtkImageSinusoidSource.html#details) |Create a sinusoidal image.
[ImageSliceMapper](/Cxx/Images/ImageSliceMapper)| [vtkImageSlice](http://www.vtk.org/doc/nightly/html/classvtkImageSlice.html#details) [vtkImageSliceMapper](http://www.vtk.org/doc/nightly/html/classvtkImageSliceMapper.html#details) | Visualize and interact with an image. This is the new way to do this. It is much more powerful.
[ImageSlice](/Cxx/Images/ImageSlice)| [vtkImageSlice](http://www.vtk.org/doc/nightly/html/classvtkImageSlice.html#details) [vtkImageResliceMapper](http://www.vtk.org/doc/nightly/html/classvtkImageResliceMapper.html#details) | Visualize and interact with an image. This is even more powerful than [vtkImageSliceMapper](http://www.vtk.org/doc/nightly/html/classvtkImageSliceMapper.html#details). It can also do oblique slices.
[ImageStack](/Cxx/Images/ImageStack)| [vtkImageStack](http://www.vtk.org/doc/nightly/html/classvtkImageStack.html#details) |Display layers of images.
[ImageStencil](/Cxx/Images/ImageStencil)| [vtkImageStencil](http://www.vtk.org/doc/nightly/html/classvtkImageStencil.html#details) [vtkImageToImageStencil](http://www.vtk.org/doc/nightly/html/classvtkImageToImageStencil.html#details) | Copy one image into another image.
[ImageText](/Cxx/Images/ImageText)| [vtkFreeTypeUtilities](http://www.vtk.org/doc/nightly/html/classvtkFreeTypeUtilities.html#details) [vtkImageBlend](http://www.vtk.org/doc/nightly/html/classvtkImageBlend.html#details) | Draw text in an image.
[ImageThreshold](/Cxx/Images/ImageThreshold)| [vtkImageThreshold](http://www.vtk.org/doc/nightly/html/classvtkImageThreshold.html#details) |Threshold an image.
[ImageToPolyDataFilter](/Cxx/Images/ImageToPolyDataFilter)| [vtkImageToPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkImageToPolyDataFilter.html#details) [vtkImageQuantizeRGBToIndex](http://www.vtk.org/doc/nightly/html/classvtkImageQuantizeRGBToIndex.html#details) | Convert a [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html#details) to a [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details).
[ImageToStructuredPoints](/Cxx/Images/ImageToStructuredPoints)| [vtkImageToStructuredPoints](http://www.vtk.org/doc/nightly/html/classvtkImageToStructuredPoints.html#details) | Convert a [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html#details) to a [vtkStructuredPoints](http://www.vtk.org/doc/nightly/html/classvtkStructuredPoints.html#details).
[InteractWithImage](/Cxx/Images/InteractWithImage)| [vtkImageActor](http://www.vtk.org/doc/nightly/html/classvtkImageActor.html#details) [vtkInteractorStyleImage](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleImage.html#details) |Visualize and interact with an image.
[Interpolation](/Cxx/Images/Interpolation)| [vtkImageSlice](http://www.vtk.org/doc/nightly/html/classvtkImageSlice.html#details) [vtkImageProperty](http://www.vtk.org/doc/nightly/html/classvtkImageProperty.html#details) | Set the interpolation type for the display of an image. If pixels look blurry instead of sharp when zoomed in, change this.
[MarkKeypoints](/Cxx/Images/MarkKeypoints)| [vtkVectorText](http://www.vtk.org/doc/nightly/html/classvtkVectorText.html#details) [vtkFollower](http://www.vtk.org/doc/nightly/html/classvtkFollower.html#details) |Mark keypoints in an image.
[NegativeIndices](/Cxx/Images/NegativeIndices)| [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html#details) | A very powerful feature of [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html#details) is that you can use negative indices.
[PickPixel2](/Cxx/Images/PickPixel2)| [vtkPropPicker](http://www.vtk.org/doc/nightly/html/classvtkPropPicker.html#details) |Picking a pixel 2 - modified version for exact pixel values.
[PickPixel](/Cxx/Images/PickPixel)| [vtkPropPicker](http://www.vtk.org/doc/nightly/html/classvtkPropPicker.html#details) |Picking a pixel.
[RTAnalyticSource](/Cxx/Images/RTAnalyticSource)| [vtkRTAnalyticSource](http://www.vtk.org/doc/nightly/html/classvtkRTAnalyticSource.html#details) | An image source that can be used for regression testing
[StaticImage](/Cxx/Images/StaticImage)|  v[vtkImageViewer2](http://www.vtk.org/doc/nightly/html/classvtkImageViewer2.html#details) | This will display the image, but not allow you to interact with it.
[Transparency](/Cxx/Images/Transparency)| [vtkImageMapToColors](http://www.vtk.org/doc/nightly/html/classvtkImageMapToColors.html#details) [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html#details) | Make part of an image transparent.


## Image Processing

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Colored2DImageFusion](/Cxx/Images/Colored2DImageFusion)| [vtkImageMapToColors](http://www.vtk.org/doc/nightly/html/classvtkImageMapToColors.html#details) |Blending 2D images with different color maps.
[CenterAnImage](/Cxx/Images/CenterAnImage)| [vtkImageChangeInformation](http://www.vtk.org/doc/nightly/html/classvtkImageChangeInformation.html#details) |Center an image.
[CombineImages](/Cxx/Images/CombineImages)| [vtkImageBlend](http://www.vtk.org/doc/nightly/html/classvtkImageBlend.html#details) |Combine two images.
[CombiningRGBChannels](/Cxx/Images/CombiningRGBChannels)| [vtkImageAppendComponents](http://www.vtk.org/doc/nightly/html/classvtkImageAppendComponents.html#details) |Combine layers into an RGB image.
[ImageMagnitude](/Cxx/Images/ImageMagnitude)| [vtkImageMagnitude](http://www.vtk.org/doc/nightly/html/classvtkImageMagnitude.html#details) | grayscaleConvert RGB image to greyscale.
[Flip](/Cxx/Images/Flip)| [vtkImageFlip](http://www.vtk.org/doc/nightly/html/classvtkImageFlip.html#details) | Flip an image.
[Gradient](/Cxx/Images/Gradient)| [vtkImageGradient](http://www.vtk.org/doc/nightly/html/classvtkImageGradient.html#details) | Compute the gradient vector at every pixel.
[ImageAccumulate](/Cxx/Images/ImageAccumulate)| [vtkImageAccumulate](http://www.vtk.org/doc/nightly/html/classvtkImageAccumulate.html#details) | Histogram
[ImageAnisotropicDiffusion2D](/Cxx/Images/ImageAnisotropicDiffusion2D)| [vtkImageAnisotropicDiffusion2D](http://www.vtk.org/doc/nightly/html/classvtkImageAnisotropicDiffusion2D.html#details) |Anisotropic diffusion (2D).
[ImageContinuousDilate3D](/Cxx/Images/ImageContinuousDilate3D)| [vtkImageContinuousDilate3D](http://www.vtk.org/doc/nightly/html/classvtkImageContinuousDilate3D.html#details) |Dilate an image.
[ImageContinuousErode3D](/Cxx/Images/ImageContinuousErode3D)| [vtkImageContinuousErode3D](http://www.vtk.org/doc/nightly/html/classvtkImageContinuousErode3D.html#details) |Erode an image.
[ImageConvolve](/Cxx/Images/ImageConvolve)| [vtkImageConvolve](http://www.vtk.org/doc/nightly/html/classvtkImageConvolve.html#details) |Convolve an image with a kernel.
[ImageCorrelation](/Cxx/Images/ImageCorrelation)| [vtkImageCorrelation](http://www.vtk.org/doc/nightly/html/classvtkImageCorrelation.html#details) |Correlate two images.
[ImageDifference](/Cxx/Images/ImageDifference)| [vtkImageDifference](http://www.vtk.org/doc/nightly/html/classvtkImageDifference.html#details) |Compute the difference image of two images.
[ImageDivergence](/Cxx/Images/ImageDivergence)| [vtkImageDivergence](http://www.vtk.org/doc/nightly/html/classvtkImageDivergence.html#details) |Divergence of a vector field.
[ImageEllipsoidSource](/Cxx/Images/ImageEllipsoidSource)| [vtkImageEllipsoidSource](http://www.vtk.org/doc/nightly/html/classvtkImageEllipsoidSource.html#details) |Create an image of an ellipsoid.
[ImageFFT](/Cxx/Images/ImageFFT)| [vtkImageFFT](http://www.vtk.org/doc/nightly/html/classvtkImageFFT.html#details) |Compute the FFT of an image.
[ImageGaussianSmooth](/Cxx/Images/ImageGaussianSmooth)| [vtkImageGaussianSmooth](http://www.vtk.org/doc/nightly/html/classvtkImageGaussianSmooth.html#details) |Smooth an image.
[ImageGradientMagnitude](/Cxx/Images/ImageGradientMagnitude)| [vtkImageGradientMagnitude](http://www.vtk.org/doc/nightly/html/classvtkImageGradientMagnitude.html#details) |Compute the magnitude of the gradient at each pixel of an image.
[ImageLaplacian](/Cxx/Images/ImageLaplacian)| [vtkImageLaplacian](http://www.vtk.org/doc/nightly/html/classvtkImageLaplacian.html#details) |Compute the Laplacian of an image.
[ImageLuminance](/Cxx/Images/ImageLuminance)| [vtkImageLuminance](http://www.vtk.org/doc/nightly/html/classvtkImageLuminance.html#details) |Convert RGB image to greyscale (luminance).
[ImageMapToColors](/Cxx/Images/ImageMapToColors)| [vtkImageMapToColors](http://www.vtk.org/doc/nightly/html/classvtkImageMapToColors.html#details) | Use a lookup table to map scalar (grayscale) values to colorsConvert greyscale image to RGB.
[ImageNoiseSource](/Cxx/Images/ImageNoiseSource)| [vtkImageNoiseSource](http://www.vtk.org/doc/nightly/html/classvtkImageNoiseSource.html#details) |Create an image of noise.
[ImagePermute](/Cxx/Images/ImagePermute)| [vtkImagePermute](http://www.vtk.org/doc/nightly/html/classvtkImagePermute.html#details) |Switch axes of an image.
[ImageShrink3D](/Cxx/Images/ImageShrink3D)| [vtkImageShrink3D](http://www.vtk.org/doc/nightly/html/classvtkImageShrink3D.html#details) |Resample an image.
[ImageSobel2D](/Cxx/Images/ImageSobel2D)| [vtkImageSobel2D](http://www.vtk.org/doc/nightly/html/classvtkImageSobel2D.html#details) |Sobel edge detection 2D.
[ImageValueRange](/Cxx/Images/ImageValueRange)| [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html#details) | Get the range of image pixel values (min/max).
[ImageVariance3D](/Cxx/Images/ImageVariance3D)| [vtkImageVariance3D](http://www.vtk.org/doc/nightly/html/classvtkImageVariance3D.html#details) | Construct a new image consisting of the variance of the input image at each pixel.
[RGBToHSV](/Cxx/Images/RGBToHSV)| [vtkImageRGBToHSV](http://www.vtk.org/doc/nightly/html/classvtkImageRGBToHSV.html#details) |Convert RGB to HSV.
[RescaleAnImage](/Cxx/ImageProcessing/RescaleAnImage) | [vtkImageShiftScale](http://www.vtk.org/doc/nightly/html/classvtkImageShiftScale.html#details) | Rescale an image
[ResizeImage](/Cxx/Images/ResizeImage)| [vtkImageResize](http://www.vtk.org/doc/nightly/html/classvtkImageResize.html#details) [vtkImageSincInterpolator](http://www.vtk.org/doc/nightly/html/classvtkImageSincInterpolator.html#details)| Resize an image using a sinc interpolator.


## Widgets

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[PolygonalSurfacePointPlacer](/Cxx/PolyData/PolygonalSurfacePointPlacer)| [vtkPolygonalSurfacePointPlacer](http://www.vtk.org/doc/nightly/html/classvtkPolygonalSurfacePointPlacer.html#details) | Used in conjuntion with [vtkContourWidget](http://www.vtk.org/doc/nightly/html/classvtkContourWidget.html#details) to draw curves on a surface.
[AffineWidget](/Cxx/Widgets/AffineWidget)| [vtkAffineWidget](http://www.vtk.org/doc/nightly/html/classvtkAffineWidget.html#details) | Apply an affine transformation interactively.
[AngleWidget2D](/Cxx/Widgets/AngleWidget2D)| [vtkAngleWidget](http://www.vtk.org/doc/nightly/html/classvtkAngleWidget.html#details) [vtkAngleRepresentation2D](http://www.vtk.org/doc/nightly/html/classvtkAngleRepresentation2D.html#details) |[vtkAngleWidget](http://www.vtk.org/doc/nightly/html/classvtkAngleWidget.html#details) + [vtkAngleRepresentation2D](http://www.vtk.org/doc/nightly/html/classvtkAngleRepresentation2D.html#details).
[AngleWidget](/Cxx/Widgets/AngleWidget)| [vtkAngleWidget](http://www.vtk.org/doc/nightly/html/classvtkAngleWidget.html#details) |
[BalloonWidget](/Cxx/Widgets/BalloonWidget)| [vtkBalloonWidget](http://www.vtk.org/doc/nightly/html/classvtkBalloonWidget.html#details) |
[BiDimensionalWidget](/Cxx/Widgets/BiDimensionalWidget) |  [vtkBiDimensionalWidget](http://www.vtk.org/doc/nightly/html/classvtkBiDimensionalWidget.html#details) |  When would you use this?
[BorderWidget](/Cxx/Widgets/BorderWidget)| [vtkBorderWidget](http://www.vtk.org/doc/nightly/html/classvtkBorderWidget.html#details) | 2D selection, 2D box.
[BoxWidget2](/Cxx/Widgets/BoxWidget2)| [vtkBoxWidget2](http://www.vtk.org/doc/nightly/html/classvtkBoxWidget2.html#details) |
[BoxWidget](/Cxx/Widgets/BoxWidget)| [vtkBoxWidget](http://www.vtk.org/doc/nightly/html/classvtkBoxWidget.html#details) |
[CaptionWidget](/Cxx/Widgets/CaptionWidget)| [vtkCaptionWidget](http://www.vtk.org/doc/nightly/html/classvtkCaptionWidget.html#details) |
[CheckerboardWidget](/Cxx/Widgets/CheckerboardWidget)| [vtkCheckerboardWidget](http://www.vtk.org/doc/nightly/html/classvtkCheckerboardWidget.html#details) [vtkCheckerboardRepresentation](http://www.vtk.org/doc/nightly/html/classvtkCheckerboardRepresentation.html#details) | Compare two images using a checkerboard.
[ContourWidget ](/Cxx/Widgets/ContourWidget) | [vtkContourWidget](http://www.vtk.org/doc/nightly/html/classvtkContourWidget.html#details) | Create a contour from a set of points and dynamically change the contour using the points as control points.
[Cursor2D](/Cxx/Visualization/Cursor2D)| [vtkCursor2D](http://www.vtk.org/doc/nightly/html/classvtkCursor2D.html#details) |
[DistanceWidget](/Cxx/Widgets/DistanceWidget) | [vtkDistanceWidget](http://www.vtk.org/doc/nightly/html/classvtkDistanceWidget.html#details) |
[HoverWidget](/Cxx/Widgets/HoverWidget)| [vtkHoverWidget](http://www.vtk.org/doc/nightly/html/classvtkHoverWidget.html#details) | How to detect a hover? 
[ImagePlaneWidget](/Cxx/Widgets/ImagePlaneWidget)| [vtkImagePlaneWidget](http://www.vtk.org/doc/nightly/html/classvtkImagePlaneWidget.html#details) |
[ImageTracerWidgetInsideContour](/Cxx/Widgets/ImageTracerWidgetInsideContour)| [vtkImageTracerWidget](http://www.vtk.org/doc/nightly/html/classvtkImageTracerWidget.html#details) | Highlight pixels inside a non-regular region scribbled on an image.
[ImageTracerWidgetNonPlanar](/Cxx/Widgets/ImageTracerWidgetNonPlanar)| [vtkImageTracerWidget](http://www.vtk.org/doc/nightly/html/classvtkImageTracerWidget.html#details) |Draw on a non-planar surface.
[ImageTracerWidget](/Cxx/Widgets/ImageTracerWidget)| [vtkImageTracerWidget](http://www.vtk.org/doc/nightly/html/classvtkImageTracerWidget.html#details) | Scribble on an image.
[ImplicitPlaneWidget2](/Cxx/Widgets/ImplicitPlaneWidget2)| [vtkImplicitPlaneWidget2](http://www.vtk.org/doc/nightly/html/classvtkImplicitPlaneWidget2.html#details) | Clip polydata with an implicit plane.
[LineWidget2](/Cxx/Widgets/LineWidget2)| [vtkLineWidget2](http://www.vtk.org/doc/nightly/html/classvtkLineWidget2.html#details) |
[LogoWidget](/Cxx/Widgets/LogoWidget)| [vtkLogoWidget](http://www.vtk.org/doc/nightly/html/classvtkLogoWidget.html#details) |Logo widget.
[OrientationMarkerWidget](/Cxx/Widgets/OrientationMarkerWidget)| [vtkOrientationMarkerWidget](http://www.vtk.org/doc/nightly/html/classvtkOrientationMarkerWidget.html#details) | Display a polydata as an orientation icon.
[PlaneWidget ](/Cxx/Widgets/PlaneWidget) | [vtkPlaneWidget](http://www.vtk.org/doc/nightly/html/classvtkPlaneWidget.html#details) | Interact with a plane.
[RectilinearWipeWidget](/Cxx/Widgets/RectilinearWipeWidget)| [vtkImageRectilinearWipe](http://www.vtk.org/doc/nightly/html/classvtkImageRectilinearWipe.html#details) [vtkRectilinearWipeWidget](http://www.vtk.org/doc/nightly/html/classvtkRectilinearWipeWidget.html#details) [vtkRectilinearWipeRepresentation](http://www.vtk.org/doc/nightly/html/classvtkRectilinearWipeRepresentation.html#details) | Compare two images.
[SeedWidgetImage](/Cxx/Widgets/SeedWidgetImage)| [vtkImageViewer2](http://www.vtk.org/doc/nightly/html/classvtkImageViewer2.html#details) [vtkSeedWidget](http://www.vtk.org/doc/nightly/html/classvtkSeedWidget.html#details) | How to start the interaction? 
[SeedWidget](/Cxx/Widgets/SeedWidget)| [vtkSeedWidget](http://www.vtk.org/doc/nightly/html/classvtkSeedWidget.html#details) |Seed widget.
[Slider2D](/Cxx/Widgets/Slider2D)| [vtkSliderWidget](http://www.vtk.org/doc/nightly/html/classvtkSliderWidget.html#details) [vtkSliderRepresentation2D](http://www.vtk.org/doc/nightly/html/classvtkSliderRepresentation2D.html#details)|2D Slider.
[Slider](/Cxx/Widgets/Slider)| [vtkSliderWidget](http://www.vtk.org/doc/nightly/html/classvtkSliderWidget.html#details) [vtkSliderRepresentation3D](http://www.vtk.org/doc/nightly/html/classvtkSliderRepresentation3D.html#details) |3D Slider.
[SphereWidget2](/Cxx/Widgets/SphereWidget2)| [vtkSphereWidget2](http://www.vtk.org/doc/nightly/html/classvtkSphereWidget2.html#details) |
[SphereWidgetEvents ](/Cxx/Widgets/SphereWidgetEvents)| [vtkSphereWidget](http://www.vtk.org/doc/nightly/html/classvtkSphereWidget.html#details) |Sphere widget events.
[SphereWidget](/Cxx/Widgets/SphereWidget)| [vtkSphereWidget](http://www.vtk.org/doc/nightly/html/classvtkSphereWidget.html#details) |Sphere widget.
[SplineWidget](/Cxx/Widgets/SplineWidget)| [vtkSplineWidget](http://www.vtk.org/doc/nightly/html/classvtkSplineWidget.html#details) |
[TextWidget](/Cxx/Widgets/TextWidget)| [vtkSeedWidget](http://www.vtk.org/doc/nightly/html/classvtkSeedWidget.html#details) || [vtkTextWidget](http://www.vtk.org/doc/nightly/html/classvtkTextWidget.html#details) |Draw movable text.
[TexturedButtonWidget](/Cxx/Widgets/TexturedButtonWidget) | [vtkButtonWidget](http://www.vtk.org/doc/nightly/html/classvtkButtonWidget.html#details) [vtkTexturedButtonRepresentation2D](http://www.vtk.org/doc/nightly/html/classvtkTexturedButtonRepresentation2D.html#details) |Create a textured 2D buttonx.

## Plotting

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[BarChart](/Cxx/Plotting/BarChart)| [vtkChartXY](http://www.vtk.org/doc/nightly/html/classvtkChartXY.html#details) |Bar chart.
[BoxChart](/Cxx/Plotting/BoxChart)| [vtkChartBox](http://www.vtk.org/doc/nightly/html/classvtkChartBox.html#details) |Box plot.
[Diagram](/Cxx/Plotting/Diagram)| |
[LinePlot](/Cxx/Plotting/LinePlot)| [vtkChartXY](http://www.vtk.org/doc/nightly/html/classvtkChartXY.html#details) |Line plot.
[ParallelCoordinates](/Cxx/Plotting/ParallelCoordinates)| [vtkChartParallelCoordinates](http://www.vtk.org/doc/nightly/html/classvtkChartParallelCoordinates.html#details) |Parallel coordinates.
[PieChart](/Cxx/Plotting/PieChart)| [vtkChartPie](http://www.vtk.org/doc/nightly/html/classvtkChartPie.html#details) [vtkPlotPie](http://www.vtk.org/doc/nightly/html/classvtkPlotPie.html#details) |Pie chart.
[ScatterPlot](/Cxx/Plotting/ScatterPlot)| [vtkPlotPoints](http://www.vtk.org/doc/nightly/html/classvtkPlotPoints.html#details) |Scatter plot.
[SpiderPlot](/Cxx/Plotting/SpiderPlot)| [vtkSpiderPlotActor](http://www.vtk.org/doc/nightly/html/classvtkSpiderPlotActor.html#details) |Spider plot.
[StackedBar](/Cxx/Plotting/StackedBar)| [vtkPlotBar](http://www.vtk.org/doc/nightly/html/classvtkPlotBar.html#details) |Stacked bar.
[StackedPlot](/Cxx/Plotting/StackedPlot)| [vtkPlotStacked](http://www.vtk.org/doc/nightly/html/classvtkPlotStacked.html#details) |Stacked plot.


## Animation

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[AnimateActors](/Cxx/Animation/AnimateActors) | [vtkAnimationScene](http://www.vtk.org/doc/nightly/html/classvtkAnimationScene.html#details) [vtkAnimationCue](http://www.vtk.org/doc/nightly/html/classvtkAnimationCue.html#details)|Animate actors.
[Animation](/Cxx/Utilities/Animation) | [vtkRenderWindowInteractor](http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html#details) | Move a sphere across a scene.
[AnimationScene](/Cxx/Utilities/AnimationScene) | [vtkAnimationScene](http://www.vtk.org/doc/nightly/html/classvtkAnimationScene.html#details) [vtkAnimationCue](http://www.vtk.org/doc/nightly/html/classvtkAnimationCue.html#details) | Animation (the right way). Zoom in on a sphere.
[DataAnimation](/Cxx/Utilities/DataAnimation) | [vtkCallbackCommand](http://www.vtk.org/doc/nightly/html/classvtkCallbackCommand.html#details) [vtkProgrammableFilter](http://www.vtk.org/doc/nightly/html/classvtkProgrammableFilter.html#details) | Data Animation. Update points in a dataset every specified interval.
[DataAnimationSubclass](/Cxx/Utilities/DataAnimationSubclass) | [vtkCommand](http://www.vtk.org/doc/nightly/html/classvtkCommand.html#details) [vtkProgrammableFilter](http://www.vtk.org/doc/nightly/html/classvtkProgrammableFilter.html#details)| Update points in a dataset every specified interval (using a [vtkCommand](http://www.vtk.org/doc/nightly/html/classvtkCommand.html#details) subclass instead of a callback function.

## Geographic Visualization (Geovis)

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[CompassWidget ](/Cxx/Geovis/CompassWidget)  | [vtkCompassWidget](http://www.vtk.org/doc/nightly/html/classvtkCompassWidget.html#details) | Compass Widget.
[EarthSource](/Cxx/Geovis/EarthSource) | [vtkEarthSource](http://www.vtk.org/doc/nightly/html/classvtkEarthSource.html#details) | Create the Earth.
[GeoAssignCoordinates](/Cxx/Geovis/GeoAssignCoordinates) | [vtkGeoAssignCoordinates](http://www.vtk.org/doc/nightly/html/classvtkGeoAssignCoordinates.html#details) | Convert lat/long coordinates to world coordinates.

## Information Visualization (Infovis)

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ParallelCoordinatesView](/Cxx/InfoVis/ParallelCoordinatesView) | [vtkParallelCoordinatesView](http://www.vtk.org/doc/nightly/html/classvtkParallelCoordinatesView.html#details) | Parallel coordinates.
[TreeMapView](/Cxx/InfoVis/TreeMapView) | [vtkTreeMapView](http://www.vtk.org/doc/nightly/html/classvtkTreeMapView.html#details) | Tree map.


## Qt
Click [here](http://www.vtk.org/Wiki/VTK/Tutorials/QtSetup) for a tutorial on how to setup Qt.


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[BorderWidgetQt](/Cxx/Qt/BorderWidgetQt) | [vtkBorderWidget](http://www.vtk.org/doc/nightly/html/classvtkBorderWidget.html#details) QApplication |
[QtBarChart](/Cxx/Qt/QtBarChart) | [vtkQtBarChart](http://www.vtk.org/doc/nightly/html/classvtkQtBarChart.html#details) |
[ShowEvent ](/Cxx/Qt/ShowEvent) |  | Use QMainWindow::showEvent event to do things that you might want to do in the constructor 
[EventQtSlotConnect](/Cxx/Qt/EventQtSlotConnect) | [vtkEventQtSlotConnect](http://www.vtk.org/doc/nightly/html/classvtkEventQtSlotConnect.html#details)|  Connect a VTK event to a Qt slot.
[ImageDataToQImage](/Cxx/Qt/ImageDataToQImage) | |  Convert a [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html#details) to a QImage.
[QImageToImageSource](/Cxx/Qt/QImageToImageSource) | [vtkQImageToImageSource](http://www.vtk.org/doc/nightly/html/classvtkQImageToImageSource.html#details) |  Convert a QImage to a [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html#details).
[RenderWindowNoUiFile](/Cxx/Qt/RenderWindowNoUiFile) | Q[VTKWidget](http://www.vtk.org/doc/nightly/html/classVTKWidget.html#details)| This is a very basic example that shows how to create a Qt window. Typically, one would want to design a form in the QtDesigner (this is shown in [[/Qt/RenderWindowUi|RenderWindowUi]]).
[RenderWindowUIMultipleInheritance](/Cxx/Qt/RenderWindowUIMultipleInheritance) | QMainWindow | Using a Q[VTKWidget](http://www.vtk.org/doc/nightly/html/classVTKWidget.html#details) with the Qt Multiple Inheritance model.
[RenderWindowUISingleInheritance](/Cxx/Qt/RenderWindowUISingleInheritance) | QMainWindow | Using a Q[VTKWidget](http://www.vtk.org/doc/nightly/html/classVTKWidget.html#details) with the Qt Single Inheritance model.
[ShareCameraQt](/Cxx/Qt/ShareCameraQt) | |  Share the camera between Q[VTKWidgets](http://www.vtk.org/doc/nightly/html/classVTKWidgets.html#details).
[SideBySideRenderWindowsQt](/Cxx/Qt/SideBySideRenderWindowsQt) | QApplication | Side by side render windows.


## Matlab
You must turn on VTK_USE_MATLAB_MEX to use these.

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[MatlabEngineFilter](/Cxx/Matlab/MatlabEngineFilter)  | [vtkMatlabEngineFilter](http://www.vtk.org/doc/nightly/html/classvtkMatlabEngineFilter.html#details) |


## Databases
### SQL
If you have any trouble or errors with the following examples, please troubleshoot using [these instructions](http://www.vtk.org/Wiki/Tutorials/SQLSetup).


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ConnectAndRead](/Cxx/Databases/SQL/MySQL/ConnectAndRead) | [vtkMySQLDatabase](http://www.vtk.org/doc/nightly/html/classvtkMySQLDatabase.html#details) [vtkSQLQuery](http://www.vtk.org/doc/nightly/html/classvtkSQLQuery.html#details) |Connect to and read a MySQL database.
[CreateDatabase](/Cxx/Databases/SQL/MySQL/CreateDatabase) | [vtkMySQLDatabase](http://www.vtk.org/doc/nightly/html/classvtkMySQLDatabase.html#details) | Create a MySQL database.
[WriteToDatabase](/Cxx/Databases/SQL/MySQL/WriteToDatabase) | [vtkSQLQuery](http://www.vtk.org/doc/nightly/html/classvtkSQLQuery.html#details) [vtkMySQLDatabase](http://www.vtk.org/doc/nightly/html/classvtkMySQLDatabase.html#details) |  Write to a MySQL database.


## RenderMan
RenderMan is a high quality rendering system created by [Pixar](https://renderman.pixar.com/view/renderman). VTK can export RenderMan RIB files for rendering by [prman](http://renderman.pixar.com/view/renderman-prman-the-rispec-and-renderman-studio). In the spring of 2015, Pixar released a [non-commercial version](http://renderman.pixar.com/view/PR-NCR) of its RenderMan products.

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[PolyDataRIB](/Cxx/RenderMan/PolyDataRIB) | [vtkRIBExporter](http://www.vtk.org/doc/nightly/html/classvtkRIBExporter.html#details)|Apply a RenderMan Shader to a PolyData.

## Remote Modules
Remote modules are user contributed code that is not distributed with VTK. A description of a remote module and the location of its repository is listed in the VTK/Remote directory with the extension .remote.cmake. Once enabled, a remote module is treated like any other VTK module. Each of the remote module examples describes how to enable the example. More information about remote modules is [here](http://www.vtk.org/Wiki/VTK/Remote_Modules).

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[FrenetSerretFrame](/Cxx/Remote/FrenetSerretFrame) | [vtkFrenetSerretFrame](http://www.vtk.org/doc/nightly/html/classvtkFrenetSerretFrame.html#details) | Compute tangent and normal vectors to a polyline.
[FrenetSerretFrameDemo](/Cxx/Remote/FrenetSerretFrameDemo) | [vtkFrenetSerretFrame](http://www.vtk.org/doc/nightly/html/classvtkFrenetSerretFrame.html#details) | Uses [vtkSplineWidget](http://www.vtk.org/doc/nightly/html/classvtkSplineWidget.html#details) to interact with a spline. Shows how to control a pipeline inside a callback.
