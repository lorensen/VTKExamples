### Description
This example creates a VTK style float array of vectors. This can be easily interchanged with vtkIntArray, vtkDoubleArray, etc.

The only difference between this example and the [VectorArrayKnownLength](/Cxx/Utilities/VectorArrayKnownLength) example is that `SetNumberOfValues()` is not called, and `SetTuple()` is replaced by `InsertNextTuple()`. 
