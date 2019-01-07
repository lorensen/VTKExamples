#!/usr/bin/python

import random

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Set the background color.
    colors.SetColor("BkgColor", [0.3, 0.6, 0.3, 1.0])

    points = vtk.vtkPoints()

    for x in range(10):
        for y in range(10):
            points.InsertNextPoint(x + random.uniform(-.25, .25),
                                   y + random.uniform(-.25, .25), 0)

    aPolyData = vtk.vtkPolyData()
    aPolyData.SetPoints(points)

    aCellArray = vtk.vtkCellArray()

    boundary = vtk.vtkPolyData()
    boundary.SetPoints(aPolyData.GetPoints())
    boundary.SetPolys(aCellArray)
    delaunay = vtk.vtkDelaunay2D()
    delaunay.SetInputData(aPolyData)
    delaunay.SetSourceData(boundary)

    delaunay.Update()

    meshMapper = vtk.vtkPolyDataMapper()
    meshMapper.SetInputConnection(delaunay.GetOutputPort())

    meshActor = vtk.vtkActor()
    meshActor.SetMapper(meshMapper)
    meshActor.GetProperty().SetEdgeColor(colors.GetColor3d("Blue"))
    meshActor.GetProperty().SetInterpolationToFlat()
    meshActor.GetProperty().SetRepresentationToWireframe()

    boundaryMapper = vtk.vtkPolyDataMapper()
    boundaryMapper.SetInputData(boundary)

    boundaryActor = vtk.vtkActor()
    boundaryActor.SetMapper(boundaryMapper)
    boundaryActor.GetProperty().SetColor(colors.GetColor3d("Red"))

    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)
    renderer.AddActor(meshActor)
    renderer.AddActor(boundaryActor)
    renderer.SetBackground(colors.GetColor3d("BkgColor"))

    renderWindowInteractor.Initialize()
    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == "__main__":
    main()
