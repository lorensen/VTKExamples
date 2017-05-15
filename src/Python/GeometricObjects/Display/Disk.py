import vtk

# create a rendering window and renderer
ren = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)

# create a renderwindowinteractor
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)

# create source
source = vtk.vtkDiskSource()
source.SetInnerRadius(1)
source.SetOuterRadius(2)
source.SetRadialResolution(100)
source.SetCircumferentialResolution(100)
source.Update()

# mapper
mapper = vtk.vtkPolyDataMapper()
mapper.SetInput(source.GetOutput())

# actor
actor = vtk.vtkActor()
actor.SetMapper(mapper)

# assign actor to the renderer
ren.AddActor(actor)

# enable user interface interactor
iren.Initialize()
renWin.Render()
iren.Start()
