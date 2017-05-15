### Description
<p>In this example a mesh is read from a file and then subdivided using linear subdivision. The SetNumberOfSubdivisions(n) function controls how many times the mesh is subdivided. For each n, the number of triangles will increase by approximately a factor of 4. For example, if n=2, the number of triangles in the resulting mesh will be 16x the number of triangles in the original mesh.<br />

Different types of subdivisions can be obtained by replacing vtkLinearSubdivisionFilter with either vtkLoopSubdivisionFilter or vtkButterflySubdivisionFilter.</p>A tutorial on how to setup a Windows Forms Application utilizing ActiViz.NET can be found here: [Setup a Windows Forms Application to use ActiViz.NET](http://www.vtk.org/Wiki/VTK/CSharp/ActiViz.NET)<br />
Note: As long as ActiViz.NET is not build with VTK version 6.0 or higher you must define the preprocessor directive VTK_MAJOR_VERSION_5.
