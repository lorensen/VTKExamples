import vtk

input1 = vtk.vtkPolyData()
input2 = vtk.vtkPolyData()

sphereSource = vtk.vtkSphereSource()
sphereSource.SetCenter(5, 0, 0)
sphereSource.Update()

input1.ShallowCopy(sphereSource.GetOutput())

coneSource = vtk.vtkConeSource()
coneSource.Update()

input2.ShallowCopy(coneSource.GetOutput())

# Append the two meshes
appendFilter = vtk.vtkAppendPolyData()
if vtk.VTK_MAJOR_VERSION <= 5:
    appendFilter.AddInputConnection(input1.GetProducerPort())
    appendFilter.AddInputConnection(input2.GetProducerPort())
else:
    appendFilter.AddInputData(input1)
    appendFilter.AddInputData(input2)

appendFilter.Update()

#  Remove any duplicate points.
cleanFilter = vtk.vtkCleanPolyData()
cleanFilter.SetInputConnection(appendFilter.GetOutputPort())
cleanFilter.Update()

# Create a mapper and actor
mapper = vtk.vtkPolyDataMapper()
mapper.SetInputConnection(cleanFilter.GetOutputPort())

actor = vtk.vtkActor()
actor.SetMapper(mapper)

# Create a renderer, render window, and interactor
renderer = vtk.vtkRenderer()
renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)
renderWindowInteractor = vtk.vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)

# Add the actors to the scene
renderer.AddActor(actor)
renderer.SetBackground(.3, .2, .1)  # Background color dark red

# Render and interact
renderWindow.Render()
renderWindowInteractor.Start()
