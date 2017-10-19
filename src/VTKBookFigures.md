# VTK Book Figure Examples

The [Visualization Toolkit Text Book](http://www.vtk.org/wp-content/uploads/2016/09/books_VTK_textbook.png)  was first published in 1995. At that time, the book was unique. It presented the theory behind computer graphics and visualization algorithms. It also provided a free C++ toolkit called VTK. Each theory chapter of the book wrapped up with a section called *Putting It All Together*. These sections provided examples using the VTK software. The examples were written in C++ or Tcl. As VTK matured, the Application Programming Interface (API) also matured. For example, today, C++ and Python are the preferred languages, although Java and Tcl are still available. Although the VTK software has always been free, until recently the VTK Book was only available commercially. Now, the book, like the software, is also free. View or download the book [here](https://www.vtk.org/vtk-textbook/).

Even though the book is over 20 years old, the concepts in the book are still relevant. The dozens of examples in the book are also still valuable for learning and using VTK. We have begun an effort to convert all of the examples in the book into C++ and present them Chapter by Chapter. These examples supplement the hundreds of examples on this [VTKExamples web site](https://lorensen.github.io/VTKExamples/site/)..

Since some of the API's have changed, the new implementations may differ from those in the book. Also, since Tcl used less frequently, the examples have been converted to C++. The examples are also enhanced by newer VTK features, like vtkNamedColors and vtkSmartPointer.

Each Figure example

1. links to the source code of the new implementation,

2. links to the doxygen documentation for classes demonstrated,

3. shows the original figure caption and,

4. if the example produces an image, links to the full resolution image. If the caption includes a source file reference, e.g. [bluntStr.cxx](https://gitlab.kitware.com/vtk/vtk/blob/d72d8120513c2c856e027ec83cd3c678912e7e0d/graphics/examplesCxx/bluntStr.cxx) or [rotations.tcl](https://gitlab.kitware.com/vtk/vtk/blob/cdd4d6fdec8b4b2c143224ca1d94699c96a8b58a/Rendering/Core/Testing/Tcl/rotations.tcl), that reference links to the original source code.

Please enjoy this new effort to revive the VTK Figure examples.

!!! info
    This is a works-in-progress. Figures with links indicate that an example has been implemented. Those without links are yet to be implemented.

## Chapter 3 - Computer Graphics

| Figure | Classes Demonstrated | Caption | Image |
|--------|----------------------|---------|-------|
Figure 3-5 | | On the top, circular representation of hue. The other two images on the bottom are slices through the HSV color space. The first slice has a value of 1.0, the other has a value of 0.5.
Figure 3-7 | | Flat and Gouraud shading. Different shading methods can dramatically improve the look of an object represented with polygons. On the top, flat shading uses a constant surface normal across each polygon. On the bottom, Gouraud shading interpolates normals from polygon vertices to give a smoother look.
[Figure 3-10](/Cxx/Rendering/SpecularSpheres) | vtkProperty | Effects of specular coefficients. Specular coefficients control the apparent “shininess” of objects. The top row has a specular intensity value of 0.5; the bottom row 1.0. Along the horizontal direction the specular power changes. The values (from left to right) are 5, 10, 20, and 40 [(SpecularSpheres.cxx](https://gitlab.kitware.com/vtk/vtk/blob/479bc209c9c2c32a478c9e33e7677baa8574fcb8/Examples/Rendering/Cxx/SpecularSpheres.cxx)).
[Figure 3-12](/Cxx/Visualization/CameraModel1) | | Camera movements around focal point ([camera.tcl](https://gitlab.kitware.com/vtk/vtk/blob/cdd4d6fdec8b4b2c143224ca1d94699c96a8b58a/Filters/Modeling/Testing/Tcl/camera.tcl)).
[Figure 3-13](/Cxx/Visualization/CameraModel2) | | Camera movements centered at camera position ([camera2.tcl](https://gitlab.kitware.com/vtk/vtk/blob/da314198bb8fbdab6f59e8a69b2d97f1611a05bd/graphics/examplesTcl/camera2.tcl)).
Figure 3-26 | | Examples of source objects that procedurally generate polygonal models.  These nine images represent just some of the capability of VTK. From upper left in reading order: sphere, cone, cylinder, cube, plane, text, random point cloud, disk (with or without hole), and line source. Other polygonal source objects are available; check subclasses of vtkPolyDataAlgorithm.
Figure 3-27 | | Four frames of output from Cone3.cxx 
Figure 3-28 | | Modifying properties and transformation matrix (Cone4.cxx)
[Figure 3-31](/Cxx/Rendering/Rotations) | vtkActor::RotateX,Y,Z vtkRenderer::EraseOff | Rotations of a cow about her axes. In this model, the x axis is from the left to right; the y axis is from bottom to top; and the z axis emerges from the image. The camera location is the same in all four images ([rotations.tcl](https://gitlab.kitware.com/vtk/vtk/blob/cdd4d6fdec8b4b2c143224ca1d94699c96a8b58a/Rendering/Core/Testing/Tcl/rotations.tcl)).
[Figure 3-32](/Cxx/Rendering/WalkCow)|  vtkBYUReader vtkRenderer::EraseOff() vtkActor | The cow "walking" around the global origin ([walkCow.tcl](https://gitlab.kitware.com/vtk/vtk/blob/d669b22d2fbfa9e28e348a7569eab2bea46459b0/graphics/examplesTcl/walkCow.tcl)).
[Figure 3-33a](/Cxx/Rendering/WalkCowA) | vtkBYUReader vtkRenderer::EraseOff() vtkActor | The cow rotating about a vector passing through her nose. (a) With origin (0,0,0). ([walkCow.tcl](https://gitlab.kitware.com/vtk/vtk/blob/d669b22d2fbfa9e28e348a7569eab2bea46459b0/graphics/examplesTcl/walkCow.tcl)).
[Figure 3-33b](/Cxx/Rendering/WalkCowB) | vtkBYUReader vtkRenderer::EraseOff() vtkActor | The cow rotating about a vector passing through her nose. (b) With origin at (6.1,1.3,.02). ([walkCow.tcl](https://gitlab.kitware.com/vtk/vtk/blob/d669b22d2fbfa9e28e348a7569eab2bea46459b0/graphics/examplesTcl/walkCow.tcl)).

## Chapter 4 - The Visualization Pipeline

| Figure | Classes Demonstrated | Caption | Image |
|--------|----------------------|---------|-------|
[Figure 4–1](/Cxx/Visualization/QuadricVisualization) | vtkQuadric vtkSampleFunction vtkContourFilter | Visualizing a quadric function ([Sample.cxx](https://gitlab.kitware.com/vtk/vtk/blob/3ad5fa14aaa30c57cab400a7494bd6e2eac37bf1/graphics/examplesCxx/Sample.cxx))
Figure 4-11 | | Dividing a sphere into a piece (red) with ghost level cells and points (blue and green).
[Figure 4-13](/Cxx/IO/3DSImporter) | | Importing and exporting files in VTK. An importer creates a vtkRenderWindow that describes the scene. Exporters use an instance of vtkRenderWindow to obtain a description of the scene ([3dsToRIB.tcl](/graphics/examplesTcl/3dsToRIB.tcl) and ([flamingo.tcl](https://gitlab.kitware.com/vtk/vtk/blob/2d323fc4f7476ad024d0f4a164a0930f005bc154/Examples/IO/Tcl/flamingo.tcl)).
[Figure 4-21](/Cxx/Rendering/Mace) | | An example of multiple inputs and outputs ([Mace.cxx](https://gitlab.kitware.com/vtk/vtk/blob/cdd4d6fdec8b4b2c143224ca1d94699c96a8b58a/Rendering/Core/Testing/Cxx/Mace.cxx)).
[Figure 4-22](/Cxx/Visualization/LoopShrink) | |  A network with a loop. VTK 5.0 does not allow you to execute a looping visualization network; this was possible in previous versions of VTK. ([LoopShrk.cxx](https://gitlab.kitware.com/vtk/vtk/blob/3ad5fa14aaa30c57cab400a7494bd6e2eac37bf1/graphics/examplesCxx/LoopShrk.cxx)).

## Chapter 5 - Basic Data Representation

| Figure | Classes Demonstrated | Caption | Image |
|--------|----------------------|---------|-------|
[Figure 5-17](/Cxx/GeometricObjects/Cube) | vtkCubeSource  | Creation of polygonal cube ([Cube.cxx](https://gitlab.kitware.com/vtk/vtk/blob/1701059360982c495abff5b449009881748a9f19/Examples/DataManipulation/Cxx/Cube.cxx)).
[Figure 5-18](/Cxx/StructuredPoints/Vol) | vtkStructuredPoints vtkContourFilter| Creating a image data dataset. Scalar data is generated from the equation for a sphere.  Volume dimensions are 26 3 ([Vol.cxx](https://gitlab.kitware.com/vtk/vtk/blob/3ad5fa14aaa30c57cab400a7494bd6e2eac37bf1/graphics/examplesCxx/Vol.cxx)).
[Figure 5-19](/Cxx/StructuredGrid/SGrid) | vtkStructuredGrid | Creating a structured grid dataset of a semi-cylinder. Vectors are created whose magnitude is proportional to radius and oriented in tangential direction ([SGrid.cxx](https://gitlab.kitware.com/vtk/vtk/blob/2d323fc4f7476ad024d0f4a164a0930f005bc154/Examples/DataManipulation/Cxx/SGrid.cxx)).
[Figure 5-20](/Cxx/RectilinearGrid/RGrid) | vtkRectilinearGrid | Creating a rectilinear grid dataset. The coordinates along each axis are defined using an instance of vtkDataArray ([RGrid.cxx](https://gitlab.kitware.com/vtk/vtk/blob/2d323fc4f7476ad024d0f4a164a0930f005bc154/Examples/DataManipulation/Cxx/RGrid.cxx)).
[Figure 5-21](/Cxx/UnstructuredGrid/UGrid) | vtkUnstructuredGrid | Creation of an unstructured grid ([UGrid.cxx](https://gitlab.kitware.com/vtk/vtk/blob/3ad5fa14aaa30c57cab400a7494bd6e2eac37bf1/graphics/examplesCxx/UGrid.cxx)).

## Chapter 6 - Fundamental Algorithms

| Figure | Classes Demonstrated | Caption | Image |
|--------|----------------------|---------|-------|
[Figure 6-3](/Cxx/Rendering/Rainbow) | vtkLookupTable | Flow density colored with different lookup tables. Top-left: grayscale; Top-right rainbow (blue to red); lower-left rainbow (red to blue); lower-right large contrast ([rainbow.tcl](https://gitlab.kitware.com/vtk/vtk/blob/6653cd058786cd7b8a69d9add61c843e4cddb945/Examples/Rendering/Tcl/rainbow.tcl)).
[Figure 6-6](/Cxx/VisualizationAlgorithms/MarchingCasesA) | vtkMarchingCubes | Marching cubes cases for 3D isosurface generation. The 256 possible cases have been reduced to 15 cases using symmetry. Dark vertices are greater than the selected isosurface value.
[Figure 6-10](/Cxx/VisualizationAlgorithms/MarchingCasesB) | vtkMarchingCubes | Marching cubes complementary cases.
Figure 6-11 | | Contouring examples. (a) Marching squares used to generate contour lines ([headSlic.tcl](https://gitlab.kitware.com/vtk/vtk/blob/da314198bb8fbdab6f59e8a69b2d97f1611a05bd/graphics/examplesTcl/headSlic.tcl)).
Figure 6-11b | | Contouring examples. (b) Marching cubes surface of human bone ([headBone.tcl](https://gitlab.kitware.com/vtk/vtk/blob/cdd4d6fdec8b4b2c143224ca1d94699c96a8b58a/Common/DataModel/Testing/Tcl/headBone.tcl)).
[Figure 6-11c](/Cxx/VisualizationAlgorithms/CombustorIsosurface) | vtkContourFilter | Contouring examples. (c) Marching cubes surface of flow density ([combIso.tcl](https://gitlab.kitware.com/vtk/vtk/blob/842ce0a6e51e8a3b0eefa089e3138d073e54724b/Graphics/Testing/Tcl/combIso.tcl)).
Figure 6-11d | | Contouring examples. (d) Marching cubes surface of iron-protein ([ironPIso.tcl](https://gitlab.kitware.com/vtk/vtk/blob/da314198bb8fbdab6f59e8a69b2d97f1611a05bd/graphics/examplesTcl/ironPIso.tcl)).
[Figure 6-12](/Cxx/Visualization/Hawaii) | vtkElevationFilter vtkColorSeries vtkLookupTable | Computing scalars using normalized dot product. Bottom half of figure illustrates technique applied to terrain data from Honolulu, Hawaii [hawaii.tcl](https://gitlab.kitware.com/vtk/vtk/blob/da314198bb8fbdab6f59e8a69b2d97f1611a05bd/graphics/examplesTcl/hawaii.tcl).
[Figure 6-13](/Cxx/Visualization/ComplexV) | vtkHedgeHog | Vector visualization techniques: (a) oriented lines; (b) using oriented glyphs; (c) complex vector visualization (complexV.tcl).
Figure 6-15 | | Vector displacement plots. (a) Vector converted to scalar via dot product computation; (b) Surface plot of vibrating plate. Dark areas show nodal lines. Bright areas show maximum motion (dispPlot.tcl).
[Figure 6-18](/Cxx/Visualization/Kitchen) | | Flow velocity computed for a small kitchen (top and side view). Forty streamlines start along the rake positioned under the window. Some eventually travel over the hot stove and are convected upwards ([Kitchen.cxx](https://gitlab.kitware.com/vtk/vtk/blob/d02e543345600e545ab0b416faec80b5c306cd91/graphics/examplesCxx/Kitchen.cxx)).
[Figure 6-19](/Cxx/VisualizationAlgorithms/BluntStreamlines) | vtkStreamTracer | Dashed streamlines around a blunt fin. Each dash is a constant time increment. Fast moving particles create longer dashes than slower moving particles. The streamlines also are colored by flow density scalar (bluntStr.cxx).
Figure -22 | | Tensor visualization techniques; (a) Tensor axes (TenAxes.tcl) ; (b) Tensor ellipsoids (TenEllip.tcl). 
Figure 6-23b | | Sampling functions: (b) Isosurface of sampled sphere.
[Figure 6-23c](/Cxx/VisualizationAlgorithms/IceCream) | vtkImplicitBoolean vtkSampleFunction | Sampling functions: (b) Isosurface of sampled sphere; (c) Boolean combination of two spheres, a cone, and two planes. (One sphere intersects the other, the planes clip the cone.) ([iceCream.tcl](https://gitlab.kitware.com/vtk/vtk/blob/2d323fc4f7476ad024d0f4a164a0930f005bc154/Examples/Modelling/Tcl/iceCream.tcl)).
Figure 6-24 | | Implicit functions used to select data: (a) 2D cells lying in ellipse are selected; (b) Two ellipsoids combined using the union operation used to select voxels from a volume. Voxels shrunk 50 percent (extractD.tcl).
[Figure 6-25](/Cxx/Visualization/Lorenz) | vtkContourFilter | Visualizing a Lorenz strange attractor by integrating the Lorenz equations in a volume.  The number of visits in each voxel is recorded as a scalar function. The surface is extracted via marching cubes using a visit value of 50. The number of integration steps is 10 million, in a volume of dimensions 200 3 . The surface roughness is caused by the discrete nature of the evaluation function ([Lorenz.cxx](https://gitlab.kitware.com/vtk/vtk/blob/3ad5fa14aaa30c57cab400a7494bd6e2eac37bf1/graphics/examplesCxx/Lorenz.cxx))
Figure 6-28 | | Implicit modelling used to thicken a stroked font. Original lines can be seen within the translucent implicit surface (hello.tcl).
Figure 6-30 | | Glyphs indicate surface normals on model of human face. Glyph positions are randomly selected (spikeF.tcl).
Figure 6-31 | | Cut through structured grid with plane. The cut plane is shown solid shaded. A computational plane of constant k value is shown in wireframe for comparison (cut.tcl). The colors correspond to flow density. Cutting surfaces are not necessarily planes: implicit functions such as spheres, cylinders, and quadrics can also be used.
[Figure 6-32](/Cxx/VolumeRendering/PseudoVolumeRendering) | vtkCutter vtkContourFilter | 100 cut planes with opacity of 0.05. Rendered back-to-front to simulate volume rendering ([PseudoVolumeRendering.tcl](https://gitlab.kitware.com/vtk/vtk/blob/6653cd058786cd7b8a69d9add61c843e4cddb945/Examples/VolumeRendering/Tcl/PseudoVolumeRendering.tcl)).
[Figure 6-33](/Cxx/VisualizationAlgorithms/CutWithScalars) | vtkContourFilter | Cutting a surface model of the skin with a series of planes produces contour lines ([cutModel.tcl](https://gitlab.kitware.com/vtk/vtk/blob/da314198bb8fbdab6f59e8a69b2d97f1611a05bd/graphics/examplesTcl/cutModel.tcl)).  Lines are wrapped with tubes for visual clarity.
Figure 6-38 | | The cost of generality. Isosurface generation of three volumes of different sizes are compared. The results show normalized execution times for two different implementations of the marching-cubes isosurface algorithm. The specialized filter is vtkMarchingCubes . The general algorithms are first vtkContourFilter and then in combination with vtkPolyDataNormals .
[Figure 6-39](/Cxx/VisualizationAlgorithms/ContourQuadric) | vtkQuadric vtkSampleFunction vtkContourFilter | Contouring quadric function. Pipeline topology, C++ code, and resulting image are shown ([contQuad.cxx](https://gitlab.kitware.com/vtk/vtk/blob/3ad5fa14aaa30c57cab400a7494bd6e2eac37bf1/graphics/examplesCxx/contQuad.cxx)). 
Figure 6-43 | | Visualizing blood flow in human carotid arteries. Cone glyphs indicate flow direction and magnitude. The code fragment shown is from the Tcl script thrshldV.tcl and shows creation of vector glyphs.
Figure 6-44 | | Visualizing blood flow in the human carotid arteries. Streamtubes of flow vectors (streamV.tcl).

## Chapter 7 - Advanced Computer Graphics

| Figure | Classes Demonstrated | Caption | Image |
|--------|----------------------|---------|-------|
Figure 7-3 | | One frame from a vector field animation using texture maps (animVectors.tcl)
Figure 7-33 | | Example of texture mapping (TPlane.tcl).
Figure 7-34 | | Volume rendering of a high potential iron protein (SimpleRayCast.tcl).
Figure 7-36 | | Example of motion blur (MotBlur.cxx)
[Figure 7-37](/Cxx/Rendering/CameraBlur) | | Example of a scene rendered with focal depth (CamBlur.cxx). 
Figure 7-39 | | Using the vtkLineWidget to produce streamtubes in the combustor dataset.  The StartInteractionEvent turns the visibility of the streamlines on; the InteractionEvent causes the streamlines to regenerate themselves (LineWidget.tcl).

## Chapter 8 - Advanced Data Representation

| Figure | Classes Demonstrated | Caption | Image |
|--------|----------------------|---------|-------|
[Figure 8-41a](/Cxx/Visualization/AlphaFrequency) | vtkLinearExtrusionFilter vtkVectorText | (a) Linearly extruded fonts to show letter frequency in text ([alphaFreq.cxx](https://gitlab.kitware.com/vtk/vtk/blob/3ad5fa14aaa30c57cab400a7494bd6e2eac37bf1/graphics/examplesCxx/alphaFreq.cxx)).
[Figure 8-41b](/Cxx/Modelling/Bottle) | vtkRotationalExtrusionFilter | (b) Rotationally symmetric objects([bottle.tcl](https://gitlab.kitware.com/vtk/vtk/blob/ea6f91948c13ee930b181a2aaf5d6431ebe30eb1/graphics/examplesTcl/bottle.tcl)).
[Figure 8-41c](/Cxx/Modelling/Spring) | vtkRotationalExtrusionFilter | (c) Rotation in combination with linear displacement and radius variation ([spring.tcl](https://gitlab.kitware.com/vtk/vtk/blob/da314198bb8fbdab6f59e8a69b2d97f1611a05bd/graphics/examplesTcl/spring.tcl)).

## Chapter 9 - Advanced Algorithms

| Figure | Classes Demonstrated | Caption | Image |
|--------|----------------------|---------|-------|
[Figure 9-4a](/Cxx/VisualizationAlgorithms/ExponentialCosine) | vtkWarpScalar | Carpet plots. (a) Visualization of an exponential cosine function. Function values are indicated by surface displacement. Colors indicate derivative values ([expCos.cxx](https://gitlab.kitware.com/vtk/vtk/blob/5881e35ac8e508ab187478234c58fcd9559ee2de/Filters/General/Testing/Cxx/expCos.cxx)).
[Figure 9-4b](/Cxx/VisualizationAlgorithms/WarpCombustor) | vtkWarpScalar vtkMultiBlockPLOT3DReader | Carpet plots. (b) Carpet plot of combustor flow energy in a structured grid. Colors and plane displacement represent energy values ([warpComb.tcl](https://gitlab.kitware.com/vtk/vtk/blob/fdc214b9c2c6f911b66588fc898a932da0aa6755/Examples/VisualizationAlgorithms/Tcl/warpComb.tcl)).
[Figure 9-10](/Cxx/VisualizationAlgorithms/CreateBFont) | vtkClipPolyData vtkImageDataGeometryFilter | A scanned image clipped with a scalar value of 1/2 its maximum intensity produces a mixture of quadrilaterals and triangles ([createBFont.tcl](https://gitlab.kitware.com/vtk/vtk/blob/cdd4d6fdec8b4b2c143224ca1d94699c96a8b58a/Filters/Core/Testing/Tcl/createBFont.tcl)).
igure 9-12d | | The stream polygon. (d) Sweeping polygon to form tube ([officeTube.tcl](https://gitlab.kitware.com/vtk/vtk/blob/2d323fc4f7476ad024d0f4a164a0930f005bc154/Examples/VisualizationAlgorithms/Tcl/officeTube.tcl)) .
Figure 9-15 | | Example of hyperstreamlines (Hyper.tcl). The four hyperstreamlines shown are integrated along the minor principle stress axis. A plane (colored with a different lookup table) is also shown.
Figure 9-19 | | Probing data in a combustor.  Probes are regular array of 50 2 points that are then passed through a contouring filter (probeComb.tcl).
Figure 9-21 | | Triangle strip examples. (a) Structured triangle mesh consisting of 134 strips each of 390 triangles (stripF.tcl). (b) Unstructured triangle mesh consisting of 2227 strips of average length 3.94, longest strip 101 triangles. Images are generated by displaying every other triangle strip (uStripeF.tcl).
[Figure 9-24](/Cxx/Visualization/NormalsDemo) | vtkPolyDataNormals | Surface normal generation. (a) Faceted model without normals.  (b)Polygons must be consistently oriented to accurately compute normals. (c)Sharp edges are poorly represented using shared normals as shown on the corners of this model. (d) Normal generation with sharp edges split (Normals.cxx).
Figure 9-27 | | Examples of decimation algorithm. Triangle meshes are shown in wireframe.  (a) Decimation of laser digitizer data (deciFran.tcl).  (b) Decimation of terrain data (deciHawa.tcl).
[Figure 9-38a](/Cxx/VisualizationAlgorithms/SingleSplat) | vtkGaussianSplatter | Elliptical splatting. (a) Single elliptical splat with eccentricity E=10.  Cone shows orientation of vector ([singleSplat.cxx](https://gitlab.kitware.com/vtk/vtk/blob/97cb084e865ac5b22b441d7010e06b59724caa2e/graphics/examplesCxx/singleSplat.cxx)).
Figure 9-38b | vtkGaussianSplatter | Elliptical splatting. (b) Surface reconstructed using elliptical splats into 100 3 volume followed by isosurface extraction. Points regularly subsampled and overlayed on original mesh (splatFace.tcl). 
Figure 9-43a | | Examples of texture thresholding. (a) Using scalar threshold to show values of flow density on plane above value of 1.5 ([texThresh.tcl](https://gitlab.kitware.com/vtk/vtk/blob/ea6f91948c13ee930b181a2aaf5d6431ebe30eb1/graphics/examplesTcl/texThresh.tcl)).
[Figure 9-43b](/Cxx/Texture/TextureCutSphere) | vtkImplicitTextureCoords | Examples of texture thresholding. (b) Boolean combination of two planes to cut nested spheres ([tcutSph.cxx](https://gitlab.kitware.com/vtk/vtk/blob/3ad5fa14aaa30c57cab400a7494bd6e2eac37bf1/graphics/examplesCxx/tcutSph.cxx)).
[Figure 9-45b](/Cxx/Texture/TextureCutQuadric) | vtkBooleanTexture vtkImplicitTextureCoords | (b) Sixteen boolean textures applied to sphere ([quadricCut.cxx](https://gitlab.kitware.com/vtk/vtk/blob/3ad5fa14aaa30c57cab400a7494bd6e2eac37bf1/graphics/examplesCxx/quadricCut.cxx))
Figure 9-47 | | Using random point seeds to create streamlines (office.tcl)
Figure 9-48 | | A plane clipped with a sphere and an ellipse. The two transforms place each implicit function into the appropriate position. Two outputs are generated by the clipper.  (clipSphCyl.tcl).
Figure 9-50 | | Visualization of multidimensional financial data. Visualization network, output image, and sample C++ code are shown (finance.cxx). The gray/wireframe surface represents the total data population. The dark surface represents data points delinquent on loan payment.
Figure 9-51 | | Applying connectivity filter to remove noisy isosurfaces (connPineRoot.tcl). Data is from 256 3 volume data of the root system of a pine tree.
Figure 9-52 | | Applying connectivity and decimation filters to remove noisy isosurfaces and reduce data size (deciPineRoot.tcl). Data is from 256 3 volume data of the root system of a pine tree.
Figure 9-53 | | Texture cut used to reveal internal structure of a motor. Two cut planes are used in combination with transparent texture (motor.tcl). 
Figure 9-54 | | Two-dimensional Delaunay triangulation of a random set of points. Points and edges are shown highlighted with sphere glyphs and tubes (DelMesh.tcl) . Only the pipeline to generate triangulation is shown.

## Chapter 10 - Image Processing

| Figure | Classes Demonstrated | Caption | Image |
|--------|----------------------|---------|-------|
Figure 10-2 | | Low-pass filters can be implemented as convolution with a Gaussian kernel.  The Gaussian kernel displayed on top has been magnified for this figure (GaussianSmooth.tcl).
Figure 10-3 | | Comparison of Gaussian and Median smoothing for reducing low-probability high-amplitude noise (MedianComparison.tcl)
Figure 10-4 | | Comparison of median and hybrid-median filters. The hybrid filter preserves corners and thin lines, better than the median filter. The lower patterns represent the three neighborhoods used to compute the hybrid median (see the example Tcl script HybridMedianComparison.tcl)
Figure 10-5 | | This figure demonstrates aliasing that occurs when a high-frequency signal is subsampled. High frequencies appear as low frequency artifacts. The lower left image is an isosurface of a skull after subsampling. The right image used a low-pass filter before subsampling to reduce aliasing (IsoSubsample.tcl).
Figure 10-6 | | This MRI image illustrates attenuation that can occur due to sensor position.  The artifact is removed by dividing by the attenuation profile determined manually.  This histograms shows how the artifact hides information in the form of scalar value clusters (Attenuation.tcl).
Figure 10-9 | | High-pass filters can extract and enhance edges in an image. Subtraction of the Laplacian (middle) from the original image (left) results in edge enhancement or a sharpening operation (right) (EnhanceEdges.tcl). 
Figure 10-10 | | The discrete Fourier transform changes an image from the spatial domain into the frequency domain, where each pixel represents a sinusoidal function. This figure show an image and its power spectrum displayed using a logarithmic transfer function (VTKSpectrum.tcl). 
Figure 10-11 | | This figure shows two high-pass filters in the frequency domain. The Butterworth high-pass filter has a gradual attenuation that avoids ringing produced by the ideal high-pass filter with an abrupt transition (IdealHighPass.tcl). 
Figure 10-14 | | This figure demonstrates various binary filters that can alter the shape of segmented regions (MorphComparison.tcl). 
Figure 10-16 | | An imaging pipeline to visualize gradient information. The gradient direction is mapped into color hue value while the gradient magnitude is mapped into the color saturation (ImageGradient.tcl).
Figure 10-17 | | Combining the imaging and visualization pipelines to deform an image in the z-direction (imageWarp.tcl). The vtkMergeFilter is used to combine the warped surface with the original color data.

## Chapter 12 - Applications

| Figure | Classes Demonstrated | Caption | Image |
|--------|----------------------|---------|-------|
[Figure 12-2](/Cxx/Medical/MedicalDemo1) | | The skin extracted from a CT dataset of the head ([Medical1.cxx](https://gitlab.kitware.com/vtk/vtk/blob/2d323fc4f7476ad024d0f4a164a0930f005bc154/Examples/Medical/Cxx/Medical1.cxx)).
[Figure 12-3](/Cxx/Medical/MedicalDemo2) | | Skin and bone isosurfaces ([Medical2.cxx](https://gitlab.kitware.com/vtk/vtk/blob/2d323fc4f7476ad024d0f4a164a0930f005bc154/Examples/Medical/Cxx/Medical2.cxx)).
[Figure 12-4](/Cxx/Medical/MedicalDemo3) | | Composite image of three planes and translucent skin [Medical3.cxx](https://gitlab.kitware.com/vtk/vtk/blob/2d323fc4f7476ad024d0f4a164a0930f005bc154/Examples/Medical/Cxx/Medical3.cxx).
Figure 12-6 | | Photographic slice of frog (upper left), segmented frog (upper right) and composite aof photo and segmentation (bottom). The purple color represents the stomach and the kidneys are yellow (frogSlice.tcl).
Figure 12-7 | | The frog’s brain. Model extracted without smoothing (left) and with smoothing (right).<
Figure 12-10 | | Two views from the stock visualization script. The top shows closing price over time; the bottom shows volume over time (stocks.tcl).
[Figure 12-13](/Cxx/Visualization/BlobbyLogo) | vtkImplicitModeller | A logo created with vtkImplicitModeller ([vtkLogo.cxx](https://gitlab.kitware.com/vtk/vtk/blob/3ad5fa14aaa30c57cab400a7494bd6e2eac37bf1/graphics/examplesCxx/vtkLogo.cxx)).
Figure 12-14 | | Portion of computational grid for the LOx post (LOxGrid.tcl).
[Figure 12-16](/Cxx/VisualizationAlgorithms/LOx) | vtkStreamTracer vtkTubeFilter | Streamtubes created by using the computational grid just in front of the post as a source for seeds ([LOx.tcl](https://gitlab.kitware.com/vtk/vtk/blob/ea6f91948c13ee930b181a2aaf5d6431ebe30eb1/graphics/examplesTcl/LOx.tcl)).
Figure 12-17 | | Ten frames from a blow molding finite element analysis. Mold halves (shown in wireframe) are closed around a parison as the parison is inflated. Coloring indicates thickness—red areas are thinner than blue (blow.tcl)
Figure 12-20 | | Towers of Hanoi. (a) Initial configuration. (b) Intermediate configuration.  (c) Final configuration (Hanoi.cxx).

 LocalWords:  documention
