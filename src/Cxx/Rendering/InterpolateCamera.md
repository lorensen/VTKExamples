## Description

This example uses vtkCameraInterpolator to generate a smooth interpolation between camera views. The key points for the cameras' positions are generated from the vtkPolyData's bounding box. The cameras' focal points are at the center of the polydata.

The key points are computed from the corners of the bounding box. They are pushed out along a vector from the center to the corner point. The amount of pushing is a random multiplier of the range of the data.
