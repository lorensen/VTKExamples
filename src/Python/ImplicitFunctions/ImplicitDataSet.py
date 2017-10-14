# Example in which a cube is used to define an implicit function (through vtkImplicitDataSet)
# which is then used to clip a sphere

import vtk

sphere = vtk.vtkSphereSource()
sphere.SetCenter(1, 1, 1)
sphere.SetRadius(1)
sphere.Update()

cube = vtk.vtkCubeSource()
cube.SetBounds(-1, 1, -1, 1, -1, 1)
cube.Update()

# Create 3D cells so vtkImplicitDataSet evaluates inside vs outside correctly
tri = vtk.vtkDelaunay3D()
tri.SetInputConnection(cube.GetOutputPort())
tri.BoundingTriangulationOff()

# vtkImplicitDataSet needs some scalars to interpolate to find inside/outside
elev = vtk.vtkElevationFilter()
elev.SetInputConnection(tri.GetOutputPort())

implicit = vtk.vtkImplicitDataSet()
implicit.SetDataSet(elev.GetOutput())

clipper = vtk.vtkClipPolyData()
clipper.SetClipFunction(implicit)
clipper.SetInputConnection(sphere.GetOutputPort())
clipper.InsideOutOn()
clipper.Update()

# Vis for clipped sphere
mapper = vtk.vtkPolyDataMapper()
mapper.SetInputConnection(clipper.GetOutputPort())
actor = vtk.vtkActor()
actor.SetMapper(mapper)

# Vis for cube so can see it in relation to clipped sphere
mapper2 = vtk.vtkDataSetMapper()
mapper2.SetInputConnection(elev.GetOutputPort())
actor2 = vtk.vtkActor()
actor2.SetMapper(mapper2)
actor2.GetProperty().SetRepresentationToWireframe()

ren1 = vtk.vtkRenderer()
ren1.AddActor(actor)
ren1.AddActor(actor2)
ren1.SetBackground(0.1, 0.2, 0.4)

renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren1)

iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)

renWin.Render()
iren.Start()
