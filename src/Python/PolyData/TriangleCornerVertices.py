import vtk
from vtk import *

Points = vtk.vtkPoints()
Vertices = vtk.vtkCellArray()

id = Points.InsertNextPoint(1.0, 0.0, 0.0)
Vertices.InsertNextCell(1)
Vertices.InsertCellPoint(id)
id = Points.InsertNextPoint(0.0, 0.0, 0.0)
Vertices.InsertNextCell(1)
Vertices.InsertCellPoint(id)
id = Points.InsertNextPoint(0.0, 1.0, 0.0)
Vertices.InsertNextCell(1)
Vertices.InsertCellPoint(id)

polydata = vtk.vtkPolyData()
polydata.SetPoints(Points)
polydata.SetVerts(Vertices)
polydata.Modified()
if vtk.VTK_MAJOR_VERSION <= 5:
    polydata.Update()

writer = vtk.vtkXMLPolyDataWriter();
writer.SetFileName("TriangleVerts.vtp");
if vtk.VTK_MAJOR_VERSION <= 5:
    writer.SetInput(polydata)
else:
    writer.SetInputData(polydata)
writer.Write()
