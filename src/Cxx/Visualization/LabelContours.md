### Description
This example labels isolines created by vtkContourFilter. After the isolines are generated, the resulting disconnected lines segments are gathered into polylines by vtkStripper. Then an appropriate position along each line is chosen to place the label for the contour. Two strategies for label placement are illustrated: a point at the midpoint of the line or a random point. vtkLabeledDataMapper places the labels for the contour lines.

The program can be run with an input XML polydata file (.vtp) or without arguments. If a file is specified then one, two or a range of contours can be specified. If run without a file name, the example generates a random scalar field on a plane.

!!! note
    The labels are represented as vtkActor2D's. If they are generated for a 3D surface, the labels that should be hidden will still be displayed.
