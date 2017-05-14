import vtk

sphere = vtk.vtkSphere()
sphere.SetCenter(0, 0, 0)
sphere.SetRadius(0.5)

# The sample function generates a distance function from the implicit
# function. This is then contoured to get a polygonal surface.
sample = vtk.vtkSampleFunction()
sample.SetImplicitFunction(sphere)
sample.SetModelBounds(-.5, .5, -.5, .5, -.5, .5)
sample.SetSampleDimensions(20, 20, 20)
sample.ComputeNormalsOff()

# contour
surface = vtk.vtkContourFilter()
surface.SetInputConnection(sample.GetOutputPort())
surface.SetValue(0, 0.0)

# mapper
mapper = vtk.vtkPolyDataMapper()
mapper.SetInputConnection(surface.GetOutputPort())
mapper.ScalarVisibilityOff()
actor = vtk.vtkActor()
actor.SetMapper(mapper)
actor.GetProperty().EdgeVisibilityOn()
actor.GetProperty().SetEdgeColor(.2, .2, .5)

# A renderer and render window
renderer = vtk.vtkRenderer()
renderer.SetBackground(1, 1, 1)

# add the actor
renderer.AddActor(actor)

# render window
renwin = vtk.vtkRenderWindow()
renwin.AddRenderer(renderer)

# An interactor
interactor = vtk.vtkRenderWindowInteractor()
interactor.SetRenderWindow(renwin)

# Start
interactor.Initialize()
interactor.Start()
