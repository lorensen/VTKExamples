### Description

vtkCylinderSource object creates a polygonal cylinder centered at Center.

The axis of the cylinder is aligned along the global y-axis. The height and radius of the cylinder can be specified, as well as the number of sides. 

It is also possible to control whether the cylinder is open-ended or capped. If you have the end points of the cylinder, you should use a vtkLineSource followed by a vtkTubeFilter instead of the vtkCylinderSource.
