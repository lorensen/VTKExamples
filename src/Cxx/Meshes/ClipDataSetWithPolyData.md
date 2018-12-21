### Description

The example that shows how to use the vtkClipDataSet to clip a
vtkRectilinearGrid with an arbitrary
polydata. vtkImplicitPolyDataDistance is used to turn the polydata
into an implicit function. Every point of the grid is evaluated before
sending to vtkClipDataSet. This example uses a vtkConeSource to
generate polydata to use, however any polydata could be used,
including stl files.

The left part of the image shows the inside clip and the distance
field on a center slice. The right side shows the outside clip. When
the program exits using the "e: key, the example will report the cell
type for both the inside and outside clips.

!!! note
    This example was translated to C++ from the Python example [here](/Python/Meshes/ClipDataSetWithPolyData).

!!! note
    vtkClipDataSet tetrahedralizes the volume before clipping. Contrast this with the vtkTableBasedClipDataSet example: [TableBasedClipDataSetWithPolyData](/Cxx/Meshes/TableBasedClipDataSetWithPolyData).

Here is the summary reported when the example exits:
<samp>
------------------------
The clipped dataset(inside) contains a 
vtkUnstructuredGrid that has 49514 cells
	Cell type vtkTetra occurs 41034 times.
	Cell type vtkWedge occurs 8480 times.
------------------------
The clipped dataset(outside) contains a 
vtkUnstructuredGrid that has 714434 cells
	Cell type vtkTetra occurs 705090 times.
	Cell type vtkWedge occurs 9344 times.
</samp>
