import vtk


def get_program_parameters():
    import argparse
    description = 'Generate image data, then write a .ply file.'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='A required ply filename.', nargs='?',
                        const='TestWritePLY.ply',
                        type=str, default='TestWritePLY.ply')
    args = parser.parse_args()
    return args.filename


def main():
    colors = vtk.vtkNamedColors()

    filename = get_program_parameters()

    sphereSource = vtk.vtkSphereSource()
    sphereSource.Update()

    plyWriter = vtk.vtkPLYWriter()
    plyWriter.SetFileName(filename)
    plyWriter.SetInputConnection(sphereSource.GetOutputPort())
    plyWriter.Write()

    # Read and display for verification
    reader = vtk.vtkPLYReader()
    reader.SetFileName(filename)
    reader.Update()

    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(reader.GetOutputPort())

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)

    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d('cobalt_green'))

    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
