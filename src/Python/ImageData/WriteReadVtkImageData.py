import vtk


def get_program_parameters():
    import argparse
    description = 'Generate image data, edit data points, store and reload it.'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='A required vtk filename, e.g. writeImageData.vti.', nargs='?',
                        const='writeImageData.vti',
                        type=str, default='writeImageData.vti')
    args = parser.parse_args()
    return args.filename


def main():
    colors = vtk.vtkNamedColors()

    filename = get_program_parameters()

    imageData = vtk.vtkImageData()
    imageData.SetDimensions(3, 4, 5)
    imageData.AllocateScalars(vtk.VTK_DOUBLE, 1)

    dims = imageData.GetDimensions()

    # Fill every entry of the image data with '2.0'
    for z in range(dims[2]):
        for y in range(dims[1]):
            for x in range(dims[0]):
                imageData.SetScalarComponentFromDouble(x, y, z, 0, 2.0)

    writer = vtk.vtkXMLImageDataWriter()
    writer.SetFileName(filename)
    writer.SetInputData(imageData)
    writer.Write()

    # Read the file (to test that it was written correctly)
    reader = vtk.vtkXMLImageDataReader()
    reader.SetFileName(filename)
    reader.Update()

    # Convert the image to a polydata
    imageDataGeometryFilter = vtk.vtkImageDataGeometryFilter()
    imageDataGeometryFilter.SetInputConnection(reader.GetOutputPort())
    imageDataGeometryFilter.Update()

    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(imageDataGeometryFilter.GetOutputPort())

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetPointSize(3)

    # Setup rendering
    renderer = vtk.vtkRenderer()
    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d('White'))
    renderer.ResetCamera()

    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)

    renderWindowInteractor = vtk.vtkRenderWindowInteractor()

    renderWindowInteractor.SetRenderWindow(renderWindow)
    renderWindowInteractor.Initialize()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
