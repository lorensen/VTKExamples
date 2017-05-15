#!/usr/bin/env python

import vtk

# Create the geometry of a point (the coordinate)
points = vtk.vtkPoints()
p = [1.0, 2.0, 3.0]

# Create the topology of the point (a vertex)
vertices = vtk.vtkCellArray()

id = points.InsertNextPoint(p)
vertices.InsertNextCell(1)
vertices.InsertCellPoint(id)

# Create a polydata object
point = vtk.vtkPolyData()

# Set the points and vertices we created as the geometry and topology of the polydata
point.SetPoints(points)
point.SetVerts(vertices)

# Visualize
mapper = vtk.vtkPolyDataMapper()
if vtk.VTK_MAJOR_VERSION <= 5:
    mapper.SetInput(point)
else:
    mapper.SetInputData(point)

actor = vtk.vtkActor()
actor.SetMapper(mapper)
actor.GetProperty().SetPointSize(20)

renderer = vtk.vtkRenderer()
renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)
renderWindowInteractor = vtk.vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)

renderer.AddActor(actor)

renderWindow.Render()
renderWindowInteractor.Start()
