import vtk

# Call back function to resize the cone


def boxCallback(obj, event):
    t = vtk.vtkTransform()
    obj.GetTransform(t)
    obj.GetProp3D().SetUserTransform(t)


# Create a Cone
cone = vtk.vtkConeSource()
cone.SetResolution(20)
coneMapper = vtk.vtkPolyDataMapper()
coneMapper.SetInputConnection(cone.GetOutputPort())
coneActor = vtk.vtkActor()
coneActor.SetMapper(coneMapper)

# A renderer and render window
renderer = vtk.vtkRenderer()
renderer.SetBackground(0, 0, 1)
renderer.AddActor(coneActor)

renwin = vtk.vtkRenderWindow()
renwin.AddRenderer(renderer)

# An interactor
interactor = vtk.vtkRenderWindowInteractor()
interactor.SetRenderWindow(renwin)

# A Box widget
boxWidget = vtk.vtkBoxWidget()
boxWidget.SetInteractor(interactor)
boxWidget.SetProp3D(coneActor)
boxWidget.SetPlaceFactor(1.25)  # Make the box 1.25x larger than the actor
boxWidget.PlaceWidget()
boxWidget.On()

# Connect the event to a function
boxWidget.AddObserver("InteractionEvent", boxCallback)

# Start
interactor.Initialize()
interactor.Start()
