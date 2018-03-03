#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    namedColors = vtk.vtkNamedColors()

    uGrid = MakeQuadraticHexahedron()

    tessellate = vtk.vtkTessellatorFilter()
    tessellate.SetInputData(uGrid)
    tessellate.SetMaximumNumberOfSubdivisions(2)

    mapper = vtk.vtkDataSetMapper()
    mapper.SetInputConnection(tessellate.GetOutputPort())
    mapper.ScalarVisibilityOff()

    # Create an actor for the grid
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetDiffuseColor(
        namedColors.GetColor3d("Tomato"))
    actor.GetProperty().SetEdgeColor(
        namedColors.GetColor3d("IvoryBlack"))
    actor.GetProperty().EdgeVisibilityOn()

    sphereSource = vtk.vtkSphereSource()
    sphereSource.SetRadius(0.02)

    glyph3D = vtk.vtkGlyph3D()
    glyph3D.SetInputData(uGrid)
    glyph3D.SetSourceConnection(sphereSource.GetOutputPort())
    glyph3D.ScalingOff()
    glyph3D.Update()

    glyph3DMapper = vtk.vtkDataSetMapper()
    glyph3DMapper.SetInputConnection(glyph3D.GetOutputPort())
    glyph3DMapper.ScalarVisibilityOff()

    glyph3DActor = vtk.vtkActor()
    glyph3DActor.SetMapper(glyph3DMapper)
    glyph3DActor.GetProperty().SetColor(
        namedColors.GetColor3d("Banana"))

    # Visualize
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("Quadratic Hexahedron")
    renderWindow.AddRenderer(renderer)
    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderWindow)

    renderer.AddActor(actor)
    renderer.AddActor(glyph3DActor)
    renderer.SetBackground(namedColors.GetColor3d("SlateGray"))

    renderWindow.Render()
    interactor.Start()


def MakeQuadraticHexahedron():
    aHexahedron = vtk.vtkQuadraticHexahedron()
    points = vtk.vtkPoints()

    pcoords = aHexahedron.GetParametricCoords()
    rng = vtk.vtkMinimalStandardRandomSequence()
    points.SetNumberOfPoints(aHexahedron.GetNumberOfPoints())
    rng.SetSeed(5070)  # for testing
    for i in range(0, aHexahedron.GetNumberOfPoints()):
        perturbation = [0.0] * 3
        for j in range(0, 3):
            rng.Next()
            perturbation[j] = rng.GetRangeValue(-0.1, 0.1)
        aHexahedron.GetPointIds().SetId(i, i)
        points.SetPoint(i, pcoords[3 * i] + perturbation[0],
                        pcoords[3 * i + 1] + perturbation[1],
                        pcoords[3 * i + 2] + perturbation[2])

    # Add the points and hexahedron to an unstructured grid
    uGrid = vtk.vtkUnstructuredGrid()
    uGrid.SetPoints(points)
    uGrid.InsertNextCell(aHexahedron.GetCellType(), aHexahedron.GetPointIds())

    return uGrid


if __name__ == '__main__':
    main()
