### Description
This example illustrates how to create an isosurface and create point data on that isosurface that is sampled from another dataset. This example creates an isosurface of a sphere and then uses the vtkProbeFilter to compute point data from a sampled cylinder.

!!! note
    All point data is sampled, even the normals. This example restores the original isosurface normals after the probe. The example has one optional command line argument that controls the sample resolution of the sphere and cylinder. The default is 50.
