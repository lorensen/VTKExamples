#!/usr/bin/env python

import vtk

# Create five points. 
origin = [0.0, 0.0, 0.0]
p0 = [1.0, 0.0, 0.0]
p1 = [0.0, 1.0, 0.0]
p2 = [0.0, 1.0, 2.0]
p3 = [1.0, 2.0, 3.0]

# Create a vtkPoints object and store the points in it
points = vtk.vtkPoints()
points.InsertNextPoint(origin)
points.InsertNextPoint(p0)
points.InsertNextPoint(p1)
points.InsertNextPoint(p2)
points.InsertNextPoint(p3)

# Create a cell array to store the lines in and add the lines to it
lines = vtk.vtkCellArray()

for i in range(3):
  line = vtk.vtkLine()
  line.GetPointIds().SetId(0,i)
  line.GetPointIds().SetId(1,i+1)
  lines.InsertNextCell(line)

# Create a polydata to store everything in
linesPolyData = vtk.vtkPolyData()

# Add the points to the dataset
linesPolyData.SetPoints(points)

# Add the lines to the dataset
linesPolyData.SetLines(lines)

# Setup actor and mapper
mapper = vtk.vtkPolyDataMapper()
if vtk.VTK_MAJOR_VERSION <= 5:
    mapper.SetInput(linesPolyData)
else:
    mapper.SetInputData(linesPolyData)

actor = vtk.vtkActor()
actor.SetMapper(mapper)

# Setup render window, renderer, and interactor
renderer = vtk.vtkRenderer()
renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)
renderWindowInteractor = vtk.vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)
renderer.AddActor(actor)

renderWindow.Render()
renderWindowInteractor.Start()
