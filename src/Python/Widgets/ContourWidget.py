#!/usr/bin/python

import math
import sys

import vtk


def main():
    colors = vtk.vtkNamedColors()

    colors.SetColor('bkg', [0.1, 0.2, 0.4, 1.0])

    # Create the RenderWindow, Renderer and both Actors

    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)

    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderWindow)

    renderer.SetBackground(colors.GetColor3d("bkg"))
    renderWindow.SetSize(600, 600)

    contourRep = vtk.vtkOrientedGlyphContourRepresentation()
    contourRep.GetLinesProperty().SetColor(colors.GetColor3d("Red"))

    contourWidget = vtk.vtkContourWidget()
    contourWidget.SetInteractor(interactor)
    contourWidget.SetRepresentation(contourRep)
    contourWidget.On()

    for arg in sys.argv:
        if "-Shift" == arg:
            contourWidget.GetEventTranslator().RemoveTranslation(
                vtk.vtkCommand.LeftButtonPressEvent)
            contourWidget.GetEventTranslator().SetTranslation(
                vtk.vtkCommand.LeftButtonPressEvent,
                vtk.vtkWidgetEvent.Translate)
        elif "-Scale" == arg:
            contourWidget.GetEventTranslator().RemoveTranslation(
                vtk.vtkCommand.LeftButtonPressEvent)
            contourWidget.GetEventTranslator().SetTranslation(
                vtk.vtkCommand.LeftButtonPressEvent,
                vtk.vtkWidgetEvent.Scale)

    pd = vtk.vtkPolyData()

    points = vtk.vtkPoints()

    num_pts = 21
    for i in range(0, num_pts):
        angle = 2.0 * math.pi * i / 20.0
        points.InsertPoint(i, 0.1 * math.cos(angle),
                           0.1 * math.sin(angle), 0.0)
        # lines.InsertNextCell(i)
    vertex_indices = list(range(0, num_pts))
    vertex_indices.append(0)
    lines = vtk.vtkCellArray()
    lines.InsertNextCell(num_pts + 1, vertex_indices)

    pd.SetPoints(points)
    pd.SetLines(lines)

    # contourWidget.Initialize(pd, 1)
    contourWidget.Initialize(pd, 1)
    contourWidget.Render()
    renderer.ResetCamera()
    renderWindow.Render()

    interactor.Initialize()
    interactor.Start()


if __name__ == '__main__':
    main()
