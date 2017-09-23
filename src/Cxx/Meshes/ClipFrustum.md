### Description
The example uses vtkClipPolyData to clip a model with a vtkCamera's view frustum. The frustum is displayed using vtkFrustumSource.

The example proceeds as follow:

1. Read a vtkPolyData. The example can read any of the supported polydata readers.
2. Generates a view of the model.
3. Recovers the view frustum of the current vtkCamera.
4. Creates an implicit function using vtkPlanes::SetFrustumPlanes.
5. Passes the vtkPlanes to vtkFrustumSource.
6. Passes the vtkPlanes to vtkClipPolyData as the *ClipFunction*.
7. Tells vtkClipPolyData to generate vtkPolyData for inside and outside.
8. Presents the frustum, and clipped models. The inside model is red and the outside model is gold.

!!! bug
    The first attempt to write the example used vtkClipConvexPolyData, but that filter has bugs and only works with one plane.
