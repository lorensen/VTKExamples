#!/usr/bin/env python
# -*- coding: utf-8 -*-

# This example demonstrates how to create a polyline through several ordered points.

import vtk

import math

def main():
    colors = vtk.vtkNamedColors()

    # Set the background color.
    colors.SetColor("BkgColor", [26, 51, 102, 255])

    # vtkPoints represents 3D points. The data model for vtkPoints is an array of
    # vx-vy-vz triplets accessible by (point or cell) id.
    points = vtk.vtkPoints()
    points.SetNumberOfPoints(6)
    c = math.cos(math.pi / 6)  # helper variable
    points.SetPoint(0, 0.0, -1.0, 0.0)
    points.SetPoint(1,   c, -0.5, 0.0)
    points.SetPoint(2,   c,  0.5, 0.0)
    points.SetPoint(3, 0.0,  1.0, 0.0)
    points.SetPoint(4,  -c,  0.5, 0.0)
    points.SetPoint(5,  -c, -0.5, 0.0)

    # vtkCellArray is a supporting object that explicitly represents cell connectivity.
    # The cell array structure is a raw integer list of the form:
    # (n,id1,id2,...,idn, n,id1,id2,...,idn, ...) where n is the number of points in
    # the cell, and id is a zero-offset index into an associated point list.
    lines = vtk.vtkCellArray()
    lines.InsertNextCell(7)
    lines.InsertCellPoint(0)
    lines.InsertCellPoint(1)
    lines.InsertCellPoint(2)
    lines.InsertCellPoint(3)
    lines.InsertCellPoint(4)
    lines.InsertCellPoint(5)
    lines.InsertCellPoint(0)

    # vtkPolyData is a data object that is a concrete implementation of vtkDataSet.
    # vtkPolyData represents a geometric structure consisting of vertices, lines,
    # polygons, and/or triangle strips
    polygon = vtk.vtkPolyData()
    polygon.SetPoints(points)
    polygon.SetLines(lines)

    # vtkPolyDataMapper is a class that maps polygonal data (i.e., vtkPolyData)
    # to graphics primitives
    polygonMapper = vtk.vtkPolyDataMapper()
    polygonMapper.SetInputData(polygon)
    polygonMapper.Update()

    # Create an actor to represent the polygon. The actor orchestrates rendering of
    # the mapper's graphics primitives. An actor also refers to properties via a
    # vtkProperty instance, and includes an internal transformation matrix. We
    # set this actor's mapper to be polygonMapper which we created above.
    polygonActor = vtk.vtkActor()
    polygonActor.SetMapper(polygonMapper)
    polygonActor.GetProperty().SetColor(colors.GetColor3d("AliceBlue"))

    # Create the Renderer and assign actors to it. A renderer is like a
    # viewport. It is part or all of a window on the screen and it is
    # responsible for drawing the actors it has.  We also set the
    # background color here.
    ren = vtk.vtkRenderer()
    ren.AddActor(polygonActor)
    ren.SetBackground(colors.GetColor3d("BkgColor"))

    # Automatically set up the camera based on the visible actors.
    # The camera will reposition itself to view the center point of the actors,
    # and move along its initial view plane normal
    # (i.e., vector defined from camera position to focal point) so that all of the
    # actors can be seen.
    ren.ResetCamera()

    # Finally we create the render window which will show up on the screen
    # We put our renderer into the render window using AddRenderer. We
    # also set the size to be 300 pixels by 300.
    renWin = vtk.vtkRenderWindow()
    renWin.SetWindowName("PolyLine1")
    renWin.AddRenderer(ren)
    renWin.SetSize(300, 300)

    # The vtkRenderWindowInteractor class watches for events (e.g., keypress,
    # mouse) in the vtkRenderWindow. These events are translated into
    # event invocations that VTK understands (see VTK/Common/vtkCommand.h
    # for all events that VTK processes). Then observers of these VTK
    # events can process them as appropriate.
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)
    iren.Initialize()
    iren.Start()

    # There is no explicit need to free any objects at this point.
    # Once Python exits, memory is automatically freed.


if __name__ == '__main__':
    main()
