### Description

* Contributed by: Lars Friedrich

This example generates a sphere (prerequisite: closed surface of type vtkPolyData) and converts it into volume representation (vtkImageData) where the foreground voxels are 255 (inside) and the background voxels are 0 (outside). Internally vtkPolyDataToImageStencil is utilized. The resultant image is saved to disk in metaimage file format (SphereVolume.mhd).
