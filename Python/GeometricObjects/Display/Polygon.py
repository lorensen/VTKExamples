#!/usr/bin/env python

import vtk

# Setup four points
points = vtk.vtkPoints()
points.InsertNextPoint(0.0, 0.0, 0.0)
points.InsertNextPoint(1.0, 0.0, 0.0)
points.InsertNextPoint(1.0, 1.0, 0.0)
points.InsertNextPoint(0.0, 1.0, 0.0)

# Create the polygon
polygon = vtk.vtkPolygon()
polygon.GetPointIds().SetNumberOfIds(4) #make a quad
polygon.GetPointIds().SetId(0, 0)
polygon.GetPointIds().SetId(1, 1)
polygon.GetPointIds().SetId(2, 2)
polygon.GetPointIds().SetId(3, 3)

# Add the polygon to a list of polygons
polygons = vtk.vtkCellArray()
polygons.InsertNextCell(polygon)

# Create a PolyData
polygonPolyData = vtk.vtkPolyData()
polygonPolyData.SetPoints(points)
polygonPolyData.SetPolys(polygons)

# Create a mapper and actor
mapper = vtk.vtkPolyDataMapper()
if vtk.VTK_MAJOR_VERSION <= 5:
    mapper.SetInput(polygonPolyData)
else:
    mapper.SetInputData(polygonPolyData)

actor = vtk.vtkActor()
actor.SetMapper(mapper)

# Visualize
renderer = vtk.vtkRenderer()
renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)
renderWindowInteractor = vtk.vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)

renderer.AddActor(actor)
renderer.SetBackground(.5,.3,.31) # Background color salmon

renderWindow.Render()
renderWindowInteractor.Start()
