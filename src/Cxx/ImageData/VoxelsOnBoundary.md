### Description

This example uses vtkMultiThreshold to extract voxels that are inside an isosurface and on the boundary of the isosurface. The result is a vtkUnstructuredGrid for each set of voxels. Before processing, vtkImageShrink3D reduces the resolution by a factor of 4.

Compare these results with 

!!! example "usage"
    VoxelsOnBoundary FullHead.mhd

!!! info
    Compare these results with [MedicalDemo1](/Cxx/Medical/MedicalDemo1) that extracts the surface using vtkMarchingCubes to extract an interpolated isosurface.

!!! info
    The example uses [FullHead.mhd](https://raw.githubusercontent.com/lorensen/VTKExamples/master/src/Testing/Data/FullHead.mhd) which references [FullHead.raw.gz](https://github.com/lorensen/VTKExamples/blob/master/src/Testing/Data/FullHead.raw.gz?raw=true).
