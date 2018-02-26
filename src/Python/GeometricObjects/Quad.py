#!/usr/bin/env python

import vtk

def main():
    colors = vtk.vtkNamedColors()

    # Create four points (must be in counter clockwise order)
    p0 = [0.0, 0.0, 0.0]
    p1 = [1.0, 0.0, 0.0]
    p2 = [1.0, 1.0, 0.0]
    p3 = [0.0, 1.0, 0.0]

    # Add the points to a vtkPoints object
    points = vtk.vtkPoints()
    points.InsertNextPoint(p0)
    points.InsertNextPoint(p1)
    points.InsertNextPoint(p2)
    points.InsertNextPoint(p3)

    # Create a quad on the four points
    quad = vtk.vtkQuad()
    quad.GetPointIds().SetId(0, 0)
    quad.GetPointIds().SetId(1, 1)
    quad.GetPointIds().SetId(2, 2)
    quad.GetPointIds().SetId(3, 3)

    # Create a cell array to store the quad in
    quads = vtk.vtkCellArray()
    quads.InsertNextCell(quad)

    # Create a polydata to store everything in
    polydata = vtk.vtkPolyData()

    # Add the points and quads to the dataset
    polydata.SetPoints(points)
    polydata.SetPolys(quads)

    # Setup actor and mapper
    mapper = vtk.vtkPolyDataMapper()
    if vtk.VTK_MAJOR_VERSION <= 5:
        mapper.SetInput(polydata)
    else:
        mapper.SetInputData(polydata)

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetColor(colors.GetColor3d("Silver"))

    # Setup render window, renderer, and interactor
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("Quad")
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("Salmon"))
    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
