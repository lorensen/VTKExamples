#!/usr/bin/env python
# -*- coding: utf-8 -*-

import math

import vtk


def main():
    colors = vtk.vtkNamedColors()

    angle = 0
    r1 = 50
    r2 = 30
    centerX = 10.0
    centerY = 5.0

    points = vtk.vtkPoints()
    idx = 0
    while angle <= 2.0 * vtk.vtkMath.Pi() + (vtk.vtkMath.Pi() / 60.0):
        points.InsertNextPoint(r1 * math.cos(angle) + centerX,
                               r2 * math.sin(angle) + centerY,
                               0.0)
        angle = angle + (vtk.vtkMath.Pi() / 60.0)
        idx += 1

    line = vtk.vtkPolyLine()
    line.GetPointIds().SetNumberOfIds(idx)
    for i in range(0, idx):
        line.GetPointIds().SetId(i, i)

    lines = vtk.vtkCellArray()
    lines.InsertNextCell(line)

    polyData = vtk.vtkPolyData()
    polyData.SetPoints(points)
    polyData.SetLines(lines)

    extrude = vtk.vtkLinearExtrusionFilter()
    extrude.SetInputData(polyData)
    extrude.SetExtrusionTypeToNormalExtrusion()
    extrude.SetVector(0, 0, 100.0)
    extrude.Update()

    lineMapper = vtk.vtkPolyDataMapper()
    lineMapper.SetInputData(polyData)

    lineActor = vtk.vtkActor()
    lineActor.SetMapper(lineMapper)
    lineActor.GetProperty().SetColor(colors.GetColor3d("Peacock"))

    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(extrude.GetOutputPort())

    back = vtk.vtkProperty()
    back.SetColor(colors.GetColor3d("Tomato"))

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetColor(colors.GetColor3d("Banana"))
    actor.SetBackfaceProperty(back)

    ren = vtk.vtkRenderer()
    ren.SetBackground(colors.GetColor3d("SlateGray"))
    ren.AddActor(actor)
    ren.AddActor(lineActor)

    renWin = vtk.vtkRenderWindow()
    renWin.SetWindowName("Elliptical Cylinder")
    renWin.AddRenderer(ren)
    renWin.SetSize(600, 600)

    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    style = vtk.vtkInteractorStyleTrackballCamera()
    iren.SetInteractorStyle(style)

    camera = vtk.vtkCamera()
    camera.SetPosition(0, 1, 0)
    camera.SetFocalPoint(0, 0, 0)
    camera.SetViewUp(0, 0, 1)
    camera.Azimuth(30)
    camera.Elevation(30)

    ren.SetActiveCamera(camera)
    ren.ResetCamera()
    ren.ResetCameraClippingRange()

    renWin.Render()
    iren.Start()


if __name__ == '__main__':
    main()
