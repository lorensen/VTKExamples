import vtk


def main():
    Points = vtk.vtkPoints()
    Points.InsertNextPoint(1.0, 0.0, 0.0)
    Points.InsertNextPoint(0.0, 0.0, 0.0)
    Points.InsertNextPoint(0.0, 1.0, 0.0)

    polydata = vtk.vtkPolyData()
    polydata.SetPoints(Points)

    writer = vtk.vtkXMLPolyDataWriter()
    writer.SetFileName("TrianglePoints.vtp")
    writer.SetInputData(polydata)
    writer.Write()


if __name__ == '__main__':
    main()
