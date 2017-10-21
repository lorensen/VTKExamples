#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# by Panos Mavrogiorgos, email : pmav99 >a< gmail

import vtk

# The source file
file_name = "uGridEx.vtk"

# Create a custom lut. The lut is used both at the mapper and at the
# scalar_bar
lut = vtk.vtkLookupTable()
lut.Build()

# Read the source file.
reader = vtk.vtkUnstructuredGridReader()
reader.SetFileName(file_name)
reader.Update()  # Needed because of GetScalarRange
output = reader.GetOutput()
scalar_range = output.GetScalarRange()

mapper = vtk.vtkDataSetMapper()
if vtk.VTK_MAJOR_VERSION <= 5:
    mapper.SetInput(output)
else:
    mapper.SetInputData(output)
mapper.SetScalarRange(scalar_range)
mapper.SetLookupTable(lut)

actor = vtk.vtkActor()
actor.SetMapper(mapper)

renderer = vtk.vtkRenderer()
renderer.AddActor(actor)
renderer.SetBackground(0.1, 0.2, 0.4)

render_window = vtk.vtkRenderWindow()
render_window.AddRenderer(renderer)
render_window.SetSize(300, 300)

interactor = vtk.vtkRenderWindowInteractor()
interactor.SetRenderWindow(render_window)

# create the scalar_bar
scalar_bar = vtk.vtkScalarBarActor()
scalar_bar.SetOrientationToHorizontal()
scalar_bar.SetLookupTable(lut)

# create the scalar_bar_widget
scalar_bar_widget = vtk.vtkScalarBarWidget()
scalar_bar_widget.SetInteractor(interactor)
scalar_bar_widget.SetScalarBarActor(scalar_bar)
scalar_bar_widget.On()

interactor.Initialize()
render_window.Render()
interactor.Start()
