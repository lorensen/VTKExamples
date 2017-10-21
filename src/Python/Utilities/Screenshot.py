import vtk

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

# mapper
mapper = vtk.vtkPolyDataMapper()
mapper.SetInputConnection(source.GetOutputPort())

# actor
actor = vtk.vtkActor()
actor.SetMapper(mapper)

# color the actor
actor.GetProperty().SetColor(1, 0, 0)  # (R,G,B)

# assign actor to the renderer
ren.AddActor(actor)

renWin.Render()

# screenshot code:
w2if = vtk.vtkWindowToImageFilter()
w2if.SetInput(renWin)
w2if.Update()

writer = vtk.vtkPNGWriter()
writer.SetFileName("screenshot.png")
writer.SetInputConnection(w2if.GetOutputPort())
writer.Write()

# enable user interface interactor
iren.Initialize()
iren.Start()
