<p>Please see <a href="http://www.vtk.org/Wiki/VTK/Tutorials/PythonEnvironmentSetup this">this</a> page to learn how to setup your environment to use VTK in Python.</p>
<p>It would be appreciated if there are any Python VTK experts who could convert any of the <a href="Cxx">c++ examples</a> to Python!</p>
<div class="toc"><span class="toctitle">Contents</span><ul>
<li><a href="#hello-world">Hello World</a></li>
<li><a href="#simple-operations">Simple Operations</a></li>
<li><a href="#input-and-output">Input and Output</a><ul>
<li><a href="#output">Output</a></li>
<li><a href="#input">Input</a></li>
</ul>
</li>
<li><a href="#working-with-arrays">Working with Arrays</a></li>
<li><a href="#geometric-objects">Geometric Objects</a><ul>
<li><a href="#display">Display</a></li>
<li><a href="#parametric-objects">Parametric Objects</a></li>
</ul>
</li>
<li><a href="#implicit-functions">Implicit Functions</a></li>
<li><a href="#working-with-polydata">Working with PolyData</a></li>
<li><a href="#working-with-3d-data">Working with 3D Data</a><ul>
<li><a href="#working-with-structured-3d-data">Working with Structured 3D Data</a></li>
<li><a href="#working-with-meshes">Working with Meshes</a></li>
</ul>
</li>
<li><a href="#miscellaneous">Miscellaneous</a></li>
<li><a href="#visualization">Visualization</a></li>
<li><a href="#working-with-vtkimagedata">Working with vtkImageData</a></li>
<li><a href="#working-with-exodusii-data">Working with ExodusII Data</a></li>
<li><a href="#graphs">Graphs</a></li>
<li><a href="#user-interaction">User Interaction</a></li>
<li><a href="#infovis">Infovis</a></li>
<li><a href="#geovis">Geovis</a></li>
<li><a href="#widgets">Widgets</a></li>
<li><a href="#utilities">Utilities</a></li>
<li><a href="#web">Web</a></li>
<li><a href="#pyqt">PyQt</a></li>
</ul>
</div>
<h1 id="hello-world">Hello World</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="/Python/Cylinder">Cylinder</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyDataMapper.html">vtkPolyDataMapper</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkActor.html">vtkActor</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkRenderer.html">vtkRenderer</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html">vtkRenderWindow</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html">vtkRenderWindowInteractor</a></td>
<td>Cylinder example from the VTK Textbook and source code. A hello world example</td>
</tr>
</tbody>
</table>
<h1 id="simple-operations">Simple Operations</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="/Python/DistanceBetweenPoints">DistanceBetweenPoints</a></td>
<td>vtkMath::Distance2BetweenPoints</td>
<td></td>
</tr>
</tbody>
</table>
<h1 id="input-and-output">Input and Output</h1>
<h2 id="output">Output</h2>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="/Python/PLYWriter">PLYWriter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPLYWriter.html">vtkPLYWriter</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/STLWriter">STLWriter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSTLWriter.html">vtkSTLWriter</a></td>
<td></td>
</tr>
</tbody>
</table>
<h2 id="input">Input</h2>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="/Python/STLReader">STLReader</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSTLReader.html">vtkSTLReader</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/UnstructuredGridReader">UnstructuredGridReader</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGridReader.html">vtkUnstructuredGridReader</a></td>
<td>Using vtkUnstructuredGridReader to read a (legacy) *.vtk file</td>
</tr>
<tr>
<td><a href="/Python/VTPReader">VTPReader</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkXMLPolyDataReader.html">vtkXMLPolyDataReader</a></td>
<td></td>
</tr>
</tbody>
</table>
<h1 id="working-with-arrays">Working with Arrays</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="/Python/Arrays/GetValues">GetValues</a></td>
<td>GetTuple3</td>
<td></td>
</tr>
<tr>
<td><a href="/Python/Arrays/RenameArray">RenameArray</a></td>
<td>SetName</td>
<td></td>
</tr>
</tbody>
</table>
<h1 id="geometric-objects">Geometric Objects</h1>
<h2 id="display">Display</h2>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="/Python/GeometricObjects/Display/Arrow">Arrow</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkArrowSource.html">vtkArrowSource</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/Axes">Axes</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkAxesActor.html">vtkAxesActor</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/Cell3DDemonstration">Cell3DDemonstration</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkHexagonalPrism.html">vtkHexagonalPrism</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkHexahedron.html">vtkHexahedron</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkPentagonalPrism.html">vtkPentagonalPrism</a>  <a href="http://www.vtk.org/doc/nightly/html/classvtkPolyhedron.html">vtkPolyhedron</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkPyramid.html">vtkPyramid</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkTetra.html">vtkTetra</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkVoxel.html">vtkVoxel</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkWedge.html">vtkWedge</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html">vtkUnstructuredGrid</a></td>
<td>Sample objects are generated from the classes derived from vtkCell3D and displayed.</td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/ColoredLines">ColoredLines</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCellData.html">vtkCellData</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkLine.html">vtkLine</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/Cone">Cone</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkConeSource.html">vtkConeSource</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/Cube">Cube</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCubeSource.html">vtkCubeSource</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/Cylinder">Cylinder</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCylinderSource.html">vtkCylinderSource</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/DataSetSurface">DataSetSurface</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDataSetSurfaceFilter.html">vtkDataSetSurfaceFilter</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/Disk">Disk</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDiskSource.html">vtkDiskSource</a></td>
<td>A circle with a hole in it.</td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/Frustum">Frustum</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkFrustumSource.html">vtkFrustumSource</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/GeometricObjectsDemo">GeometricObjectsDemo</a></td>
<td></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/Hexahedron">Hexahedron</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkHexahedron.html">vtkHexahedron</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/LineSource">LineSource</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLineSource.html">vtkLineSource</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/LongLine">LongLine</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLine.html">vtkLine</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/OrientedArrow">OrientedArrow</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkArrowSource.html">vtkArrowSource</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/Plane">Plane</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPlaneSource.html">vtkPlaneSource</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/PlanesIntersection">PlanesIntersection</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPlanesIntersection.html">vtkPlanesIntersection</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/Planes">Planes</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPlanes.html">vtkPlanes</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkHull.html">vtkHull</a></td>
<td>We create a convex hull of the planes for display purposes.</td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/PlatonicSolid">PlatonicSolid</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPlatonicSolidSource.html">vtkPlatonicSolidSource</a></td>
<td>All five platonic solids are displayed.</td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/PointSource">PointSource</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPointSource.html">vtkPointSource</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/Point">Point</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPoints.html">vtkPoints</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/PolyLine">PolyLine</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyLine.html">vtkPolyLine</a></td>
<td>This example demonstrates how to create a polygon through several ordered points.</td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/PolygonIntersection">PolygonIntersection</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolygon.html">vtkPolygon</a></td>
<td>IntersectWithLine()</td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/Polygon">Polygon</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolygon.html">vtkPolygon</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/Pyramid">Pyramid</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPyramid.html">vtkPyramid</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/Quad">Quad</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkQuad.html">vtkQuad</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/RegularPolygonSource">RegularPolygonSource</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRegularPolygonSource.html">vtkRegularPolygonSource</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/Sphere">Sphere</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSphereSource.html">vtkSphereSource</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/Tetrahedron">Tetrahedron</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTetra.html">vtkTetra</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/TextActor">TextActor</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTextActor.html">vtkTextActor</a></td>
<td>2D "HUD-type" text</td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/TriangleStrip">TriangleStrip</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTriangleStrip.html">vtkTriangleStrip</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/Triangle">Triangle</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTriangle.html">vtkTriangle</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/Display/Vertex">Vertex</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkVertex.html">vtkVertex</a></td>
<td></td>
</tr>
</tbody>
</table>
<h2 id="parametric-objects">Parametric Objects</h2>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="/Python/GeometricObjects/ParametricObjectsDemo">ParametricObjectsDemo</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkParametricBoy.html">vtkParametricBoy</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricConicSpiral.html">vtkParametricConicSpiral</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricCrossCap.html">vtkParametricCrossCap</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricDini.html">vtkParametricDini</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricEllipsoid.html">vtkParametricEllipsoid</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricEnneper.html">vtkParametricEnneper</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricFigure8Klein.html">vtkParametricFigure8Klein</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricKlein.html">vtkParametricKlein</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricMobius.html">vtkParametricMobius</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricRandomHills.html">vtkParametricRandomHills</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricRoman.html">vtkParametricRoman</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricSpline.html">vtkParametricSpline</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricSuperEllipsoid.html">vtkParametricSuperEllipsoid</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricSuperToroid.html">vtkParametricSuperToroid</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricTorus.html">vtkParametricTorus</a></td>
<td>All the objects are displayed in a 4X4 array.</td>
</tr>
<tr>
<td><a href="/Python/GeometricObjects/ParametricObjects">ParametricObjects</a></td>
<td></td>
<td>Uncomment the object that you wish to be displayed.</td>
</tr>
</tbody>
</table>
<h1 id="implicit-functions">Implicit Functions</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="/Python/Implicit/Boolean">Boolean</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImplicitBoolean.html">vtkImplicitBoolean</a></td>
<td>Demonstrate booleans of two different implicit functions</td>
</tr>
<tr>
<td><a href="/Python/Implicit/Quadric">Quadric</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkQuadric.html">vtkQuadric</a></td>
<td>Create an ellipsoid using an implicit quadric</td>
</tr>
<tr>
<td><a href="/Python/Implicit/Sphere">Sphere</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSphere.html">vtkSphere</a></td>
<td>Demonstrate sampling of a sphere implicit function</td>
</tr>
</tbody>
</table>
<h1 id="working-with-polydata">Working with PolyData</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="/Python/PolyData/BooleanOperationPolyDataFilter">BooleanOperationPolyDataFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBooleanOperationPolyDataFilter.html">vtkBooleanOperationPolyDataFilter</a></td>
<td>This example performs a boolean operation (Intersection, Union, Difference) of two PolyData</td>
</tr>
<tr>
<td><a href="/Python/ColoredTriangle">ColoredTriangle</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTriangle.html">vtkTriangle</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/Filtering/CombinePolyData">CombinePolyData</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkAppendPolyData.html">vtkAppendPolyData</a></td>
<td>This example combines Polydata objects, and displays the result to the screen.</td>
</tr>
<tr>
<td><a href="/Python/CurvaturesDemo">CurvaturesDemo</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCurvatures.html">vtkCurvatures</a>,  <a href="http://www.vtk.org/doc/nightly/html/classvtkColorTransferFunction.html">vtkColorTransferFunction</a></td>
<td>Demonstrates how to get the Gaussian and Mean curvatures of a surface.</td>
</tr>
<tr>
<td><a href="/Python/DottedLine">DottedLine</a></td>
<td>vtkActor::GetProperty::SetLineStipplePattern</td>
<td></td>
</tr>
<tr>
<td><a href="/Python/FilledPolygon">FilledPolygon</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCutter.html">vtkCutter</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/PolyData/ImplicitPolyDataDistance">ImplicitPolyDataDistance</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImplicitPolyDataDistance.html">vtkImplicitPolyDataDistance</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/IterativeClosestPoints">IterativeClosestPoints</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkIterativeClosestPointTransform.html">vtkIterativeClosestPointTransform</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/DataManipulation/KochSnowflake.py">KochSnowflake</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkCellArray.html">vtkCellArray</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkPoints.html">vtkPoints</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkPolyLine.html">vtkPolyLine</a></td>
<td>This example draws a Koch snowflake fractal using recursive functions and some of the convenient tools in the toolkit.</td>
</tr>
<tr>
<td><a href="/Python/DataManipulation/LineOnMesh">LineOnMesh</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCellLocator.html">vtkCellLocator</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParametricSpline.html">vtkParametricSpline</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/MeshLabelImageColor">MeshLabelImageColor</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDiscreteMarchingCubes.html">vtkDiscreteMarchingCubes</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/MeshLabelImage">MeshLabelImage</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDiscreteMarchingCubes.html">vtkDiscreteMarchingCubes</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/Outline">Outline</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkOutlineFilter.html">vtkOutlineFilter</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/PolyData/PolyDataContourToImageData">PolyDataContourToImageData</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLinearExtrusionFilter.html">vtkLinearExtrusionFilter</a>,<a href="http://www.vtk.org/doc/nightly/html/classvtkPolyDataToImageStencil.html">vtkPolyDataToImageStencil</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/PolyData/PolyDataToImageDataStencil">PolyDataToImageDataStencil</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyDataToImageStencil.html">vtkPolyDataToImageStencil</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/RotationAroundLine">RotationAroundLine</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTransformPolyDataFilter.html">vtkTransformPolyDataFilter</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/PolyData/RuledSurfaceFilter">RuledSurfaceFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRuledSurfaceFilter.html">vtkRuledSurfaceFilter</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/SolidColoredTriangle">SolidColoredTriangle</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTriangle.html">vtkTriangle</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/PolyData/SubdivisionFilters">SubdivisionFilters</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLoopSubdivisionFilter.html">vtkLoopSubdivisionFilter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkButterflySubdivisionFilter.html">vtkButterflySubdivisionFilter</a></td>
</tr>
<tr>
<td><a href="/Python/TriangleColoredPoints">TriangleColoredPoints</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkUnsignedCharArray.html">vtkUnsignedCharArray</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/TriangleCornerVertices">TriangleCornerVertices</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCellArray.html">vtkCellArray</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/TriangleCorners">TriangleCorners</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkXMLPolyDataWriter.html">vtkXMLPolyDataWriter</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/PolyData/WarpVector.py">WarpVectorpy</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLine.html">vtkLine</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkDoubleArray.html">vtkDoubleArray</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkWarpVector.html">vtkWarpVector</a></td>
<td>This example warps/deflects a line.</td>
</tr>
<tr>
<td><a href="/Python/WriteTriangleToFile">WriteTriangleToFile</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTriangle.html">vtkTriangle</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/DataManipulation/Cube.py">py</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPolyData.html">vtkPolyData</a></td>
<td></td>
</tr>
</tbody>
</table>
<h1 id="working-with-3d-data">Working with 3D Data</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="/Python/PolyData/ExtractSelection">ExtractSelection</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkExtractSelection.html">vtkExtractSelection</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/PolyData/ExtractSelectionCells">ExtractSelectionCells</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkExtractSelection.html">vtkExtractSelection</a></td>
<td>extract cell, select cell</td>
</tr>
</tbody>
</table>
<h2 id="working-with-structured-3d-data">Working with Structured 3D Data</h2>
<p>This section includes vtkImageData, vtkStructuredGrid, and vtkRectilinearGrid.</p>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="/Python/RectilinearGrid/RectilinearGrid">RectilinearGrid</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html">vtkRectilinearGrid</a></td>
<td>create a rectilinear grid</td>
</tr>
</tbody>
</table>
<h2 id="working-with-meshes">Working with Meshes</h2>
<p>This section includes examples of manipulating meshes.</p>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="/Python/Meshes/ClipDataSetWithPolydata">ClipDataSetWithPolydata</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkClipDataSet.html">vtkClipDataSet</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkImplicitPolyDataDistance.html">vtkImplicitPolyDataDistance</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkRectilinearGrid.html">vtkRectilinearGrid</a></td>
<td>clip a vtkRectilinearGrid with arbitrary polydata. In this example, use a vtkConeSource to generate polydata to slice the grid, resulting in an unstructured grid.</td>
</tr>
</tbody>
</table>
<h1 id="miscellaneous">Miscellaneous</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="/Python/BackgroundImage">BackgroundImage</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkJPEGReader.html">vtkJPEGReader</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkImageCanvasSource2D.html">vtkImageCanvasSource2D</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkImageActor.html">vtkImageActor</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkSuperquadricSource.html">vtkSuperquadricSource</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/Cutter">Cutter</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCutter.html">vtkCutter</a></td>
<td></td>
</tr>
<tr>
<td>[ImplicitDataSet](ImplicitDataSet](http://www.vtk.org/doc/nightly/html/classvtkImplicitDataSet.html)]( vtkIdType</td>
<td>n/a</td>
<td>This is just a typedef, Python, you can use a python "int" or "long" for vtkIdType.</td>
</tr>
<tr>
<td><a href="/Python/Screenshot">Screenshot</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkWindowToImageFilter.html">vtkWindowToImageFilter</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/Variant">Variant</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkVariant.html">vtkVariant</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/vtkVersion">vtkVersion</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkVersion.html">vtkVersion</a></td>
<td></td>
</tr>
</tbody>
</table>
<h1 id="visualization">Visualization</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="/Python/Animation">Animation</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTimerCallback.html">vtkTimerCallback</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/Visualization/AssignCellColorsFromLUT">AssignCellColorsFromLUT</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkNamedColors.html">vtkNamedColors</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkPlaneSource.html">vtkPlaneSource</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html">vtkLookupTable</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkColorTransferFunction.html">vtkColorTransferFunction</a></td>
<td>Demonstrates how to assign colors to cells in a vtkPolyData structure using lookup tables.</td>
</tr>
<tr>
<td><a href="/Python/Camera">Camera</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCamera.html">vtkCamera</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/Visualization/ClampGlyphSizes">ClampGlyphSizes</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html">vtkGlyph3D</a></td>
<td>Use vtkGlyph3D with ClampingOn to limit glyph sizes</td>
</tr>
<tr>
<td><a href="/Python/ColorActor">ColorActor</a></td>
<td>vtkActor::GetProperty()::SetColor</td>
<td></td>
</tr>
<tr>
<td><a href="/Python/Visualization/CubeAxesActor">CubeAxesActor</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCubeAxesActor.html">vtkCubeAxesActor</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/Visualization/CurvatureBandsWithGlyphs">CurvatureBandsWithGlyphs</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCurvatures.html">vtkCurvatures</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkBandedPolyDataContourFilter.html">vtkBandedPolyDataContourFilter</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html">vtkLookupTable</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkColorSeries.html">vtkColorSeries</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html">vtkGlyph3D</a></td>
<td>Demonstrates the coloring of a surface by partitioning the gaussian curvature of a surface into bands and using arrows to display the normals on the surface.</td>
</tr>
<tr>
<td><a href="/Python/Visualization/ElevationBandsWithGlyphs">ElevationBandsWithGlyphs</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBandedPolyDataContourFilter.html">vtkBandedPolyDataContourFilter</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html">vtkLookupTable</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkColorSeries.html">vtkColorSeries</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html">vtkGlyph3D</a></td>
<td>Demonstrates the coloring of a surface by partitioning the elevation into bands and using arrows to display the normals on the surface.</td>
</tr>
<tr>
<td><a href="/Python/Visualization/GlyphTable">GlyphTable</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGlyph3D.html">vtkGlyph3D</a></td>
<td>Vary the shapes of glyphed points using a glyph table</td>
</tr>
<tr>
<td><a href="/Python/Visualization/HardwareSelector">HardwareSelector</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkHardwareSelector.html">vtkHardwareSelector</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/InteractorStyleTrackballActor">InteractorStyleTrackballActor</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackBallActor.html">vtkInteractorStyleTrackBallActor</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/InteractorStyleTrackballCamera">InteractorStyleTrackballCamera</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackBallCamera.html">vtkInteractorStyleTrackBallCamera</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/MultipleViewports">MultipleViewports</a></td>
<td>vtkRenderer::SetViewport</td>
<td></td>
</tr>
<tr>
<td><a href="/Python/Visualization/NamedColorPatches">NamedColorPatches</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkNamedColors.html">vtkNamedColors</a></td>
<td>Creates a HTML file called <a href="/Python/Visualization/VTKNamedColorPatches.html">VTKNamedColorPatches.html</a> showing the available colors in the vtkNamedColors class.</td>
</tr>
<tr>
<td><a href="/Python/Visualization/NamedColors">NamedColors</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkNamedColors.html">vtkNamedColors</a></td>
<td>Demonstrates how to use the vtkNamedColor class</td>
</tr>
<tr>
<td><a href="/Python/Visualization/PointSize">PointSize</a></td>
<td>vtkActor::GetProperty()::SetPointSize</td>
<td></td>
</tr>
<tr>
<td><a href="/Python/Visualization/ProgGlyph">ProgGlyph</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkProgrammableGlyphFilter.html">vtkProgrammableGlyphFilter</a></td>
<td>Vary the shapes of glyphed points using a programmable glyph filter</td>
</tr>
<tr>
<td><a href="/Python/Visualization/QuadraticSurface">QuadraticSurface</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkQuadric.html">vtkQuadric</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/Visualization/SphereTexture">SphereTexture</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTextureMapToSphere.html">vtkTextureMapToSphere</a></td>
<td>Apply an ImageData texture to an sphere</td>
</tr>
<tr>
<td><a href="/Python/Visualization/Streamlines">Streamlines</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkStreamLine.html">vtkStreamLine</a></td>
<td>Seed streamlines with vectors from a structured grid</td>
</tr>
<tr>
<td><a href="/Python/TextSource">TextSource</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTextSource.html">vtkTextSource</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/UnstructuredTransientVolumeRendering">UnstructuredTransientVolumeRendering</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGridVolumeRayCastMapper.html">vtkUnstructuredGridVolumeRayCastMapper</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/WindowTitle">WindowTitle</a></td>
<td>vtkRenderWindow::SetWindowName</td>
<td></td>
</tr>
</tbody>
</table>
<h1 id="working-with-vtkimagedata">Working with vtkImageData</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="/Python/ImageWeightedSum">ImageWeightedSum</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageWeightedSum.html">vtkImageWeightedSum</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/SumVTKImages">SumVTKImages</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageWeightedSum.html">vtkImageWeightedSum</a></td>
<td>A function to simplify the summing of images, where you can pass a list of images and</td>
</tr>
<tr>
<td><a href="/Python/WriteReadVtkImageData">WriteReadVtkImageData</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkImageData.html">vtkImageData</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkXMLImageDataReader.html">vtkXMLImageDataReader</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkXMLImageDataWriter.html">vtkXMLImageDataWriter</a></td>
<td></td>
</tr>
<tr>
<td>weights.</td>
<td></td>
<td></td>
</tr>
</tbody>
</table>
<h1 id="working-with-exodusii-data">Working with ExodusII Data</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="/Python/ExodusII/Read">Read</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkExodusIIReader.html">vtkExodusIIReader</a></td>
<td>A simple script for reading and viewing ExodusII data interactively.</td>
</tr>
</tbody>
</table>
<h1 id="graphs">Graphs</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="/Python/Graphs/EdgeWeights">EdgeWeights</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html">vtkMutableDirectedGraph</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html">vtkGraphLayoutView</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/Graphs/NOVCAGraph">NOVCAGraph</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkUnstructuredGrid.html">vtkUnstructuredGrid</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkXMLUnstructuredGridWriter.html">vtkXMLUnstructuredGridWriter</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/Graphs/SelectedVerticesAndEdges">SelectedVerticesAndEdges</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkAnnotationLink.html">vtkAnnotationLink</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html">vtkGraphLayoutView</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/Graphs/VisualizeGraph">VisualizeGraph</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html">vtkMutableDirectedGraph</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html">vtkGraphLayoutView</a></td>
<td></td>
</tr>
</tbody>
</table>
<h1 id="user-interaction">User Interaction</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="/Python/Interaction/HighlightAPickedActor">HighlightAPickedActor</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkPropPicker.html">vtkPropPicker</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballCamera.html">vtkInteractorStyleTrackballCamera</a></td>
<td>Pick and highlight an actor based on mouse clicks.</td>
</tr>
<tr>
<td><a href="/Python/Interaction/MouseEventsObserver">MouseEventsObserver</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCallbackCommand.html">vtkCallbackCommand</a></td>
<td>Use an observer.</td>
</tr>
<tr>
<td><a href="/Python/Interaction/MouseEvents">MouseEvents</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkInteractorStyleTrackballCamera.html">vtkInteractorStyleTrackballCamera</a></td>
<td>Subclass the interactor style.</td>
</tr>
</tbody>
</table>
<h1 id="infovis">Infovis</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="/Python/Infovis/ParallelCoordinatesExtraction">ParallelCoordinatesExtraction</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkExtractSelection.html">vtkExtractSelection</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkAnnotationLink.html">vtkAnnotationLink</a></td>
<td>Extract data based on a selection in a Parallel Coordinates View</td>
</tr>
<tr>
<td><a href="/Python/Infovis/ParallelCoordinatesView">ParallelCoordinatesView</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRTAnalyticSource.html">vtkRTAnalyticSource</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParallelCoordinatesView.html">vtkParallelCoordinatesView</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkParallelCoordinatesRepresentation.html">vtkParallelCoordinatesRepresentation</a></td>
<td>Plotting data attributes in a Parallel Coordinates View</td>
</tr>
<tr>
<td><a href="/Python/Plotting/ScatterPlot">ScatterPlot</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkChartXY.html">vtkChartXY</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/Infovis/SelectedGraphIDs">SelectedGraphIDs</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkAnnotationLink.html">vtkAnnotationLink</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkRandomGraphSource.html">vtkRandomGraphSource</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkGraphLayoutView.html">vtkGraphLayoutView</a></td>
<td>Callback on vtkAnnotationLink in a Graph Layout View when selection is changed</td>
</tr>
<tr>
<td><a href="/Python/Plotting/SpiderPlot">SpiderPlot</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSpiderPlotActor.html">vtkSpiderPlotActor</a></td>
<td></td>
</tr>
</tbody>
</table>
<h1 id="geovis">Geovis</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="/Python/Geovis/GeoAssignCoordinates">GeoAssignCoordinates</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkGeoAssignCoordinates.html">vtkGeoAssignCoordinates</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkMutableDirectedGraph.html">vtkMutableDirectedGraph</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkGraphMapper.html">vtkGraphMapper</a></td>
<td>Draws a sphere, based on longituds and latitudes.</td>
</tr>
</tbody>
</table>
<h1 id="widgets">Widgets</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="/Python/Widgets/BalloonWidget">BalloonWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBalloonWidget.html">vtkBalloonWidget</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkBalloonRepresentation.html">vtkBalloonRepresentation</a></td>
<td>Uses a vtkBalloonWidget to draw labels when the mouse stays above an actor.</td>
</tr>
<tr>
<td><a href="/Python/Widgets/BoxWidget">BoxWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkBoxWidget.html">vtkBoxWidget</a></td>
<td>This 3D widget defines a region of interest that is represented by an arbitrarily oriented hexahedron with interior face angles of 90 degrees (orthogonal faces). The object creates 7 handles that can be moused on and manipulated.</td>
</tr>
<tr>
<td><a href="/Python/Widgets/CompassWidget">CompassWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkCompassWidget.html">vtkCompassWidget</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkCompassRepresentation.html">vtkCompassRepresentation</a></td>
<td>Draws an interactive compass.</td>
</tr>
<tr>
<td><a href="/Python/Widgets/ContourWidget">ContourWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkContourWidget.html">vtkContourWidget</a>, <a href="http://www.vtk.org/doc/nightly/html/classvtkOrientedGlyphContourRepresentation.html">vtkOrientedGlyphContourRepresentation</a></td>
<td>Draw a contour (line) which can be deformed by the user</td>
</tr>
<tr>
<td><a href="/Python/Widgets/OrientationMarkerWidget">OrientationMarkerWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkAnnotatedCubeActor.html">vtkAnnotatedCubeActor</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkOrientationWidget.html">vtkOrientationWidget</a></td>
<td>Draws two cubes. One of them can be clicked to be rotated, and will rotate the second one. The second one has annotations on it, and can also be moved.</td>
</tr>
<tr>
<td><a href="/Python/Widgets/ScalarBarWidget">ScalarBarWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkScalarBarWidget.html">vtkScalarBarWidget</a></td>
<td>The ScalarBarWidget displays a scalar bar that is movable and changes orientation automatically when close to the borders of the image. It needs a ScalarBarActor</td>
</tr>
<tr>
<td><a href="/Python/Widgets/SphereWidget">SphereWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkSphereWidget.html">vtkSphereWidget</a></td>
<td>This 3D widget defines a sphere that can be interactively placed in a scene.</td>
</tr>
<tr>
<td><a href="/Python/Widgets/TextWidget">TextWidget</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkTextWidget.html">vtkTextWidget</a></td>
<td>Annotate a VTK image with movable text</td>
</tr>
</tbody>
</table>
<h1 id="utilities">Utilities</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="/Python/Filtering/Delaunay2D">Delaunay2D</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkDelaunay2D.html">vtkDelaunay2D</a></td>
<td></td>
</tr>
<tr>
<td><a href="/Python/Utilities/LUTUtilities">LUTUtilities</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkLookupTable.html">vtkLookupTable</a> <a href="http://www.vtk.org/doc/nightly/html/classvtkColorSeries.html">vtkColorSeries</a></td>
<td>A utility class for vtkLookupTable allowing you to output the table contents or to compare tables.</td>
</tr>
</tbody>
</table>
<h1 id="web">Web</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="/Python/Web/RemoteRenderer">RemoteRenderer</a></td>
<td>Web/Python</td>
<td>Use vtk to show an interactive visualization on a web page. Remote rendering.</td>
</tr>
</tbody>
</table>
<h1 id="pyqt">PyQt</h1>
<table>
<thead>
<tr>
<th>Example Name</th>
<th>Classes Demonstrated</th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr>
<td><a href="/Python/Widgets/EmbedPyQt">EmbedPyQt</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html">vtkRenderWindowInteractor</a></td>
<td>Shows how to easily embed VTK in PyQt with QVTKRenderWindowInteractor, first example</td>
</tr>
<tr>
<td><a href="/Python/Widgets/EmbedPyQt2">EmbedPyQt2</a></td>
<td><a href="http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html">vtkRenderWindowInteractor</a></td>
<td>Shows how to embed VTK in PyQt with QVTKRenderWindowInteractor, second example</td>
</tr>
</tbody>
</table>