### Description
#### Produce streamlines in the combustor dataset.

This example demonstrates how to use the vtkLineWidget to seed and
manipulate streamlines. Two line widgets are created. The first is invoked
by pressing '**i**', the second by pressing '**L**' (capital). Both can exist
together.

If the fourth parameter is non-zero, it is used to generate an image with streamlines:
 1) The third parameter value is changed to 25.
 2) The camera position and first line widget are positioned differently.
 3) The streamlines are displayed running from the first line widget.
 4) The second line widget is still available.
 
In the C++ version, note how we handle callbacks by first implementing a class, then instantiating it and then passing references to the needed variables to it. Finally we add it as an observer.

For the Python version we define a class passing the needed variables in the `__init__` function and then implementing a `_call__` function that does the work.
