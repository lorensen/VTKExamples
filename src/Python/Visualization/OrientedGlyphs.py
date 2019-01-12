import vtk


def main():
    colors = vtk.vtkNamedColors()

    sphereSource = vtk.vtkSphereSource()
    sphereSource.Update()

    input_data = vtk.vtkPolyData()
    input_data.ShallowCopy(sphereSource.GetOutput())

    arrowSource = vtk.vtkArrowSource()

    glyph3D = vtk.vtkGlyph3D()
    glyph3D.SetSourceConnection(arrowSource.GetOutputPort())
    glyph3D.SetVectorModeToUseNormal()
    glyph3D.SetInputData(input_data)
    glyph3D.SetScaleFactor(.2)
    glyph3D.Update()

    # Visualize
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(glyph3D.GetOutputPort())

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetColor(colors.GetColor3d('Yellow'))

    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d('DarkGreen'))

    renderWindow.Render()
    renderer.GetActiveCamera().Zoom(1.5)
    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
