### Description

This example uses vtkExtractEnclosedPoints to select points that exist within a closed vtkPolyData surface. After reading a vtk polydata file, the example generates 10000 random points within the bounding box of the vtkPolyData.

If the polydata is not closed or is non-manifold, the filter does not create an output.

!!! warning
    Expect a warning message from the vtkExecutive is the enclosing polydata is not closed or non-manifold.

