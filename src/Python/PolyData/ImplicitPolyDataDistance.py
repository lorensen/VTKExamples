import vtk
import numpy as np

sphereSource = vtk.vtkSphereSource()
sphereSource.SetCenter(0.0, 0.0, 0.0)
sphereSource.SetRadius(1.0)
sphereSource.Update()

sphereMapper = vtk.vtkPolyDataMapper()
sphereMapper.SetInputConnection(sphereSource.GetOutputPort())
sphereMapper.ScalarVisibilityOff()

sphereActor = vtk.vtkActor()
sphereActor.SetMapper(sphereMapper)
sphereActor.GetProperty().SetOpacity(.3)
sphereActor.GetProperty().SetColor(1, 0, 0)

implicitPolyDataDistance = vtk.vtkImplicitPolyDataDistance()
implicitPolyDataDistance.SetInput(sphereSource.GetOutput())

# Setup a grid
points = vtk.vtkPoints()
step = 0.1
for x in np.arange(-2, 2, step):
    for y in np.arange(-2, 2, step):
        for z in np.arange(-2, 2, step):
            points.InsertNextPoint(x, y, z)


# Add distances to each point
signedDistances = vtk.vtkFloatArray()
signedDistances.SetNumberOfComponents(1)
signedDistances.SetName("SignedDistances")

# Evaluate the signed distance function at all of the grid points
for pointId in range(points.GetNumberOfPoints()):
    p = points.GetPoint(pointId)
    signedDistance = implicitPolyDataDistance.EvaluateFunction(p)
    signedDistances.InsertNextValue(signedDistance)

polyData = vtk.vtkPolyData()
polyData.SetPoints(points)
polyData.GetPointData().SetScalars(signedDistances)

vertexGlyphFilter = vtk.vtkVertexGlyphFilter()
vertexGlyphFilter.SetInputData(polyData)
vertexGlyphFilter.Update()

signedDistanceMapper = vtk.vtkPolyDataMapper()
signedDistanceMapper.SetInputConnection(vertexGlyphFilter.GetOutputPort())
signedDistanceMapper.ScalarVisibilityOn()

signedDistanceActor = vtk.vtkActor()
signedDistanceActor.SetMapper(signedDistanceMapper)

renderer = vtk.vtkRenderer()
renderer.AddViewProp(sphereActor)
renderer.AddViewProp(signedDistanceActor)

renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)

renWinInteractor = vtk.vtkRenderWindowInteractor()
renWinInteractor.SetRenderWindow(renderWindow)

renderWindow.Render()
renWinInteractor.Start()
