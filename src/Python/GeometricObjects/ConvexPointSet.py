# !/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    cps = vtk.vtkConvexPointSet()
    points = vtk.vtkPoints()
    points.InsertNextPoint(0, 0, 0)
    points.InsertNextPoint(1, 0, 0)
    points.InsertNextPoint(1, 1, 0)
    points.InsertNextPoint(0, 1, 0)
    points.InsertNextPoint(0, 0, 1)
    points.InsertNextPoint(1, 0, 1)
    points.InsertNextPoint(1, 1, 1)
    points.InsertNextPoint(0, 1, 1)
    points.InsertNextPoint(0.5, 0, 0)
    points.InsertNextPoint(1, 0.5, 0)
    points.InsertNextPoint(0.5, 1, 0)
    points.InsertNextPoint(0, 0.5, 0)
    points.InsertNextPoint(0.5, 0.5, 0)

    for i in range(0, 13):
        cps.GetPointIds().InsertId(i, i)

    ug = vtk.vtkUnstructuredGrid()
    ug.Allocate(1, 1)
    ug.InsertNextCell(cps.GetCellType(), cps.GetPointIds())
    ug.SetPoints(points)

    colors = vtk.vtkNamedColors()

    mapper = vtk.vtkDataSetMapper()
    mapper.SetInputData(ug)

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetColor(colors.GetColor3d("Tomato"))
    actor.GetProperty().SetLineWidth(3)
    actor.GetProperty().EdgeVisibilityOn()

    # Glyph the points
    sphere = vtk.vtkSphereSource()
    sphere.SetPhiResolution(21)
    sphere.SetThetaResolution(21)
    sphere.SetRadius(.03)

    # Create a polydata to store everything in
    polyData = vtk.vtkPolyData()
    polyData.SetPoints(points)

    pointMapper = vtk.vtkGlyph3DMapper()
    pointMapper.SetInputData(polyData)
    pointMapper.SetSourceConnection(sphere.GetOutputPort())

    pointActor = vtk.vtkActor()
    pointActor.SetMapper(pointMapper)
    pointActor.GetProperty().SetColor(colors.GetColor3d("Peacock"))

    # Create a renderer, render window, and interactor
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("Convex Point Set")
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    # Add the actors to the scene
    renderer.AddActor(actor)
    renderer.AddActor(pointActor)
    renderer.SetBackground(colors.GetColor3d("Silver"))

    renderer.ResetCamera()
    renderer.GetActiveCamera().Azimuth(210)
    renderer.GetActiveCamera().Elevation(30)
    renderer.ResetCameraClippingRange()

    # Render and interact
    renderWindow.SetSize(640, 480)
    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
