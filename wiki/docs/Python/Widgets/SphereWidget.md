[VTKExamples](Home)/[Python](Python)/Widgets/SphereWidget

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Widgets/TestSphereWidget.png" width="256" />

### Description
[Examples Python Widgets SphereWidget.png]]([File:VTK)

This example shows how to use the SphereWidget.

**SphereWidget.py**
```python
import vtk

# Call back function
def sphereCallback(obj, event):
    print('Center: {}, {}, {}'.format(*obj.GetCenter()))

# A renderer and render window
renderer = vtk.vtkRenderer()
renderer.SetBackground(1, 1, 1)

renwin = vtk.vtkRenderWindow()
renwin.AddRenderer(renderer)
 
# An interactor
interactor = vtk.vtkRenderWindowInteractor()
interactor.SetRenderWindow(renwin)

# A Sphere widget
sphereWidget = vtk.vtkSphereWidget()
sphereWidget.SetInteractor(interactor)
sphereWidget.SetRepresentationToSurface()
sphereWidget.On()

# Connect the event to a function
sphereWidget.AddObserver("InteractionEvent", sphereCallback)
 
# Start
interactor.Initialize()
interactor.Start()
```
