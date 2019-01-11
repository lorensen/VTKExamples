import vtk


# Call back function


def sphereCallback(obj, event):
    print('Center: {}, {}, {}'.format(*obj.GetCenter()))


def main():
    colors = vtk.vtkNamedColors()

    colors.SetColor('bkg', [0.1, 0.2, 0.4, 1.0])

    # A renderer and render window
    renderer = vtk.vtkRenderer()
    renderer.SetBackground(colors.GetColor3d('bkg'))

    renwin = vtk.vtkRenderWindow()
    renwin.AddRenderer(renderer)

    # An interactor
    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renwin)

    # A Sphere widget
    sphereWidget = vtk.vtkSphereWidget()
    sphereWidget.SetInteractor(interactor)
    sphereWidget.SetRepresentationToSurface()
    sphereWidget.GetSphereProperty().SetColor(colors.GetColor3d("BurlyWood"))

    sphereWidget.On()

    # Connect the event to a function
    sphereWidget.AddObserver("InteractionEvent", sphereCallback)

    # Start
    interactor.Initialize()
    renwin.Render()
    interactor.Start()


if __name__ == '__main__':
    main()
