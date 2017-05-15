### Description
This example requires the remote module ''SplineDrivenImageSampler.'' Check to see if the file ''SplineDrivenImageSlicer.remote.cmake'' exists in VTK/Remote. If it does not, copy [this file](https://gitlab.kitware.com/vtk/vtk/raw/master/Remote/SplineDrivenImageSlicer.remote.cmake) to ''VTK/Remote/SplineDrivenImageSlicer.remote.cmake''.

Next

1. reconfigure with cmake.

2. Then enable the module setting ''Module_SplineDrivenImageSlicer:BOOL=ON''

3. `make`

The classes used in this example are described in [A Spline-Driven Image Slicer](http://www.vtkjournal.org/browse/publication/838). In the example, the normal vectors are yellow, the tangent vectors are red and the binormal vectors are green.
