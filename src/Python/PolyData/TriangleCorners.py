import vtk


def get_program_parameters():
    import argparse
    description = 'Generate triangle points, then write a .vtp file.'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='A required vtp filename.', nargs='?',
                        const='TestTriangleCorners.vtp',
                        type=str, default='TestTriangleCorners.vtp')
    args = parser.parse_args()
    return args.filename


def main():
    filename = get_program_parameters()

    Points = vtk.vtkPoints()
    Points.InsertNextPoint(1.0, 0.0, 0.0)
    Points.InsertNextPoint(0.0, 0.0, 0.0)
    Points.InsertNextPoint(0.0, 1.0, 0.0)

    polydata = vtk.vtkPolyData()
    polydata.SetPoints(Points)
    polydata.Modified()

    writer = vtk.vtkXMLPolyDataWriter()
    writer.SetFileName(filename)
    writer.SetInputData(polydata)
    writer.Write()


if __name__ == '__main__':
    main()
