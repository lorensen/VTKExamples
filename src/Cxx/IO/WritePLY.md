### Description

!!! note
    Unlike vtkPolyDataXMLWriter and most other VTK writers, to write colors to the .ply file you must specify to the vtkPLYWriter:

    plyWriter->SetArrayName("Colors");

    where your color array was created/named like this:

    vtkSmartPointer<vtkUnsignedCharArray> colors =
      vtkSmartPointer<vtkUnsignedCharArray>::New();
    colors->SetNumberOfComponents(3);
    colors->SetName("Colors");

(This was found in response to a user question on StackOverflow: http://stackoverflow.com/questions/17783612/save-mesh-with-rgb-in-vtk/19525938)
