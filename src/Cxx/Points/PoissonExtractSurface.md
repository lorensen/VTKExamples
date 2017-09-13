### Description
This example uses the [PoissonReconstruction remote module](https://github.com/lorensen/PoissonReconstruction) to reconstruct surfaces from unorganized points. This code was, with permission, adapted directly from the original implementation by Kazhdan, Bolitho, and Hugues. The original implementation can be found [here](http://www.cs.jhu.edu/~misha/Code/IsoOctree/).

PoissonReconstruction requires that the vtkPolyData input have vtkNormals. If normals are not included in the vtkPointData, the example uses vtkPCANormalEstimation to create normals.

If the example is run without an argument, the example uses random points on a spherical shell. With a filename, the example uses the points on the vtkPolyData.

!!! cite
    The [VTK Journal](http://www.vtkjournal.org/) paper [Poisson Surface Reconstruction for VTK](http://www.vtkjournal.org/browse/publication/718) describes the VTK implementaion.

!!! info
    [CompareExtractSurface](/Cxx/Points/CompareExtractSurface) compares three surface extraction algorithms.

!!! seealso
    [ExtractSurface](/Cxx/Points/ExtractSurface) reconstructs surfaces and is included with the VTK distribution. [PowercrustExtractSurface](/Cxx/Points/PowercrustExtractSurface) reconstructs surfaces and is implemented as a VTK remote module.

!!! info
    PoissonReconstruction is implemented as a [VTK Remote Module](http://www.vtk.org/Wiki/VTK/Remote_Modules).

To use PoissonReconstruction in VTK:

1. Download [PoissonReconstruction.remote.cmake](https://github.com/lorensen/PoissonReconstruction/blob/master/PoissonReconstruction.remote.cmake) and place it in your *VTK/Remote* directory.
2. Reconfigure your VTK build with *cmake*
3. Enable the remote module by setting *Module_PoissonReconstruction:BOOL=ON*.
4. `make`
