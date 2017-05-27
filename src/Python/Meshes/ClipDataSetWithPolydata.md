### Description

An example that shows how to use the vtkClipDataSet to clip a vtkRectilinearGrid with an arbitrary polydata. vtkImplicitPolyDataDistance is used to turn the polydata into an implicit function. Every point of the grid is evaluated before sending to vtkClipDataSet. This example uses a vtkConeSource to generate polydata to use, however any polydata could be used, including stl files.
