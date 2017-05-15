### Description
[]([File:VTK_Examples_Python_DataManipulation_LineOnMesh1.png?|x300px|]][[File:VTK_Examples_Python_DataManipulation_LineOnMesh2.png?|x300px|?])

Create a terrain with regularly spaced points and smooth the terrain (see []([VTK/Examples/Python/PolyData/SubdivisionFilters]).
Then, a vtkCellLocator is used to find the intersection between vertical lines and the surface (using the IntersectWithLine method). Each intersection is saved as x, y, z coordinates and used to plot a spline on the surface.

*Contributed by Michka Popoff
