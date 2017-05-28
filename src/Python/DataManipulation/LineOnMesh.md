### Description

Create a terrain with regularly spaced points and smooth the terrain (see [SmoothMeshgrid](/Python/PolyData/SmoothMeshGrid).
Then, a vtkCellLocator is used to find the intersection between vertical lines and the surface (using the IntersectWithLine method). Each intersection is saved as x, y, z coordinates and used to plot a spline on the surface.

* Contributed by Michka Popoff
