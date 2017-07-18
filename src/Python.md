# Python Examples

Please see [this page](http://www.vtk.org/Wiki/VTK/Tutorials/PythonEnvironmentSetup) to learn how to setup your environment to use VTK in Python.

It would be appreciated if there are any Python VTK experts who could convert any of the [c++ examples](/Cxx) to Python!

## Hello World

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Cylinder](/Python/Cylinder)| [vtkPolyDataMapper](http://www.vtk.org/doc/nightly/html/classvtkPolyDataMapper.html#details) [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html#details) [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html#details) [vtkRenderWindow](http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html#details) [vtkRenderWindowInteractor](http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html#details) | Cylinder example from the VTK Textbook and source code. A hello world example

## Simple Operations

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[DistanceBetweenPoints](/Python/DistanceBetweenPoints) | vtkMath::Distance2BetweenPoints |

## Input and Output
### Output

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[PLYWriter](/Python/PLYWriter)| [vtkPLYWriter](http://www.vtk.org/doc/nightly/html/classvtkPLYWriter.html#details) |
[STLWriter](/Python/STLWriter) | [vtkSTLWriter](http://www.vtk.org/doc/nightly/html/classvtkSTLWriter.html#details) |

### Input

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[STLReader](/Python/STLReader)| [vtkSTLReader](http://www.vtk.org/doc/nightly/html/classvtkSTLReader.html#details) |
[UnstructuredGridReader](/Python/UnstructuredGridReader)| [vtkUnstructuredGridReader](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGridReader.html#details) | Using vtkUnstructuredGridReader to read a (legacy) *.vtk file
[VTPsReader](/Python/VTPReader)| [vtkXMLPolyDataReader](http://www.vtk.org/doc/nightly/html/classvtkXMLPolyDataReader.html#details)|

## Working with Arrays

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[GetValues](/Python/Arrays/GetValues) | GetTuple3 |
[RenameArray](/Python/Arrays/RenameArray) | SetName |

## Geometric Objects
### Display

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Arrow](/Python/GeometricObjects/Arrow) | [vtkArrowSource](http://www.vtk.org/doc/nightly/html/classvtkArrowSource.html#details) |
[Axes](/Python/GeometricObjects/Axes) | [vtkAxesActor](http://www.vtk.org/doc/nightly/html/classvtkAxesActor.html#details) |
[Cell3DDemonstration](/Python/GeometricObjects/Cell3DDemonstration) | [vtkHexagonalPrism](http://www.vtk.org/doc/nightly/html/classvtkHexagonalPrism.html#details) [vtkHexahedron](http://www.vtk.org/doc/nightly/html/classvtkHexahedron.html#details) [vtkPentagonalPrism](http://www.vtk.org/doc/nightly/html/classvtkPentagonalPrism.html#details)  [vtkPolyhedron](http://www.vtk.org/doc/nightly/html/classvtkPolyhedron.html#details) [vtkPyramid](http://www.vtk.org/doc/nightly/html/classvtkPyramid.html#details) [vtkTetra](http://www.vtk.org/doc/nightly/html/classvtkTetra.html#details) [vtkVoxel](http://www.vtk.org/doc/nightly/html/classvtkVoxel.html#details) [vtkWedge](http://www.vtk.org/doc/nightly/html/classvtkWedge.html#details) [vtkUnstructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html#details) | Sample objects are generated from the classes derived from vtkCell3D and displayed.
[ColoredLines](/Python/GeometricObjects/ColoredLines) | [vtkCellData](http://www.vtk.org/doc/nightly/html/classvtkCellData.html#details) [vtkLine](http://www.vtk.org/doc/nightly/html/classvtkLine.html#details) |
[Cone](/Python/GeometricObjects/Cone) | [vtkConeSource](http://www.vtk.org/doc/nightly/html/classvtkConeSource.html#details) |
[Cube](/Python/GeometricObjects/Cube) | [vtkCubeSource](http://www.vtk.org/doc/nightly/html/classvtkCubeSource.html#details) |
[Cylinder](/Python/GeometricObjects/Cylinder) | [vtkCylinderSource](http://www.vtk.org/doc/nightly/html/classvtkCylinderSource.html#details) |
[DataSetSurface](/Python/GeometricObjects/DataSetSurface) | [vtkDataSetSurfaceFilter](http://www.vtk.org/doc/nightly/html/classvtkDataSetSurfaceFilter.html#details) |
[Disk](/Python/GeometricObjects/Disk) | [vtkDiskSource](http://www.vtk.org/doc/nightly/html/classvtkDiskSource.html#details) | A circle with a hole in it.
[Frustum](/Python/GeometricObjects/Frustum) | [vtkFrustumSource](http://www.vtk.org/doc/nightly/html/classvtkFrustumSource.html#details) |
[GeometricObjectsDemo](/Python/GeometricObjects/GeometricObjectsDemo) |  |
[Hexahedron](/Python/GeometricObjects/Hexahedron)| [vtkHexahedron](http://www.vtk.org/doc/nightly/html/classvtkHexahedron.html#details) |
[LineSource](/Python/GeometricObjects/LineSource) | [vtkLineSource](http://www.vtk.org/doc/nightly/html/classvtkLineSource.html#details) |
[LongLine](/Python/GeometricObjects/LongLine) | [vtkLine](http://www.vtk.org/doc/nightly/html/classvtkLine.html#details) |
[OrientedArrow](/Python/GeometricObjects/OrientedArrow) | [vtkArrowSource](http://www.vtk.org/doc/nightly/html/classvtkArrowSource.html#details) |
[Plane](/Python/GeometricObjects/Plane)| [vtkPlaneSource](http://www.vtk.org/doc/nightly/html/classvtkPlaneSource.html#details) |
[PlanesIntersection](/Python/GeometricObjects/PlanesIntersection)| [vtkPlanesIntersection](http://www.vtk.org/doc/nightly/html/classvtkPlanesIntersection.html#details) |
[Planes](/Python/GeometricObjects/Planes)| [vtkPlanes](http://www.vtk.org/doc/nightly/html/classvtkPlanes.html#details) [vtkHull](http://www.vtk.org/doc/nightly/html/classvtkHull.html#details) | We create a convex hull of the planes for display purposes.
[PlatonicSolid](/Python/GeometricObjects/PlatonicSolid) | [vtkPlatonicSolidSource](http://www.vtk.org/doc/nightly/html/classvtkPlatonicSolidSource.html#details) | All five platonic solids are displayed.
[PointSource](/Python/GeometricObjects/PointSource) | [vtkPointSource](http://www.vtk.org/doc/nightly/html/classvtkPointSource.html#details) |
[Point](/Python/GeometricObjects/Point) | [vtkPoints](http://www.vtk.org/doc/nightly/html/classvtkPoints.html#details) |
[Polyline](/Python/GeometricObjects/Polyline) | [vtkPolyLine](http://www.vtk.org/doc/nightly/html/classvtkPolyLine.html#details) | This example demonstrates how to create a polygon through several ordered points.
[PolygonIntersection](/Python/GeometricObjects/PolygonIntersection) | [vtkPolygon](http://www.vtk.org/doc/nightly/html/classvtkPolygon.html#details) | IntersectWithLine()
[Polygon](/Python/GeometricObjects/Polygon) | [vtkPolygon](http://www.vtk.org/doc/nightly/html/classvtkPolygon.html#details) |
[Pyramid](/Python/GeometricObjects/Pyramid) | [vtkPyramid](http://www.vtk.org/doc/nightly/html/classvtkPyramid.html#details) |
[Quad](/Python/GeometricObjects/Quad) | [vtkQuad](http://www.vtk.org/doc/nightly/html/classvtkQuad.html#details) |
[RegularPolygonSource](/Python/GeometricObjects/RegularPolygonSource) | [vtkRegularPolygonSource](http://www.vtk.org/doc/nightly/html/classvtkRegularPolygonSource.html#details) |
[Sphere](/Python/GeometricObjects/Sphere) | [vtkSphereSource](http://www.vtk.org/doc/nightly/html/classvtkSphereSource.html#details) |
[Tetrahedron](/Python/GeometricObjects/Tetrahedron) | [vtkTetra](http://www.vtk.org/doc/nightly/html/classvtkTetra.html#details) |
[TextActor](/Python/GeometricObjects/TextActor)  | [vtkTextActor](http://www.vtk.org/doc/nightly/html/classvtkTextActor.html#details) | 2D "HUD-type" text
[TriangleStrip](/Python/GeometricObjects/TriangleStrip) | [vtkTriangleStrip](http://www.vtk.org/doc/nightly/html/classvtkTriangleStrip.html#details) | 
[Triangle](/Python/GeometricObjects/Triangle) | [vtkTriangle](http://www.vtk.org/doc/nightly/html/classvtkTriangle.html#details) |
[Vertex](/Python/GeometricObjects/Vertex) | [vtkVertex](http://www.vtk.org/doc/nightly/html/classvtkVertex.html#details) |

### Parametric Objects

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ParametricObjectsDemo](/Python/GeometricObjects/ParametricObjectsDemo) | [vtkParametricBoy](http://www.vtk.org/doc/nightly/html/classvtkParametricBoy.html#details) [vtkParametricConicSpiral](http://www.vtk.org/doc/nightly/html/classvtkParametricConicSpiral.html#details) [vtkParametricCrossCap](http://www.vtk.org/doc/nightly/html/classvtkParametricCrossCap.html#details) [vtkParametricDini](http://www.vtk.org/doc/nightly/html/classvtkParametricDini.html#details) [vtkParametricEllipsoid](http://www.vtk.org/doc/nightly/html/classvtkParametricEllipsoid.html#details) [vtkParametricEnneper](http://www.vtk.org/doc/nightly/html/classvtkParametricEnneper.html#details) [vtkParametricFigure8Klein](http://www.vtk.org/doc/nightly/html/classvtkParametricFigure8Klein.html#details) [vtkParametricKlein](http://www.vtk.org/doc/nightly/html/classvtkParametricKlein.html#details) [vtkParametricMobius](http://www.vtk.org/doc/nightly/html/classvtkParametricMobius.html#details) [vtkParametricRandomHills](http://www.vtk.org/doc/nightly/html/classvtkParametricRandomHills.html#details) [vtkParametricRoman](http://www.vtk.org/doc/nightly/html/classvtkParametricRoman.html#details) [vtkParametricSpline](http://www.vtk.org/doc/nightly/html/classvtkParametricSpline.html#details) [vtkParametricSuperEllipsoid](http://www.vtk.org/doc/nightly/html/classvtkParametricSuperEllipsoid.html#details) [vtkParametricSuperToroid](http://www.vtk.org/doc/nightly/html/classvtkParametricSuperToroid.html#details) [vtkParametricTorus](http://www.vtk.org/doc/nightly/html/classvtkParametricTorus.html#details)| Demonstration of of the vtkParametric classes added by Andrew Maclean. All the objects are displayed in a 4X4 array. 
[ParametricObjects](/Python/GeometricObjects/ParametricObjects) | | Uncomment the object that you wish to be displayed.


## Implicit Functions

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Boolean](/Python/Implicit/Boolean) | [vtkImplicitBoolean](http://www.vtk.org/doc/nightly/html/classvtkImplicitBoolean.html#details) | Demonstrate booleans of two different implicit functions
[Quadric](/Python/Implicit/Quadric) | [vtkQuadric](http://www.vtk.org/doc/nightly/html/classvtkQuadric.html#details) | Create an ellipsoid using an implicit quadric
[Sphere](/Python/Implicit/Sphere) | [vtkSphere](http://www.vtk.org/doc/nightly/html/classvtkSphere.html#details) | Demonstrate sampling of a sphere implicit function

## Working with PolyData

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[BooleanOperationPolyDataFilter](/Python/PolyData/BooleanOperationPolyDataFilter) | [vtkBooleanOperationPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkBooleanOperationPolyDataFilter.html#details) | This example performs a boolean operation (Intersection, Union, Difference) of two PolyData
[ColoredTriangle](/Python/ColoredTriangle) | [vtkTriangle](http://www.vtk.org/doc/nightly/html/classvtkTriangle.html#details) |
[CombinePolyData](/Python/Filtering/CombinePolyData) | [vtkAppendPolyData](http://www.vtk.org/doc/nightly/html/classvtkAppendPolyData.html#details) | This example combines Polydata objects, and displays the result to the screen.
[Cube](/Python/DataManipulation/Cube) | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details) |
[CurvaturesDemo](/Python/CurvaturesDemo) | [vtkCurvatures](http://www.vtk.org/doc/nightly/html/classvtkCurvatures.html#details)  [vtkColorTransferFunction](http://www.vtk.org/doc/nightly/html/classvtkColorTransferFunction.html#details)  | Demonstrates how to get the Gaussian and Mean curvatures of a surface.
[DottedLine](/Python/DottedLine) | |
[FilledPolygon](/Python/FilledPolygon) | [vtkCutter](http://www.vtk.org/doc/nightly/html/classvtkCutter.html#details) |
[ImplicitPolyDataDistance](/Python/PolyData/ImplicitPolyDataDistance) | [vtkImplicitPolyDataDistance](http://www.vtk.org/doc/nightly/html/classvtkImplicitPolyDataDistance.html#details) |
[IterativeClosestPoints](/Python/IterativeClosestPoints) | [vtkIterativeClosestPointTransform](http://www.vtk.org/doc/nightly/html/classvtkIterativeClosestPointTransform.html#details) |
[KochSnowflake](/Python/Visualization/KochSnowflake) | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details) [vtkCellArray](http://www.vtk.org/doc/nightly/html/classvtkCellArray.html#details) [vtkPoints](http://www.vtk.org/doc/nightly/html/classvtkPoints.html#details) [vtkPolyLine](http://www.vtk.org/doc/nightly/html/classvtkPolyLine.html#details) | This example draws a Koch snowflake fractal using recursive functions and some of the convenient tools in the toolkit.
[LineOnMesh](/Python/DataManipulation/LineOnMesh) | [vtkCellLocator](http://www.vtk.org/doc/nightly/html/classvtkCellLocator.html#details) [vtkParametricSpline](http://www.vtk.org/doc/nightly/html/classvtkParametricSpline.html#details) |
[MeshLabelImageColor](/Python/MeshLabelImageColor) | [vtkDiscreteMarchingCubes](http://www.vtk.org/doc/nightly/html/classvtkDiscreteMarchingCubes.html#details) |
[Outline](/Python/Outline) | [vtkOutlineFilter](http://www.vtk.org/doc/nightly/html/classvtkOutlineFilter.html#details)|
[PolyDataContourToImageData](/Python/PolyData/PolyDataContourToImageData) | [vtkLinearExtrusionFilter](http://www.vtk.org/doc/nightly/html/classvtkLinearExtrusionFilter.html#details) [vtkPolyDataToImageStencil](http://www.vtk.org/doc/nightly/html/classvtkPolyDataToImageStencil.html#details) |
[PolyDataToImageDataStencil](/Python/PolyData/PolyDataToImageDataStencil) | [vtkPolyDataToImageStencil](http://www.vtk.org/doc/nightly/html/classvtkPolyDataToImageStencil.html#details) |
[RotationAroundLine](/Python/RotationAroundLine) | [vtkTransformPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkTransformPolyDataFilter.html#details)  |
[RuledSurfaceFilter](/Python/PolyData/RuledSurfaceFilter) | [vtkRuledSurfaceFilter](http://www.vtk.org/doc/nightly/html/classvtkRuledSurfaceFilter.html#details) |
[SmoothMeshGrid](/Python/PolyData/SmoothMeshGrid) | [vtkLoopSubdivisionFilter](http://www.vtk.org/doc/nightly/html/classvtkLoopSubdivisionFilter.html#details) [vtkButterflySubdivisionFilter](http://www.vtk.org/doc/nightly/html/classvtkButterflySubdivisionFilter.html#details) |
[SolidColoredTriangle](/Python/SolidColoredTriangle) | [vtkTriangle](http://www.vtk.org/doc/nightly/html/classvtkTriangle.html#details) |
[TriangleColoredPoints](/Python/TriangleColoredPoints) | [vtkUnsignedCharArray](http://www.vtk.org/doc/nightly/html/classvtkUnsignedCharArray.html#details) |
[TriangleCornerVertices](/Python/TriangleCornerVertices) | [vtkCellArray](http://www.vtk.org/doc/nightly/html/classvtkCellArray.html#details) |
[TriangleCorners](/Python/TriangleCorners) | [vtkXMLPolyDataWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLPolyDataWriter.html#details) |
[WarpVector](/Python/PolyData/WarpVector) | [vtkLine](http://www.vtk.org/doc/nightly/html/classvtkLine.html#details) [vtkDoubleArray](http://www.vtk.org/doc/nightly/html/classvtkDoubleArray.html#details) [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html#details) [vtkWarpVector](http://www.vtk.org/doc/nightly/html/classvtkWarpVector.html#details) | This example warps/deflects a line.
[WriteTriangleToFile](/Python/WriteTriangleToFile) | [vtkTriangle](http://www.vtk.org/doc/nightly/html/classvtkTriangle.html#details) |

## Working with 3D Data

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ExtractSelection](/Python/PolyData/ExtractSelection) | [vtkExtractSelection](http://www.vtk.org/doc/nightly/html/classvtkExtractSelection.html#details) |
[ExtractSelectionCells](/Python/PolyData/ExtractSelectionCells) | [vtkExtractSelection](http://www.vtk.org/doc/nightly/html/classvtkExtractSelection.html#details) | Extract cell, select cell.

### Working with Structured 3D Data
This section includes vtkImageData, vtkStructuredGrid, and vtkRectilinearGrid.

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[RectilinearGrid](/Python/RectilinearGrid/RectilinearGrid) | [vtkRectilinearGrid](http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html#details) |create a rectilinear grid

### Working with Meshes
This section includes examples of manipulating meshes.

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ClipDataSetWithPolydata](/Python/Meshes/ClipDataSetWithPolydata) | [vtkClipDataSet](http://www.vtk.org/doc/nightly/html/classvtkClipDataSet.html#details) [vtkImplicitPolyDataDistance](http://www.vtk.org/doc/nightly/html/classvtkImplicitPolyDataDistance.html#details) [vtkRectilinearGrid](http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html#details) |clip a vtkRectilinearGrid with arbitrary polydata. In this example, use a vtkConeSource to generate polydata to slice the grid, resulting in an unstructured grid.

## Miscellaneous

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[BackgroundImage](/Python/BackgroundImage) | [vtkJPEGReader](http://www.vtk.org/doc/nightly/html/classvtkJPEGReader.html#details) [vtkImageCanvasSource2D](http://www.vtk.org/doc/nightly/html/classvtkImageCanvasSource2D.html#details) [vtkImageActor](http://www.vtk.org/doc/nightly/html/classvtkImageActor.html#details) [vtkSuperquadricSource](http://www.vtk.org/doc/nightly/html/classvtkSuperquadricSource.html#details) |
[Cutter](/Python/Cutter) | [vtkCutter](http://www.vtk.org/doc/nightly/html/classvtkCutter.html#details) |
[ImplicitDataSet](/Python/ImplicitDataSet) | [vtkImplicitDataSet](http://www.vtk.org/doc/nightly/html/classvtkImplicitDataSet.html#details) | vtkIdType  n/a. This is just a typedef, Python, you can use a python "int" or "long" for vtkIdType.
[Screenshot](/Python/Screenshot) | [vtkWindowToImageFilter](http://www.vtk.org/doc/nightly/html/classvtkWindowToImageFilter.html#details) |
[Variant](/Python/Variant) | [vtkVariant](http://www.vtk.org/doc/nightly/html/classvtkVariant.html#details) |
[vtkVersion](/Python/vtkVersion) | [vtkVersion](http://www.vtk.org/doc/nightly/html/classvtkVersion.html#details) |

## Visualization

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Animation](/Python/Animation) | [vtkTimerCallback](http://www.vtk.org/doc/nightly/html/classvtkTimerCallback.html#details) |
[AssignCellColorsFromLUT](/Python/Visualization/AssignCellColorsFromLUT) | [vtkNamedColors](http://www.vtk.org/doc/nightly/html/classvtkNamedColors.html#details) [vtkPlaneSource](http://www.vtk.org/doc/nightly/html/classvtkPlaneSource.html#details) [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html#details) [vtkColorTransferFunction](http://www.vtk.org/doc/nightly/html/classvtkColorTransferFunction.html#details) | Demonstrates how to assign colors to cells in a vtkPolyData structure using lookup tables.
[Camera](/Python/Camera) | [vtkCamera](http://www.vtk.org/doc/nightly/html/classvtkCamera.html#details) |
[ClampGlyphSizes](/Python/Visualization/ClampGlyphSizes) | [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html#details) | Use vtkGlyph3D with ClampingOn to limit glyph sizes
[ColorActor](/Python/ColorActor) | vtkActor::GetProperty()::SetColor |
[CubeAxesActor](/Python/Visualization/CubeAxesActor) | [vtkCubeAxesActor](http://www.vtk.org/doc/nightly/html/classvtkCubeAxesActor.html#details) | 
[CurvatureBandsWithGlyphs](/Python/Visualization/CurvatureBandsWithGlyphs) | [vtkCurvatures](http://www.vtk.org/doc/nightly/html/classvtkCurvatures.html#details) [vtkBandedPolyDataContourFilter](http://www.vtk.org/doc/nightly/html/classvtkBandedPolyDataContourFilter.html#details) [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html#details) [vtkColorSeries](http://www.vtk.org/doc/nightly/html/classvtkColorSeries.html#details) [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html#details) | Demonstrates the coloring of a surface by partitioning the gaussian curvature of a surface into bands and using arrows to display the normals on the surface.
[ElevationBandsWithGlyphs](/Python/Visualization/ElevationBandsWithGlyphs) | [vtkBandedPolyDataContourFilter](http://www.vtk.org/doc/nightly/html/classvtkBandedPolyDataContourFilter.html#details) [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html#details) [vtkColorSeries](http://www.vtk.org/doc/nightly/html/classvtkColorSeries.html#details) [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html#details) | Demonstrates the coloring of a surface by partitioning the elevation into bands and using arrows to display the normals on the surface.
[GlyphTable](/Python/Visualization/GlyphTable) | [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html#details) | Vary the shapes of glyphed points using a glyph table
[HardwareSelector](/Python/Visualization/HardwareSelector) | [vtkHardwareSelector](http://www.vtk.org/doc/nightly/html/classvtkHardwareSelector.html#details) |
[InteractorStyleTrackballActor](/Python/InteractorStyleTrackballActor) | [vtkInteractorStyleTrackBallActor](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackBallActor.html#details) |
[InteractorStyleTrackballCamera](/Python/InteractorStyleTrackballCamera) | [vtkInteractorStyleTrackBallCamera](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackBallCamera.html#details) |
[MultipleViewports](/Python/MultipleViewports) | vtkRenderer::SetViewport |
[NamedColorPatches](/Python/Visualization/NamedColorPatches) | [vtkNamedColors](http://www.vtk.org/doc/nightly/html/classvtkNamedColors.html#details) | Creates a HTML file called [VTKNamedColorPatches](http://htmlpreview.github.com/?https://github.com/lorensen/VTKExamples/blob/master/src/Python/Visualization/VTKNamedColorPatches.html) showing the available colors in the vtkNamedColors class.
[NamedColors](/Python/Visualization/NamedColors) | [vtkNamedColors](http://www.vtk.org/doc/nightly/html/classvtkNamedColors.html#details) | Demonstrates how to use the vtkNamedColor class
[OrientedGlyphs](/Python/Visualization/OrientedGlyphs)| [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html#details)|Create oriented glyphs from vector data.
[PointDataSubdivision](/Python/Visualization/PointDataSubdivision) | [vtkLinearSubdivisionFilter](http://www.vtk.org/doc/nightly/html/classvtkLinearSubdivisionFilter.html#details) [vtkButterflySubdivisionFilter](http://www.vtk.org/doc/nightly/html/classvtkButterflySubdivisionFilter.html#details) | Demonstrates the effect of applying these filters on various sources.
[PointSize](/Python/Visualization/PointSize) | vtkProperty()::SetPointSize |
[ProgrammableGlyphs](/Python/Visualization/ProgrammableGlyphs) | [vtkProgrammableGlyphFilter](http://www.vtk.org/doc/nightly/html/classvtkProgrammableGlyphFilter.html#details) | Vary the shapes of glyphed points using a programmable glyph filter
[QuadraticSurface](/Python/Visualization/QuadraticSurface) | [vtkQuadric](http://www.vtk.org/doc/nightly/html/classvtkQuadric.html#details) |
[SphereTexture](/Python/Visualization/SphereTexture) | [vtkTextureMapToSphere](http://www.vtk.org/doc/nightly/html/classvtkTextureMapToSphere.html#details) | Apply an ImageData texture to an sphere
[Streamlines](/Python/Visualization/Streamlines) | [vtkStreamLine](http://www.vtk.org/doc/nightly/html/classvtkStreamLine.html#details) | Seed streamlines with vectors from a structured grid
[TextSource](/Python/TextSource) | [vtkTextSource](http://www.vtk.org/doc/nightly/html/classvtkTextSource.html#details) |
[UnstructuredTransientVolumeRendering](/Python/UnstructuredTransientVolumeRendering) | [vtkUnstructuredGridVolumeRayCastMapper](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGridVolumeRayCastMapper.html#details) |
[WindowTitle](/Python/WindowTitle) | vtkRenderWindow::SetWindowName |

## Working with vtkImageData

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ImageWeightedSum](/Python/ImageWeightedSum) | [vtkImageWeightedSum](http://www.vtk.org/doc/nightly/html/classvtkImageWeightedSum.html#details) |
[SumVTKImages](/Python/SumVTKImages) | [vtkImageWeightedSum](http://www.vtk.org/doc/nightly/html/classvtkImageWeightedSum.html#details) | A function to simplify the summing of images, where you can pass a list of images and 
[WriteReadVtkImageData](/Python/WriteReadVtkImageData) | [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html#details) [vtkXMLImageDataReader](http://www.vtk.org/doc/nightly/html/classvtkXMLImageDataReader.html#details) [vtkXMLImageDataWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLImageDataWriter.html#details) |

## Working with ExodusII Data

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ReadExodusData](/Python/ExodusII/ReadExodusData) | [vtkExodusIIReader](http://www.vtk.org/doc/nightly/html/classvtkExodusIIReader.html#details) | A simple script for reading and viewing ExodusII data interactively.

## Graphs

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[EdgeWeights](/Python/Graphs/EdgeWeights)  | [vtkMutableDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html#details) [vtkGraphLayoutView](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html#details) | 
[NOVCAGraph](/Python/Graphs/NOVCAGraph)  | [vtkUnstructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html#details) [vtkXMLUnstructuredGridWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLUnstructuredGridWriter.html#details) | 
[SelectedVerticesAndEdges](/Python/Graphs/SelectedVerticesAndEdges)  | [vtkAnnotationLink](http://www.vtk.org/doc/nightly/html/classvtkAnnotationLink.html#details) [vtkGraphLayoutView](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html#details) | 
[VisualizeGraph](/Python/Graphs/VisualizeGraph)  | [vtkMutableDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html#details) [vtkGraphLayoutView](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html#details) | 

## User Interaction

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[HighlightPickedActor](/Python/Interaction/HighlightPickedActor) | [vtkPropPicker](http://www.vtk.org/doc/nightly/html/classvtkPropPicker.html#details) [vtkInteractorStyleTrackballCamera](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballCamera.html#details) | Pick and highlight an actor based on mouse clicks.
[MouseEventsObserver](/Python/Interaction/MouseEventsObserver) | [vtkCallbackCommand](http://www.vtk.org/doc/nightly/html/classvtkCallbackCommand.html#details) | Use an observer.
[MouseEvents](/Python/Interaction/MouseEvents) | [vtkInteractorStyleTrackballCamera](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballCamera.html#details) | Subclass the interactor style.

## Infovis

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ParallelCoordinatesExtraction](/Python/Infovis/ParallelCoordinatesExtraction)  | [vtkExtractSelection](http://www.vtk.org/doc/nightly/html/classvtkExtractSelection.html#details) [vtkAnnotationLink](http://www.vtk.org/doc/nightly/html/classvtkAnnotationLink.html#details) | Extract data based on a selection in a Parallel Coordinates View
[ParallelCoordinatesView](/Python/Infovis/ParallelCoordinatesView)  | [vtkRTAnalyticSource](http://www.vtk.org/doc/nightly/html/classvtkRTAnalyticSource.html#details) [vtkParallelCoordinatesView](http://www.vtk.org/doc/nightly/html/classvtkParallelCoordinatesView.html#details) [vtkParallelCoordinatesRepresentation](http://www.vtk.org/doc/nightly/html/classvtkParallelCoordinatesRepresentation.html#details) | Plotting data attributes in a Parallel Coordinates View
[ScatterPlot](/Python/Plotting/ScatterPlot)  | [vtkChartXY](http://www.vtk.org/doc/nightly/html/classvtkChartXY.html#details) | 
[SelectedGraphIDs](/Python/Infovis/SelectedGraphIDs)  | [vtkAnnotationLink](http://www.vtk.org/doc/nightly/html/classvtkAnnotationLink.html#details) [vtkRandomGraphSource](http://www.vtk.org/doc/nightly/html/classvtkRandomGraphSource.html#details) [vtkGraphLayoutView](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html#details) | Callback on vtkAnnotationLink in a Graph Layout View when selection is changed
[SpiderPlot](/Python/Plotting/SpiderPlot)  | [vtkSpiderPlotActor](http://www.vtk.org/doc/nightly/html/classvtkSpiderPlotActor.html#details) | 

## Geovis

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[GeoAssignCoordinates](/Python/Geovis/GeoAssignCoordinates) | [vtkGeoAssignCoordinates](http://www.vtk.org/doc/nightly/html/classvtkGeoAssignCoordinates.html#details) [vtkMutableDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html#details) [vtkGraphMapper](http://www.vtk.org/doc/nightly/html/classvtkGraphMapper.html#details) | Draws a sphere, based on longituds and latitudes.

## Widgets

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[BalloonWidget](/Python/Widgets/BalloonWidget) | [vtkBalloonWidget](http://www.vtk.org/doc/nightly/html/classvtkBalloonWidget.html#details) [vtkBalloonRepresentation](http://www.vtk.org/doc/nightly/html/classvtkBalloonRepresentation.html#details) | Uses a vtkBalloonWidget to draw labels when the mouse stays above an actor.
[BoxWidget](/Python/Widgets/BoxWidget) | [vtkBoxWidget](http://www.vtk.org/doc/nightly/html/classvtkBoxWidget.html#details) | This 3D widget defines a region of interest that is represented by an arbitrarily oriented hexahedron with interior face angles of 90 degrees (orthogonal faces). The object creates 7 handles that can be moused on and manipulated.
[CompassWidget](/Python/Widgets/CompassWidget) | [vtkCompassWidget](http://www.vtk.org/doc/nightly/html/classvtkCompassWidget.html#details) [vtkCompassRepresentation](http://www.vtk.org/doc/nightly/html/classvtkCompassRepresentation.html#details) | Draws an interactive compass.
[ContourWidget](/Python/Widgets/ContourWidget) | [vtkContourWidget](http://www.vtk.org/doc/nightly/html/classvtkContourWidget.html#details) [vtkOrientedGlyphContourRepresentation](http://www.vtk.org/doc/nightly/html/classvtkOrientedGlyphContourRepresentation.html#details) | Draw a contour (line) which can be deformed by the user
[OrientationMarkerWidget](/Python/Widgets/OrientationMarkerWidget) | [vtkAnnotatedCubeActor](http://www.vtk.org/doc/nightly/html/classvtkAnnotatedCubeActor.html#details) [vtkOrientationWidget](http://www.vtk.org/doc/nightly/html/classvtkOrientationWidget.html#details) | Draws two cubes. One of them can be clicked to be rotated, and will rotate the second one. The second one has annotations on it, and can also be moved.
[ScalarBarWidget](/Python/Widgets/ScalarBarWidget) | [vtkScalarBarWidget](http://www.vtk.org/doc/nightly/html/classvtkScalarBarWidget.html#details) | The ScalarBarWidget displays a scalar bar that is movable and changes orientation automatically when close to the borders of the image. It needs a ScalarBarActor
[SphereWidget](/Python/Widgets/SphereWidget) | [vtkSphereWidget](http://www.vtk.org/doc/nightly/html/classvtkSphereWidget.html#details) | This 3D widget defines a sphere that can be interactively placed in a scene.
[TextWidget](/Python/Widgets/TextWidget) | [vtkTextWidget](http://www.vtk.org/doc/nightly/html/classvtkTextWidget.html#details) | Annotate a VTK image with movable text

## Utilities

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Delaunay2D](/Python/Filtering/Delaunay2D) | [vtkDelaunay2D](http://www.vtk.org/doc/nightly/html/classvtkDelaunay2D.html#details) |
[LUTUtilities](/Python/Utilities/LUTUtilities) | [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html#details) [vtkColorSeries](http://www.vtk.org/doc/nightly/html/classvtkColorSeries.html#details) | A utility class for vtkLookupTable allowing you to output the table contents or to compare tables.

## PyQt

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[EmbedInPyQt](/Python/Widgets/EmbedInPyQt) | [vtkRenderWindowInteractor](http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html#details) | Shows how to easily embed VTK in PyQt with QVTKRenderWindowInteractor, first example
[EmbedInPyQt2](/Python/Widgets/EmbedInPyQt2) | [vtkRenderWindowInteractor](http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html#details) | Shows how to embed VTK in PyQt with QVTKRenderWindowInteractor, second example
