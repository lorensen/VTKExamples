import vtk


def main():
    colors = vtk.vtkNamedColors()

    textSource = vtk.vtkTextSource()
    textSource.SetText("Hello")
    textSource.SetForegroundColor(colors.GetColor3d('DarkSlateGray'))
    textSource.SetBackgroundColor(colors.GetColor3d('NavajoWhite'))
    textSource.BackingOn()
    textSource.Update()

    # Create a mapper and actor
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(textSource.GetOutputPort())

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)

    # Create a renderer, render window, and interactor
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    # Add the actor to the scene
    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d('Bisque'))

    # Render and interact
    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
