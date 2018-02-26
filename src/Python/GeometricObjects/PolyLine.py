#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Create five points.
    origin = [0.0, 0.0, 0.0]
    p0 = [1.0, 0.0, 0.0]
    p1 = [0.0, 1.0, 0.0]
    p2 = [0.0, 1.0, 2.0]
    p3 = [1.0, 2.0, 3.0]

    # Create a vtkPoints object and store the points in it
    points = vtk.vtkPoints()
    points.InsertNextPoint(origin)
    points.InsertNextPoint(p0)
    points.InsertNextPoint(p1)
    points.InsertNextPoint(p2)
    points.InsertNextPoint(p3)

    polyLine = vtk.vtkPolyLine()
    polyLine.GetPointIds().SetNumberOfIds(5)
    for i in range(0, 5):
        polyLine.GetPointIds().SetId(i, i)

    # Create a cell array to store the lines in and add the lines to it
    cells = vtk.vtkCellArray()
    cells.InsertNextCell(polyLine)

    # Create a polydata to store everything in
    polyData = vtk.vtkPolyData()

    # Add the points to the dataset
    polyData.SetPoints(points)

    # Add the lines to the dataset
    polyData.SetLines(cells)

    # Setup actor and mapper
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputData(polyData)

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetColor(colors.GetColor3d("Tomato"))

    # Setup render window, renderer, and interactor
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("PolyLine")
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)
    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("DarkOliveGreen"))

    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
