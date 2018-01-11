### Description
This example demonstrates the use and manipulation of vtkLookupTable's.

First create a simple pipeline that reads a vtkStructuredGrid and then extracts a plane using vtkStructuredGeometryFilter from the grid. The plane will be colored differently by using different vtkLookupTable's.

!!! note
    The Update method is manually invoked because it causes the reader to read; later on we use the output of the reader to set a range for the scalar values.

!!! note
    This original tcl source code for this example is [here](https://gitlab.kitware.com/vtk/vtk/blob/395857190c8453508d283958383bc38c9c2999bf/Examples/Rendering/Tcl/rainbow.tcl).

