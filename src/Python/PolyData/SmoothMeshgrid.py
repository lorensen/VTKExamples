#!/usr/bin/env python

import vtk
import random
import numpy

# Make a 32 x 32 grid
size = 32

# Define z values for the topography (random height)
topography = numpy.zeros([size, size])
for i in range(size):
    for j in range(size):
        topography[i][j] = random.randrange(0, 5)

# Define points, triangles and colors
colors = vtk.vtkUnsignedCharArray()
colors.SetNumberOfComponents(3)
points = vtk.vtkPoints()
triangles = vtk.vtkCellArray()

# Build the meshgrid manually
count = 0
for i in range(size-1):
    for j in range(size-1):
        
        z1 = topography[i][j]
        z2 = topography[i][j+1]
        z3 = topography[i+1][j]
        
        # Triangle 1
        points.InsertNextPoint(i, j, z1)
        points.InsertNextPoint(i, (j+1), z2)
        points.InsertNextPoint((i+1), j, z3)
        
        triangle = vtk.vtkTriangle()
        triangle.GetPointIds().SetId(0, count)
        triangle.GetPointIds().SetId(1, count + 1)
        triangle.GetPointIds().SetId(2, count + 2)
        
        triangles.InsertNextCell(triangle)
        
        z1 = topography[i][j+1]
        z2 = topography[i+1][j+1]
        z3 = topography[i+1][j]
        
        # Triangle 2
        points.InsertNextPoint(i, (j+1), z1)
        points.InsertNextPoint((i+1), (j+1), z2)
        points.InsertNextPoint((i+1), j, z3)
        
        triangle = vtk.vtkTriangle()
        triangle.GetPointIds().SetId(0, count + 3)
        triangle.GetPointIds().SetId(1, count + 4)
        triangle.GetPointIds().SetId(2, count + 5)
        
        count += 6
        
        triangles.InsertNextCell(triangle)
        
        # Add some color
        r = [int(i/float(size)*255),int(j/float(size)*255),0]
        colors.InsertNextTupleValue(r)
        colors.InsertNextTupleValue(r)
        colors.InsertNextTupleValue(r)
        colors.InsertNextTupleValue(r)
        colors.InsertNextTupleValue(r)
        colors.InsertNextTupleValue(r)

# Create a polydata object
trianglePolyData = vtk.vtkPolyData()

# Add the geometry and topology to the polydata
trianglePolyData.SetPoints(points)
trianglePolyData.GetPointData().SetScalars(colors)
trianglePolyData.SetPolys(triangles)

# Clean the polydata so that the edges are shared !
cleanPolyData = vtk.vtkCleanPolyData()
cleanPolyData.SetInputData(trianglePolyData)

# Use a filter to smooth the data (will add triangles and smooth)
# Use two different filters to show the difference
smooth_loop = vtk.vtkLoopSubdivisionFilter()
smooth_loop.SetNumberOfSubdivisions(3)
smooth_loop.SetInputConnection(cleanPolyData.GetOutputPort())
smooth_butterfly = vtk.vtkButterflySubdivisionFilter()
smooth_butterfly.SetNumberOfSubdivisions(3)
smooth_butterfly.SetInputConnection(cleanPolyData.GetOutputPort())

# Create a mapper and actor for initial dataset
mapper = vtk.vtkPolyDataMapper()
mapper.SetInputData(trianglePolyData)
actor = vtk.vtkActor()
actor.SetMapper(mapper)

# Create a mapper and actor for smoothed dataset (vtkLoopSubdivisionFilter)
mapper = vtk.vtkPolyDataMapper()
mapper.SetInputConnection(smooth_loop.GetOutputPort())
actor_loop = vtk.vtkActor()
actor_loop.SetMapper(mapper)
actor_loop.SetPosition(32, 0, 0)

# Create a mapper and actor for smoothed dataset (vtkButterflySubdivisionFilter)
mapper = vtk.vtkPolyDataMapper()
mapper.SetInputConnection(smooth_butterfly.GetOutputPort())
actor_butterfly = vtk.vtkActor()
actor_butterfly.SetMapper(mapper)
actor_butterfly.SetPosition(64, 0, 0)

# Visualise
renderer = vtk.vtkRenderer()
renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)
renderWindowInteractor = vtk.vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)

# Add actors and render
renderer.AddActor(actor)
renderer.AddActor(actor_loop)
renderer.AddActor(actor_butterfly)

renderer.SetBackground(1, 1, 1) # Background color white
renderWindow.SetSize(800, 800)
renderWindow.Render()
renderWindowInteractor.Start()
