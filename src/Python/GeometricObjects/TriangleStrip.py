#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    colors = vtk.vtkNamedColors()

    points = vtk.vtkPoints()
    points.InsertNextPoint(0, 0, 0)
    points.InsertNextPoint(0, 1, 0)
    points.InsertNextPoint(1, 0, 0)
    points.InsertNextPoint(1.5, 1, 0)

    triangleStrip = vtk.vtkTriangleStrip()
    triangleStrip.GetPointIds().SetNumberOfIds(4)
    triangleStrip.GetPointIds().SetId(0, 0)
    triangleStrip.GetPointIds().SetId(1, 1)
    triangleStrip.GetPointIds().SetId(2, 2)
    triangleStrip.GetPointIds().SetId(3, 3)

    cells = vtk.vtkCellArray()
    cells.InsertNextCell(triangleStrip)

    polydata = vtk.vtkPolyData()
    polydata.SetPoints(points)
    polydata.SetStrips(cells)

    # Create an actor and mapper
    mapper = vtk.vtkDataSetMapper()
    mapper.SetInputData(polydata)
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetColor(colors.GetColor3d("Cyan"))
    actor.GetProperty().SetRepresentationToWireframe()

    # Create a renderer, render window, and interactor
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("Triangle Strip")
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("DarkGreen"))
    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
