import vtk


def get_program_parameters():
    import argparse
    description = 'Generate image data, then write a .vtp file.'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='A required vtp filename.', nargs='?',
                        const='TestWriteTriangleToFile.vtp',
                        type=str, default='TestWriteTriangleToFile.vtp')
    args = parser.parse_args()
    return args.filename


def main():
    filename = get_program_parameters()

    Points = vtk.vtkPoints()
    Triangles = vtk.vtkCellArray()
    Triangle = vtk.vtkTriangle()

    Points.InsertNextPoint(1.0, 0.0, 0.0)
    Points.InsertNextPoint(0.0, 0.0, 0.0)
    Points.InsertNextPoint(0.0, 1.0, 0.0)

    Triangle.GetPointIds().SetId(0, 0)
    Triangle.GetPointIds().SetId(1, 1)
    Triangle.GetPointIds().SetId(2, 2)
    Triangles.InsertNextCell(Triangle)

    polydata = vtk.vtkPolyData()
    polydata.SetPoints(Points)
    polydata.SetPolys(Triangles)
    polydata.Modified()

    writer = vtk.vtkXMLPolyDataWriter()
    writer.SetFileName(filename)
    writer.SetInputData(polydata)
    writer.Write()


if __name__ == '__main__':
    main()
