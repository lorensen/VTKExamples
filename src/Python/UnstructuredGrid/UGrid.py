#!/usr/bin/env python

"""
This example shows how to create an unstructured grid.
"""

import vtk


def main():
    colors = vtk.vtkNamedColors()

    x = [[0, 0, 0], [1, 0, 0], [2, 0, 0], [0, 1, 0], [1, 1, 0], [2, 1, 0], [0, 0, 1], [1, 0, 1], [2, 0, 1], [0, 1, 1],
         [1, 1, 1], [2, 1, 1], [0, 1, 2], [1, 1, 2], [2, 1, 2], [0, 1, 3], [1, 1, 3], [2, 1, 3], [0, 1, 4], [1, 1, 4],
         [2, 1, 4], [0, 1, 5], [1, 1, 5], [2, 1, 5], [0, 1, 6], [1, 1, 6], [2, 1, 6]]
    pts = [[0, 1, 4, 3, 6, 7, 10, 9], [1, 2, 5, 4, 7, 8, 11, 10], [6, 10, 9, 12, 0, 0, 0, 0],
           [8, 11, 10, 14, 0, 0, 0, 0], [16, 17, 14, 13, 12, 15, 0, 0], [18, 15, 19, 16, 20, 17, 0, 0],
           [22, 23, 20, 19, 0, 0, 0, 0], [21, 22, 18, 0, 0, 0, 0, 0], [22, 19, 18, 0, 0, 0, 0, 0],
           [23, 26, 0, 0, 0, 0, 0, 0], [21, 24, 0, 0, 0, 0, 0, 0], [25, 0, 0, 0, 0, 0, 0, 0]]
    print(len(x), len(pts))

    renderer = vtk.vtkRenderer()

    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(renderer)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    points = vtk.vtkPoints()
    for i in range(0, len(x)):
        points.InsertPoint(i, x[i])

    ugrid = vtk.vtkUnstructuredGrid()
    ugrid.Allocate(100)
    ugrid.InsertNextCell(vtk.VTK_HEXAHEDRON, 8, pts[0])
    ugrid.InsertNextCell(vtk.VTK_HEXAHEDRON, 8, pts[1])
    ugrid.InsertNextCell(vtk.VTK_TETRA, 4, pts[2])
    ugrid.InsertNextCell(vtk.VTK_TETRA, 4, pts[3])
    ugrid.InsertNextCell(vtk.VTK_POLYGON, 6, pts[4])
    ugrid.InsertNextCell(vtk.VTK_TRIANGLE_STRIP, 6, pts[5])
    ugrid.InsertNextCell(vtk.VTK_QUAD, 4, pts[6])
    ugrid.InsertNextCell(vtk.VTK_TRIANGLE, 3, pts[7])
    ugrid.InsertNextCell(vtk.VTK_TRIANGLE, 3, pts[8])
    ugrid.InsertNextCell(vtk.VTK_LINE, 2, pts[9])
    ugrid.InsertNextCell(vtk.VTK_LINE, 2, pts[10])
    ugrid.InsertNextCell(vtk.VTK_VERTEX, 1, pts[11])

    ugrid.SetPoints(points)

    ugridMapper = vtk.vtkDataSetMapper()
    ugridMapper.SetInputData(ugrid)

    ugridActor = vtk.vtkActor()
    ugridActor.SetMapper(ugridMapper)
    ugridActor.GetProperty().SetColor(colors.GetColor3d("Peacock"))
    ugridActor.GetProperty().EdgeVisibilityOn()

    renderer.AddActor(ugridActor)
    renderer.SetBackground(colors.GetColor3d("Beige"))

    renderer.ResetCamera()
    renderer.GetActiveCamera().Elevation(60.0)
    renderer.GetActiveCamera().Azimuth(30.0)
    renderer.GetActiveCamera().Dolly(1.2)

    renWin.SetSize(640, 480)

    # Interact with the data.
    renWin.Render()

    iren.Start()


if __name__ == "__main__":
    main()
