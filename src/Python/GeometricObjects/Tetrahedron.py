#!/usr/bin/env python

import vtk


def main():
    colors = vtk.vtkNamedColors()

    points = vtk.vtkPoints()
    points.InsertNextPoint(0, 0, 0)
    points.InsertNextPoint(1, 0, 0)
    points.InsertNextPoint(1, 1, 0)
    points.InsertNextPoint(0, 1, 1)
    points.InsertNextPoint(5, 5, 5)
    points.InsertNextPoint(6, 5, 5)
    points.InsertNextPoint(6, 6, 5)
    points.InsertNextPoint(5, 6, 6)

    # The first tetrahedron
    unstructuredGrid1 = vtk.vtkUnstructuredGrid()
    unstructuredGrid1.SetPoints(points)

    tetra = vtk.vtkTetra()

    tetra.GetPointIds().SetId(0, 0)
    tetra.GetPointIds().SetId(1, 1)
    tetra.GetPointIds().SetId(2, 2)
    tetra.GetPointIds().SetId(3, 3)

    cellArray = vtk.vtkCellArray()
    cellArray.InsertNextCell(tetra)
    unstructuredGrid1.SetCells(vtk.VTK_TETRA, cellArray)

    # The second tetrahedron
    unstructuredGrid2 = vtk.vtkUnstructuredGrid()
    unstructuredGrid2.SetPoints(points)

    tetra = vtk.vtkTetra()

    tetra.GetPointIds().SetId(0, 4)
    tetra.GetPointIds().SetId(1, 5)
    tetra.GetPointIds().SetId(2, 6)
    tetra.GetPointIds().SetId(3, 7)

    cellArray = vtk.vtkCellArray()
    cellArray.InsertNextCell(tetra)
    unstructuredGrid2.SetCells(vtk.VTK_TETRA, cellArray)

    # Create a mapper and actor
    mapper1 = vtk.vtkDataSetMapper()
    if vtk.VTK_MAJOR_VERSION <= 5:
        mapper1.SetInputConnection(unstructuredGrid1.GetProducerPort())
    else:
        mapper1.SetInputData(unstructuredGrid1)

    actor1 = vtk.vtkActor()
    actor1.SetMapper(mapper1)
    actor1.GetProperty().SetColor(colors.GetColor3d("Cyan"))

    # Create a mapper and actor
    mapper2 = vtk.vtkDataSetMapper()
    if vtk.VTK_MAJOR_VERSION <= 5:
        mapper2.SetInputConnection(unstructuredGrid2.GetProducerPort())
    else:
        mapper2.SetInputData(unstructuredGrid2)

    actor2 = vtk.vtkActor()
    actor2.SetMapper(mapper2)
    actor2.GetProperty().SetColor(colors.GetColor3d("Yellow"))

    # Create a renderer, render window, and interactor
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("Tetrahedron")
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    # Add the actor to the scene
    renderer.AddActor(actor1)
    renderer.AddActor(actor2)
    renderer.SetBackground(colors.GetColor3d("DarkGreen"))
    renderer.ResetCamera()
    renderer.GetActiveCamera().Azimuth(-10)
    renderer.GetActiveCamera().Elevation(-20)


    # Render and interact
    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
