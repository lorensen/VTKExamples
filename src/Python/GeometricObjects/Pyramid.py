#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    colors = vtk.vtkNamedColors()

    points = vtk.vtkPoints()

    p0 = [1.0, 1.0, 1.0]
    p1 = [-1.0, 1.0, 1.0]
    p2 = [-1.0, -1.0, 1.0]
    p3 = [1.0, -1.0, 1.0]
    p4 = [0.0, 0.0, 0.0]

    points.InsertNextPoint(p0)
    points.InsertNextPoint(p1)
    points.InsertNextPoint(p2)
    points.InsertNextPoint(p3)
    points.InsertNextPoint(p4)

    pyramid = vtk.vtkPyramid()
    pyramid.GetPointIds().SetId(0, 0)
    pyramid.GetPointIds().SetId(1, 1)
    pyramid.GetPointIds().SetId(2, 2)
    pyramid.GetPointIds().SetId(3, 3)
    pyramid.GetPointIds().SetId(4, 4)

    cells = vtk.vtkCellArray()
    cells.InsertNextCell(pyramid)

    ug = vtk.vtkUnstructuredGrid()
    ug.SetPoints(points)
    ug.InsertNextCell(pyramid.GetCellType(), pyramid.GetPointIds())

    # Create an actor and mapper
    mapper = vtk.vtkDataSetMapper()
    if vtk.VTK_MAJOR_VERSION <= 5:
        mapper.SetInput(ug)
    else:
        mapper.SetInputData(ug)

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetColor(colors.GetColor3d("Tomato"))

    # Create a renderer, render window, and interactor
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("Pyramid")
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    renderer.AddActor(actor)

    # Create a nice view
    renderer.ResetCamera()
    renderer.GetActiveCamera().Azimuth(180)
    renderer.GetActiveCamera().Elevation(-20)
    renderer.ResetCameraClippingRange()

    renderer.SetBackground(colors.GetColor3d("Silver"))

    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
