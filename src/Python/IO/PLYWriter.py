import vtk

filename = "writeply.ply"

sphereSource = vtk.vtkSphereSource()
sphereSource.Update()

plyWriter = vtk.vtkPLYWriter()
plyWriter.SetFileName(filename)
plyWriter.SetInputConnection(sphereSource.GetOutputPort())
plyWriter.Write()

# Read and display for verication
reader = vtk.vtkPLYReader()
reader.SetFileName(filename)
reader.Update()

mapper = vtk.vtkPolyDataMapper()
mapper.SetInputConnection(reader.GetOutputPort())

actor = vtk.vtkActor()
actor.SetMapper(mapper)

renderer = vtk.vtkRenderer()
renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)
renderWindowInteractor = vtk.vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)

renderer.AddActor(actor)
renderer.SetBackground(.3, .6, .3)  # Background color green

renderWindow.Render()
renderWindowInteractor.Start()
