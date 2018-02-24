#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    colors = vtk.vtkNamedColors()

    dodecahedron = MakeDodecahedron()

    # Visualize
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputData(dodecahedron.GetPolyData())

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetColor(
        colors.GetColor3d("PapayaWhip"))

    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("Dodecahedron")
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("CadetBlue"))
    renderer.GetActiveCamera().Azimuth(30)
    renderer.GetActiveCamera().Elevation(30)

    renderer.ResetCamera()

    renderWindow.Render()
    renderWindowInteractor.Start()


def MakeDodecahedron():
    aDodecahedron = vtk.vtkPolyhedron()

    for i in range(0, 20):
        aDodecahedron.GetPointIds().InsertNextId(i)

    aDodecahedron.GetPoints().InsertNextPoint(1.21412, 0, 1.58931)
    aDodecahedron.GetPoints().InsertNextPoint(0.375185, 1.1547, 1.58931)
    aDodecahedron.GetPoints().InsertNextPoint(-0.982247, 0.713644, 1.58931)
    aDodecahedron.GetPoints().InsertNextPoint(-0.982247, -0.713644, 1.58931)
    aDodecahedron.GetPoints().InsertNextPoint(0.375185, -1.1547, 1.58931)
    aDodecahedron.GetPoints().InsertNextPoint(1.96449, 0, 0.375185)
    aDodecahedron.GetPoints().InsertNextPoint(0.607062, 1.86835, 0.375185)
    aDodecahedron.GetPoints().InsertNextPoint(-1.58931, 1.1547, 0.375185)
    aDodecahedron.GetPoints().InsertNextPoint(-1.58931, -1.1547, 0.375185)
    aDodecahedron.GetPoints().InsertNextPoint(0.607062, -1.86835, 0.375185)
    aDodecahedron.GetPoints().InsertNextPoint(1.58931, 1.1547, -0.375185)
    aDodecahedron.GetPoints().InsertNextPoint(-0.607062, 1.86835, -0.375185)
    aDodecahedron.GetPoints().InsertNextPoint(-1.96449, 0, -0.375185)
    aDodecahedron.GetPoints().InsertNextPoint(-0.607062, -1.86835, -0.375185)
    aDodecahedron.GetPoints().InsertNextPoint(1.58931, -1.1547, -0.375185)
    aDodecahedron.GetPoints().InsertNextPoint(0.982247, 0.713644, -1.58931)
    aDodecahedron.GetPoints().InsertNextPoint(-0.375185, 1.1547, -1.58931)
    aDodecahedron.GetPoints().InsertNextPoint(-1.21412, 0, -1.58931)
    aDodecahedron.GetPoints().InsertNextPoint(-0.375185, -1.1547, -1.58931)
    aDodecahedron.GetPoints().InsertNextPoint(0.982247, -0.713644, -1.58931)

    faces = [12,  # number of faces
             5, 0, 1, 2, 3, 4,  # number of ids on face, ids
             5, 0, 5, 10, 6, 1,
             5, 1, 6, 11, 7, 2,
             5, 2, 7, 12, 8, 3,
             5, 3, 8, 13, 9, 4,
             5, 4, 9, 14, 5, 0,
             5, 15, 10, 5, 14, 19,
             5, 16, 11, 6, 10, 15,
             5, 17, 12, 7, 11, 16,
             5, 18, 13, 8, 12, 17,
             5, 19, 14, 9, 13, 18,
             5, 19, 18, 17, 16, 15]

    aDodecahedron.SetFaces(faces)
    aDodecahedron.Initialize()

    return aDodecahedron


if __name__ == '__main__':
    main()
