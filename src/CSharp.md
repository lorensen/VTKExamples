I just started to maintain this page. So stay tuned. In the near future you will find useful examples here from time to time.<br />
A tutorial on how to setup a Windows Forms Application utilizing ActiViz.NET can be found here: [http://www.vtk.org/Wiki/VTK/CSharp/ActiViz.NET Setup a Windows Forms Application to use ActiViz.NET]

## Simple Operations
| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[DistancePointToLine](/CSharp/SimpleOperations/DistancePointToLine) | [vtkLine](http://www.vtk.org/doc/nightly/html/classvtkLine.html#details) | Distance between a point and a line
[DistanceBetweenPoints](/CSharp/SimpleOperations/DistanceBetweenPoints) | [vtkMath](http://www.vtk.org/doc/nightly/html/classvtkMath.html#details) | Computes the distance between two point Distance between two points
[UniformRandomNumber](/CSharp/SimpleOperations/UniformRandomNumber) | [vtkMath](http://www.vtk.org/doc/nightly/html/classvtkMath.html#details) | Generates uniform random number Random number (uniform distribution)
[GaussianRandomNumber](/CSharp/SimpleOperations/GaussianRandomNumber) | [vtkMath](http://www.vtk.org/doc/nightly/html/classvtkMath.html#details) | Generates Gaussian random number Random number (Gaussian distribution)
[RandomSequence](/CSharp/SimpleOperations/RandomSequence)|[vtkMinimalStandardRandomSequence](http://www.vtk.org/doc/nightly/html/classvtkMinimalStandardRandomSequence.html#details) | This is the preferred way to generate random numbers Random sequence
[ProjectPointPlane](/CSharp/SimpleOperations/ProjectPointPlane)|[vtkPlane](http://www.vtk.org/doc/nightly/html/classvtkPlane.html#details) | Project a point onto a plan Project a point onto a plane
[PerspectiveTransform](/CSharp/SimpleOperations/PerspectiveTransform)|[vtkPerspectiveTransform](http://www.vtk.org/doc/nightly/html/classvtkPerspectiveTransform.html#details) | Apply a perspective transformation to a point

## Input and Output
### Graph Formats

### 3D File Formats
Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[ConvertFile](/CSharp/IO/ConvertFile) |  | Convert a file from one type to another
[XGMLReader](/CSharp/InfoVis/XGMLReader) | [vtkXGMLReader](http://www.vtk.org/doc/nightly/html/classvtkXGMLReader.html#details) | Read a .gml file


#### Standard Formats
##### Input
Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[SimplePointsReader](/CSharp/IO/SimplePointsReader) | [vtkSimplePointsReader](http://www.vtk.org/doc/nightly/html/classvtkSimplePointsReader.html#details) | Read a simple "xyz" file of points
[ParticleReader](/CSharp/IO/ParticleReader)| [vtkParticleReader](http://www.vtk.org/doc/nightly/html/classvtkParticleReader.html#details) | This example reads ascii files where each line consists of points with its position (x,y,z) and (optionally) one scalar or binary files in RAW 3d file forma Read an "xyza" file
[ReadPlainText](/CSharp/IO/ReadPlainText) | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details) | Manually read a file using a streamreade Read a plain text file into a polydata
[ReadOBJ](/CSharp/IO/ReadOBJ) | [vtkOBJReader](http://www.vtk.org/doc/nightly/html/classvtkOBJReader.html#details) | Read an OBJ (.obj) File
[ReadDICOMSeries](/CSharp/IO/ReadDICOMSeries) | [vtkDICOMImageReader](http://www.vtk.org/doc/nightly/html/classvtkDICOMImageReader.html#details) | This example demonstates how to read a series of DICOM images and scroll through slice Convert a series of DICOM files into a VTI File
[VRML](/CSharp/IO/VRML)|[vtkVRMLImporter](http://www.vtk.org/doc/nightly/html/classvtkVRMLImporter.html#details) | Read a VRML (WRL) file
[DEMReader](/CSharp/IO/DEMReader) | [vtkDEMReader](http://www.vtk.org/doc/nightly/html/classvtkDEMReader.html#details) | Read DEM (elevation map) files
[ReadSTL](/CSharp/IO/ReadSTL) | [vtkSTLReader](http://www.vtk.org/doc/nightly/html/classvtkSTLReader.html#details) | Read stereo lithography STL (.stl) files
[ReadPLY](/CSharp/IO/ReadPLY) | [vtkPLYReader](http://www.vtk.org/doc/nightly/html/classvtkPLYReader.html#details) | Read PLY (.ply) files
[ReadPLOT3D](/CSharp/IO/ReadPLOT3D) | [vtkPLOT3DReader](http://www.vtk.org/doc/nightly/html/classvtkPLOT3DReader.html#details) | Read CFD (computational fluid dynamics) data produced by PLOT3D Read PLOT3D (.bin) files
[ReadPDB](/CSharp/IO/ReadPDB) | [vtkPDBReader](http://www.vtk.org/doc/nightly/html/classvtkPDBReader.html#details) | Read Protein Data Bank Files Read Protein Data Bank files (.pdb) files

#### VTK Formats
##### Input 

Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[ReadUnstructuredGrid](/CSharp/IO/ReadUnstructuredGrid)|[vtkXMLUnstructuredGridReader](http://www.vtk.org/doc/nightly/html/classvtkXMLUnstructuredGridReader.html#details) |Demonstrates how to read a .vtu fil Read an unstructured grid (.vtu) file
[ReadPolyData](/CSharp/IO/ReadPolyData)|[vtkXMLPolyDataReader](http://www.vtk.org/doc/nightly/html/classvtkXMLPolyDataReader.html#details) | Read a polygonal data (.vtp) file
[ReadImageData](/CSharp/IO/ReadImageData)|[vtkXMLImageDataReader](http://www.vtk.org/doc/nightly/html/classvtkXMLImageDataReader.html#details) | Read a image data (.vti) file
[ReadStructuredGrid](/CSharp/IO/ReadStructuredGrid)|[vtkXMLStructuredGridReader](http://www.vtk.org/doc/nightly/html/classvtkXMLStructuredGridReader.html#details) | Read a structured grid (.vts) file
[ReadRectilinearGrid](/CSharp/IO/ReadRectilinearGrid)|[vtkXMLRectilinearGridReader](http://www.vtk.org/doc/nightly/html/classvtkXMLRectilinearGridReader.html#details) | Read a rectilinear grid (.vtr) file
[ReadUnknownTypeXMLFile](/CSharp/IO/ReadUnknownTypeXMLFile)|[vtkXMLGenericDataObjectReader](http://www.vtk.org/doc/nightly/html/classvtkXMLGenericDataObjectReader.html#details) | Read an XML file and later decide what kind it is

##### Output

Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[WriteVTU](/CSharp/IO/WriteVTU)|[vtkXMLUnstructuredGridWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLUnstructuredGridWriter.html#details) | VTU is an "Unstructured Grid". This format allows for 3D data to be stored Write a .vtu file
[WriteVTP](/CSharp/IO/WriteVTP)|[vtkXMLPolyDataWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLPolyDataWriter.html#details) | VTP is a "PolyData". This format allows for the most complex geometric objects to be stored Write a .vtp file
[WriteVTI](/CSharp/IO/WriteVTI)|[vtkXMLImageDataWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLImageDataWriter.html#details) | VTI is an "ImageData" Write a .vti file
[XMLStructuredGridWriter](/CSharp/IO/XMLStructuredGridWriter)|[vtkXMLStructuredGridWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLStructuredGridWriter.html#details) | Write a .vts file from a vtkStructuredGrid


### Image Formats

#### Input
Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[ReadBMP](/CSharp/IO/ReadBMP) | [vtkBMPReader](http://www.vtk.org/doc/nightly/html/classvtkBMPReader.html#details) | Read BMP (.bmp) files
[JPEGReader](/CSharp/IO/JPEGReader)|[vtkJPEGReader](http://www.vtk.org/doc/nightly/html/classvtkJPEGReader.html#details)| Read a JPG image
[PNGReader](/CSharp/IO/PNGReader)|[vtkPNGReader](http://www.vtk.org/doc/nightly/html/classvtkPNGReader.html#details)| Read a PNG image
[ReadPNM](/CSharp/IO/ReadPNM) | [vtkPNMReader](http://www.vtk.org/doc/nightly/html/classvtkPNMReader.html#details) | Read PNM (.pnm) files
[ReadTIFF](/CSharp/IO/ReadTIFF) | [vtkTIFFReader](http://www.vtk.org/doc/nightly/html/classvtkTIFFReader.html#details) | Read TIFF (.tif) files
[MetaImageReader](/CSharp/IO/MetaImageReader) | [vtkMetaImageReader](http://www.vtk.org/doc/nightly/html/classvtkMetaImageReader.html#details) | Read .mha files
[ImageReader2Factory](/CSharp/IO/ImageReader2Factory)|[vtkImageReader2Factory](http://www.vtk.org/doc/nightly/html/classvtkImageReader2Factory.html#details) | This class tries to find an appropriate reader. It is very convenient to use this when you don't know what kind of file to expect Read most standard image formats.

#### Output

Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[WriteBMP](/CSharp/IO/WriteBMP) | [vtkBMPWriter](http://www.vtk.org/doc/nightly/html/classvtkBMPWriter.html#details) | Write a BMP (.bmp) file
[JPEGWriter](/CSharp/IO/JPEGWriter) | [vtkJPEGWriter](http://www.vtk.org/doc/nightly/html/classvtkJPEGWriter.html#details) | Write a JPEG (.jpg) file
[WritePNG](/CSharp/IO/WritePNG) | [vtkPNGWriter](http://www.vtk.org/doc/nightly/html/classvtkPNGWriter.html#details) | Write a PNG (.png) file
[WritePNM](/CSharp/IO/WritePNM) | [vtkPNMWriter](http://www.vtk.org/doc/nightly/html/classvtkPNMWriter.html#details) | Write a PNM (.pnm) file
[WriteTIFF](/CSharp/IO/WriteTIFF) | [vtkTIFFWriter](http://www.vtk.org/doc/nightly/html/classvtkTIFFWriter.html#details) | Write a TIFF (.tif) file
[MetaImageWriter](/CSharp/IO/MetaImageWriter) | [vtkMetaImageWriter](http://www.vtk.org/doc/nightly/html/classvtkMetaImageWriter.html#details) | Write a .mha/.mhd + .raw file

## Geometric Objects

Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[PolygonIntersection](/CSharp/GeometricObjects/PolygonIntersection)| [vtkPolygon](http://www.vtk.org/doc/nightly/html/classvtkPolygon.html#details) | IntersectWithLine( Compute the intersection of a line segment with a polygon
[GeometricObjectsDemo](/CSharp/GeometricObjects/GeometricObjectsDemo)|  | A demonstration of all geometric objects that work the same way
[Arrow](/CSharp/GeometricObjects/Arrow)| [vtkArrowSource](http://www.vtk.org/doc/nightly/html/classvtkArrowSource.html#details) | Arrow
[Axes](/CSharp/GeometricObjects/Axes)| [vtkAxesActor](http://www.vtk.org/doc/nightly/html/classvtkAxesActor.html#details) | Axes
[ColoredLines](/CSharp/GeometricObjects/ColoredLines)  |[vtkCellData](http://www.vtk.org/doc/nightly/html/classvtkCellData.html#details) [vtkLine](http://www.vtk.org/doc/nightly/html/classvtkLine.html#details) | Colored Lines
[Cone](/CSharp/GeometricObjects/Cone) | [vtkConeSource](http://www.vtk.org/doc/nightly/html/classvtkConeSource.html#details) | Cone
[Cube](/CSharp/GeometricObjects/Cube) | [vtkCubeSource](http://www.vtk.org/doc/nightly/html/classvtkCubeSource.html#details) | Cube
[Cylinder](/CSharp/GeometricObjects/Cylinder) | [vtkCylinderSource](http://www.vtk.org/doc/nightly/html/classvtkCylinderSource.html#details) | Cylinder
[Disk](/CSharp/GeometricObjects/Disk) | [vtkDiskSource](http://www.vtk.org/doc/nightly/html/classvtkDiskSource.html#details) | A circle with a hole in it Disk
[Frustum](/CSharp/GeometricObjects/Frustum) | [vtkFrustumSource](http://www.vtk.org/doc/nightly/html/classvtkFrustumSource.html#details) | Frustum
[Line](/CSharp/GeometricObjects/Line) | [vtkLineSource](http://www.vtk.org/doc/nightly/html/classvtkLineSource.html#details) | Line
[LongLine](/CSharp/GeometricObjects/LongLine) | [vtkLine](http://www.vtk.org/doc/nightly/html/classvtkLine.html#details) | Manually create a polyline
[Hexahedron](/CSharp/GeometricObjects/Hexahedron) | [vtkHexahedron](http://www.vtk.org/doc/nightly/html/classvtkHexahedron.html#details) | Hexahedron
[OrientedArrow](/CSharp/GeometricObjects/OrientedArrow) | [vtkArrowSource](http://www.vtk.org/doc/nightly/html/classvtkArrowSource.html#details) | Oriented Arrow
[Plane](/CSharp/GeometricObjects/Plane) | [vtkPlaneSource](http://www.vtk.org/doc/nightly/html/classvtkPlaneSource.html#details) | Plane
[Planes](/CSharp/GeometricObjects/Planes) | [vtkPlanes](http://www.vtk.org/doc/nightly/html/classvtkPlanes.html#details) | Planes
[PlanesIntersection](/CSharp/GeometricObjects/PlanesIntersection) | [vtkPlanesIntersection](http://www.vtk.org/doc/nightly/html/classvtkPlanesIntersection.html#details) | PlanesIntersection
[PlatonicSolid](/CSharp/GeometricObjects/PlatonicSolid) | [vtkPlatonicSolidSource](http://www.vtk.org/doc/nightly/html/classvtkPlatonicSolidSource.html#details) | PlatonicSolid
[Point](/CSharp/GeometricObjects/Point) | [vtkPoints](http://www.vtk.org/doc/nightly/html/classvtkPoints.html#details) | Point
[Polygon](/CSharp/GeometricObjects/Polygon) | [vtkPolygon](http://www.vtk.org/doc/nightly/html/classvtkPolygon.html#details) | Polygon
[Pyramid](/CSharp/GeometricObjects/Pyramid) | [vtkPyramid](http://www.vtk.org/doc/nightly/html/classvtkPyramid.html#details) | Pyramid
[PolyLine](/CSharp/GeometricObjects/PolyLine) | [vtkPolyLine](http://www.vtk.org/doc/nightly/html/classvtkPolyLine.html#details) | PolyLine
[Quad](/CSharp/GeometricObjects/Quad) | [vtkQuad](http://www.vtk.org/doc/nightly/html/classvtkQuad.html#details) | Quad
[RegularPolygonSource](/CSharp/GeometricObjects/RegularPolygonSource) | [vtkRegularPolygonSource](http://www.vtk.org/doc/nightly/html/classvtkRegularPolygonSource.html#details) | Regular Polygon
[Sphere](/CSharp/GeometricObjects/Sphere) | [vtkSphereSource](http://www.vtk.org/doc/nightly/html/classvtkSphereSource.html#details) | Sphere
[Triangle](/CSharp/GeometricObjects/Triangle) | [vtkTriangle](http://www.vtk.org/doc/nightly/html/classvtkTriangle.html#details) | Triangle
[TriangleStrip](/CSharp/GeometricObjects/TriangleStrip)|[vtkTriangleStrip](http://www.vtk.org/doc/nightly/html/classvtkTriangleStrip.html#details) | Triangle strip
[Tetrahedron](/CSharp/GeometricObjects/Tetrahedron) | [vtkTetra](http://www.vtk.org/doc/nightly/html/classvtkTetra.html#details) | Tetrahedron
[Vertex](/CSharp/GeometricObjects/Vertex) | [vtkVertex](http://www.vtk.org/doc/nightly/html/classvtkVertex.html#details) | Vertex

### Parametric Objects
These examples demonstrate how to create an display one of the many vtkParametric* objects. All of the classes listed can be used in an identical fashion.

Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[ParametricObjects](/CSharp/GeometricObjects/ParametricObjects) | [vtkParametricBoy](http://www.vtk.org/doc/nightly/html/classvtkParametricBoy.html#details), [vtkParametricConicSpiral](http://www.vtk.org/doc/nightly/html/classvtkParametricConicSpiral.html#details), [vtkParametricCrossCap](http://www.vtk.org/doc/nightly/html/classvtkParametricCrossCap.html#details), [vtkParametricDini](http://www.vtk.org/doc/nightly/html/classvtkParametricDini.html#details), [vtkParametricEllipsoid](http://www.vtk.org/doc/nightly/html/classvtkParametricEllipsoid.html#details), [vtkParametricEnneper](http://www.vtk.org/doc/nightly/html/classvtkParametricEnneper.html#details), [vtkParametricFigure8Klein](http://www.vtk.org/doc/nightly/html/classvtkParametricFigure8Klein.html#details), [vtkParametricKlein](http://www.vtk.org/doc/nightly/html/classvtkParametricKlein.html#details), [vtkParametricMobius](http://www.vtk.org/doc/nightly/html/classvtkParametricMobius.html#details), [vtkParametricRandomHills](http://www.vtk.org/doc/nightly/html/classvtkParametricRandomHills.html#details), [vtkParametricRoman](http://www.vtk.org/doc/nightly/html/classvtkParametricRoman.html#details), [vtkParametricSpline](http://www.vtk.org/doc/nightly/html/classvtkParametricSpline.html#details), [vtkParametricSuperEllipsoid](http://www.vtk.org/doc/nightly/html/classvtkParametricSuperEllipsoid.html#details), [vtkParametricSuperToroid](http://www.vtk.org/doc/nightly/html/classvtkParametricSuperToroid.html#details), [vtkParametricTorus](http://www.vtk.org/doc/nightly/html/classvtkParametricTorus.html#details) | Create and display a parametric object
[ParametricObjectsDemo](/CSharp/GeometricObjects/ParametricObjectsDemo) |  | Demonstration of all of the vtkParametric* classes

## Implicit Functions and Iso-surfaces

Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[IsoContours](/CSharp/ImplicitFunctions/IsoContours)|[vtkContourFunction](http://www.vtk.org/doc/nightly/html/classvtkContourFunction.html#details) | Visualize different isocontours using a slider
[SampleFunction](/CSharp/ImplicitFunctions/SampleFunction)|[vtkSampleFunction](http://www.vtk.org/doc/nightly/html/classvtkSampleFunction.html#details) | Sample and visualize an implicit function
[ExtractLargestIsosurface](/CSharp/Modelling/ExtractLargestIsosurface)|[vtkPolyDataConnectivityFilter](http://www.vtk.org/doc/nightly/html/classvtkPolyDataConnectivityFilter.html#details) | Extract largest isosurface
[BandedPolyDataContourFilter](/CSharp/VisualizationAlgorithms/BandedPolyDataContourFilter)|[vtkBandedPolyDataContourFilter](http://www.vtk.org/doc/nightly/html/classvtkBandedPolyDataContourFilter.html#details) | BandedPolyDataContourFilter
[FilledContours](/CSharp/VisualizationAlgorithms/FilledContours)|[vtkContourFilter](http://www.vtk.org/doc/nightly/html/classvtkContourFilter.html#details) | Create filled contours (vtkClipPolyData)
[ImplicitSphere](/CSharp/ImplicitFunctions/ImplicitSphere)|[vtkSphere](http://www.vtk.org/doc/nightly/html/classvtkSphere.html#details) | An implicit representation of a sphere
[MarchingCubes](/CSharp/Modelling/MarchingCubes)|[vtkMarchingCubes](http://www.vtk.org/doc/nightly/html/classvtkMarchingCubes.html#details) | Create a voxelized spher Marching cubes
[MarchingSquares](/CSharp/WishList/Modelling/MarchingSquares)|[vtkMarchingSquares](http://www.vtk.org/doc/nightly/html/classvtkMarchingSquares.html#details) | Create a contour from a structured point set (image Marching squares

## Working with 3D Data
Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[ShrinkPolyData](/CSharp/PolyData/ShrinkPolyData)|[vtkShrinkPolyData](http://www.vtk.org/doc/nightly/html/classvtkShrinkPolyData.html#details)| Move all items in a PolyData towards their centroid
[VectorFieldNonZeroExtraction](/CSharp/PolyData/VectorFieldNonZeroExtraction)|[vtkExtractSelectedThresholds](http://www.vtk.org/doc/nightly/html/classvtkExtractSelectedThresholds.html#details)| This example shows how to create an imagedata object, associate scalar data with some points and visualize only nonzero scalar value Extract non-zero vectors from a vtkImageData
[MultiBlockMergeFilter](/CSharp/PolyData/MultiBlockMergeFilter)|[vtkMultiBlockMergeFilter](http://www.vtk.org/doc/nightly/html/classvtkMultiBlockMergeFilter.html#details), [vtkMultiBlockDataSet](http://www.vtk.org/doc/nightly/html/classvtkMultiBlockDataSet.html#details) | Combine MultiBlockDataSets
[IterateOverLines](/CSharp/PolyData/IterateOverLines)|[vtkCellArray](http://www.vtk.org/doc/nightly/html/classvtkCellArray.html#details) | Iterate through the lines of a PolyData
[AlignFrames](/CSharp/PolyData/AlignFrames)|[vtkLandmarkTransform](http://www.vtk.org/doc/nightly/html/classvtkLandmarkTransform.html#details) | Align coordinate frames
[WarpVector](/CSharp/PolyData/WarpVector)|[vtkWarpVector](http://www.vtk.org/doc/nightly/html/classvtkWarpVector.html#details) | vtkWarpVector
[FindAllArrayNames](/CSharp/IO/FindAllArrayNames)|[vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details) | Get the names of all of the data arrays
[PolyDataGetPoint](/CSharp/PolyData/PolyDataGetPoint)|[vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details) | Get point locations/coordinates from a vtkPolyData
[NullPoint](/CSharp/PolyData/NullPoint)|[vtkPointData](http://www.vtk.org/doc/nightly/html/classvtkPointData.html#details) | Set everything in PointData at a specified index to NUL NullPoint
[ContoursFromPolyData](/CSharp/Filtering/ContoursFromPolyData) | [vtkCutter](http://www.vtk.org/doc/nightly/html/classvtkCutter.html#details) | Create contours from PolyData
[ImplicitBoolean](/CSharp/Filters/ImplicitBoolean) | [vtkImplicitBoolean](http://www.vtk.org/doc/nightly/html/classvtkImplicitBoolean.html#details) | Operations include intersection and union. | OperationsOnImplicitFunctions

### Working with Meshes

Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[MatrixMathFilter](/CSharp/Meshes/MatrixMathFilter)|[vtkMatrixMathFilter](http://www.vtk.org/doc/nightly/html/classvtkMatrixMathFilter.html#details) | Compute various quantities on cell and points in a mesh Matrix math filter
[WeightedTransformFilter](/CSharp/PolyData/WeightedTransformFilter) |  [vtkWeightedTransformFilter](http://www.vtk.org/doc/nightly/html/classvtkWeightedTransformFilter.html#details) | vtkWeightedTransformFilter 
[GreedyTerrainDecimation](/CSharp/PolyData/GreedyTerrainDecimation) |  [vtkGreedyTerrainDecimation](http://www.vtk.org/doc/nightly/html/classvtkGreedyTerrainDecimation.html#details) | Create a mesh from an ImageData 
[LargestRegion](/CSharp/PolyData/PolyDataConnectivityFilter_LargestRegion) |  [vtkPolyDataConnectivityFilter](http://www.vtk.org/doc/nightly/html/classvtkPolyDataConnectivityFilter.html#details) | Extract the largest connected region in a polydata
[SpecifiedRegion](/CSharp/PolyData/PolyDataConnectivityFilter_SpecifiedRegion) | [vtkPolyDataConnectivityFilter](http://www.vtk.org/doc/nightly/html/classvtkPolyDataConnectivityFilter.html#details) | Extract a specific (specified) connected region in a polydata
[ColorDisconnectedRegions](/CSharp/PolyData/ColorDisconnectedRegions) | [vtkPolyDataConnectivityFilter](http://www.vtk.org/doc/nightly/html/classvtkPolyDataConnectivityFilter.html#details) | Color each disconnected region of a vtkPolyData a different color
[Curvature](/CSharp/PolyData/Curvature)|[vtkCurvatures](http://www.vtk.org/doc/nightly/html/classvtkCurvatures.html#details) | Compute Gaussian, Mean, Min, and Max Curvatures
[HighlightBadCells](/CSharp/PolyData/HighlightBadCells)|[vtkMeshQuality](http://www.vtk.org/doc/nightly/html/classvtkMeshQuality.html#details) | Highlight Bad Cells
[PolygonalSurfaceContourLineInterpolator](/CSharp/PolyData/PolygonalSurfaceContourLineInterpolator)|[vtkPolygonalSurfaceContourLineInterpolator](http://www.vtk.org/doc/nightly/html/classvtkPolygonalSurfaceContourLineInterpolator.html#details) | Interactively find the shortest path between two points on a mesh
[DijkstraGraphGeodesicPath](/CSharp/PolyData/DijkstraGraphGeodesicPath)|[vtkDijkstraGraphGeodesicPath](http://www.vtk.org/doc/nightly/html/classvtkDijkstraGraphGeodesicPath.html#details) | Find the shortest path between two points on a mesh
[SelectPolyData](/CSharp/PolyData/SelectPolyData)|[vtkSelectPolyData](http://www.vtk.org/doc/nightly/html/classvtkSelectPolyData.html#details) | Select a region of a mesh
[ClosedSurface](/CSharp/PolyData/ClosedSurface)|[vtkFeatureEdges](http://www.vtk.org/doc/nightly/html/classvtkFeatureEdges.html#details) | Check if a surface is closed
[Decimate](/CSharp/Meshes/Decimate)|[vtkDecimatePro](http://www.vtk.org/doc/nightly/html/classvtkDecimatePro.html#details) | Reduce the number of triangles in a mesh Decimation
[QuadricDecimation](/CSharp/Meshes/QuadricDecimation)|[vtkQuadricDecimation](http://www.vtk.org/doc/nightly/html/classvtkQuadricDecimation.html#details) | Reduce the number of triangles in a mesh Decimation (quadric decimation)
[QuadricClustering](/CSharp/Meshes/QuadricClustering)|[vtkQuadricClustering](http://www.vtk.org/doc/nightly/html/classvtkQuadricClustering.html#details) | Reduce the number of triangles in a mesh Decimation (quadric clustering)
[Subdivision](/CSharp/Meshes/Subdivision)|[vtkButterflySubdivisionFilter](http://www.vtk.org/doc/nightly/html/classvtkButterflySubdivisionFilter.html#details), [vtkLoopSubdivisionFilter](http://www.vtk.org/doc/nightly/html/classvtkLoopSubdivisionFilter.html#details), [vtkLinearSubdivisionFilter](http://www.vtk.org/doc/nightly/html/classvtkLinearSubdivisionFilter.html#details) | Increase the number of triangles in a mesh Subdivision
[BoundaryEdges](/CSharp/Meshes/BoundaryEdges)|[vtkFeatureEdges](http://www.vtk.org/doc/nightly/html/classvtkFeatureEdges.html#details) | Find the edges that are used by only one face Finding Boundary Edges
[FillHoles](/CSharp/Meshes/FillHoles)|[vtkFillHolesFilter](http://www.vtk.org/doc/nightly/html/classvtkFillHolesFilter.html#details) | Close holes in a mesh Fill Holes
[WindowedSincPolyDataFilter](/CSharp/Meshes/WindowedSincPolyDataFilter)|[vtkWindowedSincPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkWindowedSincPolyDataFilter.html#details) | Smooth a mesh Windowed Sinc PolyData Filter|Smooth a mesh (windowed sinc filter)
[ColoredElevationMap](/CSharp/Meshes/ColoredElevationMap)|[vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html#details) | Colormap, color ma Color a mesh by height
[ElevationFilter](/CSharp/Meshes/ElevationFilter)|[vtkElevationFilter](http://www.vtk.org/doc/nightly/html/classvtkElevationFilter.html#details) | Color a mesh by height
[SimpleElevationFilter](/CSharp/Meshes/SimpleElevationFilter)|[vtkSimpleElevationFilter](http://www.vtk.org/doc/nightly/html/classvtkSimpleElevationFilter.html#details) | Color a mesh by dotting a vector from the origin to each point with a specified vector
[Triangulate](/CSharp/Meshes/Triangulate)|[vtkTriangleFilter](http://www.vtk.org/doc/nightly/html/classvtkTriangleFilter.html#details) | Convert all polygons in a mesh to triangles Triangulate a mesh
[ExtractEdges](/CSharp/Meshes/ExtractEdges)|[vtkExtractEdges](http://www.vtk.org/doc/nightly/html/classvtkExtractEdges.html#details) | Extract Edges
[CellEdges](/CSharp/Meshes/CellEdges)|[vtkCell](http://www.vtk.org/doc/nightly/html/classvtkCell.html#details) | Get edges of cells
[SolidClip](/CSharp/Meshes/SolidClip)|[vtkClipPolyData](http://www.vtk.org/doc/nightly/html/classvtkClipPolyData.html#details) | Create a "solid" clip
[CapClip](/CSharp/Meshes/CapClip)|[vtkClipPolyData](http://www.vtk.org/doc/nightly/html/classvtkClipPolyData.html#details) | Cap a clipped polydata with a polygon
[OBBDicer](/CSharp/Meshes/OBBDicer)|[vtkOBBDicer](http://www.vtk.org/doc/nightly/html/classvtkOBBDicer.html#details) | Breakup a mesh into pieces OBBDicer


### Working with Structured 3D Data

This section includes vtkImageData, vtkStructuredGrid, and vtkRectilinearGrid.

"ImageData" is not the traditional "flat, 2D image" you are used to. It is a special VTK data structure in the collection of 3D data structures provided by VTK. Here is an overview of these data structures: [http://vtk.org/Wiki/VTK/Tutorials/3DDataTypes]. Image data can represent at typical 2D image, but also, a 3D volume.
