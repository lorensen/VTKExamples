import vtk


def main():
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

    writer = vtk.vtkXMLPolyDataWriter()
    writer.SetFileName("TriangleVerts.vtp")
    writer.SetInputData(polydata)
    writer.Write()


if __name__ == '__main__':
    main()
