#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Create a pentagon
    polygonSource = vtk.vtkRegularPolygonSource()
    polygonSource.SetNumberOfSides(5)
    polygonSource.SetRadius(5)
    polygonSource.SetCenter(0, 0, 0)

    shrink = vtk.vtkShrinkPolyData()
    shrink.SetInputConnection(polygonSource.GetOutputPort())
    shrink.SetShrinkFactor(.9)

    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(shrink.GetOutputPort())

    back = vtk.vtkProperty()
    back.SetColor(colors.GetColor3d("Tomato"))

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().EdgeVisibilityOn()
    actor.GetProperty().SetLineWidth(5)
    actor.GetProperty().SetColor(colors.GetColor3d("Banana"))
    actor.SetBackfaceProperty(back)

    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("Regular Polygon Source")
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("Silver"))

    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
