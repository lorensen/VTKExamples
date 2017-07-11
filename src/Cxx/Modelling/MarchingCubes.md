### Description
Creates a surface from a volume using Marching Cubes.

Without arguments, the examples generates a voxelized  sphere with vtkVoxelModeller.
!!! note
    vtkVoxelModeller by default produces a VTK_BIT scalar image. Marching Cubes does not support this type. The scalar output is set to float for this example.

To generate a surface from a DICOM series, provide a folder containing the series and specify an isovalue for the surface.

This [Midas Repository](http://placid.nlm.nih.gov/community/21) contains a number of DICOM datasets.
