### Description
This example creates a VTK style float array. This can be easily
interchanged with vtkIntArray, vtkDoubleArray, etc.

The terminology is as follows:

* `SetNumberOfComponents()`: sets the number of elements that a tuple in the array will have. See [VectorArrayKnownLength](/Cxx/Utilities/VectorArrayKnownLength) for an example with tuples with more than one element.

* `SetNumberOfValues()`: sets the number of tuples the array will have. See [UnknownLengthArray](/Cxx/Utilities/UnknownLengthArray) for an example where the number of values is not known in advance.
