#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Create a sphere
    cylinderSource = vtk.vtkCylinderSource()
    cylinderSource.SetCenter(0.0, 0.0, 0.0)
    cylinderSource.SetRadius(5.0)
    cylinderSource.SetHeight(7.0)
    cylinderSource.SetResolution(100)

    # Create a mapper and actor
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(cylinderSource.GetOutputPort())
    actor = vtk.vtkActor()
    actor.GetProperty().SetColor(colors.GetColor3d("Cornsilk"))
    actor.SetMapper(mapper)

    # Create a renderer, render window, and interactor
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("Cylinder")
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    # Add the actor to the scene
    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("DarkGreen"))

    # Render and interact
    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
