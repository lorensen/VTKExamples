#!/usr/bin/python

import vtk

g = vtk.vtkMutableDirectedGraph()
latitude = vtk.vtkDoubleArray()
latitude.SetName("latitude")
longitude = vtk.vtkDoubleArray()
longitude.SetName("longitude")
for i in range(-90, 90, 10):
    for j in range(-180, 180, 20):
        g.AddVertex()
        latitude.InsertNextValue(i)
        longitude.InsertNextValue(j)
g.GetVertexData().AddArray(latitude)
g.GetVertexData().AddArray(longitude)

assign = vtk.vtkGeoAssignCoordinates()
mapper = vtk.vtkPolyDataMapper()
if vtk.VTK_MAJOR_VERSION <= 5:
    assign.SetInput(g)
else:
    assign.SetInputData(g)

assign.SetLatitudeArrayName("latitude")
assign.SetLongitudeArrayName("longitude")
assign.SetGlobeRadius(1.0)
assign.Update()

mapper = vtk.vtkGraphMapper()
mapper.SetInputConnection(assign.GetOutputPort())
actor = vtk.vtkActor()
actor.SetMapper(mapper)
ren = vtk.vtkRenderer()
ren.AddActor(actor)
iren = vtk.vtkRenderWindowInteractor()
win = vtk.vtkRenderWindow()
win.AddRenderer(ren)
win.SetInteractor(iren)
ren.ResetCamera()

iren.Initialize()
ren.Render()
iren.Start()
