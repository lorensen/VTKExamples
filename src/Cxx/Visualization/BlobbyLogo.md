### Description

This is the blobby vtk logo described in chapter 12 of the VTK textbook. The example uses vtkAppendPolyData to combine three vtkPolyData. A vtkImplicitModeller creates a vtkImageData of the distnaces from the polydata triangles. vtkContourFilter extracts an isosurface representing an offset surface.

This examples uses the data [v.vtk](https://raw.githubusercontent.com/lorensen/VTKExamples/master/src/Testing/Data/v.vtk), [t.vtk](https://raw.githubusercontent.com/lorensen/VTKExamples/master/src/Testing/Data/t.vtk) and [k.vtk](https://raw.githubusercontent.com/lorensen/VTKExamples/master/src/Testing/Data/k.vtk).

!!! info
    See [Figure 12-13](/VTKBook/12Chapter12/#Figure%2012-13) in [Chapter 12](/VTKBook/12Chapter12) the [VTK Textbook](/VTKBook/01Chapter1).
