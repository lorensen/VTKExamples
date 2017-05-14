### Description
This example illustrates how to create and display an arrow that passes through two points.

It demonstrates two different ways to apply the transform:
# Use [vtkTransformPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkTransformPolyDataFilter.html) to create a new transformed polydata. This method is useful if the transformed polydata is needed later in the pipeline, e.g. vtkGlyph3DFilter.
# Apply the transform directly to the actor using [vtkProp3D's SetUserMatrix](http://www.vtk.org/doc/nightly/html/classvtkProp3D.html#a950378fc70405a58bd998c00f84a39a3). No new data is produced.

Switch between the two methods by setting USER_MATRIX to either <math>True</math> or <math>False</math> as documented in the script.
