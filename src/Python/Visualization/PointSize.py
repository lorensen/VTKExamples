import vtk

# create a rendering window and renderer
ren = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)

# create a renderwindowinteractor
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)


# create source
src = vtk.vtkPointSource()
src.SetCenter(0, 0, 0)
src.SetNumberOfPoints(50)
src.SetRadius(5)
src.Update()


# mapper
mapper = vtk.vtkPolyDataMapper()
mapper.SetInputConnection(src.GetOutputPort())

# actor
actor = vtk.vtkActor()
actor.SetMapper(mapper)

actor.GetProperty().SetPointSize(5)

# assign actor to the renderer
ren.AddActor(actor)

# enable user interface interactor
iren.Initialize()
renWin.Render()
iren.Start()
