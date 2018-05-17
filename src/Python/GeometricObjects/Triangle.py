# !/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Create a triangle
    points = vtk.vtkPoints()
    points.InsertNextPoint(1.0, 0.0, 0.0)
    points.InsertNextPoint(0.0, 0.0, 0.0)
    points.InsertNextPoint(0.0, 1.0, 0.0)

    triangle = vtk.vtkTriangle()
    triangle.GetPointIds().SetId(0, 0)
    triangle.GetPointIds().SetId(1, 1)
    triangle.GetPointIds().SetId(2, 2)

    triangles = vtk.vtkCellArray()
    triangles.InsertNextCell(triangle)

    # Create a polydata object
    trianglePolyData = vtk.vtkPolyData()

    # Add the geometry and topology to the polydata
    trianglePolyData.SetPoints(points)
    trianglePolyData.SetPolys(triangles)

    # Create mapper and actor
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputData(trianglePolyData)
    actor = vtk.vtkActor()
    actor.GetProperty().SetColor(colors.GetColor3d("Cyan"))
    actor.SetMapper(mapper)

    # Create a renderer, render window, and an interactor
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("Triangle")
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
