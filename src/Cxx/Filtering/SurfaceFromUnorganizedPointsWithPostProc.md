### Description
This example is an extension to the example previously posted at:
[Create a surface from Unorganized Points](SurfaceFromUnorganizedPoints)

The objective is again to use vtkSurfaceReconstructionFilter to construct a surface from a set of points.
However, the direct output of the vtkSurfaceReconstructionFilter does not match with the spatial position of the original point set.
Instead, there is a scale change and translation in between.
To cure this, in this example we added a post transformation to move the reconstructed surface back to the position of the original points, which in some cases might be more favorable.
