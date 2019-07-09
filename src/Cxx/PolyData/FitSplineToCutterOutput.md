### Description
This examples cuts a vtkPolydata and fits a vtkKochanekSpline to the resulting polylines. The cut lines are passed through vtkStripper to make them into connected polylines. Then, the lines are passed through vtkTubeFilter to improve the visualization.

The examples takes an optional argument that specifies a vtk polydata file (.vtp). If run without an argument, it processes a sphere.
