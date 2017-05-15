#!/usr/bin/env python

import vtk

# Create three points. Join (Origin and P0) with a red line and
# (Origin and P1) with a green line
origin = [0.0, 0.0, 0.0]
p0 = [1.0, 0.0, 0.0]
p1 = [0.0, 1.0, 0.0]

# Create a vtkPoints object and store the points in it
pts = vtk.vtkPoints()
pts.InsertNextPoint(origin)
pts.InsertNextPoint(p0)
pts.InsertNextPoint(p1)

# Setup two colors - one for each line
red = [255, 0, 0]
green = [0, 255, 0]

# Setup the colors array
colors = vtk.vtkUnsignedCharArray()
colors.SetNumberOfComponents(3)
colors.SetName("Colors")

# Add the colors we created to the colors array
colors.InsertNextTupleValue(red)
colors.InsertNextTupleValue(green)

# Create the first line (between Origin and P0)
line0 = vtk.vtkLine()
line0.GetPointIds().SetId(0,0) # the second 0 is the index of the Origin in the vtkPoints
line0.GetPointIds().SetId(1,1) # the second 1 is the index of P0 in the vtkPoints

# Create the second line (between Origin and P1)
line1 = vtk.vtkLine()
line1.GetPointIds().SetId(0,0) # the second 0 is the index of the Origin in the vtkPoints
line1.GetPointIds().SetId(1,2) # 2 is the index of P1 in the vtkPoints

# Create a cell array to store the lines in and add the lines to it
lines = vtk.vtkCellArray()
lines.InsertNextCell(line0)
lines.InsertNextCell(line1)

# Create a polydata to store everything in
linesPolyData = vtk.vtkPolyData()

# Add the points to the dataset
linesPolyData.SetPoints(pts)

# Add the lines to the dataset
linesPolyData.SetLines(lines)

# Color the lines - associate the first component (red) of the
# colors array with the first component of the cell array (line 0)
# and the second component (green) of the colors array with the
# second component of the cell array (line 1)
linesPolyData.GetCellData().SetScalars(colors)

# Visualize
mapper = vtk.vtkPolyDataMapper()
if vtk.VTK_MAJOR_VERSION <= 5:
    mapper.SetInput(linesPolyData)
else:
    mapper.SetInputData(linesPolyData)

actor = vtk.vtkActor()
actor.SetMapper(mapper)

renderer = vtk.vtkRenderer()
renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)
renderWindowInteractor = vtk.vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)
renderer.AddActor(actor)

renderWindow.Render()
renderWindowInteractor.Start()
