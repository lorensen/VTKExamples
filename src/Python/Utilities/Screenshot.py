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
    source = vtk.vtkSphereSource()
    source.SetCenter(0, 0, 0)
    source.SetRadius(5.0)
    source.SetPhiResolution(30)
    source.SetThetaResolution(30)


    # mapper
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(source.GetOutputPort())

    # actor
    actor = vtk.vtkActor()
    actor.GetProperty().SetColor(colors.GetColor3d("IndianRed"))
    actor.GetProperty().SetSpecular(0.6)
    actor.GetProperty().SetSpecularPower(30)
    actor.SetMapper(mapper)

    # assign actor to the renderer
    ren.AddActor(actor)
    ren.SetBackground(colors.GetColor3d("MistyRose"))


    renWin.Render()

    # screenshot code:
    w2if = vtk.vtkWindowToImageFilter()
    w2if.SetInput(renWin)
    w2if.SetInputBufferTypeToRGB()
    w2if.ReadFrontBufferOff()
    w2if.Update()

    writer = vtk.vtkPNGWriter()
    writer.SetFileName("TestScreenshot.png")
    writer.SetInputConnection(w2if.GetOutputPort())
    writer.Write()

    # enable user interface interactor
    iren.Initialize()
    iren.Start()


if __name__ == '__main__':
    main()
