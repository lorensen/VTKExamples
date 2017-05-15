I just started to maintain this page. So stay tuned. In the near future you will find useful examples here from time to time.<br />
A tutorial on how to setup a Windows Forms Application utilizing ActiViz.NET can be found here: [http://www.vtk.org/Wiki/VTK/CSharp/ActiViz.NET Setup a Windows Forms Application to use ActiViz.NET]

==Simple Operations==
{{VTKExamplesTable}}
|-
| [[VTK/Examples/CSharp/SimpleOperations/DistancePointToLine | Distance between a point and a line]] || {{DoxygenURL|vtkLine}} ||
|-
| [[VTK/Examples/CSharp/SimpleOperations/DistanceBetweenPoints | Distance between two points]] || [http://www.vtk.org/doc/nightly/html/classvtkMath.html#a11944eda4bd17e4e57bcd1e49c2f9446 vtkMath::Distance2BetweenPoints] || Computes the distance between two points
|-
| [[VTK/Examples/CSharp/SimpleOperations/UniformRandomNumber | Random number (uniform distribution)]] || {{DoxygenURL|vtkMath}} || Generates uniform random numbers
|-
| [[VTK/Examples/CSharp/SimpleOperations/GaussianRandomNumber | Random number (Gaussian distribution)]] || {{DoxygenURL|vtkMath}} || Generates Gaussian random numbers
|-
| [[VTK/Examples/CSharp/SimpleOperations/RandomSequence|Random sequence]] || {{DoxygenURL|vtkMinimalStandardRandomSequence}} || This is the preferred way to generate random numbers.
|-
| [[VTK/Examples/CSharp/SimpleOperations/ProjectPointPlane|Project a point onto a plane]] || {{DoxygenURL|vtkPlane}} || Project a point onto a plane
|-
| [[VTK/Examples/CSharp/SimpleOperations/PerspectiveTransform|Apply a perspective transformation to a point]] || {{VTKDoxygenURL|vtkPerspectiveTransform}} ||
|}

==Input and Output==
===Graph Formats===

===3D File Formats===
{{VTKExamplesTable}}
|-
| [[VTK/Examples/CSharp/IO/ConvertFile | Convert a file from one type to another]] ||  ||
|-
| [[VTK/Examples/CSharp/InfoVis/XGMLReader | Read a .gml file]] || {{VTKDoxygenURL|vtkXGMLReader}} ||
|}


====Standard Formats====
=====Input=====
{{VTKExamplesTable}}
|-
| [[VTK/Examples/CSharp/IO/SimplePointsReader | Read a simple "xyz" file of points]] || {{VTKDoxygenURL|vtkSimplePointsReader}} ||
|-
| [[VTK/Examples/CSharp/IO/ParticleReader|Read an "xyza" file]] || {{VTKDoxygenURL|vtkParticleReader}} || This example reads ascii files where each line consists of points with its position (x,y,z) and (optionally) one scalar or binary files in RAW 3d file format
|-
| [[VTK/Examples/CSharp/IO/ReadPlainText | Read a plain text file into a polydata]] || {{VTKDoxygenURL|vtkPolyData}} || Manually read a file using a streamreader
|-
| [[VTK/Examples/CSharp/IO/ReadOBJ | Read an OBJ (.obj) File]] || {{VTKDoxygenURL|vtkOBJReader}} ||
|-
| [[VTK/Examples/CSharp/IO/ReadDICOMSeries | Convert a series of DICOM files into a VTI File]] || {{VTKDoxygenURL|vtkDICOMImageReader}} || This example demonstates how to read a series of DICOM images and scroll through slices
|-
| [[VTK/Examples/CSharp/IO/VRML|Read a VRML (WRL) file]] || {{VTKDoxygenURL|vtkVRMLImporter}} ||
|-
| [[VTK/Examples/CSharp/IO/DumpXMLFile|Report the contents of a VTK XML or legacy file]] || {{VTKDoxygenURL|vtkDataSetReader}} ||
|-
| [[VTK/Examples/CSharp/IO/DEMReader | Read DEM (elevation map) files]] || {{VTKDoxygenURL|vtkDEMReader}} || 
|-
| [[VTK/Examples/CSharp/IO/ReadSTL | Read stereo lithography STL (.stl) files]] || {{VTKDoxygenURL|vtkSTLReader}} ||
|-
| [[VTK/Examples/CSharp/IO/ReadPLY | Read PLY (.ply) files]] || {{VTKDoxygenURL|vtkPLYReader}} ||
|-
| [[VTK/Examples/CSharp/IO/ReadPLOT3D | Read PLOT3D (.bin) files]] || {{VTKDoxygenURL|vtkPLOT3DReader}} || Read CFD (computational fluid dynamics) data produced by PLOT3D.
|-
| [[VTK/Examples/CSharp/IO/ReadPDB | Read Protein Data Bank files (.pdb) files]] || {{VTKDoxygenURL|vtkPDBReader}} || Read Protein Data Bank Files.
|}

=====Output=====
{{VTKExamplesTable}}
|-
| [[VTK/Examples/CSharp/IO/SimplePointsWriter | Write a simple ".xyz" file]] || {{VTKDoxygenURL|vtkSimplePointsWriter}} ||
|-
| [[VTK/Examples/CSharp/IO/WriteSTL | Write stereo lithography STL (.stl) files]] || {{VTKDoxygenURL|vtkSTLWriter}} ||
|-
| [[VTK/Examples/CSharp/IO/WritePLY | Write PLY (.ply) files]] || {{VTKDoxygenURL|vtkPLYWriter}} ||
|-
| [[VTK/Examples/CSharp/InfoVis/DelimitedTextWriter | Write data to a delimited file]] || {{VTKDoxygenURL|vtkDelimitedTextWriter}} ||
|}

====VTK Formats====
=====Input=====

{{VTKExamplesTable}}
|-
| [[VTK/Examples/CSharp/IO/ReadUnstructuredGrid|Read an unstructured grid (.vtu) file]] || {{VTKDoxygenURL|vtkXMLUnstructuredGridReader}} ||Demonstrates how to read a .vtu file
|-
| [[VTK/Examples/CSharp/IO/ReadPolyData|Read a polygonal data (.vtp) file]] || {{VTKDoxygenURL|vtkXMLPolyDataReader}} ||
|-
| [[VTK/Examples/CSharp/IO/ReadImageData|Read a image data (.vti) file]] || {{VTKDoxygenURL|vtkXMLImageDataReader}} ||
|-
| [[VTK/Examples/CSharp/IO/ReadStructuredGrid|Read a structured grid (.vts) file]] || {{VTKDoxygenURL|vtkXMLStructuredGridReader}} ||
|-
| [[VTK/Examples/CSharp/IO/ReadRectilinearGrid|Read a rectilinear grid (.vtr) file]] || {{VTKDoxygenURL|vtkXMLRectilinearGridReader}} ||
|-
| [[VTK/Examples/CSharp/IO/ReadUnknownTypeXMLFile|Read an XML file and later decide what kind it is]] || {{VTKDoxygenURL|vtkXMLGenericDataObjectReader}} ||
|}

=====Output=====

{{VTKExamplesTable}}
|-
| [[VTK/Examples/CSharp/IO/WriteVTU|Write a .vtu file]] || {{VTKDoxygenURL|vtkXMLUnstructuredGridWriter}} || VTU is an "Unstructured Grid". This format allows for 3D data to be stored.
|-
| [[VTK/Examples/CSharp/IO/WriteVTP|Write a .vtp file]] || {{VTKDoxygenURL|vtkXMLPolyDataWriter}} || VTP is a "PolyData". This format allows for the most complex geometric objects to be stored.
|-
| [[VTK/Examples/CSharp/IO/WriteVTI|Write a .vti file]] || {{VTKDoxygenURL|vtkXMLImageDataWriter}} || VTI is an "ImageData".
|-
| [[VTK/Examples/CSharp/IO/XMLStructuredGridWriter|Write a .vts file from a vtkStructuredGrid]] || {{VTKDoxygenURL|vtkXMLStructuredGridWriter}} || 
|}

====Legacy VTK Formats====

{{VTKExamplesTable}}
|}

===Image Formats===

====Input====
{{VTKExamplesTable}}
|-
| [[VTK/Examples/CSharp/IO/ReadBMP | Read BMP (.bmp) files]] || {{VTKDoxygenURL|vtkBMPReader}} ||
|-
| [[VTK/Examples/CSharp/IO/JPEGReader|Read a JPG image]] || {{VTKDoxygenURL|vtkJPEGReader}}||
|-
| [[VTK/Examples/CSharp/IO/PNGReader|Read a PNG image]] || {{VTKDoxygenURL|vtkPNGReader}}||
|-
| [[VTK/Examples/CSharp/IO/ReadPNM | Read PNM (.pnm) files]] || {{VTKDoxygenURL|vtkPNMReader}} ||
|-
| [[VTK/Examples/CSharp/IO/ReadTIFF | Read TIFF (.tif) files]] || {{VTKDoxygenURL|vtkTIFFReader}} ||
|-
| [[VTK/Examples/CSharp/IO/MetaImageReader | Read .mha files]] || {{VTKDoxygenURL|vtkMetaImageReader}} ||
|-
| [[VTK/Examples/CSharp/IO/ImageReader2Factory|Read most standard image formats.]] || {{VTKDoxygenURL|vtkImageReader2Factory}} || This class tries to find an appropriate reader. It is very convenient to use this when you don't know what kind of file to expect.
|}

====Output====

{{VTKExamplesTable}}
|-
| [[VTK/Examples/CSharp/IO/WriteBMP | Write a BMP (.bmp) file]] || {{VTKDoxygenURL|vtkBMPWriter}} ||
|-
| [[VTK/Examples/CSharp/IO/JPEGWriter | Write a JPEG (.jpg) file]] || {{VTKDoxygenURL|vtkJPEGWriter}} ||
|-
| [[VTK/Examples/CSharp/IO/WritePNG | Write a PNG (.png) file]] || {{VTKDoxygenURL|vtkPNGWriter}} ||
|-
| [[VTK/Examples/CSharp/IO/WritePNM | Write a PNM (.pnm) file]] || {{VTKDoxygenURL|vtkPNMWriter}} ||
|-
| [[VTK/Examples/CSharp/IO/WriteTIFF | Write a TIFF (.tif) file]] || {{VTKDoxygenURL|vtkTIFFWriter}} ||
|-
| [[VTK/Examples/CSharp/IO/MetaImageWriter | Write a .mha/.mhd + .raw file]] || {{VTKDoxygenURL|vtkMetaImageWriter}} ||
|}

==Geometric Objects==

{{VTKExamplesTable}}
|-
| [[VTK/Examples/CSharp/GeometricObjects/PolygonIntersection| Compute the intersection of a line segment with a polygon]] || {{VTKDoxygenURL|vtkPolygon}} || IntersectWithLine()
|-
| [[VTK/Examples/CSharp/GeometricObjects/GeometricObjectsDemo| A demonstration of all geometric objects that work the same way]] ||  ||
|-
| [[VTK/Examples/CSharp/GeometricObjects/Arrow| Arrow]] || {{VTKDoxygenURL|vtkArrowSource}} ||
|-
| [[VTK/Examples/CSharp/GeometricObjects/Axes| Axes]] || {{VTKDoxygenURL|vtkAxesActor}} ||
|-
| [[VTK/Examples/CSharp/GeometricObjects/ColoredLines  |Colored Lines]] || {{VTKDoxygenURL|vtkCellData}} {{VTKDoxygenURL|vtkLine}} ||
|-
| [[VTK/Examples/CSharp/GeometricObjects/Cone | Cone]] || {{VTKDoxygenURL|vtkConeSource}} ||
|-
| [[VTK/Examples/CSharp/GeometricObjects/Cube | Cube]] || {{VTKDoxygenURL|vtkCubeSource}} ||
|-
| [[VTK/Examples/CSharp/GeometricObjects/Cylinder | Cylinder]] || {{VTKDoxygenURL|vtkCylinderSource}} ||
|-
| [[VTK/Examples/CSharp/GeometricObjects/Disk | Disk]] || {{VTKDoxygenURL|vtkDiskSource}} || A circle with a hole in it.
|-
| [[VTK/Examples/CSharp/GeometricObjects/Frustum | Frustum]] || {{VTKDoxygenURL|vtkFrustumSource}} ||
|-
| [[VTK/Examples/CSharp/GeometricObjects/Line | Line]] || {{VTKDoxygenURL|vtkLineSource}} ||
|-
| [[VTK/Examples/CSharp/GeometricObjects/LongLine | Manually create a polyline]] || {{VTKDoxygenURL|vtkLine}} ||
|-
| [[VTK/Examples/CSharp/GeometricObjects/Hexahedron | Hexahedron]]|| {{VTKDoxygenURL|vtkHexahedron}} ||
|-
| [[VTK/Examples/CSharp/GeometricObjects/OrientedArrow | Oriented Arrow]] || {{VTKDoxygenURL|vtkArrowSource}} ||
|-
| [[VTK/Examples/CSharp/GeometricObjects/Plane | Plane]]|| {{VTKDoxygenURL|vtkPlaneSource}} ||
|-
| [[VTK/Examples/CSharp/GeometricObjects/Planes | Planes]]|| {{VTKDoxygenURL|vtkPlanes}} ||
|-
| [[VTK/Examples/CSharp/GeometricObjects/PlanesIntersection | PlanesIntersection]]|| {{VTKDoxygenURL|vtkPlanesIntersection}} ||
|-
| [[VTK/Examples/CSharp/GeometricObjects/PlatonicSolid | PlatonicSolid]] || {{VTKDoxygenURL|vtkPlatonicSolidSource}} ||
|-
| [[VTK/Examples/CSharp/GeometricObjects/Point | Point]] || {{VTKDoxygenURL|vtkPoints}} ||
|-
| [[VTK/Examples/CSharp/GeometricObjects/Polygon | Polygon]] || {{VTKDoxygenURL|vtkPolygon}} ||
|-
| [[VTK/Examples/CSharp/GeometricObjects/Pyramid | Pyramid]] || {{VTKDoxygenURL|vtkPyramid}} ||
|-
| [[VTK/Examples/CSharp/GeometricObjects/PolyLine | PolyLine]] || {{VTKDoxygenURL|vtkPolyLine}} ||
|-
| [[VTK/Examples/CSharp/GeometricObjects/Quad | Quad]] || {{VTKDoxygenURL|vtkQuad}} ||
|-
| [[VTK/Examples/CSharp/GeometricObjects/RegularPolygonSource | Regular Polygon]] || {{VTKDoxygenURL|vtkRegularPolygonSource}} ||
|-
| [[VTK/Examples/CSharp/GeometricObjects/Sphere | Sphere]] || {{VTKDoxygenURL|vtkSphereSource}} ||
|-
| [[VTK/Examples/CSharp/GeometricObjects/Triangle | Triangle]] || {{VTKDoxygenURL|vtkTriangle}} ||
|-
| [[VTK/Examples/CSharp/GeometricObjects/TriangleStrip|Triangle strip]] || {{VTKDoxygenURL|vtkTriangleStrip}} || 
|-
| [[VTK/Examples/CSharp/GeometricObjects/Tetrahedron | Tetrahedron]] || {{VTKDoxygenURL|vtkTetra}} ||
|-
| [[VTK/Examples/CSharp/GeometricObjects/Vertex | Vertex]] || {{VTKDoxygenURL|vtkVertex}} ||
|}

===Parametric Objects===
These examples demonstrate how to create an display one of the many vtkParametric* objects. All of the classes listed can be used in an identical fashion.

{{VTKExamplesTable}}
|-
| [[VTK/Examples/CSharp/GeometricObjects/ParametricObjects | Create and display a parametric object]] || {{VTKDoxygenURL|vtkParametricBoy}}, {{VTKDoxygenURL|vtkParametricConicSpiral}}, {{VTKDoxygenURL|vtkParametricCrossCap}}, {{VTKDoxygenURL|vtkParametricDini}}, {{VTKDoxygenURL|vtkParametricEllipsoid}}, {{VTKDoxygenURL|vtkParametricEnneper}}, {{VTKDoxygenURL|vtkParametricFigure8Klein}}, {{VTKDoxygenURL|vtkParametricKlein}}, {{VTKDoxygenURL|vtkParametricMobius}}, {{VTKDoxygenURL|vtkParametricRandomHills}}, {{VTKDoxygenURL|vtkParametricRoman}}, {{VTKDoxygenURL|vtkParametricSpline}}, {{VTKDoxygenURL|vtkParametricSuperEllipsoid}}, {{VTKDoxygenURL|vtkParametricSuperToroid}}, {{VTKDoxygenURL|vtkParametricTorus}} ||
|-
| [[VTK/Examples/CSharp/GeometricObjects/ParametricObjectsDemo | Demonstration of all of the vtkParametric* classes]] ||  ||
|}

----

==Implicit Functions and Iso-surfaces==

{{VTKExamplesTable}}
|-
| [[VTK/Examples/CSharp/ImplicitFunctions/IsoContours|Visualize different isocontours using a slider]] || {{VTKDoxygenURL|vtkContourFunction}} ||
|-
| [[VTK/Examples/CSharp/ImplicitFunctions/SampleFunction|Sample and visualize an implicit function]] || {{VTKDoxygenURL|vtkSampleFunction}} ||
|-
| [[VTK/Examples/CSharp/Modelling/ExtractLargestIsosurface|Extract largest isosurface]] || {{VTKDoxygenURL|vtkPolyDataConnectivityFilter}} ||
|-
| [[VTK/Examples/CSharp/VisualizationAlgorithms/BandedPolyDataContourFilter|BandedPolyDataContourFilter]] || {{VTKDoxygenURL|vtkBandedPolyDataContourFilter}} ||
|-
| [[VTK/Examples/CSharp/VisualizationAlgorithms/FilledContours|Create filled contours (vtkClipPolyData)]] || {{VTKDoxygenURL|vtkContourFilter}} ||
|-
| [[VTK/Examples/CSharp/ImplicitFunctions/ImplicitSphere|An implicit representation of a sphere]] || {{VTKDoxygenURL|vtkSphere}} || 
|-
| [[VTK/Examples/CSharp/Modelling/MarchingCubes|Marching cubes]] || {{VTKDoxygenURL|vtkMarchingCubes}} || Create a voxelized sphere
|-
| [[VTK/Examples/CSharp/WishList/Modelling/MarchingSquares|Marching squares]] || {{VTKDoxygenURL|vtkMarchingSquares}} || Create a contour from a structured point set (image)
|}

==Working with 3D Data==
{{VTKExamplesTable}}
|-
| [[VTK/Examples/CSharp/PolyData/CenterOfMass|Compute the center of mass of the points]] || {{VTKDoxygenURL|CenterOfMass}}|| vtkCenterOfMass not implemented yet in ActiViz.NET
|-
| [[VTK/Examples/CSharp/PolyData/BooleanOperationPolyDataFilter|Perform boolean operations on two vtkPolyData objects]] || {{VTKDoxygenURL|BooleanOperationPolyDataFilter}}|| vtkBooleanOperationPolyDataFilter not implemented yet in ActiViz.NET
|-
| [[VTK/Examples/CSharp/PolyData/DistancePolyDataFilter|Compute the distance function from one vtkPolyData to another]] || {{VTKDoxygenURL|DistancePolyDataFilter}}|| vtkDistancePolyDataFilter not implemented yet in ActiViz.NET
|-
| [[VTK/Examples/CSharp/PolyData/ImplicitPolyDataDistance|Compute the distance function in a space around a vtkPolyData]] || {{VTKDoxygenURL|ImplicitPolyDataDistance}}|| vtkImplicitPolyDataDistance not implemented yet in ActiViz.NET
|-
| [[VTK/Examples/CSharp/PolyData/IntersectionPolyDataFilter|Compute the intersection of two vtkPolyData objects]] || {{VTKDoxygenURL|IntersectionPolyDataFilter}}|| vtkIntersectionPolyDataFilter not implemented yet in ActiViz.NET
|-
| [[VTK/Examples/CSharp/PolyData/ShrinkPolyData|Move all items in a PolyData towards their centroid]] || {{VTKDoxygenURL|vtkShrinkPolyData}}||
|-
| [[VTK/Examples/CSharp/PolyData/VectorFieldNonZeroExtraction|Extract non-zero vectors from a vtkImageData]] || {{VTKDoxygenURL|vtkExtractSelectedThresholds}}|| This example shows how to create an imagedata object, associate scalar data with some points and visualize only nonzero scalar values
|-
| [[VTK/Examples/CSharp/PolyData/MultiBlockMergeFilter|Combine MultiBlockDataSets]] || {{VTKDoxygenURL|vtkMultiBlockMergeFilter}}, {{VTKDoxygenURL|vtkMultiBlockDataSet}} || 
|-
| [[VTK/Examples/CSharp/PolyData/IterateOverLines|Iterate through the lines of a PolyData]] || {{VTKDoxygenURL|vtkCellArray}} || 
|-
| [[VTK/Examples/CSharp/PolyData/AlignFrames|Align coordinate frames]] || {{VTKDoxygenURL|vtkLandmarkTransform}} || 
|-
| [[VTK/Examples/CSharp/PolyData/WarpVector|vtkWarpVector]] || {{VTKDoxygenURL|vtkWarpVector}} || 
|-
| [[VTK/Examples/CSharp/IO/FindAllArrayNames|Get the names of all of the data arrays]] || {{VTKDoxygenURL|vtkPolyData}} || 
|-
| [[VTK/Examples/CSharp/PolyData/PolyDataGetPoint|Get point locations/coordinates from a vtkPolyData]] || {{VTKDoxygenURL|vtkPolyData}} || 
|-
| [[VTK/Examples/CSharp/PolyData/NullPoint|NullPoint]] || {{VTKDoxygenURL|vtkPointData}} || Set everything in PointData at a specified index to NULL
|-
| [[VTK/Examples/CSharp/Filtering/ContoursFromPolyData | Create contours from PolyData]] || {{VTKDoxygenURL|vtkCutter}} ||
|-
| [[VTK/Examples/CSharp/Filters/ImplicitBoolean | OperationsOnImplicitFunctions]] || {{VTKDoxygenURL|vtkImplicitBoolean}} || Operations include intersection and union. ||
|}

===Point cloud operations===

{{VTKExamplesTable}}
|}

===Working with Meshes===

{{VTKExamplesTable}}
|-
| [[VTK/Examples/CSharp/Meshes/MatrixMathFilter|Matrix math filter]] || {{VTKDoxygenURL|vtkMatrixMathFilter}} || Compute various quantities on cell and points in a mesh.
|-
| [[VTK/Examples/CSharp/PolyData/WeightedTransformFilter | vtkWeightedTransformFilter ]]  || {{VTKDoxygenURL|vtkWeightedTransformFilter}} ||
|-
| [[VTK/Examples/CSharp/PolyData/GreedyTerrainDecimation | Create a mesh from an ImageData ]]  || {{VTKDoxygenURL|vtkGreedyTerrainDecimation}} ||
|-
| [[VTK/Examples/CSharp/PolyData/vtkPolyDataConnectivityFilter_LargestRegion | Extract the largest connected region in a polydata]]  || {{VTKDoxygenURL|vtkPolyDataConnectivityFilter}} ||
|-
| [[VTK/Examples/CSharp/PolyData/vtkPolyDataConnectivityFilter_SpecifiedRegion | Extract a specific (specified) connected region in a polydata]] || {{VTKDoxygenURL|vtkPolyDataConnectivityFilter}} ||
|-
| [[VTK/Examples/CSharp/PolyData/ColorDisconnectedRegions | Color each disconnected region of a vtkPolyData a different color]] || {{VTKDoxygenURL|vtkPolyDataConnectivityFilter}} ||
|-
| [[VTK/Examples/CSharp/PolyData/Curvatures|Compute Gaussian, Mean, Min, and Max Curvatures]] || {{VTKDoxygenURL|vtkCurvatures}} ||
|-
| [[VTK/Examples/CSharp/PolyData/MeshQuality|Mesh Quality]] || {{VTKDoxygenURL|vtkMeshQuality}} ||
|-
| [[VTK/Examples/CSharp/PolyData/HighlightBadCells|Highlight Bad Cells]] || {{VTKDoxygenURL|vtkMeshQuality}} ||
|-
| [[VTK/Examples/CSharp/PolyData/PolygonalSurfaceContourLineInterpolator|Interactively find the shortest path between two points on a mesh]] || {{VTKDoxygenURL|vtkPolygonalSurfaceContourLineInterpolator}} ||
|-
| [[VTK/Examples/CSharp/PolyData/DijkstraGraphGeodesicPath|Find the shortest path between two points on a mesh]] || {{VTKDoxygenURL|vtkDijkstraGraphGeodesicPath}} ||
|-
| [[VTK/Examples/CSharp/PolyData/SelectPolyData|Select a region of a mesh]] || {{VTKDoxygenURL|vtkSelectPolyData}} ||
|-
| [[VTK/Examples/CSharp/PolyData/SmoothPolyDataFilter|Laplacian smoothing]] || {{VTKDoxygenURL|vtkSmoothPolyDataFilter}} ||
|-
| [[VTK/Examples/CSharp/PolyData/ClosedSurface|Check if a surface is closed]] || {{VTKDoxygenURL|vtkFeatureEdges}} ||
|-
| [[VTK/Examples/CSharp/Meshes/Decimation|Decimation]] || {{VTKDoxygenURL|vtkDecimatePro}} || Reduce the number of triangles in a mesh.
|-
| [[VTK/Examples/CSharp/Meshes/QuadricDecimation|Decimation (quadric decimation)]] || {{VTKDoxygenURL|vtkQuadricDecimation}} || Reduce the number of triangles in a mesh.
|-
| [[VTK/Examples/CSharp/Meshes/QuadricClustering|Decimation (quadric clustering)]] || {{VTKDoxygenURL|vtkQuadricClustering}} || Reduce the number of triangles in a mesh.
|-
| [[VTK/Examples/CSharp/Meshes/Subdivision|Subdivision]] || {{VTKDoxygenURL|vtkButterflySubdivisionFilter}}, {{VTKDoxygenURL|vtkLoopSubdivisionFilter}}, {{VTKDoxygenURL|vtkLinearSubdivisionFilter}} || Increase the number of triangles in a mesh.
|-
| [[VTK/Examples/CSharp/Meshes/BoundaryEdges|Finding Boundary Edges]] || {{VTKDoxygenURL|vtkFeatureEdges}} || Find the edges that are used by only one face.
|-
| [[VTK/Examples/CSharp/Meshes/FillHoles|Fill Holes]] || {{VTKDoxygenURL|vtkFillHolesFilter}} || Close holes in a mesh.
|-
| [[VTK/Examples/CSharp/Meshes/WindowedSincPolyDataFilter|Windowed Sinc PolyData Filter|Smooth a mesh (windowed sinc filter)]] || {{VTKDoxygenURL|vtkWindowedSincPolyDataFilter}} || Smooth a mesh.
|-
| [[VTK/Examples/CSharp/Meshes/Color a mesh by height|Color a mesh by height]]|| {{VTKDoxygenURL|vtkLookupTable}} || Colormap, color map
|-
| [[VTK/Examples/CSharp/Meshes/ElevationFilter|Color a mesh by height]] || {{VTKDoxygenURL|vtkElevationFilter}} ||
|-
| [[VTK/Examples/CSharp/Meshes/SimpleElevationFilter|Color a mesh by dotting a vector from the origin to each point with a specified vector]] || {{VTKDoxygenURL|vtkSimpleElevationFilter}} ||
|-
| [[VTK/Examples/CSharp/Meshes/Triangulate a mesh|Triangulate a mesh]] || {{VTKDoxygenURL|vtkTriangleFilter}} || Convert all polygons in a mesh to triangles.
|-
| [[VTK/Examples/CSharp/Meshes/ExtractEdges|Extract Edges]] || {{VTKDoxygenURL|vtkExtractEdges}} ||
|-
| [[VTK/Examples/CSharp/Meshes/CellEdges|Get edges of cells]] || {{VTKDoxygenURL|vtkCell}} ||
|-
| [[VTK/Examples/CSharp/Meshes/SolidClip|Create a "solid" clip]] || {{VTKDoxygenURL|vtkClipPolyData}} ||
|-
| [[VTK/Examples/CSharp/Meshes/CapClip|Cap a clipped polydata with a polygon]] || {{VTKDoxygenURL|vtkClipPolyData}} ||
|-
| [[VTK/Examples/CSharp/Meshes/OBBDicer|OBBDicer]] || {{VTKDoxygenURL|vtkOBBDicer}} || Breakup a mesh into pieces.
|-
|}

===Working with Structured 3D Data===
This section includes vtkImageData, vtkStructuredGrid, and vtkRectilinearGrid.

"ImageData" is not the traditional "flat, 2D image" you are used to. It is a special VTK data structure in the collection of 3D data structures provided by VTK. Here is an overview of these data structures: [http://vtk.org/Wiki/VTK/Tutorials/3DDataTypes]. Image data can represent at typical 2D image, but also, a 3D volume.

* [[VTK/Examples/CSharp/Visualization/StructuredDataTypes|Demonstration of structured data types]]
* [[VTK/Examples/CSharp/StructuredData/GetLinearPointId|Get the linear point id of a point in a grid]]

====vtkImageData====
{{VTKExamplesTable}}
|}

====vtkStructuredGrid====

{{VTKExamplesTable}}
|}

====vtkStructuredPoints====

{{VTKExamplesTable}}
|}

====vtkRectilinearGrid====

{{VTKExamplesTable}}
|}

===Registration===

{{VTKExamplesTable}}
|}

===Surface reconstruction===

{{VTKExamplesTable}}
|}

==Utilities==
{{VTKExamplesTable}}
|}

==Math Operations==

{{VTKExamplesTable}}
|}

==Graphs==
{{VTKExamplesTable}}
|}

===Graph Conversions===
{{VTKExamplesTable}}
|}

===Graph Conversions That Don't Work===
{{VTKExamplesTable}}
|}

==Data Structures==
{{VTKExamplesTable}}
|}

===Timing Demonstrations===
{{VTKExamplesTable}}
|}

===KD-Tree===

{{VTKExamplesTable}}
|}

===Oriented Bounding Box (OBB) Tree===

{{VTKExamplesTable}}
|}

===Octree===

{{VTKExamplesTable}}
|}

===Modified BSP Tree===

{{VTKExamplesTable}}
|}

==VTK Concepts==

{{VTKExamplesTable}}
|}

==Visualization==
See [[VTK/Tutorials/VTK_Terminology| this tutorial]] for a brief explanation of the VTK terminology of mappers, actors, etc.

{{VTKExamplesTable}}
|}

==Volume Rendering==

{{VTKExamplesTable}}
|}

==User Interaction==
{{VTKExamplesTable}}
|}

==Working with Images==
{{VTKExamplesTable}}
|}

==Image Processing==
{{VTKExamplesTable}}
|}

==Widgets==
{{VTKExamplesTable}}
|}

==Plotting==

{{VTKExamplesTable}}
|}

==Animation==
{{VTKExamplesTable}}
|}

==Geographic Visualization (Geovis)==
{{VTKExamplesTable}}
|}

==Information Visualization (Infovis)==
{{VTKExamplesTable}}
|}

==Qt==
Click [[VTK/Tutorials/QtSetup | here]] for a tutorial on how to setup Qt.

{{VTKExamplesTable}}
|}

==Matlab==
You must turn on VTK_USE_MATLAB_MEX to use these.
{{VTKExamplesTable}}
|}

==Databases==
===SQL===
If you have any trouble or errors with the following examples, please troubleshoot using [[VTK/Tutorials/SQLSetup | these instructions]].

{{VTKExamplesTable}}
|-
|}
