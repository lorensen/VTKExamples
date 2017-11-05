# Python Examples

Please see [this page](http://www.vtk.org/Wiki/VTK/Tutorials/PythonEnvironmentSetup) to learn how to setup your environment to use VTK in Python.

It would be appreciated if there are any Python VTK experts who could convert any of the [c++ examples](/Cxx) to Python!

!!! info
    [This table](/Coverage/PythonVTKClassesUsed.md) shows the VTK classes covered by the examples.

!!! info
    [This table](/Coverage/PythonVTKClassesNotUsed.md) shows VTK classes that do not have an example. Please add examples in your area of expertise!

## Hello World

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[CylinderExample](/Python/GeometricObjects/CylinderExample)| vtkPolyDataMapper vtkActor vtkRenderer vtkRenderWindow vtkRenderWindowInteractor | Cylinder example from the VTK Textbook and source code. A hello world example

## Simple Operations

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[DistanceBetweenPoints](/Python/SimpleOperations/DistanceBetweenPoints) | vtkMath::Distance2BetweenPoints |

## Input and Output
### Output

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[PLYWriter](/Python/IO/PLYWriter)| vtkPLYWriter |
[STLWriter](/Python/IO/STLWriter) | vtkSTLWriter |

### Input

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[STLReader](/Python/IO/STLReader)| vtkSTLReader |
[UnstructuredGridReader](/Python/IO/UnstructuredGridReader)| vtkUnstructuredGridReader | Using vtkUnstructuredGridReader to read a (legacy) *.vtk file
[VTPReader](/Python/IO/VTPReader)| vtkXMLPolyDataReader | Needs fixing.


## Working with Arrays

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[GetValues](/Python/Arrays/GetValues) | GetTuple3 |
[RenameArray](/Python/Arrays/RenameArray) | SetName |

## Geometric Objects
### Display

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Arrow](/Python/GeometricObjects/Arrow) | vtkArrowSource |
[Axes](/Python/GeometricObjects/Axes) | vtkAxesActor |
[Cell3DDemonstration](/Python/GeometricObjects/Cell3DDemonstration) | vtkHexagonalPrism vtkHexahedron vtkPentagonalPrism  vtkPolyhedron vtkPyramid vtkTetra vtkVoxel vtkWedge vtkUnstructuredGrid | Sample objects are generated from the classes derived from vtkCell3D and displayed.
[ColoredLines](/Python/GeometricObjects/ColoredLines) | vtkCellData vtkLine |
[Cone](/Python/GeometricObjects/Cone) | vtkConeSource |
[Cube](/Python/GeometricObjects/Cube) | vtkCubeSource |
[Cylinder](/Python/GeometricObjects/Cylinder) | vtkCylinderSource |
[DataSetSurface](/Python/GeometricObjects/DataSetSurface) | vtkDataSetSurfaceFilter |
[Disk](/Python/GeometricObjects/Disk) | vtkDiskSource | A circle with a hole in it.
[Frustum](/Python/GeometricObjects/Frustum) | vtkFrustumSource |
[GeometricObjectsDemo](/Python/GeometricObjects/GeometricObjectsDemo) |  |
[Hexahedron](/Python/GeometricObjects/Hexahedron)| vtkHexahedron |
[LineSource](/Python/GeometricObjects/LineSource) | vtkLineSource |
[LongLine](/Python/GeometricObjects/LongLine) | vtkLine |
[OrientedArrow](/Python/GeometricObjects/OrientedArrow) | vtkArrowSource |
[Plane](/Python/GeometricObjects/Plane)| vtkPlaneSource |
[PlanesIntersection](/Python/GeometricObjects/PlanesIntersection)| vtkPlanesIntersection |
[Planes](/Python/GeometricObjects/Planes)| vtkPlanes vtkHull | We create a convex hull of the planes for display purposes.
[PlatonicSolid](/Python/GeometricObjects/PlatonicSolid) | vtkPlatonicSolidSource | All five platonic solids are displayed.
[PointSource](/Python/GeometricObjects/PointSource) | vtkPointSource |
[Point](/Python/GeometricObjects/Point) | vtkPoints |
[Polyline](/Python/GeometricObjects/Polyline) | vtkPolyLine | This example demonstrates how to create a polygon through several ordered points.
[PolygonIntersection](/Python/GeometricObjects/PolygonIntersection) | vtkPolygon | IntersectWithLine()
[Polygon](/Python/GeometricObjects/Polygon) | vtkPolygon |
[Pyramid](/Python/GeometricObjects/Pyramid) | vtkPyramid |
[Quad](/Python/GeometricObjects/Quad) | vtkQuad |
[RegularPolygonSource](/Python/GeometricObjects/RegularPolygonSource) | vtkRegularPolygonSource |
[Sphere](/Python/GeometricObjects/Sphere) | vtkSphereSource |
[Tetrahedron](/Python/GeometricObjects/Tetrahedron) | vtkTetra |
[TextActor](/Python/GeometricObjects/TextActor)  | vtkTextActor | 2D "HUD-type" text
[TriangleStrip](/Python/GeometricObjects/TriangleStrip) | vtkTriangleStrip | 
[Triangle](/Python/GeometricObjects/Triangle) | vtkTriangle |
[Vertex](/Python/GeometricObjects/Vertex) | vtkVertex |

### Parametric Objects

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ParametricObjectsDemo](/Python/GeometricObjects/ParametricObjectsDemo) | vtkParametricBoy vtkParametricConicSpiral vtkParametricCrossCap vtkParametricDini vtkParametricEllipsoid vtkParametricEnneper vtkParametricFigure8Klein vtkParametricKlein vtkParametricMobius vtkParametricRandomHills vtkParametricRoman vtkParametricSpline vtkParametricSuperEllipsoid vtkParametricSuperToroid vtkParametricTorus| Demonstration of of the vtkParametric classes added by Andrew Maclean. All the objects are displayed in a 4X4 array. 
[ParametricObjects](/Python/GeometricObjects/ParametricObjects) | | Uncomment the object that you wish to be displayed.

## Implicit Functions and Iso-surfaces


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ImplicitDataSet](/Python/ImplicitFunctions/ImplicitDataSet) | vtkImplicitDataSet | vtkIdType  n/a. This is just a typedef, Python, you can use a python "int" or "long" for vtkIdType.

## Implicit Functions

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Boolean](/Python/Implicit/Boolean) | vtkImplicitBoolean | Demonstrate booleans of two different implicit functions
[Quadric](/Python/Implicit/Quadric) | vtkQuadric | Create an ellipsoid using an implicit quadric
[Sphere](/Python/Implicit/Sphere) | vtkSphere | Demonstrate sampling of a sphere implicit function

## Working with PolyData

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[BooleanOperationPolyDataFilter](/Python/PolyData/BooleanOperationPolyDataFilter) | vtkBooleanOperationPolyDataFilter | This example performs a boolean operation (Intersection, Union, Difference) of two PolyData
[ColoredTriangle](/Python/PolyData/ColoredTriangle) | vtkTriangle | Creates a file TriangleColored.vtp.
[CombinePolyData](/Python/Filtering/CombinePolyData) | vtkAppendPolyData | This example combines Polydata objects, and displays the result to the screen.
[Cube](/Python/DataManipulation/Cube) | vtkPolyData |
[CurvaturesDemo](/Python/Polydata/CurvaturesDemo) | vtkCurvatures  vtkColorTransferFunction  | Demonstrates how to get the Gaussian and Mean curvatures of a surface.
[FilledPolygon](/Python/Polydata/FilledPolygon) | vtkCutter |
[ImplicitPolyDataDistance](/Python/PolyData/ImplicitPolyDataDistance) | vtkImplicitPolyDataDistance |
[IterativeClosestPoints](/Python/Filtering/IterativeClosestPoints) | vtkIterativeClosestPointTransform |
[KochSnowflake](/Python/Visualization/KochSnowflake) | vtkPolyData vtkCellArray vtkPoints vtkPolyLine | This example draws a Koch snowflake fractal using recursive functions and some of the convenient tools in the toolkit.
[LineOnMesh](/Python/DataManipulation/LineOnMesh) | vtkCellLocator vtkParametricSpline |
[MeshLabelImageColor](/Python/DataManipulation/MeshLabelImageColor) | vtkDiscreteMarchingCubes |
[Outline](/Python/PolyData/Outline) | vtkOutlineFilter|
[PolyDataContourToImageData](/Python/PolyData/PolyDataContourToImageData) | vtkLinearExtrusionFilter vtkPolyDataToImageStencil |
[PolyDataToImageDataStencil](/Python/PolyData/PolyDataToImageDataStencil) | vtkPolyDataToImageStencil |
[RotationAroundLine](/Python/PolyData/RotationAroundLine) | vtkTransformPolyDataFilter  |
[RuledSurfaceFilter](/Python/PolyData/RuledSurfaceFilter) | vtkRuledSurfaceFilter |
[SmoothMeshGrid](/Python/PolyData/SmoothMeshGrid) | vtkLoopSubdivisionFilter vtkButterflySubdivisionFilter |
[SolidColoredTriangle](/Python/PolyData/SolidColoredTriangle) | vtkTriangle | Writes out a file TriangleSolidColor.vtp.
[TriangleColoredPoints](/Python/PolyData/TriangleColoredPoints) | vtkUnsignedCharArray |
[TriangleCornerVertices](/Python/PolyData/TriangleCornerVertices) | vtkCellArray |
[TriangleCorners](/Python/PolyData/TriangleCorners) | vtkXMLPolyDataWriter |
[WarpVector](/Python/PolyData/WarpVector) | vtkLine vtkDoubleArray vtkPolyData vtkWarpVector | This example warps/deflects a line.
[WriteTriangleToFile](/Python/IO/WriteTriangleToFile) | vtkTriangle |

## Working with 3D Data

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ExtractSelection](/Python/PolyData/ExtractSelection) | vtkExtractSelection |
[ExtractSelectionCells](/Python/PolyData/ExtractSelectionCells) | vtkExtractSelection | Extract cell, select cell.

### Working with Structured 3D Data
This section includes vtkImageData, vtkStructuredGrid, and vtkRectilinearGrid.

#### vtkImageData

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ImageWeightedSum](/Python/ImageData/ImageWeightedSum) | vtkImageWeightedSum |Add two or more images.


#### vtkRectilinearGrid

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[RectilinearGrid](/Python/RectilinearGrid/RectilinearGrid) | vtkRectilinearGrid |create a rectilinear grid

### Working with Meshes
This section includes examples of manipulating meshes.

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ClipDataSetWithPolydata](/Python/Meshes/ClipDataSetWithPolydata) | vtkClipDataSet vtkImplicitPolyDataDistance vtkRectilinearGrid |clip a vtkRectilinearGrid with arbitrary polydata. In this example, use a vtkConeSource to generate polydata to slice the grid, resulting in an unstructured grid.
[DelaunayMesh](/Python/Modelling/DelaunayMesh)| vtkDelaunay2D vtkMinimalStandardRandomSequence vtkExtractEdges vtkGlyph3D vtkTubeFilter | Two-dimensional Delaunay triangulation of a random set of points. Points and edges are shown highlighted with sphere glyphs and tubes.

## Rendering
| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[DottedLine](/Python/Rendering/DottedLine) | | This needs a re-work, see StippledLine.cxx 
[Rotations](/Python/Rendering/Rotations)| vtkActor::RotateX,Y,Z vtkRenderer::EraseOff | Rotations of a cow about her axes.
[WalkCow](/Python/Rendering/WalkCow) | vtkBYUReader renWin::EraseOff() vtkActor | This generates Figs. 3-31, 3-32, 3-33 found in VTKTextbook.pdf.

## Visualization

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[AssignCellColorsFromLUT](/Python/Visualization/AssignCellColorsFromLUT) | vtkNamedColors vtkPlaneSource vtkLookupTable vtkColorTransferFunction | Demonstrates how to assign colors to cells in a vtkPolyData structure using lookup tables.
[Camera](/Python/Visualization/Camera) | vtkCamera | Positioning and aiming the camera.
[ClampGlyphSizes](/Python/Visualization/ClampGlyphSizes) | vtkGlyph3D | Use vtkGlyph3D with ClampingOn to limit glyph sizes
[ColorActor](/Python/Visualization/ColorActor) | vtkActor::GetProperty()::SetColor | Colour the actor.
[CubeAxesActor](/Python/Visualization/CubeAxesActor) | vtkCubeAxesActor | 
[CurvatureBandsWithGlyphs](/Python/Visualization/CurvatureBandsWithGlyphs) | vtkCurvatures vtkBandedPolyDataContourFilter vtkLookupTable vtkColorSeries vtkGlyph3D | Demonstrates the coloring of a surface by partitioning the gaussian curvature of a surface into bands and using arrows to display the normals on the surface.
[Cutter](/Python/VisualizationAlgorithms/Cutter) | vtkCutter |
[DisplacementPlot](/Python/VisualizationAlgorithms/DisplacementPlot) | vtkColorTransferFunction vtkWarpVector vtkVectorDot | Show modal lines for a vibrating beam.
[ElevationBandsWithGlyphs](/Python/Visualization/ElevationBandsWithGlyphs) | vtkBandedPolyDataContourFilter vtkLookupTable vtkColorSeries vtkGlyph3D | Demonstrates the coloring of a surface by partitioning the elevation into bands and using arrows to display the normals on the surface.
[GlyphTable](/Python/Visualization/GlyphTable) | vtkGlyph3D | Vary the shapes of glyphed points using a glyph table
[Hawaii](/Python/Visualization/Hawaii)| vtkElevationFilter vtkColorSeries vtkLookupTable | Visualize elevations by coloring the scalar values with a lookup table.
[HardwareSelector](/Python/Visualization/HardwareSelector) | vtkHardwareSelector |
[InteractorStyleTrackballActor](/Python/Visualization/InteractorStyleTrackballActor) | vtkInteractorStyleTrackBallActor |
[InteractorStyleTrackballCamera](/Python/Visualization/InteractorStyleTrackballCamera) | vtkInteractorStyleTrackBallCamera |
[Motor](/Python/VisualizationAlgorithms/Motor) | vtkBYUReader vtkStructuredPointsReader vtkTexture vtkImplicitTextureCoords | Texture cut used to reveal internal structure of a motor. Two cut planes are used in combination with transparent texture.
[MultipleViewports](/Python/Visualization/MultipleViewports) | vtkRenderer::SetViewport |
[NamedColors](/Python/Visualization/NamedColors) | vtkNamedColors | Demonstrates how to use the vtkNamedColors class.
[NamedColorPatches](/Python/Visualization/NamedColorPatches) | vtkNamedColors | Creates a HTML file called [VTKNamedColorPatches](http://htmlpreview.github.com/?https://github.com/lorensen/VTKExamples/blob/master/src/Python/Visualization/VTKNamedColorPatches.html)
[OrientedGlyphs](/Python/Visualization/OrientedGlyphs)| vtkGlyph3D|Create oriented glyphs from vector data.
[PlateVibration](/Python/VisualizationAlgorithms/PlateVibration) | vtkWarpVector vtkVectorDot | Demonstrates the motion of a vibrating beam.
[PointDataSubdivision](/Python/Visualization/PointDataSubdivision) |  vtkLinearSubdivisionFilter | Vary the shapes of glyphed points using a programmable glyph filter
[QuadraticSurface](/Python/Visualization/QuadraticSurface) | vtkQuadric |
[SphereTexture](/Python/Visualization/SphereTexture) | vtkTextureMapToSphere | Apply an ImageData texture to an sphere
[Streamlines](/Python/Visualization/Streamlines) | vtkStreamLine | Seed streamlines with vectors from a structured grid
[StreamlinesWithLineWidget](/Python/VisualizationAlgorithms/StreamlinesWithLineWidget)| vtkCallbackCommand vtkLineWidget | Using the vtkLineWidget to produce streamlines in the combustor dataset.  The StartInteractionEvent turns the visibility of the streamlines on; the InteractionEvent causes the streamlines to regenerate themselves.
[TensorAxes](/Python/VisualizationAlgorithms/TensorAxes)| vtkPointLoad vtkTensorGlyph | Display the scaled and oriented principal axes of the stress tensor.
[TensorEllipsoids](/Python/VisualizationAlgorithms/TensorEllipsoids)| vtkPointLoad vtkTensorGlyph | Display the scaled and oriented principal axes as tensor ellipsoids representing the stress tensor.
[TextSource](/Python/Visualization/TextSource) | vtkTextSource |
[UnstructuredTransientVolumeRendering](/Python/Visualization/UnstructuredTransientVolumeRendering) | vtkUnstructuredGridVolumeRayCastMapper |
[VelocityProfile](/Python/VisualizationAlgorithms/VelocityProfile) | vtkMultiBlockPLOT3DReader vtkStructuredGridGeometryFilter vtkAppendPolyData vtkWarpVector | Warping the geometry of three planes to show flow momentum.
[VectorText](/Python/Visualization/VectorText)| vtkVectorText |Display high resolution text.
[WindowTitle](/Python/Visualization/WindowTitle) | vtkRenderWindow::SetWindowName |

## Working with Images

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[BackgroundImage](/Python/BackgroundImage) | vtkJPEGReader vtkImageCanvasSource2D vtkImageActor vtkSuperquadricSource | Display an image as the "background" of a scene, and render a superquadric in front of it.

## Working with vtkImageData

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[SumVTKImages](/Python/ImageData/SumVTKImages) | vtkImageWeightedSum | A function to simplify the summing of images, where you can pass a list of images and 
[WriteReadVtkImageData](/Python/ImageData/WriteReadVtkImageData) | vtkImageData vtkXMLImageDataReader vtkXMLImageDataWriter |

## Working with ExodusII Data

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ReadExodusData](/Python/ExodusII/ReadExodusData) | vtkExodusIIReader | A simple script for reading and viewing ExodusII data interactively.

## Graphs

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[EdgeWeights](/Python/Graphs/EdgeWeights)  | vtkMutableDirectedGraph vtkGraphLayoutView | 
[NOVCAGraph](/Python/Graphs/NOVCAGraph)  | vtkUnstructuredGrid vtkXMLUnstructuredGridWriter | 
[SelectedVerticesAndEdges](/Python/Graphs/SelectedVerticesAndEdges)  | vtkAnnotationLink vtkGraphLayoutView | 
[VisualizeGraph](/Python/Graphs/VisualizeGraph)  | vtkMutableDirectedGraph vtkGraphLayoutView | 

## User Interaction

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[HighlightPickedActor](/Python/Interaction/HighlightPickedActor) | vtkPropPicker vtkInteractorStyleTrackballCamera | Pick and highlight an actor based on mouse clicks.
[MouseEventsObserver](/Python/Interaction/MouseEventsObserver) | vtkCallbackCommand | Use an observer.
[MouseEvents](/Python/Interaction/MouseEvents) | vtkInteractorStyleTrackballCamera | Subclass the interactor style.

## Infovis

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ParallelCoordinatesExtraction](/Python/Infovis/ParallelCoordinatesExtraction)  | vtkExtractSelection vtkAnnotationLink | Extract data based on a selection in a Parallel Coordinates View
[ParallelCoordinatesView](/Python/Infovis/ParallelCoordinatesView)  | vtkRTAnalyticSource vtkParallelCoordinatesView vtkParallelCoordinatesRepresentation | Plotting data attributes in a Parallel Coordinates View
[ScatterPlot](/Python/Plotting/ScatterPlot)  | vtkChartXY | 
[SelectedGraphIDs](/Python/Infovis/SelectedGraphIDs)  | vtkAnnotationLink vtkRandomGraphSource vtkGraphLayoutView | Callback on vtkAnnotationLink in a Graph Layout View when selection is changed
[SpiderPlot](/Python/Plotting/SpiderPlot)  | vtkSpiderPlotActor | 

## Geovis

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[GeoAssignCoordinates](/Python/Geovis/GeoAssignCoordinates) | vtkGeoAssignCoordinates vtkMutableDirectedGraph vtkGraphMapper | Draws a sphere, based on longituds and latitudes.

## Widgets

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[BalloonWidget](/Python/Widgets/BalloonWidget) | vtkBalloonWidget vtkBalloonRepresentation | Uses a vtkBalloonWidget to draw labels when the mouse stays above an actor.
[BoxWidget](/Python/Widgets/BoxWidget) | vtkBoxWidget | This 3D widget defines a region of interest that is represented by an arbitrarily oriented hexahedron with interior face angles of 90 degrees (orthogonal faces). The object creates 7 handles that can be moused on and manipulated.
[CompassWidget](/Python/Widgets/CompassWidget) | vtkCompassWidget vtkCompassRepresentation | Draws an interactive compass.
[ContourWidget](/Python/Widgets/ContourWidget) | vtkContourWidget vtkOrientedGlyphContourRepresentation | Draw a contour (line) which can be deformed by the user
[OrientationMarkerWidget](/Python/Widgets/OrientationMarkerWidget) | vtkAnnotatedCubeActor vtkOrientationWidget | Draws two cubes. One of them can be clicked to be rotated, and will rotate the second one. The second one has annotations on it, and can also be moved.
[ScalarBarWidget](/Python/Widgets/ScalarBarWidget) | vtkScalarBarWidget | The ScalarBarWidget displays a scalar bar that is movable and changes orientation automatically when close to the borders of the image. It needs a ScalarBarActor
[SphereWidget](/Python/Widgets/SphereWidget) | vtkSphereWidget | This 3D widget defines a sphere that can be interactively placed in a scene.
[TextWidget](/Python/Widgets/TextWidget) | vtkTextWidget | Annotate a VTK image with movable text

## Utilities

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Delaunay2D](/Python/Filtering/Delaunay2D) | vtkDelaunay2D |
[LUTUtilities](/Python/Utilities/LUTUtilities) | vtkLookupTable vtkColorSeries | A utility class for vtkLookupTable allowing you to output the table contents or to compare tables.
[Screenshot](/Python/Utilities/Screenshot) | vtkWindowToImageFilter |
[Variant](/Python/Utilities/Variant) | vtkVariant |
[VTKWithNumpy](/Python/Utilities/VTKWithNumpy) | vtkImageImport |
[VTKVersion](/Python/Utilities/VTKVersion) | vtkVersion |

## Animation

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Animation](/Python/Utilities/Animation) | vtkRenderWindowInteractor | Move a sphere across a scene.

## PyQt

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[EmbedInPyQt](/Python/Widgets/EmbedInPyQt) | vtkRenderWindowInteractor | Shows how to easily embed VTK in PyQt with QVTKRenderWindowInteractor, first example
[EmbedInPyQt2](/Python/Widgets/EmbedInPyQt2) | vtkRenderWindowInteractor | Shows how to embed VTK in PyQt with QVTKRenderWindowInteractor, second example
