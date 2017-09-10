### Description
This example loosely follows the most excellent paper by Curless and Levoy: ["A Volumetric Method for Building Complex Models from Range Images."](https://graphics.stanford.edu/papers/volrange) First it estimates normals from the points, then creates a signed distance field, followed by surface extraction of the zero-level set of the distance field.

If the example is run without an argument, the example uses random points on a spherical shell. With a filename, the example uses the points on the vtkPolyData.

The image was created using the [Armadillo dataset](https://github.com/lorensen/VTKExamples/blob/master/src/Testing/Data/Armadillo.ply?raw=true)


!!! info
    [CompareExtractSurface](/Cxx/Points/CompareExtractSurface) compares three surface extraction algorithms.

!!! seealso
    [PowercrustExtractSurface](/Cxx/Points/PowercrustExtractSurface) reconstructs surfaces and is implemented as a VTK remote module. [PoissonExtractSurface](/Cxx/Points/PoissonExtractSurface) reconstructs surfaces and is implemented as a VTK remote module.

!!! warning
    If you experience extraneous lines in the reconstruction, update your VTK. A [patch](https://gitlab.kitware.com/vtk/vtk/merge_requests/3238) was made on September 5, 2017 to correct the issue.

!!! warning
    The classes used in this example require vtk 7.1 or later.
