### Description

This example demonstrates how to color the individual faces of an annotated cube.

This is based on a very nice example by Rodrigo Figueiredo
  in [this discussion](https://discourse.vtk.org/t/colors-of-vtkannotatedcubeactor-faces-with-vtkorientationmarkerwidget/934/1).

The process is:

- Create the annotated cube actor using vtkAnnotatedCubeActor.
- Select the names on the faces, text colors and, if needed, any rotations of the text.
- Make the annotated cube transparent.
- Create a cube actor with colored faces.
- Combine the annotated cube actor and cube actor into a prop assembly using vtkPropAssembly. Since the annotated cube and the cube are the same size you get an assembly with colored cube faces and the requisite text.
- Create a vtkOrientationMarkerWidget and set the set the orientation marker to be the prop assembly.

The function `MakeAnnotatedCubeActor` generates the annotated cube with different colored faces which is then added to a vtkOrientationMarkerWidget.

The colored annotated cube is then placed in the lower left of the view (default). Additionally, a vtkOrientationMarkerWidget containing an axes actor has been added to the lower right of the view.
