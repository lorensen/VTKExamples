# C++ Examples

These are fully independent, compilable examples. There is significant overlap in the examples, but they are each intended to illustrate a different concept and be fully stand alone compilable.

!!! info
    [This table](/Coverage/CxxVTKClassesUsed.md) shows the VTK classes covered by the examples.

!!! info
    [This table](/Coverage/CxxVTKClassesNotUsed.md) shows VTK classes that do not have an example. Please add examples in your area of expertise!

## Hello World

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[A hello world example](/Cxx/Rendering/CylinderRenderingProperties)  | vtkPolyDataMapper vtkActor vtkRenderer vtkRenderWindow vtkRenderWindowInteractor| Cylinder example from the VTK Textbook and source code.

## Simple Operations

| Example Name | Classes Demonstrated | Description |  Image |
|--------------|----------------------|-------------|--------|
[DistanceBetweenPoints](/Cxx/SimpleOperations/DistanceBetweenPoints)   | vtkMath| Distance between two points.
[DistancePointToLine](/Cxx/SimpleOperations/DistancePointToLine)   | vtkLine |Distance between a point and a line.
[FloatingPointExceptions](/Cxx/SimpleOperations/FloatingPointExceptions) | vtkFloatingPointExceptions | Floating Point Exceptions
[GaussianRandomNumber](/Cxx/SimpleOperations/GaussianRandomNumber)  | vtkMath | Generates Gaussian random numbers.
[UniformRandomNumber](/Cxx/SimpleOperations/UniformRandomNumber)   | vtkMath | Generates uniform random numbers.
[RandomSequence](/Cxx/SimpleOperations/RandomSequence) | vtkMinimalStandardRandomSequence | This is the preferred way to generate random numbers.
[ProjectPointPlane](/Cxx/SimpleOperations/ProjectPointPlane) | vtkPlane | Project a point onto a plane.
[PerspectiveTransform](/Cxx/SimpleOperations/PerspectiveTransform) | vtkPerspectiveTransform |Apply a perspective transformation to a point.


## Input and Output
### Graph Formats

### 3D File Formats

| Example Name | Classes Demonstrated | Description |  Image |
|--------------|----------------------|-------------|--------|
[ConvertFile](/Cxx/IO/ConvertFile)   |  |Convert a file from one type to another
[XGMLReader](/Cxx/InfoVis/XGMLReader)   | vtkXGMLReader |Read a .gml file


#### Standard Formats
##### Input

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[DelimitedTextReader](/Cxx/InfoVis/DelimitedTextReader)   | vtkDelimitedTextReader |Read a delimited file into a polydata.
[DEMReader](/Cxx/IO/DEMReader)   | vtkDEMReader | Read DEM (elevation map) files
[DumpXMLFile](/Cxx/IO/DumpXMLFile) | vtkDataSetReader |Report the contents of a VTK XML or legacy file
[IndividualVRML](/Cxx/IO/IndividualVRML) | vtkVRMLImporter | This example is used to get each actor and object from a scene and verify axes correspondence 
[ParticleReader](/Cxx/IO/ParticleReader) | vtkParticleReader | This example reads ASCII files where each line consists of points with its position (x,y,z) and (optionally) one scalar or binary files in RAW 3d file format.
[ReadAllPolyDataTypes](/Cxx/IO/ReadAllPolyDataTypes) | vtkBYUReader vtkOBJReader vtkPLYReader vtkPolyDataReader vtkSTLReader vtkXMLPolyDataReader | Read any VTK polydata file.
[ReadAllPolyDataTypesDemo](/Cxx/IO/ReadAllPolyDataTypesDemo) | vtkBYUReader vtkOBJReader vtkPLYReader vtkPolyDataReader vtkSTLReader vtkXMLPolyDataReader | Read all VTK polydata file types.
[ReadOBJ](/Cxx/IO/ReadOBJ)   | vtkOBJReader |Read an OBJ (.obj) file.
[ReadPDB](/Cxx/IO/ReadPDB)   | vtkPDBReader | Read Protein Data Bank Files.
[ReadPLOT3D](/Cxx/IO/ReadPLOT3D)   | vtkPLOT3DReader | Read CFD (computational fluid dynamics) data produced by PLOT3D.
[ReadPLY](/Cxx/IO/ReadPLY)   | vtkPLYReader |Read PLY (.ply) files
[ReadPlainTextTriangles](/Cxx/IO/ReadPlainTextTriangles)   | vtkPolyData vtkSmartPointer vtkPoints vtkCellArray vtkXMLPolyDataWriter | Read a plain text file into a polydata.
[ReadTextFile](/Cxx/IO/ReadTextFile)   | vtkPolyData | Read a plain text file into a polydata.
[ReadSTL](/Cxx/IO/ReadSTL)   | vtkSTLReader |Read stereo lithography STL (.stl) files
[SimplePointsReader](/Cxx/IO/SimplePointsReader)  | vtkSimplePointsReader |Read a simple "xyz" file of points.


###### Importers

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[3DSImporter](/Cxx/IO/3DSImporter) | vtk3DSImporter | Import a 3D Studio scene that includes multiple actors.
[OBJImporter](/Cxx/IO/OBJImporter) | vtkOBJImporter | Import an OBJ scene that includes actors, materials and textures.
[VRMLImporter](/Cxx/IO/VRMLImporter) | vtkVRMLImporter | Import a VRML 2.0 (WRL) file.
[VRMLImporterDemo](/Cxx/IO/VRMLImporterDemo) | vtkVRMLImporter | Import a VRML 2.0 (WRL) file and add normals if necessary.

##### Output

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[DelimitedTextWriter](/Cxx/InfoVis/DelimitedTextWriter)   | vtkDelimitedTextWriter |Write data to a delimited file
[SimplePointsWriter](/Cxx/IO/SimplePointsWriter)   | vtkSimplePointsWriter |Write a simple ".xyz" file
[WritePLY](/Cxx/IO/WritePLY)   | vtkPLYWriter | Write PLY (.ply) files
[WriteSTL](/Cxx/IO/WriteSTL)   | vtkSTLWriter |Write stereo lithography STL (.stl) files


#### VTK Formats
##### Input


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ReadImageData](/Cxx/IO/ReadImageData) | vtkXMLImageDataReader |Read a image data (.vti) file
[ReadPolyData](/Cxx/IO/ReadPolyData) | vtkXMLPolyDataReader |Read a polygonal data (.vtp) file
[ReadRectilinearGrid](/Cxx/IO/ReadRectilinearGrid) | vtkXMLRectilinearGridReader |Read a rectilinear grid (.vtr) file
[ReadStructuredGrid](/Cxx/IO/ReadStructuredGrid) | vtkXMLStructuredGridReader |Read a structured grid (.vts) file
[ReadUnknownTypeXMLFile](/Cxx/IO/ReadUnknownTypeXMLFile) | vtkXMLGenericDataObjectReader |Read an XML file and later decide what kind it is
[ReadUnstructuredGrid](/Cxx/IO/ReadUnstructuredGrid) | vtkXMLUnstructuredGridReader |Read an unstructured grid (.vtu) file


##### Output

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ExodusIIWriter](/Cxx/Parallel/ExodusIIWriter)   | vtkExodusIIWriter | Write a time varying ExodusII file.
[XMLPImageDataWriter](/Cxx/IO/XMLPImageDataWriter) | vtkXMLPImageDataWriter | Write a .pvti file with 4 .vti pieces.
[XMLPUnstructuredGridWriter](/Cxx/IO/XMLPUnstructuredGridWriter) | vtkXMLPUnstructuredGridWriter | Write a .pvtu with 4 .vtu pieces.
[WriteVTI](/Cxx/IO/WriteVTI) | vtkXMLImageDataWriter | Write a .vti file. VTI is an "ImageData".
[WriteVTP](/Cxx/IO/WriteVTP) | vtkXMLPolyDataWriter | Write a .vtp file. VTP is a "PolyData". This format allows for the most complex geometric objects to be stored.
[WriteVTU](/Cxx/IO/WriteVTU) | vtkXMLUnstructuredGridWriter | Write a .vtu file. VTU is an "Unstructured Grid". This format allows for 3D data to be stored.
[XMLStructuredGridWriter](/Cxx/IO/XMLStructuredGridWriter) | vtkXMLStructuredGridWriter | Write a .vts file from a vtkStructuredGrid.

#### Legacy VTK Formats

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[GenericDataObjectReader](/Cxx/IO/GenericDataObjectReader) | vtkGenericDataObjectReader |Read any type of legacy .vtk file.
[StructuredGridReader](/Cxx/IO/StructuredGridReader) | vtkStructuredGridReader |Read a structured grid (.vtk) file.
[StructuredPointsReader](/Cxx/IO/StructuredPointsReader)   | vtkStructuredPointsReader |Read a structured points (.vtk) file.


### Image Format

#### Input

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ImageReader2Factory](/Cxx/IO/ImageReader2Factory) | vtkImageReader2Factory | This class tries to find an appropriate reader. It is very convenient to use this when you don't know what kind of file to expect.
[JPEGReader](/Cxx/IO/JPEGReader) | vtkJPEGReader|Read a JPEG image.
[MetaImageReader](/Cxx/IO/MetaImageReader) | vtkMetaImageReader |Read .mha files.
[PNGReader](/Cxx/IO/PNGReader) | vtkPNGReader|Read a PNG image.
[ReadBMP](/Cxx/IO/ReadBMP) | vtkBMPReader | Read BMP (.bmp) files.
[ReadDICOMSeries](/Cxx/IO/ReadDICOMSeries)   | vtkDICOMImageReader | This example demonstrates how to read a series of DICOM images and scroll through slices
[ReadDICOM](/Cxx/IO/ReadDICOM)   | vtkDICOMImageReader |Read DICOM file
[ReadPNM](/Cxx/IO/ReadPNM) | vtkPNMReader |Read PNM (.pnm) files.
[ReadTIFF](/Cxx/IO/ReadTIFF) | vtkTIFFReader |Read TIFF (.tif) files.

#### Output

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[JPEGWriter](/Cxx/IO/JPEGWriter)   | vtkJPEGWriter |Write a JPEG (.jpg) file.
[MetaImageWriter](/Cxx/IO/MetaImageWriter)   | vtkMetaImageWriter |Write a .mha/.mhd + .raw file.
[PNGWriter](/Cxx/IO/PNGWriter)   | vtkPNGWriter |Write a PNG (.png) file.
[WriteBMP](/Cxx/IO/WriteBMP)   | vtkBMPWriter |Write a BMP (.bmp) file.
[WritePNM](/Cxx/IO/WritePNM)   | vtkPNMWriter |Write a PNM (.pnm) file.
[WriteTIFF](/Cxx/IO/WriteTIFF)   | vtkTIFFWriter |Write a TIFF (.tif) file.


## Geometric Objects

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Axes](/Cxx/GeometricObjects/Axes)  | vtkAxesActor |
[ColoredLines](/Cxx/GeometricObjects/ColoredLines)   | vtkCellData vtkLine |
[Dodecahedron](/Cxx/GeometricObjects/Dodecahedron)   | vtkPolyhedron | Create a dodecahedron using vtkPolyhedron
[EllipticalCylinder](/Cxx/GeometricObjects/EllipticalCylinder)   | vtkLinearExtrusionFilter | Create an elliptical cylinder using extrusion.
[EllipticalCylinderDemo](/Cxx/GeometricObjects/EllipticalCylinderDemo)   | vtkLinearExtrusionFilter | Show the base and extrusion vector.
[GeometricObjectsDemo](/Cxx/GeometricObjects/GeometricObjectsDemo) |  | A demonstration of all geometric objects that work the same way.
[PlanesIntersection](/Cxx/GeometricObjects/PlanesIntersection)  | vtkPlanesIntersection |
[Planes](/Cxx/GeometricObjects/Planes)  | vtkPlanes |
[PolygonIntersection](/Cxx/GeometricObjects/PolygonIntersection) | vtkPolygon |  Compute the intersection of a line segment with a polygon.

### Cells

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Cell3DDemonstration](/Cxx/GeometricObjects/Cell3DDemonstration) | vtkHexagonalPrism vtkHexahedron vtkPentagonalPrism  vtkPolyhedron vtkPyramid vtkTetra vtkVoxel vtkWedge vtkUnstructuredGrid |  Demonstrate the use of vtkCell3D to construct geometric objects. Sample objects are generated from the classes derived from vtkCell3D and displayed.
[CellTypeSource](/Cxx/GeometricObjects/CellTypeSource)  | vtkCellTypeSource vtkTessellatorFilter| Generate tessellated cells.
[ConvexPointSet](/Cxx/GeometricObjects/ConvexPointSet)  | vtkConvexPointSet| Generate a ConvexPointSetCell.
[Hexahedron](/Cxx/GeometricObjects/Hexahedron)  | vtkHexahedron |
[LongLine](/Cxx/GeometricObjects/LongLine) | vtkLine | Manually create a polyline
[Point](/Cxx/GeometricObjects/Point)   | vtkPoints |
[PolyLine](/Cxx/GeometricObjects/PolyLine)   | vtkPolyLine |
[Polygon](/Cxx/GeometricObjects/Polygon)   | vtkPolygon |
[Polyhedron](/Cxx/GeometricObjects/Polyhedron)   | vtkPolyhedron |
[Pyramid](/Cxx/GeometricObjects/Pyramid)   | vtkPyramid |
[Quad](/Cxx/GeometricObjects/Quad)   | vtkQuad |
[Tetrahedron](/Cxx/GeometricObjects/Tetrahedron)   | vtkTetra |
[Triangle strip](/Cxx/GeometricObjects/TriangleStrip) | vtkTriangleStrip | 
[Triangle](/Cxx/GeometricObjects/Triangle)   | vtkTriangle |
[Vertex](/Cxx/GeometricObjects/Vertex)   | vtkVertex |

### Sources

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Arrow](/Cxx/GeometricObjects/Arrow) | vtkArrowSource |
[Cone](/Cxx/GeometricObjects/Cone)   | vtkConeSource |
[Cube](/Cxx/GeometricObjects/Cube)   | vtkCubeSource |
[Cylinder](/Cxx/GeometricObjects/Cylinder)   | vtkCylinderSource |
[Disk](/Cxx/GeometricObjects/Disk)   | vtkDiskSource | A circle with a hole in it.
[Frustum](/Cxx/GeometricObjects/Frustum)   | vtkFrustumSource |
[Line](/Cxx/GeometricObjects/Line)   | vtkLineSource |
[OrientedArrow](/Cxx/GeometricObjects/OrientedArrow)   | vtkArrowSource | Orient an arrow along an arbitrary vector
[OrientedCylinder](/Cxx/GeometricObjects/OrientedCylinder)   | vtkCylinderSource | Orient a cylinder along an arbitrary vector
[Plane](/Cxx/GeometricObjects/Plane)  | vtkPlaneSource |
[PlatonicSolid](/Cxx/GeometricObjects/PlatonicSolid)   | vtkPlatonicSolidSource |
[RegularPolygon](/Cxx/GeometricObjects/RegularPolygonSource)   | vtkRegularPolygonSource |
[Sphere](/Cxx/GeometricObjects/Sphere)   | vtkSphereSource |
[TessellatedBoxSource](/Cxx/GeometricObjects/TessellatedBoxSource)   | vtkTessellatedBoxSource | Generated a box with tessellated sides.

### Non Linear

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[QuadraticHexahedron](/Cxx/GeometricObjects/QuadraticHexahedron) | vtkQuadraticHexahedron vtkTessellatorFilter | Create and tessellate a nonlinear cell.
[QuadraticHexahedronDemo](/Cxx/GeometricObjects/QuadraticHexahedronDemo) | vtkQuadraticHexahedron vtkTessellatorFilter | Interactively adjust chord error.
[QuadraticTetra](/Cxx/GeometricObjects/QuadraticTetra) | vtkTetra vtkTessellatorFilter | Create and tessellate a nonlinear cell.
[QuadraticTetraDemo](/Cxx/GeometricObjects/QuadraticTetraDemo) | vtkTetra vtkTessellatorFilter | Interactively adjust chord error.

### Parametric Objects

These examples demonstrate how to create an display one of the many vtkParametric objects. All of the classes listed can be used in an identical fashion.


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ParametricObjects](/Cxx/GeometricObjects/ParametricObjects)   |  | Create and display a parametric object. Uncomment the object that you wish to be displayed.
[ParametricObjectsDemo](/Cxx/GeometricObjects/ParametricObjectsDemo)   | vtkParametricBoy vtkParametricConicSpiral vtkParametricCrossCap vtkParametricDini vtkParametricEllipsoid vtkParametricEnneper vtkParametricFigure8Klein vtkParametricKlein vtkParametricMobius vtkParametricRandomHills vtkParametricRoman vtkParametricSpline vtkParametricSuperEllipsoid vtkParametricSuperToroid vtkParametricTorus | Demonstration of of the vtkParametric* classes added by Andrew Maclean. All the objects are displayed in a 4X4 array.
[ParametricObjectsDemo2](/Cxx/GeometricObjects/ParametricObjectsDemo2)   | vtkParametricBohemianDome vtkParametricBour vtkParametricCatalanMinimal vtkParametricHenneberg vtkParametricKuen vtkParametricPluckerConoid vtkParametricPseudosphere | Demonstration of additional vtkParametric* classes added by  Tim Meehan. All the objects are displayed in a 4X2 array.
[ParametricKuenDemo](/Cxx/GeometricObjects/ParametricKuenDemo) | vtkParametricKuen|Interactively change the parameters for a Kuen Surface.
[ParametricSuperEllipsoidDemo](/Cxx/GeometricObjects/ParametricSuperEllipsoidDemo) | vtkParametricSuperEllipsoid | Interactively change the parameters for a SuperEllipsoid Surface.
[ParametricSuperToroidDemo](/Cxx/GeometricObjects/ParametricSuperToroidDemo)   | vtkParametricSuperToroid| Interactively change the parameters for a SuperToroid Surface.

## Implicit Functions and Iso-surfaces


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[BandedPolyDataContourFilter](/Cxx/VisualizationAlgorithms/BandedPolyDataContourFilter) | vtkBandedPolyDataContourFilter | Create filled contours.
[ContourTriangulator](/Cxx/Modelling/ContourTriangulator) | vtkMarchingSquares vtkContourTriangulator | Create a contour from a structured point set (image) and triangulate it.
[CutWithCutFunction](/Cxx/VisualizationAlgorithms/CutWithCutFunction) | vtkCutter | Cut a surface with an implicit plane using vtkCutter.
[CutWithScalars](/Cxx/VisualizationAlgorithms/CutWithScalars) | vtkContourFilter | Cut a surface with scalars.
[DiscreteMarchingCubes](/Cxx/Modelling/DiscreteMarchingCubes) | vtkDiscreteMarchingCubes | Generate surfaces from labeled data.
[ExtractLargestIsosurface](/Cxx/Modelling/ExtractLargestIsosurface) | vtkPolyDataConnectivityFilter | Extract largest isosurface.
[FilledContours](/Cxx/VisualizationAlgorithms/FilledContours) | vtkContourFilter |Create filled contours (using vtkClipPolyData).
[ImplicitDataSet](/Cxx/ImplicitFunctions/ImplicitDataSet) | vtkImplicitDataSet | Convert an imagedata to an implicit function.
[ImplicitSphere](/Cxx/ImplicitFunctions/ImplicitSphere) | vtkSphere | An implicit representation of a sphere.
[IsoContours](/Cxx/ImplicitFunctions/IsoContours) | vtkContourFunction | Visualize different isocontours using a slider.
[MarchingCubes](/Cxx/Modelling/MarchingCubes) | vtkMarchingCubes | Create a voxelized sphere.
[MarchingCases](/Cxx/VisualizationAlgorithms/MarchingCases) | vtkMarchingCubes | Explore the Marching Cubes cases.
[MarchingSquares](/Cxx/Modelling/MarchingSquares) | vtkMarchingSquares | Create a contour from a structured point set (image).
[SampleFunction](/Cxx/ImplicitFunctions/SampleFunction) | vtkSampleFunction |Sample and visualize an implicit function.
[SmoothDiscreteMarchingCubes](/Cxx/Modelling/SmoothDiscreteMarchingCubes) | vtkDiscreteMarchingCubes vtkWindowedSincPolyDataFilter | Generate smooth surfaces from labeled data.


## Working with 3D Data

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[AlignFrames](/Cxx/PolyData/AlignFrames) | vtkLandmarkTransform | Align coordinate frames.
[AppendFilter](/Cxx/Filtering/AppendFilter) | vtkAppendFilter | Append different types of data,
[BooleanOperationPolyDataFilter](/Cxx/PolyData/BooleanOperationPolyDataFilter) | vtkBoleanOperationPolyDataFilter|Perform boolean operations on two vtkPolyData objects.
[Bottle](/Cxx/Modelling/Bottle) | vtkRotationalExtrusionFilter | Rotationally symmetric objects.
[LoopBooleanPolyDataFilter](/Cxx/PolyData/LoopBooleanPolyDataFilter) | vtkLoopBooleanOpPolyDataFilter|Perform boolean operations on two vtkPolyData objects.
[CellCenters](/Cxx/PolyData/CellCenters) | vtkCellCenters |Compute points at the center of every cell.
[CellEdgeNeighbors](/Cxx/PolyData/CellEdgeNeighbors) | vtkPolyData::GetCellNeighbors |Determine which cells share an edge with a specific cell.
[CellPointNeighbors](/Cxx/PolyData/CellPointNeighbors) | vtkPolyData::GetCellNeighbors | Determine which cells share a single point with a specific cell.
[CenterOfMass](/Cxx/PolyData/CenterOfMass) | vtkCenterOfMass|Compute the center of mass of the points.
[Circle](/Cxx/GeometricObjects/Circle) | vtkCutter | Create a circle by cutting through a sphere.
[CleanPolyData](/Cxx/PolyData/CleanPolyData) | vtkCleanPolyData |Remove coincident points.
[ColorCellsWithRGB](/Cxx/PolyData/ColorCellsWithRGB) | vtkCellData | Color individual cells of a polydata with rgb colors.
[ColorCells](/Cxx/PolyData/ColorCells) | vtkLookupTable | Color individual cells of a polydata with scalar index.
[ColoredPoints](/Cxx/PolyData/ColoredPoints) | vtkUnsignedCharArray | Add three points to a polydata and associate a color with each of them.
[CombinePolyData](/Cxx/Filtering/CombinePolyData) | vtkAppendPolyData | Combine/Append PolyData.
[ConnectivityFilter](/Cxx/Filtering/ConnectivityFilter) | vtkConnectivityFilter | Color any dataset type based on connectivity.
[ContoursFromPolyData](/Cxx/Filtering/ContoursFromPolyData) | vtkCutter | Create contours from PolyData.
[ContoursToSurface](/Cxx/PolyData/ContoursToSurface) | vtkVoxelContoursToSurfaceFilter | Convert contours to a surface.
[ConvexHull](/Cxx/PolyData/ConvexHull) | vtkHull |Convex hull using vtkHull.
[ConvexHullShrinkWrap](/Cxx/PolyData/ConvexHullShrinkWrap) | vtkSmoothPolyDataFilter | Convex hull using shrink wrapping.
[CopyAllArrays](/Cxx/PolyData/CopyAllArrays)| vtkPolyData |Copy all arrays from one vtkPolyData to another.
[DataBounds](/Cxx/PolyData/DataBounds) | vtkPolyData::GetBounds | Get the minimum and maximum value in each dimension. (Axis aligned bounding box)
[DataSetSurfaceFilter](/Cxx/PolyData/DataSetSurfaceFilter) | vtkDataSetSurfaceFilter |Convert vtkUnstructuredGrid to vtkPolyData.
[DecimatePolyline](/Cxx/PolyData/DecimatePolyline) | vtkDecimatePolylineFilter |Decimate polyline.
[DeleteCells](/Cxx/PolyData/DeleteCells) | vtkPolyData | Delete a cell from a vtkPolyData
[DeletePoint](/Cxx/PolyData/DeletePoint) | vtkPoints vtkPolyData |
[DetermineArrayDataTypes](/Cxx/PolyData/DetermineArrayDataTypes)| vtkPolyData |Determine data types of arrays.
[DistancePolyDataFilter](/Cxx/PolyData/DistancePolyDataFilter) | vtkDistancePolyDataFilter|Compute the distance function from one vtkPolyData to another.
[EmbedPointsIntoVolume](/Cxx/PolyData/EmbedPointsIntoVolume)| vtkGaussianSplatter |Embed points into a volume.
[ExternalContour](/Cxx/PolyData/ExternalContour) | vtkWindowToImageFilter vtkContourFilter |Get the External Contour from Polydata.
[ExtractCellsUsingPoints](/Cxx/PolyData/ExtractCellsUsingPoints) | vtkExtractSelection vtkSelection vtkSelectionNode |Extract points but bring cells that are still complete with them.
[ExtractOutsideSurface](/Cxx/PolyData/ExtractOutsideSurface) | vtkPolyDataConnectivityFilter | Extract the outer surface of a multiple surface polydata.
[ExtractPolyLinesFromPolyData](/Cxx/PolyData/ExtractPolyLinesFromPolyData) | vtkPolyData |Extract polylines from polydata.
[ExtractSelectedIds](/Cxx/PolyData/ExtractSelectedIds) | vtkExtractSelectedIds | Extract selected points.
[ExtractSelectionCells](/Cxx/PolyData/ExtractSelectionCells) | vtkExtractSelection | Extract selection cells.
[ExtractSelectionOriginalId](/Cxx/PolyData/ExtractSelectionOriginalId) | vtkExtractSelection |Extract selection and find correspondence between new and original Id.
[ExtractSelection](/Cxx/PolyData/ExtractSelection) | vtkExtractSelection |Extract selection points.
[ExtractVisibleCells](/Cxx/Filtering/ExtractVisibleCells) | vtkHardwareSelector |Extract and highlight visible cells.
[FieldData](/Cxx/PolyData/FieldData) | vtkFieldData | Add Global Miscellaneous Data (FieldData) to a Polydata.
[FindAllArrayNames](/Cxx/IO/FindAllArrayNames) | vtkPolyData | Get the names of all of the data arrays.
[FitSplineToCutterOutput](/Cxx/PolyData/FitSplineToCutterOutput) | vtkKochanekSpline vtkSplineFilter vtkSpline |Fit a spline to cutter output.
[GeometryFilter](/Cxx/PolyData/GeometryFilter) | vtkGeometryFilter |Convert vtkUnstructuredGrid to vtkPolyData (another way).
[GetMiscCellData](/Cxx/PolyData/GetMiscCellData) | vtkCellData |Get Miscellaneous Data from Cells in a Polydata.
[GetMiscPointData](/Cxx/PolyData/GetMiscPointData) | vtkDoubleArray |Get Miscellaneous Data from Points in a Polydata.
[GradientFilter](/Cxx/PolyData/GradientFilter) | vtkGradientFilter |Compute the gradient of a scalar field on a data set.
[ImplicitBoolean](/Cxx/Filtering/ImplicitBoolean) | vtkImplicitBoolean | Operations include intersection and union.
[ImplicitBooleanDemo](/Cxx/Filtering/ImplicitBooleanDemo) | vtkImplicitBoolean | Demo Union, Difference and Intersection.
[ImplicitModeller](/Cxx/PolyData/ImplicitModeller) | vtkImplicitModeller |Compute the distance from an object to every point on a uniform grid.
[ImplicitPolyDataDistance](/Cxx/PolyData/ImplicitPolyDataDistance) | vtkImplicitPolyDataDistance|Compute the distance function in a space around a vtkPolyData.
[InterpolateMeshOnGrid](/Cxx/PolyData/InterpolateMeshOnGrid) | vtkProbeFilter | Interpolate a mesh over a grid.
[InterpolateTerrain](/Cxx/PolyData/InterpolateTerrain) | vtkProbeFilter | vtkProbeFilter Interpolate terrain.
[IntersectionPolyDataFilter](/Cxx/PolyData/IntersectionPolyDataFilter) | vtkIntersectionPolyDataFilter|Compute the intersection of two vtkPolyData objects.
[IterateOverLines](/Cxx/PolyData/IterateOverLines) | vtkCellArray | Iterate through the lines of a PolyData.
[KMeansClustering](/Cxx/InfoVis/KMeansClustering) | vtkKMeansStatistics |KMeans Clustering
[KochanekSpline](/Cxx/PolyData/KochanekSpline) | vtkKochanekSpline |Create an Kochanek spline on a set of points.
[KochanekSplineDemo](/Cxx/PolyData/KochanekSplineDemo) | vtkKochanekSpline | Interactively change the parameters of the Kochanek spline.
[LinearExtrusion](/Cxx/PolyData/LinearExtrusion) | vtkLinearExtrusionFilter | Extrude a shape.
[MaskPoints](/Cxx/PolyData/MaskPoints) | vtkMaskPoints |Select a subset (mask) of a point set.
[MergePoints](/Cxx/PolyData/MergePoints) | vtkMergePoints | Remove duplicate (merge) points.
[MiscCellData](/Cxx/PolyData/MiscCellData) | vtkCellData |Add Miscellaneous Data to Cells in a Polydata.
[MiscPointData](/Cxx/PolyData/MiscPointData) | vtkPointData vtkFloatArray |Add Miscellaneous Data to Points in a Polydata.
[MultiBlockMergeFilter](/Cxx/PolyData/MultiBlockMergeFilter) | vtkMultiBlockMergeFilter vtkMultiBlockDataSet | Combine MultiBlockDataSets.
[NullPoint](/Cxx/PolyData/NullPoint) | vtkPointData | Set everything in PointData at a specified index to NULL
[Outline](/Cxx/PolyData/Outline) | vtkOutlineFilter | Draw the bounding box of the data
[PKMeansClustering](/Cxx/InfoVis/PKMeansClustering) | vtkPKMeansStatistics |Parallel KMeans Clustering.
[ParametricSpline](/Cxx/PolyData/ParametricSpline) | vtkCardinalSpline vtkParametricSpline vtkParametricFunctionSource |Create a Cardinal spline on a set of points.
[Perlin Noise](/Cxx/Filtering/PerlinNoise) | vtkPerlinNoise |
[PointCellIds](/Cxx/PolyData/PointCellIds) | vtkIdFilter |Generate point and cell id arrays.
[PointInsideObject2](/Cxx/PolyData/PointInsideObject2) | vtkDelaunay3D vtkPolyData::FindCell | This uses a Delaunay triangulation to compute a volume. This gives more of an "is inside convex hull" effect than an "is inside object".
[PointInsideObject](/Cxx/PolyData/PointInsideObject) | vtkSelectEnclosedPoints | Check if a point is inside an object.
[PointsProjectedHull](/Cxx/PolyData/PointsProjectedHull) | vtkPointsProjectedHull |Convex hull of points projected onto the coordinate planes.
[PolyDataCellNormals](/Cxx/PolyData/PolyDataCellNormals) | vtkCellData |Add/Get Normals to/from cells in a Polydata.
[PolyDataContourToImageData](/Cxx/PolyData/PolyDataContourToImageData) | vtkLinearExtrusionFilter vtkPolyDataToImageStencil |Generate a binarized image from a closed contour.
[PolyDataExtractNormals](/Cxx/PolyData/PolyDataExtractNormals) | vtkPolyDataNormals |Extract Normals from a Polydata.
[PolyDataGetPoint](/Cxx/PolyData/PolyDataGetPoint) | vtkPolyData | Get point locations/coordinates from a vtkPolyData.
[PolyDataIsoLines](/Cxx/PolyData/PolyDataIsoLines) | vtkBandedPolyDataContourFilter |Iso lines on the surface of a polydata
[PolyDataPointNormals](/Cxx/PolyData/PolyDataPointNormals) | vtkPointData |Add/Get Normals to/from points in a Polydata.
[PolyDataPointSampler](/Cxx/PolyData/PolyDataPointSampler) | vtkPolyDataPointSampler | Sample the edges or surfaces of a polydata.
[PolyDataToImageData](/Cxx/PolyData/PolyDataToImageData) | vtkPolyDataToImageStencil |Generate a binarized volume from a closed surface.
[ProcrustesAlignmentFilter](/Cxx/PolyData/ProcrustesAlignmentFilter) | vtkProcrustesAlignmentFilter |Align point sets.
[ProgrammableFilter](/Cxx/Filtering/ProgrammableFilter) | vtkProgrammableFilter | Create a custom filter without subclassing.
[ProgrammableSource](/Cxx/Filtering/ProgrammableSource) | vtkProgrammableSource |Create points using a programmable source. Generates points for a strange attractor.
[ProjectSphere](/Cxx/Visualization/ProjectSphere) | vtkProjectSphereFilter |Unroll a sphere or spherical-like model.
[QuantizePolyDataPoints](/Cxx/PolyData/QuantizePolyDataPoints) | vtkQuantizePolyDataPoints |Snap (quantize) points to a grid.
[Reflection](/Cxx/PolyData/Reflection) | vtkReflectionFilter |Mirror a DataSet.
[RemoveOutsideSurface](/Cxx/PolyData/RemoveOutsideSurface) | vtkConnectivityFilter | Remove the outer surface of a multiple surface polydata.
[ReverseSense](/Cxx/PolyData/ReverseSense) | vtkReverseSense |Flip normals.
[RibbonFilter](/Cxx/PolyData/RibbonFilter) | vtkRibbonFilter |
[RotationAroundLine](/Cxx/PolyData/RotationAroundLine) | vtkTransform vtkTransformPolyDataFilter |Rotation around a line.
[RuledSurfaceFilter](/Cxx/PolyData/RuledSurfaceFilter) | vtkRuledSurfaceFilter |Create a surface between lines.
[SCurveSpline](/Cxx/InfoVis/SCurveSpline) | vtkSCurveSpline |Create an SCurve spline on a set of points.
[SelectVisiblePoints](/Cxx/PolyData/SelectVisiblePoints) | vtkSelectVisiblePoints |Select visible points.
[SelectionSource](/Cxx/Filtering/SelectionSource) | vtkSelectionSource vtkExtractSelection | Specify a selection.
[ShrinkPolyData](/Cxx/PolyData/ShrinkPolyData) | vtkShrinkPolyData|Move all items in a PolyData towards their centroid.
[Silhouette](/Cxx/PolyData/Silhouette) | vtkPolyDataSilhouette |
[Stripper](/Cxx/PolyData/Stripper) | vtkStripper |Convert triangles to triangle strips.
[ThinPlateSplineTransform](/Cxx/PolyData/ThinPlateSplineTransform) | vtkThinPlateSplineTransform |
[ThresholdCells](/Cxx/PolyData/ThresholdCells) | vtkThreshold |Thresholding Cells.
[ThresholdPoints](/Cxx/PolyData/ThresholdPoints) | vtkThresholdPoints |Thresholding Points.
[TransformFilter](/Cxx/PolyData/TransformFilter) | vtkTransformFilter |Transform a data set.
[TransformOrderDemo](/Cxx/PolyData/TransformOrderDemo) | vtkTransformPolyDataFilter |Demonstrate how the order of applying transforms affects the result.
[TransformPipeline](/Cxx/PolyData/TransformPipeline) | vtkTransform |Combining the transformation, in order to manipulate a group of vtkActor. Shown in the example robot arm motion.
[TransformPolyData](/Cxx/Filtering/TransformPolyData) | vtkTransformPolyDataFilter | Apply a Transformation to a PolyData.
[TriangleArea](/Cxx/PolyData/TriangleArea) | vtkTriangle::TriangleArea | Compute the area of all triangles in a polydata.
[TriangleColoredPoints](/Cxx/PolyData/TriangleColoredPoints) | vtkUnsignedCharArray | Set the color of each point of a triangle. You will be able to interpolate the colors across the triangle.
[TriangleSolidColor](/Cxx/PolyData/TriangleSolidColor) | vtkUnsignedCharArray | Create a solid colored triangle.
[TubeFilter](/Cxx/PolyData/TubeFilter) | vtkTubeFilter | Give lines a thickness (produce a cylinder around lines.
[VectorFieldNonZeroExtraction](/Cxx/Filtering/VectorFieldNonZeroExtraction) | vtkExtractSelectedThresholds| Extract non-zero vectors from a vtkImageData.
[VertexConnectivity](/Cxx/PolyData/VertexConnectivity) | vtkPolyData::GetCellPoints |Get a list of vertices attached (through an edge) to a vertex.
[WarpScalar](/Cxx/PolyData/WarpScalar) | vtkWarpScalar |Move vertices along normals.
[WarpSurface](/Cxx/PolyData/WarpSurface) | vtkWarpVector|Warp a surface along its normal.
[WarpTo](/Cxx/Filtering/WarpTo) | vtkWarpTo | Bend an object.
[WarpVector](/Cxx/PolyData/WarpVector) | vtkWarpVector | 


### Data Types

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[CompositePolyDataMapper](/Cxx/CompositeData/CompositePolyDataMapper) | vtkCompositePolyDataMapper |
[MultiBlockDataSet](/Cxx/CompositeData/MultiBlockDataSet) | vtkMultiBlockDataSet | Demonstrates how to make and use VTK's MultiBlock type data
[OverlappingAMR](/Cxx/CompositeData/OverlappingAMR) | vtkOverlappingAMR |Demonstrates how to create and populate a VTK's Overlapping AMR Grid type Data


### Data Type Conversions


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[PolyDataToUnstructuredGrid](/Cxx/PolyData/PolyDataToUnstructuredGrid) | vtkAppendFilter |Convert a vtkPolyData to a vtkUnstructuredGrid.


### Point Cloud Operations

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[CompareExtractSurface](/Cxx/Points/CompareExtractSurface) | vtkExractSurface | Compare three extract surface algorithms.
[DensifyPoints](/Cxx/Points/DensifyPoints) | vtkDensifyPointCloudFilter | Add points to a point cloud.
[DownsamplePointCloud](/Cxx/PolyData/DownsamplePointCloud) | vtkCleanPolyData | Down sample a point cloud. Remove points so that there are no points within a tolerance of any point.
[ExtractClusters](/Cxx/Points/ExtractClusters) | vtkEuclideanClusterExtraction | From a set of randomly distributed spheres, extract connected clusters.
[ExtractPointsDemo](/Cxx/Points/ExtractPointsDemo) | vtkExtractPoints |Extract points inside an implicit function.
[ExtractSurfaceDemo](/Cxx/Points/ExtractSurfaceDemo) | vtkExtractSurface vtkPCANormalEstimation vtkSignedDistance |Create a surface from Unorganized Points using Point filters (DEMO).
[ExtractSurface](/Cxx/Points/ExtractSurface) | vtkExtractSurface vtkPCANormalEstimation vtkSignedDistance |Create a surface from Unorganized Points using Point filters.
[FitImplicitFunction](/Cxx/Points/FitImplicitFunction) | vtkFitImplicitFunction | Extract points within a distance to an implicit function.
[MaskPointsFilter](/Cxx/Points/MaskPointsFilter) | vtkMaskPointsFilter |Extract points within an image mask.
[NormalEstimation](/Cxx/Points/NormalEstimation) | vtkPCANormalEstimation | Estimate the normals of a random points that lie on a sphere.
[PointOccupancy](/Cxx/Points/PointOccupancy) | vtkPointOccupancyFilter |Show which voxels contain points.
[PointSource](/Cxx/PolyData/PointSource) | vtkPointSource |Generate a random point cloud.
[PoissonExtractSurface](/Cxx/Points/PoissonExtractSurface) | | Create a surface from Unorganized Points using the PoissonReconstruction algorithm.
[PowercrustExtractSurface](/Cxx/Points/PowercrustExtractSurface) | | Create a surface from Unorganized Points using the Powercrust algorithm.
[RadiusOutlierRemoval](/Cxx/Points/RadiusOutlierRemoval) | vtkRadiusOutlierRemoval |Remove outliers.
[SignedDistance](/Cxx/Points/SignedDistance) | vtkSignedDistance |Compute signed distance to a point cloud.
[UnsignedDistance](/Cxx/Points/UnsignedDistance) | vtkUnsignedDistance |Compute unsigned distance to a point cloud.


### Working with Meshes


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[AddCell](/Cxx/Meshes/AddCell) | vtkPolyData | Add a cell to an existing mesh.
[BoundaryEdges](/Cxx/Meshes/BoundaryEdges) | vtkFeatureEdges | Find the edges that are used by only one face.
[CellEdges](/Cxx/Meshes/CellEdges) | vtkCell |Get edges of cells.
[ClosedSurface](/Cxx/PolyData/ClosedSurface) | vtkFeatureEdges |Check if a surface is closed.
[ColorDisconnectedRegions](/Cxx/PolyData/ColorDisconnectedRegions) | vtkPolyDataConnectivityFilter | Color each disconnected region of a vtkPolyData a different color.
[ColoredElevationMap](/Cxx/Meshes/ColoredElevationMap)| vtkLookupTable |Color a mesh by height.
[Curvatures](/Cxx/PolyData/Curvatures) | vtkCurvatures |Compute Gaussian, Mean, Min, and Max Curvatures.
[Decimation](/Cxx/Meshes/Decimation) | vtkDecimatePro | Reduce the number of triangles in a mesh.
[DeformPointSet](/Cxx/Meshes/DeformPointSet) | vtkDeformPointSet | Deform a point set with a control polyhedra.
[DijkstraGraphGeodesicPath](/Cxx/PolyData/DijkstraGraphGeodesicPath) | vtkDijkstraGraphGeodesicPath |Find the shortest path between two points on a mesh.
[ElevationFilter](/Cxx/Meshes/ElevationFilter) | vtkElevationFilter |Color a mesh by height.
[ExtractEdges](/Cxx/Meshes/ExtractEdges) | vtkExtractEdges |
[FillHoles](/Cxx/Meshes/FillHoles) | vtkFillHolesFilter | Close holes in a mesh.
[GreedyTerrainDecimation](/Cxx/PolyData/GreedyTerrainDecimation)  | vtkGreedyTerrainDecimation | Create a mesh from an ImageData 
[HighlightBadCells](/Cxx/PolyData/HighlightBadCells) | vtkMeshQuality |
[IdentifyHoles](/Cxx/Meshes/IdentifyHoles) | vtkFillHolesFilter | Close holes in a mesh and identify the holes.
[ImplicitSelectionLoop](/Cxx/PolyData/ImplicitSelectionLoop) | vtkImplicitSelectionLoop |Select a region of a mesh with an implicit function.
[LargestRegion](/Cxx/PolyData/PolyDataConnectivityFilter_LargestRegion)  | vtkPolyDataConnectivityFilter |  Extract the largest connected region in a polydata.
[MatrixMathFilter](/Cxx/Meshes/MatrixMathFilter) | vtkMatrixMathFilter | Compute various quantities on cell and points in a mesh.
[MeshQuality](/Cxx/PolyData/MeshQuality) | vtkMeshQuality |
[OBBDicer](/Cxx/Meshes/OBBDicer) | vtkOBBDicer | Breakup a mesh into pieces.
[PolygonalSurfaceContourLineInterpolator](/Cxx/PolyData/PolygonalSurfaceContourLineInterpolator) | vtkPolygonalSurfaceContourLineInterpolator |Interactively find the shortest path between two points on a mesh.
[QuadricClustering](/Cxx/Meshes/QuadricClustering) | vtkQuadricClustering | Reduce the number of triangles in a mesh.
[QuadricDecimation](/Cxx/Meshes/QuadricDecimation) | vtkQuadricDecimation | Reduce the number of triangles in a mesh.
[SelectPolyData](/Cxx/PolyData/SelectPolyData) | vtkSelectPolyData |Select a region of a mesh.
[SimpleElevationFilter](/Cxx/Meshes/SimpleElevationFilter) | vtkSimpleElevationFilter |Color a mesh by dotting a vector from the origin to each point with a specified vector.
[SmoothPolyDataFilter](/Cxx/PolyData/SmoothPolyDataFilter) | vtkSmoothPolyDataFilter |Laplacian smoothing.
[SpecifiedRegion](/Cxx/PolyData/PolyDataConnectivityFilter_SpecifiedRegion) | vtkPolyDataConnectivityFilter | Extract a specific (specified) connected region in a polydata.
[SplitPolyData](/Cxx/Meshes/SplitPolyData) | vtkOBBDicer | Breakup a mesh into pieces and save the pieces into files
[Subdivision](/Cxx/Meshes/Subdivision) | vtkButterflySubdivisionFilter vtkLoopSubdivisionFilter vtkLinearSubdivisionFilter | Increase the number of triangles in a mesh.
[Triangulate](/Cxx/Meshes/Triangulate) | vtkTriangleFilter | Convert all polygons in a mesh to triangles.
[WeightedTransformFilter](/Cxx/PolyData/WeightedTransformFilter)  | vtkWeightedTransformFilter |
[WindowedSincPolyDataFilter](/Cxx/Meshes/WindowedSincPolyDataFilter) | vtkWindowedSincPolyDataFilter | Smooth a mesh (windowed sinc filter).

#### Clipping

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[BoxClipStructuredPoints](/Cxx/Visualization/BoxClipStructuredPoints) | vtkBoxClipDataSet vtkStructuredPoints |Clip vtkStructuredPoints with a box. The results are unstructured grids with tetrahedra.
[BoxClipUnstructuredGrid](/Cxx/Visualization/BoxClipUnstructuredGrid) | vtkBoxClipDataSet vtkUnstructuredGrid |Clip a vtkUnstructuredGrid with a box. The results are unstructured grids with tetrahedra.
[CapClip](/Cxx/Meshes/CapClip) | vtkClipPolyData |Cap a clipped polydata with a polygon.
[ClipClosedSurface](/Cxx/Meshes/ClipClosedSurface) | vtkClipClosedSurface |Clip a surface with multiple planes.
[ClipDataSetWithPolyData](/Cxx/Meshes/ClipDataSetWithPolyData) | vtkClipDataSet vtkImplicitPolyDataDistance vtkRectilinearGrid |Clip a vtkRectilinearGrid with arbitrary polydata. In this example, use a vtkConeSource to generate polydata to slice the grid, resulting in an unstructured grid. Contrast this with the next example.
[ClipFrustum](/Cxx/Meshes/ClipFrustum) | vtkFrustumSource vtkClipPolyData | Clip a vtkPolyData with the vtkCamera's view frustum.
[GenericClip](/Cxx/Filtering/GenericClip) | vtkGenericClip vtkBridgeDataSet vtkGenericDataSet | 
[ImplicitDataSetClipping](/Cxx/PolyData/ImplicitDataSetClipping) | vtkImplicitDataSet |Clip using an implicit data set.
[SolidClip](/Cxx/Meshes/SolidClip) | vtkClipPolyData |Create a "solid" clip.
[TableBasedClipDataSetWithPolyData](/Cxx/Meshes/TableBasedClipDataSetWithPolyData) | vtkTableBasedClipDataSet vtkImplicitPolyDataDistance vtkRectilinearGrid |Clip a vtkRectilinearGrid with arbitrary polydata. In this example, use a vtkConeSource to generate polydata to slice the grid, resulting in an unstructured grid. Contrast this with the previous example.


### Working with Structured 3D Data
This section includes vtkImageData vtkStructuredGrid and vtkRectilinearGrid.

"ImageData" is not the traditional "flat, 2D image" you are used to. It is a special VTK data structure in the collection of 3D data structures provided by VTK. [Here is an overview of these data structures](http://www.vtk.org/Wiki/VTK/Tutorials/3DDataTypes). Image data can represent at typical 2D image, but also, a 3D volume.

* [Demonstration of structured data types](/Cxx/Visualization/StructuredDataTypes)
* [Get the linear point id of a point in a grid](/Cxx/StructuredData/GetLinearPointId)

#### vtkImageData

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[CellIdFromGridCoordinates](/Cxx/ImageData/CellIdFromGridCoordinates) | vtkStructuredData|Get the id of a cell from its grid coordinates.
[ExtractVOI](/Cxx/ImageData/ExtractVOI) | vtkExtractVOI | Extract a volume of interest (subvolume).
[GetCellCenter](/Cxx/ImageData/GetCellCenter) | vtkImageData|Get the coordinates of the center of a cell.
[ImageIterator](/Cxx/ImageData/ImageIterator)| vtkImageIterator |
[ImageIteratorDemo](/Cxx/ImageData/ImageIteratorDemo)| vtkImageIterator | Demonstrate using an iterator to access pixels in a region.
[ImageNormalize](/Cxx/ImageData/ImageNormalize) | vtkImageNormalize |Normalize an image.
[ImageReslice](/Cxx/ImageData/ImageReslice) | vtkImageReslice |Resize a vtkImageData.
[ImageTranslateExtent](/Cxx/ImageData/ImageTranslateExtent) | vtkImageTranslateExtent |Change the extent of a vtkImageData.
[ImageWeightedSum](/Cxx/ImageData/ImageWeightedSum) | vtkImageWeightedSum |Add two or more images.
[IntersectLine](/Cxx/ImageData/IntersectLine) | vtkImageData |Intersect a line with all cells of a vtkImageData.
[IterateImageData](/Cxx/ImageData/IterateImageData) | vtkImageData | Iterating over a vtkImageData.

#### Conversions

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ImageDataGeometryFilter](/Cxx/ImageData/ImageDataGeometryFilter) | vtkImageDataGeometryFilter |Convert a vtkImageData to a vtkPolyData
[ImageDataToPointSet](/Cxx/ImageData/ImageDataToPointSet) | vtkImageDataToPointSet |Convert a vtkImageData to a vtkStructuredGrid.

#### vtkStructuredGrid


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[BlankPoint](/Cxx/StructuredGrid/BlankPoint) | vtkStructuredGrid |Blank a point of a vtkStructuredGrid.
[StructuredGridOutline](/Cxx/StructuredGrid/StructuredGridOutline) | vtkStructuredGridOutlineFilter | Visualize the outline of a structured grid.
[StructuredGrid](/Cxx/StructuredGrid/StructuredGrid) | vtkStructuredGrid |Structured Grid.
[VisualizeStructuredGridCells](/Cxx/StructuredGrid/VisualizeStructuredGridCells) | vtkShrinkFilter | Visualize the cells of a structured grid.
[VisualizeStructuredGrid](/Cxx/StructuredGrid/VisualizeStructuredGrid) | vtkStructuredGridGeometryFilter | Visualize the points of a structured grid.

#### vtkStructuredPoints

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[StructuredPointsToUnstructuredGrid](/Cxx/StructuredPoints/StructuredPointsToUnstructuredGrid) | vtkStructuredPoints vtkUnstructuredGrid|Convert a vtkStructuredPoints to a vtkUnstructuredGrid.

#### vtkRectilinearGrid

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[RectilinearGridToTetrahedra](/Cxx/RectilinearGrid/RectilinearGridToTetrahedra) | vtkRectilinearGridToTetrahedra |Convert a vtkRectilinearGrid to a vtkUnstructuredGrid mesh
[RectilinearGrid](/Cxx/RectilinearGrid/RectilinearGrid) | vtkRectilinearGrid |Rectilinear grid
[VisualizeRectilinearGrid](/Cxx/RectilinearGrid/VisualizeRectilinearGrid) | vtkRectilinearGrid vtkShrinkFilter| Visualize the cells of a rectilinear grid

### Registration

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[IterativeClosestPointsTransform](/Cxx/Filtering/IterativeClosestPointsTransform) | vtkIterativeClosestPointTransform | Iterative Closest Points (ICP) Transform.
[LandmarkTransform](/Cxx/Filtering/LandmarkTransform) | vtkLandmarkTransform |Landmark Transform.

### Medical

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[GenerateCubesFromLabels](/Cxx/Medical/GenerateCubesFromLabels) | vtkMetaImageReader vtkMaskFields |Create cubes from labeled volume data.
[GenerateModelsFromLabels](/Cxx/Medical/GenerateModelsFromLabels) | vtkDiscreteMarchingCubes vtkWindowedSincPolyDataFilter | Create models from labeled volume data (vtkDiscreteMarchingCubes).
[MedicalDemo1](/Cxx/Medical/MedicalDemo1) | vtkMarchingCubes |Create a skin surface from volume data
[MedicalDemo2](/Cxx/Medical/MedicalDemo2) | vtkMarchingCubes |Create a skin and bone surface from volume data
[MedicalDemo3](/Cxx/Medical/MedicalDemo3) | vtkMarchingCubes |Create skin, bone and slices from volume data
[MedicalDemo4](/Cxx/Medical/MedicalDemo4) | vtkFixedPointVolumeRayCastMapper |Create a volume rendering
[TissueLens](/Cxx/Medical/TissueLens) | vtkMarchingCubes vtkClipDataSet  vtkProbeFilter |Cut a volume with a sphere

### Surface reconstruction

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Delaunay3D](/Cxx/Modelling/Delaunay3D) | vtkDelaunay3D | Create a solid mesh from Unorganized Points.
[Delaunay3DDemo](/Cxx/Modelling/Delaunay3DDemo) | vtkDelaunay3DDemo | Interactively adjust Alpha for Delaunay3D.
[ExtractSurfaceDemo](/Cxx/Points/ExtractSurfaceDemo) | vtkExtractSurface vtkPCANormalEstimation vtkSignedDistance |Create a surface from Unorganized Points using Point filters (DEMO).
[ExtractSurface](/Cxx/Points/ExtractSurface) | vtkExtractSurface vtkPCANormalEstimation vtkSignedDistance |Create a surface from Unorganized Points using Point filters.
[GaussianSplat](/Cxx/Filtering/GaussianSplat) | vtkGaussianSplatter |Create a surface from Unorganized Points (Gaussian Splat).
[SurfaceFromUnorganizedPointsWithPostProc](/Cxx/Filtering/SurfaceFromUnorganizedPointsWithPostProc) | vtkSurfaceReconstructionFilter |Create a surface from Unorganized Points (with post processing).
[SurfaceFromUnorganizedPoints](/Cxx/Filtering/SurfaceFromUnorganizedPoints) | vtkSurfaceReconstructionFilter |Create a surface from Unorganized Points.
[TriangulateTerrainMap](/Cxx/Filtering/TriangulateTerrainMap) | vtkDelaunay2D | Generate heights (z values) on a 10x10 grid (a terrain map) and then triangulate the points to form a surface.

## Utilities

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[BoundingBoxIntersection](/Cxx/Utilities/BoundingBoxIntersection) | vtkBoundingBox |Box intersection and Inside tests.
[BoundingBox](/Cxx/Utilities/BoundingBox) | vtkBoundingBox |Bounding Box construction.
[BrownianPoints](/Cxx/Utilities/BrownianPoints) | vtkBrownianPoints |Produce a random vector at each point in a dataset.
[CardinalSpline](/Cxx/Utilities/CardinalSpline) | vtkCardinalSpline |Cardinal spline Interpolation.
[Casting](/Cxx/PolyData/Casting)| vtkObject::SafeDownCast | Casting VTK objects.
[CheckVTKVersion](/Cxx/Utilities/CheckVTKVersion) | vtkVersion | Check VTK Version.
[ColorLookupTable](/Cxx/Utilities/ColorLookupTable) | vtkLookupTable |Color Lookup Table.
[ColorTransferFunction](/Cxx/Utilities/ColorTransferFunction) | vtkColorTransferFunction |Color Transfer Function.
[CommandSubclass](/Cxx/Utilities/CommandSubclass) | vtkCommand | Instead of using a callback function, it is more powerful to subclass vtkCommand.
[ConstrainedDelaunay2D](/Cxx/Filtering/ConstrainedDelaunay2D) |  vtkDelaunay2D | Perform a 2D Delaunay triangulation on a point set respecting a specified boundary.
[Coordinate](/Cxx/Utilities/Coordinate)| vtkCoordinate |Coordinate system conversions.
[DeepCopy](/Cxx/Utilities/DeepCopy) |  | Deep copy a VTK object.
[Delaunay2D](/Cxx/Filtering/Delaunay2D) | vtkDelaunay2D | Perform a 2D Delaunay triangulation on a point set.
[DetermineActorType](/Cxx/Utilities/DetermineActorType) | vtkActor vtkActorCollection |Determine the type of an actor.
[DiscretizableColorTransferFunction](/Cxx/Utilities/DiscretizableColorTransferFunction) | vtkDiscretizableColorTransferFunction |Discretizable Color Transfer Function.
[FileOutputWindow](/Cxx/Utilities/FileOutputWindow) | vtkFileOutputWindow | Write errors to a log file instead of the screen.
[FilenameFunctions](/Cxx/Utilities/FilenameFunctions) | vtkDirectory vtksys/SystemTools | Do things like get the file extension, strip the file extension, etc.
[FilterSelfProgress](/Cxx/Developers/FilterSelfProgress) |  |Monitor a filters progress.
[FrameRate](/Cxx/Utilities/FrameRate) | | Get the frame rate of the rendering.
[FullScreen](/Cxx/Utilities/FullScreen) | vtkRenderWindow | Maximize/full screen a vtkRenderWindow.
[FunctionParser](/Cxx/Utilities/FunctionParser) | vtkFunctionParser |String function parser.
[GetClassName](/Cxx/Utilities/GetClassName) | GetClassName() |Determine the type of a VTK variable.
[GetDataRoot](/Cxx/Utilities/GetDataRoot) | vtkTesting | Find the path of VTK_DATA_ROOT.
[LUTUtilities](/Cxx/Utilities/LUTUtilities) | vtkLookupTable vtkColorSeries | A utility class for vtkLookupTable allowing you to output the table contents or to compare tables.
[MultipleRenderWindows](/Cxx/Visualization/MultipleRenderWindows) | vtkRenderWindow | Multiple Render Windows
[MultipleViewports](/Cxx/Visualization/MultipleViewports) | vtkRenderer::SetViewPort |Multiple Viewports.
[OffScreenRendering](/Cxx/Utilities/OffScreenRendering) | vtkImagingFactory vtkGraphicsFactory |Off Screen Rendering.
[PCADemo](/Cxx/Utilities/PCADemo) | vtkPCAStatistics |Project 2D points onto the best 1D subspace (PCA Demo).
[PCAStatistics](/Cxx/Utilities/PCAStatistics) | vtkPCAStatistics |Compute Principal Component Analysis (PCA) values.
[PassThrought](/Cxx/InfoVis/PassThrough) | vtkPassThrough |Pass input along to outpu.
[PiecewiseFunction](/Cxx/Utilities/PiecewiseFunction) | vtkPiecewiseFunction |Interpolation using a piecewise function.
[PointInPolygon](/Cxx/Utilities/PointInPolygon) | vtkPolygon | Point inside polygon test.
[ReportRenderWindowCapabilities](/Cxx/Utilities/ReportRenderWindowCapabilities) | vtkRenderWindow | Report the capabilities of a render window.
[SaveSceneToFieldData](/Cxx/Utilities/SaveSceneToFieldData) | vtkCamera | Save a vtkCamera's state i a vtkDataSet's vtkFieldData and restore it.
[SaveSceneToFile](/Cxx/Utilities/SaveSceneToFile) | vtkCamera | Save a vtkCamera's state in a file and restore it.d.
[Screenshot](/Cxx/Utilities/Screenshot) | vtkWindowToImageFilter |
[ShallowCopy](/Cxx/Utilities/ShallowCopy) |  | Shallow copy a VTK object.
[ShareCamera](/Cxx/Utilities/ShareCamera) | vtkRenderer vtkCamera | Share a camera between multiple renderers.
[ShepardMethod](/Cxx/Utilities/ShepardMethod) | vtkShepardMethod |Shepard method interpolation.
[SideBySideViewports](/Cxx/Visualization/SideBySideViewports) | vtkRenderer::SetViewPort | Side by side viewports.
[TimeStamp](/Cxx/Utilities/TimeStamp) | vtkTimeStamp |Time stamp.
[TimerLog](/Cxx/Utilities/TimerLog) | vtkTimerLog |Timer log.
[Timer](/Cxx/Utilities/Timer) | vtkRenderWindowInteractor::CreateRepeatingTimer |
[Variant](/Cxx/Utilities/Variant) | vtkVariant |Convert between data types.
[Vector](/Cxx/Utilities/Vector) | vtkVector |Mathematical vector class.
[VersionMacros](/Cxx/Utilities/VersionMacros) | Macro/#define's | Check VTK Version.
[ViewportBorders](/Cxx/Utilities/ViewportBorders) | | Draw a border around each viewport.
[VisualDebugging](/Cxx/Demos/VisualDebugging) | | Update the screen from inside an algorithm.
[ZBuffer](/Cxx/Utilities/ZBuffer) | vtkRenderer | zbuffer.

### Arrays

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[2DArray](/Cxx/Utilities/2DArray) | vtkDenseArray |2D Array.
[3DArray](/Cxx/Utilities/3DArray) | vtkDenseArray |3D Array.
[ArrayCalculator](/Cxx/Utilities/ArrayCalculator) | vtkArrayCalculator | Perform in-place operations on arrays.
[ArrayLookup](/Cxx/Utilities/ArrayLookup) | vtkDataArray | Find the location of a value in a vtkDataArray.
[ArrayRange](/Cxx/Utilities/ArrayRange) | vtkFloatArray::GetRange |Get the bounds (min,max) of a vtk array.
[ArrayToTable](/Cxx/InfoVis/ArrayToTable) | vtkArrayToTable |Convert a vtkDenseArray to a vtkTable.
[ArrayWriter](/Cxx/Utilities/ArrayWriter) | vtkArrayWriter| Write a DenseArray or SparseArray to a file.
[ConstructTable](/Cxx/Utilities/ConstructTable) | vtkTable | A table is a 2D array of any type of elements. They do not all have to be the same type. This is achieved using vtkVariant.
[CustomDenseArray](/Cxx/Utilities/CustomDenseArray) | vtkDenseArray |Custom type Dense (2D) Array.
[DenseArrayRange](/Cxx/Utilities/DenseArrayRange) | vtkDenseArray vtkArrayRange |Get the bounds of a vtkDenseArray.
[ExtractArrayComponent](/Cxx/Utilities/ExtractArrayComponent) | vtkArrayCalculator |Extract a component of an array.
[KnownLengthArray](/Cxx/Utilities/KnownLengthArray) | vtkFloatArray |Known Length Array.
[SortDataArray](/Cxx/Utilities/SortDataArray) | vtkSortDataArray | Reorder array values based on an ordering (key) array.
[SparseArray](/Cxx/Utilities/SparseArray) | vtkSparseArray |Sparse Array.
[UnknownLengthArray](/Cxx/Utilities/UnknownLengthArray) | vtkFloatArray |Unknown Length Array.
[VectorArrayKnownLength](/Cxx/Utilities/VectorArrayKnownLength) | vtkFloatArray |Array of Vectors (Known Length).
[VectorArrayUnknownLength](/Cxx/Utilities/VectorArrayUnknownLength) | vtkFloatArray |Array of Vectors (Unknown Length).

### Events

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[CameraModifiedEvent](/Cxx/Utilities/CameraModifiedEvent) | vtkCameraWindow | Catch the camera modified event.
[ObserveError](/Cxx/Utilities/ObserveError) | vtkCommand | Catch errors and warnings.
[WindowModifiedEvent](/Cxx/Utilities/WindowModifiedEvent) | vtkRenderWindow | Catch the window modified event.

## CMake Techniques

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Check if a specific module is present](/Cxx/CMakeTechniques/CheckForModule) |  |
[Check VTK Version in CMake](/Cxx/Utilities/CMakeVTKVersionCheck) | |  | 


## Math Operations

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[EigenSymmetric](/Cxx/Math/EigenSymmetric)| vtkMath::Jacobi |Compute eigenvalues and eigenvectors of a symmetric matrix.
[HomogeneousLeastSquares](/Cxx/Math/HomogeneousLeastSquares)| vtkMath::SolveHomogeneousLeastSquares |Homogeneous Least Squares.
[1DTupleInterpolation](/Cxx/Math/1DTupleInterpolation)| vtkTupleInterpolator vtkCardinalSpline vtkKochanekSpline | A simple example demonstrating how functions defined by sparsely distributed supporting points can be interpolated at arbitrary positions.
[LUFactorization](/Cxx/Math/LUFactorization)| vtkMath |LU Factorization.
[LeastSquares](/Cxx/Math/LeastSquares)| vtkMath::SolveLeastSquares |Least Squares.
[MatrixInverse](/Cxx/Math/MatrixInverse)| vtkMatrix3x3 |Matrix inverse.
[MatrixTranspose](/Cxx/Math/MatrixTranspose)| vtkMatrix3x3 |Matrix transpose.
[NormalizeVector](/Cxx/Math/NormalizeVector)| vtkMath |Normalize a vector.
[PerpendicularVector](/Cxx/Math/PerpendicularVector) | vtkMath::Perpendiculars |Get a vector perpendicular to another vector.
[VectorDot](/Cxx/Math/VectorDot)| vtkVectorDot |
[VectorNorm](/Cxx/Math/VectorNorm) | vtkVectorNorm |Get the lengths of an array of vectors.


## Graphs

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[AdjacencyMatrixToEdgeTable](/Cxx/Graphs/AdjacencyMatrixToEdgeTable)| vtkAdjacencyMatrixToEdgeTable | Convert an adjacency matrix to an edge table.
[AdjacentVertexIterator](/Cxx/Graphs/AdjacentVertexIterator)| vtkAdjacentVertexIterator |Get all vertices connected to a specified vertex.
[BoostBreadthFirstSearchTree](/Cxx/Graphs/BoostBreadthFirstSearchTree)| vtkBoostBreadthFirstSearchTree | Breadth first search tree. Can also be used to convert a graph to a tree.
[BreadthFirstDistance](/Cxx/Graphs/BreadthFirstDistance)| vtkBoostBreadthFirstSearch |Distance from origin.
[ColorEdges](/Cxx/Graphs/ColorEdges)| vtkGraphLayoutView |Color edges.
[ColorVertexLabels](/Cxx/Graphs/ColorVertexLabels)| vtkGraphLayoutView vtkRenderedGraphRepresentation |Set the color of vertex labels.
[ColorVerticesLookupTable](/Cxx/Graphs/ColorVerticesLookupTable)| vtkGraphLayoutView |Color vertices.
[ConnectedComponents](/Cxx/Graphs/ConnectedComponents)| vtkBoostConnectedComponents |Find connected components of a graph.
[ConstructGraph](/Cxx/Graphs/ConstructGraph)| vtkMutableUndirectedGraph |Construct a graph.
[ConstructTree](/Cxx/Graphs/ConstructTree)| vtkTree vtkMutableDirectedGraph  |Construct a tree.
[DepthFirstSearchAnimation](/Cxx/Graphs/DepthFirstSearchAnimation)| vtkTreeDFSIterator |Depth First Search Animation.
[DepthFirstSearchIterator](/Cxx/Graphs/DepthFirstSearchIterator)| vtkTreeDFSIterator |Depth First Search iterator.
[EdgeListIterator](/Cxx/Graphs/EdgeListIterator)| vtkEdgeListIterator |Iterate over edges of a graph.
[EdgeWeights](/Cxx/Graphs/EdgeWeights)| vtkGraph::GetEdgeData::AddArray |Edge weights.
[GraphPoints](/Cxx/InfoVis/GraphPoints)| vtkGraph::SetPoints, vtkPassThroughLayoutStrategy |Manually set coordinates of vertices in a graph.
[GraphToPolyData](/Cxx/Graphs/GraphToPolyData)| vtkGraphToPolyData |Convert a graph to a PolyData.
[InEdgeIterator](/Cxx/Graphs/InEdgeIterator)| vtkInEdgeIterator |Iterate over edges incoming to a vertex.
[LabelVerticesAndEdges](/Cxx/Graphs/LabelVerticesAndEdges)| vtkGraphLayoutView |Label vertices and edges.
[MinimumSpanningTree](/Cxx/Graphs/MinimumSpanningTree)| vtkBoostPrimMinimumSpanningTree |Minimum spanning tree of a graph.
[MutableGraphHelper](/Cxx/InfoVis/MutableGraphHelper)| vtkMutableGraphHelper |Create either a vtkMutableDirectedGraph or vtkMutableUndirectedGraph.
[NOVCAGraph](/Cxx/Graphs/NOVCAGraph)| vtkUnstructuredGrid vtkXMLUnstructuredGridWriter vtkPolyLine|Create a graph & visualize it in ParaView/VisIt.
[OutEdgeIterator](/Cxx/Graphs/OutEdgeIterator)| vtkOutEdgeIterator |Iterate over edges outgoing from a vertex.
[RandomGraphSource](/Cxx/Graphs/RandomGraphSource)| vtkRandomGraphSource |Create a random graph.
[RemoveIsolatedVertices](/Cxx/Graphs/RemoveIsolatedVertices)| vtkRemoveIsolatedVertices |Remove vertices of degree 0 from a vtkGraph.
[ScaleVertices](/Cxx/Graphs/ScaleVertices)| vtkGraphLayoutView vtkRenderedGraphRepresentation |Size/scale vertices based on a data array.
[SelectedVerticesAndEdges](/Cxx/Graphs/SelectedVerticesAndEdges)| vtkAnnotationLink |Get a list of selected vertices and edges.
[SelectedVerticesAndEdgesObserver](/Cxx/Graphs/SelectedVerticesAndEdgesObserver)| vtkAnnotationLink |Get a list of selected vertices and edges using an observer of AnnotationChangedEvent.
[ShortestPath](/Cxx/Graphs/ShortestPath)| vtkDijkstraGraphGeodesicPath |Find the shortest path on a graph.
[SideBySideGraphs](/Cxx/Graphs/SideBySideGraphs)| vtkGraphLayoutView |Display two graphs side by side.
[TreeBFSIterator](/Cxx/Graphs/TreeBFSIterator)| vtkTreeBFSIterator |Breadth First Search iterator.
[VertexSize](/Cxx/Graphs/VertexSize)| vtkGraphLayoutView vtkRenderedGraphRepresentation | Set the size of vertices.
[VisualizeDirectedGraph](/Cxx/Graphs/VisualizeDirectedGraph)| vtkGlyphSource2D | Visualize a directed graph.
[VisualizeGraph](/Cxx/Graphs/VisualizeGraph)| vtkGraphLayoutView vtkGraphLayoutStrategy vtkSimple2DLayoutStrategy | Visualize a graph.

### Graph Conversions

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[DirectedGraphToMutableDirectedGraph](/Cxx/Graphs/Conversions/DirectedGraphToMutableDirectedGraph)| vtkMutableDirectedGraph vtkDirectedGraph | vtkDirectedGraph to vtkMutableDirectedGraph.
[MutableDirectedGraphToDirectedGraph](/Cxx/Graphs/Conversions/MutableDirectedGraphToDirectedGraph)| vtkMutableDirectedGraph vtkDirectedGraph | vtkMutableDirectedGraph to vtkDirectedGraph.
[TreeToMutableDirectedGraph](/Cxx/Graphs/Conversions/TreeToMutableDirectedGraph)| vtkMutableDirectedGraph vtkTree | vtkTree to vtkMutableDirectedGraph

## Data Structures

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[AttachAttributes](/Cxx/PolyData/AttachAttributes)| vtkInformation | Attach attributes to a VTK array
[CellLocatorVisualization](/Cxx/PolyData/CellLocatorVisualization)| vtkCellLocator | Visualization of the tree of a vtkCellLocator.
[CellLocator](/Cxx/PolyData/CellLocator)| vtkCellLocator | Project a point onto a mesh. Closest point on a mesh.Efficient 3D cell query.
[CellTreeLocator](/Cxx/PolyData/CellTreeLocator)| vtkCellTreeLocator |Points inside an object using vtkCellTreeLocator.
[PointLocatorVisualization](/Cxx/PolyData/PointLocatorVisualization)| vtkPointLocator | Visualization of the tree of a vtkPointLocator.
[PointLocator](/Cxx/PolyData/PointLocator)| vtkPointLocator |Efficient 3D point query.
[PointLocatorRadius](/Cxx/PolyData/PointLocatorRadius)| vtkPointLocator |Find all points within a radius of a specified point.


### Timing Demonstrations

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[KDTreeTimingDemo](/Cxx/DataStructures/KDTreeTimingDemo)| vtkKdTreePointLocator | Plot the runtime vs MaxLevel (doesn't seem correct)
[ModifiedBSPTreeTimingDemo](/Cxx/DataStructures/ModifiedBSPTreeTimingDemo)| vtkModifiedBSPTree | Plot the runtime vs MaxLevel
[OBBTreeTimingDemo](/Cxx/DataStructures/OBBTreeTimingDemo)| vtkOBBTree | Plot the runtime vs MaxLevel
[OctreeTimingDemo](/Cxx/DataStructures/OctreeTimingDemo)| vtkOctreePointLocator | Plot the runtime vs MaxPointsPerRegionOctree timing demo.

### KD-Tree


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[BuildLocatorFromKClosestPoints](/Cxx/DataStructures/BuildLocatorFromKClosestPoints)| vtkKdTree |
[ClosestNPoints](/Cxx/DataStructures/KdTreePointLocator/ClosestNPoints)| vtkKdTreePointLocator |Find the closest N points to a query point.
[DataStructureComparison](/Cxx/DataStructures/DataStructureComparison)| vtkKdTree vtkOBBTree vtkOctreePointLocator vtkModifiedBSPTree | Illustrates, side by side, the differences between several spatial data structures
[KDTreeAccessPoints](/Cxx/DataStructures/KDTreeAccessPoints)| vtkKdTree |Access the points of a KDTree.
[KDTreeFindPointsWithinRadius](/Cxx/DataStructures/KDTreeFindPointsWithinRadius) | vtkKdTreePointLocator |Find points within a specified radius of  a query point.
[KdTreePointLocatorClosestPoint](/Cxx/DataStructures/KdTreePointLocatorClosestPoint)| vtkKdTreePointLocator |Find the closest point to a query point.
[KdTree](/Cxx/DataStructures/KdTree)| vtkKdTree |
[VisualizeKDTree](/Cxx/DataStructures/VisualizeKDTree)| vtkKdTreePointLocator | Visualize levels of the tree.


### Oriented Bounding Box (OBB) Tree

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[OBBTreeIntersectWithLine](/Cxx/DataStructures/OBBTreeIntersectWithLine)| vtkOBBTree |Intersect a line with a vtkOBBTree.
[OBBTreeExtractCells](/Cxx/DataStructures/OBBTreeExtractCells)| vtkOBBTree |Intersect a line with an OBB Tree and display all intersected cells.
[VisualizeOBBTree](/Cxx/DataStructures/VisualizeOBBTree) | vtkOBBTree | Visualize levels of the tree.

### Octree

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[BuildOctree](/Cxx/DataStructures/BuildOctree)| vtkOctreePointLocator |Create an octree.
[OctreeFindPointsWithinRadius](/Cxx/DataStructures/OctreeFindPointsWithinRadius)| vtkOctreePointLocator |Find the points within a sphere of specified radius to a query point.
[IncrementalOctreePointLocator](/Cxx/DataStructures/IncrementalOctreePointLocator)| vtkIncrementalOctreePointLocator | Insert points into an octree without rebuilding it.
[OctreeKClosestPoints](/Cxx/DataStructures/OctreeKClosestPoints)| vtkOctreePointLocator |Find the K closest points to a query point.
[OctreeClosestPoint](/Cxx/DataStructures/OctreeClosestPoint)| vtkOctreePointLocator |Find the closest point to a query point.
[OctreeVisualize](/Cxx/DataStructures/OctreeVisualize)| vtkOctreePointLocator | Visualize levels of the tree.

### Modified BSP Tree

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ModifiedBSPTreeIntersectWithLine](/Cxx/DataStructures/ModifiedBSPTreeIntersectWithLine)| vtkModifiedBSPTree |Intersect a line with a modified BSP Tree.
[ModifiedBSPTreeExtractCells](/Cxx/DataStructures/ModifiedBSPTreeExtractCells)| vtkModifiedBSPTree |Intersect a line with a modified BSP Tree and display all intersected cells.
[VisualizeModifiedBSPTree](/Cxx/DataStructures/ModifiedBSPTree/VisualizeModifiedBSPTree)| vtkModifiedBSPTree | Visualize levels of the tree.

### HyperTreeGrid

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[HyperTreeGridSource](/Cxx/HyperTreeGrid/HyperTreeGridSource)| vtkHyperTreeGridSource |Create a vtkHyperTreeGrid.

## VTK Concepts


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Scalars](/Cxx/VTKConcepts/Scalars) | VTKConcepts | Attach a scalar value to each point (PointData) or cell (CellData) in a data set.


## Rendering

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[AmbientSpheres](/Cxx/Rendering/AmbientSpheres)| vtkProperty |Demonstrates the effect of ambient lighting on spheres.
[CylinderRenderingProperties](/Cxx/Rendering/CylinderRenderingProperties)| vtkProperty |Change the properties of a cylinder.
[DiffuseSpheres](/Cxx/Rendering/DiffuseSpheres)| vtkProperty |Demonstrates the effect of diffuse lighting on spheres.
[Rainbow](/Cxx/Rendering/Rainbow)| vtkLookupTable | Use and manipulation of vtkLookupTables.
[Rotations](/Cxx/Rendering/Rotations)| vtkActor::RotateX,Y,Z vtkRenderer::EraseOff | Rotations of a cow about her axes.
[SpecularSpheres](/Cxx/Rendering/SpecularSpheres)| vtkProperty |Demonstrates the effect of specular lighting on spheres.
[StippledLine](/Cxx/Rendering/StippledLine)| vtkTexture | Draw a stippled line.
[WalkCow](/Cxx/Rendering/WalkCow) | vtkBYUReader vtkRenderWindow::EraseOff() vtkActor | This generates Figs. 3-31, 3-32, 3-33 found in VTKTextbook.pdf.


## Lighting


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[LightActor](/Cxx/Lighting/LightActor)| vtkLightActor |Display the location and direction of a light.
[Light](/Cxx/Lighting/Light)| vtkLight |Add a directional light to a scene.
[Shadows](/Cxx/Visualization/Shadows)| vtkShadowMapPass |Create shadows.
[SpotLights](/Cxx/Lighting/SpotLights)| vtkLight | Create two positional(spot) lights.


## Texture Mapping
| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[BackgroundTexture](/Cxx/Visualization/BackgroundTexture)| vtkRenderer vtkTexture |Use a texture for the background of a vtkRenderer.
[ClipArt](/Cxx/Visualization/ClipArt) | vtkTextureMapToPlane | Generate 3D clip art from an image.
[TextureCutQuadric](/Cxx/Texture/TextureCutQuadric)| vtkBooleanTexture vtkImplicitTextureCoords | Cut a quadric with boolean textures.
[TextureCutSphere](/Cxx/Texture/TextureCutSphere)| vtkImplicitTextureCoords | Cut a sphere using texture coordinates.
[TextureMapImageData](/Cxx/Visualization/TextureMapImageData) | vtkImageCanvasSource2D | Texture map an ImageData.
[TextureMapPlane](/Cxx/Visualization/TextureMapPlane)| vtkTextureMapToPlane |Texture map a plane.
[TextureMapQuad](/Cxx/Visualization/TextureMapQuad)| vtkPolygon vtkPolyData |Texture map a quad.
[TexturedSphere](/Cxx/Texture/TexturedSphere)| vtkTextureMapToSphere | Texture a sphere.

## Visualization
See [this tutorial](http://www.vtk.org/Wiki/VTK/Tutorials/3DDataTypes) for a brief explanation of the VTK terminology of mappers, actors, etc.


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Arbitrary3DCursor](/Cxx/Visualization/Arbitrary3DCursor)| vtkPointWidget |Track a 3D cursor.
[AssignCellColorsFromLUT](/Cxx/Visualization/AssignCellColorsFromLUT)| vtkNamedColors vtkPlaneSource vtkLookupTable vtkColorTransferFunction | Demonstrates how to assign colors to cells in a vtkPolyData structure using lookup tables.
[BackfaceCulling](/Cxx/Visualization/BackfaceCulling)| vtkActor | Backface culling.
[BackgroundColor](/Cxx/Visualization/BackgroundColor) | vtkRenderer | Background color.
[BackgroundGradient](/Cxx/Visualization/BackgroundGradient) | vtkRenderer vtkRenderer | Background gradient.
[BillboardTextActor3D](/Cxx/Visualization/BillboardTextActor3D) | vtkBillboardTextActor3D | Label points with billboards.
[BlobbyLogo](/Cxx/Visualization/BlobbyLogo) | vtkImplicitModeller | Blobby logo from VTK textbook.
[BluntStreamlines](/Cxx/VisualizationAlgorithms/BluntStreamlines) | vtkStructuredGridGeometryFilter vtkStreamTracer| Demonstrates airflow around a blunt fin using streamlines.
[CameraActor](/Cxx/Visualization/CameraActor) | vtkCameraActor | Visualize a camera (frustum) in a scene.
[CameraModel1](/Cxx/Visualization/CameraModel1) | vtkCameraActor | Illustrate camera movement.
[CameraModel2](/Cxx/Visualization/CameraModel2) | vtkCameraActor | Illustrate camera movement.
[Camera](/Cxx/Visualization/Camera)| vtkCamera |Positioning and aiming the camera.
[CaptionActor2D](/Cxx/Visualization/CaptionActor2D)| vtkCaptionActor2D |Draw a caption/bubble pointing to a particular point.
[ChooseTextColorDemo](/Cxx/Visualization/ChooseTextColorDemo)| vtkTextActor vtkNamedColors | Create a grid of random colored viewpports and pick a good text color.
[ChooseTextColor](/Cxx/Visualization/ChooseTextColor)| vtkTextActor vtkTextProperty::SetFontFamily vtkNamedColors | Choose a text color that contrasts with a background color.
[CloseWindow](/Cxx/Visualization/CloseWindow)| vtkRenderWindowInteractor vtkRenderWindow |Close a render window.
[ColorActorEdges](/Cxx/Visualization/ColorActorEdges) | vtkActor | Color the edges of an Actor.
[ColorAnActor](/Cxx/Visualization/ColorAnActor) | vtkActor | Color an Actor.
[ColorGlyphs](/Cxx/Visualization/ColorGlyphs)| vtkGlyph3D vtkGlyph3D |Color glyphs.
[ComplexV](/Cxx/Visualization/ComplexV) | vtkHedgeHog | ComplexV from the VTK Textbook.
[CornerAnnotation](/Cxx/Visualization/CornerAnnotation)| vtkCornerAnnotation | Write text in the corners of a window.
[CorrectlyRenderTranslucentGeometry](/Cxx/Visualization/CorrectlyRenderTranslucentGeometry)| vtkDepthSortPolyData |Correctly Rendering Translucent Geometry.
[CubeAxesActor2D](/Cxx/Visualization/CubeAxesActor2D)| vtkCubeAxesActor2D | This example uses the vtkCubeAxesActor2D to show your scene with axes to indicate the spatial extent of your data.
[CubeAxesActor](/Cxx/Visualization/CubeAxesActor)| vtkCubeAxesActor |Display three orthogonal axes with labels.
[Cursor3D](/Cxx/Visualization/Cursor3D)| vtkCursor3D |
[CursorShape](/Cxx/Visualization/CursorShape)| vtkRenderWindow |Change the shape of the cursor.
[CurvatureBandsWithGlyphs](/Cxx/Visualization/CurvatureBandsWithGlyphs)| vtkCurvatures vtkBandedPolyDataContourFilter vtkLookupTable vtkColorSeries vtkGlyph3D | Demonstrates the coloring of a surface by partitioning the gaussian curvature of a surface into bands and using arrows to display the normals on the surface.
[CurvedReformation](/Cxx/Visualization/CurvedReformation) | vtkProbeFilter| Sample a volume with a curved surface. In medical imaging, this is often called curved multi planar reformation.
[Cutter](/Cxx/VisualizationAlgorithms/Cutter)| vtkCutter |
[DepthSortPolyData](/Cxx/Visualization/DepthSortPolyData)| vtkDepthSortPolyData |Poly Data Depth Sorting.
[DisplacementPlot](/Cxx/VisualizationAlgorithms/DisplacementPlot) | vtkColorTransferFunction vtkWarpVector vtkVectorDot | Show modal lines for a vibrating beam.
[DisplayCoordinateAxes](/Cxx/Visualization/DisplayCoordinateAxes)| vtkOrientationMarkerWidget |Display coordinate axes.
[DisplayQuadricSurfaces](/Cxx/Visualization/DisplayQuadricSurfaces)| vtkQuadric vtkSampleFunction vtkContourFilter |Display Quadric Surfaces.
[DistanceToCamera](/Cxx/Visualization/DistanceToCamera) | vtkDistanceToCamera |
[DrawText](/Cxx/Visualization/DrawText)| vtkTextActor vtkTextProperty |Display Text.
[ElevationBandsWithGlyphs](/Cxx/Visualization/ElevationBandsWithGlyphs)| vtkBandedPolyDataContourFilter vtkLookupTable vtkColorSeries vtkGlyph3D | Demonstrates the coloring of a surface by partitioning the elevation into bands and using arrows to display the normals on the surface.
[ExtrudePolyDataAlongLine](/Cxx/Visualization/ExtrudePolyDataAlongLine) | vtkRuledSurfaceFilter | Extrude a 2D polydata along a line in 3D space.
[FastSplatter](/Cxx/Visualization/FastSplatter)| vtkFastSplatter |Convolve a splat image with every point in an input image.
[FindCellIntersections](/Cxx/VisualizationAlgorithms/FindCellIntersections) | vtkCellLocator | Find the intersection of a line and the cells in an unstructured dataset
[FlatShading](/Cxx/Visualization/FlatShading) | vtkActor |
[Follower](/Cxx/Visualization/Follower) | vtkFollower | Draw text that stays right side up.
[FontFile](/Cxx/Visualization/FontFile) | vtkTextProperty | Use an external font.
[Glyph2D](/Cxx/Filtering/Glyph2D) | vtkGlyph2D|
[Glyph3D](/Cxx/Filtering/Glyph3D) | vtkGlyph3D|
[Glyph3DImage](/Cxx/Visualization/Glyph3DImage)| vtkGlyph3DMapper | Glyph the points in a vtkImageData.
[Glyph3DMapper](/Cxx/Visualization/Glyph3DMapper)| vtkGlyph3DMapper |
[Hawaii](/Cxx/Visualization/Hawaii)| vtkElevationFilter vtkColorSeries vtkLookupTable | Visualize elevations by coloring the scalar values with a lookup table.
[HedgeHog](/Cxx/Visualization/HedgeHog)| vtkHedgeHog vtkStructuredGrid |Create oriented lines (hedgehogs) from vector data.
[HideActor](/Cxx/Visualization/HideActor)| vtkPropCollection vtkProp | visible
[HideAllActors](/Cxx/Visualization/HideAllActors)| vtkRenderer |Hide all actors.
[ImageMapper](/Cxx/Visualization/ImageMapper)| vtkImageMapper | Display an image in 2D.
[ImageOrder](/Cxx/Visualization/ImageOrder)| vtkRenderer |Determine the display order of a stack of images.
[ImageOrientation](/Cxx/Visualization/ImageOrientation) | vtkInteractorStyleImage |Orientation of the view of an image.
[ImageTransparency](/Cxx/Visualization/ImageTransparency)| vtkImageData|Set transparency of image pixels.
[IsosurfaceSampling](/Cxx/Visualization/IsosurfaceSampling) | vtkProbeFilter|Demonstrates how to create point data on an isosurface.
[Kitchen](/Cxx/Visualization/Kitchen) | vtkStreamTracer vtkStructuredGrid| Demonstrates stream tracing in a kitchen.
[LODProp3D](/Cxx/Visualization/LODProp3D) | vtkLODProp3D | Level of detail rendering.
[LabelContours](/Cxx/Visualization/LabelContours)| vtkLabeledDataMapper |Label Contours.
[LabelPlacementMapper](/Cxx/Visualization/LabelPlacementMapper)| vtkPointSetToLabelHierarchy vtkLabelPlacementMapper | Display a non-overlapping text label at each point.
[LabeledDataMapper](/Cxx/Visualization/LabeledDataMapper)| vtkLabeledDataMapper |Display the point ID at each point.
[LabeledMesh](/Cxx/Visualization/LabeledMesh) | vtkLabeledDataMapper | Label Mesh.
[LegendScaleActor](/Cxx/Visualization/LegendScaleActor)| vtkLegendScaleActor |Display the scale of a scene.
[Legend](/Cxx/Visualization/Legend) | vtkLegendBoxActor |
[LineWidth](/Cxx/Visualization/LineWidth)| vtkActor vtkProperty |Change the width/thickness of lines in an actor.
[MovableAxes](/Cxx/Visualization/MovableAxes) | vtkFollower vtkAxesActor vtkAssembly | Movable axes.
[MoveActor](/Cxx/Visualization/MoveActor)| vtkInteractorStyleTrackballActor |Moving an Actor.
[MoveCamera](/Cxx/Visualization/MoveCamera)| vtkInteractorStyleTrackballCamera |Moving the Camera.
[MultipleActors](/Cxx/Visualization/MultipleActors)| vtkActor |Multiple Actors.
[NamedColors](/Cxx/Visualization/NamedColors) | vtkNamedColors | Demonstrate the use of the vtkNamedColors class.<
[NamedColorPatches](/Cxx/Visualization/NamedColorPatches) | vtkNamedColors | Creates a HTML file called [VTKNamedColorPatches](http://htmlpreview.github.com/?https://github.com/lorensen/VTKExamples/blob/master/src/Python/Visualization/VTKNamedColorPatches.html) | Demonstrates how to use the vtkNamedColors class.
[NoShading](/Cxx/Visualization/NoShading) | vtkActor |
[NormalsDemo](/Cxx/Visualization/NormalsDemo)| vtkPolyDataNormals | Demo different ooption to generate normals.
[Opacity](/Cxx/Visualization/Opacity)| vtkActor | Transparency, transparent.
[OrientedGlyphs](/Cxx/Visualization/OrientedGlyphs)| vtkGlyph3D|Create oriented glyphs from vector data.
[PlateVibration](/Cxx/VisualizationAlgorithms/PlateVibration) | vtkWarpVector vtkVectorDot | Demonstrates the motion of a vibrating beam.
[PointDataSubdivision](/Cxx/Visualization/PointDataSubdivision) | vtkLinearSubdivisionFilter vtkButterflySubdivisionFilter | Demonstrates the effect of applying these filters on various sources.
[PointSize](/Cxx/Visualization/PointSize) | vtkActor |
[ProgrammableGlyphFilter](/Cxx/Visualization/ProgrammableGlyphFilter)| vtkProgrammableGlyphFilter |Generate a custom glyph at each point.
[QuadraticSurface](/Cxx/Visualization/QuadraticSurface)| vtkQuadric |Display a quadratic surface.
[QuadricLODActor](/Cxx/Visualization/QuadricLODActor)| vtkQuadricLODActor | Level of detail adjustment.
[RandomProbe](/Cxx/Visualization/RandomProbe)| vtkProbeFilter|Demonstrates how to probe a dataset with random points and select points inside the data set.
[RenderLargeImage](/Cxx/Visualization/RenderLargeImage)| vtkRenderLargeImage |Render a large image, larger than a window.
[RenderView](/Cxx/Views/RenderView)| vtkRenderView |A little bit easier rendering.
[ReverseAccess](/Cxx/Visualization/ReverseAccess) | vtkActor|Demonstrates how to access the source (e.g. vtkSphereSource) of an actor reversely.
[RotateActor](/Cxx/Visualization/RotateActor)| vtkActor |Rotate an Actor.
[ScalarBarActorColorSeries](/Cxx/Visualization/ScalarBarActorColorSeries)| vtkScalarBarActor vtkColorSeries | Display a color bar with a color series lookup table.
[ScalarBarActor](/Cxx/Visualization/ScalarBarActor)| vtkScalarBarActor | Display a color bar.
[ScalarVisibility](/Cxx/Visualization/ScalarVisibility)| vtkDataSetMapper | Switch between coloring the actor and coloring the data.
[ScaleGlyphs](/Cxx/Visualization/ScaleGlyphs)| vtkGlyph3D vtkGlyph3D |Scale glyphs.
[SceneBounds](/Cxx/Visualization/SceneBounds)| vtkRenderer |Get the bounds of the whole scene.
[SelectWindowRegion](/Cxx/Visualization/SelectWindowRegion)| vtkInteractorStyleRubberBand2D |Select a region of a window.
[StreamLines](/Cxx/Visualization/StreamLines) | vtkStreamTracer | Streamlines.
[TensorGlyph](/Cxx/Visualization/TensorGlyph)| vtkTensorGlyph | Draw a rotated/scaled glyph at each point.
[TextSource](/Cxx/Visualization/TextSource)| vtkTextSource |Display text.
[TransformActorCollection](/Cxx/Visualization/TransformActorCollection)| vtkActorCollection |Transform an actor collection.
[TransformActor](/Cxx/Visualization/TransformActor)| vtkActor |Transform an Actor.
[TubesFromSplines](/Cxx/VisualizationAlgorithms/TubesFromSplines)| vtkTubeFilter vtkParametricFunctionSource  vtkTupleInterpolator|Create tubes from interpolated points and scalars.
[TubesWithVaryingRadiusAndColors](/Cxx/VisualizationAlgorithms/TubesWithVaryingRadiusAndColors)| vtkTubeFilter |Create tubes with varying radius and colors.
[VectorOfActors](/Cxx/Visualization/VectorOfActors)| vtkActor |Multiple Actors in a Vector.
[VectorText](/Cxx/Visualization/VectorText)| vtkVectorText |Display high resolution text.
[VertexGlyphFilter](/Cxx/Filtering/VertexGlyphFilter) | vtkVertexGlyphFilter | Add a vertex to each point.
[VelocityProfile](/Cxx/VisualizationAlgorithms/VelocityProfile) | vtkMultiBlockPLOT3DReader vtkStructuredGridGeometryFilter vtkAppendPolyData vtkWarpVector | Warping the geometry of three planes to show flow momentum.
[Visualize2DPoints](/Cxx/Visualization/Visualize2DPoints)| vtkPolyDataMapper2D vtkProperty2D | Visualize a 2D Set of Points.
[VisualizeImageData](/Cxx/Visualization/VisualizeImageData)| vtkDataSetMapper | Visualize the points of an ImageData.
[VisualizeVTP](/Cxx/Visualization/VisualizeVTP)| vtkXMLPolyDataReader vtkPolyDataMapper | Visualize a VTP File.
[WindowSize](/Cxx/Visualization/WindowSize)| vtkRenderWindow:SetSize | Change the size of a window.
[WindowTitle](/Cxx/Visualization/WindowTitle)| vtkRenderWindow | Change the title of a window.
[Wireframe](/Cxx/Visualization/Wireframe)| vtkActor |
[KochSnowflake](/Cxx/Visualization/KochSnowflake) | vtkPolyData vtkPolyLine vtkTriangle vtkLookupTable| Use recursion to represent a Koch snowflake fractal.

## Volume Rendering


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[FixedPointVolumeRayCastMapperCT](/Cxx/VolumeRendering/FixedPointVolumeRayCastMapperCT)| vtkFixedPointVolumeRayCastMapper vtkColorTransferFunction vtkDICOMImageReader vtkMetaImageReader | Volume render DICOM or Meta volumes with various vtkColorTransferFunction's.
[HAVS](/Cxx/VolumeRendering/HAVSVolumeMapper)| vtkHAVSVolumeMapper |
[IntermixedUnstructuredGrid](/Cxx/VolumeRendering/IntermixedUnstructuredGrid)| vtkUnstructuredGridVolumeRayCastMapper vtkSLCReader |mix of poly data and unstructured grid volume mapper.
[MinIntensityRendering](/Cxx/VolumeRendering/MinIntensityRendering)| vtkFixedPointVolumeRayCastMapper |Min intensity rendering.
[SmartVolumeMapper](/Cxx/VolumeRendering/SmartVolumeMapper)| vtkSmartVolumeMapper |Smart volume mapper.


## User Interaction

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[AreaPicking](/Cxx/Picking/AreaPicking)| vtkAreaPicker |Area Picking.
[Assembly](/Cxx/Interaction/Assembly)| vtkAssembly | Combine/group actors into an assembly.
[CallData](/Cxx/Interaction/CallData)| vtkCommand | Pass an observer a value (via CallData).
[CellPicking](/Cxx/Picking/CellPicking)| vtkCellPicker | Cell Picking.
[ClientData](/Cxx/Interaction/ClientData)| vtkCommand | Give an observer access to an object (via ClientData).
[DoubleClick](/Cxx/Interaction/DoubleClick)| vtkInteractorStyleTrackballCamera |Catch a double click.
[Game](/Cxx/Interaction/Game)| vtkInteractorStyleTrackballActor | Move a cube into a sphere.
[EllipticalButton](/Cxx/Interaction/EllipticalButton)| vtkEllipticalButtonSource vtkButtonWidget |Create an elliptical button.
[HighlightPickedActor](/Cxx/Picking/HighlightPickedActor)| vtkPropPicker |Highlight a picked actor.
[HighlightSelectedPoints](/Cxx/Picking/HighlightSelectedPoints)| vtkExtractGeometry |Highlight Selected Points.
[HighlightSelection](/Cxx/Picking/HighlightSelection)| vtkExtractPolyDataGeometry |Highlight selection.
[ImageClip](/Cxx/Interaction/ImageClip)| vtkImageClip | Demonstrates how to interactively select and display a region of an image.
[ImageRegion](/Cxx/Interaction/ImageRegion)| vtkCommand |Select a region of an image.
[InteractorStyleTerrain](/Cxx/Interaction/InteractorStyleTerrain)| vtkInteractorStyleTerrain |Terrain mode.
[InteractorStyleUser](/Cxx/Interaction/InteractorStyleUser)| vtkInteractorStyleUser | Create a completely custom interactor style (no default functionality is provided)
[KeypressEvents](/Cxx/Interaction/KeypressEvents)| vtkInteractorStyleTrackballCamera |Handle keypress events.
[KeypressObserver](/Cxx/Interaction/KeypressObserver) | vtkCallbackCommand | This uses a callback function rather than a derived interactor class. Handle keypress events (lightweight).
[MouseEvents](/Cxx/Interaction/MouseEvents) | vtkInteractorStyleTrackballCamera | Subclass the interactor style. Handle mouse events.
[MouseEventsObserver](/Cxx/Interaction/MouseEventsObserver) | vtkCallbackCommand | Use an observer. Handle mouse events (light weight).
[MoveAGlyph](/Cxx/Interaction/MoveAGlyph)| vtkGlyph3D | Drag a glyph around.
[MoveAVertexUnstructuredGrid](/Cxx/Interaction/MoveAVertexUnstructuredGrid)| vtkPointPicker | Click and drag a vertex of a vtkUnstructuredGrid.
[ObserverMemberFunction](/Cxx/Interaction/ObserverMemberFunction)|  | Set observers to be class member functions.
[PickableOff](/Cxx/Interaction/PickableOff)| vtkActor |Disallow interaction with a specific actor.
[Picking](/Cxx/Interaction/Picking)| vtkPropPicker | Get the world coordinate of the mouse click (if you clicked an actor)
[PointPicker](/Cxx/Interaction/PointPicker)| vtkPointPicker | Get the coordinates of the closest point in the data set to the mouse click.
[RubberBand2DObserver](/Cxx/Interaction/RubberBand2DObserver)| vtkInteractorStyleRubberBand2D |RubberBand2D Observer.
[RubberBand2D](/Cxx/Interaction/RubberBand2D)| vtkInteractorStyleRubberBand2D |
[RubberBand3D](/Cxx/Interaction/RubberBand3D)| vtkInteractorStyleRubberBand3D |
[RubberBandPick](/Cxx/Interaction/RubberBandPick)| vtkInteractorStyleRubberBandPick |
[RubberBandZoom](/Cxx/Interaction/RubberBandZoom)| vtkInteractorStyleRubberBandZoom |
[SelectAnActor](/Cxx/Interaction/SelectAnActor)| vtkPropPicker |Select an actor.
[SelectAVertex](/Cxx/Interaction/SelectAVertex)| vtkPointPicker | Click and drag a vertex of a vtkPolyData.
[ShiftAndControl](/Cxx/Interaction/ShiftAndControl)| vtkRenderWindowInteractor | Hold/holding down a key. Check if shift or control is being held.
[StyleSwitch](/Cxx/Interaction/StyleSwitch)| vtkInteractorStyleSwitch |Choose between multiple interaction modes.
[TrackballActor](/Cxx/Interaction/TrackballActor)| vtkInteractorStyleTrackballActor |Trackball actor mode.
[TrackballCamera](/Cxx/Interaction/TrackballCamera)| vtkInteractorStyleTrackballCamera |Trackball camera mode.
[UserEvent](/Cxx/Interaction/UserEvent)|  | Simple observer. Create, invoke, and handle a custom event.
[WorldPointPicker](/Cxx/Interaction/WorldPointPicker)| vtkWorldPointPicker |Get world coordinates of mouse click.


## Working with Images

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Actor2D](/Cxx/Images/Actor2D)| vtkActor2D vtkMapper2D |2D actor and mapper.
[BackgroundImage](/Cxx/Images/BackgroundImage)|  vtkImageCanvasSource2D |Display an image as the background of a scene.
[BorderPixelSize](/Cxx/Images/BorderPixelSize)| vtkImageSliceMapper |Set the size of border pixels.
[CannyEdgeDetector](/Cxx/Images/CannyEdgeDetector)| | Perform Canny edge detection on an image.
[Cast](/Cxx/Images/Cast)| vtkImageCast |Cast an image to a different type.
[DotProduct](/Cxx/Images/DotProduct)| vtkImageDotProduct | Compute the pixel-wise dot product of two vector images.
[DrawOnAnImage](/Cxx/Images/DrawOnAnImage)| vtkImageCanvasSource2D |Drawing on an image.
[DrawShapes](/Cxx/Images/DrawShapes)| vtkImageCanvasSource2D |Drawing shapes in an image.
[ExtractComponents](/Cxx/Images/ExtractComponents)| vtkImageExtractComponents |  Extract components of an image. This can be used to get, for example, the red channel of an image.
[FillWindow](/Cxx/Images/FillWindow)| vtkCamera | Fit imageSetup the camera to fill the window with an image.
[ImageAccumulateGreyscale](/Cxx/Images/ImageAccumulateGreyscale)| vtkImageAccumulate vtkBarChartActor | Display a grey scale histogram.
[ImageCheckerboard](/Cxx/Images/ImageCheckerboard)| vtkImageCheckerboard | Visually Compare Two Images.
[ImageCityBlockDistance](/Cxx/Images/ImageCityBlockDistance)| vtkImageCityBlockDistance | Compute the Manhattan distance from every point to every black point in a binary image.
[ImageDilateErode3D](/Cxx/Images/ImageDilateErode3D)| vtkImageDilateErode3D | Dilate or erode an image.
[ImageExport](/Cxx/Images/ImageExport) | vtkImageExport | Export an image to a C array.
[ImageGridSource](/Cxx/Images/ImageGridSource)| vtkImageGridSource |Create a image of a grid.
[ImageHybridMedian2D](/Cxx/Images/ImageHybridMedian2D)| vtkImageHybridMedian2D | Median filter an image.
[ImageHistogram](/Cxx/Images/ImageHistogram)| vtkImageHistogram | Compute the histogram of an image.
[ImageIdealHighPass](/Cxx/Images/ImageIdealHighPass)| vtkImageIdealHighPass |High pass filter an image.
[ImageImport](/Cxx/Images/ImageImport) | vtkImageImport | Import an image from a C array.
[ImageIslandRemoval2D](/Cxx/Images/ImageIslandRemoval2D)| vtkImageIslandRemoval2D | Remove small patches from an image.
[ImageMagnify](/Cxx/Images/ImageMagnify)| vtkImageMagnify | Supersample and stretch an image.
[ImageMandelbrotSource](/Cxx/Images/ImageMandelbrotSource)| vtkImageMandelbrotSource |Create a Mandelbrot image.
[ImageMask](/Cxx/Images/ImageMask)| vtkImageMask |Mask a region of an image.
[ImageMathematics](/Cxx/Images/ImageMathematics)| vtkImageMathematics |Perform mathematical operations on an image.
[ImageMedian3D](/Cxx/Images/ImageMedian3D)| vtkImageMedian3D | Median filter a 3d or 2d image.
[ImageMirrorPad](/Cxx/Images/ImageMirrorPad)| vtkImageMirrorPad | Pad the edges of an extended image by mirror existing pixels.
[ImageNonMaximumSuppression](/Cxx/Images/ImageNonMaximumSuppression)| vtkImageNonMaximumSuppression |Find peaks in an image using non maximum suppression.
[ImageOpenClose3D](/Cxx/Images/ImageOpenClose3D)| vtkImageOpenClose3D | Open or close (morphologically) an image.
[ImageRFFT](/Cxx/Images/ImageRFFT)| vtkImageRFFT | Inverse FFT.
[ImageRange3D](/Cxx/Images/ImageRange3D)| vtkImageRange3D | Replace every pixel with the range of its neighbors according to a kernel.
[ImageRotate](/Cxx/Images/ImageRotate)| vtkImageSlice vtkImageResliceMapper | Rotate a 2D image. This is even more powerful than vtkImageSliceMapper. It can also do oblique slices.
[ImageSeparableConvolution](/Cxx/Images/ImageSeparableConvolution)| vtkImageSeparableConvolution | Convolve a separable kernel with an image.
[ImageShiftScale](/Cxx/Images/ImageShiftScale)| vtkImageShiftScale | Shift and scale an image.
[ImageSinusoidSource](/Cxx/Images/ImageSinusoidSource)| vtkImageSinusoidSource |Create a sinusoidal image.
[ImageSliceMapper](/Cxx/Images/ImageSliceMapper)| vtkImageSlice vtkImageSliceMapper | Visualize and interact with an image. This is the new way to do this. It is much more powerful.
[ImageSlice](/Cxx/Images/ImageSlice)| vtkImageSlice vtkImageResliceMapper | Visualize and interact with an image. This is even more powerful than vtkImageSliceMapper. It can also do oblique slices.
[ImageStack](/Cxx/Images/ImageStack)| vtkImageStack |Display layers of images.
[ImageStencil](/Cxx/Images/ImageStencil)| vtkImageStencil vtkImageToImageStencil | Copy one image into another image.
[ImageText](/Cxx/Images/ImageText)| vtkFreeTypeUtilities vtkImageBlend | Draw text in an image.
[ImageThreshold](/Cxx/Images/ImageThreshold)| vtkImageThreshold |Threshold an image.
[ImageToPolyDataFilter](/Cxx/Images/ImageToPolyDataFilter)| vtkImageToPolyDataFilter vtkImageQuantizeRGBToIndex | Convert a vtkImageData to a vtkPolyData.
[ImageToStructuredPoints](/Cxx/Images/ImageToStructuredPoints)| vtkImageToStructuredPoints | Convert a vtkImageData to a vtkStructuredPoints.
[InteractWithImage](/Cxx/Images/InteractWithImage)| vtkImageActor vtkInteractorStyleImage | Visualize and interact with an image.
[Interpolation](/Cxx/Images/Interpolation)| vtkImageSlice vtkImageProperty | Set the interpolation type for the display of an image. If pixels look blurry instead of sharp when zoomed in, change this.
[MarkKeypoints](/Cxx/Images/MarkKeypoints)| vtkVectorText vtkFollower |Mark keypoints in an image.
[NegativeIndices](/Cxx/Images/NegativeIndices)| vtkImageData | A very powerful feature of vtkImageData is that you can use negative indices.
[PickPixel2](/Cxx/Images/PickPixel2)| vtkPropPicker |Picking a pixel 2 - modified version for exact pixel values.
[PickPixel](/Cxx/Images/PickPixel)| vtkPropPicker |Picking a pixel.
[RTAnalyticSource](/Cxx/Images/RTAnalyticSource)| vtkRTAnalyticSource | An image source that can be used for regression testing
[StaticImage](/Cxx/Images/StaticImage)|  vvtkImageViewer2 | This will display the image, but not allow you to interact with it.
[Transparency](/Cxx/Images/Transparency)| vtkImageMapToColors vtkLookupTable | Make part of an image transparent.


## Image Processing

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Colored2DImageFusion](/Cxx/Images/Colored2DImageFusion)| vtkImageMapToColors |Blending 2D images with different color maps.
[CenterAnImage](/Cxx/Images/CenterAnImage)| vtkImageChangeInformation |Center an image.
[CombineImages](/Cxx/Images/CombineImages)| vtkImageBlend |Combine two images.
[CombiningRGBChannels](/Cxx/Images/CombiningRGBChannels)| vtkImageAppendComponents |Combine layers into an RGB image.
[ImageMagnitude](/Cxx/Images/ImageMagnitude)| vtkImageMagnitude | grayscaleConvert RGB image to grey scale.
[Flip](/Cxx/Images/Flip)| vtkImageFlip | Flip an image.
[Gradient](/Cxx/Images/Gradient)| vtkImageGradient | Compute the gradient vector at every pixel.
[ImageAccumulate](/Cxx/Images/ImageAccumulate)| vtkImageAccumulate | Histogram
[ImageAnisotropicDiffusion2D](/Cxx/Images/ImageAnisotropicDiffusion2D)| vtkImageAnisotropicDiffusion2D |Anisotropic diffusion (2D).
[ImageContinuousDilate3D](/Cxx/Images/ImageContinuousDilate3D)| vtkImageContinuousDilate3D |Dilate an image.
[ImageContinuousErode3D](/Cxx/Images/ImageContinuousErode3D)| vtkImageContinuousErode3D |Erode an image.
[ImageConvolve](/Cxx/Images/ImageConvolve)| vtkImageConvolve |Convolve an image with a kernel.
[ImageCorrelation](/Cxx/Images/ImageCorrelation)| vtkImageCorrelation |Correlate two images.
[ImageDifference](/Cxx/Images/ImageDifference)| vtkImageDifference |Compute the difference image of two images.
[ImageDivergence](/Cxx/Images/ImageDivergence)| vtkImageDivergence |Divergence of a vector field.
[ImageEllipsoidSource](/Cxx/Images/ImageEllipsoidSource)| vtkImageEllipsoidSource |Create an image of an ellipsoid.
[ImageFFT](/Cxx/Images/ImageFFT)| vtkImageFFT |Compute the FFT of an image.
[ImageGaussianSmooth](/Cxx/Images/ImageGaussianSmooth)| vtkImageGaussianSmooth |Smooth an image.
[ImageGradientMagnitude](/Cxx/Images/ImageGradientMagnitude)| vtkImageGradientMagnitude |Compute the magnitude of the gradient at each pixel of an image.
[ImageLaplacian](/Cxx/Images/ImageLaplacian)| vtkImageLaplacian |Compute the Laplacian of an image.
[ImageLuminance](/Cxx/Images/ImageLuminance)| vtkImageLuminance |Convert RGB image to greyscale (luminance).
[ImageMapToColors](/Cxx/Images/ImageMapToColors)| vtkImageMapToColors | Use a lookup table to map scalar (gray scale) values to colorsConvert grey scale image to RGB.
[ImageNoiseSource](/Cxx/Images/ImageNoiseSource)| vtkImageNoiseSource |Create an image of noise.
[ImagePermute](/Cxx/Images/ImagePermute)| vtkImagePermute |Switch axes of an image.
[ImageShrink3D](/Cxx/Images/ImageShrink3D)| vtkImageShrink3D |Resample an image.
[ImageSobel2D](/Cxx/Images/ImageSobel2D)| vtkImageSobel2D |Sobel edge detection 2D.
[ImageValueRange](/Cxx/Images/ImageValueRange)| vtkImageData | Get the range of image pixel values (min/max).
[ImageVariance3D](/Cxx/Images/ImageVariance3D)| vtkImageVariance3D | Construct a new image consisting of the variance of the input image at each pixel.
[RGBToHSI](/Cxx/Images/RGBToHSI)| vtkImageRGBToHSI |Convert RGB to HSI.
[RGBToHSV](/Cxx/Images/RGBToHSV)| vtkImageRGBToHSV |Convert RGB to HSV.
[RGBToYIQ](/Cxx/Images/RGBToYIQ)| vtkImageRGBToYIQ |Convert RGB to YIQ.
[RescaleAnImage](/Cxx/ImageProcessing/RescaleAnImage) | vtkImageShiftScale | Rescale an image
[ResizeImage](/Cxx/Images/ResizeImage)| vtkImageResize vtkImageSincInterpolator| Resize an image using a sinc interpolator.
[ResizeImageDemo](/Cxx/Images/ResizeImageDemo)| vtkImageResize vtkImageSincInterpolator| Demonstrate allsinc interpolators to resize an image.

## Widgets

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[PolygonalSurfacePointPlacer](/Cxx/PolyData/PolygonalSurfacePointPlacer)| vtkPolygonalSurfacePointPlacer | Used in conjunction with vtkContourWidget to draw curves on a surface.
[AffineWidget](/Cxx/Widgets/AffineWidget)| vtkAffineWidget | Apply an affine transformation interactively.
[AngleWidget2D](/Cxx/Widgets/AngleWidget2D)| vtkAngleWidget vtkAngleRepresentation2D | vtkAngleWidget + vtkAngleRepresentation2D.
[AngleWidget](/Cxx/Widgets/AngleWidget)| vtkAngleWidget |
[BalloonWidget](/Cxx/Widgets/BalloonWidget)| vtkBalloonWidget |
[BiDimensionalWidget](/Cxx/Widgets/BiDimensionalWidget) |  vtkBiDimensionalWidget |  When would you use this?
[BorderWidget](/Cxx/Widgets/BorderWidget)| vtkBorderWidget | 2D selection, 2D box.
[BoxWidget2](/Cxx/Widgets/BoxWidget2)| vtkBoxWidget2 |
[BoxWidget](/Cxx/Widgets/BoxWidget)| vtkBoxWidget |
[CaptionWidget](/Cxx/Widgets/CaptionWidget)| vtkCaptionWidget |
[CheckerboardWidget](/Cxx/Widgets/CheckerboardWidget)| vtkCheckerboardWidget vtkCheckerboardRepresentation | Compare two images using a checkerboard.
[ContourWidget](/Cxx/Widgets/ContourWidget) | vtkContourWidget | Create a contour from a set of points and dynamically change the contour using the points as control points.
[Cursor2D](/Cxx/Visualization/Cursor2D)| vtkCursor2D |
[DistanceWidget](/Cxx/Widgets/DistanceWidget) | vtkDistanceWidget |
[HoverWidget](/Cxx/Widgets/HoverWidget)| vtkHoverWidget | How to detect a hover? 
[ImagePlaneWidget](/Cxx/Widgets/ImagePlaneWidget)| vtkImagePlaneWidget |
[ImageTracerWidgetInsideContour](/Cxx/Widgets/ImageTracerWidgetInsideContour)| vtkImageTracerWidget | Highlight pixels inside a non-regular region scribbled on an image.
[ImageTracerWidgetNonPlanar](/Cxx/Widgets/ImageTracerWidgetNonPlanar)| vtkImageTracerWidget |Draw on a non-planar surface.
[ImageTracerWidget](/Cxx/Widgets/ImageTracerWidget)| vtkImageTracerWidget | Scribble on an image.
[ImplicitPlaneWidget2](/Cxx/Widgets/ImplicitPlaneWidget2)| vtkImplicitPlaneWidget2 | Clip polydata with an implicit plane.
[LineWidget2](/Cxx/Widgets/LineWidget2)| vtkLineWidget2 |
[LogoWidget](/Cxx/Widgets/LogoWidget)| vtkLogoWidget |Logo widget.
[OrientationMarkerWidget](/Cxx/Widgets/OrientationMarkerWidget)| vtkOrientationMarkerWidget | Display a polydata as an orientation icon.
[PlaneWidget](/Cxx/Widgets/PlaneWidget) | vtkPlaneWidget | Interact with a plane.
[RectilinearWipeWidget](/Cxx/Widgets/RectilinearWipeWidget)| vtkImageRectilinearWipe vtkRectilinearWipeWidget vtkRectilinearWipeRepresentation | Compare two images.
[SeedWidgetImage](/Cxx/Widgets/SeedWidgetImage)| vtkImageViewer2 vtkSeedWidget | How to start the interaction? 
[SeedWidget](/Cxx/Widgets/SeedWidget)| vtkSeedWidget |Seed widget.
[Slider2D](/Cxx/Widgets/Slider2D)| vtkSliderWidget vtkSliderRepresentation2D|2D Slider.
[Slider](/Cxx/Widgets/Slider)| vtkSliderWidget vtkSliderRepresentation3D |3D Slider.
[SphereWidget2](/Cxx/Widgets/SphereWidget2)| vtkSphereWidget2 |
[SphereWidgetEvents](/Cxx/Widgets/SphereWidgetEvents)| vtkSphereWidget |Sphere widget events.
[SphereWidget](/Cxx/Widgets/SphereWidget)| vtkSphereWidget |Sphere widget.
[SplineWidget](/Cxx/Widgets/SplineWidget)| vtkSplineWidget |
[TextWidget](/Cxx/Widgets/TextWidget)| vtkSeedWidget || vtkTextWidget |Draw movable text.
[TexturedButtonWidget](/Cxx/Widgets/TexturedButtonWidget) | vtkButtonWidget vtkTexturedButtonRepresentation2D |Create a textured 2D button.

## Plotting

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[BarChart](/Cxx/Plotting/BarChart)| vtkChartXY |Bar chart.
[BoxChart](/Cxx/Plotting/BoxChart)| vtkChartBox |Box plot.
[Diagram](/Cxx/Plotting/Diagram)| |
[LinePlot](/Cxx/Plotting/LinePlot)| vtkChartXY |Line plot.
[HistogramBarChart](/Cxx/Plotting/HistogramBarChart)| vtkBarChartActor | Histogram using bar chart.
[ParallelCoordinates](/Cxx/Plotting/ParallelCoordinates)| vtkChartParallelCoordinates |Parallel coordinates.
[PieChart](/Cxx/Plotting/PieChart)| vtkChartPie vtkPlotPie | Pie chart.
[PieChartActor](/Cxx/Plotting/PieChart)| vtkPieChartActor | Pie chart.
[ScatterPlot](/Cxx/Plotting/ScatterPlot)| vtkPlotPoints |Scatter plot.
[SpiderPlot](/Cxx/Plotting/SpiderPlot)| vtkSpiderPlotActor |Spider plot.
[StackedBar](/Cxx/Plotting/StackedBar)| vtkPlotBar |Stacked bar.
[StackedPlot](/Cxx/Plotting/StackedPlot)| vtkPlotStacked |Stacked plot.


## Animation

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[AnimateActors](/Cxx/Animation/AnimateActors) | vtkAnimationScene vtkAnimationCue|Animate actors.
[Animation](/Cxx/Utilities/Animation) | vtkRenderWindowInteractor | Move a sphere across a scene.
[AnimationScene](/Cxx/Utilities/AnimationScene) | vtkAnimationScene vtkAnimationCue | Animation (the right way). Zoom in on a sphere.
[DataAnimation](/Cxx/Utilities/DataAnimation) | vtkCallbackCommand vtkProgrammableFilter | Data Animation. Update points in a dataset every specified interval.
[DataAnimationSubclass](/Cxx/Utilities/DataAnimationSubclass) | vtkCommand vtkProgrammableFilter| Update points in a dataset every specified interval (using a vtkCommand subclass instead of a callback function.

## Geographic Visualization (Geovis)

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[CompassWidget](/Cxx/Geovis/CompassWidget)  | vtkCompassWidget | Compass Widget.
[EarthSource](/Cxx/Geovis/EarthSource) | vtkEarthSource | Create the Earth.
[GeoAssignCoordinates](/Cxx/Geovis/GeoAssignCoordinates) | vtkGeoAssignCoordinates | Convert lat/long coordinates to world coordinates.

## Information Visualization (Infovis)

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ParallelCoordinatesView](/Cxx/InfoVis/ParallelCoordinatesView) | vtkParallelCoordinatesView | Parallel coordinates.
[TreeMapView](/Cxx/InfoVis/TreeMapView) | vtkTreeMapView | Tree map.


## Qt
Click [here](http://www.vtk.org/Wiki/VTK/Tutorials/QtSetup) for a tutorial on how to setup Qt.


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[BorderWidgetQt](/Cxx/Qt/BorderWidgetQt) | vtkBorderWidget QApplication |
[QtBarChart](/Cxx/Qt/QtBarChart) | vtkQtBarChart |
[ShowEvent](/Cxx/Qt/ShowEvent) |  | Use QMainWindow::showEvent event to do things that you might want to do in the constructor 
[EventQtSlotConnect](/Cxx/Qt/EventQtSlotConnect) | vtkEventQtSlotConnect|  Connect a VTK event to a Qt slot.
[ImageDataToQImage](/Cxx/Qt/ImageDataToQImage) | |  Convert a vtkImageData to a QImage.
[QImageToImageSource](/Cxx/Qt/QImageToImageSource) | vtkQImageToImageSource |  Convert a QImage to a vtkImageData.
[RenderWindowNoUiFile](/Cxx/Qt/RenderWindowNoUiFile) | QVTKOpenGLWidget| This is a very basic example that shows how to create a Qt window. Typically, one would want to design a form in the QtDesigner (this is shown in [[/Qt/RenderWindowUi|RenderWindowUi]]).
[RenderWindowUIMultipleInheritance](/Cxx/Qt/RenderWindowUIMultipleInheritance) | QMainWindow | Using a QVTKOpenGLWidget with the Qt Multiple Inheritance model.
[RenderWindowUISingleInheritance](/Cxx/Qt/RenderWindowUISingleInheritance) | QMainWindow | Using a QVTKOpenGLWidget with the Qt Single Inheritance model.
[ShareCameraQt](/Cxx/Qt/ShareCameraQt) | |  Share the camera between QVTKOpenGLWidgets.
[SideBySideRenderWindowsQt](/Cxx/Qt/SideBySideRenderWindowsQt) | QApplication | Side by side render windows.


## Matlab
You must turn on VTK_USE_MATLAB_MEX to use these.

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[MatlabEngineFilter](/Cxx/Matlab/MatlabEngineFilter)  | vtkMatlabEngineFilter |


## Databases
### SQL
If you have any trouble or errors with the following examples, please troubleshoot using [these instructions](http://www.vtk.org/Wiki/Tutorials/SQLSetup).


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ConnectAndRead](/Cxx/Databases/SQL/MySQL/ConnectAndRead) | vtkMySQLDatabase vtkSQLQuery |Connect to and read a MySQL database.
[CreateDatabase](/Cxx/Databases/SQL/MySQL/CreateDatabase) | vtkMySQLDatabase | Create a MySQL database.
[WriteToDatabase](/Cxx/Databases/SQL/MySQL/WriteToDatabase) | vtkSQLQuery vtkMySQLDatabase |  Write to a MySQL database.


## RenderMan
RenderMan is a high quality rendering system created by [Pixar](https://renderman.pixar.com/view/renderman). VTK can export RenderMan RIB files for rendering by [prman](http://renderman.pixar.com/view/renderman-prman-the-rispec-and-renderman-studio). In the spring of 2015, Pixar released a [non-commercial version](http://renderman.pixar.com/view/PR-NCR) of its RenderMan products.

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[PolyDataRIB](/Cxx/RenderMan/PolyDataRIB) | vtkRIBExporter|Apply a RenderMan Shader to a PolyData.

## Remote Modules
Remote modules are user contributed code that is not distributed with VTK. A description of a remote module and the location of its repository is listed in the VTK/Remote directory with the extension .remote.cmake. Once enabled, a remote module is treated like any other VTK module. Each of the remote module examples describes how to enable the example. More information about remote modules is [here](http://www.vtk.org/Wiki/VTK/Remote_Modules).

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[FrenetSerretFrame](/Cxx/Remote/FrenetSerretFrame) | vtkFrenetSerretFrame | Compute tangent and normal vectors to a polyline.
[FrenetSerretFrameDemo](/Cxx/Remote/FrenetSerretFrameDemo) | vtkFrenetSerretFrame | Uses vtkSplineWidget to interact with a spline. Shows how to control a pipeline inside a callback.
