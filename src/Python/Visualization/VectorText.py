import vtk

# Create a sphere
textSource = vtk.vtkVectorText()
textSource.SetText("Hello")
textSource.Update()

# Create a mapper and actor
mapper = vtk.vtkPolyDataMapper()
mapper.SetInputConnection(textSource.GetOutputPort())

actor = vtk.vtkActor()
actor.SetMapper(mapper)
actor.GetProperty().SetColor(1.0, 0.0, 0.0)

# Create a renderer, render window, and interactor
renderer = vtk.vtkRenderer()
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
