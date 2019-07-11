### Description
This example shows how to generate a "cap" on a clipped vtkPolyData. After clipping with vtkClipPolyData, it uses a clever ''trick'' to convert polylines into polygons. If a polydata file is provided, it will cap it. Otherwise it caps a clipped sphere.

!!! warning
    The clipping is done with a scalar field provided by vtkPlane and results may depend on the resolution of the input vtkPolyData.

!!! tip "Style"
    This example collects all of the color definition in the beginning of the example. This makes it easier to make changes to the colors without having to search the code.
