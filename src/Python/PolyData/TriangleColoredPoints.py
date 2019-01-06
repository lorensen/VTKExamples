import vtk


def main():
    colors = vtk.vtkNamedColors()

    # setup points and vertices
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

    # setup colors
    Colors = vtk.vtkUnsignedCharArray()
    Colors.SetNumberOfComponents(3)
    Colors.SetName("Colors")
    Colors.InsertNextTuple3(*colors.GetColor3ub('Red'))
    Colors.InsertNextTuple3(*colors.GetColor3ub('LimeGreen'))
    Colors.InsertNextTuple3(*colors.GetColor3ub('Blue'))

    polydata = vtk.vtkPolyData()
    polydata.SetPoints(Points)
    polydata.SetVerts(Vertices)
    polydata.GetPointData().SetScalars(Colors)
    polydata.Modified()

    writer = vtk.vtkXMLPolyDataWriter()
    writer.SetFileName("TriangleColoredPoints.vtp")
    writer.SetInputData(polydata)
    writer.Write()


if __name__ == '__main__':
    main()
