#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    colors = vtk.vtkNamedColors()

    diskSource = vtk.vtkDiskSource()

    # Create a mapper and actor.
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(diskSource.GetOutputPort())

    actor = vtk.vtkActor()
    actor.GetProperty().SetColor(colors.GetColor3d("Cornsilk"))
    actor.SetMapper(mapper)

    # Create a renderer, render window, and interactor
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("Disk")
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    # Add the actors to the scene
    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("DarkGreen"))

    # Render and interact
    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
