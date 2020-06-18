# Python Examples

Please see [this page](https://www.vtk.org/Wiki/VTK/PythonDevelopment) to learn how to setup your environment to use VTK in Python.

It would be appreciated if there are any Python VTK experts who could convert any of the [c++ examples](/Cxx) to Python!

!!! info
    [This table](/Coverage/PythonVTKClassesUsed.md) shows the VTK classes covered by the examples.

!!! info
    [This table](/Coverage/PythonVTKClassesNotUsed.md) shows VTK classes that do not have an example. Please add examples in your area of expertise!

## Hello World

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[A hello world example](/Python/GeometricObjects/CylinderExample) | vtkPolyDataMapper vtkActor vtkRenderer vtkRenderWindow vtkRenderWindowInteractor | Cylinder example from the VTK Textbook and source code. A hello world example.

## Simple Operations

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[DistanceBetweenPoints](/Python/SimpleOperations/DistanceBetweenPoints) | vtkMath::Distance2BetweenPoints |

## Input and Output

### Graph Formats

### 3D File Formats

#### Standard Formats

##### Input

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ReadExodusData](/Python/IO/ReadExodusData) | vtkExodusIIReader | A simple script for reading and viewing ExodusII data interactively.
[ReadSLC](/Python/IO/ReadSLC) | vtkSLCReader | Read an SLC file.
[ReadSTL](/Python/IO/ReadSTL) | vtkSTLReader | Read an STL file.
[ReadVTP](/Python/IO/ReadVTP) | vtkXMLPolyDataReader | Read a VTK XML PolyData file.
[ReadUnstructuredGrid](/Python/IO/ReadUnstructuredGrid) | vtkUnstructuredGridReader | Using vtkUnstructuredGridReader to read a (legacy) *.vtk file

###### Importers

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[3DSImporter](/Python/IO/3DSImporter) | vtk3DSImporter | Import a 3D Studio scene that includes multiple actors.

##### Output

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[WritePLY](/Python/IO/WritePLY) | vtkPLYWriter |
[WriteSTL](/Python/IO/WriteSTL) | vtkSTLWriter |

#### VTK Formats

##### Input

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ReadImageData](/Python/IO/ReadImageData) | vtkXMLImageDataReader | Read an image data (.vti) file
[ReadPolyData](/Python/IO/ReadPolyData) | vtkXMLPolyDataReader | Read a polygonal data (.vtp) file

##### Output

#### Legacy VTK Formats

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ReadLegacyUnstructuredGrid](/Python/IO/ReadLegacyUnstructuredGrid) | vtkUnstructuredGridReader | Read an unstructured grid that contains 11 linear cells.
[WriteLegacyLinearCells](/Python/IO/WriteLegacyLinearCells) | vtkUnstructuredGridWriter | Write each linear cell into a legacy UnstructuredGrid file.
[WriteXMLLinearCells](/Python/IO/WriteXMLLinearCells) | vtkXMLDataSetWriter | Write each linear cell into an XML UnstructuredGrid file (.vtu).

### Image Format

#### Input

#### Output

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ImageWriter](/Python/IO/ImageWriter) | vtkBMPWriter vtkJPEGWriter vtkPNMWriter vtkPostScriptWriter vtkTIFFWriter vtkPNGWriter vtkWindowToImageFilter | Write an imagefile based on the file extension.

## Geometric Objects

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Axes](/Python/GeometricObjects/Axes) | vtkAxesActor |
[ColoredLines](/Python/GeometricObjects/ColoredLines) | vtkCellData vtkLine |
[Circle](/Python/GeometricObjects/Circle) | vtkRegularPolygonSource | A disk is shown however this can be modified to show a circle.
[Dodecahedron](/Python/GeometricObjects/Dodecahedron) | vtkPolyhedron | Create a dodecahedron using vtkPolyhedron.
[EllipticalCylinder](/Python/GeometricObjects/EllipticalCylinder) | vtkLinearExtrusionFilter | Create an elliptical cylinder using extrusion.
[EllipticalCylinderDemo](/Python/GeometricObjects/EllipticalCylinderDemo) | vtkLinearExtrusionFilter | Show the base and extrusion vector.
[GeometricObjectsDemo](/Python/GeometricObjects/GeometricObjectsDemo) |  |
[Planes](/Python/GeometricObjects/Planes) | vtkPlanes vtkHull | We create a convex hull of the planes for display purposes.
[PlanesIntersection](/Python/GeometricObjects/PlanesIntersection) | vtkPlanesIntersection |
[PolygonIntersection](/Python/GeometricObjects/PolygonIntersection) | vtkPolygon | IntersectWithLine()
[SourceObjectsDemo](/Python/GeometricObjects/SourceObjectsDemo) | vtkSphereSource vtkConeSource vtkCylinderSource vtkCubeSource vtkPlaneSource vtkTextSource vtkPointSource vtkDiskSource vtkLineSource | Examples of source objects that procedurally generate polygonal models.  These nine images represent just some of the capability of VTK. From upper left in reading order: sphere, cone, cylinder, cube, plane, text, random point cloud, disk (with or without hole), and line source. Other polygonal source objects are available; check subclasses of vtkPolyDataAlgorithm.

### Cells

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Cell3DDemonstration](/Python/GeometricObjects/Cell3DDemonstration) | vtkHexagonalPrism vtkHexahedron vtkPentagonalPrism  vtkPolyhedron vtkPyramid vtkTetra vtkVoxel vtkWedge vtkUnstructuredGrid | Sample objects are generated from the classes derived from vtkCell3D and displayed.
[CellTypeSource](/Python/GeometricObjects/CellTypeSource) | vtkCellTypeSource vtkTessellatorFilter | Generate tessellated cells.
[ConvexPointSet](/Python/GeometricObjects/ConvexPointSet) | vtkConvexPointSet | Generate a ConvexPointSetCell.
[Hexahedron](/Python/GeometricObjects/Hexahedron) | vtkHexahedron |
[LinearCellDemo](/Python/GeometricObjects/LinearCellDemo) | vtkCell vtkCell3D | Linear cell types in VTK.
[LongLine](/Python/GeometricObjects/LongLine) | vtkLine | Manually create a polyline.
[Point](/Python/GeometricObjects/Point) | vtkPoints |
[PolyLine](/Python/GeometricObjects/PolyLine) | vtkPolyLine |
[Polygon](/Python/GeometricObjects/Polygon) | vtkPolygon |
[Polyhedron](/Python/GeometricObjects/Polyhedron) | vtkPolyhedron | Create an unstructured grid representation of a polyhedron (cube) and write it out to a file.
[Pyramid](/Python/GeometricObjects/Pyramid) | vtkPyramid |
[Quad](/Python/GeometricObjects/Quad) | vtkQuad |
[Tetrahedron](/Python/GeometricObjects/Tetrahedron) | vtkTetra |
[Triangle](/Python/GeometricObjects/Triangle) | vtkTriangle |
[TriangleStrip](/Python/GeometricObjects/TriangleStrip) | vtkTriangleStrip |
[Vertex](/Python/GeometricObjects/Vertex) | vtkVertex |

### Sources

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Arrow](/Python/GeometricObjects/Arrow) | vtkArrowSource |
[Cone](/Python/GeometricObjects/Cone) | vtkConeSource |
[Cube](/Python/GeometricObjects/Cube) | vtkPolyData | Manually build a polygonal cube.
[Cube1](/Python/GeometricObjects/Cube1) | vtkCubeSource | A nice simple example that demonstrates the operation of the VTK pipeline.
[Cylinder](/Python/GeometricObjects/Cylinder) | vtkCylinderSource |
[Disk](/Python/GeometricObjects/Disk) | vtkDiskSource | A circle with a hole in it.
[Frustum](/Python/GeometricObjects/Frustum) | vtkFrustumSource |
[Line](/Python/GeometricObjects/Line) | vtkLineSource |
[OrientedArrow](/Python/GeometricObjects/OrientedArrow) | vtkArrowSource | Orient an arrow along an arbitrary vector.
[OrientedCylinder](/Python/GeometricObjects/OrientedCylinder) | vtkCylinderSource | Orient a cylinder along an arbitrary vector.
[Plane](/Python/GeometricObjects/Plane) | vtkPlaneSource |
[PlatonicSolids](/Python/GeometricObjects/PlatonicSolids) | vtkPlatonicSolidSource | All five platonic solids are displayed.
[PolyLine1](/Python/GeometricObjects/PolyLine1) | vtkPolyLine | This example demonstrates how to create a polygon through several ordered points.
[RegularPolygonSource](/Python/GeometricObjects/RegularPolygonSource) | vtkRegularPolygonSource |
[ShrinkCube](/Python/GeometricObjects/ShrinkCube) | vtkCubeSource vtkShrinkFilter | Applying shrink filter to an object.
[Sphere](/Python/GeometricObjects/Sphere) | vtkSphereSource |
[TessellatedBoxSource](/Python/GeometricObjects/TessellatedBoxSource) | vtkTessellatedBoxSource | Generate a box with tessellated sides.
[TextActor](/Python/GeometricObjects/TextActor) | vtkTextActor | 2D "HUD-type" text

### Non Linear

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[IsoparametricCellsDemo](/Python/GeometricObjects/IsoparametricCellsDemo) | vtkNonLinearCell | Nonlinear isoparametric cell types in VTK.
[QuadraticHexahedron](/Python/GeometricObjects/QuadraticHexahedron) | vtkQuadraticHexahedron vtkTessellatorFilter | Create and tessellate a nonlinear cell.
[QuadraticHexahedronDemo](/Python/GeometricObjects/QuadraticHexahedronDemo) | vtkQuadraticHexahedron vtkTessellatorFilter | Interactively adjust chord error.
[QuadraticTetra](/Python/GeometricObjects/QuadraticTetra) | vtkQuadraticTetra vtkTessellatorFilter | Create and tessellate a nonlinear cell.
[QuadraticTetraDemo](/Python/GeometricObjects/QuadraticTetraDemo) | vtkQuadraticTetra vtkTessellatorFilter | Interactively adjust chord error.

### Parametric Objects

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ParametricKuenDemo](/Python/GeometricObjects/ParametricKuenDemo) | vtkParametricKuen | Interactively change the parameters for a Kuen Surface.
[ParametricObjectsDemo](/Python/GeometricObjects/ParametricObjectsDemo) |  | Demonstrates the Parametric classes added by Andrew Maclean and additional classes added by Tim Meehan. The parametric spline is also included. Options are provided to display single objects, add backface, add normals and print out an image.
[ParametricSuperEllipsoidDemo](/Python/GeometricObjects/ParametricSuperEllipsoidDemo) | vtkParametricSuperEllipsoid | Interactively change the parameters for a SuperEllipsoid Surface.
[ParametricSuperToroidDemo](/Python/GeometricObjects/ParametricSuperToroidDemo) | vtkParametricSuperToroid | Interactively change the parameters for a SuperToroid Surface.

## Implicit Functions and Iso-surfaces

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Boolean](/Python/ImplicitFunctions/Boolean) | vtkImplicitBoolean | Demonstrate booleans of two different implicit functions
[CutWithScalars](/Python/VisualizationAlgorithms/CutWithScalars) | vtkContourFilter | Cut a surface with scalars.
[ExtractData](/Python/VisualizationAlgorithms/ExtractData) | vtkSampleFunction | Implicit functions used to select data: Two ellipsoids are combined using the union operation used to select voxels from a volume. Voxels are shrunk 50 percent.
[Hello](/Python/VisualizationAlgorithms/Hello) | vtkImplicitModeller | Implicit modelling used to thicken a stroked font.
[IceCream](/Python/VisualizationAlgorithms/IceCream) | vtkImplicitBoolean vtkSampleFunction | How to use boolean combinations of implicit functions to create a model of an ice cream cone.
[ImplicitDataSet](/Python/ImplicitFunctions/ImplicitDataSet) | vtkImplicitDataSet | A cube is used to define an implicit function (through vtkImplicitDataSet) which is then used to clip a sphere.
[ImplicitSphere](/Python/ImplicitFunctions/ImplicitSphere) | vtkSphere | An implicit representation of a sphere.
[Lorenz](/Python/Visualization/Lorenz) | vtkContourFilter | Visualizing a Lorenz strange attractor by integrating the Lorenz equations in a volume.
[MarchingCases](/Python/VisualizationAlgorithms/MarchingCases) | vtkMarchingCubes | Explore the Marching Cubes cases.
[MarchingCasesA](/Python/VisualizationAlgorithms/MarchingCasesA) | vtkMarchingCubes | The 256 possible cases have been reduced to 15 cases using symmetry.
[MarchingCasesB](/Python/VisualizationAlgorithms/MarchingCasesB) | vtkMarchingCubes | Marching cubes complementary cases. Cases 3c, 6c, 7c, 10c, 12c and 13c are displayed.
[MarchingCasesC](/Python/VisualizationAlgorithms/MarchingCasesC) | vtkMarchingCubes | Marching cubes, case 3 is rotated 90 degrees about the y-axis with no label.
[MarchingCasesD](/Python/VisualizationAlgorithms/MarchingCasesD) | vtkMarchingCubes | Marching cubes, case 7 is rotated 180 degrees about the y-axis with no label.
[Quadric](/Python/ImplicitFunctions/Quadric) | vtkQuadric | Create an ellipsoid using an implicit quadric
[Sphere](/Python/ImplicitFunctions/Sphere) | vtkSphere | Demonstrate sampling of a sphere implicit function
[SampleFunction](/Python/ImplicitFunctions/SampleFunction) | vtkSampleFunction | Sample and visualize an implicit function.

## Working with 3D Data

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[AlignTwoPolyDatas](/Python/PolyData/AlignTwoPolyDatas) | vtkIterativeClosestPointTransform vtkLandmarkTransform vtkHausdorffDistancePointSetFilter | Align two vtkPolyData's.
[AppendFilter](/Python/Filtering/AppendFilter) | vtkAppendFilter | Append different types of data,
[BooleanOperationPolyDataFilter](/Python/PolyData/BooleanOperationPolyDataFilter) | vtkBooleanOperationPolyDataFilter | This example performs a boolean operation (Intersection, Union, Difference) of two PolyData
[Bottle](/Python/Modelling/Bottle) | vtkRotationalExtrusionFilter | Rotationally symmetric objects.
[CappedSphere](/Python/Modelling/CappedSphere) | vtkRotationalExtrusionFilter | Rotate an arc to create a capped sphere.
[CellsInsideObject](/Python/PolyData/CellsInsideObject) | vtkSelectEnclosedPoints vtkMultiThreshold | Extract cells inside a closed surface.
[ColoredTriangle](/Python/PolyData/ColoredTriangle) | vtkTriangle | Creates a file TriangleColored.vtp.
[CombinePolyData](/Python/Filtering/CombinePolyData) | vtkAppendPolyData | This example combines Polydata objects, and displays the result to the screen.
[ConnectivityFilter](/Python/Filtering/ConnectivityFilter) | vtkConnectivityFilter | Color any dataset type based on connectivity.
[CurvaturesDemo](/Python/PolyData/CurvaturesDemo) | vtkCurvatures  vtkColorTransferFunction | Demonstrates how to get the Gaussian and Mean curvatures of a surface.
[ExtractPolyLinesFromPolyData](/Python/PolyData/ExtractPolyLinesFromPolyData) | vtkPolyData | Extract polylines from polydata. 
[ExtractSelection](/Python/PolyData/ExtractSelection) | vtkExtractSelection |
[ExtractSelectionCells](/Python/PolyData/ExtractSelectionCells) | vtkExtractSelection | Extract cell, select cell.
[FilledPolygon](/Python/PolyData/FilledPolygon) | vtkCutter |
[Finance](/Python/Modelling/Finance) | vtkGaussianSplatter | Visualization of multidimensional financial data. The gray/wireframe surface represents the total data population. The red surface represents data points delinquent on loan payment.
[FinanceFieldData](/Python/Modelling/FinanceFieldData) | vtkGaussianSplatter | Visualization of multidimensional financial data. The yellow surface represents the total data population. The red surface represents data points delinquent on loan payment.
[Glyph2D](/Python/Filtering/Glyph2D) | vtkGlyph2D |
[Glyph3D](/Python/Filtering/Glyph3D) | vtkGlyph3D |
[ImplicitPolyDataDistance](/Python/PolyData/ImplicitPolyDataDistance) | vtkImplicitPolyDataDistance |
[IterateOverLines](/Python/PolyData/IterateOverLines) | vtkCellArray | Iterate through the lines of a PolyData.
[IterativeClosestPoints](/Python/Filtering/IterativeClosestPoints) | vtkIterativeClosestPointTransform |
[LineOnMesh](/Python/DataManipulation/LineOnMesh) | vtkCellLocator vtkParametricSpline |
[MeshLabelImageColor](/Python/DataManipulation/MeshLabelImageColor) | vtkDiscreteMarchingCubes |
[Outline](/Python/PolyData/Outline) | vtkOutlineFilter |
[PolyDataContourToImageData](/Python/PolyData/PolyDataContourToImageData) | vtkLinearExtrusionFilter vtkPolyDataToImageStencil |
[PolyDataToImageDataStencil](/Python/PolyData/PolyDataToImageDataStencil) | vtkPolyDataToImageStencil |
[PerlinNoise](/Python/Filtering/PerlinNoise) | vtkPerlinNoise |
[RotationAroundLine](/Python/PolyData/RotationAroundLine) | vtkTransformPolyDataFilter |
[RuledSurfaceFilter](/Python/PolyData/RuledSurfaceFilter) | vtkRuledSurfaceFilter |
[SmoothMeshGrid](/Python/PolyData/SmoothMeshGrid) | vtkLoopSubdivisionFilter vtkButterflySubdivisionFilter |
[SolidColoredTriangle](/Python/PolyData/SolidColoredTriangle) | vtkTriangle | Writes out a file TriangleSolidColor.vtp.
[Spring](/Python/Modelling/Spring) | vtkRotationalExtrusionFilter | Rotation in combination with linear displacement and radius variation.
[TriangleColoredPoints](/Python/PolyData/TriangleColoredPoints) | vtkUnsignedCharArray |
[TriangleCornerVertices](/Python/PolyData/TriangleCornerVertices) | vtkCellArray |
[TriangleCorners](/Python/PolyData/TriangleCorners) | vtkXMLPolyDataWriter |
[TriangulateTerrainMap](/Python/Filtering/TriangulateTerrainMap) | vtkDelaunay2D | Generate heights (z values) on a 10x10 grid (a terrain map) and then triangulate the points to form a surface.
[TransformPolyData](/Python/Filtering/TransformPolyData) | vtkTransformPolyDataFilter | Apply a Transformation to a PolyData.
[VertexGlyphFilter](/Python/Filtering/VertexGlyphFilter) | vtkVertexGlyphFilter | Add a vertex to each point.
[WarpTo](/Python/Filtering/WarpTo) | vtkWarpTo | Deform geometry by warping towards a point.
[WarpVector](/Python/PolyData/WarpVector) | vtkLine vtkDoubleArray vtkPolyData vtkWarpVector | This example warps/deflects a line.
[WriteTriangleToFile](/Python/IO/WriteTriangleToFile) | vtkTriangle |
[TubeFilter](/Python/PolyData/TubeFilter) | vtkTubeFilter | Give lines a thickness (produce a cylinder around lines).

### Data Types
| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[CompositePolyDataMapper](/Python/CompositeData/CompositePolyDataMapper) | vtkCompositePolyDataMapper |
[MultiBlockDataSet](/Python/CompositeData/MultiBlockDataSet) | vtkMultiBlockDataSet | Demonstrates how to make and use VTK's MultiBlock type data
[OverlappingAMR](/Python/CompositeData/OverlappingAMR) | vtkOverlappingAMR | Demonstrates how to create and populate a VTK's Overlapping AMR Grid type Data

### Data Type Conversions

### Point Cloud Operations

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[PointSource](/Python/GeometricObjects/PointSource) | vtkPointSource |

### Working with Meshes

This section includes examples of manipulating meshes.

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[BoundaryEdges](/Python/Meshes/BoundaryEdges) | vtkFeatureEdges | Find the edges that are used by only one face.
[ClosedSurface](/Python/PolyData/ClosedSurface) | vtkFeatureEdges | Check if a surface is closed.
[ColoredElevationMap](/Python/Meshes/ColoredElevationMap) | vtkLookupTable | Color a mesh by height.
[Decimation](/Python/Meshes/Decimation) | vtkDecimatePro | Reduce the number of triangles in a mesh.
[DeformPointSet](/Python/Meshes/DeformPointSet) | vtkDeformPointSet vtkElevationFilter | Use the vtkDeformPointSet filter to deform a vtkSphereSource with arbitrary polydata.
[DelaunayMesh](/Python/Modelling/DelaunayMesh) | vtkDelaunay2D vtkMinimalStandardRandomSequence vtkExtractEdges vtkGlyph3D vtkTubeFilter | Two-dimensional Delaunay triangulation of a random set of points. Points and edges are shown highlighted with sphere glyphs and tubes.
[PointInterpolator](/Python/Meshes/PointInterpolator) | vtkPointInterpolator | Plot a scalar field of points onto a PolyData surface.

#### Clipping

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[CapClip](/Python/Meshes/CapClip) | vtkClipPolyData | Cap a clipped polydata with a polygon.
[ClipDataSetWithPolyData](/Python/Meshes/ClipDataSetWithPolyData) | vtkClipDataSet vtkImplicitPolyDataDistance vtkRectilinearGrid | clip a vtkRectilinearGrid with arbitrary polydata. In this example, use a vtkConeSource to generate polydata to slice the grid, resulting in an unstructured grid.
[SolidClip](/Python/Meshes/SolidClip) | vtkClipPolyData | Create a "solid" clip. The "ghost" of the part clipped away is also shown.

### Working with Structured 3D Data

This section includes vtkImageData vtkStructuredGrid and vtkRectilinearGrid.

"ImageData" is not the traditional "flat, 2D image" you are used to. It is a special VTK data structure in the collection of 3D data structures provided by VTK.

#### vtkImageData

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ImageWeightedSum](/Python/ImageData/ImageWeightedSum) | vtkImageWeightedSum | Add two or more images.

#### Conversions

#### vtkStructuredGrid

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[SGrid](/Python/StructuredGrid/SGrid) | vtkStructuredGrid | Creating a structured grid dataset of a semi-cylinder. Vectors are created whose magnitude is proportional to radius and oriented in tangential direction.

#### vtkStructuredPoints

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Vol](/Python/StructuredPoints/Vol) | vtkStructuredPoints vtkContourFilter | Creating a image data dataset. Scalar data is generated from the equation for a sphere. Volume dimensions are 26 x 26 x 26.

#### vtkRectilinearGrid

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[RGrid](/Python/RectilinearGrid/RGrid) | vtkRectilinearGrid | Creating a rectilinear grid dataset. The coordinates along each axis are defined using an instance of vtkDataArray.
[RectilinearGrid](/Python/RectilinearGrid/RectilinearGrid) | vtkRectilinearGrid | create a rectilinear grid

### Working with Unstructured 3D Data

This section includes vtkUnstructuredGrid.

#### vtkUnstructuredGrid

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ClipUnstructuredGridWithPlane](/Python/UnstructuredGrid/ClipUnstructuredGridWithPlane) | vtkTableBasedClipDataSet vtkUnstructuredGrid | Clip a UGrid with a plane.
[ClipUnstructuredGridWithPlane2](/Python/UnstructuredGrid/ClipUnstructuredGridWithPlane2) | vtkClipDataSet vtkUnstructuredGrid | Clip a UGrid with a plane.
[UGrid](/Python/UnstructuredGrid/UGrid) | vtkUnstructuredGrid | Creation of an unstructured grid.

### Registration

### Medical

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[MedicalDemo1](/Python/Medical/MedicalDemo1) | vtkMarchingCubes | Create a skin surface from volume data
[MedicalDemo2](/Python/Medical/MedicalDemo2) | vtkMarchingCubes | Create a skin and bone surface from volume data
[MedicalDemo3](/Python/Medical/MedicalDemo3) | vtkMarchingCubes | Create skin, bone and slices from volume data
[MedicalDemo4](/Python/Medical/MedicalDemo4) | vtkFixedPointVolumeRayCastMapper | Create a volume rendering

### Surface reconstruction

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[GaussianSplat](/Python/Filtering/GaussianSplat) | vtkGaussianSplatter | Create a surface from Unorganized Points (Gaussian Splat).

## Utilities

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Delaunay2D](/Python/Filtering/Delaunay2D) | vtkDelaunay2D |
[LUTUtilities](/Python/Utilities/LUTUtilities) | vtkLookupTable vtkColorSeries | A utility class for vtkLookupTable allowing you to output the table contents or to compare tables.
[MultipleViewports](/Python/Visualization/MultipleViewports) | vtkRenderer::SetViewport |
[SaveSceneToFieldData](/Python/Utilities/SaveSceneToFieldData) | vtkCamera | Save a vtkCamera's state in a vtkDataSet's vtkFieldData and restore it.
[SaveSceneToFile](/Python/Utilities/SaveSceneToFile) | vtkCamera | Save a vtkCamera's state in a file and restore it.
[Screenshot](/Python/Utilities/Screenshot) | vtkWindowToImageFilter |
[VTKVersion](/Python/Utilities/VTKVersion) | vtkVersion |
[VTKWithNumpy](/Python/Utilities/VTKWithNumpy) | vtkImageImport |
[Variant](/Python/Utilities/Variant) | vtkVariant |

### Arrays

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[GetValues](/Python/Arrays/GetValues) | GetTuple3 |
[RenameArray](/Python/Arrays/RenameArray) | SetName |

### Events

## Math Operations

## Graphs

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ColorEdges](/Python/Graphs/ColorEdges) | vtkGraphLayoutView | Color edges.
[ColorVertexLabels](/Python/Graphs/ColorVertexLabels) | vtkGraphLayoutView vtkRenderedGraphRepresentation | Set the color of vertex labels.
[ColorVerticesLookupTable](/Python/Graphs/ColorVerticesLookupTable) | vtkGraphLayoutView | Color vertices.
[ConstructGraph](/Python/Graphs/ConstructGraph) | vtkMutableUndirectedGraph | Construct a graph.
[ConstructTree](/Python/Graphs/ConstructTree) | vtkTree vtkMutableDirectedGraph | Construct a tree.
[EdgeWeights](/Python/Graphs/EdgeWeights) | vtkMutableDirectedGraph vtkGraphLayoutView |
[GraphToPolyData](/Python/Graphs/GraphToPolyData) | vtkGraphToPolyData | Convert a graph to a PolyData.
[LabelVerticesAndEdges](/Python/Graphs/LabelVerticesAndEdges) | vtkGraphLayoutView | Label vertices and edges.
[NOVCAGraph](/Python/Graphs/NOVCAGraph) | vtkUnstructuredGrid vtkXMLUnstructuredGridWriter |
[RandomGraphSource](/Python/Graphs/RandomGraphSource) | vtkRandomGraphSource | Create a random graph.
[ScaleVertices](/Python/Graphs/ScaleVertices) | vtkGraphLayoutView vtkRenderedGraphRepresentation | Size/scale vertices based on a data array.
[SelectedVerticesAndEdges](/Python/Graphs/SelectedVerticesAndEdges) | vtkAnnotationLink vtkGraphLayoutView |
[SideBySideGraphs](/Python/Graphs/SideBySideGraphs) | vtkGraphLayoutView | Display two graphs side by side.
[VisualizeDirectedGraph](/Python/Graphs/VisualizeDirectedGraph) | vtkGlyphSource2D | Visualize a directed graph.
[VisualizeGraph](/Python/Graphs/VisualizeGraph) | vtkMutableDirectedGraph vtkGraphLayoutView |

### Graph Conversions

## Data Structures

### Timing Demonstrations

### KD-Tree

### Oriented Bounding Box (OBB) Tree

### Octree

### Modified BSP Tree

### HyperTreeGrid

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[HyperTreeGridSource](/Python/HyperTreeGrid/HyperTreeGridSource) | vtkHyperTreeGridSource | Create a vtkHyperTreeGrid.

## VTK Concepts

## Rendering

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[AmbientSpheres](/Python/Rendering/AmbientSpheres) | vtkProperty | Demonstrates the effect of ambient lighting on spheres.
[CameraBlur](/Python/Rendering/CameraBlur) |  | Example of a scene rendered with focal depth.
[ColoredSphere](/Python/Rendering/ColoredSphere) | vtkSphereSource vtkElevationFilter | A simple sphere.
[Cone3](/Python/Rendering/Cone3) | vtkRenderWindow | Four frames of output, based on the VTK example Cone3.py.
[Cone4](/Python/Rendering/Cone4) | vtkRenderWindow | Modifying properties and transformation matrix based on the VTK example Cone4.py.
[DiffuseSpheres](/Python/Rendering/DiffuseSpheres) | vtkProperty | Demonstrates the effect of diffuse lighting on spheres.
[FlatVersusGouraud](/Python/Rendering/FlatVersusGouraud) | vtkProperty::SetInterpolationToFlat vtkProperty::SetInterpolationToGouraud | Flat and Gouraud shading. Different shading methods can dramatically improve the look of an object represented with polygons. On the top, flat shading uses a constant surface normal across each polygon. On the bottom, Gouraud shading interpolates normals from polygon vertices to give a smoother look.
[Mace](/Python/Rendering/Mace) |  | An example of multiple inputs and outputs.
[Model](/Python/Rendering/Model) | vtkRenderer vtkRenderWindow vtkRenderWindowInteractor | Illustrative diagram of graphics objects.
[MotionBlur](/Python/Rendering/MotionBlur) | vtkRenderStepsPass vtkSimpleMotionBlurPass | Example of motion blur.
[PhysicallyBasedRendering](/Python/Rendering/PhysicallyBasedRendering) | vtkSkybox vtkTexture | Demonstrates physically based rendering, image based lighting, texturing and a skybox.
[Rainbow](/Python/Rendering/Rainbow) | vtkLookupTable | Use and manipulation of vtkLookupTables.
[Rotations](/Python/Rendering/Rotations) | vtkActor::RotateX,Y,Z vtkRenderer::EraseOff | Rotations of a cow about her axes.
[RotationsA](/Python/Rendering/RotationsA) | vtkActor::RotateX,Y,Z vtkRenderer::EraseOff | Perform six rotations of a cow about her x-axis (Figure 3-31a).
[RotationsB](/Python/Rendering/RotationsB) | vtkActor::RotateX,Y,Z vtkRenderer::EraseOff | Perform six rotations of a cow about her y-axis (Figure 3-31b).
[RotationsC](/Python/Rendering/RotationsC) | vtkActor::RotateX,Y,Z vtkRenderer::EraseOff | Perform six rotations of a cow about her z-axis (Figure 3-31c).
[RotationsD](/Python/Rendering/RotationsD) | vtkActor::RotateX,Y,Z vtkRenderer::EraseOff | First a rotation of a cow about her x-axis, then six rotations about her y-axis (Figure 3-31d).
[Shadows](/Python/Rendering/Shadows) | vtkCameraPass vtkRenderStepsPass vtkSequencePass vtkShadowMapBakerPass vtkShadowMapPass | Draw model with shadows.
[Skybox_PBR](/Python/Rendering/Skybox_PBR) | vtkSkybox vtkTexture | Demonstrates physically based rendering, image based lighting and a skybox.
[SpecularSpheres](/Python/Rendering/SpecularSpheres) | vtkProperty | Demonstrates the effect of specular lighting on spheres.
[StippledLine](/Python/Rendering/StippledLine) | vtkTexture | Draw a stippled line.
[StripFran](/Python/Rendering/StripFran) | vtkDecimatePro vtkStripper | Triangle strip examples. (a) Structured triangle mesh consisting of 134 strips each of 390 triangles. (b) Unstructured triangle mesh consisting of 2227 strips of average length 3.94, longest strip 101 triangles. Images are generated by displaying every other triangle strip.
[TransformSphere](/Python/Rendering/TransformSphere) | vtkSphereSource vtkElevationFilter vtkTransform vkTransformFilter | The addition of a transform filter to [ColoredSphere](/Python/Rendering/ColoredSphere).
[TransparentBackground](/Python/Rendering/TransparentBackground) | vtkCallbackCommand vtkInteractorObserver vtkRendererCollection | Demonstrates the use of two renderers. Notice that the second (and subsequent) renderers will have a transparent background.
[WalkCow](/Python/Rendering/WalkCow) | vtkBYUReader vtkRenderWindow::EraseOff() vtkActor | This generates Figs. 3-32, 3-33 found in VTKTextbook.pdf.
[WalkCowA](/Python/Rendering/WalkCowA) | vtkBYUReader vtkRenderWindow::EraseOff() vtkActor | This generates Fig. 3-33a found in VTKTextbook.pdf.
[WalkCowB](/Python/Rendering/WalkCowB) | vtkBYUReader vtkRenderWindow::EraseOff() vtkActor | This generates Fig. 3-33b found in VTKTextbook.pdf.

## Lighting

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ShadowsLightsDemo](/Python/Visualization/ShadowsLightsDemo) | vtkLightActor vtkSequencePass vtkShadowMapBakerPass vtkShadowMapPass | Show lights casting shadows.

## Texture Mapping

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[AnimateVectors](/Python/Texture/AnimateVectors) | vtkTexture vtkGlyph3D | One frame from a vector field animation using texture maps.
[TextureCutQuadric](/Python/Texture/TextureCutQuadric) | vtkBooleanTexture vtkImplicitTextureCoords | Cut a quadric with boolean textures.
[TextureCutSphere](/Python/Texture/TextureCutSphere) | vtkImplicitTextureCoords | Examples of texture thresholding. (b) Boolean combination of two planes to cut nested spheres.
[TexturePlane](/Python/Texture/TexturePlane) | vtkTexture | Example of texture mapping.
[TextureThreshold](/Python/Texture/TextureThreshold) | vtkTexture vtkThresholdTextureCoords vtkStructuredGridGeometryFilter | Demonstrate the use of scalar thresholds to show values of flow density on three planes.

## Visualization

See [this tutorial](http://www.vtk.org/Wiki/VTK/Tutorials/3DDataTypes) for a brief explanation of the VTK terminology of mappers, actors, etc.

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[AlphaFrequency](/Python/Visualization/AlphaFrequency) | vtkLinearExtrusionFilter vtkVectorText | Linearly extrude fonts to show letter frequencies in text.
[AnatomicalOrientation](/Python/VisualizationAlgorithms/AnatomicalOrientation) | vtkAnnotatedCubeActor vtkAxesActor vtkOrientationMarkerWidget vtkTransform | Show a labelled set of anatomical planes transecting a human figure.
[AssignCellColorsFromLUT](/Python/Visualization/AssignCellColorsFromLUT) | vtkNamedColors vtkPlaneSource vtkLookupTable vtkColorTransferFunction | Demonstrates how to assign colors to cells in a vtkPolyData structure using lookup tables.
[BlobbyLogo](/Python/Visualization/BlobbyLogo) | vtkImplicitModeller | A logo created with vtkImplicitModeller.
[Blow](/Python/Visualization/Blow) | vtkUnstructuredGridReader vtkWarpVector vtkConnectivityFilter | Ten frames from a blow molding finite element analysis.
[BluntStreamlines](/Python/VisualizationAlgorithms/BluntStreamlines) | vtkStructuredGridGeometryFilter vtkStreamTracer | Demonstrates airflow around a blunt fin using streamlines.
[Camera](/Python/Visualization/Camera) | vtkCamera | Positioning and aiming the camera.
[CameraModel1](/Python/Visualization/CameraModel1) | vtkCameraActor | Illustrate camera movement.
[CameraModel2](/Python/Visualization/CameraModel2) | vtkCameraActor | Illustrate camera movement.
[CarotidFlow](/Python/VisualizationAlgorithms/CarotidFlow) | vtkStreamTracer vtkThresholdPoints | Visualizing blood flow in the human carotid arteries. Streamtubes of flow velocity are generated.
[CarotidFlowGlyphs](/Python/VisualizationAlgorithms/CarotidFlowGlyphs) | vtkGlyph3D vtkThresholdPoints | Visualizing blood flow in human carotid arteries. Cone glyphs indicate flow direction and magnitude.
[ClampGlyphSizes](/Python/Visualization/ClampGlyphSizes) | vtkGlyph3D | Use vtkGlyph3D with ClampingOn to limit glyph sizes
[ClipSphereCylinder](/Python/VisualizationAlgorithms/ClipSphereCylinder) | vtkImplicitBoolean vtkClipPolyData | A plane clipped with a sphere and an ellipse. The two transforms place each implicit function into the appropriate position. Two outputs are generated by the clipper.
[CollisionDetection](/Python/Visualization/CollisionDetection) | vtkCollisionDetectionFilter | Collison between two spheres.
[ColorActor](/Python/Visualization/ColorActor) | vtkActor::GetProperty()::SetColor | Colour the actor.
[ColoredAnnotatedCube](/Python/VisualizationAlgorithms/ColoredAnnotatedCube) | vtkAnnotatedCubeActor vtkAxesActor vtkCubeSource vtkPropAssembly vtkOrientationMarkerWidget | How to color the individual faces of an annotated cube.
[ColorSeriesPatches](/Python/Visualization/ColorSeriesPatches) | vtkColorSeries | Creates a HTML file called [VTKColorSeriesPatches](http://htmlpreview.github.com/?https://github.com/lorensen/VTKExamples/blob/master/src/Python/Visualization/VTKColorSeriesPatches.html)
[CombustorIsosurface](/Python/VisualizationAlgorithms/CombustorIsosurface) | vtkContourFilter | Marching cubes surface of flow density.
[ComplexV](/Python/Visualization/ComplexV) | vtkHedgeHog | ComplexV from the VTK Textbook.
[ContourQuadric](/Python/VisualizationAlgorithms/ContourQuadric) | vtkQuadric vtkSampleFunction vtkContourFilter | Contouring a quadric function.
[CreateBFont](/Python/VisualizationAlgorithms/CreateBFont) | vtkClipPolyData vtkImageDataGeometryFilter | A scanned image clipped with a scalar value of 1/2 its maximum intensity produces a mixture of quadrilaterals and triangles.
[CreateColorSeriesDemo](/Python/Visualization/CreateColorSeriesDemo) | vtkColorSeries vtkLookupTable | Create a custom vtkColorSeries.
[CubeAxesActor](/Python/Visualization/CubeAxesActor) | vtkCubeAxesActor | Display three orthogonal axes with labels.FWorking with 3D
[CurvatureBandsWithGlyphs](/Python/Visualization/CurvatureBandsWithGlyphs) | vtkCurvatures vtkBandedPolyDataContourFilter vtkLookupTable vtkColorSeries vtkGlyph3D | Demonstrates the coloring of a surface by partitioning the gaussian curvature of a surface into bands and using arrows to display the normals on the surface.
[CutStructuredGrid](/Python/VisualizationAlgorithms/CutStructuredGrid) | vtkCutter | Cut through structured grid with plane. The cut plane is shown solid shaded. A computational plane of constant k value is shown in wireframe for comparison. The colors correspond to flow density. Cutting surfaces are not necessarily planes: implicit functions such as spheres, cylinders, and quadrics can also be used.
[Cutter](/Python/VisualizationAlgorithms/Cutter) | vtkCutter | How to use vtkCutter by cutting through a cube.
[DataSetSurface](/Python/VisualizationAlgorithms/DataSetSurface) | vtkDataSetSurfaceFilter | Cutting a hexahedron with a plane. The red line on the surface shows the cut.
[DecimateFran](/Python/VisualizationAlgorithms/DecimateFran) | vtkDecimatePro | Examples of decimation algorithm. (a) Decimation of laser digitizer data.
[DecimateHawaii](/Python/VisualizationAlgorithms/DecimateHawaii) | vtkDecimatePro | Examples of decimation algorithm. (b) Decimation of terrain data.
[DisplacementPlot](/Python/VisualizationAlgorithms/DisplacementPlot) | vtkColorTransferFunction vtkWarpVector vtkVectorDot | Show modal lines for a vibrating beam.
[DisplayCoordinateAxes](/Python/Visualization/DisplayCoordinateAxes) | vtkOrientationMarkerWidget | Display coordinate axes.
[ElevationBandsWithGlyphs](/Python/Visualization/ElevationBandsWithGlyphs) | vtkBandedPolyDataContourFilter vtkLookupTable vtkColorSeries vtkGlyph3D | Demonstrates the coloring of a surface by partitioning the elevation into bands and using arrows to display the normals on the surface.
[ExponentialCosine](/Python/VisualizationAlgorithms/ExponentialCosine) | vtkWarpScalar | Carpet plots. Visualization of an exponential cosine function. Function values are indicated by surface displacement. Colors indicate derivative values.
[FlyingFrogSkinAndTissue](/Python/Visualization/FlyingFrogSkinAndTissue) | vtkMetaImageReader vtkFlyingEdges3D vtkWindowedSincPolyDataFilter vtkImageGaussianSmooth | All frog parts and translucent skin.
[FlyingHeadSlice](/Python/VisualizationAlgorithms/FlyingHeadSlice) | vtkFlyingEdges2D | Flying edges used to generate contour lines.
[FrogSlice](/Python/Visualization/FrogSlice) | vtkMetaImageReader | Photographic slice of frog (upper left), segmented frog (upper right) and composite of photo and segmentation (bottom). The purple color represents the stomach and the kidneys are yellow.
[GlyphTable](/Python/Visualization/GlyphTable) | vtkGlyph3D | Vary the shapes of glyphed points using a glyph table
[Hanoi](/Python/Visualization/Hanoi) |  | Towers of Hanoi.
[HanoiInitial](/Python/Visualization/HanoiInitial) |  | Towers of Hanoi - Initial configuration.
[HanoiIntermediate](/Python/Visualization/HanoiIntermediate) |  | Towers of Hanoi - Intermediate configuration.
[HardwareSelector](/Python/Visualization/HardwareSelector) | vtkHardwareSelector |
[Hawaii](/Python/Visualization/Hawaii) | vtkElevationFilter vtkColorSeries vtkLookupTable | Visualize elevations by coloring the scalar values with a lookup table.
[HeadBone](/Python/VisualizationAlgorithms/HeadBone) | vtkMarchingCubes | Marching cubes surface of human bone.
[HeadSlice](/Python/VisualizationAlgorithms/HeadSlice) | vtkContourFilter | Marching squares used to generate contour lines.
[HyperStreamline](/Python/VisualizationAlgorithms/HyperStreamline) | vtkHyperStreamline | Example of hyperstreamlines, the four hyperstreamlines shown are integrated along the minor principle stress axis. A plane (colored with a different lookup table) is also shown.
[InteractorStyleTrackballActor](/Python/Visualization/InteractorStyleTrackballActor) | vtkInteractorStyleTrackBallActor |
[InteractorStyleTrackballCamera](/Python/Visualization/InteractorStyleTrackballCamera) | vtkInteractorStyleTrackBallCamera |
[IronIsoSurface](/Python/VisualizationAlgorithms/IronIsoSurface) | vtkContourFilter | Marching cubes surface of iron-protein.
[Kitchen](/Python/Visualization/Kitchen) | vtkStreamTracer vtkStructuredGrid | Demonstrates stream tracing in a kitchen.
[KochSnowflake](/Python/Visualization/KochSnowflake) | vtkPolyData vtkCellArray vtkPoints vtkPolyLine | This example draws a Koch snowflake fractal using recursive functions and some of the convenient tools in the toolkit.
[LOx](/Python/VisualizationAlgorithms/LOx) | vtkStreamTracer vtkTubeFilter | Streamtubes created by using the computational grid just in front of the post as a source for seeds.
[LOxGrid](/Python/VisualizationAlgorithms/LOxGrid) | vtkStreamTracer vtkTubeFilter | Portion of computational grid for the LOx post.
[LOxSeeds](/Python/VisualizationAlgorithms/LOxSeeds) | vtkStreamTracer vtkTubeFilter | Streamlines seeded with spherical cloud of points. Four separate cloud positions are shown.
[LoopShrink](/Python/Visualization/LoopShrink) |  | A network with a loop. VTK 5.0 does not allow you to execute a looping visualization network; this was possible in previous versions of VTK.
[Motor](/Python/VisualizationAlgorithms/Motor) | vtkBYUReader vtkStructuredPointsReader vtkTexture vtkImplicitTextureCoords | Texture cut used to reveal internal structure of a motor. Two cut planes are used in combination with transparent texture.
[NamedColorPatches](/Python/Visualization/NamedColorPatches) | vtkNamedColors | Creates a HTML file called [VTKNamedColorPatches](http://htmlpreview.github.com/?https://github.com/lorensen/VTKExamples/blob/master/src/Python/Visualization/VTKNamedColorPatches.html)
[NamedColors](/Python/Visualization/NamedColors) | vtkNamedColors | Demonstrates how to use the vtkNamedColors class.
[NormalsDemo](/Python/Visualization/NormalsDemo) | vtkPolyDataNormals | Demo different options to generate normals.
[Office](/Python/VisualizationAlgorithms/Office) | vtkPointSource vtkStreamTracer | Using random point seeds to create streamlines.
[OfficeA](/Python/VisualizationAlgorithms/OfficeA) | vtkPointSource vtkStreamTracer | Corresponds to Fig 9-47(a) in the VTK textbook.
[OfficeTube](/Python/VisualizationAlgorithms/OfficeTube) | vtkStreamTracer vtkTubeFilter | The stream polygon. Sweeping a polygon to form a tube.
[OrientedGlyphs](/Python/Visualization/OrientedGlyphs) | vtkGlyph3D | Create oriented glyphs from vector data.
[PineRootConnectivity](/Python/VisualizationAlgorithms/PineRootConnectivity) | vtkMCubesReader vtkPolyDataConnectivityFilter | Applying the connectivity filter to remove noisy isosurfaces.
[PineRootConnectivityA](/Python/VisualizationAlgorithms/PineRootConnectivityA) | vtkMCubesReader vtkPolyDataConnectivityFilter | The isosurface, with no connectivity filter applied.
[PineRootDecimation](/Python/VisualizationAlgorithms/PineRootDecimation) | vtkMCubesReader vtkDecimatePro vtkConnectivityFilter | Applying the decimation and connectivity filters to remove noisy isosurfaces and reduce data size.
[PlateVibration](/Python/VisualizationAlgorithms/PlateVibration) | vtkWarpVector vtkVectorDot | Demonstrates the motion of a vibrating beam.
[PointDataSubdivision](/Python/Visualization/PointDataSubdivision) | vtkLinearSubdivisionFilter | Vary the shapes of glyphed points using a programmable glyph filter
[PointSize](/Python/Visualization/PointSize) | vtkActor |
[ProbeCombustor](/Python/VisualizationAlgorithms/ProbeCombustor) | vtkProbeFilter | Probing data in a combustor.  Probes are regular arrays of 50 by 50 points that are then passed through a contouring filter.
[ProgrammableGlyphs](/Python/Visualization/ProgrammableGlyphs) | vtkProgrammableGlyphFilter | Generate programmable glyphs.
[PseudoVolumeRendering](/Python/VolumeRendering/PseudoVolumeRendering) | vtkCutter vtkContourFilter | 100 cut planes with opacity of 0.05. Rendered back-to-front to simulate volume rendering.
[QuadraticSurface](/Python/Visualization/QuadraticSurface) | vtkQuadric |
[QuadricVisualization](/Python/Visualization/QuadricVisualization) | vtkQuadric vtkSampleFunction vtkContourFilter | Visualizing a quadric function.
[SingleSplat](/Python/VisualizationAlgorithms/SingleSplat) | vtkGaussianSplatter | Elliptical splatting. (a) Single elliptical splat with eccentricity E=10.  Cone shows orientation of vector.
[SphereTexture](/Python/Visualization/SphereTexture) | vtkTextureMapToSphere | Apply an ImageData texture to an sphere
[SpikeFran](/Python/VisualizationAlgorithms/SpikeFran) | vtkGlyph3D | Glyphs indicate surface normals on model of human face. Glyph positions are randomly selected.
[SplatFace](/Python/VisualizationAlgorithms/SplatFace) | vtkGaussianSplatter | Elliptical splatting. (b) Surface reconstructed using elliptical splats into 100^3 volume followed by isosurface extraction. Points regularly subsampled and overlaid on original mesh.
[Stocks](/Python/VisualizationAlgorithms/Stocks) | vtkRibbonFilter vtkLinearExtrusionFilter | Two views from the stock visualization script. The top shows closing price over time; the bottom shows volume over time.
[StreamLines](/Python/Visualization/StreamLines) | vtkStreamLine | Seed streamlines with vectors from a structured grid
[StreamlinesWithLineWidget](/Python/VisualizationAlgorithms/StreamlinesWithLineWidget) | vtkCallbackCommand vtkLineWidget | Using the vtkLineWidget to produce streamlines in the combustor dataset.  The StartInteractionEvent turns the visibility of the streamlines on; the InteractionEvent causes the streamlines to regenerate themselves.
[TensorAxes](/Python/VisualizationAlgorithms/TensorAxes) | vtkPointLoad vtkTensorGlyph | Display the scaled and oriented principal axes of the stress tensor.
[TensorEllipsoids](/Python/VisualizationAlgorithms/TensorEllipsoids) | vtkPointLoad vtkTensorGlyph | Display the scaled and oriented principal axes as tensor ellipsoids representing the stress tensor.
[TextSource](/Python/Visualization/TextSource) | vtkTextSource |
[VectorText](/Python/Visualization/VectorText) | vtkVectorText | Display high resolution text.
[VelocityProfile](/Python/VisualizationAlgorithms/VelocityProfile) | vtkMultiBlockPLOT3DReader vtkStructuredGridGeometryFilter vtkAppendPolyData vtkWarpVector | Warping the geometry of three planes to show flow momentum.
[ViewFrog](/Python/Visualization/ViewFrog) | vtkMetaImageReader vtkMarchingCubes vtkImageGaussianSmooth vtkWindowedSincPolyDataFilter | The complete frog without skin.
[ViewFrogA](/Python/Visualization/ViewFrogA) | vtkMetaImageReader vtkMarchingCubes vtkImageGaussianSmooth vtkWindowedSincPolyDataFilter | The complete frog without skin or skeleton.
[ViewFrogBoth](/Python/Visualization/ViewFrogBoth) | vtkMetaImageReader vtkMarchingCubes vtkImageGaussianSmooth vtkImageGaussianSmooth | The frog’s brain. Model extracted without smoothing (left) and with smoothing (right).
[ViewFrogSkinAndTissue](/Python/Visualization/ViewFrogSkinAndTissue) | vtkMetaImageReader vtkMarchingCubes vtkWindowedSincPolyDataFilter vtkImageGaussianSmooth | All frog parts and translucent skin.
[WarpCombustor](/Python/VisualizationAlgorithms/WarpCombustor) | vtkWarpScalar vtkMultiBlockPLOT3DReader | Carpet plots. Carpet plot of combustor flow energy in a structured grid. Colors and plane displacement represent energy values.
[WindowTitle](/Python/Visualization/WindowTitle) | vtkRenderWindow::SetWindowName |

## Working with vtkImageData

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ImageDataGeometryFilter](/Python/ImageData/ImageDataGeometryFilter) | vtkImageDataGeometryFilter | Convert a vtkImageData to a vtkPolyData.
[ImageNormalize](/Python/ImageData/ImageNormalize) | vtkImageNormalize | Normalize an image.
[SumVTKImages](/Python/ImageData/SumVTKImages) | vtkImageWeightedSum | A function to simplify the summing of images, where you can pass a list of images and weights.
[WriteReadVtkImageData](/Python/ImageData/WriteReadVtkImageData) | vtkImageData vtkXMLImageDataReader vtkXMLImageDataWriter | Generate, edit and read out vtk image data.

## Volume Rendering

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[SimpleRayCast](/Python/VolumeRendering/SimpleRayCast) | vtkFixedPointVolumeRayCastMapper | Volume rendering of a high potential iron protein.

## User Interaction

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[CallBack](/Python/Interaction/CallBack) | vtkCallbackCommand vtkOrientationMarkerWidget | Setting up a callback with client data. Two different methods are demonstrated.
[HighlightPickedActor](/Python/Picking/HighlightPickedActor) | vtkPropPicker vtkInteractorStyleTrackballCamera | Pick and highlight an actor based on mouse clicks.
[HighlightWithSilhouette](/Python/Picking/HighlightWithSilhouette) | vtkPropPicker vtkPolyDataSilhouette| Highlight a picked actor by adding a silhouette.
[MouseEvents](/Python/Interaction/MouseEvents) | vtkInteractorStyleTrackballCamera | Subclass the interactor style.
[MouseEventsObserver](/Python/Interaction/MouseEventsObserver) | vtkCallbackCommand | Use an observer.

## Working with Images

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Actor2D](/Python/Images/Actor2D) | vtkActor2D vtkMapper2D | 2D actor and mapper.
[Cast](/Python/Images/Cast) | vtkImageCast | Cast an image to a different type.
[BackgroundImage](/Python/Images/BackgroundImage) | vtkJPEGReader vtkImageCanvasSource2D vtkImageActor vtkSuperquadricSource | Display an image as the "background" of a scene, and render a superquadric in front of it.

## Image Processing

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Attenuation](/Python/ImageProcessing/Attenuation) | vtkImageGaussianSmooth vtkImageMathematics vtkImageShiftScale | This MRI image illustrates attenuation that can occur due to sensor position.  The artifact is removed by dividing by the attenuation profile determined manually.
[EnhanceEdges](/Python/ImageProcessing/EnhanceEdges) | vtkImageLaplacian vtkImageMathematics | High-pass filters can extract and enhance edges in an image. Subtraction of the Laplacian (middle) from the original image (left) results in edge enhancement or a sharpening operation (right).
[GaussianSmooth](/Python/ImageProcessing/GaussianSmooth) | vtkImageGaussianSmooth | Low-pass filters can be implemented as convolution with a Gaussian kernel.
[HybridMedianComparison](/Python/ImageProcessing/HybridMedianComparison) | vtkImageHybridMedian2D vtkImageMedian3D | Comparison of median and hybrid-median filters. The hybrid filter preserves corners and thin lines, better than the median filter.
[IdealHighPass](/Python/ImageProcessing/IdealHighPass) | vtkImageFFT vtkImageRFFT vtkImageIdealHighPass vtkImageButterworthHighPass | This figure shows two high-pass filters in the frequency domain. The Butterworth high-pass filter has a gradual attenuation that avoids ringing produced by the ideal high-pass filter with an abrupt transition.
[ImageGradient](/Python/VisualizationAlgorithms/ImageGradient) | vtkImageMagnify vtkImageGaussianSmooth vtkImageGradient vtkImageEuclideanToPolar vtkImageExtractComponents vtkImageHSVToRGB | Create an imaging pipeline to visualize gradient information.
[ImageWarp](/Python/Images/ImageWarp) | vtkBMPReader vtkImageLuminance vtkWarpScalar vtkMergeFilter | Combine the imaging and visualization pipelines to deform an image in the z-direction. The vtkMergeFilter is used to combine the warped surface with the original color data.
[IsoSubsample](/Python/ImageProcessing/IsoSubsample) | vtkImageMarchingCubes vtkImageShrink3D vtkImageGaussianSmooth | This figure demonstrates aliasing that occurs when a high-frequency signal is subsampled. High frequencies appear as low frequency artifacts. The left image is an isosurface of a skull after subsampling. The right image used a low-pass filter before subsampling to reduce aliasing.
[MedianComparison](/Python/ImageProcessing/MedianComparison) | vtkImageGaussianSmooth vtkImageMedian3D vtkImageNoiseSource | Comparison of Gaussian and Median smoothing for reducing low-probability high-amplitude noise.
[MorphologyComparison](/Python/ImageProcessing/MorphologyComparison) | vtkImageDilateErode3D vtkImageSeedConnectivity | This figure demonstrates various binary filters that can alter the shape of segmented regions.
[Pad](/Python/ImageProcessing/Pad) | vtkImageConstantPad vtkImageMirrorPad | Convolution in frequency space treats the image as a periodic function. A large kernel can pick up features from both sides of the image. The lower-left image has been padded with zeros to eliminate wraparound during convolution. On the right, mirror padding has been used to remove artificial edges introduced by borders.
[VTKSpectrum](/Python/ImageProcessing/VTKSpectrum) | vtkImageFFT vtkImageFourierCenter vtkImageLogarithmicScale vtkImageMagnitude | The discrete Fourier transform changes an image from the spatial domain into the frequency domain, where each pixel represents a sinusoidal function. This figure shows an image and its power spectrum displayed using a logarithmic transfer function.

## Widgets

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[BalloonWidget](/Python/Widgets/BalloonWidget) | vtkBalloonWidget vtkBalloonRepresentation | Uses a vtkBalloonWidget to draw labels when the mouse stays above an actor.
[BoxWidget](/Python/Widgets/BoxWidget) | vtkBoxWidget | This 3D widget defines a region of interest that is represented by an arbitrarily oriented hexahedron with interior face angles of 90 degrees (orthogonal faces). The object creates 7 handles that can be moused on and manipulated.
[ContourWidget](/Python/Widgets/ContourWidget) | vtkContourWidget vtkOrientedGlyphContourRepresentation | Draw a contour (line) which can be deformed by the user
[OrientationMarkerWidget](/Python/Widgets/OrientationMarkerWidget) | vtkAnnotatedCubeActor vtkOrientationWidget | Draws two cubes. One of them can be clicked to be rotated, and will rotate the second one. The second one has annotations on it, and can also be moved.
[ScalarBarWidget](/Python/Widgets/ScalarBarWidget) | vtkScalarBarWidget | The ScalarBarWidget displays a scalar bar that is movable and changes orientation automatically when close to the borders of the image. It needs a ScalarBarActor
[SphereWidget](/Python/Widgets/SphereWidget) | vtkSphereWidget | This 3D widget defines a sphere that can be interactively placed in a scene.
[TextWidget](/Python/Widgets/TextWidget) | vtkTextWidget | Annotate a VTK image with movable text

## Plotting

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ScatterPlot](/Python/Plotting/ScatterPlot) | vtkChartXY |
[SpiderPlot](/Python/Plotting/SpiderPlot) | vtkSpiderPlotActor |
[SurfacePlot](/Python/Plotting/SurfacePlot) | vtkPlotSurface vtkChartXYZ | Surface plot

## Animation

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Animation](/Python/Utilities/Animation) | vtkRenderWindowInteractor | Move a sphere across a scene.

## Annotation

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[MultiLineText](/Python/Annotation/MultiLineText) | vtkTextMapper | Display multiline text.
[TextOrigin](/Python/Annotation/TextOrigin) |  | This example demonstrates the use of vtkVectorText and vtkFollower. vtkVectorText is used to create 3D annotation.

## Geographic Visualization (Geovis)

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[CompassWidget](/Python/Widgets/CompassWidget) | vtkCompassWidget vtkCompassRepresentation | Draws an interactive compass.
[CompassWidget](/Python/Geovis/CompassWidget) | vtkCompassWidget | Compass Widget.
[EarthSource](/Python/Geovis/EarthSource) | vtkEarthSource | Create the Earth.
[GeoGraticle](/Python/Geovis/GeoGraticle) | vtkGeoGraticle | Show lat/long lines that have been distorted.
[GeoAssignCoordinates](/Python/Geovis/GeoAssignCoordinates) | vtkGeoAssignCoordinates vtkMutableDirectedGraph vtkGraphMapper | Draws a sphere, based on longituds and latitudes.
[ParallelCoordinatesView](/Python/InfoVis/ParallelCoordinatesView) | vtkRTAnalyticSource vtkParallelCoordinatesView vtkParallelCoordinatesRepresentation | Plotting data attributes in a Parallel Coordinates View

## InfoVis

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ParallelCoordinatesExtraction](/Python/InfoVis/ParallelCoordinatesExtraction) | vtkExtractSelection vtkAnnotationLink | Extract data based on a selection in a Parallel Coordinates View
[SelectedGraphIDs](/Python/InfoVis/SelectedGraphIDs) | vtkAnnotationLink vtkRandomGraphSource vtkGraphLayoutView | Callback on vtkAnnotationLink in a Graph Layout View when selection is changed

## PyQt

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[EmbedInPyQt](/Python/Widgets/EmbedInPyQt) | vtkRenderWindowInteractor | Shows how to easily embed VTK in PyQt with QVTKRenderWindowInteractor, first example
[EmbedInPyQt2](/Python/Widgets/EmbedInPyQt2) | vtkRenderWindowInteractor | Shows how to embed VTK in PyQt with QVTKRenderWindowInteractor, second example

## Has Bugs

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[UnstructuredTransientVolumeRendering](/Python/Untested/HasBugs/UnstructuredTransientVolumeRendering) | vtkUnstructuredGridVolumeRayCastMapper |
