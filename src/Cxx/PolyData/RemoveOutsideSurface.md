### Description
This example removes the outer surface of a multiple surface vtkPolyData model. The examples assumes the outside surface is closed and there is only one outside surface. It also assumes that the center of the model lies inside the outer surface.

The example proceeds as follows:

1. Use vtkConnectivityFilter to label all of the regions in the model with a region id.

2. Cast a ray from outside the bounds of the model into the center of the model. Use a vtkCellLocator to intersect the ray with the model. The intersected cell will be on the outside surface of the model.

3. The vtkCellData of the intersected cell will have the region id of the cell.

4. Use a vtkCellIterator to visit each cell of the model. Cells whose region id is not equal to the interesected cell's region io are retained on a new vtkPolyData

The resulting vtkPolyData will contain all but the outside surface.

If run without arguments, the example generates several small (in area) spheres inside a large (in area) sphere. The inner sphere have more cells than the outer sphere, but will not be extracted.

The gold model is the original polydata and the blue model is the original with tghe outer surface removed.

You can try your own surface by specifying a XML PolyData file (.vtp) on the command line.

!!! seealso
    [ExtractOutsideSurface](/Cxx/PolyData/ExtractOutsideSurface) extracts only the outside surface.
