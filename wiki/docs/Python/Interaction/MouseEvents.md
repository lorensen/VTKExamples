[VTKExamples](/home/)/[Python](/Python)/Interaction/MouseEvents

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Interaction/TestMouseEvents.png?raw=true" width="256" />

### Description
This example creates a new vtkInteractorStyle which can be used to implement custom reactions on user events. If you just want to disable single events you can also have a look at []([VTK/Examples/Python/Interaction/MouseEventsObserver]). This specific example just prints a simple message and then calls the original eventhandler of the vtkInteractorStyleTrackballCamera.

**MouseEvents.py**
```python
#!/usr/bin/env python
from __future__ import print_function

import vtk

class MyInteractorStyle(vtk.vtkInteractorStyleTrackballCamera):

    def __init__(self,parent=None):
        self.AddObserver("MiddleButtonPressEvent",self.middleButtonPressEvent)
        self.AddObserver("MiddleButtonReleaseEvent",self.middleButtonReleaseEvent)

    def middleButtonPressEvent(self,obj,event):
        print("Middle Button pressed")
        self.OnMiddleButtonDown()
        return

    def middleButtonReleaseEvent(self,obj,event):
        print("Middle Button released")
        self.OnMiddleButtonUp()
        return


source = vtk.vtkSphereSource()
source.SetCenter(0, 0, 0)
source.SetRadius(1)
source.Update()

mapper = vtk.vtkPolyDataMapper()
mapper.SetInputConnection(source.GetOutputPort())

actor = vtk.vtkActor()
actor.SetMapper(mapper)

renderer = vtk.vtkRenderer()
renderer.SetBackground(1, 1, 1)
renderer.AddActor(actor)

renwin = vtk.vtkRenderWindow()
renwin.AddRenderer(renderer)

interactor = vtk.vtkRenderWindowInteractor()
interactor.SetInteractorStyle(MyInteractorStyle())
interactor.SetRenderWindow(renwin)

interactor.Initialize()
interactor.Start()
```
