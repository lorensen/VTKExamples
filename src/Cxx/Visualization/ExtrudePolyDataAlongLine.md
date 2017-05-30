### Description

Extrude a 2D polydata along a line. It uses vtkRuledSurfaceFilter.

The example proceeds as follows:

1. Obtain the 2D polydata from a file( or generate a disk).

2. Generates random points in 3D space and fits a spline to the points.

3. Computes an orientation  frame at each point on the line.

4. Places a copy of the 2D polydata at each point on the line, oriented by the the frame at that point.

5. For each contour in the 2D polydata, appends all of the copies.

6. Creates a ruled surface for each contour.

!!! note
    This example requires the remote module ''SplineDrivenImageSampler.'' Check to see if the file ''SplineDrivenImageSlicer.remote.cmake'' exists in VTK/Remote. If it does not, copy [this file](https://gitlab.kitware.com/vtk/vtk/raw/master/Remote/SplineDrivenImageSlicer.remote.cmake) to ''VTK/Remote/SplineDrivenImageSlicer.remote.cmake''.

!!! warning
    A bug in vtkRuledSurfaceFilter occasionally drops triangles. This is being fixed.
