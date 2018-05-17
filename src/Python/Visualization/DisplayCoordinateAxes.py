#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    colors = vtk.vtkNamedColors()

    sphereSource = vtk.vtkSphereSource()
    sphereSource.SetCenter(0.0, 0.0, 0.0)
    sphereSource.SetRadius(1.0)
    sphereSource.Update()

    polydata = sphereSource.GetOutput()

    # Create a mapper
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputData(polydata)

    # Create an actor
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)

    # A renderer and render window
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("Display Coordinate Axes")
    renderWindow.AddRenderer(renderer)

    # An interactor
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    # Add the actors to the scene
    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("SlateGray"))

    axes = vtk.vtkAxesActor()

    widget = vtk.vtkOrientationMarkerWidget()
    rgba = [0] * 4
    colors.GetColor("Carrot", rgba)
    widget.SetOutlineColor(rgba[0], rgba[1], rgba[2])
    widget.SetOrientationMarker(axes)
    widget.SetInteractor(renderWindowInteractor)
    widget.SetViewport(0.0, 0.0, 0.4, 0.4)
    widget.SetEnabled(1)
    widget.InteractiveOn()

    renderer.GetActiveCamera().Azimuth(50)
    renderer.GetActiveCamera().Elevation(-30)

    renderer.ResetCamera()
    renderWindow.Render()

    # Begin mouse interaction
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
