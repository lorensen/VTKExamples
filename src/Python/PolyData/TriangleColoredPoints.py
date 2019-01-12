import vtk

def get_program_parameters():
    import argparse
    description = 'Generate a triangle with colored points and write it to a .vtp file.'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='A required vtp filename.', nargs='?',
                        const='TestTriangleColoredPoints.vtp',
                        type=str, default='TestTriangleColoredPoints.vtp')
    args = parser.parse_args()
    return args.filename


def main():
    colors = vtk.vtkNamedColors()

    filename = get_program_parameters()

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
    writer.SetFileName(filename)
    writer.SetInputData(polydata)
    writer.Write()


if __name__ == '__main__':
    main()
