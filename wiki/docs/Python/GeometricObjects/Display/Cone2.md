[VTKExamples](/home/)/[Python](/Python)/GeometricObjects/Display/Cone2

### Description
<source lang="python">
import vtk

# create a rendering window and renderer
ren = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)
WIDTH=640
HEIGHT=480
renWin.SetSize(WIDTH,HEIGHT)

# create a renderwindowinteractor
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)

# create cone
cone = vtk.vtkConeSource()
cone.SetResolution(60)
cone.SetCenter(-2,0,0)

# mapper
coneMapper = vtk.vtkPolyDataMapper()
coneMapper.SetInput(cone.GetOutput())

# actor
coneActor = vtk.vtkActor()
coneActor.SetMapper(coneMapper)

# assign actor to the renderer
ren.AddActor(coneActor)

# enable user interface interactor
iren.Initialize()
renWin.Render()
iren.Start()
</source>

**Cone2.py**
```python
import vtk

coneSource = vtk.vtkConeSource()
#coneSource.SetResolution(60)
#coneSource.SetCenter(-2,0,0)
 
# Create a mapper and actor
mapper = vtk.vtkPolyDataMapper()
mapper.SetInput(coneSource.GetOutput())
actor = vtk.vtkActor()
actor.SetMapper(mapper)

# Visualize
renderer = vtk.vtkRenderer()
renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)
renderWindowInteractor = vtk.vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)
 
renderer.AddActor(actor)
renderer.SetBackground(.1, .2, .3) # Background color dark blue
renderer.SetBackground(.3, .2, .1) # Background color dark red
renderWindow.Render()
renderWindowInteractor.Start()
```
