import vtk


def get_program_parameters():
    import argparse
    description = 'Generate a colored triangle, then write a .vtp file.'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='A required vtp filename.', nargs='?',
                        const='TestColoredTriangle.vtp',
                        type=str, default='TestColoredTriangle.vtp')
    args = parser.parse_args()
    return args.filename


def main():
    colors = vtk.vtkNamedColors()

    filename = get_program_parameters()

    # setup points and vertices
    Points = vtk.vtkPoints()
    Triangles = vtk.vtkCellArray()

    Points.InsertNextPoint(1.0, 0.0, 0.0)
    Points.InsertNextPoint(0.0, 0.0, 0.0)
    Points.InsertNextPoint(0.0, 1.0, 0.0)

    Triangle = vtk.vtkTriangle()
    Triangle.GetPointIds().SetId(0, 0)
    Triangle.GetPointIds().SetId(1, 1)
    Triangle.GetPointIds().SetId(2, 2)
    Triangles.InsertNextCell(Triangle)

    # setup colors
    Colors = vtk.vtkUnsignedCharArray()
    Colors.SetNumberOfComponents(3)
    Colors.SetName("Colors")
    Colors.InsertNextTuple3(*colors.GetColor3ub('Red'))
    Colors.InsertNextTuple3(*colors.GetColor3ub('Lime'))
    Colors.InsertNextTuple3(*colors.GetColor3ub('Blue'))

    polydata = vtk.vtkPolyData()
    polydata.SetPoints(Points)
    polydata.SetPolys(Triangles)

    polydata.GetPointData().SetScalars(Colors)
    polydata.Modified()

    writer = vtk.vtkXMLPolyDataWriter()
    writer.SetFileName(filename)
    writer.SetInputData(polydata)
    writer.Write()


if __name__ == '__main__':
    main()
