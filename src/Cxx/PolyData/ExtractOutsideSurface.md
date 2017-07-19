### Description
This example extracts the outer surface of a multiple surface vtkPolyData model. The example assumes the outside surface is closed and there is only one outside surface. It also assumes that the center of the model lies inside the outer surface.

The example casts a ray from outside the bounds of the model into the center of the model. It uses a vtkCellLocator to intersect the ray with the model. The intersected cell is used as a seed to the vtkPolyDataConnectivityFilter which is run with the extraction mode set to CellSeededRegions.

If run without arguments, the example generates a small (in area) sphere inside a large (in area) sphere. The inner sphere has more cells than the outer sphere, but should not be extracted.

The gold model is the original vtkPolyData and the blue model is the outer surface.

You can try your own surface by specifying a XML PolyData file (.vtp) on the command line.

!!! seealso
    [RemoveOutsideSurface](/Cxx/PolyData/RemoveOutsideSurface) removes the outside surface.
