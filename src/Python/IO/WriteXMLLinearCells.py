#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    filenames = list()
    uGrids = list()

    uGrids.append(MakeUnstructuredGrid(vtk.vtkVertex()))
    filenames.append("Vertex.vtu")

    uGrids.append(MakePolyVertex())
    filenames.append("PolyVertex.vtu")

    uGrids.append(MakeUnstructuredGrid(vtk.vtkLine()))
    filenames.append("Line.vtu")

    uGrids.append(MakePolyLine())
    filenames.append("PolyLine.vtu")

    uGrids.append(MakeUnstructuredGrid(vtk.vtkTriangle()))
    filenames.append("Triangle.vtu")

    uGrids.append(MakeTriangleStrip())
    filenames.append("TriangleStrip.vtu")

    uGrids.append(MakePolygon())
    filenames.append("Polygon.vtu")

    uGrids.append(MakeUnstructuredGrid(vtk.vtkPixel()))
    filenames.append("Pixel.vtu")

    uGrids.append(MakeUnstructuredGrid(vtk.vtkQuad()))
    filenames.append("Quad.vtu")

    uGrids.append(MakeUnstructuredGrid(vtk.vtkTetra()))
    filenames.append("Tetra.vtu")

    uGrids.append(MakeUnstructuredGrid(vtk.vtkVoxel()))
    filenames.append("Voxel.vtu")

    uGrids.append(MakeUnstructuredGrid(vtk.vtkHexahedron()))
    filenames.append("Hexahedron.vtu")

    uGrids.append(MakeUnstructuredGrid(vtk.vtkWedge()))
    filenames.append("Wedge.vtu")

    uGrids.append(MakeUnstructuredGrid(vtk.vtkPyramid()))
    filenames.append("Pyramid.vtu")

    uGrids.append(MakeUnstructuredGrid(vtk.vtkPentagonalPrism()))
    filenames.append("PentagonalPrism.vtu")

    uGrids.append(MakeUnstructuredGrid(vtk.vtkHexagonalPrism()))
    filenames.append("HexagonalPrism.vtu")

    # Write each grid into  a file
    for i in range(0, len(uGrids)):
        print("Writing: ", filenames[i])
        writer = vtk.vtkXMLDataSetWriter()
        writer.SetFileName(filenames[i])
        writer.SetInputData(uGrids[i])
        writer.Write()


def MakeUnstructuredGrid(aCell):
    pcoords = aCell.GetParametricCoords()
    for i in range(0, aCell.GetNumberOfPoints()):
        aCell.GetPointIds().SetId(i, i)
        aCell.GetPoints().SetPoint(i, (pcoords[3 * i]), (pcoords[3 * i + 1]), (pcoords[3 * i + 2]))

    ug = vtk.vtkUnstructuredGrid()
    ug.SetPoints(aCell.GetPoints())
    ug.InsertNextCell(aCell.GetCellType(), aCell.GetPointIds())
    return ug


def MakePolyVertex():
    # A polyvertex is a cell represents a set of 0D vertices
    numberOfVertices = 6

    points = vtk.vtkPoints()
    points.InsertNextPoint(0, 0, 0)
    points.InsertNextPoint(1, 0, 0)
    points.InsertNextPoint(0, 1, 0)
    points.InsertNextPoint(0, 0, 1)
    points.InsertNextPoint(1, 0, .4)
    points.InsertNextPoint(0, 1, .6)

    polyVertex = vtk.vtkPolyVertex()
    polyVertex.GetPointIds().SetNumberOfIds(numberOfVertices)

    for i in range(0, numberOfVertices):
        polyVertex.GetPointIds().SetId(i, i)

    ug = vtk.vtkUnstructuredGrid()
    ug.SetPoints(points)
    ug.InsertNextCell(polyVertex.GetCellType(), polyVertex.GetPointIds())

    return ug


def MakePolyLine():
    # A polyline is a cell that represents a set of 1D lines
    numberOfVertices = 5

    points = vtk.vtkPoints()
    points.InsertNextPoint(0, .5, 0)
    points.InsertNextPoint(.5, 0, 0)
    points.InsertNextPoint(1, .3, 0)
    points.InsertNextPoint(1.5, .4, 0)
    points.InsertNextPoint(2.0, .4, 0)

    polyline = vtk.vtkPolyLine()
    polyline.GetPointIds().SetNumberOfIds(numberOfVertices)

    for i in range(0, numberOfVertices):
        polyline.GetPointIds().SetId(i, i)

    ug = vtk.vtkUnstructuredGrid()
    ug.SetPoints(points)
    ug.InsertNextCell(polyline.GetCellType(), polyline.GetPointIds())

    return ug


def MakeTriangleStrip():
    # A triangle is a cell that represents a triangle strip
    numberOfVertices = 10

    points = vtk.vtkPoints()
    points.InsertNextPoint(0, 0, 0)
    points.InsertNextPoint(.5, 1, 0)
    points.InsertNextPoint(1, -.1, 0)
    points.InsertNextPoint(1.5, .8, 0)
    points.InsertNextPoint(2.0, -.1, 0)
    points.InsertNextPoint(2.5, .9, 0)
    points.InsertNextPoint(3.0, 0, 0)
    points.InsertNextPoint(3.5, .8, 0)
    points.InsertNextPoint(4.0, -.2, 0)
    points.InsertNextPoint(4.5, 1.1, 0)

    trianglestrip = vtk.vtkTriangleStrip()
    trianglestrip.GetPointIds().SetNumberOfIds(numberOfVertices)
    for i in range(0, numberOfVertices):
        trianglestrip.GetPointIds().SetId(i, i)

    ug = vtk.vtkUnstructuredGrid()
    ug.SetPoints(points)
    ug.InsertNextCell(trianglestrip.GetCellType(), trianglestrip.GetPointIds())

    return ug


def MakePolygon():
    # A polygon is a cell that represents a polygon
    numberOfVertices = 6

    points = vtk.vtkPoints()
    points.InsertNextPoint(0, 0, 0)
    points.InsertNextPoint(1, -.1, 0)
    points.InsertNextPoint(.8, .5, 0)
    points.InsertNextPoint(1, 1, 0)
    points.InsertNextPoint(.6, 1.2, 0)
    points.InsertNextPoint(0, .8, 0)

    polygon = vtk.vtkPolygon()
    polygon.GetPointIds().SetNumberOfIds(numberOfVertices)
    for i in range(0, numberOfVertices):
        polygon.GetPointIds().SetId(i, i)

    ug = vtk.vtkUnstructuredGrid()
    ug.SetPoints(points)
    ug.InsertNextCell(polygon.GetCellType(), polygon.GetPointIds())

    return ug


if __name__ == '__main__':
    main()
