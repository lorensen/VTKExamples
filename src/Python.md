# Python Examples

Please see [this page](http://www.vtk.org/Wiki/VTK/Tutorials/PythonEnvironmentSetup) to learn how to setup your environment to use VTK in Python.

It would be appreciated if there are any Python VTK experts who could convert any of the [c++ examples](/Cxx) to Python!

## Hello World

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[Cylinder](/Python/Cylinder)| [vtkPolyDataMapper](http://www.vtk.org/doc/nightly/html/classvtkPolyDataMapper.html) [vtkActor](http://www.vtk.org/doc/nightly/html/classvtkActor.html) [vtkRenderer](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html) [vtkRenderWindow](http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html) [vtkRenderWindowInteractor](http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html) | Cylinder example from the VTK Textbook and source code. A hello world example

## Simple Operations

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[DistanceBetweenPoints](/Python/DistanceBetweenPoints) | vtkMath::Distance2BetweenPoints |

## Input and Output
### Output

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[PLYWriter](/Python/PLYWriter)| [vtkPLYWriter](http://www.vtk.org/doc/nightly/html/classvtkPLYWriter.html) |
[STLWriter](/Python/STLWriter) | [vtkSTLWriter](http://www.vtk.org/doc/nightly/html/classvtkSTLWriter.html) |

### Input

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[STLReader](/Python/STLReader)| [vtkSTLReader](http://www.vtk.org/doc/nightly/html/classvtkSTLReader.html) |
[UnstructuredGridReader](/Python/UnstructuredGridReader)| [vtkUnstructuredGridReader](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGridReader.html) | Using vtkUnstructuredGridReader to read a (legacy) *.vtk file
[VTPsReader](/Python/VTPReader)| [vtkXMLPolyDataReader](http://www.vtk.org/doc/nightly/html/classvtkXMLPolyDataReader.html)|

## Working with Arrays

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[GetValues](/Python/Arrays/GetValues) | GetTuple3 |
[RenameArray](/Python/Arrays/RenameArray) | SetName |

## Geometric Objects
### Display

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[Arrow](/Python/GeometricObjects/Display/Arrow) | [vtkArrowSource](http://www.vtk.org/doc/nightly/html/classvtkArrowSource.html) |
[Axes](/Python/GeometricObjects/Display/Axes) | [vtkAxesActor](http://www.vtk.org/doc/nightly/html/classvtkAxesActor.html) |
[Cell3DDemonstration](/Python/GeometricObjects/Display/Cell3DDemonstration) | [vtkHexagonalPrism](http://www.vtk.org/doc/nightly/html/classvtkHexagonalPrism.html) [vtkHexahedron](http://www.vtk.org/doc/nightly/html/classvtkHexahedron.html) [vtkPentagonalPrism](http://www.vtk.org/doc/nightly/html/classvtkPentagonalPrism.html)  [vtkPolyhedron](http://www.vtk.org/doc/nightly/html/classvtkPolyhedron.html) [vtkPyramid](http://www.vtk.org/doc/nightly/html/classvtkPyramid.html) [vtkTetra](http://www.vtk.org/doc/nightly/html/classvtkTetra.html) [vtkVoxel](http://www.vtk.org/doc/nightly/html/classvtkVoxel.html) [vtkWedge](http://www.vtk.org/doc/nightly/html/classvtkWedge.html) [vtkUnstructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html) | Sample objects are generated from the classes derived from vtkCell3D and displayed.
[ColoredLines](/Python/GeometricObjects/Display/ColoredLines) | [vtkCellData](http://www.vtk.org/doc/nightly/html/classvtkCellData.html) [vtkLine](http://www.vtk.org/doc/nightly/html/classvtkLine.html) |
[Cone](/Python/GeometricObjects/Display/Cone) | [vtkConeSource](http://www.vtk.org/doc/nightly/html/classvtkConeSource.html) |
[Cube](/Python/GeometricObjects/Display/Cube) | [vtkCubeSource](http://www.vtk.org/doc/nightly/html/classvtkCubeSource.html) |
[Cylinder](/Python/GeometricObjects/Display/Cylinder) | [vtkCylinderSource](http://www.vtk.org/doc/nightly/html/classvtkCylinderSource.html) |
[DataSetSurface](/Python/GeometricObjects/Display/DataSetSurface) | [vtkDataSetSurfaceFilter](http://www.vtk.org/doc/nightly/html/classvtkDataSetSurfaceFilter.html) |
[Disk](/Python/GeometricObjects/Display/Disk) | [vtkDiskSource](http://www.vtk.org/doc/nightly/html/classvtkDiskSource.html) | A circle with a hole in it.
[Frustum](/Python/GeometricObjects/Display/Frustum) | [vtkFrustumSource](http://www.vtk.org/doc/nightly/html/classvtkFrustumSource.html) |
[GeometricObjectsDemo](/Python/GeometricObjects/Display/GeometricObjectsDemo) |  |
[Hexahedron](/Python/GeometricObjects/Display/Hexahedron)| [vtkHexahedron](http://www.vtk.org/doc/nightly/html/classvtkHexahedron.html) |
[LineSource](/Python/GeometricObjects/Display/LineSource) | [vtkLineSource](http://www.vtk.org/doc/nightly/html/classvtkLineSource.html) |
[LongLine](/Python/GeometricObjects/Display/LongLine) | [vtkLine](http://www.vtk.org/doc/nightly/html/classvtkLine.html) |
[OrientedArrow](/Python/GeometricObjects/Display/OrientedArrow) | [vtkArrowSource](http://www.vtk.org/doc/nightly/html/classvtkArrowSource.html) |
[Plane](/Python/GeometricObjects/Display/Plane)| [vtkPlaneSource](http://www.vtk.org/doc/nightly/html/classvtkPlaneSource.html) |
[PlanesIntersection](/Python/GeometricObjects/Display/PlanesIntersection)| [vtkPlanesIntersection](http://www.vtk.org/doc/nightly/html/classvtkPlanesIntersection.html) |
[Planes](/Python/GeometricObjects/Display/Planes)| [vtkPlanes](http://www.vtk.org/doc/nightly/html/classvtkPlanes.html), [vtkHull](http://www.vtk.org/doc/nightly/html/classvtkHull.html) | We create a convex hull of the planes for display purposes.
[PlatonicSolid](/Python/GeometricObjects/Display/PlatonicSolid) | [vtkPlatonicSolidSource](http://www.vtk.org/doc/nightly/html/classvtkPlatonicSolidSource.html) | All five platonic solids are displayed.
[PointSource](/Python/GeometricObjects/Display/PointSource) | [vtkPointSource](http://www.vtk.org/doc/nightly/html/classvtkPointSource.html) |
[Point](/Python/GeometricObjects/Display/Point) | [vtkPoints](http://www.vtk.org/doc/nightly/html/classvtkPoints.html) |
[PolyLine](/Python/GeometricObjects/Display/PolyLine) | [vtkPolyLine](http://www.vtk.org/doc/nightly/html/classvtkPolyLine.html) | This example demonstrates how to create a polygon through several ordered points.
[PolygonIntersection](/Python/GeometricObjects/Display/PolygonIntersection) | [vtkPolygon](http://www.vtk.org/doc/nightly/html/classvtkPolygon.html) | IntersectWithLine()
[Polygon](/Python/GeometricObjects/Display/Polygon) | [vtkPolygon](http://www.vtk.org/doc/nightly/html/classvtkPolygon.html) |
[Pyramid](/Python/GeometricObjects/Display/Pyramid) | [vtkPyramid](http://www.vtk.org/doc/nightly/html/classvtkPyramid.html) |
[Quad](/Python/GeometricObjects/Display/Quad) | [vtkQuad](http://www.vtk.org/doc/nightly/html/classvtkQuad.html) |
[RegularPolygonSource](/Python/GeometricObjects/Display/RegularPolygonSource) | [vtkRegularPolygonSource](http://www.vtk.org/doc/nightly/html/classvtkRegularPolygonSource.html) |
[Sphere](/Python/GeometricObjects/Display/Sphere) | [vtkSphereSource](http://www.vtk.org/doc/nightly/html/classvtkSphereSource.html) |
[Tetrahedron](/Python/GeometricObjects/Display/Tetrahedron) | [vtkTetra](http://www.vtk.org/doc/nightly/html/classvtkTetra.html) |
[TextActor](/Python/GeometricObjects/Display/TextActor)  | [vtkTextActor](http://www.vtk.org/doc/nightly/html/classvtkTextActor.html) | 2D "HUD-type" text
[TriangleStrip](/Python/GeometricObjects/Display/TriangleStrip) | [vtkTriangleStrip](http://www.vtk.org/doc/nightly/html/classvtkTriangleStrip.html) | 
[Triangle](/Python/GeometricObjects/Display/Triangle) | [vtkTriangle](http://www.vtk.org/doc/nightly/html/classvtkTriangle.html) |
[Vertex](/Python/GeometricObjects/Display/Vertex) | [vtkVertex](http://www.vtk.org/doc/nightly/html/classvtkVertex.html) |

### Parametric Objects

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[ParametricObjectsDemo](/Python/GeometricObjects/ParametricObjectsDemo) | [vtkParametricBoy](http://www.vtk.org/doc/nightly/html/classvtkParametricBoy.html), [vtkParametricConicSpiral](http://www.vtk.org/doc/nightly/html/classvtkParametricConicSpiral.html), [vtkParametricCrossCap](http://www.vtk.org/doc/nightly/html/classvtkParametricCrossCap.html), [vtkParametricDini](http://www.vtk.org/doc/nightly/html/classvtkParametricDini.html), [vtkParametricEllipsoid](http://www.vtk.org/doc/nightly/html/classvtkParametricEllipsoid.html), [vtkParametricEnneper](http://www.vtk.org/doc/nightly/html/classvtkParametricEnneper.html), [vtkParametricFigure8Klein](http://www.vtk.org/doc/nightly/html/classvtkParametricFigure8Klein.html), [vtkParametricKlein](http://www.vtk.org/doc/nightly/html/classvtkParametricKlein.html), [vtkParametricMobius](http://www.vtk.org/doc/nightly/html/classvtkParametricMobius.html), [vtkParametricRandomHills](http://www.vtk.org/doc/nightly/html/classvtkParametricRandomHills.html), [vtkParametricRoman](http://www.vtk.org/doc/nightly/html/classvtkParametricRoman.html), [vtkParametricSpline](http://www.vtk.org/doc/nightly/html/classvtkParametricSpline.html), [vtkParametricSuperEllipsoid](http://www.vtk.org/doc/nightly/html/classvtkParametricSuperEllipsoid.html), [vtkParametricSuperToroid](http://www.vtk.org/doc/nightly/html/classvtkParametricSuperToroid.html), [vtkParametricTorus](http://www.vtk.org/doc/nightly/html/classvtkParametricTorus.html)| Demonstration of of the vtkParametric classes added by Andrew Maclean. All the objects are displayed in a 4X4 array. 
[ParametricObjects](/Python/GeometricObjects/ParametricObjects) | | Uncomment the object that you wish to be displayed. |


## Implicit Functions

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[Boolean](/Python/Implicit/Boolean) | [vtkImplicitBoolean](http://www.vtk.org/doc/nightly/html/classvtkImplicitBoolean.html) | Demonstrate booleans of two different implicit functions
[Quadric](/Python/Implicit/Quadric) | [vtkQuadric](http://www.vtk.org/doc/nightly/html/classvtkQuadric.html) | Create an ellipsoid using an implicit quadric
[Sphere](/Python/Implicit/Sphere) | [vtkSphere](http://www.vtk.org/doc/nightly/html/classvtkSphere.html) | Demonstrate sampling of a sphere implicit function

## Working with PolyData

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[BooleanOperationPolyDataFilter](/Python/PolyData/BooleanOperationPolyDataFilter) | [vtkBooleanOperationPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkBooleanOperationPolyDataFilter.html) | This example performs a boolean operation (Intersection, Union, Difference) of two PolyData
[ColoredTriangle](/Python/ColoredTriangle) | [vtkTriangle](http://www.vtk.org/doc/nightly/html/classvtkTriangle.html) |
[CombinePolyData](/Python/Filtering/CombinePolyData) | [vtkAppendPolyData](http://www.vtk.org/doc/nightly/html/classvtkAppendPolyData.html) | This example combines Polydata objects, and displays the result to the screen.
[CurvaturesDemo](/Python/CurvaturesDemo) | [vtkCurvatures](http://www.vtk.org/doc/nightly/html/classvtkCurvatures.html),  [vtkColorTransferFunction](http://www.vtk.org/doc/nightly/html/classvtkColorTransferFunction.html)  | Demonstrates how to get the Gaussian and Mean curvatures of a surface.
[DottedLine](/Python/DottedLine) | vtkActor::GetProperty::SetLineStipplePattern |
[FilledPolygon](/Python/FilledPolygon) | [vtkCutter](http://www.vtk.org/doc/nightly/html/classvtkCutter.html) |
[ImplicitPolyDataDistance](/Python/PolyData/ImplicitPolyDataDistance) | [vtkImplicitPolyDataDistance](http://www.vtk.org/doc/nightly/html/classvtkImplicitPolyDataDistance.html) |
[IterativeClosestPoints](/Python/IterativeClosestPoints) | [vtkIterativeClosestPointTransform](http://www.vtk.org/doc/nightly/html/classvtkIterativeClosestPointTransform.html) |
[KochSnowflake](/Python/DataManipulation/KochSnowflake.py) | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html), [vtkCellArray](http://www.vtk.org/doc/nightly/html/classvtkCellArray.html), [vtkPoints](http://www.vtk.org/doc/nightly/html/classvtkPoints.html), [vtkPolyLine](http://www.vtk.org/doc/nightly/html/classvtkPolyLine.html) | This example draws a Koch snowflake fractal using recursive functions and some of the convenient tools in the toolkit.
[LineOnMesh](/Python/DataManipulation/LineOnMesh) | [vtkCellLocator](http://www.vtk.org/doc/nightly/html/classvtkCellLocator.html), [vtkParametricSpline](http://www.vtk.org/doc/nightly/html/classvtkParametricSpline.html) |
[MeshLabelImageColor](/Python/MeshLabelImageColor) | [vtkDiscreteMarchingCubes](http://www.vtk.org/doc/nightly/html/classvtkDiscreteMarchingCubes.html) |
[MeshLabelImage](/Python/MeshLabelImage) | [vtkDiscreteMarchingCubes](http://www.vtk.org/doc/nightly/html/classvtkDiscreteMarchingCubes.html) |
[Outline](/Python/Outline) | [vtkOutlineFilter](http://www.vtk.org/doc/nightly/html/classvtkOutlineFilter.html)|
[PolyDataContourToImageData](/Python/PolyData/PolyDataContourToImageData) | [vtkLinearExtrusionFilter](http://www.vtk.org/doc/nightly/html/classvtkLinearExtrusionFilter.html),[vtkPolyDataToImageStencil](http://www.vtk.org/doc/nightly/html/classvtkPolyDataToImageStencil.html) |
[PolyDataToImageDataStencil](/Python/PolyData/PolyDataToImageDataStencil) | [vtkPolyDataToImageStencil](http://www.vtk.org/doc/nightly/html/classvtkPolyDataToImageStencil.html) |
[RotationAroundLine](/Python/RotationAroundLine) | [vtkTransformPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkTransformPolyDataFilter.html)  |
[RuledSurfaceFilter](/Python/PolyData/RuledSurfaceFilter) | [vtkRuledSurfaceFilter](http://www.vtk.org/doc/nightly/html/classvtkRuledSurfaceFilter.html) |
[SolidColoredTriangle](/Python/SolidColoredTriangle) | [vtkTriangle](http://www.vtk.org/doc/nightly/html/classvtkTriangle.html) |
[SubdivisionFilters](/Python/PolyData/SubdivisionFilters) | [vtkLoopSubdivisionFilter](http://www.vtk.org/doc/nightly/html/classvtkLoopSubdivisionFilter.html) | [vtkButterflySubdivisionFilter](http://www.vtk.org/doc/nightly/html/classvtkButterflySubdivisionFilter.html) |
[TriangleColoredPoints](/Python/TriangleColoredPoints) | [vtkUnsignedCharArray](http://www.vtk.org/doc/nightly/html/classvtkUnsignedCharArray.html) |
[TriangleCornerVertices](/Python/TriangleCornerVertices) | [vtkCellArray](http://www.vtk.org/doc/nightly/html/classvtkCellArray.html) |
[TriangleCorners](/Python/TriangleCorners) | [vtkXMLPolyDataWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLPolyDataWriter.html) |
[WarpVectorpy](/Python/PolyData/WarpVector.py) | [vtkLine](http://www.vtk.org/doc/nightly/html/classvtkLine.html), [vtkDoubleArray](http://www.vtk.org/doc/nightly/html/classvtkDoubleArray.html), [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html), [vtkWarpVector](http://www.vtk.org/doc/nightly/html/classvtkWarpVector.html) | This example warps/deflects a line.
[WriteTriangleToFile](/Python/WriteTriangleToFile) | [vtkTriangle](http://www.vtk.org/doc/nightly/html/classvtkTriangle.html) |
[py](/Python/DataManipulation/Cube.py) | [vtkPolyData](http://www.vtk.org/doc/nightly/html/classvtkPolyData.html) |

## Working with 3D Data

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[ExtractSelection](/Python/PolyData/ExtractSelection) | [vtkExtractSelection](http://www.vtk.org/doc/nightly/html/classvtkExtractSelection.html) |
[ExtractSelectionCells](/Python/PolyData/ExtractSelectionCells) | [vtkExtractSelection](http://www.vtk.org/doc/nightly/html/classvtkExtractSelection.html) | extract cell, select cell |

### Working with Structured 3D Data
This section includes vtkImageData, vtkStructuredGrid, and vtkRectilinearGrid.

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[RectilinearGrid](/Python/RectilinearGrid/RectilinearGrid) | [vtkRectilinearGrid](http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html) |create a rectilinear grid

### Working with Meshes
This section includes examples of manipulating meshes.

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[ClipDataSetWithPolydata](/Python/Meshes/ClipDataSetWithPolydata) | [vtkClipDataSet](http://www.vtk.org/doc/nightly/html/classvtkClipDataSet.html), [vtkImplicitPolyDataDistance](http://www.vtk.org/doc/nightly/html/classvtkImplicitPolyDataDistance.html), [vtkRectilinearGrid](http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html) |clip a vtkRectilinearGrid with arbitrary polydata. In this example, use a vtkConeSource to generate polydata to slice the grid, resulting in an unstructured grid.

## Miscellaneous

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[BackgroundImage](/Python/BackgroundImage) | [vtkJPEGReader](http://www.vtk.org/doc/nightly/html/classvtkJPEGReader.html), [vtkImageCanvasSource2D](http://www.vtk.org/doc/nightly/html/classvtkImageCanvasSource2D.html), [vtkImageActor](http://www.vtk.org/doc/nightly/html/classvtkImageActor.html), [vtkSuperquadricSource](http://www.vtk.org/doc/nightly/html/classvtkSuperquadricSource.html) |
[Cutter](/Python/Cutter) | [vtkCutter](http://www.vtk.org/doc/nightly/html/classvtkCutter.html) |
[ImplicitDataSet](ImplicitDataSet](http://www.vtk.org/doc/nightly/html/classvtkImplicitDataSet.html)]( vtkIdType | n/a | This is just a typedef, Python, you can use a python "int" or "long" for vtkIdType.
[Screenshot](/Python/Screenshot) | [vtkWindowToImageFilter](http://www.vtk.org/doc/nightly/html/classvtkWindowToImageFilter.html) |
[Variant](/Python/Variant) | [vtkVariant](http://www.vtk.org/doc/nightly/html/classvtkVariant.html) |
[vtkVersion](/Python/vtkVersion) | [vtkVersion](http://www.vtk.org/doc/nightly/html/classvtkVersion.html) |

## Visualization

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[Animation](/Python/Animation) | [vtkTimerCallback](http://www.vtk.org/doc/nightly/html/classvtkTimerCallback.html) |
[AssignCellColorsFromLUT](/Python/Visualization/AssignCellColorsFromLUT) | [vtkNamedColors](http://www.vtk.org/doc/nightly/html/classvtkNamedColors.html), [vtkPlaneSource](http://www.vtk.org/doc/nightly/html/classvtkPlaneSource.html), [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html), [vtkColorTransferFunction](http://www.vtk.org/doc/nightly/html/classvtkColorTransferFunction.html) | Demonstrates how to assign colors to cells in a vtkPolyData structure using lookup tables.
[Camera](/Python/Camera) | [vtkCamera](http://www.vtk.org/doc/nightly/html/classvtkCamera.html) |
[ClampGlyphSizes](/Python/Visualization/ClampGlyphSizes) | [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html) | Use vtkGlyph3D with ClampingOn to limit glyph sizes
[ColorActor](/Python/ColorActor) | vtkActor::GetProperty()::SetColor |
[CubeAxesActor](/Python/Visualization/CubeAxesActor) | [vtkCubeAxesActor](http://www.vtk.org/doc/nightly/html/classvtkCubeAxesActor.html) | 
[CurvatureBandsWithGlyphs](/Python/Visualization/CurvatureBandsWithGlyphs) | [vtkCurvatures](http://www.vtk.org/doc/nightly/html/classvtkCurvatures.html), [vtkBandedPolyDataContourFilter](http://www.vtk.org/doc/nightly/html/classvtkBandedPolyDataContourFilter.html), [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html), [vtkColorSeries](http://www.vtk.org/doc/nightly/html/classvtkColorSeries.html), [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html) | Demonstrates the coloring of a surface by partitioning the gaussian curvature of a surface into bands and using arrows to display the normals on the surface.
[ElevationBandsWithGlyphs](/Python/Visualization/ElevationBandsWithGlyphs) | [vtkBandedPolyDataContourFilter](http://www.vtk.org/doc/nightly/html/classvtkBandedPolyDataContourFilter.html), [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html), [vtkColorSeries](http://www.vtk.org/doc/nightly/html/classvtkColorSeries.html), [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html) | Demonstrates the coloring of a surface by partitioning the elevation into bands and using arrows to display the normals on the surface.
[GlyphTable](/Python/Visualization/GlyphTable) | [vtkGlyph3D](http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html) | Vary the shapes of glyphed points using a glyph table
[HardwareSelector](/Python/Visualization/HardwareSelector) | [vtkHardwareSelector](http://www.vtk.org/doc/nightly/html/classvtkHardwareSelector.html) |
[InteractorStyleTrackballActor](/Python/InteractorStyleTrackballActor) | [vtkInteractorStyleTrackBallActor](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackBallActor.html) |
[InteractorStyleTrackballCamera](/Python/InteractorStyleTrackballCamera) | [vtkInteractorStyleTrackBallCamera](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackBallCamera.html) |
[MultipleViewports](/Python/MultipleViewports) | vtkRenderer::SetViewport |
[NamedColorPatches](/Python/Visualization/NamedColorPatches) | [vtkNamedColors](http://www.vtk.org/doc/nightly/html/classvtkNamedColors.html) | Creates a HTML file called [VTKNamedColorPatches](Python/Visualization/VTKNamedColorPatches_html) showing the available colors in the vtkNamedColors class.
[NamedColors](/Python/Visualization/NamedColors) | [vtkNamedColors](http://www.vtk.org/doc/nightly/html/classvtkNamedColors.html) | Demonstrates how to use the vtkNamedColor class
[PointDataSubdivision](/Python/Visualization/PointDataSubdivision) | [vtkLinearSubdivisionFilter](http://www.vtk.org/doc/nightly/html/classvtkLinearSubdivisionFilter.html) [vtkButterflySubdivisionFilter](http://www.vtk.org/doc/nightly/html/classvtkButterflySubdivisionFilter.html) | Demonstrates the effect of applying these filters on various sources.
[PointSize](/Python/Visualization/PointSize) | vtkActor::GetProperty()::SetPointSize |
[ProgGlyph](/Python/Visualization/ProgGlyph) | [vtkProgrammableGlyphFilter](http://www.vtk.org/doc/nightly/html/classvtkProgrammableGlyphFilter.html) | Vary the shapes of glyphed points using a programmable glyph filter
[QuadraticSurface](/Python/Visualization/QuadraticSurface) | [vtkQuadric](http://www.vtk.org/doc/nightly/html/classvtkQuadric.html) |
[SphereTexture](/Python/Visualization/SphereTexture) | [vtkTextureMapToSphere](http://www.vtk.org/doc/nightly/html/classvtkTextureMapToSphere.html) | Apply an ImageData texture to an sphere
[Streamlines](/Python/Visualization/Streamlines) | [vtkStreamLine](http://www.vtk.org/doc/nightly/html/classvtkStreamLine.html) | Seed streamlines with vectors from a structured grid
[TextSource](/Python/TextSource) | [vtkTextSource](http://www.vtk.org/doc/nightly/html/classvtkTextSource.html) |
[UnstructuredTransientVolumeRendering](/Python/UnstructuredTransientVolumeRendering) | [vtkUnstructuredGridVolumeRayCastMapper](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGridVolumeRayCastMapper.html) |
[WindowTitle](/Python/WindowTitle) | vtkRenderWindow::SetWindowName |

## Working with vtkImageData

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[ImageWeightedSum](/Python/ImageWeightedSum) | [vtkImageWeightedSum](http://www.vtk.org/doc/nightly/html/classvtkImageWeightedSum.html) |
[SumVTKImages](/Python/SumVTKImages) | [vtkImageWeightedSum](http://www.vtk.org/doc/nightly/html/classvtkImageWeightedSum.html) | A function to simplify the summing of images, where you can pass a list of images and 
[WriteReadVtkImageData](/Python/WriteReadVtkImageData) | [vtkImageData](http://www.vtk.org/doc/nightly/html/classvtkImageData.html), [vtkXMLImageDataReader](http://www.vtk.org/doc/nightly/html/classvtkXMLImageDataReader.html), [vtkXMLImageDataWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLImageDataWriter.html) |
weights.

## Working with ExodusII Data

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[Read](/Python/ExodusII/Read) | [vtkExodusIIReader](http://www.vtk.org/doc/nightly/html/classvtkExodusIIReader.html) | A simple script for reading and viewing ExodusII data interactively.

## Graphs

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[EdgeWeights](/Python/Graphs/EdgeWeights)  | [vtkMutableDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html), [vtkGraphLayoutView](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html) | 
[NOVCAGraph](/Python/Graphs/NOVCAGraph)  | [vtkUnstructuredGrid](http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html), [vtkXMLUnstructuredGridWriter](http://www.vtk.org/doc/nightly/html/classvtkXMLUnstructuredGridWriter.html) | 
[SelectedVerticesAndEdges](/Python/Graphs/SelectedVerticesAndEdges)  | [vtkAnnotationLink](http://www.vtk.org/doc/nightly/html/classvtkAnnotationLink.html), [vtkGraphLayoutView](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html) | 
[VisualizeGraph](/Python/Graphs/VisualizeGraph)  | [vtkMutableDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html), [vtkGraphLayoutView](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html) | 

## User Interaction

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[HighlightAPickedActor](/Python/Interaction/HighlightAPickedActor) | [vtkPropPicker](http://www.vtk.org/doc/nightly/html/classvtkPropPicker.html), [vtkInteractorStyleTrackballCamera](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballCamera.html) | Pick and highlight an actor based on mouse clicks.
[MouseEventsObserver](/Python/Interaction/MouseEventsObserver) | [vtkCallbackCommand](http://www.vtk.org/doc/nightly/html/classvtkCallbackCommand.html) | Use an observer.
[MouseEvents](/Python/Interaction/MouseEvents) | [vtkInteractorStyleTrackballCamera](http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballCamera.html) | Subclass the interactor style.

## Infovis

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[ParallelCoordinatesExtraction](/Python/Infovis/ParallelCoordinatesExtraction)  | [vtkExtractSelection](http://www.vtk.org/doc/nightly/html/classvtkExtractSelection.html), [vtkAnnotationLink](http://www.vtk.org/doc/nightly/html/classvtkAnnotationLink.html) | Extract data based on a selection in a Parallel Coordinates View
[ParallelCoordinatesView](/Python/Infovis/ParallelCoordinatesView)  | [vtkRTAnalyticSource](http://www.vtk.org/doc/nightly/html/classvtkRTAnalyticSource.html), [vtkParallelCoordinatesView](http://www.vtk.org/doc/nightly/html/classvtkParallelCoordinatesView.html), [vtkParallelCoordinatesRepresentation](http://www.vtk.org/doc/nightly/html/classvtkParallelCoordinatesRepresentation.html) | Plotting data attributes in a Parallel Coordinates View
[ScatterPlot](/Python/Plotting/ScatterPlot)  | [vtkChartXY](http://www.vtk.org/doc/nightly/html/classvtkChartXY.html) | 
[SelectedGraphIDs](/Python/Infovis/SelectedGraphIDs)  | [vtkAnnotationLink](http://www.vtk.org/doc/nightly/html/classvtkAnnotationLink.html), [vtkRandomGraphSource](http://www.vtk.org/doc/nightly/html/classvtkRandomGraphSource.html), [vtkGraphLayoutView](http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html) | Callback on vtkAnnotationLink in a Graph Layout View when selection is changed
[SpiderPlot](/Python/Plotting/SpiderPlot)  | [vtkSpiderPlotActor](http://www.vtk.org/doc/nightly/html/classvtkSpiderPlotActor.html) | 

## Geovis

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[GeoAssignCoordinates](/Python/Geovis/GeoAssignCoordinates) | [vtkGeoAssignCoordinates](http://www.vtk.org/doc/nightly/html/classvtkGeoAssignCoordinates.html), [vtkMutableDirectedGraph](http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html), [vtkGraphMapper](http://www.vtk.org/doc/nightly/html/classvtkGraphMapper.html) | Draws a sphere, based on longituds and latitudes.

## Widgets

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[BalloonWidget](/Python/Widgets/BalloonWidget) | [vtkBalloonWidget](http://www.vtk.org/doc/nightly/html/classvtkBalloonWidget.html), [vtkBalloonRepresentation](http://www.vtk.org/doc/nightly/html/classvtkBalloonRepresentation.html) | Uses a vtkBalloonWidget to draw labels when the mouse stays above an actor.
[BoxWidget](/Python/Widgets/BoxWidget) | [vtkBoxWidget](http://www.vtk.org/doc/nightly/html/classvtkBoxWidget.html) | This 3D widget defines a region of interest that is represented by an arbitrarily oriented hexahedron with interior face angles of 90 degrees (orthogonal faces). The object creates 7 handles that can be moused on and manipulated.
[CompassWidget](/Python/Widgets/CompassWidget) | [vtkCompassWidget](http://www.vtk.org/doc/nightly/html/classvtkCompassWidget.html), [vtkCompassRepresentation](http://www.vtk.org/doc/nightly/html/classvtkCompassRepresentation.html) | Draws an interactive compass.
[ContourWidget](/Python/Widgets/ContourWidget) | [vtkContourWidget](http://www.vtk.org/doc/nightly/html/classvtkContourWidget.html), [vtkOrientedGlyphContourRepresentation](http://www.vtk.org/doc/nightly/html/classvtkOrientedGlyphContourRepresentation.html) | Draw a contour (line) which can be deformed by the user
[OrientationMarkerWidget](/Python/Widgets/OrientationMarkerWidget) | [vtkAnnotatedCubeActor](http://www.vtk.org/doc/nightly/html/classvtkAnnotatedCubeActor.html) [vtkOrientationWidget](http://www.vtk.org/doc/nightly/html/classvtkOrientationWidget.html) | Draws two cubes. One of them can be clicked to be rotated, and will rotate the second one. The second one has annotations on it, and can also be moved.
[ScalarBarWidget](/Python/Widgets/ScalarBarWidget) | [vtkScalarBarWidget](http://www.vtk.org/doc/nightly/html/classvtkScalarBarWidget.html) | The ScalarBarWidget displays a scalar bar that is movable and changes orientation automatically when close to the borders of the image. It needs a ScalarBarActor
[SphereWidget](/Python/Widgets/SphereWidget) | [vtkSphereWidget](http://www.vtk.org/doc/nightly/html/classvtkSphereWidget.html) | This 3D widget defines a sphere that can be interactively placed in a scene.
[TextWidget](/Python/Widgets/TextWidget) | [vtkTextWidget](http://www.vtk.org/doc/nightly/html/classvtkTextWidget.html) | Annotate a VTK image with movable text

## Utilities

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[Delaunay2D](/Python/Filtering/Delaunay2D) | [vtkDelaunay2D](http://www.vtk.org/doc/nightly/html/classvtkDelaunay2D.html) |
[LUTUtilities](/Python/Utilities/LUTUtilities) | [vtkLookupTable](http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html) [vtkColorSeries](http://www.vtk.org/doc/nightly/html/classvtkColorSeries.html) | A utility class for vtkLookupTable allowing you to output the table contents or to compare tables.|

## Web

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[RemoteRenderer](/Python/Web/RemoteRenderer) | Web/Python | Use vtk to show an interactive visualization on a web page. Remote rendering. |

## PyQt

| Example Name | Classes Demonstrated | Description |
|--------------|----------------------|-------------|
[EmbedPyQt](/Python/Widgets/EmbedPyQt) | [vtkRenderWindowInteractor](http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html) | Shows how to easily embed VTK in PyQt with QVTKRenderWindowInteractor, first example
[EmbedPyQt2](/Python/Widgets/EmbedPyQt2) | [vtkRenderWindowInteractor](http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html) | Shows how to embed VTK in PyQt with QVTKRenderWindowInteractor, second example
