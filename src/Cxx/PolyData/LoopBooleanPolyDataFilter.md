### Description
The vtkLoopBooleanPolyDataFilter works best with "clean" data, so this examples first runs vtkTriangleFilter and then vtkCleanPolyData.

This example can be run in three ways:

1.  *LoopBooleanPolyDataFilter* - Computes the intersection of two spheres

2.  *LoopBooleanPolyDataFilter* **intersection|difference|union** - Computes the intersection(difference or union) of two spheres

3.  *LoopBooleanPolyDataFilter* **input1.vtk intersection|difference|union input2.vtk** - Computes the intersection(difference or union) of two vtkPolyData's

!!! seealso
    [BooleanOperationPolyDataFilter](/Cxx/PolyData/BooleanOperationPolyDataFilter) uses an alternative algorithm to do the boolean operations.
