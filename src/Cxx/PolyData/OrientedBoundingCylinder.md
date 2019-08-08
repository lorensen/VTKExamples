### Description

This example creates an oriented cylinder that encloses a vtkPolyData. The axis of the cylinder is aligned with the longest axis of the vtkPolyData.

The example proceeds as follow:

1. A vtkOBBTree creates an oriented bounding box. The z dimension of the box is aligned with the longest axis.
2. A vtkQuad finds the center of each face of the bounding box.
3. A vtkLineSource creates a line from the centers of the long axis faces.
4. vtkTubeFilter creates a "cylinder" from the lines with a radius equal to the an inner circle of bounding box.
5. vtkExtractEnclosedPoints determines if there are points outside the initial guess.
6. If there are points outside, the example does a linear search from the initial radius to the outer circle.
