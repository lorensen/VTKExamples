# Java Examples

Click [here](http://www.vtk.org/Wiki/VTK/Tutorials/JavaEnvironmentSetup) for a tutorial on setting up your Java environment.

It would be appreciated if there are any Java VTK experts who could convert any of the [c++ examples](/Cxx) to Java!

!!! info
    [This table](/Coverage/JavaVTKClassesUsed.md) shows the VTK classes covered by the examples.

!!! info
    [This table](/Coverage/JavaVTKClassesNotUsed.md) shows VTK classes that do not have an example. Please add examples in your area of expertise!

## Hello World

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[A hello world example](/Java/GeometricObjects/CylinderExample) | vtkPolyDataMapper vtkActor vtkRenderer vtkRenderWindow vtkRenderWindowInteractor |  Cylinder example from the VTK Textbook and source code. A hello world example.

## Annotation

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[TextOrigin](/Java/Annotation/TextOrigin) | vtkTextOrigin | TextOrigin
[MultiLineText](/Java/Annotation/MultiLineText) | vtkMultiLineText | MultiLineText

## CompositeData

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[CompositePolyDataMapper](/Java/CompositeData/CompositePolyDataMapper) | vtkCompositePolyDataMapper | CompositePolyDataMapper

## Filtering

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Delaunay2D](/Java/Filtering/Delaunay2D) | vtkDelaunay2D | An example to generate set of points and to triangulate using Delaunay2D
[Glyph2D](/Java/Filtering/Glyph2D) | vtkGlyph2D | Example to copy a polydata to everypoint in the input set. 
[Glyph3D](/Java/Filtering/Glyph3D) | vtkGlyph3D | This example applies an object at every point using vtkGlyph3D
[PerlinNoise](/Java/Filtering/PerlinNoise) | vtkPerlinNoise | An implicit function that implements Perlin noise.
[TransformPolyData](/Java/Filtering/TransformPolyData) | vtkTransformPolyDataFilter | Transforms points, associated normals and vectors for polygonal dataset
[VertexGlyphFilter](/Java/Filtering/VertexGlyphFilter) | vtkVertexGlyphFilter | Creates a set of points and adds a vertex at each point.
[WarpTo](/Java/Filtering/WarpTo) | vtkWarpTo | Deform geometry by warping towards a point

## GeometricObjects

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Arrow](/Java/GeometricObjects/Arrow) | vtkArrow | Arrow Visualization
[Circle](/Java/GeometricObjects/Circle) | vtkCircle |Circle Visualization
[Cone](/Java/GeometricObjects/Cone) | vtkCone | Cone Visualization
[EllipticalCylinder](/Java/GeometricObjects/EllipticalCylinder) | vtkEllipticalCylinder | EllipticalCylinder
[ConvexPointSet](/Java/GeometricObjects/ConvexPointSet) | vtkConvexPointSet | ConvexPointSet Visualization
[Frustum](/Java/GeometricObjects/Frustum) | vtkFrustum | Frustum Visualization
[Disk](/Java/GeometricObjects/Disk) | vtkDiskSource | Disk Visualization
[Line](/Java/GeometricObjects/Line) | vtkLineSource | Line Visualization
[LongLine](/Java/GeometricObjects/LongLine) | vtkLine | A visualization of a long line
[OrientedCylinder](/Java/GeometricObjects/OrientedCylinder) | vtkOrientedCylinder |Oriented Cylinder visualization
[OrientedArrow](/Java/GeometricObjects/OrientedArrow) | vtkOrientedArrow | Oriented Arrow visualization.
[Polygon](/Java/GeometricObjects/Polygon) | vtkPolygon | Polygon Visualization
[PlanesIntersection](/Java/GeometricObjects/PlanesIntersection) | vtkPlanesIntersection | PlanesIntersection
[RegularPolygonSource](/Java/GeometricObjects/RegularPolygonSource) | vtkRegularPolygonSource| RegularPolygon Visualization
[ParametricObjects](/Java/GeometricObjects/ParametricObjects) | vtkParametricObjects| ParametricObjects Visualization
[Pyramid](/Java/GeometricObjects/Pyramid) | vtkPyramid | Pyramid Visualization
[Quad](/Java/GeometricObjects/Quad) | vtkQuad | Quad Visualization
[ShrinkCube](/Java/GeometricObjects/ShrinkCube) | vtkCubeSource vtkShrinkFilter | Applying shrink filter to an object.
[Vertex](/Java/GeometricObjects/Vertex) | vtkVertex | Vertex Visualization
[TextActor](/Java/GeometricObjects/TextActor) | vtkTextActor | TextActor Demonstration
[Triangle](/Java/GeometricObjects/Triangle) | vtkTriangle | Triangle Visualization
[TriangleStrip](/Java/GeometricObjects/TriangleStrip) | vtkTriangleStrip | Triangle Strip Visualization

## HyperTreeGrid

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[HyperTreeGridSource](/Java/HyperTreeGrid/HyperTreeGridSource) | vtkHyperTreeGridSource |  Demonstration of a hyper-tree grid source.

## Geovis

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[EarthSource](/Java/Geovis/EarthSource) | vtkEarthSource | Earth Source Visualization
[CompassWidget](/Java/Geovis/CompassWidget) | vtkCompassWidget| CompassWidget Visualization

## Graphs

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[VisualizeGraph](/Java/Graphs/VisualizeGraph) | vtkMutableUndirectedGraph  | An example to construct a graph and visualize it.

## Images

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Actor2D](/Java/Images/Actor2D) | vtkActor2D | A actor that draws 2D data
[StaticImage](/Java/Images/StaticImage) | vtkImageViewer2 | Displays a 2D image
[RTAnalyticSource](/Java/Images/RTAnalyticSource) | vtkRTAnalyticSource | Creates an image for regression testing

## Input and Output

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Read a polydata(.vtp) file](/Java/IO/ReadPolyData) | vtkXMLPolyDataReader | IO
[Write a polygonal data (.vtp) file](/Java/IO/WritePolyData) | vtkXMLPolyDataWriter | IO
[JPEGWriter](/Java/IO/JPEGWriter) | vtkJPEGWriter | vtkJPEGWriter can be used to write JPEG files

## Implicit Functions and Iso-surfaces

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ImplicitDataSet](/Java/ImplicitFunctions/ImplicitDataSet) | | Implicit functions, implicit data set.
[ImplicitSphere](/Java/ImplicitFunctions/ImplicitSphere) | vtkSphere vtkAppendPolyData vtkTubeFilter | ImplicitFunctions, Append poly data, tube filter, sphere

## Data Structures

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[VisualizeKDTree](/Java/DataStructures/VisualizeKDTree) | vtkKdTreePointLocator | Show the levels of a KD Tree.

## Image Processing

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ImageTest](/Java/Imaging/ImageTest) | vtkImageReader2Factory | use Java File Dialog to select Image File to Display
[ShotNoise](/Java/ImageProcessing/ShotNoise) | vtkPNGWriter | Example program to write PNG files

## Rendering

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Cone6](/Java/Rendering/Cone6) | vtkBoxWidget vtkInteractorStyleTrackballCamera | This example introduces 3D widgets. 3D widgets take advantage of the event/observer design pattern. Corresponds to the missing Step 6 Java example from VTK/Examples/Tutorial.

## Lighting

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[SpotLight](/Java/Lighting/SpotLight) | vtkSpotLight | vtkSpotLight Demonstration
[LightActor](/Java/Lighting/LightActor) | vtkLightActor| vtkLightActor Demonstration

## Parallel

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ExodusIIWriter](/Java/Parallel/ExodusIIWriter) | vtkExodusIIWriter | Example Program to demonstrates how to use vtkExodusIIWriter

## PolyData

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Stripper](/Java/PolyData/Stripper) | vtkStripper | Stripper
[KochanekSpline](/Java/PolyData/KochanekSpline) | vtkKochanekSpline | KochanekSpline
[ColorDisconnectedRegions](/Java/PolyData/ColorDisconnectedRegions) | vtkColorDisconnectedRegions | ColorDisconnectedRegions
[ColoredPoints](/Java/PolyData/ColoredPoints) | vtkUnsignedCharArray | Example to visualize Colored Points. 
[Outline](/Java/PolyData/Outline) | vtkOutline | Outline
[RibbonFilter](/Java/PolyData/RibbonFilter) | vtkRibbonFilter | RibbonFilter
[ColorCells](/Java/PolyData/ColorCells) | vtkColorCells | ColorCells
[TubeFilter](/Java/PolyData/TubeFilter) | vtkTubeFilter | TubeFilter
[ConvexHullShrinkWrap](/Java/PolyData/ConvexHullShrinkWrap) | vtkConvexHullShrinkWrap | ConvexHullShrinkWrap
[MeshQuality](/Java/PolyData/MeshQuality) | vtkMeshQuality | MeshQuality
[ColorCellsWithRGB](/Java/PolyData/ColorCellsWithRGB) | vtkColorCellsWithRGB | ColorCellsWithRGB
[Reflection](/Java/PolyData/Reflection) | vtkReflection | Reflection
[TriangleColoredPoints](/Java/PolyData/TriangleColoredPoints) | vtkUnsignedCharArray | Adding color to each vertex of a triangle
[TransformFilter](/Java/PolyData/TransformFilter) | vtkTransformFilter | Transforms points, associated normals and vectors


| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[AVI](/Java/Untested/Video/AVI) | vtkAVIWriter | An example to demonstrate how to make an AVI video using vtkAVIWriter


| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[RenderView](/Java/Views/RenderView) | vtkRenderView | An easier way to make objects appear on the screen using RenderView

## Utilities

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[FullScreen](/Java/Utilities/FullScreen) | vtkRenderWindow | Example to Display Actors in a Full Screen Render Window
[TimerLog](/Java/Utilities/TimerLog) | vtkTimerLog | Example to Demonstrate Timer support and logging.

### Arrays

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[UnKnownLengthArray](/Java/Utilities/UnKnownLengthArray) | vtkFloatArray | UnKnown Length Array
[KnownLengthArray](/Java/Utilities/KnownLengthArray) | vtkFloatArray | Known Length Array


## Visualization

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[AnimDataCone](/Java/Visualization/AnimDataCone) | vtkRenderWindowInteractor | Animate a cone by modifying the polydata points - uses Interaction M key (Motion) to toggle animation.
[Animation](/Java/Visualization/Animation) |  | Move a sphere across a scene
[BackfaceCulling](/Java/Visualization/BackfaceCulling) | | Turn on/off fast culling of polygons based on orientation of normal with respect to camera.
[AnnotatedCubeActor](/Java/Visualization/AnnotatedCubeActor) | vtkAnnotatedCubeActor | A 3D cube with face labels.
[BackgroundColor](/Java/Visualization/BackgroundColor) |  |  Example program to set the background color of the render window
[BackgroundGradient](/Java/Visualization/BackgroundGradient) |  | viewport having gradient background using the Background (bottom) and Background2 (top) colors.
[CameraActor](/Java/Visualization/CameraActor) | vtkCameraActor | A frustum to represent a camera.
[ColorAnActor](/Java/Visualization/ColorAnActor) | vtkActor vtkCanvas | Switch style interaction adds C and A key actions for selecting Camera or Actor interaction, and T and J key actions for Trackball or Joystick interaction mode. Adds charEvent observer callback to restore the missing E and Q events to quit.
[Cursor2D](/Java/Visualization/Cursor2D) | vtkCursor2D | Generates a 2D Cursor Representation.
[Cursor3D](/Java/Visualization/Cursor3D) | vtkCursor3D | Generates a 3D Cursor Representation
[CursorShape](/Java/Visualization/CursorShape) | | Change the shape of the cursor. 
[Cutter](/Java/VisualizationAlgorithms/Cutter) | vtkCutter | How to use vtkCutter by cutting through a cube.
[Follower](/Java/Visualization/Follower) | vtkFollower | Draw text that stays right side up.
[OrientedGlyphs](/Java/Visualization/OrientedGlyphs) | vtkGlyph3D | Copies oriented and scaled glyph geometry to every input point
[VectorFieldExample](/Java/Visualization/VectorFieldExample) | vtkXMLUnstructuredGridReader, vtkThresholdPoints, vtkGlyph3D | A vector field visualisation.
[WireframeSphere](/Java/Visualization/WireframeSphere) | vtkSphere | A Wireframe Sphere Visualization.

## Graphs

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[SelectGraphVertices](/Java/Graphs/SelectGraphVertices) | vtkAnnotationLink | Select Edges and vertices in a graph

## SimpleOperations

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[DistanceBetweenPoints](/Java/SimpleOperations/DistanceBetweenPoints) | vtkMath | Example Program to find squared distance and the Euclidean distance between two 3D points.
[PerspectiveTransform](/Java/SimpleOperations/PerspectiveTransform) | vtkPerspectiveTransform | It is used to describe the full range of homogeneous transformations. It was designed in particular to describe a camera-view of a scene
[ProjectPointPlane](/Java/SimpleOperations/ProjectPointPlane) | vtkPlane | Performs various plane computations.
[RandomSequence](/Java/SimpleOperations/RandomSequence) | vtkMinimalStandardRandomSequence | Park and Miller Sequence of pseudo random numbers.

## Swing Integration

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[JFrameRender](/Java/SwingIntegration/JFrameRenderer) | vtkRenderWindowPanel | Render a scene in a JFrame using a vtkRenderWindowPanel
[SwingHandleMouseEvent](/Java/SwingIntegration/SwingHandleMouseEvent) | vtkRenderWindowPanel | Display in a JLabel the point the mouse is hovering over using a mouse listener

## Widgets

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[AngleWidget](/Java/Widgets/AngleWidget) | vtkAngleWidget | AngleWidget Demonstration
[AngleWidget2D](/Java/Widgets/AngleWidget2D) | vtkAngleWidget2D | AngleWidget2D Demonstration
[BalloonWidget](/Java/Widgets/BalloonWidget) |  vtkBalloonWidget | The balloon text describes each object when you hover it.
[DistanceWidget](/Java/Widgets/DistanceWidget) | vtkDistanceWidget | Measures the distance between two points.
[PlaneWidget](/Java/Widgets/PlaneWidget) | vtkPlaneWidget | A finite (bounded) plane that can be interactively placed in a scene.
[SeedWidget](/Java/Widgets/SeedWidget) | vtkSeedWidget | Places multiple seed points, where a user moves the cursor to and clicks it.
[SplineWidget](/Java/Widgets/SplineWidget) | vtkSplineWidget | SplineWidget Demonstration
[TextWidget](/Java/Widgets/TextWidget) | vtkTextWidget | Widget for placing text on overlay plane.
