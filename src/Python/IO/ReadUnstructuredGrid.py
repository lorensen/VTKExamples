#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# by Panos Mavrogiorgos, email: pmav99 <> gmail

import vtk.vtk

# The source file
file_name = "uGridEx.vtk"

# Read the source file.
reader = vtk.vtkUnstructuredGridReader()
reader.SetFileName(file_name)
reader.Update()  # Needed because of GetScalarRange
output = reader.GetOutput()
scalar_range = output.GetScalarRange()

# Create the mapper that corresponds the objects of the vtk.vtk file
# into graphics elements
mapper = vtk.vtkDataSetMapper()
mapper.SetInputData(output)
mapper.SetScalarRange(scalar_range)

# Create the Actor
actor = vtk.vtkActor()
actor.SetMapper(mapper)

# Create the Renderer
renderer = vtk.vtkRenderer()
renderer.AddActor(actor)
renderer.SetBackground(1, 1, 1)  # Set background to white

# Create the RendererWindow
renderer_window = vtk.vtkRenderWindow()
renderer_window.AddRenderer(renderer)

# Create the RendererWindowInteractor and display the vtk_file
interactor = vtk.vtkRenderWindowInteractor()
interactor.SetRenderWindow(renderer_window)
interactor.Initialize()
interactor.Start()
