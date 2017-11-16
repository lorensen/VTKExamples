### Description

#### Demonstrate how to set up a callback with client data.

Getting the camera orientation after interacting with the image is used as an example.

We define a callback passing the active camera as client data and linking the callback to the  **EndInteractionEvent** of the vtkRenderWindowInteractor class.
This allows us to get the camera orientation after we manipulate the image. We can then copy/paste this data as needed into our camera to set up a nice initial orientation as shown in the example.

To help orient the cone, we use a vtkOrientationMarkerWidget and a vtkOutlineFilter.

##### C++

There are two methodologies in C++.

1. Create a class that inherits from vtkCallbackCommand reimplementing `Execute(` vtkObject `*caller, unsigned long evId, void*)` and setting pointers to a client and/or call data as needed.  When the class is implemented, it becomes the callback function.
2. Create a function with this signature: `void f(` vtkObject `* caller, long unsigned int evId, void* clientData, void* callData)`
  and, where needed, create a vtkCallbackCommand setting its callback to the function we have created.

The example demonstrates both approaches.

In the function **PrintCameraOrientation** note how we convert an array to a vector and get a comma-separated list.

##### Python

In Python the approach is even simpler. We simply define a function to use as the callback with this signature: `def MyCallback(obj, ev):`.
Then, to pass client data to it, we simply do: `MyCallback.myClientData = myClientData`.
This relies on the fact that Python functions are in fact objects and we are simply adding new attributes such as `myClientData` in this case.

An alternative method is to define a class passsing the needed variables in the `__init__` function and then implement a `_call__` function that does the work.

Both approaches are demonstrated in the example.
