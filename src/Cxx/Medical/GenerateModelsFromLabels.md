### Description
This example uses vtkDiscreteMarchingCubes to create vtkPolyData models from a 3D volume that contains
discrete labels. These volumes are normally the output of a
segmentation algorithm. The polydata for each label will be output
into a separate file.

If you want to see the segmentation results as
cube models, see the example [GenerateCubesFromLabels](/Cxx/Medical/GenerateCubesFromLabels).
The input volume must be in [MetaIO format](http://www.vtk.org/Wiki/MetaIO/Documentation).

Once you generate the models, you can view them with [Paraview](http://paraview.org)
