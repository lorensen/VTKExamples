#!/usr/bin/env python

import vtk

points = vtk.vtkPoints()
points.InsertNextPoint(0,0,0)
points.InsertNextPoint(0,1,0)
points.InsertNextPoint(1,0,0)
points.InsertNextPoint(1.5,1,0)

triangleStrip = vtk.vtkTriangleStrip()
triangleStrip.GetPointIds().SetNumberOfIds(4)
triangleStrip.GetPointIds().SetId(0,0)
triangleStrip.GetPointIds().SetId(1,1)
triangleStrip.GetPointIds().SetId(2,2)
triangleStrip.GetPointIds().SetId(3,3)

cells = vtk.vtkCellArray()
cells.InsertNextCell(triangleStrip)

polydata = vtk.vtkPolyData()
polydata.SetPoints(points)
polydata.SetStrips(cells)

# Create an actor and mapper
mapper = vtk.vtkDataSetMapper()
if vtk.VTK_MAJOR_VERSION <= 5:
    mapper.SetInput(polydata)
else:
    mapper.SetInputData(polydata)

actor = vtk.vtkActor()
actor.SetMapper(mapper)
actor.GetProperty().SetRepresentationToWireframe()

# Create a renderer, render window, and interactor
renderer = vtk.vtkRenderer()
renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)
renderWindowInteractor = vtk.vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)

renderer.AddActor(actor)
renderWindow.Render()
renderWindowInteractor.Start()
