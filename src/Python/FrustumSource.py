import vtk

# create a rendering window and renderer
ren = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)

# create a renderwindowinteractor
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)

planesArray=[0]*24 # Allocate a list of length 24
camera = vtk.vtkCamera()
camera.GetFrustumPlanes(1, planesArray)
planes=vtk.vtkPlanes()
planes.SetFrustumPlanes(planesArray)

frustumSource = vtk.vtkFrustumSource()
frustumSource.SetPlanes(planes)
frustumSource.ShowLinesOff();
frustumSource.Update()

# mapper
mapper = vtk.vtkPolyDataMapper()
mapper.SetInputData(frustumSource.GetOutput())

# actor
actor = vtk.vtkActor()
actor.SetMapper(mapper)
actor.GetProperty().SetColor(0.8,0.9,0.7)

# assign actor to the renderer
ren.AddActor(actor)
ren.SetBackground(0.2,0.1,0.3)
# enable user interface interactor
iren.Initialize()
renWin.Render()
iren.Start()
