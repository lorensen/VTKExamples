### Description
The vtkBooleanOperationPolyDataFilter works best with "clean" data, so this examples first runs vtkTriangleFilter and then vtkCleanPolyData.

This example can be run in three ways:

1.  *BooleanOperationPolyDataFilter* - Computes the intersection of two spheres

2.  *BooleanOperationPolyDataFilter* **intersection|difference|union** - Computes the intersection(difference or union) of two spheres

3.  *BooleanOperationPolyDataFilter* **input1.vtk intersection|difference|union input2.vtk** - Computes the intersection(difference or union) of two vtkPolyData's

!!! cite
    See [Boolean Operations on Surfaces in VTK Without External Libraries](http://www.vtkjournal.org/browse/publication/797) for details on the algorithm.

!!! seealso
    [LoopBooleanPolyDataFilter](/Cxx/PolyData/LoopBooleanPolyDataFilter) uses an alternative algorithm to do the boolean operations.
