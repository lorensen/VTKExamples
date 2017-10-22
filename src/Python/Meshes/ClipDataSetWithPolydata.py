import vtk
import numpy as np

# Create polydata to slice the grid with. In this case, use a cone. This could
# be any polydata including a stl file.
cone = vtk.vtkConeSource()
cone.SetResolution(20)
cone.Update()

# implicit function that will be used to slice the mesh
implicitPolyDataDistance = vtk.vtkImplicitPolyDataDistance()
implicitPolyDataDistance.SetInput(cone.GetOutput())

# create a grid
xCoords = vtk.vtkFloatArray()
for x, i in enumerate(np.linspace(-1.0, 1.0, 15)):
    xCoords.InsertNextValue(i)

yCoords = vtk.vtkFloatArray()
for y, i in enumerate(np.linspace(-1.0, 1.0, 15)):
    yCoords.InsertNextValue(i)

zCoords = vtk.vtkFloatArray()
for z, i in enumerate(np.linspace(-1.0, 1.0, 15)):
    zCoords.InsertNextValue(i)

# The coordinates are assigned to the rectilinear grid. Make sure that
# the number of values in each of the XCoordinates, YCoordinates,
# and ZCoordinates is equal to what is defined in SetDimensions().
rgrid = vtk.vtkRectilinearGrid()
rgrid.SetDimensions(x + 1, y + 1, z + 1)
rgrid.SetXCoordinates(xCoords)
rgrid.SetYCoordinates(yCoords)
rgrid.SetZCoordinates(zCoords)

# Create an array to hold distance information
signedDistances = vtk.vtkFloatArray()
signedDistances.SetNumberOfComponents(1)
signedDistances.SetName("SignedDistances")

# Evaluate the signed distance function at all of the grid points
for pointId in range(rgrid.GetNumberOfPoints()):
    p = rgrid.GetPoint(pointId)
    signedDistance = implicitPolyDataDistance.EvaluateFunction(p)
    signedDistances.InsertNextValue(signedDistance)

# add the SignedDistances to the grid
rgrid.GetPointData().SetScalars(signedDistances)

# use vtkClipDataSet to slice the grid with the polydata
clipper = vtk.vtkClipDataSet()
clipper.SetInputData(rgrid)
clipper.InsideOutOn()
clipper.SetValue(0.0)
clipper.Update()

# --- mappers, actors, render, etc. ---
# mapper and actor to view the cone
coneMapper = vtk.vtkPolyDataMapper()
coneMapper.SetInputConnection(cone.GetOutputPort())
coneActor = vtk.vtkActor()
coneActor.SetMapper(coneMapper)

# geometry filter to view the background grid
geometryFilter = vtk.vtkRectilinearGridGeometryFilter()
geometryFilter.SetInputData(rgrid)
geometryFilter.SetExtent(0, x + 1, 0, y + 1, (z + 1) // 2, (z + 1) // 2)
geometryFilter.Update()

rgridMapper = vtk.vtkPolyDataMapper()
rgridMapper.SetInputConnection(geometryFilter.GetOutputPort())

wireActor = vtk.vtkActor()
wireActor.SetMapper(rgridMapper)
wireActor.GetProperty().SetRepresentationToWireframe()
wireActor.GetProperty().SetColor(.1, .1, .1)

# mapper and actor to view the clipped mesh
clipperMapper = vtk.vtkDataSetMapper()
clipperMapper.SetInputConnection(clipper.GetOutputPort())

clipperActor = vtk.vtkActor()
clipperActor.SetMapper(clipperMapper)
clipperActor.GetProperty().SetRepresentationToWireframe()
clipperActor.GetProperty().SetColor(.1, .1, .1)

# A renderer and render window
renderer = vtk.vtkRenderer()
renderer.SetBackground(1, 1, 1)

# add the actors
# renderer.AddActor(coneActor)
renderer.AddActor(wireActor)
renderer.AddActor(clipperActor)

renwin = vtk.vtkRenderWindow()
renwin.AddRenderer(renderer)

# An interactor
interactor = vtk.vtkRenderWindowInteractor()
interactor.SetRenderWindow(renwin)

# Start
interactor.Initialize()
interactor.Start()
