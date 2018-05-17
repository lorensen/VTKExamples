#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Set the background color.
    colors.SetColor("BkgColor", [26, 51, 77, 255])

    # Create a plane
    planeSource = vtk.vtkPlaneSource()
    planeSource.SetCenter(1.0, 0.0, 0.0)
    planeSource.SetNormal(1.0, 0.0, 1.0)
    planeSource.Update()

    plane = planeSource.GetOutput()

    # Create a mapper and actor
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputData(plane)

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetColor(colors.GetColor3d("Cyan"))

    # Create a renderer, render window and interactor
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("Plane")
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    # Add the actors to the scene
    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("BkgColor"))

    # Render and interact
    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()

# import vtk
#
# # create a rendering window and renderer
# ren = vtk.vtkRenderer()
# renWin = vtk.vtkRenderWindow()
# renWin.AddRenderer(ren)
#
# # create a renderwindowinteractor
# iren = vtk.vtkRenderWindowInteractor()
# iren.SetRenderWindow(renWin)
#
# # create source
# source = vtk.vtkPlaneSource()
# source.SetCenter(1, 0, 0)
# source.SetNormal(1, 0, 1)
#
# # mapper
# mapper = vtk.vtkPolyDataMapper()
# mapper.SetInputConnection(source.GetOutputPort())
#
# # actor
# actor = vtk.vtkActor()
# actor.SetMapper(mapper)
#
# # assign actor to the renderer
# ren.AddActor(actor)
#
# # enable user interface interactor
# iren.Initialize()
# renWin.Render()
# iren.Start()
