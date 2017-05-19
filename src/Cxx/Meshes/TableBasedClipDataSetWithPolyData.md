### Description

The example that shows how to use the vtkTableBasedClipDataSet to clip
a vtkRectilinearGrid with an arbitrary
polydata. vtkImplicitPolyDataDistance is used to turn the polydata
into an implicit function. Every point of the grid is evaluated before
sending to vtkTableBasedClipDataSet. This example uses a vtkConeSource
to generate polydata to use, however any polydata could be used,
including stl files.

The left part of the image shows the inside clip and the distance
field on a center slice. The right side shows the outside clip. When
the program exits using the "e: key, the example will report the cell
type for both the inside and outside clips.

!!! note
    Contrast this with the vtkClipDataSet example: [ClipDataSetWithPolyData](ClipDataSetWithPolyData).

Here is the summary reported when the example exits:
<pre><code>
The clipped dataset(inside) contains a 
vtkUnstructuredGrid that has 14176 cells
	Cell type vtkTetra occurs 3084 times.
	Cell type vtkHexahedron occurs 6820 times.
	Cell type vtkWedge occurs 1196 times.
	Cell type vtkPyramid occurs 3076 times.
------------------------
The clipped dataset(outside) contains a 
vtkUnstructuredGrid that has 125600 cells
	Cell type vtkTetra occurs 3276 times.
	Cell type vtkHexahedron occurs 117732 times.
	Cell type vtkWedge occurs 1260 times.
	Cell type vtkPyramid occurs 3332 times.
</code></pre>
