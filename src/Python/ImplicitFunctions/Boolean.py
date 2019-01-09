import vtk


def main():
    colors = vtk.vtkNamedColors()

    # create a sphere
    sphere = vtk.vtkSphere()
    sphere.SetRadius(1)
    sphere.SetCenter(1, 0, 0)

    # create a box
    box = vtk.vtkBox()
    box.SetBounds(-1, 1, -1, 1, -1, 1)

    # combine the two implicit functions
    boolean = vtk.vtkImplicitBoolean()
    boolean.SetOperationTypeToDifference()
    # boolean.SetOperationTypeToUnion()
    # boolean.SetOperationTypeToIntersection()
    boolean.AddFunction(box)
    boolean.AddFunction(sphere)

    # The sample function generates a distance function from the implicit
    # function. This is then contoured to get a polygonal surface.
    sample = vtk.vtkSampleFunction()
    sample.SetImplicitFunction(boolean)
    sample.SetModelBounds(-1, 2, -1, 1, -1, 1)
    sample.SetSampleDimensions(40, 40, 40)
    sample.ComputeNormalsOff()

    # contour
    surface = vtk.vtkContourFilter()
    surface.SetInputConnection(sample.GetOutputPort())
    surface.SetValue(0, 0.0)

    # mapper
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(surface.GetOutputPort())
    mapper.ScalarVisibilityOff()
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().EdgeVisibilityOn()
    actor.GetProperty().SetColor(colors.GetColor3d('AliceBlue'))
    actor.GetProperty().SetEdgeColor(colors.GetColor3d('SteelBlue'))

    # A renderer and render window
    renderer = vtk.vtkRenderer()
    renderer.SetBackground(colors.GetColor3d('Silver'))

    # add the actor
    renderer.AddActor(actor)

    # render window
    renwin = vtk.vtkRenderWindow()
    renwin.AddRenderer(renderer)

    # An interactor
    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renwin)

    # Start
    interactor.Initialize()
    renwin.Render()
    # renderer.GetActiveCamera().AddObserver('ModifiedEvent', CameraModifiedCallback)
    renderer.GetActiveCamera().SetPosition(5.0, -4.0, 1.6)
    renderer.GetActiveCamera().SetViewUp(0.1, 0.5, 0.9)
    renderer.GetActiveCamera().SetDistance(6.7)
    renwin.Render()
    interactor.Start()


if __name__ == '__main__':
    main()
