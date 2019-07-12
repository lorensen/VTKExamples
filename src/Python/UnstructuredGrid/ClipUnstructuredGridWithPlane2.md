### Description

The example uses vtkClipDataSet to clip a vtkUnstructuredGrid. The resulting output and clipped output are presented in yellow and red respectively. To illustrate the clipped interfaces, the example uses a vtkTransform to rotate each output about their centers.

Note that this clipping filter does not retain the original cells if they are not clipped.

After exiting, the example reports the number of each cell type for each output:
<pre><code>
The inside dataset contains a
  vtkUnstructuredGrid that has 110148 cells
        Cell type vtkTetra occurs 106998 times.
        Cell type vtkWedge occurs 3150 times.
The clipped dataset contains a
  vtkUnstructuredGrid that has 111824 cells
        Cell type vtkTetra occurs 107420 times.
        Cell type vtkWedge occurs 4404 times.
</code></pre>

Compare these results with [ClipUnstructuredGridWithPlane (C++)](/Cxx/UnstructuredGrid/ClipUnstructuredGridWithPlane) [ClipUnstructuredGridWithPlane (Python)](/Python/UnstructuredGrid/ClipUnstructuredGridWithPlane). Notice that in this example, the original vtkHexahedron in the unclipped regions are converted to vtkTetra. Also, the resulting vtkUnstructuredGrid's have more than 4 times the number of cells.

!!! example "usage"
    ClipUnstructuredGridWithPlane2 treemesh.vtk

!!! info "thanks"
    Thanks to Bane Sullivan for sharing the treemesh.vtk unstructured grid dataset.