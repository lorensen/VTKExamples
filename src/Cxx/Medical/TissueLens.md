### Description
This example uses two vtkClipDataSet filters to achieve a "tissue lens" affect. First, a vtkSphere implicit function is used to clip a spherical hole in the isosurface extracted with vtkMarchingCubes. Then a geometric vtkSphereSource samples the original volume data using a vtkProbeFilter. vtkClipDataSet uses the resulting scalar point data to clip the sphere surface with the isosurface value.

!!! example "Usage"
    TissueLens FullHead.mhd

!!! info
    The example uses [FullHead.mhd](https://raw.githubusercontent.com/lorensen/VTKExamples/master/src/Testing/Data/FullHead.mhd) which references [FullHead.raw.gz](https://github.com/lorensen/VTKExamples/blob/master/src/Testing/Data/FullHead.raw.gz?raw=true).
