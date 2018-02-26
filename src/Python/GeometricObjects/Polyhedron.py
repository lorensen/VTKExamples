#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # create polyhedron (cube)
    # The point Ids are: [0, 1, 2, 3, 4, 5, 6, 7]

    points = vtk.vtkPoints()
    points.InsertNextPoint(-1.0, -1.0, -1.0)
    points.InsertNextPoint(1.0, -1.0, -1.0)
    points.InsertNextPoint(1.0, 1.0, -1.0)
    points.InsertNextPoint(-1.0, 1.0, -1.0)
    points.InsertNextPoint(-1.0, -1.0, 1.0)
    points.InsertNextPoint(1.0, -1.0, 1.0)
    points.InsertNextPoint(1.0, 1.0, 1.0)
    points.InsertNextPoint(-1.0, 1.0, 1.0)

    # These are the point ids corresponding to each face.
    faces = [[0, 3, 2, 1], [0, 4, 7, 3], [4, 5, 6, 7], [5, 1, 2, 6], [0, 1, 5, 4], [2, 3, 7, 6]]
    faceId = vtk.vtkIdList()
    faceId.InsertNextId(6)  # Six faces make up the cell.
    for face in faces:
        faceId.InsertNextId(len(face))  # The number of points in the face.
        [faceId.InsertNextId(i) for i in face]

    ugrid = vtk.vtkUnstructuredGrid()
    ugrid.SetPoints(points)
    ugrid.InsertNextCell(vtk.VTK_POLYHEDRON, faceId)

    # Here we write out the cube.
    writer = vtk.vtkXMLUnstructuredGridWriter()
    if vtk.VTK_MAJOR_VERSION <= 5:
        writer.SetInput(ugrid)
    else:
        writer.SetInputData(ugrid)
    writer.SetFileName("polyhedron.vtu")
    writer.SetDataModeToAscii()
    writer.Update()

    # Create a mapper and actor
    mapper = vtk.vtkDataSetMapper()
    if vtk.VTK_MAJOR_VERSION <= 5:
        mapper.SetInput(ugrid)
    else:
        mapper.SetInputData(ugrid)

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetColor(
        colors.GetColor3d("Silver"))

    # Visualize
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("Polyhedron")
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("Salmon"))
    renderer.ResetCamera()
    renderer.GetActiveCamera().Azimuth(30)
    renderer.GetActiveCamera().Elevation(30)
    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
