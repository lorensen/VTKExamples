### Description
This example uses a vtkBoxWidget to manipulate an actor. The class includes geometry to draw a box around the object, which is bound to it via *SetProp3D*. The box is dimensioned using the *SetPlaceFactor* method, and positioned with the *PlaceWidget* method. After the initial setup, synchronizing the box with the object is done through a custom callback class, which is passed to the box widget through the *AddObserver* method.

For a widget that isn't tied to a specific vtkProp3D and has its geometric representation separate from the interaction logic, see the example [BoxWidget2](/Cxx/Widgets/BoxWidget2).
