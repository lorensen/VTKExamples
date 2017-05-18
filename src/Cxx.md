These are fully independent, compilable examples. There is significant overlap in the examples, but they are each intended to illustrate a different concept and be fully stand alone compilable.

Please add examples in your areas of expertise!

[TOC]

#Hello World

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[A hello world example](/Cxx/Rendering/CylinderRenderingProperties)  | [vtkPolyDataMapper](http://www.vtk.org/doc/nightly/html/classvtkPolyDataMapper.html) [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html) [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html) [vtkRenderWindow](http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html) [vtkRenderWindowInteractor](http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html)| Cylinder example from the VTK Textbook and source code.

#Simple Operations

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[DistanceBetweenPoints](/Cxx/SimpleOperations/DistanceBetweenPoints)   | [vtkMath](http://www.vtk.org/doc/nightly/html/classvtkMath.html)| Distance between two points.
[DistancePointToLine](/Cxx/SimpleOperations/DistancePointToLine)   | [vtkLine](http://www.vtk.org/doc/nightly/html/classvtkLine.html) |Distance between a point and a line.
[FloatingPointExceptions](/Cxx/SimpleOperations/FloatingPointExceptions) | [vtkFloatingPointExceptions](http://www.vtk.org/doc/nightly/html/classvtkFloatingPointExceptions.html) | Floating Point Exceptions
[GaussianRandomNumber](/Cxx/SimpleOperations/GaussianRandomNumber)  | [vtkMath](http://www.vtk.org/doc/nightly/html/classvtkMath.html) | Generates Gaussian random numbers.
[UniformRandomNumber](/Cxx/SimpleOperations/UniformRandomNumber)   | [vtkMath](http://www.vtk.org/doc/nightly/html/classvtkMath.html) | Generates uniform random numbers.
[RandomSequence](/Cxx/SimpleOperations/RandomSequence) | [vtkMinimalStandardRandomSequence](http://www.vtk.org/doc/nightly/html/classvtkMinimalStandardRandomSequence.html) | This is the preferred way to generate random numbers.
[ProjectPointPlane](/Cxx/SimpleOperations/ProjectPointPlane) | [vtkPlane](http://www.vtk.org/doc/nightly/html/classvtkPlane.html) | Project a point onto a plane.
[PerspectiveTransform](/Cxx/SimpleOperations/PerspectiveTransform) | [vtkPerspectiveTransform](http://www.vtk.org/doc/nightly/html/classvtkPerspectiveTransform.html) |Apply a perspective transformation to a point.


#Input and Output
##Graph Formats

##3D File Formats

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[ConvertFile](/Cxx/IO/ConvertFile)   |  |Convert a file from one type to another
[XGMLReader](/Cxx/InfoVis/XGMLReader)   | [vtkXGMLReader](http://www.vtk.org/doc/nightly/html/classvtkXGMLReader.html) |Read a .gml file


###Standard Formats
####Input

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[DEMReader](/Cxx/IO/DEMReader)   | [vtkDEMReader](http://www.vtk.org/doc/nightly/html/classvtkDEMReader.html) | Read DEM (elevation map) files
[DumpXMLFile](/Cxx/IO/DumpXMLFile) | [vtkDataSetReader](http://www.vtk.org/doc/nightly/html/classvtkDataSetReader.html) |Report the contents of a VTK XML or legacy file
[IndividualVRML](/Cxx/IO/IndividualVRML) | [vtkVRMLImporter](http://www.vtk.org/doc/nightly/html/classvtkVRMLImporter.html) | This example is used to get each actor and object from a scene and verify axes correspondence 
[ParticleReader](/Cxx/IO/ParticleReader) | [vtkParticleReader](http://www.vtk.org/doc/nightly/html/classvtkParticleReader.html) | This example reads ascii files where each line consists of points with its position (x,y,z) and (optionally) one scalar or binary files in RAW 3d file format.
[ReadDICOMSeries](/Cxx/IO/ReadDICOMSeries)   | [vtkDICOMImageReader](http://www.vtk.org/doc/nightly/html/classvtkDICOMImageReader.html) | This example demonstrates how to read a series of DICOM images and scroll through slices
[ReadDICOM](/Cxx/IO/ReadDICOM)   | [vtkDICOMImageReader](http://www.vtk.org/doc/nightly/html/classvtkDICOMImageReader.html) |Read DICOM file
[ReadDelimitedFile](/Cxx/InfoVis/ReadDelimitedFile)   | [vtkDelimitedTextReader](http://www.vtk.org/doc/nightly/html/classvtkDelimitedTextReader.html) |Read a delimited file into a polydata.
[ReadOBJ](/Cxx/IO/ReadOBJ)   | [vtkOBJReader](http://www.vtk.org/doc/nightly/html/classvtkOBJReader.html) |Read an OBJ (.obj) file.
[ReadPDB](/Cxx/IO/ReadPDB)   | [vtkPDBReader](http://www.vtk.org/doc/nightly/html/classvtkPDBReader.html) | Read Protein Data Bank Files.
[ReadPLOT3D](/Cxx/IO/ReadPLOT3D)   | [vtkPLOT3DReader](http://www.vtk.org/doc/nightly/html/classvtkPLOT3DReader.html) | Read CFD (computational fluid dynamics) data produced by PLOT3D.
[ReadPLY](/Cxx/IO/ReadPLY)   | [vtkPLYReader](http://www.vtk.org/doc/nightly/html/classvtkPLYReader.html) |Read PLY (.ply) files
[ReadPlainTextTriangles](/Cxx/IO/ReadPlainTextTriangles)   | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html) [vtkSmartPointer](http://www.vtk.org/doc/nightly/html/classvtkSmartPointer.html) [vtkPoints](http://www.vtk.org/doc/nightly/html/classvtkPoints.html) [vtkCellArray](http://www.vtk.org/doc/nightly/html/classvtkCellArray.html) [vtkXMLPolyDataWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLPolyDataWriter.html) | Read a plain text file into a polydata.
[ReadPlainText](/Cxx/IO/ReadPlainText)   | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html) | Read a plain text file into a polydata.
[ReadSTL](/Cxx/IO/ReadSTL)   | [vtkSTLReader](http://www.vtk.org/doc/nightly/html/classvtkSTLReader.html) |Read stereo lithography STL (.stl) files
[SimplePointsReader ](/Cxx/IO/SimplePointsReader)  | [vtkSimplePointsReader](http://www.vtk.org/doc/nightly/html/classvtkSimplePointsReader.html) |Read a simple "xyz" file of points.
[VRML](/Cxx/IO/VRML) | [vtkVRMLImporter](http://www.vtk.org/doc/nightly/html/classvtkVRMLImporter.html) |Read a VRML (WRL) file.


####Output

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[DelimitedTextWriter](/Cxx/InfoVis/DelimitedTextWriter)   | [vtkDelimitedTextWriter](http://www.vtk.org/doc/nightly/html/classvtkDelimitedTextWriter.html) |Write data to a delimited file
[SimplePointsWriter](/Cxx/IO/SimplePointsWriter)   | [vtkSimplePointsWriter](http://www.vtk.org/doc/nightly/html/classvtkSimplePointsWriter.html) |Write a simple ".xyz" file
[WritePLY](/Cxx/IO/WritePLY)   | [vtkPLYWriter](http://www.vtk.org/doc/nightly/html/classvtkPLYWriter.html) | Write PLY (.ply) files
[WriteSTL](/Cxx/IO/WriteSTL)   | [vtkSTLWriter](http://www.vtk.org/doc/nightly/html/classvtkSTLWriter.html) |Write stereo lithography STL (.stl) files


###VTK Formats
####Input


| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[ReadImageData](/Cxx/IO/ReadImageData) | [vtkXMLImageDataReader](http://www.vtk.org/doc/nightly/html/classvtkXMLImageDataReader.html) |Read a image data (.vti) file
[ReadPolyData](/Cxx/IO/ReadPolyData) | [vtkXMLPolyDataReader](http://www.vtk.org/doc/nightly/html/classvtkXMLPolyDataReader.html) |Read a polygonal data (.vtp) file
[ReadRectilinearGrid](/Cxx/IO/ReadRectilinearGrid) | [vtkXMLRectilinearGridReader](http://www.vtk.org/doc/nightly/html/classvtkXMLRectilinearGridReader.html) |Read a rectilinear grid (.vtr) file
[ReadStructuredGrid](/Cxx/IO/ReadStructuredGrid) | [vtkXMLStructuredGridReader](http://www.vtk.org/doc/nightly/html/classvtkXMLStructuredGridReader.html) |Read a structured grid (.vts) file
[ReadUnknownTypeXMLFile](/Cxx/IO/ReadUnknownTypeXMLFile) | [vtkXMLGenericDataObjectReader](http://www.vtk.org/doc/nightly/html/classvtkXMLGenericDataObjectReader.html) |Read an XML file and later decide what kind it is
[ReadUnstructuredGrid](/Cxx/IO/ReadUnstructuredGrid) | [vtkXMLUnstructuredGridReader](http://www.vtk.org/doc/nightly/html/classvtkXMLUnstructuredGridReader.html) |Read an unstructured grid (.vtu) file


####Output


| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[Write an ExodusII file](/Cxx/Parallel/ExodusIIWriter)   | [vtkExodusIIWriter](http://www.vtk.org/doc/nightly/html/classvtkExodusIIWriter.html) | Write a time varying ExodusII file.
[Write an image file to parallel files](/Cxx/IO/XMLPImageDataWriter) | [vtkXMLPImageDataWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLPImageDataWriter.html) | Write a .pvti file with 4 .vti pieces.
[Write an unstructured grid to parallel files](/Cxx/IO/XMLPUnstructuredGridWriter) | [vtkXMLPUnstructuredGridWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLPUnstructuredGridWriter.html) | Write a .pvtu with 4 .vtu pieces.
[WriteVTI](/Cxx/IO/WriteVTI) | [vtkXMLImageDataWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLImageDataWriter.html) | Write a .vti file. VTI is an "ImageData".
[WriteVTP](/Cxx/IO/WriteVTP) | [vtkXMLPolyDataWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLPolyDataWriter.html) | Write a .vtp file. VTP is a "PolyData". This format allows for the most complex geometric objects to be stored.
[WriteVTU](/Cxx/IO/WriteVTU) | [vtkXMLUnstructuredGridWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLUnstructuredGridWriter.html) | Write a .vtu file. VTU is an "Unstructured Grid". This format allows for 3D data to be stored.
[XMLStructuredGridWriter](/Cxx/IO/XMLStructuredGridWriter) | [vtkXMLStructuredGridWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLStructuredGridWriter.html) | Write a .vts file from a [vtkStructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkStructuredGrid.html).

###Legacy VTK Formats


| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[GenericDataObjectReader](/Cxx/IO/GenericDataObjectReader) | [vtkGenericDataObjectReader](http://www.vtk.org/doc/nightly/html/classvtkGenericDataObjectReader.html) |Read any type of legacy .vtk file.
[StructuredGridReader](/Cxx/IO/StructuredGridReader) | [vtkStructuredGridReader](http://www.vtk.org/doc/nightly/html/classvtkStructuredGridReader.html) |Read a structured grid (.vtk) file.
[StructuredPointsReader](/Cxx/IO/StructuredPointsReader)   | [vtkStructuredPointsReader](http://www.vtk.org/doc/nightly/html/classvtkStructuredPointsReader.html) |Read a structured points (.vtk) file.


##Image Format

###Input

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[ImageReader2Factory](/Cxx/IO/ImageReader2Factory) | [vtkImageReader2Factory](http://www.vtk.org/doc/nightly/html/classvtkImageReader2Factory.html) | This class tries to find an appropriate reader. It is very convenient to use this when you don't know what kind of file to expect.
[JPEGReader](/Cxx/IO/JPEGReader) |[vtkJPEGReader](http://www.vtk.org/doc/nightly/html/classvtkJPEGReader.html)|Read a JPG image.
[MetaImageReader](/Cxx/IO/MetaImageReader) | [vtkMetaImageReader](http://www.vtk.org/doc/nightly/html/classvtkMetaImageReader.html) |Read .mha files.
[PNGReader](/Cxx/IO/PNGReader) | [vtkPNGReader](http://www.vtk.org/doc/nightly/html/classvtkPNGReader.html)|Read a PNG image.
[ReadBMP](/Cxx/IO/ReadBMP) |[vtkBMPReader](http://www.vtk.org/doc/nightly/html/classvtkBMPReader.html) | Read BMP (.bmp) files.
[ReadPNM](/Cxx/IO/ReadPNM) | [vtkPNMReader](http://www.vtk.org/doc/nightly/html/classvtkPNMReader.html) |Read PNM (.pnm) files.
[ReadTIFF](/Cxx/IO/ReadTIFF) | [vtkTIFFReader](http://www.vtk.org/doc/nightly/html/classvtkTIFFReader.html) |Read TIFF (.tif) files.

###Output


| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[JPEGWriter](/Cxx/IO/JPEGWriter)   | [vtkJPEGWriter](http://www.vtk.org/doc/nightly/html/classvtkJPEGWriter.html) |Write a JPEG (.jpg) file.
[MetaImageWriter](/Cxx/IO/MetaImageWriter)   | [vtkMetaImageWriter](http://www.vtk.org/doc/nightly/html/classvtkMetaImageWriter.html) |Write a .mha/.mhd + .raw file.
[WriteBMP](/Cxx/IO/WriteBMP)   | [vtkBMPWriter](http://www.vtk.org/doc/nightly/html/classvtkBMPWriter.html) |Write a BMP (.bmp) file.
[WritePNG](/Cxx/IO/WritePNG)   | [vtkPNGWriter](http://www.vtk.org/doc/nightly/html/classvtkPNGWriter.html) |Write a PNG (.png) file.
[WritePNM](/Cxx/IO/WritePNM)   | [vtkPNMWriter](http://www.vtk.org/doc/nightly/html/classvtkPNMWriter.html) |Write a PNM (.pnm) file.
[WriteTIFF](/Cxx/IO/WriteTIFF)   | [vtkTIFFWriter](http://www.vtk.org/doc/nightly/html/classvtkTIFFWriter.html) |Write a TIFF (.tif) file.


#Geometric Objects

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[Arrow](/Cxx/GeometricObjects/Arrow) | [vtkArrowSource](http://www.vtk.org/doc/nightly/html/classvtkArrowSource.html) |
[Axes](/Cxx/GeometricObjects/Axes)  | [vtkAxesActor](http://www.vtk.org/doc/nightly/html/classvtkAxesActor.html) |
[Cell3DDemonstration](/Cxx/GeometricObjects/Cell3DDemonstration) | [vtkHexagonalPrism](http://www.vtk.org/doc/nightly/html/classvtkHexagonalPrism.html) [vtkHexahedron](http://www.vtk.org/doc/nightly/html/classvtkHexahedron.html) [vtkPentagonalPrism](http://www.vtk.org/doc/nightly/html/classvtkPentagonalPrism.html)  [vtkPolyhedron](http://www.vtk.org/doc/nightly/html/classvtkPolyhedron.html) [vtkPyramid](http://www.vtk.org/doc/nightly/html/classvtkPyramid.html) [vtkTetra](http://www.vtk.org/doc/nightly/html/classvtkTetra.html) [vtkVoxel](http://www.vtk.org/doc/nightly/html/classvtkVoxel.html) [vtkWedge](http://www.vtk.org/doc/nightly/html/classvtkWedge.html) [vtkUnstructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html) |  Demonstrate the use of [vtkCell3D](http://www.vtk.org/doc/nightly/html/classvtkCell3D.html) to construct geometric objects. Sample objects are generated from the classes derived from [vtkCell3D](http://www.vtk.org/doc/nightly/html/classvtkCell3D.html) and displayed.
[Colored Lines](/Cxx/GeometricObjects/ColoredLines)   | [vtkCellData](http://www.vtk.org/doc/nightly/html/classvtkCellData.html) [vtkLine](http://www.vtk.org/doc/nightly/html/classvtkLine.html) |
[Cone](/Cxx/GeometricObjects/Cone)   | [vtkConeSource](http://www.vtk.org/doc/nightly/html/classvtkConeSource.html) |
[Cube](/Cxx/GeometricObjects/Cube)   | [vtkCubeSource](http://www.vtk.org/doc/nightly/html/classvtkCubeSource.html) |
[Cylinder](/Cxx/GeometricObjects/Cylinder)   | [vtkCylinderSource](http://www.vtk.org/doc/nightly/html/classvtkCylinderSource.html) |
[Disk](/Cxx/GeometricObjects/Disk)   | [vtkDiskSource](http://www.vtk.org/doc/nightly/html/classvtkDiskSource.html) | A circle with a hole in it.
[Dodecahedron](/Cxx/GeometricObjects/Dodecahedron)   | [vtkPolyhedron](http://www.vtk.org/doc/nightly/html/classvtkPolyhedron.html) | Create a dodecahedron using [vtkPolyhedron](http://www.vtk.org/doc/nightly/html/classvtkPolyhedron.html)
[Frustum](/Cxx/GeometricObjects/Frustum)   | [vtkFrustumSource](http://www.vtk.org/doc/nightly/html/classvtkFrustumSource.html) |
[GeometricObjectsDemo](/Cxx/GeometricObjects/GeometricObjectsDemo) |  | A demonstration of all geometric objects that work the same way.
[Hexahedron](/Cxx/GeometricObjects/Hexahedron)  | [vtkHexahedron](http://www.vtk.org/doc/nightly/html/classvtkHexahedron.html) |
[Line](/Cxx/GeometricObjects/Line)   | [vtkLineSource](http://www.vtk.org/doc/nightly/html/classvtkLineSource.html) |
[LongLine](/Cxx/GeometricObjects/LongLine) | [vtkLine](http://www.vtk.org/doc/nightly/html/classvtkLine.html) | Manually create a polyline
[Oriented Arrow](/Cxx/GeometricObjects/OrientedArrow)   | [vtkArrowSource](http://www.vtk.org/doc/nightly/html/classvtkArrowSource.html) | Orient an arrow along an arbitrary vector
[Oriented Cylinder](/Cxx/GeometricObjects/OrientedCylinder)   | [vtkCylinderSource](http://www.vtk.org/doc/nightly/html/classvtkCylinderSource.html) | Orient a cylinder along an arbitrary vector
[Plane](/Cxx/GeometricObjects/Plane)  | [vtkPlaneSource](http://www.vtk.org/doc/nightly/html/classvtkPlaneSource.html) |
[PlanesIntersection](/Cxx/GeometricObjects/PlanesIntersection)  | [vtkPlanesIntersection](http://www.vtk.org/doc/nightly/html/classvtkPlanesIntersection.html) |
[Planes](/Cxx/GeometricObjects/Planes)  | [vtkPlanes](http://www.vtk.org/doc/nightly/html/classvtkPlanes.html) |
[PlatonicSolid](/Cxx/GeometricObjects/PlatonicSolid)   | [vtkPlatonicSolidSource](http://www.vtk.org/doc/nightly/html/classvtkPlatonicSolidSource.html) |
[Point](/Cxx/GeometricObjects/Point)   | [vtkPoints](http://www.vtk.org/doc/nightly/html/classvtkPoints.html) |
[PolyLine](/Cxx/GeometricObjects/PolyLine)   | [vtkPolyLine](http://www.vtk.org/doc/nightly/html/classvtkPolyLine.html) |
[PolygonIntersection](/Cxx/GeometricObjects/PolygonIntersection) | [vtkPolygon](http://www.vtk.org/doc/nightly/html/classvtkPolygon.html) |  Compute the intersection of a line segment with a polygon.
[Polygon](/Cxx/GeometricObjects/Polygon)   | [vtkPolygon](http://www.vtk.org/doc/nightly/html/classvtkPolygon.html) |
[Polyhedron](/Cxx/GeometricObjects/Polyhedron)   | [vtkPolyhedron](http://www.vtk.org/doc/nightly/html/classvtkPolyhedron.html) |
[Pyramid](/Cxx/GeometricObjects/Pyramid)   | [vtkPyramid](http://www.vtk.org/doc/nightly/html/classvtkPyramid.html) |
[Quad](/Cxx/GeometricObjects/Quad)   | [vtkQuad](http://www.vtk.org/doc/nightly/html/classvtkQuad.html) |
[Regular Polygon](/Cxx/GeometricObjects/RegularPolygonSource)   | [vtkRegularPolygonSource](http://www.vtk.org/doc/nightly/html/classvtkRegularPolygonSource.html) |
[Sphere](/Cxx/GeometricObjects/Sphere)   | [vtkSphereSource](http://www.vtk.org/doc/nightly/html/classvtkSphereSource.html) |
[Tetrahedron](/Cxx/GeometricObjects/Tetrahedron)   | [vtkTetra](http://www.vtk.org/doc/nightly/html/classvtkTetra.html) |
[Triangle strip](/Cxx/GeometricObjects/TriangleStrip) | [vtkTriangleStrip](http://www.vtk.org/doc/nightly/html/classvtkTriangleStrip.html) | 
[Triangle](/Cxx/GeometricObjects/Triangle)   | [vtkTriangle](http://www.vtk.org/doc/nightly/html/classvtkTriangle.html) |
[Vertex](/Cxx/GeometricObjects/Vertex)   | [vtkVertex](http://www.vtk.org/doc/nightly/html/classvtkVertex.html) |


##Parametric Objects

These examples demonstrate how to create an display one of the many [vtkParametric](http://www.vtk.org/doc/nightly/html/classvtkParametric.html) objects. All of the classes listed can be used in an identical fashion.


| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[ParametricObjects](/Cxx/GeometricObjects/ParametricObjects)   |  | Create and display a parametric object. Uncomment the object that you wish to be displayed.
[ParametricObjectsDemo](/Cxx/GeometricObjects/ParametricObjectsDemo)   | [vtkParametricBoy](http://www.vtk.org/doc/nightly/html/classvtkParametricBoy.html), [vtkParametricConicSpiral](http://www.vtk.org/doc/nightly/html/classvtkParametricConicSpiral.html), [vtkParametricCrossCap](http://www.vtk.org/doc/nightly/html/classvtkParametricCrossCap.html), [vtkParametricDini](http://www.vtk.org/doc/nightly/html/classvtkParametricDini.html), [vtkParametricEllipsoid](http://www.vtk.org/doc/nightly/html/classvtkParametricEllipsoid.html), [vtkParametricEnneper](http://www.vtk.org/doc/nightly/html/classvtkParametricEnneper.html), [vtkParametricFigure8Klein](http://www.vtk.org/doc/nightly/html/classvtkParametricFigure8Klein.html), [vtkParametricKlein](http://www.vtk.org/doc/nightly/html/classvtkParametricKlein.html), [vtkParametricMobius](http://www.vtk.org/doc/nightly/html/classvtkParametricMobius.html), [vtkParametricRandomHills](http://www.vtk.org/doc/nightly/html/classvtkParametricRandomHills.html), [vtkParametricRoman](http://www.vtk.org/doc/nightly/html/classvtkParametricRoman.html), [vtkParametricSpline](http://www.vtk.org/doc/nightly/html/classvtkParametricSpline.html), [vtkParametricSuperEllipsoid](http://www.vtk.org/doc/nightly/html/classvtkParametricSuperEllipsoid.html), [vtkParametricSuperToroid](http://www.vtk.org/doc/nightly/html/classvtkParametricSuperToroid.html), [vtkParametricTorus](http://www.vtk.org/doc/nightly/html/classvtkParametricTorus.html) | Demonstration of of the [vtkParametric](http://www.vtk.org/doc/nightly/html/classvtkParametric.html)* classes added by Andrew Maclean. All the objects are displayed in a 4X4 array.
[ParametricObjectsDemo2](/Cxx/GeometricObjects/ParametricObjectsDemo2)   | [vtkParametricBohemianDome](http://www.vtk.org/doc/nightly/html/classvtkParametricBohemianDome.html), [vtkParametricBour](http://www.vtk.org/doc/nightly/html/classvtkParametricBour.html), [vtkParametricCatalanMinimal](http://www.vtk.org/doc/nightly/html/classvtkParametricCatalanMinimal.html), [vtkParametricHenneberg](http://www.vtk.org/doc/nightly/html/classvtkParametricHenneberg.html), [vtkParametricKuen](http://www.vtk.org/doc/nightly/html/classvtkParametricKuen.html), [vtkParametricPluckerConoid](http://www.vtk.org/doc/nightly/html/classvtkParametricPluckerConoid.html), [vtkParametricPseudosphere](http://www.vtk.org/doc/nightly/html/classvtkParametricPseudosphere.html) | Demonstration of additional vtkParametric* classes added by  Tim Meehan. All the objects are displayed in a 4X2 array.
[ParametricKuenDemo](/Cxx/GeometricObjects/ParametricKuenDemo)|[vtkParametricKuen](http://www.vtk.org/doc/nightly/html/classvtkParametricKuen.html)|Interactively change the parameters for a Kuen Surface.
[ParametricSuperEllipsoidDemo](/Cxx/GeometricObjects/ParametricSuperEllipsoidDemo) | [vtkParametricSuperEllipsoid](http://www.vtk.org/doc/nightly/html/classvtkParametricSuperEllipsoid.html) | Interactively change the parameters for a SuperEllipsoid Surface.
[ParametricSuperToroidDemo](/Cxx/GeometricObjects/ParametricSuperToroidDemo)   | [vtkParametricSuperToroid](http://www.vtk.org/doc/nightly/html/classvtkParametricSuperToroid.html)| Interactively change the parameters for a SuperToroid Surface.

#Implicit Functions and Iso-surfaces


| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[BandedPolyDataContourFilter](/Cxx/VisualizationAlgorithms/BandedPolyDataContourFilter) | [vtkBandedPolyDataContourFilter](http://www.vtk.org/doc/nightly/html/classvtkBandedPolyDataContourFilter.html) | Create filled contours.
[ContourTriangulator](/Cxx/Modelling/ContourTriangulator) | [vtkMarchingSquares](http://www.vtk.org/doc/nightly/html/classvtkMarchingSquares.html) [vtkContourTriangulator](http://www.vtk.org/doc/nightly/html/classvtkContourTriangulator.html) | Create a contour from a structured point set (image) and triangulate it.
[CutWithCutFunction](/Cxx/VisualizationAlgorithms/CutWithCutFunction) | [vtkCutter](http://www.vtk.org/doc/nightly/html/classvtkCutter.html) | Cut a surface with an implicit plane using [vtkCutter](http://www.vtk.org/doc/nightly/html/classvtkCutter.html).
[CutWithScalars](/Cxx/VisualizationAlgorithms/CutWithScalars) | [vtkContourFilter](http://www.vtk.org/doc/nightly/html/classvtkContourFilter.html) | Cut a surface with scalars.
[ExtractLargestIsosurface](/Cxx/Modelling/ExtractLargestIsosurface) | [vtkPolyDataConnectivityFilter](http://www.vtk.org/doc/nightly/html/classvtkPolyDataConnectivityFilter.html) | Extract largest isosurface.
[FilledContours](/Cxx/VisualizationAlgorithms/FilledContours) | [vtkContourFilter](http://www.vtk.org/doc/nightly/html/classvtkContourFilter.html) |Create filled contours (using [vtkClipPolyData](http://www.vtk.org/doc/nightly/html/classvtkClipPolyData.html)).
[ImplicitDataSet](/ImplicitFunctions/ImplicitDataSet) | [vtkImplicitDataSet](http://www.vtk.org/doc/nightly/html/classvtkImplicitDataSet.html) | Convert an imagedata to an implicit function.
[ImplicitSphere](/Cxx/ImplicitFunctions/ImplicitSphere) | [vtkSphere](http://www.vtk.org/doc/nightly/html/classvtkSphere.html) | An implicit representation of a sphere.
[IsoContours](/Cxx/ImplicitFunctions/IsoContours) | [vtkContourFunction](http://www.vtk.org/doc/nightly/html/classvtkContourFunction.html) | Visualize different isocontours using a slider.
[MarchingCubes](/Cxx/Modelling/MarchingCubes) | [vtkMarchingCubes](http://www.vtk.org/doc/nightly/html/classvtkMarchingCubes.html) | Create a voxelized sphere.
[MarchingSquares](/Cxx/Modelling/MarchingSquares) | [vtkMarchingSquares](http://www.vtk.org/doc/nightly/html/classvtkMarchingSquares.html) | Create a contour from a structured point set (image).
[SampleFunction](/Cxx/ImplicitFunctions/SampleFunction) | [vtkSampleFunction](http://www.vtk.org/doc/nightly/html/classvtkSampleFunction.html) |Sample and visualize an implicit function.


#Working with 3D Data

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[AlignFrames](/Cxx/PolyData/AlignFrames) | [vtkLandmarkTransform](http://www.vtk.org/doc/nightly/html/classvtkLandmarkTransform.html) | Align coordinate frames.
[AppendFilter](/Cxx/Filters/AppendFilter) | [vtkAppendFilter](http://www.vtk.org/doc/nightly/html/classvtkAppendFilter.html) | Append different types of data,
[BooleanOperationPolyDataFilter](/Cxx/PolyData/BooleanOperationPolyDataFilter) | [vtkBooleanOperationPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkBooleanOperationPolyDataFilter.html)|Perform boolean operations on two [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html) objects.
[CellCenters](/Cxx/PolyData/CellCenters) | [vtkCellCenters](http://www.vtk.org/doc/nightly/html/classvtkCellCenters.html) |Compute points at the center of every cell.
[CellEdgeNeighbors](/Cxx/PolyData/CellEdgeNeighbors) | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html)::GetCellNeighbors |Determine which cells share an edge with a specific cell.
[CellPointNeighbors](/Cxx/PolyData/CellPointNeighbors) | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html)::GetCellNeighbors | Determine which cells share a single point with a specific cell.
[CenterOfMass](/Cxx/PolyData/CenterOfMass) | [vtkCenterOfMass](http://www.vtk.org/doc/nightly/html/classvtkCenterOfMass.html)|Compute the center of mass of the points.
[Circle](/Cxx/GeometricObjects/Circle) | [vtkCutter](http://www.vtk.org/doc/nightly/html/classvtkCutter.html) | Create a circle by cutting through a sphere.
[CleanPolyData](/Cxx/PolyData/CleanPolyData) | [vtkCleanPolyData](http://www.vtk.org/doc/nightly/html/classvtkCleanPolyData.html) |Remove coincident points.
[ColorCellsWithRGB](/Cxx/PolyData/ColorCellsWithRGB) |[vtkCellData](http://www.vtk.org/doc/nightly/html/classvtkCellData.html) | Color individual cells of a polydata with rgb colors.
[ColorCells](/Cxx/PolyData/ColorCells) | [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html) | Color individual cells of a polydata with scalar index.
[Colored Points](/Cxx/PolyData/ColoredPoints) | [vtkUnsignedCharArray](http://www.vtk.org/doc/nightly/html/classvtkUnsignedCharArray.html) | Add three points to a polydata and associate a color with each of them.
[CombinePolydata](/Cxx/Filters/CombinePolydata) | [vtkAppendPolyData](http://www.vtk.org/doc/nightly/html/classvtkAppendPolyData.html) | Combine/Append PolyData.
[ConnectivityFilter](/Cxx/Filters/ConnectivityFilter) | [vtkConnectivityFilter](http://www.vtk.org/doc/nightly/html/classvtkConnectivityFilter.html) | Color any dataset type based on connectivity.
[ContoursFromPolyData](/Cxx/Filtering/ContoursFromPolyData) | [vtkCutter](http://www.vtk.org/doc/nightly/html/classvtkCutter.html) | Create contours from PolyData.
[ContoursToSurface](/Cxx/PolyData/ContoursToSurface) | [vtkVoxelContoursToSurfaceFilter](http://www.vtk.org/doc/nightly/html/classvtkVoxelContoursToSurfaceFilter.html) | Convert contours to a surface.
[ConvexHull_ShrinkWrap](/Cxx/PolyData/ConvexHull_ShrinkWrap) | [vtkSmoothPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkSmoothPolyDataFilter.html) | Convex hull using shrink wrapping.
[ConvexHull_vtkHull](/Cxx/PolyData/ConvexHull_vtkHull) | [vtkHull](http://www.vtk.org/doc/nightly/html/classvtkHull.html) |Convex hull using [vtkHull](http://www.vtk.org/doc/nightly/html/classvtkHull.html).
[CopyAllArrays](/Cxx/PolyData/CopyAllArrays)| [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html) |Copy all arrays from one [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html) to another.
[Data Bounds](/Cxx/PolyData/DataBounds) | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html)::GetBounds | Get the minimum and maximum value in each dimension. (Axis aligned bounding box)
[DataSetSurfaceFilter](/Cxx/PolyData/DataSetSurfaceFilter) | [vtkDataSetSurfaceFilter](http://www.vtk.org/doc/nightly/html/classvtkDataSetSurfaceFilter.html) |Convert [vtkUnstructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html) to [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html).
[DecimatePolyline](/Cxx/PolyData/DecimatePolyline) | [vtkDecimatePolylineFilter](http://www.vtk.org/doc/nightly/html/classvtkDecimatePolylineFilter.html) |Decimate polyline.
[Delete cells](/Cxx/Broken/PolyData/DeleteCells) | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html) | Delete a cell from a [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html)
[DeletePoint](/Cxx/PolyData/DeletePoint) | [vtkPoints](http://www.vtk.org/doc/nightly/html/classvtkPoints.html), [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html) |
[DetermineArrayDataTypes](/Cxx/PolyData/DetermineArrayDataTypes)| [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html) |Determine data types of arrays.
[DistancePolyDataFilter](/Cxx/PolyData/DistancePolyDataFilter) | [vtkDistancePolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkDistancePolyDataFilter.html)|Compute the distance function from one [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html) to another.
[EmbedPointsIntoVolume](/Cxx/PolyData/EmbedPointsIntoVolume)| [vtkGaussianSplatter](http://www.vtk.org/doc/nightly/html/classvtkGaussianSplatter.html) |Embed points into a volume.
[ExternalContour](/Cxx/PolyData/ExternalContour) | [vtkWindowToImageFilter](http://www.vtk.org/doc/nightly/html/classvtkWindowToImageFilter.html), [vtkContourFilter](http://www.vtk.org/doc/nightly/html/classvtkContourFilter.html) |Get the External Contour from Polydata.
[ExtractCellsUsingPoints](/Cxx/PolyData/ExtractCellsUsingPoints) | [vtkExtractSelection](http://www.vtk.org/doc/nightly/html/classvtkExtractSelection.html), [vtkSelection](http://www.vtk.org/doc/nightly/html/classvtkSelection.html), [vtkSelectionNode](http://www.vtk.org/doc/nightly/html/classvtkSelectionNode.html) |Extract points but bring cells that are still complete with them.
[ExtractOutsideSurface](/Cxx/PolyData/ExtractOutsideSurface) | [vtkPolyDataConnectivityFilter](http://www.vtk.org/doc/nightly/html/classvtkPolyDataConnectivityFilter.html) | Extract the outer surface of a multiple surface polydata.
[ExtractPolyLinesFromPolyData](/Cxx/PolyData/ExtractPolyLinesFromPolyData) | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html) |Extract polylines from polydata.
[ExtractSelectedIds](/Cxx/PolyData/ExtractSelectedIds) | [vtkExtractSelectedIds](http://www.vtk.org/doc/nightly/html/classvtkExtractSelectedIds.html) | Extract selected points.
[ExtractSelectionCells](/Cxx/PolyData/ExtractSelectionCells) | [vtkExtractSelection](http://www.vtk.org/doc/nightly/html/classvtkExtractSelection.html) | Extract selection cells.
[ExtractSelectionOriginalId](/Cxx/PolyData/ExtractSelectionOriginalId) | [vtkExtractSelection](http://www.vtk.org/doc/nightly/html/classvtkExtractSelection.html) |Extract selection and find correspondence between new and original Id.
[ExtractSelection](/Cxx/PolyData/ExtractSelection) | [vtkExtractSelection](http://www.vtk.org/doc/nightly/html/classvtkExtractSelection.html) |Extract selection points.
[ExtractVisibleCells](/Cxx/Filtering/ExtractVisibleCells) | [vtkHardwareSelector](http://www.vtk.org/doc/nightly/html/classvtkHardwareSelector.html) |Extract and highlight visible cells.
[FieldData](/Cxx/PolyData/FieldData) | [vtkFieldData](http://www.vtk.org/doc/nightly/html/classvtkFieldData.html) | Add Global Miscellaneous Data (FieldData) to a Polydata.
[FindAllArrayNames](/Cxx/IO/FindAllArrayNames) | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html) | Get the names of all of the data arrays.
[FitSplineToCutterOutput](/Cxx/PolyData/FitSplineToCutterOutput) | [vtkKochanekSpline](http://www.vtk.org/doc/nightly/html/classvtkKochanekSpline.html), [vtkSplineFilter](http://www.vtk.org/doc/nightly/html/classvtkSplineFilter.html), [vtkSpline](http://www.vtk.org/doc/nightly/html/classvtkSpline.html) |Fit a spline to cutter output.
[GeometryFilter](/Cxx/PolyData/GeometryFilter) | [vtkGeometryFilter](http://www.vtk.org/doc/nightly/html/classvtkGeometryFilter.html) |Convert [vtkUnstructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html) to [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html) (another way).
[GetMiscCellData](/Cxx/PolyData/GetMiscCellData) | [vtkCellData](http://www.vtk.org/doc/nightly/html/classvtkCellData.html) |Get Miscellaneous Data from Cells in a Polydata.
[GetMiscPointData](/Cxx/PolyData/GetMiscPointData) | [vtkDoubleArray](http://www.vtk.org/doc/nightly/html/classvtkDoubleArray.html) |Get Miscellaneous Data from Points in a Polydata.
[GradientFilter](/Cxx/PolyData/GradientFilter) | [vtkGradientFilter](http://www.vtk.org/doc/nightly/html/classvtkGradientFilter.html) |Compute the gradient of a scalar field on a data set.
[ImplicitBoolean](/Cxx/Filters/ImplicitBoolean) | [vtkImplicitBoolean](http://www.vtk.org/doc/nightly/html/classvtkImplicitBoolean.html) | Operations include intersection and union.
[ImplicitModeller](/Cxx/PolyData/ImplicitModeller) | [vtkImplicitModeller](http://www.vtk.org/doc/nightly/html/classvtkImplicitModeller.html) |Compute the distance from an object to every point on a uniform grid.
[ImplicitPolyDataDistance](/Cxx/PolyData/ImplicitPolyDataDistance) | [vtkImplicitPolyDataDistance](http://www.vtk.org/doc/nightly/html/classvtkImplicitPolyDataDistance.html)|Compute the distance function in a space around a [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html).
[InterpolateMeshOnGrid](/Cxx/PolyData/InterpolateMeshOnGrid) | [vtkProbeFilter](http://www.vtk.org/doc/nightly/html/classvtkProbeFilter.html) | Interpolate a mesh over a grid.
[InterpolateTerrain](/Cxx/PolyData/InterpolateTerrain) | [vtkProbeFilter](http://www.vtk.org/doc/nightly/html/classvtkProbeFilter.html) | [http://[vtk](http://www.vtk.org/doc/nightly/html/classvtk.html).org/Wiki/Demystifying_the_[vtkProbeFilter](http://www.vtk.org/doc/nightly/html/classvtkProbeFilter.html) Here] is a good explanation of what is going on.Interpolate terrain.
[IntersectionPolyDataFilter](/Cxx/PolyData/IntersectionPolyDataFilter) | [vtkIntersectionPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkIntersectionPolyDataFilter.html)|Compute the intersection of two [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html) objects.
[IterateOverLines](/Cxx/PolyData/IterateOverLines) | [vtkCellArray](http://www.vtk.org/doc/nightly/html/classvtkCellArray.html) | Iterate through the lines of a PolyData.
[KMeansClustering](/Cxx/InfoVis/KMeansClustering) | [vtkKMeansStatistics](http://www.vtk.org/doc/nightly/html/classvtkKMeansStatistics.html) |KMeans Clustering
[KochanekSpline](/Cxx/PolyData/KochanekSpline) | [vtkKochanekSpline](http://www.vtk.org/doc/nightly/html/classvtkKochanekSpline.html) |Create an Kochanek spline on a set of points.
[LinearExtrusion](/Cxx/PolyData/LinearExtrusion) | [vtkLinearExtrusionFilter](http://www.vtk.org/doc/nightly/html/classvtkLinearExtrusionFilter.html) | Extrude a shape.
[MaskPoints](/Cxx/PolyData/MaskPoints) | [vtkMaskPoints](http://www.vtk.org/doc/nightly/html/classvtkMaskPoints.html) |Select a subset (mask) of a point set.
[MergePoints](/Cxx/PolyData/MergePoints) | [vtkMergePoints](http://www.vtk.org/doc/nightly/html/classvtkMergePoints.html) | Remove duplicate (merge) points.
[MiscCellData](/Cxx/PolyData/MiscCellData) | [vtkCellData](http://www.vtk.org/doc/nightly/html/classvtkCellData.html) |Add Miscellaneous Data to Cells in a Polydata.
[MiscPointData](/Cxx/PolyData/MiscPointData) | [vtkPointData](http://www.vtk.org/doc/nightly/html/classvtkPointData.html), [vtkFloatArray](http://www.vtk.org/doc/nightly/html/classvtkFloatArray.html) |Add Miscellaneous Data to Points in a Polydata.
[MultiBlockMergeFilter](/Cxx/PolyData/MultiBlockMergeFilter) | [vtkMultiBlockMergeFilter](http://www.vtk.org/doc/nightly/html/classvtkMultiBlockMergeFilter.html), [vtkMultiBlockDataSet](http://www.vtk.org/doc/nightly/html/classvtkMultiBlockDataSet.html) | Combine MultiBlockDataSets.
[NullPoint](/Cxx/PolyData/NullPoint) | [vtkPointData](http://www.vtk.org/doc/nightly/html/classvtkPointData.html) | Set everything in PointData at a specified index to NULL
[Outline](/Cxx/PolyData/Outline) | [vtkOutlineFilter](http://www.vtk.org/doc/nightly/html/classvtkOutlineFilter.html) | Draw the bounding box of the data
[PKMeansClustering](/Cxx/InfoVis/PKMeansClustering) | [vtkPKMeansStatistics](http://www.vtk.org/doc/nightly/html/classvtkPKMeansStatistics.html) |Parallel KMeans Clustering.
[ParametricSpline](/Cxx/PolyData/ParametricSpline) | [vtkCardinalSpline](http://www.vtk.org/doc/nightly/html/classvtkCardinalSpline.html), [vtkParametricSpline](http://www.vtk.org/doc/nightly/html/classvtkParametricSpline.html), [vtkParametricFunctionSource](http://www.vtk.org/doc/nightly/html/classvtkParametricFunctionSource.html) |Create a Cardinal spline on a set of points.
[Perlin Noise](/Cxx/Filters/PerlinNoise) | [vtkPerlinNoise](http://www.vtk.org/doc/nightly/html/classvtkPerlinNoise.html) |
[PointCellIds](/Cxx/PolyData/PointCellIds) | [vtkIdFilter](http://www.vtk.org/doc/nightly/html/classvtkIdFilter.html) |Generate point and cell id arrays.
[PointInsideObject2](/Cxx/PolyData/PointInsideObject2) | [vtkDelaunay3D](http://www.vtk.org/doc/nightly/html/classvtkDelaunay3D.html), [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html)::FindCell | This uses a Delaunay triangulation to compute a volume. This gives more of an "is inside convex hull" effect than an "is inside object".
[PointInsideObject](/Cxx/PolyData/PointInsideObject) | [vtkSelectEnclosedPoints](http://www.vtk.org/doc/nightly/html/classvtkSelectEnclosedPoints.html) | Check if a point is inside an object.
[PointsProjectedHull](/Cxx/PolyData/PointsProjectedHull) | [vtkPointsProjectedHull](http://www.vtk.org/doc/nightly/html/classvtkPointsProjectedHull.html) |Convex hull of points projected onto the coordinate planes.
[PolyDataCellNormals](/Cxx/PolyData/PolyDataCellNormals) | [vtkCellData](http://www.vtk.org/doc/nightly/html/classvtkCellData.html) |Add/Get Normals to/from cells in a Polydata.
[PolyDataContourToImageData](/Cxx/PolyData/PolyDataContourToImageData) | [vtkLinearExtrusionFilter](http://www.vtk.org/doc/nightly/html/classvtkLinearExtrusionFilter.html),[vtkPolyDataToImageStencil](http://www.vtk.org/doc/nightly/html/classvtkPolyDataToImageStencil.html) |Generate a binarized image from a closed contour.
[PolyDataExtractNormals](/Cxx/PolyData/PolyDataExtractNormals) | [vtkPolyDataNormals](http://www.vtk.org/doc/nightly/html/classvtkPolyDataNormals.html) |Extract Normals from a Polydata.
[PolyDataGetPoint](/Cxx/PolyData/PolyDataGetPoint) | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html) | Get point locations/coordinates from a [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html).
[PolyDataIsoLines](/Cxx/PolyData/PolyDataIsoLines) | [vtkBandedPolyDataContourFilter](http://www.vtk.org/doc/nightly/html/classvtkBandedPolyDataContourFilter.html) |Iso lines on the surface of a polydata
[PolyDataPointNormals](/Cxx/PolyData/PolyDataPointNormals) | [vtkPointData](http://www.vtk.org/doc/nightly/html/classvtkPointData.html) |Add/Get Normals to/from points in a Polydata.
[PolyDataPointSampler](/Cxx/PolyData/PolyDataPointSampler) | [vtkPolyDataPointSampler](http://www.vtk.org/doc/nightly/html/classvtkPolyDataPointSampler.html) | Sample the edges or surfaces of a polydata.
[PolyDataToImageData](/Cxx/PolyData/PolyDataToImageData) | [vtkPolyDataToImageStencil](http://www.vtk.org/doc/nightly/html/classvtkPolyDataToImageStencil.html) |Generate a binarized volume from a closed surface.
[ProcrustesAlignmentFilter](/Cxx/PolyData/ProcrustesAlignmentFilter) | [vtkProcrustesAlignmentFilter](http://www.vtk.org/doc/nightly/html/classvtkProcrustesAlignmentFilter.html) |Align point sets.
[ProgrammableFilter](/Cxx/Filters/ProgrammableFilter) | [vtkProgrammableFilter](http://www.vtk.org/doc/nightly/html/classvtkProgrammableFilter.html) | Create a custom filter without subclassing.
[ProgrammableSource](/Cxx/Filtering/ProgrammableSource) |[vtkProgrammableSource](http://www.vtk.org/doc/nightly/html/classvtkProgrammableSource.html) |Create points using a programmable source. Generates points for a strange attractor.
[ProjectSphere](/Cxx/Visualization/ProjectSphere) |[vtkProjectSphereFilter](http://www.vtk.org/doc/nightly/html/classvtkProjectSphereFilter.html) |Unroll a sphere or spherical-like model.
[QuantizePolyDataPoints](/Cxx/PolyData/QuantizePolyDataPoints) | [vtkQuantizePolyDataPoints](http://www.vtk.org/doc/nightly/html/classvtkQuantizePolyDataPoints.html) |Snap (quantize) points to a grid.
[Reflection](/Cxx/PolyData/Reflection) | [vtkReflectionFilter](http://www.vtk.org/doc/nightly/html/classvtkReflectionFilter.html) |Mirror a DataSet.
[ReverseSense](/Cxx/PolyData/ReverseSense) | [vtkReverseSense](http://www.vtk.org/doc/nightly/html/classvtkReverseSense.html) |Flip normals.
[RibbonFilter](/Cxx/PolyData/RibbonFilter) | [vtkRibbonFilter](http://www.vtk.org/doc/nightly/html/classvtkRibbonFilter.html) |
[RotationAroundLine](/Cxx/PolyData/RotationAroundLine) | [vtkTransform](http://www.vtk.org/doc/nightly/html/classvtkTransform.html), [vtkTransformPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkTransformPolyDataFilter.html) |Rotation around a line.
[RuledSurfaceFilter](/Cxx/PolyData/RuledSurfaceFilter) | [vtkRuledSurfaceFilter](http://www.vtk.org/doc/nightly/html/classvtkRuledSurfaceFilter.html) |Create a surface between lines.
[SCurveSpline](/Cxx/InfoVis/SCurveSpline) | [vtkSCurveSpline](http://www.vtk.org/doc/nightly/html/classvtkSCurveSpline.html) |Create an SCurve spline on a set of points.
[SelectVisiblePoints](/Cxx/PolyData/SelectVisiblePoints) | [vtkSelectVisiblePoints](http://www.vtk.org/doc/nightly/html/classvtkSelectVisiblePoints.html) |Select visible points.
[SelectionSource](/Cxx/Filtering/SelectionSource) | [vtkSelectionSource](http://www.vtk.org/doc/nightly/html/classvtkSelectionSource.html), [vtkExtractSelection](http://www.vtk.org/doc/nightly/html/classvtkExtractSelection.html) | Specify a selection.
[ShrinkPolyData](/Cxx/PolyData/ShrinkPolyData) | [vtkShrinkPolyData](http://www.vtk.org/doc/nightly/html/classvtkShrinkPolyData.html)|Move all items in a PolyData towards their centroid.
[Silhouette](/Cxx/PolyData/Silhouette) | [vtkPolyDataSilhouette](http://www.vtk.org/doc/nightly/html/classvtkPolyDataSilhouette.html) |
[Stripper](/Cxx/PolyData/Stripper) | [vtkStripper](http://www.vtk.org/doc/nightly/html/classvtkStripper.html) |Convert triangles to triangle strips.
[ThinPlateSplineTransform](/Cxx/PolyData/ThinPlateSplineTransform) | [vtkThinPlateSplineTransform](http://www.vtk.org/doc/nightly/html/classvtkThinPlateSplineTransform.html) |
[ThresholdingCells](/Cxx/PolyData/ThresholdingCells) | [vtkThreshold](http://www.vtk.org/doc/nightly/html/classvtkThreshold.html) |Thresholding Cells.
[ThresholdingPoints](/Cxx/PolyData/ThresholdingPoints) | [vtkThresholdPoints](http://www.vtk.org/doc/nightly/html/classvtkThresholdPoints.html) |Thresholding Points.
[TransformFilter](/Cxx/PolyData/TransformFilter) | [vtkTransformFilter](http://www.vtk.org/doc/nightly/html/classvtkTransformFilter.html) |Transform a data set.
[TransformOrder](/Cxx/PolyData/TransformOrder) | [vtkTransformPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkTransformPolyDataFilter.html) |Demonstrate how the order of applying transforms affects the result.
[TransformPipeline](/Cxx/PolyData/TransformPipeline) | [vtkTransform](http://www.vtk.org/doc/nightly/html/classvtkTransform.html) |Combining the transformation, in order to manipulate a group of [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html). Shown in the example robot arm motion.
[TransformPolyData](/Cxx/Filtering/TransformPolyData) | [vtkTransformPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkTransformPolyDataFilter.html) | Apply a Transformation to a PolyData.
[TriangleArea](/Cxx/PolyData/TriangleArea) | [vtkTriangle](http://www.vtk.org/doc/nightly/html/classvtkTriangle.html)::TriangleArea | Compute the area of all triangles in a polydata.
[TriangleColoredPoints](/Cxx/PolyData/TriangleColoredPoints) | [vtkUnsignedCharArray](http://www.vtk.org/doc/nightly/html/classvtkUnsignedCharArray.html) | Set the color of each point of a triangle. You will be able to interpolate the colors across the triangle.
[TriangleSolidColor](/Cxx/PolyData/TriangleSolidColor) | [vtkUnsignedCharArray](http://www.vtk.org/doc/nightly/html/classvtkUnsignedCharArray.html) | Create a solid colored triangle.
[TubeFilter](/Cxx/PolyData/TubeFilter) | [vtkTubeFilter](http://www.vtk.org/doc/nightly/html/classvtkTubeFilter.html) | Give lines a thickness (produce a cylinder around lines.
[VectorFieldNonZeroExtraction](/Cxx/Filtering/VectorFieldNonZeroExtraction) | [vtkExtractSelectedThresholds](http://www.vtk.org/doc/nightly/html/classvtkExtractSelectedThresholds.html)| Extract non-zero vectors from a [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html).
[VertexConnectivity](/Cxx/PolyData/VertexConnectivity) | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html)::GetCellPoints |Get a list of vertices attached (through an edge) to a vertex.
[WarpScalar](/Cxx/PolyData/WarpScalar) | [vtkWarpScalar](http://www.vtk.org/doc/nightly/html/classvtkWarpScalar.html) |Move vertices along normals.
[WarpSurface](/Cxx/PolyData/WarpSurface) | [vtkWarpVector](http://www.vtk.org/doc/nightly/html/classvtkWarpVector.html)|Warp a surface along its normal.
[WarpTo](/Cxx/Filtering/WarpTo) | [vtkWarpTo](http://www.vtk.org/doc/nightly/html/classvtkWarpTo.html) | Bend an object.
[WarpVector](/Cxx/PolyData/WarpVector) | [vtkWarpVector](http://www.vtk.org/doc/nightly/html/classvtkWarpVector.html) | 


##Data Types

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[CompositePolyDataMapper](/Cxx/CompositeData/CompositePolyDataMapper) | [vtkCompositePolyDataMapper](http://www.vtk.org/doc/nightly/html/classvtkCompositePolyDataMapper.html) |
[MultiBlockDataSet](/Cxx/CompositeData/MultiBlockDataSet) | [vtkMultiBlockDataSet](http://www.vtk.org/doc/nightly/html/classvtkMultiBlockDataSet.html) | Demonstrates how to make and use VTK's MultiBlock type data
[OverlappingAMR](/Cxx/CompositeData/OverlappingAMR) | [vtkOverlappingAMR](http://www.vtk.org/doc/nightly/html/classvtkOverlappingAMR.html) |Demonstrates how to create and populate a VTK's Overlapping AMR Grid type Data


##Data Type Conversions


| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[PolyDataToUnstructuredGrid](/Cxx/PolyData/PolyDataToUnstructuredGrid) | [vtkAppendFilter](http://www.vtk.org/doc/nightly/html/classvtkAppendFilter.html) |Convert a [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html) to a [vtkUnstructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html).


##Point cloud operations


| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[DensifyPoints](/Cxx/Points/DensifyPoints) | [vtkDensifyPointCloudFilter](http://www.vtk.org/doc/nightly/html/classvtkDensifyPointCloudFilter.html) | Add points to a point cloud.
[DownsamplePointCloud](/Cxx/PolyData/DownsamplePointCloud) | [vtkCleanPolyData](http://www.vtk.org/doc/nightly/html/classvtkCleanPolyData.html) | Downsample a point cloud. Remove points so that there are no points within a tolerance of any point.
[ExtractCluster](/Cxx/Points/ExtractCluster) | [vtkEuclideanClusterExtraction](http://www.vtk.org/doc/nightly/html/classvtkEuclideanClusterExtraction.html) | From a set of randomly distributed spheres, extract connected clusters.
[ExtractPointsDemo](/Cxx/Points/ExtractPointsDemo) | [vtkExtractPoints](http://www.vtk.org/doc/nightly/html/classvtkExtractPoints.html) |Extract points inside an implicit function.
[ExtractSurfaceDemo](/Cxx/Points/ExtractSurfaceDemo) | [vtkExtractSurface](http://www.vtk.org/doc/nightly/html/classvtkExtractSurface.html),[vtkPCANormalEstimation](http://www.vtk.org/doc/nightly/html/classvtkPCANormalEstimation.html),[vtkSignedDistance](http://www.vtk.org/doc/nightly/html/classvtkSignedDistance.html) |Create a surface from Unorganized Points using Point filters (DEMO).
[ExtractSurface](/Cxx/Points/ExtractSurface) | [vtkExtractSurface](http://www.vtk.org/doc/nightly/html/classvtkExtractSurface.html),[vtkPCANormalEstimation](http://www.vtk.org/doc/nightly/html/classvtkPCANormalEstimation.html),[vtkSignedDistance](http://www.vtk.org/doc/nightly/html/classvtkSignedDistance.html) |Create a surface from Unorganized Points using Point filters.
[FitImplicitFunction](/Cxx/Points/FitImplicitFunction) | [vtkFitImplicitFunction](http://www.vtk.org/doc/nightly/html/classvtkFitImplicitFunction.html) | Extract points within a distance to an implicit function.
[MaskPointsFilter](/Cxx/Points/MaskPointsFilter) | [vtkMaskPointsFilter](http://www.vtk.org/doc/nightly/html/classvtkMaskPointsFilter.html) |Extract points within an image mask.
[NormalEstimation](/Cxx/Points/NormalEstimation) | [vtkPCANormalEstimation](http://www.vtk.org/doc/nightly/html/classvtkPCANormalEstimation.html) | Estimate the normals of a random points that lie on a sphere.
[PointOccupancy](/Cxx/Points/PointOccupancy) | [vtkPointOccupancy](http://www.vtk.org/doc/nightly/html/classvtkPointOccupancy.html) |Show which voxels contain points.
[PointSource](/Cxx/PolyData/PointSource) | [vtkPointSource](http://www.vtk.org/doc/nightly/html/classvtkPointSource.html) |Generate a random point cloud.
[RadiusOutlierRemoval](/Cxx/Points/RadiusOutlierRemoval) | [vtkRadiusOutlierRemoval](http://www.vtk.org/doc/nightly/html/classvtkRadiusOutlierRemoval.html) |Remove outliers.
[SignedDistance](/Cxx/Points/SignedDistance) | [vtkSignedDistance](http://www.vtk.org/doc/nightly/html/classvtkSignedDistance.html) |Compute signed distance to a point cloud.
[UnsignedDistance](/Cxx/Points/UnsignedDistance) | [vtkUnsignedDistance](http://www.vtk.org/doc/nightly/html/classvtkUnsignedDistance.html) |Compute unsigned distance to a point cloud.


##Working with Meshes


| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[AddCell](/Cxx/Meshes/AddCell) | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html) | Add a cell to an existing mesh.
[BoundaryEdges](/Cxx/Meshes/BoundaryEdges) | [vtkFeatureEdges](http://www.vtk.org/doc/nightly/html/classvtkFeatureEdges.html) | Find the edges that are used by only one face.
[CellEdges](/Cxx/Meshes/CellEdges) | [vtkCell](http://www.vtk.org/doc/nightly/html/classvtkCell.html) |Get edges of cells.
[ClosedSurface](/Cxx/PolyData/ClosedSurface) | [vtkFeatureEdges](http://www.vtk.org/doc/nightly/html/classvtkFeatureEdges.html) |Check if a surface is closed.
[ColorDisconnectedRegions](/Cxx/PolyData/ColorDisconnectedRegions) | [vtkPolyDataConnectivityFilter](http://www.vtk.org/doc/nightly/html/classvtkPolyDataConnectivityFilter.html) | Color each disconnected region of a [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html) a different color.
[ColoredElevationMap](/Cxx/Meshes/ColoredElevationMap)| [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html) |Color a mesh by height.
[Curvatures](/Cxx/PolyData/Curvatures) | [vtkCurvatures](http://www.vtk.org/doc/nightly/html/classvtkCurvatures.html) |Compute Gaussian, Mean, Min, and Max Curvatures.
[Decimation](/Cxx/Meshes/Decimation) | [vtkDecimatePro](http://www.vtk.org/doc/nightly/html/classvtkDecimatePro.html) | Reduce the number of triangles in a mesh.
[DeformPointSet](/Cxx/Meshes/DeformPointSet) | [vtkDeformPointSet](http://www.vtk.org/doc/nightly/html/classvtkDeformPointSet.html) | Deform a point set with a control polyhedra.
[DijkstraGraphGeodesicPath](/Cxx/PolyData/DijkstraGraphGeodesicPath) | [vtkDijkstraGraphGeodesicPath](http://www.vtk.org/doc/nightly/html/classvtkDijkstraGraphGeodesicPath.html) |Find the shortest path between two points on a mesh.
[ElevationFilter](/Cxx/Meshes/ElevationFilter) | [vtkElevationFilter](http://www.vtk.org/doc/nightly/html/classvtkElevationFilter.html) |Color a mesh by height.
[ExtractEdges](/Cxx/Meshes/ExtractEdges) | [vtkExtractEdges](http://www.vtk.org/doc/nightly/html/classvtkExtractEdges.html) |
[FillHoles](/Cxx/Meshes/FillHoles) | [vtkFillHolesFilter](http://www.vtk.org/doc/nightly/html/classvtkFillHolesFilter.html) | Close holes in a mesh.
[GreedyTerrainDecimation](/Cxx/PolyData/GreedyTerrainDecimation)  | [vtkGreedyTerrainDecimation](http://www.vtk.org/doc/nightly/html/classvtkGreedyTerrainDecimation.html) | Create a mesh from an ImageData 
[HighlightBadCells](/Cxx/PolyData/HighlightBadCells) | [vtkMeshQuality](http://www.vtk.org/doc/nightly/html/classvtkMeshQuality.html) |
[LargestRegion](/Cxx/PolyData/PolyDataConnectivityFilter_LargestRegion)  | [vtkPolyDataConnectivityFilter](http://www.vtk.org/doc/nightly/html/classvtkPolyDataConnectivityFilter.html) |  Extract the largest connected region in a polydata.
[MatrixMathFilter](/Cxx/Meshes/MatrixMathFilter) | [vtkMatrixMathFilter](http://www.vtk.org/doc/nightly/html/classvtkMatrixMathFilter.html) | Compute various quantities on cell and points in a mesh.
[MeshQuality](/Cxx/PolyData/MeshQuality) | [vtkMeshQuality](http://www.vtk.org/doc/nightly/html/classvtkMeshQuality.html) |
[OBBDicer](/Cxx/Meshes/OBBDicer) | [vtkOBBDicer](http://www.vtk.org/doc/nightly/html/classvtkOBBDicer.html) | Breakup a mesh into pieces.
[PolygonalSurfaceContourLineInterpolator](/Cxx/PolyData/PolygonalSurfaceContourLineInterpolator) | [vtkPolygonalSurfaceContourLineInterpolator](http://www.vtk.org/doc/nightly/html/classvtkPolygonalSurfaceContourLineInterpolator.html) |Interactively find the shortest path between two points on a mesh.
[QuadricClustering](/Cxx/Meshes/QuadricClustering) | [vtkQuadricClustering](http://www.vtk.org/doc/nightly/html/classvtkQuadricClustering.html) | Reduce the number of triangles in a mesh.
[QuadricDecimation](/Cxx/Meshes/QuadricDecimation) | [vtkQuadricDecimation](http://www.vtk.org/doc/nightly/html/classvtkQuadricDecimation.html) | Reduce the number of triangles in a mesh.
[SelectPolyData](/Cxx/PolyData/SelectPolyData) | [vtkSelectPolyData](http://www.vtk.org/doc/nightly/html/classvtkSelectPolyData.html) |Select a region of a mesh.
[SimpleElevationFilter](/Cxx/Meshes/SimpleElevationFilter) | [vtkSimpleElevationFilter](http://www.vtk.org/doc/nightly/html/classvtkSimpleElevationFilter.html) |Color a mesh by dotting a vector from the origin to each point with a specified vector.
[SmoothPolyDataFilter](/Cxx/PolyData/SmoothPolyDataFilter) | [vtkSmoothPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkSmoothPolyDataFilter.html) |Laplacian smoothing.
[SpecifiedRegion](/Cxx/PolyData/PolyDataConnectivityFilter_SpecifiedRegion) | [vtkPolyDataConnectivityFilter](http://www.vtk.org/doc/nightly/html/classvtkPolyDataConnectivityFilter.html) | Extract a specific (specified) connected region in a polydata.
[SplitPolyData](/Cxx/Meshes/SplitPolyData) | [vtkOBBDicer](http://www.vtk.org/doc/nightly/html/classvtkOBBDicer.html) | Breakup a mesh into pieces and save the pieces into files
[Subdivision](/Cxx/Meshes/Subdivision) | [vtkButterflySubdivisionFilter](http://www.vtk.org/doc/nightly/html/classvtkButterflySubdivisionFilter.html), [vtkLoopSubdivisionFilter](http://www.vtk.org/doc/nightly/html/classvtkLoopSubdivisionFilter.html), [vtkLinearSubdivisionFilter](http://www.vtk.org/doc/nightly/html/classvtkLinearSubdivisionFilter.html) | Increase the number of triangles in a mesh.
[Triangluate](/Cxx/Meshes/Triangulate) | [vtkTriangleFilter](http://www.vtk.org/doc/nightly/html/classvtkTriangleFilter.html) | Convert all polygons in a mesh to triangles.
[WeightedTransformFilter ](/Cxx/PolyData/WeightedTransformFilter)  | [vtkWeightedTransformFilter](http://www.vtk.org/doc/nightly/html/classvtkWeightedTransformFilter.html) |
[WindowedSincPolyDataFilter](/Cxx/Meshes/WindowedSincPolyDataFilter) | [vtkWindowedSincPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkWindowedSincPolyDataFilter.html) | Smooth a mesh (windowed sinc filter).

###Clipping

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[BoxClipStructuredPoints](/Cxx/Visualization/BoxClipStructuredPoints) | [vtkBoxClipDataSet](http://www.vtk.org/doc/nightly/html/classvtkBoxClipDataSet.html), [vtkStructuredPoints](http://www.vtk.org/doc/nightly/html/classvtkStructuredPoints.html) |Clip [vtkStructuredPoints](http://www.vtk.org/doc/nightly/html/classvtkStructuredPoints.html) with a box. The results are unstructured grids with tetrahedra.
[BoxClipUnstructuredGrid](/Cxx/Visualization/BoxClipUnstructuredGrid) | [vtkBoxClipDataSet](http://www.vtk.org/doc/nightly/html/classvtkBoxClipDataSet.html), [vtkUnstructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html) |Clip a [vtkUnstructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html) with a box. The results are unstructured grids with tetrahedra.
[CapClip](/Cxx/Meshes/CapClip) | [vtkClipPolyData](http://www.vtk.org/doc/nightly/html/classvtkClipPolyData.html) |Cap a clipped polydata with a polygon.
[ClipClosedSurface](/Cxx/Meshes/ClipClosedSurface) | [vtkClipClosedSurface](http://www.vtk.org/doc/nightly/html/classvtkClipClosedSurface.html) |Clip a surface with multiple planes.
[ClipDataSetWithPolyData](/Cxx/Meshes/ClipDataSetWithPolyData) | [vtkClipDataSet](http://www.vtk.org/doc/nightly/html/classvtkClipDataSet.html), [vtkImplicitPolyDataDistance](http://www.vtk.org/doc/nightly/html/classvtkImplicitPolyDataDistance.html), [vtkRectilinearGrid](http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html) |Clip a [vtkRectilinearGrid](http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html) with arbitrary polydata. In this example, use a [vtkConeSource](http://www.vtk.org/doc/nightly/html/classvtkConeSource.html) to generate polydata to slice the grid, resulting in an unstructured grid. Contrast this with the next example.
[GenericClip](/Cxx/Filtering/GenericClip) | [vtkGenericClip](http://www.vtk.org/doc/nightly/html/classvtkGenericClip.html),[vtkBridgeDataSet](http://www.vtk.org/doc/nightly/html/classvtkBridgeDataSet.html), [vtkGenericDataSet](http://www.vtk.org/doc/nightly/html/classvtkGenericDataSet.html) | 
[ImplicitDataSetClipping](/Cxx/PolyData/ImplicitDataSetClipping) | [vtkImplicitDataSet](http://www.vtk.org/doc/nightly/html/classvtkImplicitDataSet.html) |Clip using an implicit data set.
[SolidClip](/Cxx/Meshes/SolidClip) | [vtkClipPolyData](http://www.vtk.org/doc/nightly/html/classvtkClipPolyData.html) |Create a "solid" clip.
[TableBasedClipDataSetWithPolyData](/Cxx/Meshes/TableBasedClipDataSetWithPolyData) | [vtkTableBasedClipDataSet](http://www.vtk.org/doc/nightly/html/classvtkTableBasedClipDataSet.html), [vtkImplicitPolyDataDistance](http://www.vtk.org/doc/nightly/html/classvtkImplicitPolyDataDistance.html), [vtkRectilinearGrid](http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html) |Clip a [vtkRectilinearGrid](http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html) with arbitrary polydata. In this example, use a [vtkConeSource](http://www.vtk.org/doc/nightly/html/classvtkConeSource.html) to generate polydata to slice the grid, resulting in an unstructured grid. Contrast this with the previous example.


##Working with Structured 3D Data
This section includes [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html), [vtkStructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkStructuredGrid.html), and [vtkRectilinearGrid](http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html).

"ImageData" is not the traditional "flat, 2D image" you are used to. It is a special VTK data structure in the collection of 3D data structures provided by VTK. [Here is an overview of these data structures](http://www.vtk.org/Wiki/VTK/Tutorials/3DDataTypes). Image data can represent at typical 2D image, but also, a 3D volume.

* [[/Cxx/Visualization/StructuredDataTypes|Demonstration of structured data types]]
* [[/Cxx/StructuredData/GetLinearPointId|Get the linear point id of a point in a grid]]

###[vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html)

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[GetCellCenter](/Cxx/ImageData/GetCellCenter) | [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html)|Get the coordinates of the center of a cell.
[CellIdFromGridCoordinates](/Cxx/ImageData/CellIdFromGridCoordinates) | [vtkStructuredData](http://www.vtk.org/doc/nightly/html/classvtkStructuredData.html)|Get the id of a cell from its grid coordinates.
[IterateImageData](/Cxx/ImageData/IterateImageData) | [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html) | Iterating over a [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html).
[ImageNormalize](/Cxx/ImageData/ImageNormalize) | [vtkImageNormalize](http://www.vtk.org/doc/nightly/html/classvtkImageNormalize.html) |Normalize an image.
[ExtractVOI](e/Cxx/ImageData/ExtractVOI) | [vtkExtractVOI](http://www.vtk.org/doc/nightly/html/classvtkExtractVOI.html) | Extract a volume of interest (subvolume).
[ImageWeightedSum](/Cxx/ImageData/ImageWeightedSum) | [vtkImageWeightedSum](http://www.vtk.org/doc/nightly/html/classvtkImageWeightedSum.html) |Add two or more images.
[ImageReslice](/Cxx/ImageData/ImageReslice) | [vtkImageReslice](http://www.vtk.org/doc/nightly/html/classvtkImageReslice.html) |Resize a [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html).
[ImageTranslateExtent](/Cxx/ImageData/ImageTranslateExtent) | [vtkImageTranslateExtent](http://www.vtk.org/doc/nightly/html/classvtkImageTranslateExtent.html) |Change the extent of a [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html).
[IntersectLine](/Cxx/ImageData/IntersectLine) | [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html) |Intersect a line with all cells of a [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html).
[ImageIterator](/Cxx/ImageData/ImageIterator)| [vtkImageIterator](http://www.vtk.org/doc/nightly/html/classvtkImageIterator.html) |


###Conversions

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[ImageDataGeometryFilter](/Cxx/ImageData/ImageDataGeometryFilter) | [vtkImageDataGeometryFilter](http://www.vtk.org/doc/nightly/html/classvtkImageDataGeometryFilter.html) |Convert a [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html) to a [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html)
[ImageDataToPointSet](/Cxx/ImageData/ImageDataToPointSet) | [vtkImageDataToPointSet](http://www.vtk.org/doc/nightly/html/classvtkImageDataToPointSet.html) |Convert a [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html) to a [vtkStructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkStructuredGrid.html).

###[vtkStructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkStructuredGrid.html)


| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[BlankPoint](/Cxx/StructuredGrid/BlankPoint) | [vtkStructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkStructuredGrid.html) |Blank a point of a [vtkStructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkStructuredGrid.html).
[OutlineStructuredGrid](/Cxx/StructuredGrid/OutlineStructuredGrid) | [vtkStructuredGridOutlineFilter](http://www.vtk.org/doc/nightly/html/classvtkStructuredGridOutlineFilter.html) |Visualize the outline of a structured grid.
[StructuredGrid](/Cxx/StructuredGrid/StructuredGrid) | [vtkStructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkStructuredGrid.html) |Structured Grid.
[VisualizeStructuredGridCells](/Cxx/StructuredGrid/VisualizeStructuredGridCells) | [vtkShrinkFilter](http://www.vtk.org/doc/nightly/html/classvtkShrinkFilter.html) |Visualize the cells of a structured grid.
[VisualizeStructuredGrid](/Cxx/StructuredGrid/VisualizeStructuredGrid) | [vtkStructuredGridGeometryFilter](http://www.vtk.org/doc/nightly/html/classvtkStructuredGridGeometryFilter.html) |Visualize the points of a structured grid.

###[vtkStructuredPoints](http://www.vtk.org/doc/nightly/html/classvtkStructuredPoints.html)


| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[StructuredPointsToUnstructuredGrid](/Cxx/StructuredPoints/StructuredPointsToUnstructuredGrid) | [vtkStructuredPoints](http://www.vtk.org/doc/nightly/html/classvtkStructuredPoints.html), [vtkUnstructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html)|Convert a [vtkStructuredPoints](http://www.vtk.org/doc/nightly/html/classvtkStructuredPoints.html) to a [vtkUnstructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html).


###[vtkRectilinearGrid](http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html)


| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[RectilinearGridToTetrahedra](/Cxx/RectilinearGrid/RectilinearGridToTetrahedra) | [vtkRectilinearGridToTetrahedra](http://www.vtk.org/doc/nightly/html/classvtkRectilinearGridToTetrahedra.html) |Convert a [vtkRectilinearGrid](http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html) to a [vtkUnstructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html) mesh
[RectilinearGrid](/Cxx/RectilinearGrid/RectilinearGrid) | [vtkRectilinearGrid](http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html) |Rectilinear grid
[VisualizeRectilinearGridCells](/Cxx/RectilinearGrid/VisualizeRectilinearGridCells) | [vtkRectilinearGrid](http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html), [vtkShrinkFilter](http://www.vtk.org/doc/nightly/html/classvtkShrinkFilter.html)|Visualize the cells of a rectilinear grid

##Registration

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[IterativeClosestPointsTransform](/Cxx/Filters/IterativeClosestPointsTransform) | [vtkIterativeClosestPointTransform](http://www.vtk.org/doc/nightly/html/classvtkIterativeClosestPointTransform.html) | Iterative Closest Points (ICP) Transform.
[LandmarkTransform](/Cxx/Filters/LandmarkTransform) | [vtkLandmarkTransform](http://www.vtk.org/doc/nightly/html/classvtkLandmarkTransform.html) |Landmark Transform.

##Medical

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[MedicalDemo1](/Cxx/Medical/MedicalDemo1) | [vtkMarchingCubes](http://www.vtk.org/doc/nightly/html/classvtkMarchingCubes.html) |Create a skin surface from volume data
[MedicalDemo2](/Cxx/Medical/MedicalDemo2) | [vtkMarchingCubes](http://www.vtk.org/doc/nightly/html/classvtkMarchingCubes.html) |Create a skin and bone surface from volume data
[MedicalDemo3](/Cxx/Medical/MedicalDemo3) | [vtkMarchingCubes](http://www.vtk.org/doc/nightly/html/classvtkMarchingCubes.html) |Create skin, bone and slices from volume data
[MedicalDemo4](/Cxx/Medical/MedicalDemo4) | [vtkFixedPointVolumeRayCastMapper](http://www.vtk.org/doc/nightly/html/classvtkFixedPointVolumeRayCastMapper.html) |Create a volume rendering
[TissueLens](/Cxx/Medical/TissueLens) | [vtkMarchingCubes](http://www.vtk.org/doc/nightly/html/classvtkMarchingCubes.html) [vtkClipDataSet](http://www.vtk.org/doc/nightly/html/classvtkClipDataSet.html)  [vtkProbeFilter](http://www.vtk.org/doc/nightly/html/classvtkProbeFilter.html) |Cut a volume with a sphere

##Surface reconstruction

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[Delaunay3D](/Cxx/Modelling/Delaunay3D) | [vtkDelaunay3D](http://www.vtk.org/doc/nightly/html/classvtkDelaunay3D.html) | Create a solid mesh from Unorganized Points (Delaunay3D).
[ExtractSurfaceDemo](/Cxx/Points/ExtractSurfaceDemo) | [vtkExtractSurface](http://www.vtk.org/doc/nightly/html/classvtkExtractSurface.html),[vtkPCANormalEstimation](http://www.vtk.org/doc/nightly/html/classvtkPCANormalEstimation.html),[vtkSignedDistance](http://www.vtk.org/doc/nightly/html/classvtkSignedDistance.html) |Create a surface from Unorganized Points using Point filters (DEMO).
[ExtractSurface](/Cxx/Points/ExtractSurface) | [vtkExtractSurface](http://www.vtk.org/doc/nightly/html/classvtkExtractSurface.html),[vtkPCANormalEstimation](http://www.vtk.org/doc/nightly/html/classvtkPCANormalEstimation.html),[vtkSignedDistance](http://www.vtk.org/doc/nightly/html/classvtkSignedDistance.html) |Create a surface from Unorganized Points using Point filters.
[GaussianSplat](/Cxx/Filtering/GaussianSplat) | [vtkGaussianSplatter](http://www.vtk.org/doc/nightly/html/classvtkGaussianSplatter.html) |Create a surface from Unorganized Points (Gaussian Splat).
[GenerateCubesFromLabels](/Cxx/Medical/GenerateCubesFromLabels) | [vtkMetaImageReader](http://www.vtk.org/doc/nightly/html/classvtkMetaImageReader.html), [vtkMaskFields](http://www.vtk.org/doc/nightly/html/classvtkMaskFields.html) |Create cubes from labeled volume data.
[GenerateModelsFromLabels](/Cxx/Medical/GenerateModelsFromLabels) | [vtkDiscreteMarchingCubes](http://www.vtk.org/doc/nightly/html/classvtkDiscreteMarchingCubes.html) |Create models from labeled volume data (Discrete MarchingCubes).
[SurfaceFromUnorganizedPointsWithPostProc](/Cxx/Filtering/SurfaceFromUnorganizedPointsWithPostProc) | [vtkSurfaceReconstructionFilter](http://www.vtk.org/doc/nightly/html/classvtkSurfaceReconstructionFilter.html) |Create a surface from Unorganized Points (with post processing).
[SurfaceFromUnorganizedPoints](/Cxx/Filtering/SurfaceFromUnorganizedPoints) | [vtkSurfaceReconstructionFilter](http://www.vtk.org/doc/nightly/html/classvtkSurfaceReconstructionFilter.html) |Create a surface from Unorganized Points.
[TriangulateTerrainMap](/Cxx/Filtering/TriangulateTerrainMap) | [vtkDelaunay2D](http://www.vtk.org/doc/nightly/html/classvtkDelaunay2D.html) | Generate heights (z values) on a 10x10 grid (a terrain map) and then triangulate the points to form a surface.

#Utilities

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[BoundingBoxIntersection](/Cxx/Utilities/BoundingBoxIntersection) | [vtkBoundingBox](http://www.vtk.org/doc/nightly/html/classvtkBoundingBox.html) |Box intersection and Inside tests.
[BoundingBox](/Cxx/Utilities/BoundingBox) | [vtkBoundingBox](http://www.vtk.org/doc/nightly/html/classvtkBoundingBox.html) |Bounding Box construction.
[BrownianPoints](/Cxx/Utilities/BrownianPoints) | [vtkBrownianPoints](http://www.vtk.org/doc/nightly/html/classvtkBrownianPoints.html) |Produce a random vector at each point in a dataset.
[CardinalSpline](/Cxx/Utilities/CardinalSpline) | [vtkCardinalSpline](http://www.vtk.org/doc/nightly/html/classvtkCardinalSpline.html) |Cardinal spline Interpolation.
[Casting](/Cxx/PolyData/Casting)| [vtkObject](http://www.vtk.org/doc/nightly/html/classvtkObject.html)::SafeDownCast | Casting VTK objects.
[CheckVTKVersion](/Cxx/Utilities/Check[VTKVersion](http://www.vtk.org/doc/nightly/html/classVTKVersion.html)) | [vtkVersion](http://www.vtk.org/doc/nightly/html/classvtkVersion.html) | Check VTK Version.
[ColorLookupTable](/Cxx/Utilities/ColorLookupTable) | [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html) |Color Lookup Table.
[ColorTransferFunction](/Cxx/Utilities/ColorTransferFunction) | [vtkColorTransferFunction](http://www.vtk.org/doc/nightly/html/classvtkColorTransferFunction.html) |Color Transfer Function.
[CommandSubclass](/Cxx/Utilities/CommandSubclass) | [vtkCommand](http://www.vtk.org/doc/nightly/html/classvtkCommand.html) | Instead of using a callback function, it is more powerful to subclass [vtkCommand](http://www.vtk.org/doc/nightly/html/classvtkCommand.html).
[ConstrainedDelaunay2D](/Cxx/Filtering/ConstrainedDelaunay2D) |  [vtkDelaunay2D](http://www.vtk.org/doc/nightly/html/classvtkDelaunay2D.html) | Perform a 2D Delaunay triangulation on a point set respecting a specified boundary.
[Coordinate](/Cxx/Utilities/Coordinate)| [vtkCoordinate](http://www.vtk.org/doc/nightly/html/classvtkCoordinate.html) |Coordinate system conversions.
[DeepCopy](/Cxx/Utilities/DeepCopy) |  | Deep copy a VTK object.
[Delaunay2D](/Cxx/Filtering/Delaunay2D) | [vtkDelaunay2D](http://www.vtk.org/doc/nightly/html/classvtkDelaunay2D.html) | Perform a 2D Delaunay triangulation on a point set.
[DetermineActorType](/Cxx/Utilities/DetermineActorType) | [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html), [vtkActorCollection](http://www.vtk.org/doc/nightly/html/classvtkActorCollection.html) |Determine the type of an actor.
[DetermineVariableType](/Cxx/Utilities/DetermineVariableType) | GetClassName() |Determine the type of a VTK variable.
[DiscretizableColorTransferFunction](/Cxx/Utilities/DiscretizableColorTransferFunction) | [vtkDiscretizableColorTransferFunction](http://www.vtk.org/doc/nightly/html/classvtkDiscretizableColorTransferFunction.html) |Discretizable Color Transfer Function.
[FileOutputWindow](/Cxx/Utilities/FileOutputWindow) | [vtkFileOutputWindow](http://www.vtk.org/doc/nightly/html/classvtkFileOutputWindow.html) | Write errors to a log file instead of the screen.
[FilenameFunctions](/Cxx/Utilities/FilenameFunctions) | [vtkDirectory](http://www.vtk.org/doc/nightly/html/classvtkDirectory.html), [vtksys](http://www.vtk.org/doc/nightly/html/classvtksys.html)/SystemTools | Do things like get the file extension, strip the file extension, etc.
[FilterProgress](/Cxx/Utilities/FilterProgress) |  |Monitor a filters progress.
[FrameRate](/Cxx/Utilities/FrameRate) | | Get the frame rate of the rendering.
[FullScreen](/Cxx/Utilities/FullScreen) | [vtkRenderWindow](http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html) | Maximize/full screen a [vtkRenderWindow](http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html).
[FunctionParser](/Cxx/Utilities/FunctionParser) | [vtkFunctionParser](http://www.vtk.org/doc/nightly/html/classvtkFunctionParser.html) |String function parser.
[GetDataRoot](/Cxx/Utilities/GetDataRoot) | [vtkTesting](http://www.vtk.org/doc/nightly/html/classvtkTesting.html) | Find the path of VTK_DATA_ROOT.
[LUTUtilities](/Cxx/Utilities/LUTUtilities) | [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html) [vtkColorSeries](http://www.vtk.org/doc/nightly/html/classvtkColorSeries.html) | A utility class for [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html) allowing you to output the table contents or to compare tables.|
[MultipleRenderWindows](/Cxx/Visualization/MultipleRenderWindows) | [vtkRenderWindow](http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html) | Multiple Render Windows
[MultipleViewports](/Cxx/Visualization/MultipleViewports) | [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html)::SetViewPort |Multiple Viewports.
[OffScreenRendering](/Cxx/Utilities/OffScreenRendering) | [vtkImagingFactory](http://www.vtk.org/doc/nightly/html/classvtkImagingFactory.html), [vtkGraphicsFactory](http://www.vtk.org/doc/nightly/html/classvtkGraphicsFactory.html) |Off Screen Rendering.
[PCADemo](/Cxx/Utilities/PCADemo) | [vtkPCAStatistics](http://www.vtk.org/doc/nightly/html/classvtkPCAStatistics.html) |Project 2D points onto the best 1D subspace (PCA Demo).
[PCAStatistics](/Cxx/Utilities/PCAStatistics) | [vtkPCAStatistics](http://www.vtk.org/doc/nightly/html/classvtkPCAStatistics.html) |Compute Principal Component Analysis (PCA) values.
[PassThrought](/Cxx/InfoVis/PassThrough) | [vtkPassThrough](http://www.vtk.org/doc/nightly/html/classvtkPassThrough.html) |Pass input along to outpu.
[PiecewiseFunction](/Cxx/Utilities/PiecewiseFunction) | [vtkPiecewiseFunction](http://www.vtk.org/doc/nightly/html/classvtkPiecewiseFunction.html) |Interpolation using a piecewise function.
[PointInPolygon](/Cxx/Utilities/PointInPolygon) | [vtkPolygon](http://www.vtk.org/doc/nightly/html/classvtkPolygon.html) | Point inside polygon test.
[Screenshot](/Cxx/Utilities/Screenshot) | [vtkWindowToImageFilter](http://www.vtk.org/doc/nightly/html/classvtkWindowToImageFilter.html) |
[ShallowCopy](/Cxx/Utilities/ShallowCopy) |  | Shallow copy a VTK object.
[ShareCamera](/Cxx/Utilities/ShareCamera) | [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html), [vtkCamera](http://www.vtk.org/doc/nightly/html/classvtkCamera.html) | Share a camera between multiple renderers.
[ShepardMethod](/Cxx/Utilities/ShepardMethod) | [vtkShepardMethod](http://www.vtk.org/doc/nightly/html/classvtkShepardMethod.html) |Shepard method interpolation.
[SideBySideViewports](/Cxx/Visualization/SideBySideViewports) | [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html)::SetViewPort | Side by side viewports.
[TimeStamp](/Cxx/Utilities/TimeStamp) | [vtkTimeStamp](http://www.vtk.org/doc/nightly/html/classvtkTimeStamp.html) |Time stamp.
[TimerLog](/Cxx/Utilities/TimerLog) | [vtkTimerLog](http://www.vtk.org/doc/nightly/html/classvtkTimerLog.html) |Timer log.
[Timer](/Cxx/Utilities/Timer) | [vtkRenderWindowInteractor](http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html)::CreateRepeatingTimer |
[Variant](/Cxx/Utilities/Variant) | [vtkVariant](http://www.vtk.org/doc/nightly/html/classvtkVariant.html) |Convert between data types.
[Vector](/Cxx/Utilities/Vector) | [vtkVector](http://www.vtk.org/doc/nightly/html/classvtkVector.html) |Mathematical vector class.
[VersionMacros](/Cxx/Utilities/VersionMacros) | Macro/#define's | Check VTK Version.
[VisualDebugging](/Cxx/Utilities/VisualDebugging) | | Update the screen from inside an algorithm.
[ZBuffer](/Cxx/Utilities/ZBuffer) | [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html) | zbuffer.

##Arrays

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[2DArray](/Cxx/Utilities/2DArray) | [vtkDenseArray](http://www.vtk.org/doc/nightly/html/classvtkDenseArray.html) |2D Array.
[3DArray](/Cxx/Utilities/3DArray) | [vtkDenseArray](http://www.vtk.org/doc/nightly/html/classvtkDenseArray.html) |3D Array.
[ArrayCalculator](/Cxx/Utilities/ArrayCalculator) | [vtkArrayCalculator](http://www.vtk.org/doc/nightly/html/classvtkArrayCalculator.html) | Perform in-place operations on arrays.
[ArrayLookup](/Cxx/Utilities/ArrayLookup) | [vtkDataArray](http://www.vtk.org/doc/nightly/html/classvtkDataArray.html) | Find the location of a value in a [vtkDataArray](http://www.vtk.org/doc/nightly/html/classvtkDataArray.html).
[ArrayRange](/Cxx/Utilities/ArrayRange) | [vtkFloatArray](http://www.vtk.org/doc/nightly/html/classvtkFloatArray.html)::GetRange |Get the bounds (min,max) of a [vtk](http://www.vtk.org/doc/nightly/html/classvtk.html) array.
[ArrayToTable](/Cxx/InfoVis/ArrayToTable) | [vtkArrayToTable](http://www.vtk.org/doc/nightly/html/classvtkArrayToTable.html) |Convert a [vtkDenseArray](http://www.vtk.org/doc/nightly/html/classvtkDenseArray.html) to a [vtkTable](http://www.vtk.org/doc/nightly/html/classvtkTable.html).
[ArrayWriter](/Cxx/Utilities/ArrayWriter) | [vtkArrayWriter](http://www.vtk.org/doc/nightly/html/classvtkArrayWriter.html)| Write a DenseArray or SparseArray to a file.
[ConcatenateArray](/Cxx/TextAnalysis/ConcatenateArray) | [vtkConcatenateArray](http://www.vtk.org/doc/nightly/html/classvtkConcatenateArray.html) |Concatenate two arrays.
[ConstructTable](/Cxx/Utilities/ConstructTable) | [vtkTable](http://www.vtk.org/doc/nightly/html/classvtkTable.html) | A table is a 2D array of any type of elements. They do not all have to be the same type. This is achieved using [vtkVariant](http://www.vtk.org/doc/nightly/html/classvtkVariant.html).
[CustomDenseArray](/Cxx/Utilities/CustomDenseArray) | [vtkDenseArray](http://www.vtk.org/doc/nightly/html/classvtkDenseArray.html) |Custom type Dense (2D) Array.
[DenseArrayRange](/Cxx/Utilities/DenseArrayRange) | [vtkDenseArray](http://www.vtk.org/doc/nightly/html/classvtkDenseArray.html), [vtkArrayRange](http://www.vtk.org/doc/nightly/html/classvtkArrayRange.html) |Get the bounds of a [vtkDenseArray](http://www.vtk.org/doc/nightly/html/classvtkDenseArray.html).
[ExtractArrayComponent](/Cxx/Utilities/ExtractArrayComponent) | [vtkArrayCalculator](http://www.vtk.org/doc/nightly/html/classvtkArrayCalculator.html) |Extract a component of an array.
[KnownLengthArrayOfVectors](/Cxx/Utilities/KnownLengthArrayOfVectors) | [vtkFloatArray](http://www.vtk.org/doc/nightly/html/classvtkFloatArray.html) |Array of Vectors (Known Length).
[KnownLengthArray](/Cxx/Utilities/KnownLengthArray) | [vtkFloatArray](http://www.vtk.org/doc/nightly/html/classvtkFloatArray.html) |Known Length Array.
[SortDataArray](/Cxx/Utilities/SortDataArray) | [vtkSortDataArray](http://www.vtk.org/doc/nightly/html/classvtkSortDataArray.html) | Reorder array values based on an ordering (key) array.
[SparseArray](/Cxx/Utilities/SparseArray) | [vtkSparseArray](http://www.vtk.org/doc/nightly/html/classvtkSparseArray.html) |Sparse Array.
[UnknownLengthArrayOfVectors](/Cxx/Utilities/UnknownLengthArrayOfVectors) | [vtkFloatArray](http://www.vtk.org/doc/nightly/html/classvtkFloatArray.html) |Array of Vectors (Unknown Length).
[UnknownLengthArray](/Cxx/Utilities/UnknownLengthArray) | [vtkFloatArray](http://www.vtk.org/doc/nightly/html/classvtkFloatArray.html) |Unknown Length Array.

##Events

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[CameraModifiedEvent](/Cxx/Utilities/CameraModifiedEvent) | [vtkCameraWindow](http://www.vtk.org/doc/nightly/html/classvtkCameraWindow.html) | Catch the camera modified event.
[ObserveError](/Cxx/Utilities/ObserveError) | [vtkCommand](http://www.vtk.org/doc/nightly/html/classvtkCommand.html) | Catch errors and warnings.
[WindowModifiedEvent](/Cxx/Utilities/WindowModifiedEvent) | [vtkRenderWindow](http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html) | Catch the window modified event.

#CMake Techniques

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[Check if a specific module is present](/Cxx/CMakeTechniques/CheckForModule) |  |
[Check VTK Version in CMake](/Cxx/Utilities/CMake[VTKVersionCheck](http://www.vtk.org/doc/nightly/html/classVTKVersionCheck.html)) |  | 


#Math Operations

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[EigenSymmetric](/Cxx/Math/EigenSymmetric)| [vtkMath](http://www.vtk.org/doc/nightly/html/classvtkMath.html)::Jacobi |Compute eigenvalues and eigenvectors of a symmetric matrix.
[HomogeneousLeastSquares](/Cxx/Math/HomogeneousLeastSquares)| [vtkMath](http://www.vtk.org/doc/nightly/html/classvtkMath.html)::SolveHomogeneousLeastSquares |Homogeneous Least Squares.
[1DTupleInterpolation](/Cxx/Math/1DTupleInterpolation)|[vtkTupleInterpolator](http://www.vtk.org/doc/nightly/html/classvtkTupleInterpolator.html) [vtkCardinalSpline](http://www.vtk.org/doc/nightly/html/classvtkCardinalSpline.html) [vtkKochanekSpline](http://www.vtk.org/doc/nightly/html/classvtkKochanekSpline.html) | A simple example demonstrating how functions defined by sparsely distributed supporting points can be interpolated at arbitrary positions.
[LUFactorization](/Cxx/Math/LUFactorization)| [vtkMath](http://www.vtk.org/doc/nightly/html/classvtkMath.html) |LU Factorization.
[LeastSquares](/Cxx/Math/LeastSquares)| [vtkMath](http://www.vtk.org/doc/nightly/html/classvtkMath.html)::SolveLeastSquares |Least Squares.
[MatrixInverse](/Cxx/Math/MatrixInverse)| [vtkMatrix3x3](http://www.vtk.org/doc/nightly/html/classvtkMatrix3x3.html) |Matrix inverse.
[MatrixTranspose](/Cxx/Math/MatrixTranspose)| [vtkMatrix3x3](http://www.vtk.org/doc/nightly/html/classvtkMatrix3x3.html) |Matrix transpose.
[NormalizeVector](/Cxx/Math/NormalizeVector)| [vtkMath](http://www.vtk.org/doc/nightly/html/classvtkMath.html) |Normalize a vector.
[PerpendicularVector](/Cxx/Math/PerpendicularVector) | [vtkMath](http://www.vtk.org/doc/nightly/html/classvtkMath.html)::Perpendiculars |Get a vector perpendicular to another vector.
[PowerWeighting](/Cxx/TextAnalysis/PowerWeighting)| [vtkPowerWeighting](http://www.vtk.org/doc/nightly/html/classvtkPowerWeighting.html) |Raise all elements in an array to a power.
[VectorDot](/Cxx/Math/VectorDot)| [vtkVectorDot](http://www.vtk.org/doc/nightly/html/classvtkVectorDot.html) |
[VectorNorm](/Cxx/Math/VectorNorm) |[vtkVectorNorm](http://www.vtk.org/doc/nightly/html/classvtkVectorNorm.html) |Get the lengths of an array of vectors.


#Graphs

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[AdjacencyMatrixToEdgeTable](/Cxx/Graphs/AdjacencyMatrixToEdgeTable)| [vtkAdjacencyMatrixToEdgeTable](http://www.vtk.org/doc/nightly/html/classvtkAdjacencyMatrixToEdgeTable.html) | Convert an adjacency matrix to an edge table.
[AdjacentVertexIterator](/Cxx/Graphs/AdjacentVertexIterator)| [vtkAdjacentVertexIterator](http://www.vtk.org/doc/nightly/html/classvtkAdjacentVertexIterator.html) |Get all vertices connected to a specified vertex.
[BFSTree](/Cxx/Graphs/BFSTree)| [vtkBoostBreadthFirstSearchTree](http://www.vtk.org/doc/nightly/html/classvtkBoostBreadthFirstSearchTree.html) | Breadth first search tree. Can also be used to convert a graph to a tree.
[BreadthFirstDistance](/Cxx/Graphs/BreadthFirstDistance)| [vtkBoostBreadthFirstSearch](http://www.vtk.org/doc/nightly/html/classvtkBoostBreadthFirstSearch.html) |Distance from origin.
[BreadthFirstSearchIterator](/Cxx/Graphs/BreadthFirstSearchIterator)| [vtkTreeBFSIterator](http://www.vtk.org/doc/nightly/html/classvtkTreeBFSIterator.html) |Breadth First Search iterator.
[ColorEdges](/Cxx/Graphs/ColorEdges)| [vtkGraphLayoutView](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html) |Color edges.
[ColorVertexLabels](/Cxx/Graphs/ColorVertexLabels)| [vtkGraphLayoutView](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html), [vtkRenderedGraphRepresentation](http://www.vtk.org/doc/nightly/html/classvtkRenderedGraphRepresentation.html) |Set the color of vertex labels.
[ColorVerticesLookupTable](/Cxx/Graphs/ColorVerticesLookupTable)| [vtkGraphLayoutView](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html) |Color vertices.
[ConnectedComponents](/Cxx/Graphs/ConnectedComponents)| [vtkBoostConnectedComponents](http://www.vtk.org/doc/nightly/html/classvtkBoostConnectedComponents.html) |Find connected components of a graph.
[ConstructGraph](/Cxx/Graphs/ConstructGraph)| [vtkMutableUndirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkMutableUndirectedGraph.html) |Construct a graph.
[ConstructTree](/Cxx/Graphs/ConstructTree)| [vtkTree](http://www.vtk.org/doc/nightly/html/classvtkTree.html), [vtkMutableDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html)  |Construct a tree.
[DFSAnimation](/Cxx/Graphs/DFSAnimation)| [vtkTreeDFSIterator](http://www.vtk.org/doc/nightly/html/classvtkTreeDFSIterator.html) |Depth First Search Animation.
[DepthFirstSearchIterator](/Cxx/Graphs/DepthFirstSearchIterator)| [vtkTreeDFSIterator](http://www.vtk.org/doc/nightly/html/classvtkTreeDFSIterator.html) |Depth First Search iterator.
[EdgeWeights](/Cxx/Graphs/EdgeWeights)| [vtkGraph](http://www.vtk.org/doc/nightly/html/classvtkGraph.html)::GetEdgeData::AddArray |Edge weights.
[GraphPoints](/Cxx/InfoVis/GraphPoints)| [vtkGraph](http://www.vtk.org/doc/nightly/html/classvtkGraph.html)::SetPoints, [vtkPassThroughLayoutStrategy](http://www.vtk.org/doc/nightly/html/classvtkPassThroughLayoutStrategy.html) |Manually set coordinates of vertices in a graph.
[GraphToPolyData](/Cxx/Graphs/GraphToPolyData)| [vtkGraphToPolyData](http://www.vtk.org/doc/nightly/html/classvtkGraphToPolyData.html) |Convert a graph to a PolyData.
[InEdgeIterator](/Cxx/Graphs/InEdgeIterator)| [vtkInEdgeIterator](http://www.vtk.org/doc/nightly/html/classvtkInEdgeIterator.html) |Iterate over edges incoming to a vertex.
[IterateEdges](/Cxx/Graphs/IterateEdges)| [vtkEdgeListIterator](http://www.vtk.org/doc/nightly/html/classvtkEdgeListIterator.html) |Iterate over edges of a graph.
[LabelVerticesAndEdges](/Cxx/Graphs/LabelVerticesAndEdges)| [vtkGraphLayoutView](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html)::SetEdgeLabelArrayName, [vtkGraphLayoutView](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html)::SetVertexLabelArrayName|Label vertices and edges.
[MinimumSpanningTree](/Cxx/Graphs/MinimumSpanningTree)| [vtkBoostPrimMinimumSpanningTree](http://www.vtk.org/doc/nightly/html/classvtkBoostPrimMinimumSpanningTree.html) |Minimum spanning tree of a graph.
[MutableGraphHelper](/Cxx/InfoVis/MutableGraphHelper)| [vtkMutableGraphHelper](http://www.vtk.org/doc/nightly/html/classvtkMutableGraphHelper.html) |Create either a [vtkMutableDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html) or [vtkMutableUndirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkMutableUndirectedGraph.html).
[NOVCAGraph](/Cxx/Graphs/NOVCAGraph)| [vtkUnstructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html), [vtkXMLUnstructuredGridWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLUnstructuredGridWriter.html), [vtkPolyLine](http://www.vtk.org/doc/nightly/html/classvtkPolyLine.html)|Create a graph & visualize it in ParaView/VisIt.
[OutEdgeIterator](/Cxx/Graphs/OutEdgeIterator)| [vtkOutEdgeIterator](http://www.vtk.org/doc/nightly/html/classvtkOutEdgeIterator.html) |Iterate over edges outgoing from a vertex.
[RandomGraphSource](/Cxx/Graphs/RandomGraphSource)| [vtkRandomGraphSource](http://www.vtk.org/doc/nightly/html/classvtkRandomGraphSource.html) |Create a random graph.
[RemoveIsolatedVertices](/Cxx/Graphs/RemoveIsolatedVertices)| [vtkRemoveIsolatedVertices](http://www.vtk.org/doc/nightly/html/classvtkRemoveIsolatedVertices.html) |Remove vertices of degree 0 from a [vtkGraph](http://www.vtk.org/doc/nightly/html/classvtkGraph.html).
[ScaleVertices](/Cxx/Graphs/ScaleVertices)| [vtkGraphLayoutView](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html), [vtkRenderedGraphRepresentation](http://www.vtk.org/doc/nightly/html/classvtkRenderedGraphRepresentation.html) |Size/scale vertices based on a data array.
[SelectedVerticesAndEdges ](/Cxx/Graphs/SelectedVerticesAndEdges)| [vtkAnnotationLink](http://www.vtk.org/doc/nightly/html/classvtkAnnotationLink.html) |Get a list of selected vertices and edges.
[SelectedVerticesAndEdgesObserver](/Cxx/Graphs/SelectedVerticesAndEdgesObserver)| [vtkAnnotationLink](http://www.vtk.org/doc/nightly/html/classvtkAnnotationLink.html) |Get a list of selected vertices and edges using an observer of AnnotationChangedEvent.
[ShortestPath](/Cxx/Graphs/ShortestPath)| [vtkDijkstraGraphGeodesicPath](http://www.vtk.org/doc/nightly/html/classvtkDijkstraGraphGeodesicPath.html) |Find the shortest path on a graph.
[SideBySideGraphs](/Cxx/Graphs/SideBySideGraphs)| [vtkGraphLayoutView](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html) |Display two graphs side by side.
[VertexSize](/Cxx/Graphs/VertexSize)| [vtkGraphLayoutView](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html), [vtkRenderedGraphRepresentation](http://www.vtk.org/doc/nightly/html/classvtkRenderedGraphRepresentation.html) | Set the size of vertices.
[VisualizeDirectedGraph](/Cxx/Graphs/VisualizeDirectedGraph)| [vtkGlyphSource2D](http://www.vtk.org/doc/nightly/html/classvtkGlyphSource2D.html) |Visualize a directed graph.
[VisualizeGraph](/Cxx/Graphs/VisualizeGraph)| [vtkGraphLayoutView](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html), [vtkGraphLayoutStrategy](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutStrategy.html), [vtkSimple2DLayoutStrategy](http://www.vtk.org/doc/nightly/html/classvtkSimple2DLayoutStrategy.html)|Visualize a graph.

##Graph Conversions

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[DirectedGraphToMutableDirectedGraph](/Cxx/Graphs/Conversions/DirectedGraphToMutableDirectedGraph)| [vtkMutableDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html), [vtkDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkDirectedGraph.html) | [vtkDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkDirectedGraph.html) to [vtkMutableDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html).
[MutableDirectedGraphToDirectedGraph](/Cxx/Graphs/Conversions/MutableDirectedGraphToDirectedGraph)| [vtkMutableDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html), [vtkDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkDirectedGraph.html) |[vtkMutableDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html) to [vtkDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkDirectedGraph.html).
[TreeToMutableDirectedGraph](/Cxx/Graphs/Conversions/TreeToMutableDirectedGraph)| [vtkMutableDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html), [vtkTree](http://www.vtk.org/doc/nightly/html/classvtkTree.html) | [vtkTree](http://www.vtk.org/doc/nightly/html/classvtkTree.html) to [vtkMutableDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html)

#Data Structures

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[AttachAttributes](/Cxx/PolyData/AttachAttributes)| [vtkInformation](http://www.vtk.org/doc/nightly/html/classvtkInformation.html) | Attach attributes to a VTK array
[CellLocatorVisualization](/Cxx/PolyData/CellLocatorVisualization)| [vtkCellLocator](http://www.vtk.org/doc/nightly/html/classvtkCellLocator.html) |Visualization of the tree of a [vtkCellLocator](http://www.vtk.org/doc/nightly/html/classvtkCellLocator.html).
[CellLocator](/Cxx/PolyData/CellLocator)| [vtkCellLocator](http://www.vtk.org/doc/nightly/html/classvtkCellLocator.html) | Project a point onto a mesh. Closest point on a mesh.Efficient 3D cell query.
[CellTreeLocator](/Cxx/PolyData/CellTreeLocator)| [vtkCellTreeLocator](http://www.vtk.org/doc/nightly/html/classvtkCellTreeLocator.html) |Points inside an object using [vtkCellTreeLocator](http://www.vtk.org/doc/nightly/html/classvtkCellTreeLocator.html).
[PointLocatorVisualization](/Cxx/PolyData/PointLocatorVisualization)| [vtkPointLocator](http://www.vtk.org/doc/nightly/html/classvtkPointLocator.html) |Visualization of the tree of a [vtkPointLocator](http://www.vtk.org/doc/nightly/html/classvtkPointLocator.html).
[PointLocator](/Cxx/PolyData/PointLocator)| [vtkPointLocator](http://www.vtk.org/doc/nightly/html/classvtkPointLocator.html) |Efficient 3D point query.
[Radius](/Cxx/PolyData/PointLocator_Radius)| [vtkPointLocator](http://www.vtk.org/doc/nightly/html/classvtkPointLocator.html) |Find all points within a radius of a specified point.


##Timing Demonstrations

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[KDTreeTimingDemo](/Cxx/DataStructures/KDTreeTimingDemo)| [vtkKdTreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkKdTreePointLocator.html) | Plot the runtime vs MaxLevel (doesn't seem correct)
[ModifiedBSPTreeTimingDemo](/Cxx/DataStructures/ModifiedBSPTreeTimingDemo)| [vtkModifiedBSPTree](http://www.vtk.org/doc/nightly/html/classvtkModifiedBSPTree.html) | Plot the runtime vs MaxLevel
[OBBTreeTimingDemo](/Cxx/DataStructures/OBBTreeTimingDemo)| [vtkOBBTree](http://www.vtk.org/doc/nightly/html/classvtkOBBTree.html) | Plot the runtime vs MaxLevel
[OctreeTimingDemo](/Cxx/DataStructures/OctreeTimingDemo)| [vtkOctreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkOctreePointLocator.html) | Plot the runtime vs MaxPointsPerRegionOctree timing demo.

##KD-Tree


| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[BuildLocatorFromKClosestPoints](/Cxx/DataStructures/BuildLocatorFromKClosestPoints)| [vtkKdTree](http://www.vtk.org/doc/nightly/html/classvtkKdTree.html) |
[ClosestNPoints](/Cxx/DataStructures/KdTreePointLocator/ClosestNPoints)| [vtkKdTreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkKdTreePointLocator.html) |Find the closest N points to a query point.
[DataStructureComparison](/Cxx/DataStructures/DataStructureComparison)| [vtkKdTree](http://www.vtk.org/doc/nightly/html/classvtkKdTree.html), [vtkOBBTree](http://www.vtk.org/doc/nightly/html/classvtkOBBTree.html), [vtkOctreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkOctreePointLocator.html), [vtkModifiedBSPTree](http://www.vtk.org/doc/nightly/html/classvtkModifiedBSPTree.html) | Illustrates, side by side, the differences between several spatial data structures
[KDTreeAccessPoints](/Cxx/DataStructures/KDTreeAccessPoints)| [vtkKdTree](http://www.vtk.org/doc/nightly/html/classvtkKdTree.html) |Access the points of a KDTree.
[KDTreeFindPointsWithinRadius](/Cxx/DataStructures/KDTreeFindPointsWithinRadius) | [vtkKdTreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkKdTreePointLocator.html) |Find points within a specified radius of  a query point.
[KdTreePointLocatorClosestPoint](/Cxx/DataStructures/KdTreePointLocatorClosestPoint)| [vtkKdTreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkKdTreePointLocator.html) |Find the closest point to a query point.
[KdTree](/Cxx/DataStructures/KdTree)| [vtkKdTree](http://www.vtk.org/doc/nightly/html/classvtkKdTree.html) |
[VisualizeKDTree](/Cxx/DataStructures/VisualizeKDTree)| [vtkKdTreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkKdTreePointLocator.html) |Visualize levels of the tree.


##Oriented Bounding Box (OBB) Tree


| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[IntersectWithLine](/Cxx/DataStructures/OBBTree_IntersectWithLine)| [vtkOBBTree](http://www.vtk.org/doc/nightly/html/classvtkOBBTree.html) |Intersect a line with a [vtkOBBTree](http://www.vtk.org/doc/nightly/html/classvtkOBBTree.html).
[OBBTreeExtractCells](/Cxx/DataStructures/OBBTreeExtractCells)| [vtkOBBTree](http://www.vtk.org/doc/nightly/html/classvtkOBBTree.html) |Intersect a line with an OBB Tree and display all intersected cells.
[VisualizeOBBTree](/Cxx/DataStructures/VisualizeOBBTree) | [vtkOBBTree](http://www.vtk.org/doc/nightly/html/classvtkOBBTree.html) |Visualize levels of the tree.

##Octree

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[BuildTree](/Cxx/DataStructures/Octree/BuildTree)| [vtkOctreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkOctreePointLocator.html) |Create an octree.
[ClosestPoint](/Cxx/DataStructures/Octree/ClosestPoint)| [vtkOctreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkOctreePointLocator.html) |Find the closest point to a query point.
[FindPointsWithinRadius](/Cxx/DataStructures/Octree/FindPointsWithinRadius)| [vtkOctreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkOctreePointLocator.html) |Find the points within a sphere of specified radius to a query point.
[IncrementalOctreePointLocator](/Cxx/DataStructures/IncrementalOctreePointLocator)|[vtkIncrementalOctreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkIncrementalOctreePointLocator.html) | Insert points into an octree without rebuilding it.
[KClosestPoints](/Cxx/DataStructures/Octree/KClosestPoints)| [vtkOctreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkOctreePointLocator.html) |Find the K closest points to a query point.
[OctreeVisualize](/Cxx/DataStructures/OctreeVisualize)|[vtkOctreePointLocator](http://www.vtk.org/doc/nightly/html/classvtkOctreePointLocator.html) |Visualize levels of the tree.


##Modified BSP Tree


| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[ModifiedBSPTreeIntersectWithLine](/Cxx/DataStructures/ModifiedBSPTreeIntersectWithLine)| [vtkModifiedBSPTree](http://www.vtk.org/doc/nightly/html/classvtkModifiedBSPTree.html) |Intersect a line with a modified BSP Tree.
[ModifiedBSPTreeExtractCells](/Cxx/DataStructures/ModifiedBSPTreeExtractCells)| [vtkModifiedBSPTree](http://www.vtk.org/doc/nightly/html/classvtkModifiedBSPTree.html) |Intersect a line with a modified BSP Tree and display all intersected cells.
[VisualizeModifiedBSPTree](/Cxx/DataStructures/ModifiedBSPTree/VisualizeModifiedBSPTree)| [vtkModifiedBSPTree](http://www.vtk.org/doc/nightly/html/classvtkModifiedBSPTree.html) |Visualize levels of the tree.


#VTK Concepts


| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[Scalars](/Cxx/[VTKConcepts](http://www.vtk.org/doc/nightly/html/classVTKConcepts.html)/Scalars)| |Attach a scalar value to each point (PointData) or cell (CellData) in a data set.


#Rendering

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[AmbientSpheres](/Cxx/Rendering/AmbientSpheres)| [vtkProperty](http://www.vtk.org/doc/nightly/html/classvtkProperty.html) |Demonstrates the effect of ambient lighting on spheres.
[DiffuseSpheres](/Cxx/Rendering/DiffuseSpheres)| [vtkProperty](http://www.vtk.org/doc/nightly/html/classvtkProperty.html) |Demonstrates the effect of diffuse lighting on spheres.
[SpecularSpheres](/Cxx/Rendering/SpecularSpheres)| [vtkProperty](http://www.vtk.org/doc/nightly/html/classvtkProperty.html) |Demonstrates the effect of specular lighting on spheres.
[CylinderRenderingProperties](/Cxx/Rendering/CylinderRenderingProperties)| [vtkProperty](http://www.vtk.org/doc/nightly/html/classvtkProperty.html) |Change the properties of a cylinder.


#Lighting


| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[Shadows](/Cxx/Visualization/Shadows)| [vtkShadowMapPass](http://www.vtk.org/doc/nightly/html/classvtkShadowMapPass.html) |Create shadows.
[Light](/Cxx/Lighting/Light)| [vtkLight](http://www.vtk.org/doc/nightly/html/classvtkLight.html) |Add a directional light to a scene.
[LightActor](/Cxx/Lighting/LightActor)| [vtkLightActor](http://www.vtk.org/doc/nightly/html/classvtkLightActor.html) |Display the location and direction of a light.


#Visualization
See [this tutorial](http://www.vtk.org/Wiki/VTK/Tutorials/3DDataTypes) for a brief explanation of the VTK terminology of mappers, actors, etc.


| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[ BillboardTextActor3D](/Cxx/Visualization/BillboardTextActor3D) | [vtkBillboardTextActor3D](http://www.vtk.org/doc/nightly/html/classvtkBillboardTextActor3D.html) | Label points with billboards.
[ CameraActor](/Cxx/Visualization/CameraActor) | [vtkCameraActor](http://www.vtk.org/doc/nightly/html/classvtkCameraActor.html) | Visualize a camera (frustum) in a scene.
[ DistanceToCamera](/Cxx/Visualization/DistanceToCamera) | [vtkDistanceToCamera](http://www.vtk.org/doc/nightly/html/classvtkDistanceToCamera.html) |
[ FindCellIntersections](/Cxx/VisualizationAlgorithms/FindCellIntersections) | [vtkCellLocator](http://www.vtk.org/doc/nightly/html/classvtkCellLocator.html) | Find the intersection of a line and the cells in an unstructured dataset
[ FlatShading](/Cxx/Visualization/FlatShading) | [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html)::GetProperty::SetInterpolationToFlat |
[ Legend](/Cxx/Visualization/Legend) | [vtkLegendBoxActor](http://www.vtk.org/doc/nightly/html/classvtkLegendBoxActor.html) |
[ NoShading](/Cxx/Visualization/NoShading) | [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html)::GetProperty::SetAmbient, [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html)::GetProperty::SetDiffuse, [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html)::GetProperty::SetSpecular |
[ PointSize](/Cxx/Visualization/PointSize) | [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html)::GetProperty::SetPointSize |
[Arbitrary3DCursor](/Cxx/Visualization/Arbitrary3DCursor)| [vtkPointWidget](http://www.vtk.org/doc/nightly/html/classvtkPointWidget.html) |Track a 3D cursor.
[AssignColorsFromLUT](/Cxx/Visualization/AssignColorsFromLUT)| [vtkNamedColors](http://www.vtk.org/doc/nightly/html/classvtkNamedColors.html), [vtkPlaneSource](http://www.vtk.org/doc/nightly/html/classvtkPlaneSource.html), [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html), [vtkColorTransferFunction](http://www.vtk.org/doc/nightly/html/classvtkColorTransferFunction.html) | Demonstrates how to assign colors to cells in a [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html) structure using lookup tables.
[BackfaceCulling](/Cxx/Visualization/BackfaceCulling)| [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html)::GetProperty::BackfaceCullingOn | Backface culling.
[BackgroundColor ](/Cxx/Visualization/BackgroundColor) | [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html)::SetBackground | Background color.
[BackgroundGradient ](/Cxx/Visualization/BackgroundGradient) | [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html)::GradientBackgroundOn, [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html)::Setbackground2 | Background gradient.
[BackgroundTexture](/Cxx/Visualization/BackgroundTexture)| [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html), [vtkTexture](http://www.vtk.org/doc/nightly/html/classvtkTexture.html) |Use a texture for the background of a [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html).
[Camera](/Cxx/Visualization/Camera)| [vtkCamera](http://www.vtk.org/doc/nightly/html/classvtkCamera.html) |Positioning and aiming the camera.
[CaptionActor2D](/Cxx/Visualization/CaptionActor2D)| [vtkCaptionActor2D](http://www.vtk.org/doc/nightly/html/classvtkCaptionActor2D.html) |Draw a caption/bubble pointing to a particular point.
[ClipArt ](/Cxx/Visualization/ClipArt) | [vtkTextureMapToPlane](http://www.vtk.org/doc/nightly/html/classvtkTextureMapToPlane.html) | Generate 3D clip art from an image.
[CloseWindow](/Cxx/Visualization/CloseWindow)| [vtkRenderWindowInteractor](http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html)::TerminateApp, [vtkRenderWindow](http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html)::Finalize |Close a render window.
[ColorActorEdges ](/Cxx/Visualization/ColorActorEdges) | [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html)::GetProperty::SetEdgeColor | Color the edges of an Actor.
[ColorAnActor ](/Cxx/Visualization/ColorAnActor) | [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html)::GetProperty::SetColor | Color an Actor.
[ColorGlyphs](/Cxx/Visualization/ColorGlyphs)| [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html) [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html)::SetColorModeToColorByScalar |Color glyphs.
[CornerAnnotation](/Cxx/Visualization/CornerAnnotation)| [vtkCornerAnnotation](http://www.vtk.org/doc/nightly/html/classvtkCornerAnnotation.html) | Write text in the corners of a window.
[CorrectlyRenderingTranslucentGeometry](/Cxx/Visualization/CorrectlyRenderingTranslucentGeometry)| [vtkDepthSortPolyData](http://www.vtk.org/doc/nightly/html/classvtkDepthSortPolyData.html) |Correctly Rendering Translucent Geometry.
[CubeAxesActor2D](/Cxx/Visualization/CubeAxesActor2D)| [vtkCubeAxesActor2D](http://www.vtk.org/doc/nightly/html/classvtkCubeAxesActor2D.html) | This example uses the [vtkCubeAxesActor2D](http://www.vtk.org/doc/nightly/html/classvtkCubeAxesActor2D.html) to show your scene with axes to indicate the spatial extent of your data.
[CubeAxesActor](/Cxx/Visualization/CubeAxesActor)| [vtkCubeAxesActor](http://www.vtk.org/doc/nightly/html/classvtkCubeAxesActor.html) |Display three orthogonal axes with labels.
[Cursor3D](/Cxx/Visualization/Cursor3D)| [vtkCursor3D](http://www.vtk.org/doc/nightly/html/classvtkCursor3D.html) |
[CursorShape](/Cxx/Visualization/CursorShape)| [vtkRenderWindow](http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html) |Change the shape of the cursor.
[CurvatureBandsWithGlyphs](/Cxx/Visualization/CurvatureBandsWithGlyphs)| [vtkCurvatures](http://www.vtk.org/doc/nightly/html/classvtkCurvatures.html), [vtkBandedPolyDataContourFilter](http://www.vtk.org/doc/nightly/html/classvtkBandedPolyDataContourFilter.html), [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html), [vtkColorSeries](http://www.vtk.org/doc/nightly/html/classvtkColorSeries.html), [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html) | Demonstrates the coloring of a surface by partitioning the gaussian curvature of a surface into bands and using arrows to display the normals on the surface.
[CurvedReformation ](/Cxx/Visualization/CurvedReformation) | [vtkProbeFilter](http://www.vtk.org/doc/nightly/html/classvtkProbeFilter.html)| Sample a volume with a curved surface. In medical imaging, this is often called curved multi planar reformation.
[Cutter](/Cxx/VisualizationAlgorithms/Cutter)| [vtkCutter](http://www.vtk.org/doc/nightly/html/classvtkCutter.html) |
[DisplayCoordinateAxes](/Cxx/Visualization/DisplayCoordinateAxes)| [vtkOrientationMarkerWidget](http://www.vtk.org/doc/nightly/html/classvtkOrientationMarkerWidget.html) |Display coordinate axes.
[DisplayQuadraticSurfaces](/Cxx/Visualization/DisplayQuadraticSurfaces)| [vtkQuadric](http://www.vtk.org/doc/nightly/html/classvtkQuadric.html), [vtkSampleFunction](http://www.vtk.org/doc/nightly/html/classvtkSampleFunction.html), [vtkContourFilter](http://www.vtk.org/doc/nightly/html/classvtkContourFilter.html) |Display Quadratic Surfaces.
[DisplayText](/Cxx/Visualization/DisplayText)| [vtkTextActor](http://www.vtk.org/doc/nightly/html/classvtkTextActor.html), [vtkTextProperty](http://www.vtk.org/doc/nightly/html/classvtkTextProperty.html) |Display Text.
[ElevationBandsWithGlyphs](/Cxx/Visualization/ElevationBandsWithGlyphs)| [vtkBandedPolyDataContourFilter](http://www.vtk.org/doc/nightly/html/classvtkBandedPolyDataContourFilter.html), [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html), [vtkColorSeries](http://www.vtk.org/doc/nightly/html/classvtkColorSeries.html), [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html) | Demonstrates the coloring of a surface by partitioning the elevation into bands and using arrows to display the normals on the surface.
[FastSplatter](/Cxx/Visualization/FastSplatter)| [vtkFastSplatter](http://www.vtk.org/doc/nightly/html/classvtkFastSplatter.html) |Convolve a splat image with every point in an input image.
[Follower ](/Cxx/Visualization/Follower) | [vtkFollower](http://www.vtk.org/doc/nightly/html/classvtkFollower.html) | Draw text that stays right side up.
[Glyph2D ](/Cxx/Filtering/Glyph2D) | [vtkGlyph2D](http://www.vtk.org/doc/nightly/html/classvtkGlyph2D.html)|
[Glyph3D ](/Cxx/Filtering/Glyph3D) | [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html)|
[Glyph3DMapper](/Cxx/Visualization/Glyph3DMapper)| [vtkGlyph3DMapper](http://www.vtk.org/doc/nightly/html/classvtkGlyph3DMapper.html) |
[HedgeHog](/Cxx/Visualization/HedgeHog)| [vtkHedgeHog](http://www.vtk.org/doc/nightly/html/classvtkHedgeHog.html), [vtkStructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkStructuredGrid.html) |Create oriented lines (hedgehogs) from vector data.
[Hide an actor](/Cxx/Visualization/HideActor)| [vtkPropCollection](http://www.vtk.org/doc/nightly/html/classvtkPropCollection.html), [vtkProp](http://www.vtk.org/doc/nightly/html/classvtkProp.html)::VisibilityOff | visible
[HideAllActors](/Cxx/Visualization/HideAllActors)| [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html)::RemoveAllViewProps |Hide all actors.
[ImageMapper](/Cxx/Visualization/ImageMapper)| [vtkImageMapper](http://www.vtk.org/doc/nightly/html/classvtkImageMapper.html) | Display an image in 2D.
[ImageOrder](/Cxx/Visualization/ImageOrder)| [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html) |Determine the display order of a stack of images.
[ImageOrientation ](/Cxx/Visualization/ImageOrientation) | [vtkInteractorStyleImage](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleImage.html) |Orientation of the view of an image.
[ImageTransparency](/Cxx/Visualization/ImageTransparency)| [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html)|Set transparency of image pixels.
[IsosurfaceSampling ](/Cxx/Visualization/IsosurfaceSampling) | [vtkProbeFilter](http://www.vtk.org/doc/nightly/html/classvtkProbeFilter.html)|Demonstrates how to create point data on an isosurface.
[LODProp3D ](/Cxx/Visualization/LODProp3D) | [vtkLODProp3D](http://www.vtk.org/doc/nightly/html/classvtkLODProp3D.html) | Level of detail rendering.
[LabelContours](/Cxx/Visualization/LabelContours)| [vtkLabeledDataMapper](http://www.vtk.org/doc/nightly/html/classvtkLabeledDataMapper.html) |Label Contours.
[LabelMesh ](/Cxx/Visualization/LabelMesh) | [vtkLabeledDataMapper](http://www.vtk.org/doc/nightly/html/classvtkLabeledDataMapper.html) | Label Mesh.
[LabelPlacementMapper](/Cxx/Visualization/LabelPlacementMapper)| [vtkPointSetToLabelHierarchy](http://www.vtk.org/doc/nightly/html/classvtkPointSetToLabelHierarchy.html), [vtkLabelPlacementMapper](http://www.vtk.org/doc/nightly/html/classvtkLabelPlacementMapper.html) | Display a non-overlapping text label at each point.
[LabeledDataMapper](/Cxx/Visualization/LabeledDataMapper)| [vtkLabeledDataMapper](http://www.vtk.org/doc/nightly/html/classvtkLabeledDataMapper.html) |Display the point ID at each point.
[LayeredRenderers](/Cxx/WishList/Visualization/LayeredRenderers)| [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html) | Layered renderers.
[LegendScaleActor](/Cxx/Visualization/LegendScaleActor)| [vtkLegendScaleActor](http://www.vtk.org/doc/nightly/html/classvtkLegendScaleActor.html) |Display the scale of a scene.
[LineWidth](/Cxx/Visualization/LineWidth)| [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html), [vtkProperty](http://www.vtk.org/doc/nightly/html/classvtkProperty.html) |Change the width/thickness of lines in an actor.
[MovableAxes ](/Cxx/Visualization/MovableAxes) | [vtkFollower](http://www.vtk.org/doc/nightly/html/classvtkFollower.html), [vtkAxesActor](http://www.vtk.org/doc/nightly/html/classvtkAxesActor.html), [vtkAssembly](http://www.vtk.org/doc/nightly/html/classvtkAssembly.html) | Movable axes.
[MoveActor](/Cxx/Visualization/MoveActor)| [vtkInteractorStyleTrackballActor](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballActor.html) |Moving an Actor.
[MoveCamera](/Cxx/Visualization/MoveCamera)| [vtkInteractorStyleTrackballCamera](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballCamera.html) |Moving the Camera.
[MultipleActors](/Cxx/Visualization/MultipleActors)| [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html) |Multiple Actors.
[NamedColorPatches ](/Cxx/Visualization/NamedColorPatches) | [vtkNamedColors](http://www.vtk.org/doc/nightly/html/classvtkNamedColors.html) | Creates a HTML file called [VTKNamedColorPatches.html](Python/Visualization/VTKNamedColorPatches.html) showing the available colors in the vtkNamedColors class.
[NamedColors ](/Cxx/Visualization/NamedColors) | [vtkNamedColors](http://www.vtk.org/doc/nightly/html/classvtkNamedColors.html) | Demonstrates how to use the [vtkNamedColor](http://www.vtk.org/doc/nightly/html/classvtkNamedColor.html) class.
[Opacity](/Cxx/Visualization/Opacity)| [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html)::GetProperty::SetOpacity | Transparency, transparent.
[OrientedGlyphs](/Cxx/Visualization/OrientedGlyphs)| [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html)|Create oriented glyphs from vector data.
[PolyDataDepthSorting](/Cxx/Visualization/PolyDataDepthSorting)| [vtkDepthSortPolyData](http://www.vtk.org/doc/nightly/html/classvtkDepthSortPolyData.html) |Poly Data Depth Sorting.
[ProgrammableGlyphFilter](/Cxx/Visualization/ProgrammableGlyphFilter)| [vtkProgrammableGlyphFilter](http://www.vtk.org/doc/nightly/html/classvtkProgrammableGlyphFilter.html) |Generate a custom glyph at each point.
[QuadraticSurface](/Cxx/Visualization/QuadraticSurface)| [vtkQuadric](http://www.vtk.org/doc/nightly/html/classvtkQuadric.html) |Display a quadratic surface.
[QuadricLODActor](/Cxx/Visualization/QuadricLODActor)| [vtkQuadricLODActor](http://www.vtk.org/doc/nightly/html/classvtkQuadricLODActor.html) | Level of detail adjustment.
[RandomProbe](/Cxx/Visualization/RandomProbe)| [vtkProbeFilter](http://www.vtk.org/doc/nightly/html/classvtkProbeFilter.html)|Demonstrates how to probe a dataset with random points and select points inside the data set.
[RenderLargeImage](/Cxx/Visualization/RenderLargeImage)| [vtkRenderLargeImage](http://www.vtk.org/doc/nightly/html/classvtkRenderLargeImage.html) |Render a large image, larger than a window.
[RenderPassExistingContext](/Cxx/Visualization/RenderPassExistingContext)| [vtkRenderPass](http://www.vtk.org/doc/nightly/html/classvtkRenderPass.html),[vtkVolumetricPass](http://www.vtk.org/doc/nightly/html/classvtkVolumetricPass.html) |Render into an existing OpenGL Context.
[RenderView](/Cxx/Views/RenderView)| [vtkRenderView](http://www.vtk.org/doc/nightly/html/classvtkRenderView.html) |A little bit easier rendering.
[ReverseAccess ](/Cxx/Visualization/ReverseAccess) | [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html)|Demonstrates how to access the source (e.g. [vtkSphereSource](http://www.vtk.org/doc/nightly/html/classvtkSphereSource.html)) of an actor reversely.
[RotateActor](/Cxx/Visualization/RotateActor)| [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html)::GetMatrix |Rotate an Actor.
[ScalarBarActor](/Cxx/Visualization/ScalarBarActor)| [vtkScalarBarActor](http://www.vtk.org/doc/nightly/html/classvtkScalarBarActor.html) | Display a color bar.
[ScalarVisibility](/Cxx/Visualization/ScalarVisibility)| [vtkDataSetMapper](http://www.vtk.org/doc/nightly/html/classvtkDataSetMapper.html) | Switch between coloring the actor and coloring the data.
[ScaleGlyphs](/Cxx/Visualization/ScaleGlyphs)| [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html) [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html)::SetScaleModeToScaleByScalar |Scale glyphs.
[SceneBounds](/Cxx/Visualization/SceneBounds)| [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html) |Get the bounds of the whole scene.
[SelectWindowRegion](/Cxx/Visualization/SelectWindowRegion)|[vtkInteractorStyleRubberBand2D](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleRubberBand2D.html) |Select a region of a window.
[StreamLines](/Cxx/Visualization/StreamLines)| [vtkStreamLine](http://www.vtk.org/doc/nightly/html/classvtkStreamLine.html) |Stream Lines.
[TensorGlyph](Visualization/TensorGlyph)| [vtkTensorGlyph](http://www.vtk.org/doc/nightly/html/classvtkTensorGlyph.html) | Draw a rotated/scaled glyph at each point.
[TextSource](/Cxx/Visualization/TextSource)| [vtkTextSource](http://www.vtk.org/doc/nightly/html/classvtkTextSource.html) |Display text.
[TextureMapImageData ](/Cxx/Visualization/TextureMapImageData) | [vtkImageCanvasSource2D](http://www.vtk.org/doc/nightly/html/classvtkImageCanvasSource2D.html) | Texture map an ImageData.
[TextureMapPlane](/Cxx/Visualization/TextureMapPlane)| [vtkTextureMapToPlane](http://www.vtk.org/doc/nightly/html/classvtkTextureMapToPlane.html) |Texture map a plane.
[TextureMapQuad](/Cxx/Visualization/TextureMapQuad)| [vtkPolygon](http://www.vtk.org/doc/nightly/html/classvtkPolygon.html), [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html)::GetPointData::SetTCoords |Texture map a quad.
[TransformActorCollection](/Cxx/Visualization/TransformActorCollection)| [vtkActorCollection](http://www.vtk.org/doc/nightly/html/classvtkActorCollection.html) |Transform an actor collection.
[TransformActor](/Cxx/Visualization/TransformActor)| [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html)::SetUserTransform |Transform an Actor.
[TubesFromSplines](/Cxx/VisualizationAlgorithms/TubesFromSplines)| [vtkTubeFilter](http://www.vtk.org/doc/nightly/html/classvtkTubeFilter.html), [vtkParametricFunctionSource](http://www.vtk.org/doc/nightly/html/classvtkParametricFunctionSource.html)  [vtkTupleInterpolator](http://www.vtk.org/doc/nightly/html/classvtkTupleInterpolator.html)|Create tubes from interpolated points and scalars.
[TubesWithVaryingRadiusAndColors](/Cxx/VisualizationAlgorithms/TubesWithVaryingRadiusAndColors)| [vtkTubeFilter](http://www.vtk.org/doc/nightly/html/classvtkTubeFilter.html) |Create tubes with varying radius and colors.
[VectorField ](/Cxx/WishList/Visualization/VectorField) | [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html) | Visualize a vector field.
[VectorOfActors](/Cxx/Visualization/VectorOfActors)| [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html) |Multiple Actors in a Vector.
[VectorText](/Cxx/Visualization/VectorText)| [vtkVectorText](http://www.vtk.org/doc/nightly/html/classvtkVectorText.html) |Display high resolution text.
[VertexGlyphFilter ](/Cxx/Filtering/VertexGlyphFilter) | [vtkVertexGlyphFilter](http://www.vtk.org/doc/nightly/html/classvtkVertexGlyphFilter.html) | Add a vertex to each point.
[Visualize2DPoints](/Cxx/Visualization/Visualize2DPoints)| [vtkPolyDataMapper2D](http://www.vtk.org/doc/nightly/html/classvtkPolyDataMapper2D.html), [vtkProperty2D](http://www.vtk.org/doc/nightly/html/classvtkProperty2D.html) |Visualize a 2D Set of Points.
[VisualizeImageData](/Cxx/Visualization/VisualizeImageData)| [vtkDataSetMapper](http://www.vtk.org/doc/nightly/html/classvtkDataSetMapper.html) |Visualize the points of an ImageData.
[VisualizeVTP](/Cxx/Visualization/VisualizeVTP)| [vtkXMLPolyDataReader](http://www.vtk.org/doc/nightly/html/classvtkXMLPolyDataReader.html), [vtkPolyDataMapper](http://www.vtk.org/doc/nightly/html/classvtkPolyDataMapper.html) |Visualize a VTP File.
[WindowSize](/Cxx/Visualization/WindowSize)| [vtkRenderWindow](http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html):SetSize | Change the size of a window.
[WindowTitle](/Cxx/Visualization/WindowTitle)| [vtkRenderWindow](http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html)::SetWindowName | Change the title of a window.
[Wireframe](/Cxx/Visualization/Wireframe)| [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html)::GetProperty::SetRepresentationToWireframe |
[a KochSnowflake](/Cxx/Visualization/KochSnowflake) | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html), [vtkPolyLine](http://www.vtk.org/doc/nightly/html/classvtkPolyLine.html), [vtkTriangle](http://www.vtk.org/doc/nightly/html/classvtkTriangle.html), [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html),| Use recursion to represent a Koch snowflake fractal.

#Volume Rendering


| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[HAVS](/Cxx/VolumeRendering/HAVSVolumeMapper)| [vtkHAVSVolumeMapper](http://www.vtk.org/doc/nightly/html/classvtkHAVSVolumeMapper.html) |
[MinIntensityRendering](/Cxx/VolumeRendering/MinIntensityRendering)| [vtkFixedPointVolumeRayCastMapper](http://www.vtk.org/doc/nightly/html/classvtkFixedPointVolumeRayCastMapper.html) |Min intensity rendering.
[SmartVolumeMapper](/Cxx/VolumeRendering/SmartVolumeMapper)| [vtkSmartVolumeMapper](http://www.vtk.org/doc/nightly/html/classvtkSmartVolumeMapper.html) |Smart volume mapper.
[itk[VtkImageConvert](http://www.vtk.org/doc/nightly/html/classVtkImageConvert.html)](/Cxx/VolumeRendering/itk[VtkImageConvert](http://www.vtk.org/doc/nightly/html/classVtkImageConvert.html))|  | Conversion maintaining DICOM orientation and positionITK->VTK conversion.


#User Interaction

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[AreaPicking](/Cxx/Picking/AreaPicking)| [vtkAreaPicker](http://www.vtk.org/doc/nightly/html/classvtkAreaPicker.html) |Area Picking.
[Assembly](/Cxx/Interaction/Assembly)| [vtkAssembly](http://www.vtk.org/doc/nightly/html/classvtkAssembly.html) | Combine/group actors into an assembly.
[CallData](/Cxx/Interaction/CallData)| [vtkCommand](http://www.vtk.org/doc/nightly/html/classvtkCommand.html) | Pass an observer a value (via CallData).
[CellPicking](/Cxx/Picking/CellPicking)| [vtkCellPicker](http://www.vtk.org/doc/nightly/html/classvtkCellPicker.html) | Cell Picking.
[ClientData](/Cxx/Interaction/ClientData)| [vtkCommand](http://www.vtk.org/doc/nightly/html/classvtkCommand.html) | Give an observer access to an object (via ClientData).
[DoubleClick](/Cxx/Interaction/DoubleClick)| [vtkInteractorStyleTrackballCamera](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballCamera.html) |Catch a double click.
[Game](/Cxx/Interaction/Game)| [vtkInteractorStyleTrackballActor](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballActor.html) | Move a cube into a sphere.
[HighlightPickedActor](/Cxx/Picking/HighlightPickedActor)| [vtkPropPicker](http://www.vtk.org/doc/nightly/html/classvtkPropPicker.html) |Highlight a picked actor.
[HighlightSelectedPoints](/Cxx/Picking/HighlightSelectedPoints)| [vtkExtractGeometry](http://www.vtk.org/doc/nightly/html/classvtkExtractGeometry.html) |Highlight Selected Points.
[HighlightSelection](/Cxx/Picking/HighlightSelection)| [vtkExtractPolyDataGeometry](http://www.vtk.org/doc/nightly/html/classvtkExtractPolyDataGeometry.html) |Highlight selection.
[ImageClip](/Cxx/Interaction/ImageClip)| [vtkImageClip](http://www.vtk.org/doc/nightly/html/classvtkImageClip.html) | Demonstrates how to interactively select and display a region of an image.
[ImageRegion](/Cxx/Interaction/ImageRegion)| [vtkCommand](http://www.vtk.org/doc/nightly/html/classvtkCommand.html) |Select a region of an image.
[InteractorStyleTerrain](/Cxx/Interaction/InteractorStyleTerrain)| [vtkInteractorStyleTerrain](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTerrain.html) |Terrain mode.
[InteractorStyleUser](/Cxx/Interaction/InteractorStyleUser)| [vtkInteractorStyleUser](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleUser.html) | Create a completely custom interactor style (no default functionality is provided)
[KeypressEvents](/Cxx/Interaction/KeypressEvents)| [vtkInteractorStyleTrackballCamera](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballCamera.html) |Handle keypress events.
[KeypressObserver ](/Cxx/Interaction/KeypressObserver) | [vtkCallbackCommand](http://www.vtk.org/doc/nightly/html/classvtkCallbackCommand.html) | This uses a callback function rather than a derived interactor class. Handle keypress events (lightweight).
[MouseEvents ](/Cxx/Interaction/MouseEvents) | [vtkInteractorStyleTrackballCamera](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballCamera.html) | Subclass the interactor style. Handle mouse events.
[MouseEventsObserver ](/Cxx/Interaction/MouseEventsObserver) | [vtkCallbackCommand](http://www.vtk.org/doc/nightly/html/classvtkCallbackCommand.html) | Use an observer. Handle mouse events (light weight).
[MoveAGlyph](/Cxx/Interaction/MoveAGlyph)| [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html) | Drag a glyph around.
[MoveAVertexUnstructuredGrid](/Cxx/Interaction/MoveAVertexUnstructuredGrid)| [vtkPointPicker](http://www.vtk.org/doc/nightly/html/classvtkPointPicker.html) | Click and drag a vertex of a [vtkUnstructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html).
[MoveAVertex](/Cxx/Interaction/MoveAVertex)| [vtkPointPicker](http://www.vtk.org/doc/nightly/html/classvtkPointPicker.html) | Click and drag a vertex of a [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html).
[ObserverMemberFunction](/Cxx/Interaction/ObserverMemberFunction)|  | Set observers to be class member functions.
[PickableOff](/Cxx/Interaction/PickableOff)| [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html)::PickableOff |Disallow interaction with a specific actor.
[Picking](/Cxx/Interaction/Picking)| [vtkPropPicker](http://www.vtk.org/doc/nightly/html/classvtkPropPicker.html) | Get the world coordinate of the mouse click (if you clicked an actor)
[PointPicker](/Cxx/Interaction/PointPicker)| [vtkPointPicker](http://www.vtk.org/doc/nightly/html/classvtkPointPicker.html) | Get the coordinates of the closest point in the data set to the mouse click.
[RubberBand2DObserver](/Cxx/Interaction/RubberBand2DObserver)| [vtkInteractorStyleRubberBand2D](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleRubberBand2D.html) |RubberBand2D Observer.
[RubberBand2D](/Cxx/Interaction/RubberBand2D)| [vtkInteractorStyleRubberBand2D](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleRubberBand2D.html) |
[RubberBand3D](/Cxx/Interaction/RubberBand3D)| [vtkInteractorStyleRubberBand3D](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleRubberBand3D.html) |
[RubberBandPick](/Cxx/Interaction/RubberBandPick)| [vtkInteractorStyleRubberBandPick](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleRubberBandPick.html) |
[RubberBandZoom](/Cxx/Interaction/RubberBandZoom)| [vtkInteractorStyleRubberBandZoom](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleRubberBandZoom.html) |
[SelectAnActor](/Cxx/Interaction/SelectAnActor)| [vtkPropPicker](http://www.vtk.org/doc/nightly/html/classvtkPropPicker.html) |Select an actor.
[ShiftAndControl](/Cxx/Interaction/ShiftAndControl)| [vtkRenderWindowInteractor](http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html)::GetControlKey() | Hold/holding down a key. Check if shift or control is being held.
[StyleSwitch](/Cxx/Interaction/StyleSwitch)| [vtkInteractorStyleSwitch](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleSwitch.html) |Choose between multiple interaction modes.
[TrackballActor](/Cxx/Interaction/TrackballActor)| [vtkInteractorStyleTrackballActor](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballActor.html) |Trackball actor mode.
[TrackballCamera](/Cxx/Interaction/TrackballCamera)| [vtkInteractorStyleTrackballCamera](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballCamera.html) |Trackball camera mode.
[UserEvent](/Cxx/Interaction/UserEvent)|  | Simple observer. Create, invoke, and handle a custom event.
[WorldPointPicker](/Cxx/Interaction/WorldPointPicker)| [vtkWorldPointPicker](http://www.vtk.org/doc/nightly/html/classvtkWorldPointPicker.html) |Get world coordinates of mouse click.


#Working with Images

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[Actor2D](/Cxx/Images/Actor2D)| [vtkActor2D](http://www.vtk.org/doc/nightly/html/classvtkActor2D.html) [vtkMapper2D](http://www.vtk.org/doc/nightly/html/classvtkMapper2D.html) |2D actor and mapper.
[BackgroundImage](/Cxx/Images/BackgroundImage)|  [vtkImageCanvasSource2D](http://www.vtk.org/doc/nightly/html/classvtkImageCanvasSource2D.html) |Display an image as the background of a scene.
[BorderPixelSize](/Cxx/Images/BorderPixelSize)| [vtkImageSliceMapper](http://www.vtk.org/doc/nightly/html/classvtkImageSliceMapper.html) |Set the size of border pixels.
[CannyEdgeDetector](/Cxx/Images/CannyEdgeDetector)| | Perform Canny edge detection on an image.
[Cast](/Cxx/Images/Cast)| [vtkImageCast](http://www.vtk.org/doc/nightly/html/classvtkImageCast.html) |Cast an image to a different type.
[DotProduct](/Cxx/Images/DotProduct)| [vtkImageDotProduct](http://www.vtk.org/doc/nightly/html/classvtkImageDotProduct.html) | Compute the pixel-wise dot product of two vector images.
[DrawOnAnImage](/Cxx/Images/DrawOnAnImage)| [vtkImageCanvasSource2D](http://www.vtk.org/doc/nightly/html/classvtkImageCanvasSource2D.html) |Drawing on an image.
[DrawShapes](/Cxx/Images/DrawShapes)| [vtkImageCanvasSource2D](http://www.vtk.org/doc/nightly/html/classvtkImageCanvasSource2D.html) |Drawing shapes in an image.
[ExtractComponents](/Cxx/Images/ExtractComponents)| [vtkImageExtractComponents](http://www.vtk.org/doc/nightly/html/classvtkImageExtractComponents.html) |  Extract components of an image. This can be used to get, for example, the red channel of an image.
[FillWindow](/Cxx/Images/FillWindow)| [vtkCamera](http://www.vtk.org/doc/nightly/html/classvtkCamera.html) | Fit imageSetup the camera to fill the window with an image.
[ImageAccumulateGreyscale](/Cxx/Images/ImageAccumulateGreyscale)| [vtkImageAccumulate](http://www.vtk.org/doc/nightly/html/classvtkImageAccumulate.html), [vtkBarChartActor](http://www.vtk.org/doc/nightly/html/classvtkBarChartActor.html) | Display a greyscale histogram.
[ImageCheckerboard](/Cxx/Images/ImageCheckerboard)| [vtkImageCheckerboard](http://www.vtk.org/doc/nightly/html/classvtkImageCheckerboard.html) |Visually Compare Two Images.
[ImageCityBlockDistance](/Cxx/Images/ImageCityBlockDistance)| [vtkImageCityBlockDistance](http://www.vtk.org/doc/nightly/html/classvtkImageCityBlockDistance.html) | Compute the Manhattan distance from every point to every black point in a binary image.
[ImageDilateErode3D](/Cxx/Images/ImageDilateErode3D)| [vtkImageDilateErode3D](http://www.vtk.org/doc/nightly/html/classvtkImageDilateErode3D.html) | Dilate or erode an image.
[ImageExport ](/Cxx/Images/ImageExport) | [vtkImageExport](http://www.vtk.org/doc/nightly/html/classvtkImageExport.html) | Export an image to a C array.
[ImageGridSource](/Cxx/Images/ImageGridSource)| [vtkImageGridSource](http://www.vtk.org/doc/nightly/html/classvtkImageGridSource.html) |Create a image of a grid.
[ImageHybridMedian2D](/Cxx/Images/ImageHybridMedian2D)| [vtkImageHybridMedian2D](http://www.vtk.org/doc/nightly/html/classvtkImageHybridMedian2D.html) | Median filter an image.
[ImageIdealHighPass](/Cxx/Images/ImageIdealHighPass)| [vtkImageIdealHighPass](http://www.vtk.org/doc/nightly/html/classvtkImageIdealHighPass.html) |High pass filter an image.
[ImageImport ](/Cxx/Images/ImageImport) | [vtkImageImport](http://www.vtk.org/doc/nightly/html/classvtkImageImport.html) | Import an image from a C array.
[ImageIslandRemoval2D](/Cxx/Images/ImageIslandRemoval2D)| [vtkImageIslandRemoval2D](http://www.vtk.org/doc/nightly/html/classvtkImageIslandRemoval2D.html) | Remove small patches from an image.
[ImageMagnify](/Cxx/Images/ImageMagnify)| [vtkImageMagnify](http://www.vtk.org/doc/nightly/html/classvtkImageMagnify.html) | Supersample and stretch an image.
[ImageMandelbrotSource](/Cxx/Images/ImageMandelbrotSource)| [vtkImageMandelbrotSource](http://www.vtk.org/doc/nightly/html/classvtkImageMandelbrotSource.html) |Create a Mandelbrot image.
[ImageMask](/Cxx/Images/ImageMask)| [vtkImageMask](http://www.vtk.org/doc/nightly/html/classvtkImageMask.html) |Mask a region of an image.
[ImageMathematics](/Cxx/Images/ImageMathematics)| [vtkImageMathematics](http://www.vtk.org/doc/nightly/html/classvtkImageMathematics.html) |Perform mathematical operations on an image.
[ImageMedian3D](/Cxx/Images/ImageMedian3D)| [vtkImageMedian3D](http://www.vtk.org/doc/nightly/html/classvtkImageMedian3D.html) | Median filter a 3d or 2d image.
[ImageMirrorPad](/Cxx/Images/ImageMirrorPad)| [vtkImageMirrorPad](http://www.vtk.org/doc/nightly/html/classvtkImageMirrorPad.html) | Pad the edges of an extended image by mirror existing pixels.
[ImageNonMaximumSuppression](/Cxx/Images/ImageNonMaximumSuppression)| [vtkImageNonMaximumSuppression](http://www.vtk.org/doc/nightly/html/classvtkImageNonMaximumSuppression.html) |Find peaks in an image using non maximum suppression.
[ImageOpenClose3D](/Cxx/Images/ImageOpenClose3D)| [vtkImageOpenClose3D](http://www.vtk.org/doc/nightly/html/classvtkImageOpenClose3D.html) | Open or close (morphologically) an image.
[ImageRFFT](/Cxx/Images/ImageRFFT)| [vtkImageRFFT](http://www.vtk.org/doc/nightly/html/classvtkImageRFFT.html) | Inverse FFT.
[ImageRange3D](/Cxx/Images/ImageRange3D)| [vtkImageRange3D](http://www.vtk.org/doc/nightly/html/classvtkImageRange3D.html) | Replace every pixel with the range of its neighbors according to a kernel.
[ImageRotate](/Cxx/Images/ImageRotate)| [vtkImageSlice](http://www.vtk.org/doc/nightly/html/classvtkImageSlice.html), [vtkImageResliceMapper](http://www.vtk.org/doc/nightly/html/classvtkImageResliceMapper.html) | Rotate a 2D image. This is even more powerful than [vtkImageSliceMapper](http://www.vtk.org/doc/nightly/html/classvtkImageSliceMapper.html). It can also do oblique slices.
[ImageSeparableConvolution](/Cxx/Images/ImageSeparableConvolution)| [vtkImageSeparableConvolution](http://www.vtk.org/doc/nightly/html/classvtkImageSeparableConvolution.html) | Convolve a separable kernel with an image.
[ImageShiftScale](/Cxx/Images/ImageShiftScale)| [vtkImageShiftScale](http://www.vtk.org/doc/nightly/html/classvtkImageShiftScale.html) | Shift and scale an image.
[ImageSinusoidSource](/Cxx/Images/ImageSinusoidSource)| [vtkImageSinusoidSource](http://www.vtk.org/doc/nightly/html/classvtkImageSinusoidSource.html) |Create a sinusoidal image.
[ImageSliceMapper](/Cxx/Images/ImageSliceMapper)| [vtkImageSlice](http://www.vtk.org/doc/nightly/html/classvtkImageSlice.html), [vtkImageSliceMapper](http://www.vtk.org/doc/nightly/html/classvtkImageSliceMapper.html) | Visualize and interact with an image. This is the new way to do this. It is much more powerful.
[ImageSlice](/Cxx/Images/ImageSlice)| [vtkImageSlice](http://www.vtk.org/doc/nightly/html/classvtkImageSlice.html), [vtkImageResliceMapper](http://www.vtk.org/doc/nightly/html/classvtkImageResliceMapper.html) | Visualize and interact with an image. This is even more powerful than [vtkImageSliceMapper](http://www.vtk.org/doc/nightly/html/classvtkImageSliceMapper.html). It can also do oblique slices.
[ImageStack](/Cxx/Images/ImageStack)| [vtkImageStack](http://www.vtk.org/doc/nightly/html/classvtkImageStack.html) |Display layers of images.
[ImageStencil](/Cxx/Images/ImageStencil)| [vtkImageStencil](http://www.vtk.org/doc/nightly/html/classvtkImageStencil.html), [vtkImageToImageStencil](http://www.vtk.org/doc/nightly/html/classvtkImageToImageStencil.html) | Copy one image into another image.
[ImageText](/Cxx/Broken/Images/ImageText)| [vtkFreeTypeUtilities](http://www.vtk.org/doc/nightly/html/classvtkFreeTypeUtilities.html), [vtkImageBlend](http://www.vtk.org/doc/nightly/html/classvtkImageBlend.html) | Draw text in an image.
[ImageThreshold](/Cxx/Images/ImageThreshold)| [vtkImageThreshold](http://www.vtk.org/doc/nightly/html/classvtkImageThreshold.html) |Threshold an image.
[ImageToPolyDataFilter](/Cxx/Images/ImageToPolyDataFilter)| [vtkImageToPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkImageToPolyDataFilter.html), [vtkImageQuantizeRGBToIndex](http://www.vtk.org/doc/nightly/html/classvtkImageQuantizeRGBToIndex.html) | Convert a [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html) to a [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html).
[ImageToStructuredPoints](/Cxx/Images/ImageToStructuredPoints)| [vtkImageToStructuredPoints](http://www.vtk.org/doc/nightly/html/classvtkImageToStructuredPoints.html) | Convert a [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html) to a [vtkStructuredPoints](http://www.vtk.org/doc/nightly/html/classvtkStructuredPoints.html).
[InteractWithImage](/Cxx/Images/InteractWithImage)| [vtkImageActor](http://www.vtk.org/doc/nightly/html/classvtkImageActor.html), [vtkInteractorStyleImage](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleImage.html) |Visualize and interact with an image.
[Interpolation](/Cxx/Images/Interpolation)| [vtkImageSlice](http://www.vtk.org/doc/nightly/html/classvtkImageSlice.html), [vtkImageProperty](http://www.vtk.org/doc/nightly/html/classvtkImageProperty.html) | Set the interpolation type for the display of an image. If pixels look blurry instead of sharp when zoomed in, change this.
[MarkKeypoints](/Cxx/Images/MarkKeypoints)| [vtkVectorText](http://www.vtk.org/doc/nightly/html/classvtkVectorText.html), [vtkFollower](http://www.vtk.org/doc/nightly/html/classvtkFollower.html) |Mark keypoints in an image.
[NegativeIndices](/Cxx/Images/NegativeIndices)| [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html) | A very powerful feature of [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html) is that you can use negative indices.
[PickingAPixel2](/Cxx/Images/PickingAPixel2)| [vtkPropPicker](http://www.vtk.org/doc/nightly/html/classvtkPropPicker.html) |Picking a pixel 2 - modified version for exact pixel values.
[PickingAPixel](/Cxx/Images/PickingAPixel)| [vtkPropPicker](http://www.vtk.org/doc/nightly/html/classvtkPropPicker.html) |Picking a pixel.
[RTAnalyticSource](/Cxx/Images/RTAnalyticSource)| [vtkRTAnalyticSource](http://www.vtk.org/doc/nightly/html/classvtkRTAnalyticSource.html) | An image source that can be used for regression testing
[StaticImage](/Cxx/Images/StaticImage)|  v[vtkImageViewer2](http://www.vtk.org/doc/nightly/html/classvtkImageViewer2.html) | This will display the image, but not allow you to interact with it.
[Transparency](/Cxx/Images/Transparency)| [vtkImageMapToColors](http://www.vtk.org/doc/nightly/html/classvtkImageMapToColors.html), [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html) | Make part of an image transparent.


#Image Processing

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[Blending2DImagesWithDifferentColorMaps](/Cxx/Images/Blending2DImagesWithDifferentColorMaps)| [vtkImageMapToColors](http://www.vtk.org/doc/nightly/html/classvtkImageMapToColors.html) |Blending 2D images with different color maps.
[CenterAnImage](/Cxx/Images/CenterAnImage)| [vtkImageChangeInformation](http://www.vtk.org/doc/nightly/html/classvtkImageChangeInformation.html) |Center an image.
[CombineImages](/Cxx/Images/CombineImages)| [vtkImageBlend](http://www.vtk.org/doc/nightly/html/classvtkImageBlend.html) |Combine two images.
[CombiningRGBChannels](/Cxx/Images/CombiningRGBChannels)| [vtkImageAppendComponents](http://www.vtk.org/doc/nightly/html/classvtkImageAppendComponents.html) |Combine layers into an RGB image.
[ConvertToGreyScale](/Cxx/Images/ConvertToGreyScale)| [vtkImageMagnitude](http://www.vtk.org/doc/nightly/html/classvtkImageMagnitude.html) | grayscaleConvert RGB image to greyscale.
[Flip](/Cxx/Images/Flip)| [vtkImageFlip](http://www.vtk.org/doc/nightly/html/classvtkImageFlip.html) | Flip an image.
[Gradient](/Cxx/Images/Gradient)| [vtkImageGradient](http://www.vtk.org/doc/nightly/html/classvtkImageGradient.html) | Compute the gradient vector at every pixel.
[ImageAccumulate](/Cxx/Images/ImageAccumulate)| [vtkImageAccumulate](http://www.vtk.org/doc/nightly/html/classvtkImageAccumulate.html) | Histogram
[ImageAnisotropicDiffusion2D](/Cxx/Images/ImageAnisotropicDiffusion2D)| [vtkImageAnisotropicDiffusion2D](http://www.vtk.org/doc/nightly/html/classvtkImageAnisotropicDiffusion2D.html) |Anisotropic diffusion (2D).
[ImageContinuousDilate3D](/Cxx/Images/ImageContinuousDilate3D)| [vtkImageContinuousDilate3D](http://www.vtk.org/doc/nightly/html/classvtkImageContinuousDilate3D.html) |Dilate an image.
[ImageContinuousErode3D](/Cxx/Images/ImageContinuousErode3D)| [vtkImageContinuousErode3D](http://www.vtk.org/doc/nightly/html/classvtkImageContinuousErode3D.html) |Erode an image.
[ImageConvolve](/Cxx/Images/ImageConvolve)| [vtkImageConvolve](http://www.vtk.org/doc/nightly/html/classvtkImageConvolve.html) |Convolve an image with a kernel.
[ImageCorrelation](/Cxx/Images/ImageCorrelation)| [vtkImageCorrelation](http://www.vtk.org/doc/nightly/html/classvtkImageCorrelation.html) |Correlate two images.
[ImageDifference](/Cxx/Images/ImageDifference)| [vtkImageDifference](http://www.vtk.org/doc/nightly/html/classvtkImageDifference.html) |Compute the difference image of two images.
[ImageDivergence](/Cxx/Images/ImageDivergence)| [vtkImageDivergence](http://www.vtk.org/doc/nightly/html/classvtkImageDivergence.html) |Divergence of a vector field.
[ImageEllipsoidSource](/Cxx/Images/ImageEllipsoidSource)| [vtkImageEllipsoidSource](http://www.vtk.org/doc/nightly/html/classvtkImageEllipsoidSource.html) |Create an image of an ellipsoid.
[ImageFFT](/Cxx/Images/ImageFFT)| [vtkImageFFT](http://www.vtk.org/doc/nightly/html/classvtkImageFFT.html) |Compute the FFT of an image.
[ImageGaussianSmooth](/Cxx/Images/ImageGaussianSmooth)| [vtkImageGaussianSmooth](http://www.vtk.org/doc/nightly/html/classvtkImageGaussianSmooth.html) |Smooth an image.
[ImageGradientMagnitude](/Cxx/Images/ImageGradientMagnitude)| [vtkImageGradientMagnitude](http://www.vtk.org/doc/nightly/html/classvtkImageGradientMagnitude.html) |Compute the magnitude of the gradient at each pixel of an image.
[ImageLaplacian](/Cxx/Images/ImageLaplacian)| [vtkImageLaplacian](http://www.vtk.org/doc/nightly/html/classvtkImageLaplacian.html) |Compute the Laplacian of an image.
[ImageLuminance](/Cxx/Images/ImageLuminance)| [vtkImageLuminance](http://www.vtk.org/doc/nightly/html/classvtkImageLuminance.html) |Convert RGB image to greyscale (luminance).
[ImageMapToColors](/Cxx/Images/ImageMapToColors)| [vtkImageMapToColors](http://www.vtk.org/doc/nightly/html/classvtkImageMapToColors.html) | Use a lookup table to map scalar (grayscale) values to colorsConvert greyscale image to RGB.
[ImageNoiseSource](/Cxx/Images/ImageNoiseSource)| [vtkImageNoiseSource](http://www.vtk.org/doc/nightly/html/classvtkImageNoiseSource.html) |Create an image of noise.
[ImagePermute](/Cxx/Images/ImagePermute)| [vtkImagePermute](http://www.vtk.org/doc/nightly/html/classvtkImagePermute.html) |Switch axes of an image.
[ImageShrink3D](/Cxx/Images/ImageShrink3D)| [vtkImageShrink3D](http://www.vtk.org/doc/nightly/html/classvtkImageShrink3D.html) |Resample an image.
[ImageSobel2D](/Cxx/Images/ImageSobel2D)| [vtkImageSobel2D](http://www.vtk.org/doc/nightly/html/classvtkImageSobel2D.html) |Sobel edge detection 2D.
[ImageValueRange](/Cxx/Images/ImageValueRange)| [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html) | Get the range of image pixel values (min/max).
[ImageVariance3D](/Cxx/Images/ImageVariance3D)| [vtkImageVariance3D](http://www.vtk.org/doc/nightly/html/classvtkImageVariance3D.html) | Construct a new image consisting of the variance of the input image at each pixel.
[RGBToHSV](/Cxx/Images/RGBToHSV)| [vtkImageRGBToHSV](http://www.vtk.org/doc/nightly/html/classvtkImageRGBToHSV.html) |Convert RGB to HSV.
[RescaleAnImage](/Cxx/ImageProcessing/RescaleAnImage) | [vtkImageShiftScale](http://www.vtk.org/doc/nightly/html/classvtkImageShiftScale.html) | Rescale an image
[ResizeImage](/Cxx/Images/ResizeImage)| [vtkImageResize](http://www.vtk.org/doc/nightly/html/classvtkImageResize.html) [vtkImageSincInterpolator](http://www.vtk.org/doc/nightly/html/classvtkImageSincInterpolator.html)| Resize an image using a sinc interpolator.


#Widgets

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[ PolygonalSurfacePointPlacer](/Cxx/PolyData/PolygonalSurfacePointPlacer)| [vtkPolygonalSurfacePointPlacer](http://www.vtk.org/doc/nightly/html/classvtkPolygonalSurfacePointPlacer.html) | Used in conjuntion with [vtkContourWidget](http://www.vtk.org/doc/nightly/html/classvtkContourWidget.html) to draw curves on a surface.
[AffineWidget](/Cxx/Widgets/AffineWidget)| [vtkAffineWidget](http://www.vtk.org/doc/nightly/html/classvtkAffineWidget.html) | Apply an affine transformation interactively.
[AngleWidget2D](/Cxx/Widgets/AngleWidget2D)| [vtkAngleWidget](http://www.vtk.org/doc/nightly/html/classvtkAngleWidget.html), [vtkAngleRepresentation2D](http://www.vtk.org/doc/nightly/html/classvtkAngleRepresentation2D.html) |[vtkAngleWidget](http://www.vtk.org/doc/nightly/html/classvtkAngleWidget.html) + [vtkAngleRepresentation2D](http://www.vtk.org/doc/nightly/html/classvtkAngleRepresentation2D.html).
[AngleWidget](/Cxx/Widgets/AngleWidget)| [vtkAngleWidget](http://www.vtk.org/doc/nightly/html/classvtkAngleWidget.html) |
[BalloonWidget](/Cxx/Widgets/BalloonWidget)| [vtkBalloonWidget](http://www.vtk.org/doc/nightly/html/classvtkBalloonWidget.html) |
[BiDimensionalWidget](/Cxx/Widgets/BiDimensionalWidget) |  [vtkBiDimensionalWidget](http://www.vtk.org/doc/nightly/html/classvtkBiDimensionalWidget.html) |  When would you use this?
[BorderWorldCoords](Broken/Cxx/Widgets/BorderWorldCoords)| [vtkBorderWidget](http://www.vtk.org/doc/nightly/html/classvtkBorderWidget.html) | 2D selection box in world coordinates.
[Border](/Cxx/Widgets/Border)| [vtkBorderWidget](http://www.vtk.org/doc/nightly/html/classvtkBorderWidget.html) | 2D selection, 2D box.
[BoxWidget2](/Cxx/Widgets/BoxWidget2)| [vtkBoxWidget2](http://www.vtk.org/doc/nightly/html/classvtkBoxWidget2.html) |
[BoxWidget](/Cxx/Widgets/BoxWidget)| [vtkBoxWidget](http://www.vtk.org/doc/nightly/html/classvtkBoxWidget.html) |
[Caption](/Cxx/Widgets/Caption)| [vtkCaptionWidget](http://www.vtk.org/doc/nightly/html/classvtkCaptionWidget.html) |
[CheckerboardWidget](/Cxx/Widgets/CheckerboardWidget)| [vtkCheckerboardWidget](http://www.vtk.org/doc/nightly/html/classvtkCheckerboardWidget.html), [vtkCheckerboardRepresentation](http://www.vtk.org/doc/nightly/html/classvtkCheckerboardRepresentation.html) | Compare two images using a checkerboard.
[ContourWidget ](/Cxx/Widgets/ContourWidget) | [vtkContourWidget](http://www.vtk.org/doc/nightly/html/classvtkContourWidget.html) | Create a contour from a set of points and dynamically change the contour using the points as control points.
[Cursor2D](/Cxx/Visualization/Cursor2D)| [vtkCursor2D](http://www.vtk.org/doc/nightly/html/classvtkCursor2D.html) |
[DistanceWidget](/Cxx/Widgets/DistanceWidget) | [vtkDistanceWidget](http://www.vtk.org/doc/nightly/html/classvtkDistanceWidget.html) |
[HoverWidget](/Cxx/Widgets/HoverWidget)| [vtkHoverWidget](http://www.vtk.org/doc/nightly/html/classvtkHoverWidget.html) | How to detect a hover? 
[ImagePlaneWidget](/Cxx/Widgets/ImagePlaneWidget)| [vtkImagePlaneWidget](http://www.vtk.org/doc/nightly/html/classvtkImagePlaneWidget.html) |
[ImageTracerWidgetInsideContour](/Cxx/Widgets/ImageTracerWidgetInsideContour)| [vtkImageTracerWidget](http://www.vtk.org/doc/nightly/html/classvtkImageTracerWidget.html) | Highlight pixels inside a non-regular region scribbled on an image.
[ImageTracerWidgetNonPlanar](/Cxx/Widgets/ImageTracerWidgetNonPlanar)| [vtkImageTracerWidget](http://www.vtk.org/doc/nightly/html/classvtkImageTracerWidget.html) |Draw on a non-planar surface.
[ImageTracerWidget](/Cxx/Widgets/ImageTracerWidget)| [vtkImageTracerWidget](http://www.vtk.org/doc/nightly/html/classvtkImageTracerWidget.html) | Scribble on an image.
[ImplicitPlaneWidget2](/Cxx/Widgets/ImplicitPlaneWidget2)| [vtkImplicitPlaneWidget2](http://www.vtk.org/doc/nightly/html/classvtkImplicitPlaneWidget2.html) | Clip polydata with an implicit plane.
[LineWidget2](/Cxx/Widgets/LineWidget2)| [vtkLineWidget2](http://www.vtk.org/doc/nightly/html/classvtkLineWidget2.html) |
[LogoWidget](/Cxx/Widgets/LogoWidget)| [vtkLogoWidget](http://www.vtk.org/doc/nightly/html/classvtkLogoWidget.html) |Logo widget.
[OrientationMarkerWidget](/Cxx/Widgets/OrientationMarkerWidget)| [vtkOrientationMarkerWidget](http://www.vtk.org/doc/nightly/html/classvtkOrientationMarkerWidget.html) | Display a polydata as an orientation icon.
[PlaneWidget ](/Cxx/Widgets/PlaneWidget) | [vtkPlaneWidget](http://www.vtk.org/doc/nightly/html/classvtkPlaneWidget.html) | Interact with a plane.
[PointWidget](Broken/Widgets/PointWidget)| [vtkPointWidget](http://www.vtk.org/doc/nightly/html/classvtkPointWidget.html) | 
[RectilinearWipeWidget](/Cxx/Widgets/RectilinearWipeWidget)| [vtkImageRectilinearWipe](http://www.vtk.org/doc/nightly/html/classvtkImageRectilinearWipe.html), [vtkRectilinearWipeWidget](http://www.vtk.org/doc/nightly/html/classvtkRectilinearWipeWidget.html), [vtkRectilinearWipeRepresentation](http://www.vtk.org/doc/nightly/html/classvtkRectilinearWipeRepresentation.html) | Compare two images.
[SeedWidgetImage](Widgets/SeedWidgetImage)| [vtkImageViewer2](http://www.vtk.org/doc/nightly/html/classvtkImageViewer2.html), [vtkSeedWidget](http://www.vtk.org/doc/nightly/html/classvtkSeedWidget.html) | How to start the interaction? 
[SeedWidget](/Cxx/Widgets/SeedWidget)| [vtkSeedWidget](http://www.vtk.org/doc/nightly/html/classvtkSeedWidget.html) |Seed widget.
[Slider2D](/Cxx/Widgets/Slider2D)| [vtkSliderWidget](http://www.vtk.org/doc/nightly/html/classvtkSliderWidget.html), [vtkSliderRepresentation2D](http://www.vtk.org/doc/nightly/html/classvtkSliderRepresentation2D.html)|2D Slider.
[Slider](/Cxx/Widgets/Slider)| [vtkSliderWidget](http://www.vtk.org/doc/nightly/html/classvtkSliderWidget.html), [vtkSliderRepresentation3D](http://www.vtk.org/doc/nightly/html/classvtkSliderRepresentation3D.html) |3D Slider.
[SphereWidget2](/Cxx/Widgets/SphereWidget2)| [vtkSphereWidget2](http://www.vtk.org/doc/nightly/html/classvtkSphereWidget2.html) |
[SphereWidgetEvents ](/Cxx/Widgets/SphereWidgetEvents)| [vtkSphereWidget](http://www.vtk.org/doc/nightly/html/classvtkSphereWidget.html) |Sphere widget events.
[SphereWidget](/Cxx/Widgets/SphereWidget)| [vtkSphereWidget](http://www.vtk.org/doc/nightly/html/classvtkSphereWidget.html) |Sphere widget.
[SplineWidget](/Cxx/Widgets/Spline)| [vtkSplineWidget](http://www.vtk.org/doc/nightly/html/classvtkSplineWidget.html) |
[TextWidget](/Cxx/Widgets/TextWidget)| [vtkSeedWidget](http://www.vtk.org/doc/nightly/html/classvtkSeedWidget.html) || [vtkTextWidget](http://www.vtk.org/doc/nightly/html/classvtkTextWidget.html) |Draw movable text.
[TexturedButtonWidget](/Cxx/Widgets/TexturedButtonWidget) | [vtkButtonWidget](http://www.vtk.org/doc/nightly/html/classvtkButtonWidget.html),[vtkTexturedButtonRepresentation2D](http://www.vtk.org/doc/nightly/html/classvtkTexturedButtonRepresentation2D.html) |Create a textured 2D buttonx.

#Plotting

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[BarChart](/Cxx/Plotting/BarChart)| [vtkChartXY](http://www.vtk.org/doc/nightly/html/classvtkChartXY.html) |Bar chart.
[BoxChart](/Cxx/Plotting/BoxChart)| [vtkChartBox](http://www.vtk.org/doc/nightly/html/classvtkChartBox.html) |Box plot.
[Diagram](/Cxx/Plotting/Diagram)| |
[LinePlot](/Cxx/Plotting/LinePlot)| [vtkChartXY](http://www.vtk.org/doc/nightly/html/classvtkChartXY.html) |Line plot.
[ParallelCoordinates](/Cxx/Plotting/ParallelCoordinates)| [vtkChartParallelCoordinates](http://www.vtk.org/doc/nightly/html/classvtkChartParallelCoordinates.html) |Parallel coordinates.
[PieChart](/Cxx/Plotting/PieChart)| [vtkChartPie](http://www.vtk.org/doc/nightly/html/classvtkChartPie.html), [vtkPlotPie](http://www.vtk.org/doc/nightly/html/classvtkPlotPie.html) |Pie chart.
[ScatterPlot](/Cxx/Plotting/ScatterPlot)| [vtkPlotPoints](http://www.vtk.org/doc/nightly/html/classvtkPlotPoints.html) |Scatter plot.
[StackedBar](/Cxx/Plotting/StackedBar)| [vtkPlotBar](http://www.vtk.org/doc/nightly/html/classvtkPlotBar.html) |Stacked bar.
[StackedPlot](/Cxx/Plotting/StackedPlot)| [vtkPlotStacked](http://www.vtk.org/doc/nightly/html/classvtkPlotStacked.html) |Stacked plot.


#Animation

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[AnimateActors](/Cxx/Animation/AnimateActors) | [vtkAnimationScene](http://www.vtk.org/doc/nightly/html/classvtkAnimationScene.html), [vtkAnimationCue](http://www.vtk.org/doc/nightly/html/classvtkAnimationCue.html)|Animate actors.
[Animation](/Cxx/Utilities/Animation) | [vtkRenderWindowInteractor](http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html)::CreateRepeatingTimer | Move a sphere across a scene.
[AnimationScene](/Cxx/Utilities/AnimationScene) | [vtkAnimationScene](http://www.vtk.org/doc/nightly/html/classvtkAnimationScene.html), [vtkAnimationCue](http://www.vtk.org/doc/nightly/html/classvtkAnimationCue.html) | Animation (the right way). Zoom in on a sphere.
[DataAnimation](/Cxx/Utilities/DataAnimation) | [vtkCallbackCommand](http://www.vtk.org/doc/nightly/html/classvtkCallbackCommand.html), [vtkProgrammableFilter](http://www.vtk.org/doc/nightly/html/classvtkProgrammableFilter.html) | Data Animation. Update points in a dataset every specified interval.
[DataAnimationSubclass](/Cxx/Utilities/DataAnimationSubclass) | [vtkCommand](http://www.vtk.org/doc/nightly/html/classvtkCommand.html), [vtkProgrammableFilter](http://www.vtk.org/doc/nightly/html/classvtkProgrammableFilter.html)| Update points in a dataset every specified interval (using a [vtkCommand](http://www.vtk.org/doc/nightly/html/classvtkCommand.html) subclass instead of a callback function.

#Geographic Visualization (Geovis)

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[CompassWidget ](/Cxx/Geovis/CompassWidget)  | [vtkCompassWidget](http://www.vtk.org/doc/nightly/html/classvtkCompassWidget.html) | Compass Widget.
[EarthSource](/Cxx/Geovis/EarthSource) | [vtkEarthSource](http://www.vtk.org/doc/nightly/html/classvtkEarthSource.html) | Create the Earth.
[GeoAssignCoordinates](/Cxx/Geovis/GeoAssignCoordinates) | [vtkGeoAssignCoordinates](http://www.vtk.org/doc/nightly/html/classvtkGeoAssignCoordinates.html) | Convert lat/long coordinates to world coordinates.

#Information Visualization (Infovis)

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[ParallelCoordinatesView](/Cxx/InfoVis/ParallelCoordinatesView) | [vtkParallelCoordinatesView](http://www.vtk.org/doc/nightly/html/classvtkParallelCoordinatesView.html) | Parallel coordinates.
[TreeMapView](/Cxx/InfoVis/TreeMapView) | [vtkTreeMapView](http://www.vtk.org/doc/nightly/html/classvtkTreeMapView.html) | Tree map.


#Qt
Click [here](http://www.vtk.org/Wiki/VTK/Tutorials/QtSetup) for a tutorial on how to setup Qt.


| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[ Border Widget](/Cxx/Qt/BorderWidget) | [vtkBorderWidget](http://www.vtk.org/doc/nightly/html/classvtkBorderWidget.html), QApplication |
[ QtBarChart](/Cxx/Qt/QtBarChart) | [vtkQtBarChart](http://www.vtk.org/doc/nightly/html/classvtkQtBarChart.html) |
[ ShowEvent ](/Cxx/Qt/ShowEvent) |  | Use QMainWindow::showEvent event to do things that you might want to do in the constructor 
[EventQtSlotConnect](/Cxx/Qt/EventQtSlotConnect) | [vtkEventQtSlotConnect](http://www.vtk.org/doc/nightly/html/classvtkEventQtSlotConnect.html)|  Connect a VTK event to a Qt slot.
[ImageDataToQImage](/Cxx/Qt/ImageDataToQImage) | |  Convert a [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html) to a QImage.
[QImageToImageSource](/Cxx/Qt/QImageToImageSource) | [vtkQImageToImageSource](http://www.vtk.org/doc/nightly/html/classvtkQImageToImageSource.html) |  Convert a QImage to a [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html).
[RenderWindowNoUiFile](/Cxx/Qt/RenderWindowNoUiFile) | Q[VTKWidget](http://www.vtk.org/doc/nightly/html/classVTKWidget.html)| This is a very basic example that shows how to create a Qt window. Typically, one would want to design a form in the QtDesigner (this is shown in [[/Qt/RenderWindowUi|RenderWindowUi]]).
[RenderWindowUIMultipleInheritance](/Cxx/Qt/RenderWindowUIMultipleInheritance) | QMainWindow | Using a Q[VTKWidget](http://www.vtk.org/doc/nightly/html/classVTKWidget.html) with the Qt Multiple Inheritance model.
[RenderWindowUISingleInheritance](/Cxx/Qt/RenderWindowUISingleInheritance) | QMainWindow | Using a Q[VTKWidget](http://www.vtk.org/doc/nightly/html/classVTKWidget.html) with the Qt Single Inheritance model.
[ShareCameraBetweenQ[VTKWidgets](http://www.vtk.org/doc/nightly/html/classVTKWidgets.html)](/Cxx/Qt/ShareCameraBetweenQ[VTKWidgets](http://www.vtk.org/doc/nightly/html/classVTKWidgets.html)) | |  Share the camera between Q[VTKWidgets](http://www.vtk.org/doc/nightly/html/classVTKWidgets.html).
[SideBySideRenderWindows](/Cxx/Qt/SideBySideRenderWindows) | QApplication | Side by side render windows.


#Matlab
You must turn on VTK_USE_MATLAB_MEX to use these.

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[MatlabEngineFilter](/Cxx/Matlab/MatlabEngineFilter)  | [vtkMatlabEngineFilter](http://www.vtk.org/doc/nightly/html/classvtkMatlabEngineFilter.html) |


#Databases
##SQL
If you have any trouble or errors with the following examples, please troubleshoot using [these instructions](http://www.vtk.org/Wiki/Tutorials/SQLSetup).


| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[ConnectAndRead](/Cxx/Databases/SQL/MySQL/ConnectAndRead) | [vtkMySQLDatabase](http://www.vtk.org/doc/nightly/html/classvtkMySQLDatabase.html), [vtkSQLQuery](http://www.vtk.org/doc/nightly/html/classvtkSQLQuery.html) |Connect to and read a MySQL database.
[CreateDatabase](/Cxx/Databases/SQL/MySQL/CreateDatabase) | [vtkMySQLDatabase](http://www.vtk.org/doc/nightly/html/classvtkMySQLDatabase.html) | Create a MySQL database.
[WriteToDatabase](/Cxx/Databases/SQL/MySQL/WriteToDatabase) | [vtkSQLQuery](http://www.vtk.org/doc/nightly/html/classvtkSQLQuery.html), [vtkMySQLDatabase](http://www.vtk.org/doc/nightly/html/classvtkMySQLDatabase.html) |  Write to a MySQL database.


#RenderMan
RenderMan is a high quality rendering system created by [Pixar](https://renderman.pixar.com/view/renderman). VTK can export RenderMan RIB files for rendering by [prman](http://renderman.pixar.com/view/renderman-prman-the-rispec-and-renderman-studio). In the spring of 2015, Pixar released a [non-commercial version](http://renderman.pixar.com/view/PR-NCR) of its RenderMan products.

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[PolyDataRIB](/Cxx/RenderMan/PolyDataRIB) | [vtkRIBExporter](http://www.vtk.org/doc/nightly/html/classvtkRIBExporter.html)|Apply a RenderMan Shader to a PolyData.

#Remote Modules
Remote modules are user contributed code that is not distributed with VTK. A description of a remote module and the location of its repository is listed in the VTK/Remote directory with the extension .remote.cmake. Once enabled, a remote module is treated like any other VTK module. Each of the remote module examples describes how to enable the example. More information about remote modules is [here](http://www.vtk.org/Wiki/VTK/Remote_Modules).

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[FrenetSerretFrame](/Cxx/Remote/FrenetSerretFrame) | [vtkFrenetSerretFrame](http://www.vtk.org/doc/nightly/html/classvtkFrenetSerretFrame.html) | Compute tangent and normal vectors to a polyline.
[FrenetSerretFrameDemo](/Cxx/Remote/FrenetSerretFrameDemo) | [vtkFrenetSerretFrame](http://www.vtk.org/doc/nightly/html/classvtkFrenetSerretFrame.html) | Uses [vtkSplineWidget](http://www.vtk.org/doc/nightly/html/classvtkSplineWidget.html) to interact with a spline. Shows how to control a pipeline inside a callback.
