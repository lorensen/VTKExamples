#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Setup the coordinates of eight points
    # (the two faces must be in counter clockwise order as viewed from the
    # outside)
    pointCoords = [
        [0.0, 0.0, 0.0],
        [1.0, 0.0, 0.0],
        [1.0, 1.0, 0.0],
        [0.0, 1.0, 0.0],
        [0.0, 0.0, 1.0],
        [1.0, 0.0, 1.0],
        [1.0, 1.0, 1.0],
        [0.0, 1.0, 1.0]
    ]

    # Create the points and a hexahedron from the points.
    points = vtk.vtkPoints()
    hexa = vtk.vtkHexahedron()
    for i, pointCoord in enumerate(pointCoords):
        points.InsertNextPoint(pointCoord)
        hexa.GetPointIds().SetId(i, i)

    # Add the hexahedron to a cell array.
    hexs = vtk.vtkCellArray()
    hexs.InsertNextCell(hexa)

    # Add the points and hexahedron to an unstructured grid.
    uGrid = vtk.vtkUnstructuredGrid()
    uGrid.SetPoints(points)
    uGrid.InsertNextCell(hexa.GetCellType(), hexa.GetPointIds())

    # Extract the outer (polygonal) surface.
    surface = vtk.vtkDataSetSurfaceFilter()
    surface.SetInputData(uGrid)
    surface.Update()

    aBeamMapper = vtk.vtkDataSetMapper()
    aBeamMapper.SetInputConnection(surface.GetOutputPort())
    aBeamActor = vtk.vtkActor()
    aBeamActor.SetMapper(aBeamMapper)
    aBeamActor.AddPosition(0, 0, 0)
    aBeamActor.GetProperty().SetColor(
        colors.GetColor3d("Yellow"))
    aBeamActor.GetProperty().SetOpacity(0.60)
    aBeamActor.GetProperty().EdgeVisibilityOn()
    aBeamActor.GetProperty().SetEdgeColor(
        colors.GetColor3d("Black"))
    aBeamActor.GetProperty().SetLineWidth(1.5)

    # Create a plane to cut, here it cuts in the XZ direction
    # (xz normal=(1,0,0) XY =(0,0,1), YZ =(0,1,0)
    plane = vtk.vtkPlane()
    plane.SetOrigin(0.5, 0, 0)
    plane.SetNormal(1, 0, 0)

    # Create cutter
    cutter = vtk.vtkCutter()
    cutter.SetCutFunction(plane)
    cutter.SetInputData(aBeamActor.GetMapper().GetInput())
    cutter.Update()
    cutterMapper = vtk.vtkPolyDataMapper()
    cutterMapper.SetInputConnection(cutter.GetOutputPort())

    # Create plane actor
    planeActor = vtk.vtkActor()
    planeActor.GetProperty().SetColor(
        colors.GetColor3d("Red"))
    planeActor.GetProperty().SetLineWidth(2)
    planeActor.SetMapper(cutterMapper)

    # Create a renderer, render window, and interactor
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("Dataset Surface")
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    # Add the actors to the scene
    renderer.AddActor(aBeamActor)
    renderer.AddActor(planeActor)
    renderer.SetBackground(
        colors.GetColor3d("Seashell"))

    renderer.ResetCamera()
    renderer.GetActiveCamera().Azimuth(30)
    renderer.GetActiveCamera().Elevation(30)

    # Render and interact
    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
