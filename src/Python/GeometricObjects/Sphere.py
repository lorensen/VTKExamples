#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Create a sphere
    sphereSource = vtk.vtkSphereSource()
    sphereSource.SetCenter(0.0, 0.0, 0.0)
    sphereSource.SetRadius(5.0)
    # Make the surface smooth.
    sphereSource.SetPhiResolution(100)
    sphereSource.SetThetaResolution(100)

    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(sphereSource.GetOutputPort())

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetColor(colors.GetColor3d("Cornsilk"))

    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("Sphere")
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("DarkGreen"))

    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
