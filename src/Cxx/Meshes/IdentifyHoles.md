### Description
This example fills the holes in a mesh and then extracts the filled holes as seprate regions.

The example proceeds as follow:

1. Read the polydata.
2. Fill the holes with vtkFillHolesFilter.
3. Create a new polydata that contains the filled holes. To do this we rely on the fact that the fill holes filter stores the original cells first and then adds the new cells that fill the holes.  Using vtkCellIterator, we skip the original cells and then continue iterating to obtain the new cells.
4. Use vtkConnectivityFilter on the filled polydata to identify the individual holes.

!!! note
    We have to use [vtkConnectivtyFilter](http://www.vtk.org/doc/nightly/html/classvtkConnectivityFilter.html) and not [vtkPolyDataConnectivityFilter](http://www.vtk.org/doc/nightly/html/classvtkPolyDataConnectivityFilter.html) since the later does not create RegionIds cell data.
