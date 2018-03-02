#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Set the background color.
    colors.SetColor("BkgColor", [51, 77, 102, 255])

    # For the hexahedron setup the coordinates of eight points.
    # The two faces must be in counter clockwise order as viewed from the
    # outside.
    pointCoordinates = list()
    pointCoordinates.append([0.0, 0.0, 0.0])  # Face 1
    pointCoordinates.append([1.0, 0.0, 0.0])
    pointCoordinates.append([1.0, 1.0, 0.0])
    pointCoordinates.append([0.0, 1.0, 0.0])
    pointCoordinates.append([0.0, 0.0, 1.0])  # Face 2
    pointCoordinates.append([1.0, 0.0, 1.0])
    pointCoordinates.append([1.0, 1.0, 1.0])
    pointCoordinates.append([0.0, 1.0, 1.0])

    # Create the points.
    points = vtk.vtkPoints()

    # Create a hexahedron from the points.
    hexahedron = vtk.vtkHexahedron()

    for i in range(0, len(pointCoordinates)):
        points.InsertNextPoint(pointCoordinates[i])
        hexahedron.GetPointIds().SetId(i, i)

    # Add the hexahedron to a cell array.
    hexs = vtk.vtkCellArray()
    hexs.InsertNextCell(hexahedron)

    # Add the points and hexahedron to an unstructured grid.
    uGrid = vtk.vtkUnstructuredGrid()
    uGrid.SetPoints(points)
    uGrid.InsertNextCell(hexahedron.GetCellType(), hexahedron.GetPointIds())

    # Visualize.
    mapper = vtk.vtkDataSetMapper()
    mapper.SetInputData(uGrid)

    actor = vtk.vtkActor()
    actor.GetProperty().SetColor(colors.GetColor3d("Cornsilk"))
    actor.SetMapper(mapper)

    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("Hexahedron")
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("BkgColor"))
    renderer.ResetCamera()
    renderer.GetActiveCamera().Azimuth(30)
    renderer.GetActiveCamera().Elevation(30)

    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
