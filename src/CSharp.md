I just started to maintain this page. So stay tuned. In the near future you will find useful examples here from time to time.<br />
A tutorial on how to setup a Windows Forms Application utilizing ActiViz.NET can be found here: [http://www.vtk.org/Wiki/VTK/CSharp/ActiViz.NET Setup a Windows Forms Application to use ActiViz.NET]

## Simple Operations
| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
| [DistancePointToLine](/CSharp/SimpleOperations/DistancePointToLine) | {{DoxygenURL|vtkLine}} | Distance between a point and a line
| [DistanceBetweenPoints](/CSharp/SimpleOperations/DistanceBetweenPoints) | [http://www.vtk.org/doc/nightly/html/classvtkMath.html#a11944eda4bd17e4e57bcd1e49c2f9446 vtkMath::Distance2BetweenPoints] || Computes the distance between two point Distance between two points
| [UniformRandomNumber](/CSharp/SimpleOperations/UniformRandomNumber) | {{DoxygenURL|vtkMath}} || Generates uniform random number Random number (uniform distribution)
| [GaussianRandomNumber](/CSharp/SimpleOperations/GaussianRandomNumber) | {{DoxygenURL|vtkMath}} || Generates Gaussian random number Random number (Gaussian distribution)
| [RandomSequence](/CSharp/SimpleOperations/RandomSequence)|{{DoxygenURL|vtkMinimalStandardRandomSequence}} || This is the preferred way to generate random numbers Random sequence
| [ProjectPointPlane](/CSharp/SimpleOperations/ProjectPointPlane)|{{DoxygenURL|vtkPlane}} || Project a point onto a plan Project a point onto a plane
| [PerspectiveTransform](/CSharp/SimpleOperations/PerspectiveTransform)|{{VTKDoxygenURL|vtkPerspectiveTransform}} | Apply a perspective transformation to a point

## Input and Output
### Graph Formats

### 3D File Formats
| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
| [ConvertFile](/CSharp/IO/ConvertFile) |  | Convert a file from one type to another
| [XGMLReader](/CSharp/InfoVis/XGMLReader) | {{VTKDoxygenURL|vtkXGMLReader}} | Read a .gml file


#### Standard Formats
##### Input
| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|

| [SimplePointsReader](/CSharp/IO/SimplePointsReader) | {{VTKDoxygenURL|vtkSimplePointsReader}} | Read a simple "xyz" file of points
| [ParticleReader](/CSharp/IO/ParticleReader)|{{VTKDoxygenURL|vtkParticleReader}} || This example reads ascii files where each line consists of points with its position (x,y,z) and (optionally) one scalar or binary files in RAW 3d file forma Read an "xyza" file

| [ReadPlainText](/CSharp/IO/ReadPlainText) | {{VTKDoxygenURL|vtkPolyData}} || Manually read a file using a streamreade Read a plain text file into a polydata
| [ReadOBJ](/CSharp/IO/ReadOBJ) | {{VTKDoxygenURL|vtkOBJReader}} | Read an OBJ (.obj) File
| [ReadDICOMSeries](/CSharp/IO/ReadDICOMSeries) | {{VTKDoxygenURL|vtkDICOMImageReader}} || This example demonstates how to read a series of DICOM images and scroll through slice Convert a series of DICOM files into a VTI File
| [VRML](/CSharp/IO/VRML)|{{VTKDoxygenURL|vtkVRMLImporter}} | Read a VRML (WRL) file
| [DumpXMLFile](/CSharp/IO/DumpXMLFile)|{{VTKDoxygenURL|vtkDataSetReader}} | Report the contents of a VTK XML or legacy file
| [DEMReader](/CSharp/IO/DEMReader) | {{VTKDoxygenURL|vtkDEMReader}} || Read DEM (elevation map) files
| [ReadSTL](/CSharp/IO/ReadSTL) | {{VTKDoxygenURL|vtkSTLReader}} | Read stereo lithography STL (.stl) files
| [ReadPLY](/CSharp/IO/ReadPLY) | {{VTKDoxygenURL|vtkPLYReader}} | Read PLY (.ply) files
| [ReadPLOT3D](/CSharp/IO/ReadPLOT3D) | {{VTKDoxygenURL|vtkPLOT3DReader}} || Read CFD (computational fluid dynamics) data produced by PLOT3D Read PLOT3D (.bin) files
| [ReadPDB](/CSharp/IO/ReadPDB) | {{VTKDoxygenURL|vtkPDBReader}} || Read Protein Data Bank Files Read Protein Data Bank files (.pdb) files

##### Output
| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|

| [SimplePointsWriter](/CSharp/IO/SimplePointsWriter) | {{VTKDoxygenURL|vtkSimplePointsWriter}} | Write a simple ".xyz" file
| [WriteSTL](/CSharp/IO/WriteSTL) | {{VTKDoxygenURL|vtkSTLWriter}} | Write stereo lithography STL (.stl) files
| [WritePLY](/CSharp/IO/WritePLY) | {{VTKDoxygenURL|vtkPLYWriter}} | Write PLY (.ply) files
| [DelimitedTextWriter](/CSharp/InfoVis/DelimitedTextWriter) | {{VTKDoxygenURL|vtkDelimitedTextWriter}} | Write data to a delimited file

#### VTK Formats
##### Input 

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
| [ReadUnstructuredGrid](/CSharp/IO/ReadUnstructuredGrid)|{{VTKDoxygenURL|vtkXMLUnstructuredGridReader}} ||Demonstrates how to read a .vtu fil Read an unstructured grid (.vtu) file
| [ReadPolyData](/CSharp/IO/ReadPolyData)|{{VTKDoxygenURL|vtkXMLPolyDataReader}} | Read a polygonal data (.vtp) file
| [ReadImageData](/CSharp/IO/ReadImageData)|{{VTKDoxygenURL|vtkXMLImageDataReader}} | Read a image data (.vti) file
| [ReadStructuredGrid](/CSharp/IO/ReadStructuredGrid)|{{VTKDoxygenURL|vtkXMLStructuredGridReader}} | Read a structured grid (.vts) file
| [ReadRectilinearGrid](/CSharp/IO/ReadRectilinearGrid)|{{VTKDoxygenURL|vtkXMLRectilinearGridReader}} | Read a rectilinear grid (.vtr) file
| [ReadUnknownTypeXMLFile](/CSharp/IO/ReadUnknownTypeXMLFile)|{{VTKDoxygenURL|vtkXMLGenericDataObjectReader}} | Read an XML file and later decide what kind it is

##### Output

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
| [WriteVTU](/CSharp/IO/WriteVTU)|{{VTKDoxygenURL|vtkXMLUnstructuredGridWriter}} || VTU is an "Unstructured Grid". This format allows for 3D data to be stored Write a .vtu file
| [WriteVTP](/CSharp/IO/WriteVTP)|{{VTKDoxygenURL|vtkXMLPolyDataWriter}} || VTP is a "PolyData". This format allows for the most complex geometric objects to be stored Write a .vtp file
| [WriteVTI](/CSharp/IO/WriteVTI)|{{VTKDoxygenURL|vtkXMLImageDataWriter}} || VTI is an "ImageData" Write a .vti file
| [XMLStructuredGridWriter](/CSharp/IO/XMLStructuredGridWriter)|{{VTKDoxygenURL|vtkXMLStructuredGridWriter}} || Write a .vts file from a vtkStructuredGrid


### Image Formats

#### Input
| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
| [ReadBMP](/CSharp/IO/ReadBMP) | {{VTKDoxygenURL|vtkBMPReader}} | Read BMP (.bmp) files
| [JPEGReader](/CSharp/IO/JPEGReader)|{{VTKDoxygenURL|vtkJPEGReader}}| Read a JPG image
| [PNGReader](/CSharp/IO/PNGReader)|{{VTKDoxygenURL|vtkPNGReader}}| Read a PNG image
| [ReadPNM](/CSharp/IO/ReadPNM) | {{VTKDoxygenURL|vtkPNMReader}} | Read PNM (.pnm) files
| [ReadTIFF](/CSharp/IO/ReadTIFF) | {{VTKDoxygenURL|vtkTIFFReader}} | Read TIFF (.tif) files
| [MetaImageReader](/CSharp/IO/MetaImageReader) | {{VTKDoxygenURL|vtkMetaImageReader}} | Read .mha files
| [ImageReader2Factory](/CSharp/IO/ImageReader2Factory)|{{VTKDoxygenURL|vtkImageReader2Factory}} || This class tries to find an appropriate reader. It is very convenient to use this when you don't know what kind of file to expect Read most standard image formats.

#### Output

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
| [WriteBMP](/CSharp/IO/WriteBMP) | {{VTKDoxygenURL|vtkBMPWriter}} | Write a BMP (.bmp) file
| [JPEGWriter](/CSharp/IO/JPEGWriter) | {{VTKDoxygenURL|vtkJPEGWriter}} | Write a JPEG (.jpg) file
| [WritePNG](/CSharp/IO/WritePNG) | {{VTKDoxygenURL|vtkPNGWriter}} | Write a PNG (.png) file
| [WritePNM](/CSharp/IO/WritePNM) | {{VTKDoxygenURL|vtkPNMWriter}} | Write a PNM (.pnm) file
| [WriteTIFF](/CSharp/IO/WriteTIFF) | {{VTKDoxygenURL|vtkTIFFWriter}} | Write a TIFF (.tif) file
| [MetaImageWriter](/CSharp/IO/MetaImageWriter) | {{VTKDoxygenURL|vtkMetaImageWriter}} | Write a .mha/.mhd + .raw file

## Geometric Objects

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
| [PolygonIntersection](/CSharp/GeometricObjects/PolygonIntersection)| {{VTKDoxygenURL|vtkPolygon}} || IntersectWithLine( Compute the intersection of a line segment with a polygon
| [GeometricObjectsDemo](/CSharp/GeometricObjects/GeometricObjectsDemo)|  | A demonstration of all geometric objects that work the same way
| [Arrow](/CSharp/GeometricObjects/Arrow)| {{VTKDoxygenURL|vtkArrowSource}} | Arrow
| [Axes](/CSharp/GeometricObjects/Axes)| {{VTKDoxygenURL|vtkAxesActor}} | Axes
| [ColoredLines](/CSharp/GeometricObjects/ColoredLines)  |{{VTKDoxygenURL|vtkCellData}} {{VTKDoxygenURL|vtkLine}} | Colored Lines
| [Cone](/CSharp/GeometricObjects/Cone) | {{VTKDoxygenURL|vtkConeSource}} | Cone
| [Cube](/CSharp/GeometricObjects/Cube) | {{VTKDoxygenURL|vtkCubeSource}} | Cube
| [Cylinder](/CSharp/GeometricObjects/Cylinder) | {{VTKDoxygenURL|vtkCylinderSource}} | Cylinder
| [Disk](/CSharp/GeometricObjects/Disk) | {{VTKDoxygenURL|vtkDiskSource}} || A circle with a hole in it Disk
| [Frustum](/CSharp/GeometricObjects/Frustum) | {{VTKDoxygenURL|vtkFrustumSource}} | Frustum
| [Line](/CSharp/GeometricObjects/Line) | {{VTKDoxygenURL|vtkLineSource}} | Line
| [LongLine](/CSharp/GeometricObjects/LongLine) | {{VTKDoxygenURL|vtkLine}} | Manually create a polyline
| [Hexahedron](/CSharp/GeometricObjects/Hexahedron) | {VTKDoxygenURL|vtkHexahedron}} | Hexahedron
| [OrientedArrow](/CSharp/GeometricObjects/OrientedArrow) | {{VTKDoxygenURL|vtkArrowSource}} | Oriented Arrow
| [Plane](/CSharp/GeometricObjects/Plane) | {VTKDoxygenURL|vtkPlaneSource}} | Plane
| [Planes](/CSharp/GeometricObjects/Planes) | {VTKDoxygenURL|vtkPlanes}} | Planes
| [PlanesIntersection](/CSharp/GeometricObjects/PlanesIntersection) | {VTKDoxygenURL|vtkPlanesIntersection}} | PlanesIntersection
| [PlatonicSolid](/CSharp/GeometricObjects/PlatonicSolid) | {{VTKDoxygenURL|vtkPlatonicSolidSource}} | PlatonicSolid
| [Point](/CSharp/GeometricObjects/Point) | {{VTKDoxygenURL|vtkPoints}} | Point
| [Polygon](/CSharp/GeometricObjects/Polygon) | {{VTKDoxygenURL|vtkPolygon}} | Polygon
| [Pyramid](/CSharp/GeometricObjects/Pyramid) | {{VTKDoxygenURL|vtkPyramid}} | Pyramid
| [PolyLine](/CSharp/GeometricObjects/PolyLine) | {{VTKDoxygenURL|vtkPolyLine}} | PolyLine
| [Quad](/CSharp/GeometricObjects/Quad) | {{VTKDoxygenURL|vtkQuad}} | Quad
| [RegularPolygonSource](/CSharp/GeometricObjects/RegularPolygonSource) | {{VTKDoxygenURL|vtkRegularPolygonSource}} | Regular Polygon
| [Sphere](/CSharp/GeometricObjects/Sphere) | {{VTKDoxygenURL|vtkSphereSource}} | Sphere
| [Triangle](/CSharp/GeometricObjects/Triangle) | {{VTKDoxygenURL|vtkTriangle}} | Triangle
| [TriangleStrip](/CSharp/GeometricObjects/TriangleStrip)|{{VTKDoxygenURL|vtkTriangleStrip}} || Triangle strip
| [Tetrahedron](/CSharp/GeometricObjects/Tetrahedron) | {{VTKDoxygenURL|vtkTetra}} | Tetrahedron
| [Vertex](/CSharp/GeometricObjects/Vertex) | {{VTKDoxygenURL|vtkVertex}} | Vertex

### Parametric Objects
These examples demonstrate how to create an display one of the many vtkParametric* objects. All of the classes listed can be used in an identical fashion.

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|


| [ParametricObjects](/CSharp/GeometricObjects/ParametricObjects) | {{VTKDoxygenURL|vtkParametricBoy}}, {{VTKDoxygenURL|vtkParametricConicSpiral}}, {{VTKDoxygenURL|vtkParametricCrossCap}}, {{VTKDoxygenURL|vtkParametricDini}}, {{VTKDoxygenURL|vtkParametricEllipsoid}}, {{VTKDoxygenURL|vtkParametricEnneper}}, {{VTKDoxygenURL|vtkParametricFigure8Klein}}, {{VTKDoxygenURL|vtkParametricKlein}}, {{VTKDoxygenURL|vtkParametricMobius}}, {{VTKDoxygenURL|vtkParametricRandomHills}}, {{VTKDoxygenURL|vtkParametricRoman}}, {{VTKDoxygenURL|vtkParametricSpline}}, {{VTKDoxygenURL|vtkParametricSuperEllipsoid}}, {{VTKDoxygenURL|vtkParametricSuperToroid}}, {{VTKDoxygenURL|vtkParametricTorus}} | Create and display a parametric object
| [ParametricObjectsDemo](/CSharp/GeometricObjects/ParametricObjectsDemo) |  | Demonstration of all of the vtkParametric* classes

## Implicit Functions and Iso-surfaces

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
| [IsoContours](/CSharp/ImplicitFunctions/IsoContours)|{{VTKDoxygenURL|vtkContourFunction}} | Visualize different isocontours using a slider
| [SampleFunction](/CSharp/ImplicitFunctions/SampleFunction)|{{VTKDoxygenURL|vtkSampleFunction}} | Sample and visualize an implicit function
| [ExtractLargestIsosurface](/CSharp/Modelling/ExtractLargestIsosurface)|{{VTKDoxygenURL|vtkPolyDataConnectivityFilter}} | Extract largest isosurface
| [BandedPolyDataContourFilter](/CSharp/VisualizationAlgorithms/BandedPolyDataContourFilter)|{{VTKDoxygenURL|vtkBandedPolyDataContourFilter}} | BandedPolyDataContourFilter
| [FilledContours](/CSharp/VisualizationAlgorithms/FilledContours)|{{VTKDoxygenURL|vtkContourFilter}} | Create filled contours (vtkClipPolyData)
| [ImplicitSphere](/CSharp/ImplicitFunctions/ImplicitSphere)|{{VTKDoxygenURL|vtkSphere}} || An implicit representation of a sphere
| [MarchingCubes](/CSharp/Modelling/MarchingCubes)|{{VTKDoxygenURL|vtkMarchingCubes}} || Create a voxelized spher Marching cubes
| [MarchingSquares](/CSharp/WishList/Modelling/MarchingSquares)|{{VTKDoxygenURL|vtkMarchingSquares}} || Create a contour from a structured point set (image Marching squares

## Working with 3D Data
| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
| [CenterOfMass](/CSharp/PolyData/CenterOfMass)|{{VTKDoxygenURL|CenterOfMass}}|| vtkCenterOfMass not implemented yet in ActiViz.NE Compute the center of mass of the points
| [BooleanOperationPolyDataFilter](/CSharp/PolyData/BooleanOperationPolyDataFilter)|{{VTKDoxygenURL|BooleanOperationPolyDataFilter}}|| vtkBooleanOperationPolyDataFilter not implemented yet in ActiViz.NE Perform boolean operations on two vtkPolyData objects
| [DistancePolyDataFilter](/CSharp/PolyData/DistancePolyDataFilter)|{{VTKDoxygenURL|DistancePolyDataFilter}}|| vtkDistancePolyDataFilter not implemented yet in ActiViz.NE Compute the distance function from one vtkPolyData to another
| [ImplicitPolyDataDistance](/CSharp/PolyData/ImplicitPolyDataDistance)|{{VTKDoxygenURL|ImplicitPolyDataDistance}}|| vtkImplicitPolyDataDistance not implemented yet in ActiViz.NE Compute the distance function in a space around a vtkPolyData
| [IntersectionPolyDataFilter](/CSharp/PolyData/IntersectionPolyDataFilter)|{{VTKDoxygenURL|IntersectionPolyDataFilter}}|| vtkIntersectionPolyDataFilter not implemented yet in ActiViz.NE Compute the intersection of two vtkPolyData objects
| [ShrinkPolyData](/CSharp/PolyData/ShrinkPolyData)|{{VTKDoxygenURL|vtkShrinkPolyData}}| Move all items in a PolyData towards their centroid
| [VectorFieldNonZeroExtraction](/CSharp/PolyData/VectorFieldNonZeroExtraction)|{{VTKDoxygenURL|vtkExtractSelectedThresholds}}|| This example shows how to create an imagedata object, associate scalar data with some points and visualize only nonzero scalar value Extract non-zero vectors from a vtkImageData
| [MultiBlockMergeFilter](/CSharp/PolyData/MultiBlockMergeFilter)|{{VTKDoxygenURL|vtkMultiBlockMergeFilter}}, {{VTKDoxygenURL|vtkMultiBlockDataSet}} || Combine MultiBlockDataSets
| [IterateOverLines](/CSharp/PolyData/IterateOverLines)|{{VTKDoxygenURL|vtkCellArray}} || Iterate through the lines of a PolyData
| [AlignFrames](/CSharp/PolyData/AlignFrames)|{{VTKDoxygenURL|vtkLandmarkTransform}} || Align coordinate frames
| [WarpVector](/CSharp/PolyData/WarpVector)|{{VTKDoxygenURL|vtkWarpVector}} || vtkWarpVector
| [FindAllArrayNames](/CSharp/IO/FindAllArrayNames)|{{VTKDoxygenURL|vtkPolyData}} || Get the names of all of the data arrays
| [PolyDataGetPoint](/CSharp/PolyData/PolyDataGetPoint)|{{VTKDoxygenURL|vtkPolyData}} || Get point locations/coordinates from a vtkPolyData
| [NullPoint](/CSharp/PolyData/NullPoint)|{{VTKDoxygenURL|vtkPointData}} || Set everything in PointData at a specified index to NUL NullPoint
| [ContoursFromPolyData](/CSharp/Filtering/ContoursFromPolyData) | {{VTKDoxygenURL|vtkCutter}} | Create contours from PolyData
| [ImplicitBoolean](/CSharp/Filters/ImplicitBoolean) | {{VTKDoxygenURL|vtkImplicitBoolean}} || Operations include intersection and union. | OperationsOnImplicitFunctions

### Working with Meshes

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
| [MatrixMathFilter](/CSharp/Meshes/MatrixMathFilter)|{{VTKDoxygenURL|vtkMatrixMathFilter}} || Compute various quantities on cell and points in a mesh Matrix math filter
| [WeightedTransformFilter](/CSharp/PolyData/WeightedTransformFilter) |  {{VTKDoxygenURL|vtkWeightedTransformFilter}} | vtkWeightedTransformFilter 
| [GreedyTerrainDecimation](/CSharp/PolyData/GreedyTerrainDecimation) |  {{VTKDoxygenURL|vtkGreedyTerrainDecimation}} | Create a mesh from an ImageData 
| [LargestRegion](/CSharp/PolyData/vtkPolyDataConnectivityFilter_LargestRegion) |  {{VTKDoxygenURL|vtkPolyDataConnectivityFilter}} | Extract the largest connected region in a polydata
| [SpecifiedRegion](/CSharp/PolyData/vtkPolyDataConnectivityFilter_SpecifiedRegion) | {{VTKDoxygenURL|vtkPolyDataConnectivityFilter}} | Extract a specific (specified) connected region in a polydata
| [ColorDisconnectedRegions](/CSharp/PolyData/ColorDisconnectedRegions) | {{VTKDoxygenURL|vtkPolyDataConnectivityFilter}} | Color each disconnected region of a vtkPolyData a different color
| [Curvatures](/CSharp/PolyData/Curvatures)|{{VTKDoxygenURL|vtkCurvatures}} | Compute Gaussian, Mean, Min, and Max Curvatures
| [MeshQuality](/CSharp/PolyData/MeshQuality)|{{VTKDoxygenURL|vtkMeshQuality}} | Mesh Quality
| [HighlightBadCells](/CSharp/PolyData/HighlightBadCells)|{{VTKDoxygenURL|vtkMeshQuality}} | Highlight Bad Cells
| [PolygonalSurfaceContourLineInterpolator](/CSharp/PolyData/PolygonalSurfaceContourLineInterpolator)|{{VTKDoxygenURL|vtkPolygonalSurfaceContourLineInterpolator}} | Interactively find the shortest path between two points on a mesh
| [DijkstraGraphGeodesicPath](/CSharp/PolyData/DijkstraGraphGeodesicPath)|{{VTKDoxygenURL|vtkDijkstraGraphGeodesicPath}} | Find the shortest path between two points on a mesh
| [SelectPolyData](/CSharp/PolyData/SelectPolyData)|{{VTKDoxygenURL|vtkSelectPolyData}} | Select a region of a mesh
| [SmoothPolyDataFilter](/CSharp/PolyData/SmoothPolyDataFilter)|{{VTKDoxygenURL|vtkSmoothPolyDataFilter}} | Laplacian smoothing
| [ClosedSurface](/CSharp/PolyData/ClosedSurface)|{{VTKDoxygenURL|vtkFeatureEdges}} | Check if a surface is closed
| [Decimation](/CSharp/Meshes/Decimation)|{{VTKDoxygenURL|vtkDecimatePro}} || Reduce the number of triangles in a mesh Decimation
| [QuadricDecimation](/CSharp/Meshes/QuadricDecimation)|{{VTKDoxygenURL|vtkQuadricDecimation}} || Reduce the number of triangles in a mesh Decimation (quadric decimation)
| [QuadricClustering](/CSharp/Meshes/QuadricClustering)|{{VTKDoxygenURL|vtkQuadricClustering}} || Reduce the number of triangles in a mesh Decimation (quadric clustering)
| [Subdivision](/CSharp/Meshes/Subdivision)|{{VTKDoxygenURL|vtkButterflySubdivisionFilter}}, {{VTKDoxygenURL|vtkLoopSubdivisionFilter}}, {{VTKDoxygenURL|vtkLinearSubdivisionFilter}} || Increase the number of triangles in a mesh Subdivision
| [BoundaryEdges](/CSharp/Meshes/BoundaryEdges)|{{VTKDoxygenURL|vtkFeatureEdges}} || Find the edges that are used by only one face Finding Boundary Edges
| [FillHoles](/CSharp/Meshes/FillHoles)|{{VTKDoxygenURL|vtkFillHolesFilter}} || Close holes in a mesh Fill Holes
| [WindowedSincPolyDataFilter](/CSharp/Meshes/WindowedSincPolyDataFilter)|{{VTKDoxygenURL|vtkWindowedSincPolyDataFilter}} || Smooth a mesh Windowed Sinc PolyData Filter|Smooth a mesh (windowed sinc filter)
| [height](/CSharp/Meshes/Color a mesh by height)|{VTKDoxygenURL|vtkLookupTable}} || Colormap, color ma Color a mesh by height
| [ElevationFilter](/CSharp/Meshes/ElevationFilter)|{{VTKDoxygenURL|vtkElevationFilter}} | Color a mesh by height
| [SimpleElevationFilter](/CSharp/Meshes/SimpleElevationFilter)|{{VTKDoxygenURL|vtkSimpleElevationFilter}} | Color a mesh by dotting a vector from the origin to each point with a specified vector
| [mesh](/CSharp/Meshes/Triangulate a mesh)|{{VTKDoxygenURL|vtkTriangleFilter}} || Convert all polygons in a mesh to triangles Triangulate a mesh
| [ExtractEdges](/CSharp/Meshes/ExtractEdges)|{{VTKDoxygenURL|vtkExtractEdges}} | Extract Edges
| [CellEdges](/CSharp/Meshes/CellEdges)|{{VTKDoxygenURL|vtkCell}} | Get edges of cells
| [SolidClip](/CSharp/Meshes/SolidClip)|{{VTKDoxygenURL|vtkClipPolyData}} | Create a "solid" clip
| [CapClip](/CSharp/Meshes/CapClip)|{{VTKDoxygenURL|vtkClipPolyData}} | Cap a clipped polydata with a polygon
| [OBBDicer](/CSharp/Meshes/OBBDicer)|{{VTKDoxygenURL|vtkOBBDicer}} || Breakup a mesh into pieces OBBDicer


### Working with Structured 3D Data

This section includes vtkImageData, vtkStructuredGrid, and vtkRectilinearGrid.

"ImageData" is not the traditional "flat, 2D image" you are used to. It is a special VTK data structure in the collection of 3D data structures provided by VTK. Here is an overview of these data structures: [http://vtk.org/Wiki/VTK/Tutorials/3DDataTypes]. Image data can represent at typical 2D image, but also, a 3D volume.

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[StructuredDataTypes](/CSharp/Visualization/StructuredDataTypes) | | Demonstration of structured data types
[GetLinearPointId](/CSharp/StructuredData/GetLinearPointId) | | Get the linear point id of a point in a grid
