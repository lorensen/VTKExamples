### Description
This example illustrates how to create and display a cylinder that passes through two points.

It demonstrates two different ways to apply the transform:

1. Use [vtkTransformPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkTransformPolyDataFilter.html) to create a new transformed polydata. This method is useful if the transformed polydata is needed later in the pipeline, e.g. vtkGlyph3DFilter.

2. Apply the transform directly to the actor using [vtkProp3D's SetUserMatrix](http://www.vtk.org/doc/nightly/html/classvtkProp3D.html#a950378fc70405a58bd998c00f84a39a3). No new data is produced.

Switch between the two methods by setting USER_MATRIX to **True** or **False**.

!!! See also
    Compare this example with [OrientedArrow](/Python/GeometricObjects/OrientedArrow). The transform is different because the cylinder height direction is along the y-axis and the arrow height is along the x axis.
