#!/usr/bin/env python

import vtk

points = vtk.vtkPoints()
points.InsertNextPoint(0,0,0)

vertex = vtk.vtkVertex()
vertex.GetPointIds().SetId(0, 0)

vertices = vtk.vtkCellArray()
vertices.InsertNextCell(vertex)

polydata = vtk.vtkPolyData()
polydata.SetPoints(points)
polydata.SetVerts(vertices)


# Setup actor and mapper
mapper = vtk.vtkPolyDataMapper()
if vtk.VTK_MAJOR_VERSION <= 5:
    mapper.SetInputConnection(polydata.GetProducerPort())
else:
    mapper.SetInputData(polydata)

actor = vtk.vtkActor()
actor.SetMapper(mapper)
actor.GetProperty().SetPointSize(10)

# Setup render window, renderer, and interactor
renderer = vtk.vtkRenderer()
renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)
renderWindowInteractor = vtk.vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)
renderer.AddActor(actor)

renderWindow.Render()
renderWindowInteractor.Start()
