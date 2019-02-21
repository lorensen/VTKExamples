### Description

Given latitude and longitude arrays, take the values in those arrays and convert them to x,y,z world coordinates. 

Uses a spherical model of the earth to do the conversion. The position is in meters relative to the center of the earth.

If a transform is given, use the transform to convert latitude and longitude to the world coordinate.

!!! note
    The vtkGeovisCore classes as well as the module vtkViewsGeovis have been deprecated for VTK 8.2 and will be removed in a future version.
    See [VTK Merge Request 4395](https://gitlab.kitware.com/vtk/vtk/merge_requests/4395)
   
