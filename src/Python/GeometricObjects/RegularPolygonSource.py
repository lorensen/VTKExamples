#!/usr/bin/env python

import vtk

# Create a pentagon
polygonSource = vtk.vtkRegularPolygonSource()

#polygonSource.GeneratePolygonOff()
polygonSource.SetNumberOfSides(5)
polygonSource.SetRadius(5)
polygonSource.SetCenter(0,0,0)
polygonSource.Update()

mapper = vtk.vtkPolyDataMapper()
mapper.SetInputConnection(polygonSource.GetOutputPort())
actor = vtk.vtkActor()
actor.SetMapper(mapper)

renderer = vtk.vtkRenderer()
renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)
renderWindowInteractor = vtk.vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)

renderer.AddActor(actor)
renderer.SetBackground(.3,.3,.5) # Background color purple

renderWindow.Render()
renderWindowInteractor.Start()
