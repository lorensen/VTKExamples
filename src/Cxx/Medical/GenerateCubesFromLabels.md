### Description
Sometimes it is helpful to view the results of a segmentation without any post processing. This example converts the point data from a labeled volume into cell data. The surfaces are displayed as vtkPolydata. If you want to created smoothed polydata models from your segmented volumes, see the example [GenerateModelsFromLabels](/Cxx/Medical/GenerateModelsFromLabels). The input volume must be in [MetaIO format](http://www.vtk.org/Wiki/MetaIO/Documentation).

```
 Usage: GenerateCubesFromLabels FullHead.mhd StartLabel EndLabel
      where
        InputVolume is a meta file containing a 3 volume of discrete labels.
        StartLabel is the first label to be processed
        EndLabel is the last label to be processed
        NOTE: There can be gaps in the labeling. If a label does not exist in the volume, it will be skipped.
```


!!! note
    This original source code for this example is [here](https://gitlab.kitware.com/vtk/vtk/blob/395857190c8453508d283958383bc38c9c2999bf/Examples/Medical/Cxx/GenerateCubesFromLabels.cxx).
