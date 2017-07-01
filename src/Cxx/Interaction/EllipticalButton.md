### Description
This example creates a 3D button using vtkEllipsoidalButton. Interaction is done by assigning the button to a vtkProp3DButtonRepresentation. Then a callback for a vtkButtonWidget controls the color of the button and the displayed geometry. Click on the button to see the color of both the button and geometry change.

!!! warning
    There is a bug in vtkEllipticalButtonSource. If CircumferentialResolution is odd, improper geometry is created.

!!! warning
    Values close to 1.0 for RadialRatio can cause shading artifacts at the corners of the button.



