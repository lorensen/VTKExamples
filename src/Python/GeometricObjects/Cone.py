import vtk

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
cone = vtk.vtkConeSource()
cone.SetResolution(60)
cone.SetCenter(-2, 0, 0)
cone.Update()

# mapper
coneMapper = vtk.vtkPolyDataMapper()
coneMapper.SetInputData(cone.GetOutput())

# actor
coneActor = vtk.vtkActor()
coneActor.SetMapper(coneMapper)

# assign actor to the renderer
ren.AddActor(coneActor)

# enable user interface interactor
iren.Initialize()
renWin.Render()
iren.Start()
