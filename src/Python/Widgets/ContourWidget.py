#!/usr/bin/python

import vtk
import sys
import math

# Create the RenderWindow, Renderer and both Actors

renderer = vtk.vtkRenderer()
renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)

interactor = vtk.vtkRenderWindowInteractor()
interactor.SetRenderWindow(renderWindow)

renderer.SetBackground(0.1, 0.2, 0.4)
renderWindow.SetSize(600, 600)

contourRep = vtk.vtkOrientedGlyphContourRepresentation()
contourRep.GetLinesProperty().SetColor(1, 0, 0)  # set color to red

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
lines = vtk.vtkCellArray()

for i in range(0, 21):
    angle = 2.0 * math.pi * i / 20.0
    points.InsertPoint(i, 0.1 * math.cos(angle),
                       0.1 * math.sin(angle), 0.0)
    lines.InsertNextCell(i)

pd.SetPoints(points)
pd.SetLines(lines)

contourWidget.Initialize(pd, 1)
contourWidget.Render()
renderer.ResetCamera()
renderWindow.Render()

interactor.Initialize()
interactor.Start()

contourWidget.Off()
