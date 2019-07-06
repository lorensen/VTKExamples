### Description

The example uses vtkTableBasedClipDataSet to clip a vtkUnstructuredGrid. The resulting output and clipped output are presented in yellow and red respectively. To illustrate the clipped interfaces, the example uses a vtkTransform to rotate each output about their centers.

Note that unlike other clipping filters (except for vtkClipPolyData), vtkTableBasedClipDataSet retains the original cells if they are not clipped.

After exiting, the example reports the number of each cell type for each output:
<pre><code>
The inside dataset contains a
  vtkUnstructuredGrid that has 26116 cells
	Cell type vtkTetra occurs 3751 times.
	Cell type vtkHexahedron occurs 17361 times.
	Cell type vtkWedge occurs 628 times.
	Cell type vtkPyramid occurs 4376 times.
The clipped dataset contains a 
  vtkUnstructuredGrid that has 25655 cells
	Cell type vtkTetra occurs 3715 times.
	Cell type vtkHexahedron occurs 16984 times.
	Cell type vtkWedge occurs 616 times.
	Cell type vtkPyramid occurs 4340 times.
</code></pre>

Compare these results with [ClipUnstructuredGridWithPlane2](/Cxx/UnstructuredGrid/ClipUnstructuredGridWithPlane2). Also, the resulting vtkUnstructuredGrid's has 1/4 the number of cells.

!!! example "usage"
    ClipUnstructuredGridWithPlane treemesh.vtk

!!! info "thanks"
    Thanks to Bane Sullivan for sharing the treemesh.vtk unstructured grid dataset.