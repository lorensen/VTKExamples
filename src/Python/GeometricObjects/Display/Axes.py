import vtk

#create a Sphere
sphereSource = vtk.vtkSphereSource()
sphereSource.SetCenter(0.0, 0.0, 0.0)
sphereSource.SetRadius(0.5)
 
#create a mapper
sphereMapper = vtk.vtkPolyDataMapper()
sphereMapper.SetInputConnection(sphereSource.GetOutputPort())
 
#create an actor
sphereActor = vtk.vtkActor()
sphereActor.SetMapper(sphereMapper)
 
#a renderer and render window
renderer = vtk.vtkRenderer()
renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)
 
#an interactor
renderWindowInteractor = vtk.vtkRenderWindowInteractor() 
renderWindowInteractor.SetRenderWindow(renderWindow)
 
#add the actors to the scene
renderer.AddActor(sphereActor)
renderer.SetBackground(.1,.2,.3) # Background dark blue
 
transform = vtk.vtkTransform()
transform.Translate(1.0, 0.0, 0.0)
 
axes = vtk.vtkAxesActor()
#  The axes are positioned with a user transform
axes.SetUserTransform(transform)
 
# properties of the axes labels can be set as follows
# this sets the x axis label to red
# axes->GetXAxisCaptionActor2D()->GetCaptionTextProperty()->SetColor(1,0,0);
 
# the actual text of the axis label can be changed:
# axes->SetXAxisLabelText("test");
 
renderer.AddActor(axes)
 
renderer.ResetCamera()
renderWindow.Render()
 
# begin mouse interaction
renderWindowInteractor.Start()
