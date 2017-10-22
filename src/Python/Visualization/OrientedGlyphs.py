import vtk

sphereSource = vtk.vtkSphereSource()
sphereSource.Update()

input_data = vtk.vtkPolyData()
input_data.ShallowCopy(sphereSource.GetOutput())

arrowSource = vtk.vtkArrowSource()

glyph3D = vtk.vtkGlyph3D()
glyph3D.SetSourceConnection(arrowSource.GetOutputPort())
glyph3D.SetVectorModeToUseNormal()
glyph3D.SetInputData(input_data)
glyph3D.SetScaleFactor(.2)
glyph3D.Update()

# Visualize
mapper = vtk.vtkPolyDataMapper()
mapper.SetInputConnection(glyph3D.GetOutputPort())

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
