# Python Examples

Please see [this page](https://www.vtk.org/Wiki/VTK/PythonDevelopment) to learn how to setup your environment to use VTK in Python.

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

###### Importers

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[3DSImporter](/Python/IO/3DSImporter) | vtk3DSImporter | Import a 3D Studio scene that includes multiple actors.


## Working with Arrays

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[GetValues](/Python/Arrays/GetValues) | GetTuple3 |
[RenameArray](/Python/Arrays/RenameArray) | SetName |

### Image Format

#### Output

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ImageWriter](/Python/IO/ImageWriter) | vtkBMPWriter vtkJPEGWriter vtkPNMWriter vtkPostScriptWriter vtkTIFFWriter vtkPNGWriter vtkWindowToImageFilter | Write an imagefile based on the file extension.

## Geometric Objects

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[SourceObjectsDemo](/Python/GeometricObjects/SourceObjectsDemo) | vtkSphereSource vtkConeSource vtkCylinderSource vtkCubeSource vtkPlaneSource vtkTextSource vtkPointSource vtkDiskSource vtkLineSource | Examples of source objects that procedurally generate polygonal models.  These nine images represent just some of the capability of VTK. From upper left in reading order: sphere, cone, cylinder, cube, plane, text, random point cloud, disk (with or without hole), and line source. Other polygonal source objects are available; check subclasses of vtkPolyDataAlgorithm.

### Display

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Arrow](/Python/GeometricObjects/Arrow) | vtkArrowSource |
[Axes](/Python/GeometricObjects/Axes) | vtkAxesActor |
[Cell3DDemonstration](/Python/GeometricObjects/Cell3DDemonstration) | vtkHexagonalPrism vtkHexahedron vtkPentagonalPrism  vtkPolyhedron vtkPyramid vtkTetra vtkVoxel vtkWedge vtkUnstructuredGrid | Sample objects are generated from the classes derived from vtkCell3D and displayed.
[ColoredLines](/Python/GeometricObjects/ColoredLines) | vtkCellData vtkLine |
[Cone](/Python/GeometricObjects/Cone) | vtkConeSource |
[Cube](/Python/GeometricObjects/Cube)   | vtkCubeSource |
[Cube1](/Python/GeometricObjects/Cube1) | vtkCubeSource |
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
[TessellatedBoxSource](/Python/GeometricObjects/TessellatedBoxSource)   | vtkTessellatedBoxSource | Generate a box with tessellated sides.
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
[Boolean](/Python/ImplicitFunctions/Boolean) | vtkImplicitBoolean | Demonstrate booleans of two different implicit functions
[CutWithScalars](/Python/VisualizationAlgorithms/CutWithScalars) | vtkContourFilter | Cut a surface with scalars.
[ExtractData](/Python/VisualizationAlgorithms/ExtractData) | vtkSampleFunction | Implicit functions used to select data: Two ellipsoids are combined using the union operation used to select voxels from a volume. Voxels are shrunk 50 percent. 
[Hello](/Python/VisualizationAlgorithms/Hello) | vtkImplicitModeller | Implicit modelling used to thicken a stroked font.
[IceCream](/Python/VisualizationAlgorithms/IceCream) | vtkImplicitBoolean vtkSampleFunction | How to use boolean combinations of implicit functions to create a model of an ice cream cone.
[ImplicitDataSet](/Python/ImplicitFunctions/ImplicitDataSet) | vtkImplicitDataSet | A cube is used to define an implicit function (through vtkImplicitDataSet) which is then used to clip a sphere.
[ImplicitSphere](/Python/ImplicitFunctions/ImplicitSphere) | vtkSphere | An implicit representation of a sphere.
[Lorenz](/Python/Visualization/Lorenz) | vtkContourFilter | Visualizing a Lorenz strange attractor by integrating the Lorenz equations in a volume.
[MarchingCases](/Python/VisualizationAlgorithms/MarchingCases) | vtkMarchingCubes | Explore the Marching Cubes cases.
[Quadric](/Python/ImplicitFunctions/Quadric) | vtkQuadric | Create an ellipsoid using an implicit quadric
[Sphere](/Python/ImplicitFunctions/Sphere) | vtkSphere | Demonstrate sampling of a sphere implicit function

## Working with PolyData

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[BooleanOperationPolyDataFilter](/Python/PolyData/BooleanOperationPolyDataFilter) | vtkBooleanOperationPolyDataFilter | This example performs a boolean operation (Intersection, Union, Difference) of two PolyData
[ColoredTriangle](/Python/PolyData/ColoredTriangle) | vtkTriangle | Creates a file TriangleColored.vtp.
[CombinePolyData](/Python/Filtering/CombinePolyData) | vtkAppendPolyData | This example combines Polydata objects, and displays the result to the screen.
[Cube](/Python/DataManipulation/Cube) | vtkPolyData |
[CurvaturesDemo](/Python/PolyData/CurvaturesDemo) | vtkCurvatures  vtkColorTransferFunction  | Demonstrates how to get the Gaussian and Mean curvatures of a surface.
[FilledPolygon](/Python/PolyData/FilledPolygon) | vtkCutter |
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
[Bottle](/Python/Modelling/Bottle) | vtkRotationalExtrusionFilter | Rotationally symmetric objects.
[ExtractSelection](/Python/PolyData/ExtractSelection) | vtkExtractSelection |
[ExtractSelectionCells](/Python/PolyData/ExtractSelectionCells) | vtkExtractSelection | Extract cell, select cell.
[Spring](/Python/Modelling/Spring) | vtkRotationalExtrusionFilter | Rotation in combination with linear displacement and radius variation.

### Working with Structured 3D Data
This section includes vtkImageData, vtkStructuredGrid, and vtkRectilinearGrid.

#### vtkImageData

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ImageWeightedSum](/Python/ImageData/ImageWeightedSum) | vtkImageWeightedSum |Add two or more images.

#### vtkStructuredGrid

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[SGrid](/Python/StructuredGrid/SGrid) | vtkStructuredGrid | Creating a structured grid dataset of a semi-cylinder. Vectors are created whose magnitude is proportional to radius and oriented in tangential direction.

#### vtkStructuredPoints

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[Vol](/Python/StructuredPoints/Vol) | vtkStructuredPoints vtkContourFilter| Creating a image data dataset. Scalar data is generated from the equation for a sphere. Volume dimensions are 26 x 26 x 26.


#### vtkRectilinearGrid

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[RectilinearGrid](/Python/RectilinearGrid/RectilinearGrid) | vtkRectilinearGrid |create a rectilinear grid
[RGrid](/Python/RectilinearGrid/RGrid) | vtkRectilinearGrid | Creating a rectilinear grid dataset. The coordinates along each axis are defined using an instance of vtkDataArray.

### Working with Unstructured 3D Data
This section includes vtkUnstructuredGrid.

#### vtkUnstructuredGrid
| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[UGrid](/Python/UnstructuredGrid/UGrid) | vtkUnstructuredGrid | Creation of an unstructured grid.

### Working with Meshes
This section includes examples of manipulating meshes.

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ClipDataSetWithPolydata](/Python/Meshes/ClipDataSetWithPolydata) | vtkClipDataSet vtkImplicitPolyDataDistance vtkRectilinearGrid |clip a vtkRectilinearGrid with arbitrary polydata. In this example, use a vtkConeSource to generate polydata to slice the grid, resulting in an unstructured grid.
[DelaunayMesh](/Python/Modelling/DelaunayMesh)| vtkDelaunay2D vtkMinimalStandardRandomSequence vtkExtractEdges vtkGlyph3D vtkTubeFilter | Two-dimensional Delaunay triangulation of a random set of points. Points and edges are shown highlighted with sphere glyphs and tubes.

## Rendering
| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[CameraBlur](/Cxx/Rendering/CameraBlur) | | Example of a scene rendered with focal depth.
[ColoredSphere](/Python/Rendering/ColoredSphere) | vtkSphereSource vtkElevationFilter | A simple sphere.
[Cone3](/Python/Rendering/Cone3) | vtkRenderWindow | Four frames of output, based on the VTK example Cone3.py.
[Cone4](/Python/Rendering/Cone4) | vtkRenderWindow | Modifying properties and transformation matrix based on the VTK example Cone4.py.
[DottedLine](/Python/Rendering/DottedLine) | | This needs a re-work, see StippledLine.cxx 
[FlatVersusGouraud](/Python/Rendering/FlatVersusGouraud) | vtkProperty::SetInterpolationToFlat vtkProperty::SetInterpolationToGouraud | Flat and Gouraud shading. Different shading methods can dramatically improve the look of an object represented with polygons. On the top, flat shading uses a constant surface normal across each polygon. On the bottom, Gouraud shading interpolates normals from polygon vertices to give a smoother look.
[Mace](/Python/Rendering/Mace) | | An example of multiple inputs and outputs.
[Model](/Python/Rendering/Model) | vtkRenderer vtkRenderWindow vtkRenderWindowInteractor | Illustrative diagram of graphics objects.
[MotionBlur](/Python/Rendering/MotionBlur) | vtkRenderStepsPass vtkSimpleMotionBlurPass | Example of motion blur.
[Rainbow](/Python/Rendering/Rainbow)| vtkLookupTable | Use and manipulation of vtkLookupTables.
[Rotations](/Python/Rendering/Rotations)| vtkActor::RotateX,Y,Z vtkRenderer::EraseOff | Rotations of a cow about her axes.
[SpecularSpheres](/Python/Rendering/SpecularSpheres)| vtkProperty |Demonstrates the effect of specular lighting on spheres.
[TransformSphere](/Python/Rendering/TransformSphere) | vtkSphereSource vtkElevationFilter vtkTransform vkTransformFilter | The addition of a transform filter to [ColoredSphere](/Python/Rendering/ColoredSphere).
[WalkCow](/Python/Rendering/WalkCow) | vtkBYUReader renWin::EraseOff() vtkActor | This generates Figs. 3-31, 3-32, 3-33 found in VTKTextbook.pdf.

## Texture Mapping
| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[AnimateVectors](/Python/Texture/AnimateVectors) | vtkTexture vtkGlyph3D | One frame from a vector field animation using texture maps.
[TexturePlane](/Python/Texture/TexturePlane) | vtkTexture | Example of texture mapping.
[TextureThreshold](/Python/Texture/TextureThreshold)| vtkTexture vtkThresholdTextureCoords vtkStructuredGridGeometryFilter | Demonstrate the use of scalar thresholds to show values of flow density on three planes.

## Visualization

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[AlphaFrequency](/Python/Visualization/AlphaFrequency) | vtkLinearExtrusionFilter vtkVectorText | Linearly extrude fonts to show letter frequencies in text.
[AnatomicalOrientation](/Python/VisualizationAlgorithms/AnatomicalOrientation)| vtkAnnotatedCubeActor vtkAxesActor vtkOrientationMarkerWidget vtkTransform | Show a labelled set of anatomical planes transecting a human figure.
[AssignCellColorsFromLUT](/Python/Visualization/AssignCellColorsFromLUT) | vtkNamedColors vtkPlaneSource vtkLookupTable vtkColorTransferFunction | Demonstrates how to assign colors to cells in a vtkPolyData structure using lookup tables.
[Blow](/Python/Visualization/Blow)| vtkUnstructuredGridReader vtkWarpVector vtkConnectivityFilter | Ten frames from a blow molding finite element analysis.
[BluntStreamlines](/Python/VisualizationAlgorithms/BluntStreamlines) | vtkStructuredGridGeometryFilter vtkStreamTracer| Demonstrates airflow around a blunt fin using streamlines.
[Camera](/Python/Visualization/Camera) | vtkCamera | Positioning and aiming the camera.
[CameraModel1](/Python/Visualization/CameraModel1) | vtkCameraActor | Illustrate camera movement.
[CameraModel2](/Python/Visualization/CameraModel2) | vtkCameraActor | Illustrate camera movement.
[CarotidFlow](/Python/VisualizationAlgorithms/CarotidFlow) | vtkStreamTracer vtkThresholdPoints | Visualizing blood flow in the human carotid arteries. Streamtubes of flow velocity are generated.
[CarotidFlowGlyphs](/Python/VisualizationAlgorithms/CarotidFlowGlyphs) | vtkGlyph3D vtkThresholdPoints | Visualizing blood flow in human carotid arteries. Cone glyphs indicate flow direction and magnitude.
[ClampGlyphSizes](/Python/Visualization/ClampGlyphSizes) | vtkGlyph3D | Use vtkGlyph3D with ClampingOn to limit glyph sizes
[ColorActor](/Python/Visualization/ColorActor) | vtkActor::GetProperty()::SetColor | Colour the actor.
[CombustorIsosurface](/Python/VisualizationAlgorithms/CombustorIsosurface) | vtkContourFilter | Marching cubes surface of flow density.
[ComplexV](/Python/Visualization/ComplexV) | vtkHedgeHog | ComplexV from the VTK Textbook.
[ContourQuadric](/Python/VisualizationAlgorithms/ContourQuadric) | vtkQuadric vtkSampleFunction vtkContourFilter | Contouring a quadric function.
[CubeAxesActor](/Python/Visualization/CubeAxesActor) | vtkCubeAxesActor | 
[CurvatureBandsWithGlyphs](/Python/Visualization/CurvatureBandsWithGlyphs) | vtkCurvatures vtkBandedPolyDataContourFilter vtkLookupTable vtkColorSeries vtkGlyph3D | Demonstrates the coloring of a surface by partitioning the gaussian curvature of a surface into bands and using arrows to display the normals on the surface.
[CutStructuredGrid](/Python/VisualizationAlgorithms/CutStructuredGrid) | vtkCutter | Cut through structured grid with plane. The cut plane is shown solid shaded. A computational plane of constant k value is shown in wireframe for comparison. The colors correspond to flow density. Cutting surfaces are not necessarily planes: implicit functions such as spheres, cylinders, and quadrics can also be used.
[Cutter](/Python/VisualizationAlgorithms/Cutter) | vtkCutter |
[DisplacementPlot](/Python/VisualizationAlgorithms/DisplacementPlot) | vtkColorTransferFunction vtkWarpVector vtkVectorDot | Show modal lines for a vibrating beam.
[ElevationBandsWithGlyphs](/Python/Visualization/ElevationBandsWithGlyphs) | vtkBandedPolyDataContourFilter vtkLookupTable vtkColorSeries vtkGlyph3D | Demonstrates the coloring of a surface by partitioning the elevation into bands and using arrows to display the normals on the surface.
[GlyphTable](/Python/Visualization/GlyphTable) | vtkGlyph3D | Vary the shapes of glyphed points using a glyph table
[Hanoi](/Python/Visualization/Hanoi)|  | Towers of Hanoi.
[Hawaii](/Python/Visualization/Hawaii)| vtkElevationFilter vtkColorSeries vtkLookupTable | Visualize elevations by coloring the scalar values with a lookup table.
[HardwareSelector](/Python/Visualization/HardwareSelector) | vtkHardwareSelector |
[HeadBone](/Python/VisualizationAlgorithms/HeadBone) | vtkMarchingCubes | Marching cubes surface of human bone.
[HeadSlice](/Python/VisualizationAlgorithms/HeadSlice) | vtkContourFilter | Marching squares used to generate contour lines.
[InteractorStyleTrackballActor](/Python/Visualization/InteractorStyleTrackballActor) | vtkInteractorStyleTrackBallActor |
[InteractorStyleTrackballCamera](/Python/Visualization/InteractorStyleTrackballCamera) | vtkInteractorStyleTrackBallCamera |
[IronIsoSurface](/Python/VisualizationAlgorithms/IronIsoSurface) | vtkContourFilter | Marching cubes surface of iron-protein.
[Kitchen](/Python/Visualization/Kitchen) | vtkStreamTracer vtkStructuredGrid| Demonstrates stream tracing in a kitchen.
[LoopShrink](/Python/Visualization/LoopShrink) | |  A network with a loop. VTK 5.0 does not allow you to execute a looping visualization network; this was possible in previous versions of VTK.
[Motor](/Python/VisualizationAlgorithms/Motor) | vtkBYUReader vtkStructuredPointsReader vtkTexture vtkImplicitTextureCoords | Texture cut used to reveal internal structure of a motor. Two cut planes are used in combination with transparent texture.
[MultipleViewports](/Python/Visualization/MultipleViewports) | vtkRenderer::SetViewport |
[NamedColors](/Python/Visualization/NamedColors) | vtkNamedColors | Demonstrates how to use the vtkNamedColors class.
[NamedColorPatches](/Python/Visualization/NamedColorPatches) | vtkNamedColors | Creates a HTML file called [VTKNamedColorPatches](http://htmlpreview.github.com/?https://github.com/lorensen/VTKExamples/blob/master/src/Python/Visualization/VTKNamedColorPatches.html)
[Office](/Python/VisualizationAlgorithms/Office) | vtkPointSource vtkStreamTracer | Using random point seeds to create streamlines.
[OfficeTube](/Python/VisualizationAlgorithms/OfficeTube) | vtkStreamTracer vtkTubeFilter | The stream polygon. Sweeping a polygon to form a tube.
[OrientedGlyphs](/Python/Visualization/OrientedGlyphs)| vtkGlyph3D|Create oriented glyphs from vector data.
[PineRootConnectivity](/Python/VisualizationAlgorithms/PineRootConnectivity) | vtkMCubesReader vtkPolyDataConnectivityFilter | Applying the connectivity filter to remove noisy isosurfaces.
[PineRootDecimation](/Python/VisualizationAlgorithms/PineRootDecimation) | vtkMCubesReader vtkDecimatePro vtkConnectivityFilter | Applying the decimation and connectivity filters to remove noisy isosurfaces and reduce data size.
[PlateVibration](/Python/VisualizationAlgorithms/PlateVibration) | vtkWarpVector vtkVectorDot | Demonstrates the motion of a vibrating beam.
[PointDataSubdivision](/Python/Visualization/PointDataSubdivision) |  vtkLinearSubdivisionFilter | Vary the shapes of glyphed points using a programmable glyph filter
[PseudoVolumeRendering](/Python/VolumeRendering/PseudoVolumeRendering) | vtkCutter vtkContourFilter | 100 cut planes with opacity of 0.05. Rendered back-to-front to simulate volume rendering.
[QuadraticSurface](/Python/Visualization/QuadraticSurface) | vtkQuadric |
[QuadricVisualization](/Python/Visualization/QuadricVisualization) | vtkQuadric vtkSampleFunction vtkContourFilter | Visualizing a quadric function.
[SpikeFran](/Python/VisualizationAlgorithms/SpikeFran) | vtkGlyph3D | Glyphs indicate surface normals on model of human face. Glyph positions are randomly selected.
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
[BackgroundImage](/Python/Images/BackgroundImage) | vtkJPEGReader vtkImageCanvasSource2D vtkImageActor vtkSuperquadricSource | Display an image as the "background" of a scene, and render a superquadric in front of it.

## Image Processing

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[ImageWarp](/Python/Images/ImageWarp)| vtkBMPReader vtkImageLuminance vtkWarpScalar vtkMergeFilter | Combine the imaging and visualization pipelines to deform an image in the z-direction. The vtkMergeFilter is used to combine the warped surface with the original color data.
[ImageGradient](/Python/VisualizationAlgorithms/ImageGradient)| vtkImageMagnify vtkImageGaussianSmooth vtkImageGradient vtkImageEuclideanToPolar vtkImageExtractComponents vtkImageHSVToRGB | Create an imaging pipeline to visualize gradient information.

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

## Volume Rendering


| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[SimpleRayCast](/Python/VolumeRendering/SimpleRayCast) | vtkFixedPointVolumeRayCastMapper | Volume rendering of a high potential iron protein.

## User Interaction

| Example Name | Classes Demonstrated | Description | Image |
|--------------|----------------------|-------------|-------|
[CallBack](/Python/Interaction/CallBack)| vtkCallbackCommand vtkOrientationMarkerWidget | Setting up a callback with client data. Two different methods are demonstrated.
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
