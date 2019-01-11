import vtk


def main():
    colors = vtk.vtkNamedColors()

    # create a rendering window and renderer
    ren = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren)

    # create a renderwindowinteractor
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    style = vtk.vtkInteractorStyleTrackballActor()
    iren.SetInteractorStyle(style)

    # create source
    sphereSource = vtk.vtkSphereSource()

    # mapper
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(sphereSource.GetOutputPort())

    # actor
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetColor(colors.GetColor3d('Chartreuse'))

    # assign actor to the renderer
    ren.AddActor(actor)
    ren.SetBackground(colors.GetColor3d('PaleGoldenrod'))

    # enable user interface interactor
    iren.Initialize()
    renWin.Render()
    iren.Start()


if __name__ == '__main__':
    main()
