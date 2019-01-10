import vtk


def main():
    colors = vtk.vtkNamedColors()

    sphereSource = vtk.vtkSphereSource()
    sphereSource.SetCenter(0.0, 0.0, 0.0)
    sphereSource.SetRadius(5)

    # Create a mapper and actor
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(sphereSource.GetOutputPort())
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetColor(colors.GetColor3d('Bisque'))

    # Setup a renderer, render window, and interactor
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    # renderWindow.SetWindowName("Test")

    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    # Add the actor to the scene
    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d('Navy'))

    # Render and interact
    renderWindow.Render()
    # *** SetWindowName after renderWindow.Render() is called ***
    renderWindow.SetWindowName("Test")
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
