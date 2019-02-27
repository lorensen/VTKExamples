### Description

This example uses vtkPolyDataConnectivity to separate an input vtkPolyData into disconnected regions. Each region is assigned a unique color. A number of vtkNamedColors are used to fill part of the vtkLookupTable. If the number of extracted regions is more that the number of specified colors, the remaining colors are generated with a random number generator.

The default representation is surface. If the user types a "w" in the render window, the view will be rendered as a wireframe. The renderer will use hidden line removal.

The example supports any vtkPolyData reader.

!!! info
    [ConnectivityFilter](/Cxx/Filtering/ConnectivityFilter) illustrates vtkConnectivityFilter on a simple 2 region dataset.
