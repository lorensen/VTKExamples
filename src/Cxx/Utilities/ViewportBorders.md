### Description

Sometimes multiple vtkRenderer viewports can be difficult to differentiate. This example draws a border around each viewport. The example creates a vtkPolyLine that outlines the viewport. The coordinates for the vtkPoints are specified in normalized viewport coordinates. The coordinate selection is made with a vtkCoordinate. The vtkPolyDataMapper2D and vtkActor2D render the border.

To run the example, provide 1-N vtkPolyDataReader files.

This examples uses the data [v.vtk](https://raw.githubusercontent.com/lorensen/VTKExamples/master/src/Testing/Data/v.vtk), [t.vtk](https://raw.githubusercontent.com/lorensen/VTKExamples/master/src/Testing/Data/t.vtk) and [k.vtk](https://raw.githubusercontent.com/lorensen/VTKExamples/master/src/Testing/Data/k.vtk).
