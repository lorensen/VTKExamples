import vtk


# Create a sphere
sphereSource = vtk.vtkSphereSource()
sphereSource.SetCenter(0.0, 0.0, 0.0)
sphereSource.SetRadius(10)
sphereSource.Update()

# Create a mapper and actor
mapper = vtk.vtk.vtkPolyDataMapper()
mapper.SetInputConnection(sphereSource.GetOutputPort())

actor = vtk.vtkActor()
actor.SetMapper(mapper)

camera = vtk.vtkCamera()
camera.SetPosition(0, 0, 100)
camera.SetFocalPoint(0, 0, 0)

# Create a renderer, render window, and interactor
renderer = vtk.vtkRenderer()
renderer.SetActiveCamera(camera)

renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)
renderWindowInteractor = vtk.vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)

# Add the actor to the scene
renderer.AddActor(actor)
renderer.SetBackground(1, 1, 1)  # Background color white

# Render and interact
renderWindow.Render()
renderWindowInteractor.Start()
