### Description
This example requires the remote module ''SplineDrivenImageSampler.'' Check to see if the file ''SplineDrivenImageSlicer.remote.cmake'' exists in VTK/Remote. If it does not, copy [this file](https://gitlab.kitware.com/vtk/vtk/raw/master/Remote/SplineDrivenImageSlicer.remote.cmake) to ''VTK/Remote/SplineDrivenImageSlicer.remote.cmake''.

Next
# reconfigure with cmake.
# Then enable the module setting ''Module_SplineDrivenImageSlicer:BOOL=ON''
# make

The classes used in this example are described in [A Spline-Driven Image Slicer](http://www.vtkjournal.org/browse/publication/838). In the example, the normal vectors are yellow, the tangent vectors are red and the binormal vectors are green.

This example illustrates how to control a pipeline inside a callback.
