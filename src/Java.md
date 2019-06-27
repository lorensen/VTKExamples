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

## Input and Output

### Graph Formats

### 3D File Formats

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | -------- |
[ConvertFile](/Java/IO/ConvertFile) |  | Convert a file from one type to another

#### Standard Formats

##### Input

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[DEMReader](/Java/IO/DEMReader) | vtkDEMReader | Read DEM (elevation map) files
[ParticleReader](/Java/IO/ParticleReader) | vtkParticleReader | This example reads ASCII files where each line consists of points with its position (x,y,z) and (optionally) one scalar or binary files in RAW 3d file format.
[ReadCML](/Java/IO/ReadCML) | vtkCMLMoleculeReader | Read Chemistry Markup Language files.
[ReadOBJ](/Java/IO/ReadOBJ) | vtkOBJReader | Read an OBJ (.obj) file.
[ReadPLOT3D](/Java/IO/ReadPLOT3D) | vtkPLOT3DReader | Read PLOT3D data files.
[ReadPLY](/Java/IO/ReadPLY) | vtkPLYReader | Read PLY (.ply) files
[ReadSLC](Java/IO/ReadSLC) | vtkSLCReader | Read an SLC volume file.
[ReadSTL](/Java/IO/ReadSTL) | vtkSTLReader | Read stereo lithography STL (.stl) files.
[SimplePointsReader](/Java/IO/SimplePointsReader) | vtkSimplePointsReader | Read a simple "xyz" file of points.

##### Importers

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ThreeDSImporter](/Java/IO/ThreeDSImporter) | vtk3DSImporter | Import a 3D Studio scene that includes multiple actors.
[VRMLImporter](/Java/Io/VRMLImporter) | vtkVRMLImporter | Import a VRML 2.0 (WRL) file.

##### Output

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[SimplePointsWriter](/Java/IO/SimplePointsWriter) | vtkSimplePointsWriter | Write a simple ".xyz" file
[WritePLY](/Java/IO/WritePLY) | vtkPLYWriter | Write PLY (.ply) files.
[WriteSTL](/Java/IO/WriteSTL) | vtkSTLWriter | Write stereo lithography STL (.stl) files.


#### VTK Formats

##### Input

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ReadPolyData](/Java/IO/ReadPolyData) | vtkXMLPolyDataReader | Read VTK XML PolyData files.
[ReadRectilinearGrid](/Java/IO/ReadRectilinearGrid) | vtkXMLRectilinearGridReader | Read VTK XML RectilinearGrid files.
[ReadStructuredGrid](/Java/IO/ReadStructuredGrid) | vtkXMLStructuredGridReader | Read VTK XML StructuredGrid files.
[ReadVTP](/Java/IO/ReadVTP) | vtkXMLPolyDataReader | Read a VTK XML PolyData file.

##### Output

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[WriteVTP](/Java/IO/WriteVTP) | vtkXMLPolyDataWriter | Write a VTK XML PolyData file.
[WriteVTU](/Java/IO/WriteVTU) | vtkXMLUnstructuredGridWriter | Write a .vtu file. VTU is an "Unstructured Grid". This format allows for 3D data to be stored.
[XMLPImageDataWriter](/Java/IO/XMLPImageDataWriter) | vtkXMLPImageDataWriter | Write a .pvti file with 4 .vti pieces.
[XMLPUnstructuredGridWriter](/Java/IO/XMLPUnstructuredGridWriter) | vtkXMLPUnstructuredGridWriter | Write a .pvtu with 4 .vtu pieces.
[XMLStructuredGridWriter](/Java/IO/XMLStructuredGridWriter) | vtkXMLStructuredGridWriter | Write a .vts file from a vtkStructuredGrid.

##### Legacy VTK Formats

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[StructuredPointsReader](/Java/IO/StructuredPointsReader) | vtkStructuredPointsReader | Read a structured points (.vtk) file.


### Image Format

#### Input

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ReadBMP](/Java/IO/ReadBMP) | vtkBMPReader | Read Windows BMP files.
[ReadDICOM](/Java/IO/ReadDICOM) | vtkDICOMImageReader | Read DICOM images.
[JPEGReader](/Java/IO/JPEGReader) | vtkJPEGReader | Read a JPEG image.
[ReadPNM](/Java/IO/ReadPNM) | vtkPNMReader | Read PNM (.pnm) files.
[ReadTIFF](/Java/IO/ReadTIFF) | vtkTIFFReader | Read TIFF (.tif) files.

####  Output

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[JPEGWriter](/Java/IO/JPEGWriter) | vtkJPEGWriter | Write a JPEG file.
[PNGReader](/Java/IO/PNGReader) | vtkPNGReader | Read a PNG image.
[WritePNM](/Java/IO/WritePNM) | vtkPNMWriter | Write a PNM (.pnm) file.
[WriteTIFF](/Java/IO/WriteTIFF) | vtkTIFFWriter | Write a TIFF (.tif) file.


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

## Geographic Visualization (Geovis)

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[EarthSource](/Java/Geovis/EarthSource) | vtkEarthSource | Earth Source Visualization
[CompassWidget](/Java/Geovis/CompassWidget) | vtkCompassWidget| CompassWidget Visualization
[GeoAssignCoordinates](/Java/Geovis/GeoAssignCoordinates) | vtkGeoAssignCoordinates | Convert latitude and longitude coordinates to world coordinates.

## Graphs

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[VisualizeGraph](/Java/Graphs/VisualizeGraph) | vtkMutableUndirectedGraph  | An example to construct a graph and visualize it.
[GraphPoints](/Java/InfoVis/GraphPoints) | vtkGraph | Manually set the coordinates of vertices in a graph.
[RandomGraphSource](/Java/Graphs/RandomGraphSource) | vtkRandomGraphSource | A graph with random edges.

## Working with Images

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Actor2D](/Java/Images/Actor2D) | vtkActor2D | A actor that draws 2D data
[Cast](/Java/Images/Cast) | vtkImageCast | Image Data type Casting Filter.
[ImageSinusoidSource](/Java/Images/ImageSinusoidSource) | vtkImageSinusoidSource | Creates an image with sinusoidal pixel values.
[StaticImage](/Java/Images/StaticImage) | vtkImageViewer2 | Displays a 2D image
[RTAnalyticSource](/Java/Images/RTAnalyticSource) | vtkRTAnalyticSource | Creates an image for regression testing


## Image Processing

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Flip](/Java/Images/Flip) | vtkImageFlip | Flips an image.
[ImageFFT](/Java/Images/ImageFFT) | vtkImageFFT |  Compute the Fast Fourier Transform of an image.
[ImageTest](/Java/Imaging/ImageTest) | vtkImageReader2Factory | Use Java file dialog to select an image file to display.
[ShotNoise](/Java/ImageProcessing/ShotNoise) | vtkImageCanvasSource2D vtkPNGWriter | Create an image using vtkImageCanvasSource2D and write it to a file.


## Implicit Functions and Iso-surfaces

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[IceCream](/Java/VisualizationAlgorithms/IceCream) | vtkImplicitBoolean vtkSampleFunction | How to use boolean combinations of implicit functions to create a model of an ice cream cone.
[ImplicitDataSet](/Java/ImplicitFunctions/ImplicitDataSet) | | Implicit functions, implicit data set.
[ImplicitSphere](/Java/ImplicitFunctions/ImplicitSphere) | vtkSphere vtkAppendPolyData vtkTubeFilter | ImplicitFunctions, Append poly data, tube filter, sphere
[SampleFunction](/Java/ImplicitFunctions/SampleFunction) | vtkSampleFunction | Sample an implicit function over a structured point set.

## User Interaction

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Assembly](/Java/Interaction/Assembly) | vtkAssembly | Combine/group actors into an assembly.
[InteractorStyleTerrain](/Java/Interaction/InteractorStyleTerrain) | vtkInteractorStyleTerrain | Manipulate camera in scene with natural view up.
[RubberBandPick](/Java/Interaction/RubberBandPick) | vtkInteractorStyleRubberBandPick | Pick props underneath a rubber band selection rectangle.
[RubberBandZoom](/Java/Interaction/RubberBandZoom) | vtkInteractorStyleRubberBandZoom | Zoom in by amount indicated by rubber band box.
[TrackballActor](/Java/Interaction/TrackballActor) | vtkInteractorStyleTrackballActor | Trackball actor mode.
[TrackballCamera](/Java/Interaction/TrackballCamera) | vtkInteractorStyleTrackballCamera | Trackball camera mode.
[PickableOff](/Java/Interaction/PickableOff) | vtkActor | Disallow interaction with a specific actor.
[StyleSwitch](/Java/Interaction/StyleSwitch) | vtkInteractorStyleSwitch | Choose between multiple interaction modes.

## Working with Meshes

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[AddCell](/Java/Meshes/AddCell) | vtkPolyData | Add a cell to an existing mesh.
[BoundaryEdges](/Java/Meshes/BoundaryEdges) | vtkFeatureEdges | Find the edges that are used by only one face.
[DelaunayMesh](/Java/Modelling/DelaunayMesh) | vtkDelaunay2D vtkMinimalStandardRandomSequence vtkExtractEdges vtkGlyph3D vtkTubeFilter | Two-dimensional Delaunay triangulation of a random set of points. Points and edges are shown highlighted with sphere glyphs and tubes.



## Working with 3D Data

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[Bottle](/Java/Modelling/Bottle) | vtkRotationalExtrusionFilter | Sweeps polygonal data creating "skirt" from free edges and lines, and lines from vertices
[CellCenters](/Java/PolyData/CellCenters) | vtkCellCenters | Compute points at the center of every cell.
[CenterOfMass](/Java/PolyData/vtkCenterOfMass) | vtkCenterOfMass | Compute the center of mass of the points.
[ProjectSphere](/Java/Visualization/ProjectSphere) | vtkProjectSphereFilter | Unroll a sphere or spherical-like model.
[Spring](/Java/Modelling/Spring) | vtkRotationalExtrusionFilter | Rotation in combination with linear displacement and radius variation.

### Working with Structured 3D Data


This section includes vtkImageData vtkStructuredGrid and vtkRectilinearGrid.

"ImageData" is not the traditional "flat, 2D image" you are used to. It is a special VTK data structure in the collection of 3D data structures provided by VTK. [Here is an overview of these data structures](http://www.vtk.org/Wiki/VTK/Tutorials/3DDataTypes). Image data can represent at typical 2D image, but also, a 3D volume.

#### vtkImageData

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[ImageNormalize](/Java/ImageData/ImageNormalize) | vtkImageNormalize  | Normalizes the scalar components for each point.
[ImageWeightedSum](/Java/ImageData/ImageWeightedSum) | vtkImageWeightedSum | Add two or more images.


#### vtkStructuredPoints

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[StructuredPointsToUnstructuredGrid](/Java/StructuredPoints/StructuredPointsToUnstructuredGrid) | vtkStructuredPoints vtkUnstructuredGrid | Convert a vtkStructuredPoints to a vtkUnstructuredGrid.
[Vol](/Java/StructuredPoints/Vol) | vtkStructuredPoints vtkContourFilter | Creating a image data dataset. Scalar data is generated from the equation for a sphere. Volume dimensions are 26 x 26 x 26.

#### vtkStructuredGrid

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[BlankPoint](/Java/vtkStructuredGrid/BlankPoint) | vtkStructuredGrid | Blank a point of a vtkStructuredGrid.
[StructuredGridOutline](/Java/StructuredGrid/StructuredGridOutline) | vtkStructuredGridOutlineFilter | Creates a wireframe outline for structured grid.

This section includes vtkImageData, vtkStructuredGrid and vtkRectilinearGrid.

"ImageData" is not the traditional "flat, 2D image" you are used to. It is a special VTK data structure in the collection of 3D data structures provided by VTK. [Here is an overview of these data structures](http://www.vtk.org/Wiki/VTK/Tutorials/3DDataTypes). Image data can represent at typical 2D image, but also, a 3D volume.

#### vtkRectilinearGrid

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[RectilinearGrid](/Java/RectilinearGrid/RectilinearGrid) | vtkRectilinearGrid | A dataset that is topologically regular with variable spacing in the three coordinate directions
[RectilinearGridToTetrahedra](/Java/RectilinearGrid/RectilinearGridToTetrahedra) | vtkRectilinearGridToTetrahedra | Convert a vtkRectilinearGrid to a vtkUnstructuredGrid mesh.
[VisualizeRectilinearGrid](/Java/RectilinearGrid/VisualizeRectilinearGrid) | vtkRectilinearGrid vtkShrinkFilter| Visualize the cells of a rectilinear grid.



### Point Cloud Operations

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[FitImplicitFunction](/Java/Points/FitImplicitFunction) | vtkFitImplicitFunction | Extract points within a distance to an implicit function.

## Data Structures

### KD-Tree

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[VisualizeKDTree](/Java/DataStructures/VisualizeKDTree) | vtkKdTreePointLocator | Show the levels of a KD Tree.

### Octree

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[BuildOctree](/Java/DataStructures/BuildOctree) | vtkOctreePointLocator | Create an octree.


## Rendering

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[AmbientSpheres](/Java/Rendering/AmbientSpheres) | vtkProperty | Demonstrates the effect of ambient lighting on spheres.
[ColoredSphere](/Java/Rendering/ColoredSphere) | vtkSphereSource vtkElevationFilter | A simple sphere.
[Cone6](/Java/Rendering/Cone6) | vtkBoxWidget vtkInteractorStyleTrackballCamera | This example introduces 3D widgets. 3D widgets take advantage of the event/observer design pattern. Corresponds to the missing Step 6 Java example from VTK/Examples/Tutorial.
[Mace](/Java/Rendering/Mace) | | An example of multiple inputs and outputs.
[SpecularSpheres](/Java/Rendering/SpecularSpheres) | vtkProperty | Demonstrates the effect of specular lighting on spheres.

## Lighting

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[SpotLight](/Java/Lighting/SpotLight) | vtkSpotLight | vtkSpotLight Demonstration
[LightActor](/Java/Lighting/LightActor) | vtkLightActor| vtkLightActor Demonstration



## Math Operations

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[MatrixInverse](/Java/Math/MatrixInverse) | vtkMatrix3x3 | Represents and manipulates  3x3 transformation matrices.
[MatrixTranspose](/Java/Math/MatrixTranspose) | vtkMatrix3x3 | The transpose of a matrix is a new matrix whose rows are the columns of the original.
[NormalizeVector](/Java/Math/vtkMath) | vtkMath | Normalize a vector.

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
[RotationAroundLine](/Java/PolyData/RotationAroundLine) | vtkTransform vtkTransformPolyDataFilter | Rotation around a line.
[RuledSurfaceFilter](/Java/PolyData/RuledSurfaceFilter) | vtkRuledSurfaceFilter | Create a surface between lines.
[ThinPlateSplineTransform](/Java/PolyData/ThinPlateSplineTransform) | vtkThinPlateSplineTransform | A nonlinear warp transformation.
[TriangleColoredPoints](/Java/PolyData/TriangleColoredPoints) | vtkUnsignedCharArray | Adding color to each vertex of a triangle
[TransformPipeline](/Java/PolyData/TransformPipeline) | vtkTransform | Combining the transformation, in order to manipulate a group of vtkActor. Shown in the example robot arm motion.
[TransformFilter](/Java/PolyData/TransformFilter) | vtkTransformFilter | Transforms points, associated normals and vectors



| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[AVI](/Java/Untested/Video/AVI) | vtkAVIWriter | An example to demonstrate how to make an AVI video using vtkAVIWriter


| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[RenderView](/Java/Views/RenderView) | vtkRenderView | An easier way to make objects appear on the screen using RenderView


## Texture Mapping
| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[TexturePlane](/Java/Texture/TexturePlane) | vtkTexture | Example of texture mapping.
[TexturedSphere](/Java/Texture/TexturedSphere) | vtkTexturedSphereSource | Texture a sphere.


## Utilities

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[BrownianPoints](/Java/Utilities/BrownianPoints) | vtkBrownianPoints | Produce a random vector at each point in a dataset.
[DiscretizableColorTransferFunction](/Java/Utilities/DiscretizableColorTransferFunction) | vtkDiscretizableColorTransferFunction | Discretizable Color Transfer Function.
[FullScreen](/Java/Utilities/FullScreen) | vtkRenderWindow | Example to Display Actors in a Full Screen Render Window.
[FunctionParser](/Java/Utilities/FunctionParser) | vtkFunctionParser | String function parser.
[GetDataRoot](/Java/Utilities/GetDataRoot) | vtkTesting | Find the path of VTK_DATA_ROOT.
[TimerLog](/Java/Utilities/TimerLog) | vtkTimerLog | Example to Demonstrate Timer support and logging.
[ColorLookupTable](/Java/Utilities/ColorLookupTable) | vtkLookupTable | Color Lookup Table.
[PassThrough](/Java/InfoVis/PassThrough) | vtkPassThrough | Shallow copies the input into the output.
[PiecewiseFunction](/Java/Utilities/PiecewiseFunction) | vtkPiecewiseFunction | Interpolation using a piecewise function.
[ReportRenderWindowCapabilities](/Java/Utilities/ReportRenderWindowCapabilities) | vtkRenderWindow | Report the capabilities of a render window.
[Screenshot](/Java/Utilities/Screenshot) | vtkWindowToImageFilter | Use a vtkWindow as input to image pipeline.



### Arrays

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[UnKnownLengthArray](/Java/Utilities/UnKnownLengthArray) | vtkFloatArray | UnKnown Length Array
[KnownLengthArray](/Java/Utilities/KnownLengthArray) | vtkFloatArray | Known Length Array

## Video
| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[OggTheora](/Java/Video/AVI) | vtkOggTheoraWriter | Uses the ogg and theora libraries to write video files.

## Visualization

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[AnimDataCone](/Java/Visualization/AnimDataCone) | vtkRenderWindowInteractor | Animate a cone by modifying the polydata points - uses Interaction M key (Motion) to toggle animation.
[Animation](/Java/Visualization/Animation) |  | Move a sphere across a scene
[BackfaceCulling](/Java/Visualization/BackfaceCulling) | | Turn on/off fast culling of polygons based on orientation of normal with respect to camera.
[AnnotatedCubeActor](/Java/Visualization/AnnotatedCubeActor) | vtkAnnotatedCubeActor | A 3D cube with face labels.
[BackgroundColor](/Java/Visualization/BackgroundColor) |  |  Example program to set the background color of the render window
[BackgroundGradient](/Java/Visualization/BackgroundGradient) |  | viewport having gradient background using the Background (bottom) and Background2 (top) colors.
[BlobbyLogo](/Java/Visualization/BlobbyLogo) | vtkImplicitModeller | Blobby logo from VTK textbook.
[Camera](/Java/Visualization/Camera) | vtkCamera | A virtual camera for 3D rendering.
[CameraActor](/Java/Visualization/CameraActor) | vtkCameraActor | A frustum to represent a camera.
[ColorAnActor](/Java/Visualization/ColorAnActor) | vtkActor vtkCanvas | Switch style interaction adds C and A key actions for selecting Camera or Actor interaction, and T and J key actions for Trackball or Joystick interaction mode. Adds charEvent observer callback to restore the missing E and Q events to quit.
[CornerAnnotation](/Java/Visualization/CornerAnnotation) | vtkCornerAnnotation | Write text in the corners of a window.
[ColorActorEdges](/Java/Visualization/ColorActorEdges) | vtkActor | Color the edges of an Actor.
[ComplexV](/Java/Visualization/ComplexV) | vtkHedgeHog | ComplexV from the VTK Textbook.
[CubeAxesActor](/Java/Visualization/CubeAxesActor) | vtkCubeAxesActor | Display three orthogonal axes with labels.
[CubeAxesActor2D](/Java/Visualization/CubeAxesActor2D) | vtkCubeAxesActor2D | This example uses the vtkCubeAxesActor2D to show your scene with axes to indicate the spatial extent of your data.
[Cursor2D](/Java/Visualization/Cursor2D) | vtkCursor2D | Generates a 2D Cursor Representation.
[Cursor3D](/Java/Visualization/Cursor3D) | vtkCursor3D | Generates a 3D Cursor Representation
[CursorShape](/Java/Visualization/CursorShape) | | Change the shape of the cursor. 
[Cutter](/Java/VisualizationAlgorithms/Cutter) | vtkCutter | How to use vtkCutter by cutting through a cube.
[DrawText](/Java/Visualization/DrawText) | vtkTextActor vtkTextProperty | Display Text.
[DisplayCoordinateAxes](/Java/Visualization/DisplayCoordinateAxes) | vtkOrientationMarkerWidget | Display coordinate axes.
[DistanceToCamera](/Java/Visualization/DistanceToCamera) | vtkDistanceToCamera | Calculate distance from points to the camera.
[Follower](/Java/Visualization/Follower) | vtkFollower | Draw text that stays right side up.
[SpikeFran](/Java/VisualizationAlgorithms/SpikeFran) | vtkGlyph3D | Glyphs indicate surface normals on model of human face. Glyph positions are randomly selected.
[ImageOrientation](/Java/Visualization/ImageOrientation) | vtkInteractorStyleImage | Orientation of the view of an image.
[Legend](/Java/Visualization/Legend) | vtkLegendBoxActor | Draw symbols with text.
[LegendScaleActor](/Java/Visualization/LegendScaleActor) | vtkLegendScaleActor | Display the scale of a scene.
[LoopShrink](/Java/Visualization/LoopShrink) | vtkShrinkFilter| A network with a loop.
[LineWidth](/Java/Visualization/LineWidth) | vtkActor vtkProperty | Change the width/thickness of lines in an actor.
[MoveActor](/Java/Visualization/MoveActor) | vtkInteractorStyleTrackballActor | Moving an Actor.
[MoveCamera](/Java/Visualization/MoveCamera) | vtkInteractorStyleTrackballCamera | Moving the Camera.
[MultipleActors](/Java/Visualization/MultipleActors) | vtkActor | Multiple Actors.
[MultipleViewports](/Java/Visualization/MultipleViewports) | vtkRenderer | Multiple Viewports.
[Opacity](/Java/Visualization/Opacity) | vtkActor | Transparency, transparent.
[OrientedGlyphs](/Java/Visualization/OrientedGlyphs) | vtkGlyph3D | Copies oriented and scaled glyph geometry to every input point
[VectorFieldExample](/Java/Visualization/VectorFieldExample) | vtkXMLUnstructuredGridReader, vtkThresholdPoints, vtkGlyph3D | A vector field visualisation.
[NoShading](/Java/Visualization/NoShading) | vtkActor | 
[ProteinRibbons](/Java/Visualization/ProteinRibbons) | vtkProteinRibbonFilter | Display pdb ribbons.
[RandomProbe](/Java/Visualization/RandomProbe) | vtkProbeFilter | Demonstrates how to probe a dataset with random points and select points inside the data set.
[ScalarBarActor](/Java/Visualization/ScalarBarActor) | vtkScalarBarActor | Display a color bar.
[ScalarBarActorColorSeries](/Java/Visualization/ScalarBarActorColorSeries) | vtkScalarBarActor vtkColorSeries | Display a color bar with a color series lookup table.
[ScalarVisibility](/Java/Visualization/ScalarVisibility) | vtkDataSetMapper | Switch between coloring the actor and coloring the data.
[SideBySideViewports](/Java/Visualization/SideBySideViewports) | vtkRenderer | Side by side viewports.
[VisualizeImageData](/Java/Visualization/VisualizeImageData) | vtkDataSetMapper vtkImageData | Visualize the points of an ImageData.
[VisualizeVTP](/Java/Visualization/VisualizeVTP) | vtkXMLPolyDataReader vtkPolyDataMapper | Visualize a VTP File.
[WindowSize](/Java/Visualization/WindowSize) | vtkRenderWindow | Change the size of a window.
[WireframeSphere](/Java/Visualization/WireframeSphere) | vtkSphere | A Wireframe Sphere Visualization.

## Volume Rendering

| Example Name | Classes Demonstrated | Description | Image |
| -------------- | ---------------------- | ------------- | ------- |
[SimpleRayCast](/Java/VolumeRendering/SimpleRayCast) | vtkFixedPointVolumeRayCastMapper | Volume rendering of a high potential iron protein.

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
[CaptionWidget](/Java/Widgets/CaptionWidget) | vtkCaptionWidget | Widget for placing a caption (text plus leader)
[DistanceWidget](/Java/Widgets/DistanceWidget) | vtkDistanceWidget | Measures the distance between two points.
[ImagePlaneWidget](/Java/Widgets/ImagePlaneWidget) | vtkImagePlaneWidget | 3D widget for reslicing image data.
[ImageTracerWidgetNonPlanar](/Java/Widgets/ImageTracerWidgetNonPlanar) | vtkImageTracerWidget | 3D widget for tracing on planar props.
[LogoWidget](/Java/Widgets/LogoWidget) | vtkLogoWidget | 2D widget for placing and manipulating a logo
[OrientationMarkerWidget](/Java/widgets/OrientationMarkerWidget) | vtkOrientationMarkerWidget | Display a polydata as an orientation icon.
[PlaneWidget](/Java/Widgets/PlaneWidget) | vtkPlaneWidget | A finite (bounded) plane that can be interactively placed in a scene.
[SeedWidget](/Java/Widgets/SeedWidget) | vtkSeedWidget | Places multiple seed points, where a user moves the cursor to and clicks it.
[SplineWidget](/Java/Widgets/SplineWidget) | vtkSplineWidget | SplineWidget Demonstration
[TextWidget](/Java/Widgets/TextWidget) | vtkTextWidget | Widget for placing text on overlay plane.


