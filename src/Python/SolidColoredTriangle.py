import vtk
from vtk import *
 
#setup points and vertices
Points = vtk.vtkPoints()
Triangles = vtk.vtkCellArray()
 
Points.InsertNextPoint(1.0, 0.0, 0.0)
Points.InsertNextPoint(0.0, 0.0, 0.0)
Points.InsertNextPoint(0.0, 1.0, 0.0)
 
Triangle = vtk.vtkTriangle();
Triangle.GetPointIds().SetId(0, 0);
Triangle.GetPointIds().SetId(1, 1);
Triangle.GetPointIds().SetId(2, 2);
Triangles.InsertNextCell(Triangle);
 
#setup colors (setting the name to "Colors" is nice but not necessary)
Colors = vtk.vtkUnsignedCharArray();
Colors.SetNumberOfComponents(3);
Colors.SetName("Colors");
Colors.InsertNextTuple3(255,0,0);
 
polydata = vtk.vtkPolyData()
polydata.SetPoints(Points)
polydata.SetPolys(Triangles)
 
polydata.GetCellData().SetScalars(Colors);
polydata.Modified()
if vtk.VTK_MAJOR_VERSION <= 5:
    polydata.Update()
 
writer = vtk.vtkXMLPolyDataWriter();
writer.SetFileName("TriangleSolidColor.vtp");
if vtk.VTK_MAJOR_VERSION <= 5:
    writer.SetInput(polydata)
else:
    writer.SetInputData(polydata)
writer.Write()
