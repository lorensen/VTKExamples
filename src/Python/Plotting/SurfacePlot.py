#!/usr/bin/env python
from math import sin, sqrt

import vtk

def main():
    colors = vtk.vtkNamedColors()

    chart = vtk.vtkChartXYZ()
    chart.SetGeometry(vtk.vtkRectf(10.0, 10.0, 630, 470))

    plot = vtk.vtkPlotSurface()

    view = vtk.vtkContextView()
    view.GetRenderer().SetBackground(colors.GetColor3d("Silver"))
    view.GetRenderWindow().SetSize(640, 480)
    view.GetScene().AddItem(chart)

    # Create a surface
    table = vtk.vtkTable()
    numPoints = 70
    inc = 9.424778 / (numPoints - 1)
    for i in range(numPoints):
        arr = vtk.vtkFloatArray()
        table.AddColumn(arr)

    table.SetNumberOfRows(numPoints)
    for i in range(numPoints):
        x = i * inc
        for j in range(numPoints):
            y = j * inc
            table.SetValue(i, j, sin(sqrt(x*x + y*y)))

    # Set up the surface plot we wish to visualize and add it to the chart
    plot.SetXRange(0, 10.0)
    plot.SetYRange(0, 10.0)
    plot.SetInputData(table)
    plot.GetPen().SetColorF(colors.GetColor3d("Tomato"))
    chart.AddPlot(plot)

    view.GetRenderWindow().SetMultiSamples(0)
    view.GetInteractor().Initialize()
    view.GetRenderWindow().Render()

    # Rotate
    mouseEvent = vtk.vtkContextMouseEvent()
    mouseEvent.SetInteractor(view.GetInteractor())

    pos = vtk.vtkVector2i()

    lastPos = vtk.vtkVector2i()
    mouseEvent.SetButton(vtk.vtkContextMouseEvent.LEFT_BUTTON)
    lastPos.Set(100, 50)
    mouseEvent.SetLastScreenPos(lastPos)
    pos.Set(150, 100)
    mouseEvent.SetScreenPos(pos)

    sP = [float(x) for x in pos]
    lSP = [float(x) for x in lastPos]
    screenPos = [float(x) for x in mouseEvent.GetScreenPos()]
    lastScreenPos = [float(x) for x in mouseEvent.GetLastScreenPos()]

    chart.MouseMoveEvent(mouseEvent)

    view.GetInteractor().Start()

if __name__=='__main__':
    main()
