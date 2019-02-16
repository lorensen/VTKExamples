### Description

!!! warning
    This example requires the remote module ''SplineDrivenImageSampler.''

Next

1. reconfigure with cmake.

2. Then enable the module setting ''Module_SplineDrivenImageSlicer:BOOL=ON'' or ''VTK_MODULE_ENABLE_VTK_SplineDrivenImageSlicer:STRING=WANT''

3. `make`

The classes used in this example are described in [A Spline-Driven Image Slicer](http://www.vtkjournal.org/browse/publication/838). In the example, the normal vectors are yellow, the tangent vectors are red and the binormal vectors are green.
