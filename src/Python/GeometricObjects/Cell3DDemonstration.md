### Description

This is a demonstration of how to construct and display geometric
objects using the classes derived from vtkCell3D. For each object we
specify the points and cell Ids.

From this we create an unstructured grid. In some cases a vtkCellArray
is used and the result is added to the unstructured grid, see:
MakePolyhedron() and MakeTetrahedron().

Also demonstrated is the use of vectors to hold the unstructured
grids, mappers, actors and renderers.

The resultant objects are then displayed in a grid.
