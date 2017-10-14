import vtk

# create a rendering window and renderer
ren = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)

# create a renderwindowinteractor
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)

# create source
source = vtk.vtkCylinderSource()
source.SetCenter(0,0,0)
source.SetRadius(5.0)
source.SetHeight(7.0)
source.SetResolution(100)

# mapper
mapper = vtk.vtkPolyDataMapper()
mapper.SetInputConnection(source.GetOutputPort())

# actor
actor = vtk.vtkActor()
actor.SetMapper(mapper)

# assign actor to the renderer
ren.AddActor(actor)
ren.SetBackground(0.1, 0.3,0.2); # Background color dark green

# enable user interface interactor
iren.Initialize()
renWin.Render()
iren.Start()
