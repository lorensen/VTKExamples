#!/usr/bin/env python
#Author: Pavan Kumar B N
#Organization: Virtual Environments Lab, Chung-Ang Univeristy, Seoul, South Korea.
#Email: pavanbn8@gmail.com

import vtk
filename = "vw_knee.slc"

#vtkSLCReader to read
reader = vtk.vtkSLCReader()
reader.SetFileName(filename)
reader.Update()

#create a mapper
mapper = vtk.vtkPolyDataMapper()
if vtk.VTK_MAJOR_VERSION <= 5:
    mapper.SetInput(reader.GetOutput())
else:
    mapper.SetInputConnection(reader.GetOutputPort())

#Implementing Marching Cubes Algorithm to create the surface using vtkContourFilter object 	
contourFilter = vtk.vtkContourFilter()
contourFilter.SetInputConnection(reader.GetOutputPort())
contourFilter.SetValue(0,72.0)  

outliner = vtk.vtkOutlineFilter()
outliner.SetInputConnection(reader.GetOutputPort())
outliner.Update()

mapper = vtk.vtkPolyDataMapper()
mapper.SetInputConnection(contourFilter.GetOutputPort())
mapper.SetScalarVisibility(0)

colors = vtk.vtkNamedColors()
actor = vtk.vtkActor()
actor.SetMapper(mapper)

# Create a rendering window and renderer
renderer = vtk.vtkRenderer()
renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)

# Create a renderwindowinteractor
renderWindowInteractor = vtk.vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)

# Assign actor to the renderer
renderer.AddActor(actor)
renderer.SetBackground(colors.GetColor3d("lemon_chiffon"))

# Enable user interface interactor
renderWindowInteractor.Initialize()
renderWindow.Render()
renderWindowInteractor.Start()
