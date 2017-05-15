### Description
This examples cuts a polydata and fits a spline to the resulting polylines. The cut lines are passed through vtkStripper to make them into connected polylines. The lines are passed through vtkTubeFilter to improve the visualization.

The examples takes an optional argument that specifies a vtk polydata file (.vtp). If run without an argument, it processes a sphere.
