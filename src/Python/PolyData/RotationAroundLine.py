import vtk


def main():
    colors = vtk.vtkNamedColors()

    # create two cones, rotate one of them.

    # create a rendering window and renderer
    ren = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren)
    WIDTH = 640
    HEIGHT = 480
    renWin.SetSize(WIDTH, HEIGHT)

    # create a renderwindowinteractor
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # create cone
    source = vtk.vtkConeSource()
    source.SetResolution(60)
    source.SetCenter(-2, 0, 0)

    # create a transform that rotates the cone
    transform = vtk.vtkTransform()
    transform.RotateWXYZ(45, 0, 1, 0)
    transformFilter = vtk.vtkTransformPolyDataFilter()
    transformFilter.SetTransform(transform)
    transformFilter.SetInputConnection(source.GetOutputPort())
    transformFilter.Update()

    # mapper for original cone
    coneMapper1 = vtk.vtkPolyDataMapper()
    coneMapper1.SetInputConnection(source.GetOutputPort())

    # another mapper for the rotated cone
    coneMapper2 = vtk.vtkPolyDataMapper()
    coneMapper2.SetInputConnection(transformFilter.GetOutputPort())

    # actor for original cone
    actor1 = vtk.vtkActor()
    actor1.SetMapper(coneMapper1)

    # actor for rotated cone
    actor2 = vtk.vtkActor()
    actor2.SetMapper(coneMapper2)

    # color the original cone red
    actor1.GetProperty().SetColor(colors.GetColor3d('Red'))
    # color rotated cone blue
    actor2.GetProperty().SetColor(colors.GetColor3d('Blue'))

    # assign actor to the renderer
    ren.AddActor(actor1)
    ren.AddActor(actor2)

    # enable user interface interactor
    iren.Initialize()
    renWin.Render()
    iren.Start()


if __name__ == '__main__':
    main()
