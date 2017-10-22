import vtk

# create an ellipsoid using a implicit quadric
quadric = vtk.vtkQuadric()
quadric.SetCoefficients(.5, 1, .2, 0, .1, 0, 0, .2, 0, 0)

# The sample function generates a distance function from the implicit
# function. This is then contoured to get a polygonal surface.
sample = vtk.vtkSampleFunction()
sample.SetImplicitFunction(quadric)
sample.SetModelBounds(-.5, .5, -.5, .5, -.5, .5)
sample.SetSampleDimensions(40, 40, 40)
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
interactor.Start()
