import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Create a sphere
    sphereSource = vtk.vtkSphereSource()
    sphereSource.SetCenter(0.0, 0.0, 0.0)
    sphereSource.SetRadius(10)
    sphereSource.SetPhiResolution(30)
    sphereSource.SetThetaResolution(30)
    sphereSource.Update()

    # Create a mapper and actor
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(sphereSource.GetOutputPort())

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetSpecular(0.6)
    actor.GetProperty().SetSpecularPower(30)
    actor.GetProperty().SetColor(colors.GetColor3d("LightSkyBlue"))

    camera = vtk.vtkCamera()
    camera.SetPosition(0, 0, 100)
    camera.SetFocalPoint(0, 0, 0)

    # Create a renderer, render window, and interactor
    renderer = vtk.vtkRenderer()
    renderer.SetActiveCamera(camera)

    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    # Add the actor to the scene
    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("MistyRose"))

    # Render and interact
    renderWindowInteractor.Initialize()
    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
