### Description
Sometimes it is helpful to view the results of a segmentation without
any post processing. This example converts the point data from a
labeled volume into cell data. The surfaces are displayed as
polydata. If you want to created smoothed polydata models from your
segmented volumes, see the example [GenerateModelsFromLabels](/Cxx/Medical/GenerateModelsFromLabels). The input volume must be in [MetaIO format](http://www.vtk.org/Wiki/MetaIO/Documentation).

!!! note
    This original source code for this example is [here](https://gitlab.kitware.com/vtk/vtk/blob/395857190c8453508d283958383bc38c9c2999bf/Examples/Medical/Cxx/GenerateCubesFromLabels.cxx).
