#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk

def main():
    colors = vtk.vtkNamedColors()
    lineColor = colors.GetColor3d("peacock")
    modelColor = colors.GetColor3d("silver")
    backgroundColor = colors.GetColor3d("wheat")

    modelSource = vtk.vtkSphereSource()

    plane = vtk.vtkPlane()

    cutter = vtk.vtkCutter()
    cutter.SetInputConnection(modelSource.GetOutputPort())
    cutter.SetCutFunction(plane)
    cutter.GenerateValues(10, -.5, .5)

    modelMapper = vtk.vtkPolyDataMapper()
    modelMapper.SetInputConnection(modelSource.GetOutputPort())

    model = vtk.vtkActor()
    model.SetMapper(modelMapper)
    model.GetProperty().SetDiffuseColor(modelColor)
    model.GetProperty().SetInterpolationToFlat()

    stripper = vtk.vtkStripper()
    stripper.SetInputConnection(cutter.GetOutputPort())
    stripper.JoinContiguousSegmentsOn()

    linesMapper = vtk.vtkPolyDataMapper()
    linesMapper.SetInputConnection(stripper.GetOutputPort())

    lines = vtk.vtkActor()
    lines.SetMapper(linesMapper)
    lines.GetProperty().SetDiffuseColor(lineColor)
    lines.GetProperty().SetLineWidth(3.)

    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()

    renderWindow.AddRenderer(renderer)
    renderWindow.SetSize(640, 480)

    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderWindow)

    # Add the actors to the renderer.
    renderer.AddActor(model)
    renderer.AddActor(lines)
    renderer.SetBackground(backgroundColor)

    # This starts the event loop and as a side effect causes an
    # initial render.
    renderWindow.Render()
    interactor.Start()

    # Extract the lines from the polydata.
    numberOfLines = cutter.GetOutput().GetNumberOfLines()

    print("-----------Lines without using vtkStripper")
    print("There are {0} lines in the polydata".format(numberOfLines))

    numberOfLines = stripper.GetOutput().GetNumberOfLines()
    points = stripper.GetOutput().GetPoints()
    cells = stripper.GetOutput().GetLines()
    cells.InitTraversal()

    print("-----------Lines using vtkStripper")
    print("There are {0} lines in the polydata".format(numberOfLines))

    indices = vtk.vtkIdList()
    lineCount = 0

    while cells.GetNextCell(indices):
        print("Line {0}:".format(lineCount))
        for i in range(indices.GetNumberOfIds()):
            point = points.GetPoint(indices.GetId(i))
            print("\t({0:0.6f} ,{1:0.6f}, {2:0.6f})".format(point[0], point[1], point[2]))
        lineCount += 1

if __name__ == "__main__":
    main()
