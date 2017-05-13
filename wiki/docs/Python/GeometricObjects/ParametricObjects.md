[VTKExamples](/index/)/[Python](/Python)/GeometricObjects/ParametricObjects

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/GeometricObjects/TestParametricObjects.png?raw=true" width="256" />

### Description
==Description==
See [Parametric Equations for Surfaces](http://www.vtk.org/VTK/img/ParametricSurfaces.pdf) by Andrew Maclean for an excellent description of these beautiful parametric surfaces.

You can edit the following code by selecting any one of the functions and the corresponding object will be displayed.

**ParametricObjects.py**
```python
#!/usr/bin/env python

import vtk
import random

class ParametricObjects():

    def ParametricObjects(self):

        # Select one of the following functions.
        parametricObject = vtk.vtkParametricTorus()
#         parametricObject = vtk.vtkParametricBoy()
#         parametricObject = vtk.vtkParametricConicSpiral()
#         parametricObject = vtk.vtkParametricCrossCap()
#         parametricObject = vtk.vtkParametricDini()
#         parametricObject = vtk.vtkParametricEllipsoid()
#         parametricObject = vtk.vtkParametricEnneper()
#         parametricObject = vtk.vtkParametricFigure8Klein()
#         parametricObject = vtk.vtkParametricKlein()
#         parametricObject = vtk.vtkParametricMobius()
#         parametricObject = vtk.vtkParametricRandomHills()
#         parametricObject = vtk.vtkParametricRoman()
#         parametricObject = vtk.vtkParametricSpline()
#         parametricObject = vtk.vtkParametricSuperEllipsoid()
#         parametricObject = vtk.vtkParametricSuperToroid()
#         parametricObject = vtk.vtkParametricTorus()

        parametricSource = vtk.vtkParametricFunctionSource()
        parametricSource.SetParametricFunction(parametricObject)

        # mapper
        mapper = vtk.vtkPolyDataMapper()
        mapper.SetInputConnection(parametricSource.GetOutputPort())

        # actor
        actor = vtk.vtkActor()
        actor.SetMapper(mapper)

        # ------------------------------------------------------------
        # Create the RenderWindow, Renderer and Interactor
        # ------------------------------------------------------------
        ren = vtk.vtkRenderer()
        renWin = vtk.vtkRenderWindow()
        iren = vtk.vtkRenderWindowInteractor()

        renWin.AddRenderer(ren)
        iren.SetRenderWindow(renWin)

        # add actors
        ren.AddViewProp(actor)
        ren.SetBackground(1,1,1) # Background color white

        # enable user interface interactor
        iren.Initialize()
        renWin.Render()
        iren.Start()

if __name__ == "__main__":
    po = ParametricObjects()
    po.ParametricObjects()
```
