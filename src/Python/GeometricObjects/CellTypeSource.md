### Description

This example uses vtkCellTypeSource to generate a vtkUnstructuredGrid. If a cell does not fill a rectangular area or volume, then multiple cells will be generated. For example, a vtkTetra requires 12 cells to fill a cube. A vtkTriangle requires two cells to fill a square. vtkCellTypeSource generates a uniform set of coordinates. The example perturbs those coordinates to illustrate the results of the vtkTessellatorFilter. Also, each cell is passed through vtkShrinkFilter to help identify the cells. Each generated cell also has a unique color.

The example takes an optonal argument, a vtkCell name.

For example, to generate vtkTriangles, run

```CellTypeSource``` vtkTriangle


