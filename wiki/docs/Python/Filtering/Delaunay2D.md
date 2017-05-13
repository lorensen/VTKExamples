[VTKExamples](Home)/[Python](Python)/Filtering/Delaunay2D

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Filtering/TestDelaunay2D.png" width="256" />

### Description
[]([File:VTK_Examples_Python_Filtering_Delaunay2D.png])

**Delaunay2D.py**
```python
#!/usr/bin/python
 
import vtk, random
 
points = vtk.vtkPoints()
 
for x in range(10):
    for y in range(10):
        points.InsertNextPoint(x + random.uniform(-.25, .25), 
                               y + random.uniform(-.25, .25), 0)
 
aPolyData = vtk.vtkPolyData()
aPolyData.SetPoints(points)
 
aCellArray = vtk.vtkCellArray()
 
boundary = vtk.vtkPolyData()
boundary.SetPoints(aPolyData.GetPoints())
boundary.SetPolys(aCellArray)
delaunay = vtk.vtkDelaunay2D()
if vtk.VTK_MAJOR_VERSION <= 5:
    delaunay.SetInput(aPolyData.GetOutput())
    delaunay.SetSource(boundary)
else:
    delaunay.SetInputData(aPolyData)
    delaunay.SetSourceData(boundary)

delaunay.Update()
 
meshMapper = vtk.vtkPolyDataMapper()
meshMapper.SetInputConnection(delaunay.GetOutputPort())
 
meshActor = vtk.vtkActor()
meshActor.SetMapper(meshMapper)
meshActor.GetProperty().SetEdgeColor(0, 0, 1)
meshActor.GetProperty().SetInterpolationToFlat()
meshActor.GetProperty().SetRepresentationToWireframe()
 
boundaryMapper = vtk.vtkPolyDataMapper()
if vtk.VTK_MAJOR_VERSION <= 5:
    boundaryMapper.SetInputConnection(boundary.GetProducerPort())
else:
    boundaryMapper.SetInputData(boundary)
 
boundaryActor = vtk.vtkActor()
boundaryActor.SetMapper(boundaryMapper)
boundaryActor.GetProperty().SetColor(1, 0, 0)
 
renderer = vtk.vtkRenderer()
renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)
renderWindowInteractor = vtk.vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)
renderer.AddActor(meshActor)
renderer.AddActor(boundaryActor)
renderer.SetBackground(.3, .6, .3)
 
renderWindowInteractor.Initialize()
renderWindow.Render()
renderWindowInteractor.Start()
```
