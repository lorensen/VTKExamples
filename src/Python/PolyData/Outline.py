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

    # create source
    source = vtk.vtkConeSource()
    source.SetCenter(0, 0, 0)
    source.SetResolution(100)

    # mapper
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(source.GetOutputPort())

    # actor
    actor1 = vtk.vtkActor()
    actor1.SetMapper(mapper)

    # outline
    outline = vtk.vtkOutlineFilter()
    outline.SetInputConnection(source.GetOutputPort())
    mapper2 = vtk.vtkPolyDataMapper()
    mapper2.SetInputConnection(outline.GetOutputPort())

    actor2 = vtk.vtkActor()
    actor2.SetMapper(mapper2)

    # assign actor to the renderer
    ren.AddActor(actor1)
    ren.AddActor(actor2)
    ren.SetBackground(colors.GetColor3d('MidnightBlue'))

    # enable user interface interactor
    iren.Initialize()
    renWin.Render()
    iren.Start()


if __name__ == '__main__':
    main()
