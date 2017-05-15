import vtk

coneSource = vtk.vtkConeSource()
#coneSource.SetResolution(60)
#coneSource.SetCenter(-2,0,0)
 
# Create a mapper and actor
mapper = vtk.vtkPolyDataMapper()
mapper.SetInput(coneSource.GetOutput())
actor = vtk.vtkActor()
actor.SetMapper(mapper)

# Visualize
renderer = vtk.vtkRenderer()
renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)
renderWindowInteractor = vtk.vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)
 
renderer.AddActor(actor)
renderer.SetBackground(.1, .2, .3) # Background color dark blue
renderer.SetBackground(.3, .2, .1) # Background color dark red
renderWindow.Render()
renderWindowInteractor.Start()
