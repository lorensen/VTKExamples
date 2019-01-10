import vtk


def get_program_parameters():
    import argparse
    description = 'Generate triangle polydata, then write a .vtp file.'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='A required vtp filename.', nargs='?',
                        const='TestTriangleCornerVertices.vtp',
                        type=str, default='TestTriangleCornerVertices.vtp')
    args = parser.parse_args()
    return args.filename


def main():
    filename = get_program_parameters()

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
    writer.SetFileName(filename)
    writer.SetInputData(polydata)
    writer.Write()


if __name__ == '__main__':
    main()
