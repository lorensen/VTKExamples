# !/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    titles = list()
    textMappers = list()
    textActors = list()

    uGrids = list()
    mappers = list()
    actors = list()
    renderers = list()

    uGrids.append(MakeVertex())
    titles.append("VTK_VERTEX (=1)")
    uGrids.append(MakePolyVertex())
    titles.append("VTK_POLY_VERTEX (=2)")
    uGrids.append(MakeLine())
    titles.append("VTK_LINE (=3)")
    uGrids.append(MakePolyLine())
    titles.append("VTK_POLY_LINE (=4)")
    uGrids.append(MakeTriangle())
    titles.append("VTK_TRIANGLE (=5)")
    uGrids.append(MakeTriangleStrip())
    titles.append("VTK_TRIANGLE_STRIP (=6)")
    uGrids.append(MakePolygon())
    titles.append("VTK_POLYGON (=7)")
    uGrids.append(MakePixel())
    titles.append("VTK_PIXEL (=8)")
    uGrids.append(MakeQuad())
    titles.append("VTK_QUAD (=9)")
    uGrids.append(MakeTetra())
    titles.append("VTK_TETRA (=10)")
    uGrids.append(MakeVoxel())
    titles.append("VTK_VOXEL (=11)")
    uGrids.append(MakeHexahedron())
    titles.append("VTK_HEXAHEDRON (=12)")
    uGrids.append(MakeWedge())
    titles.append("VTK_WEDGE (=13)")
    uGrids.append(MakePyramid())
    titles.append("VTK_PYRAMID (=14)")
    uGrids.append(MakePentagonalPrism())
    titles.append("VTK_PENTAGONAL_PRISM (=15)")
    uGrids.append(MakeHexagonalPrism())
    titles.append("VTK_HEXAGONAL_PRISM (=16)")

    colors = vtk.vtkNamedColors()

    renWin = vtk.vtkRenderWindow()
    renWin.SetSize(600, 600)
    renWin.SetWindowName("Linear Cell")

    iRen = vtk.vtkRenderWindowInteractor()
    iRen.SetRenderWindow(renWin)

    # Create one sphere for all
    sphere = vtk.vtkSphereSource()
    sphere.SetPhiResolution(21)
    sphere.SetThetaResolution(21)
    sphere.SetRadius(.08)

    # Create one text property for all
    textProperty = vtk.vtkTextProperty()
    textProperty.SetFontSize(10)
    textProperty.SetJustificationToCentered()

    # Create and link the mappers actors and renderers together.
    for i in range(0, len(uGrids)):
        print("Creating:", titles[i])
        textMappers.append(vtk.vtkTextMapper())
        textActors.append(vtk.vtkActor2D())

        mappers.append(vtk.vtkDataSetMapper())
        actors.append(vtk.vtkActor())
        renderers.append(vtk.vtkRenderer())
        mappers[i].SetInputData(uGrids[i])
        actors[i].SetMapper(mappers[i])
        actors[i].GetProperty().SetColor(colors.GetColor3d("Tomato"))
        actors[i].GetProperty().EdgeVisibilityOn()
        actors[i].GetProperty().SetLineWidth(3)
        actors[i].GetProperty().SetOpacity(.5)
        renderers[i].AddViewProp(actors[i])

        textMappers[i].SetInput(titles[i])
        textActors[i].SetMapper(textMappers[i])
        textActors[i].SetPosition(50, 10)
        renderers[i].AddViewProp(textActors[i])

        # Label the points
        labelMapper = vtk.vtkLabeledDataMapper()
        labelMapper.SetInputData(uGrids[i])
        labelActor = vtk.vtkActor2D()
        labelActor.SetMapper(labelMapper)
        renderers[i].AddViewProp(labelActor)

        # Glyph the points
        pointMapper = vtk.vtkGlyph3DMapper()
        pointMapper.SetInputData(uGrids[i])
        pointMapper.SetSourceConnection(sphere.GetOutputPort())
        pointMapper.ScalingOff()
        pointMapper.ScalarVisibilityOff()

        pointActor = vtk.vtkActor()
        pointActor.SetMapper(pointMapper)
        pointActor.GetProperty().SetDiffuseColor(colors.GetColor3d("Banana"))
        pointActor.GetProperty().SetSpecular(.6)
        pointActor.GetProperty().SetSpecularColor(1.0, 1.0, 1.0)
        pointActor.GetProperty().SetSpecularPower(100)
        renderers[i].AddViewProp(pointActor)

        renWin.AddRenderer(renderers[i])

    # Setup the viewports
    xGridDimensions = 4
    yGridDimensions = 4
    rendererSize = 240
    renWin.SetSize(rendererSize * xGridDimensions, rendererSize * yGridDimensions)
    for row in range(0, yGridDimensions):
        for col in range(0, xGridDimensions):
            index = row * xGridDimensions + col

            # (xmin, ymin, xmax, ymax)
            viewport = [float(col) / xGridDimensions,
                        float(yGridDimensions - (row + 1)) / yGridDimensions,
                        float(col + 1) / xGridDimensions,
                        float(yGridDimensions - row) / yGridDimensions]

            if index > (len(actors) - 1):
                # Add a renderer even if there is no actor.
                # This makes the render window background all the same color.
                ren = vtk.vtkRenderer()
                ren.SetBackground(colors.GetColor3d("SlateGray"))
                ren.SetViewport(viewport)
                renWin.AddRenderer(ren)
                continue

            renderers[index].SetViewport(viewport)
            renderers[index].SetBackground(colors.GetColor3d("SlateGray"))
            renderers[index].ResetCamera()
            renderers[index].GetActiveCamera().Azimuth(30)
            renderers[index].GetActiveCamera().Elevation(-30)
            if index == 0:
                renderers[index].GetActiveCamera().Dolly(.1)
            else:
                renderers[index].ResetCameraClippingRange()

    iRen.Initialize()
    renWin.Render()
    iRen.Start()


# These functions return a vtkUnstructured grid corresponding to the object.

def MakeVertex():
    # A vertex is a cell that represents a 3D point
    numberOfVertices = 1

    points = vtk.vtkPoints()
    points.InsertNextPoint(0, 0, 0)

    vertex = vtk.vtkVertex()
    for i in range(0, numberOfVertices):
        vertex.GetPointIds().SetId(i, i)

    ug = vtk.vtkUnstructuredGrid()
    ug.SetPoints(points)
    ug.InsertNextCell(vertex.GetCellType(), vertex.GetPointIds())

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


def MakeLine():
    # A line is a cell that represents a 1D point
    numberOfVertices = 2

    points = vtk.vtkPoints()
    points.InsertNextPoint(0, 0, 0)
    points.InsertNextPoint(.5, .5, 0)

    line = vtk.vtkLine()
    for i in range(0, numberOfVertices):
        line.GetPointIds().SetId(i, i)

    ug = vtk.vtkUnstructuredGrid()
    ug.SetPoints(points)
    ug.InsertNextCell(line.GetCellType(), line.GetPointIds())

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


def MakeTriangle():
    # A triangle is a cell that represents a 1D point
    numberOfVertices = 3

    points = vtk.vtkPoints()
    points.InsertNextPoint(0, 0, 0)
    points.InsertNextPoint(.5, .5, 0)
    points.InsertNextPoint(.2, 1, 0)

    triangle = vtk.vtkTriangle()
    for i in range(0, numberOfVertices):
        triangle.GetPointIds().SetId(i, i)

    ug = vtk.vtkUnstructuredGrid()
    ug.SetPoints(points)
    ug.InsertNextCell(triangle.GetCellType(), triangle.GetPointIds())

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


def MakePixel():
    # A pixel is a cell that represents a pixel
    pixel = vtk.vtkPixel()
    pixel.GetPoints().SetPoint(0, 0, 0, 0)
    pixel.GetPoints().SetPoint(1, 1, 0, 0)
    pixel.GetPoints().SetPoint(2, 0, 1, 0)
    pixel.GetPoints().SetPoint(3, 1, 1, 0)

    pixel.GetPointIds().SetId(0, 0)
    pixel.GetPointIds().SetId(1, 1)
    pixel.GetPointIds().SetId(2, 2)
    pixel.GetPointIds().SetId(3, 3)

    ug = vtk.vtkUnstructuredGrid()
    ug.SetPoints(pixel.GetPoints())
    ug.InsertNextCell(pixel.GetCellType(), pixel.GetPointIds())

    return ug


def MakeQuad():
    # A quad is a cell that represents a quad
    quad = vtk.vtkQuad()
    quad.GetPoints().SetPoint(0, 0, 0, 0)
    quad.GetPoints().SetPoint(1, 1, 0, 0)
    quad.GetPoints().SetPoint(2, 1, 1, 0)
    quad.GetPoints().SetPoint(3, 0, 1, 0)

    quad.GetPointIds().SetId(0, 0)
    quad.GetPointIds().SetId(1, 1)
    quad.GetPointIds().SetId(2, 2)
    quad.GetPointIds().SetId(3, 3)

    ug = vtk.vtkUnstructuredGrid()
    ug.SetPoints(quad.GetPoints())
    ug.InsertNextCell(quad.GetCellType(), quad.GetPointIds())

    return ug


def MakeTetra():
    # Make a tetrahedron.
    numberOfVertices = 4

    points = vtk.vtkPoints()
    points.InsertNextPoint(0, 0, 0)
    points.InsertNextPoint(1, 0, 0)
    points.InsertNextPoint(1, 1, 0)
    points.InsertNextPoint(0, 1, 1)

    tetra = vtk.vtkTetra()
    for i in range(0, numberOfVertices):
        tetra.GetPointIds().SetId(i, i)

    cellArray = vtk.vtkCellArray()
    cellArray.InsertNextCell(tetra)

    unstructuredGrid = vtk.vtkUnstructuredGrid()
    unstructuredGrid.SetPoints(points)
    unstructuredGrid.SetCells(vtk.VTK_TETRA, cellArray)

    return unstructuredGrid


def MakeVoxel():
    # A voxel is a representation of a regular grid in 3-D space.
    numberOfVertices = 8

    points = vtk.vtkPoints()
    points.InsertNextPoint(0, 0, 0)
    points.InsertNextPoint(1, 0, 0)
    points.InsertNextPoint(0, 1, 0)
    points.InsertNextPoint(1, 1, 0)
    points.InsertNextPoint(0, 0, 1)
    points.InsertNextPoint(1, 0, 1)
    points.InsertNextPoint(0, 1, 1)
    points.InsertNextPoint(1, 1, 1)

    voxel = vtk.vtkVoxel()
    for i in range(0, numberOfVertices):
        voxel.GetPointIds().SetId(i, i)

    ug = vtk.vtkUnstructuredGrid()
    ug.SetPoints(points)
    ug.InsertNextCell(voxel.GetCellType(), voxel.GetPointIds())

    return ug


def MakeHexahedron():
    # A regular hexagon (cube) with all faces square and three squares around
    # each vertex is created below.

    # Setup the coordinates of eight points
    # (the two faces must be in counter clockwise
    # order as viewed from the outside).

    numberOfVertices = 8

    # Create the points
    points = vtk.vtkPoints()
    points.InsertNextPoint(0.0, 0.0, 0.0)
    points.InsertNextPoint(1.0, 0.0, 0.0)
    points.InsertNextPoint(1.0, 1.0, 0.0)
    points.InsertNextPoint(0.0, 1.0, 0.0)
    points.InsertNextPoint(0.0, 0.0, 1.0)
    points.InsertNextPoint(1.0, 0.0, 1.0)
    points.InsertNextPoint(1.0, 1.0, 1.0)
    points.InsertNextPoint(0.0, 1.0, 1.0)

    # Create a hexahedron from the points
    hexhedr = vtk.vtkHexahedron()
    for i in range(0, numberOfVertices):
        hexhedr.GetPointIds().SetId(i, i)

    # Add the points and hexahedron to an unstructured grid
    uGrid = vtk.vtkUnstructuredGrid()
    uGrid.SetPoints(points)
    uGrid.InsertNextCell(hexhedr.GetCellType(), hexhedr.GetPointIds())

    return uGrid


def MakeWedge():
    # A wedge consists of two triangular ends and three rectangular faces.

    numberOfVertices = 6

    points = vtk.vtkPoints()

    points.InsertNextPoint(0, 1, 0)
    points.InsertNextPoint(0, 0, 0)
    points.InsertNextPoint(0, .5, .5)
    points.InsertNextPoint(1, 1, 0)
    points.InsertNextPoint(1, 0.0, 0.0)
    points.InsertNextPoint(1, .5, .5)

    wedge = vtk.vtkWedge()
    for i in range(0, numberOfVertices):
        wedge.GetPointIds().SetId(i, i)

    ug = vtk.vtkUnstructuredGrid()
    ug.SetPoints(points)
    ug.InsertNextCell(wedge.GetCellType(), wedge.GetPointIds())

    return ug


def MakePyramid():
    # Make a regular square pyramid.
    numberOfVertices = 5

    points = vtk.vtkPoints()

    p0 = [1.0, 1.0, 0.0]
    p1 = [-1.0, 1.0, 0.0]
    p2 = [-1.0, -1.0, 0.0]
    p3 = [1.0, -1.0, 0.0]
    p4 = [0.0, 0.0, 1.0]

    points.InsertNextPoint(p0)
    points.InsertNextPoint(p1)
    points.InsertNextPoint(p2)
    points.InsertNextPoint(p3)
    points.InsertNextPoint(p4)

    pyramid = vtk.vtkPyramid()
    for i in range(0, numberOfVertices):
        pyramid.GetPointIds().SetId(i, i)

    ug = vtk.vtkUnstructuredGrid()
    ug.SetPoints(points)
    ug.InsertNextCell(pyramid.GetCellType(), pyramid.GetPointIds())

    return ug


def MakePentagonalPrism():
    pentagonalPrism = vtk.vtkPentagonalPrism()

    pentagonalPrism.GetPointIds().SetId(0, 0)
    pentagonalPrism.GetPointIds().SetId(1, 1)
    pentagonalPrism.GetPointIds().SetId(2, 2)
    pentagonalPrism.GetPointIds().SetId(3, 3)
    pentagonalPrism.GetPointIds().SetId(4, 4)
    pentagonalPrism.GetPointIds().SetId(5, 5)
    pentagonalPrism.GetPointIds().SetId(6, 6)
    pentagonalPrism.GetPointIds().SetId(7, 7)
    pentagonalPrism.GetPointIds().SetId(8, 8)
    pentagonalPrism.GetPointIds().SetId(9, 9)

    scale = 2.0
    pentagonalPrism.GetPoints().SetPoint(0, 11 / scale, 10 / scale, 10 / scale)
    pentagonalPrism.GetPoints().SetPoint(1, 13 / scale, 10 / scale, 10 / scale)
    pentagonalPrism.GetPoints().SetPoint(2, 14 / scale, 12 / scale, 10 / scale)
    pentagonalPrism.GetPoints().SetPoint(3, 12 / scale, 14 / scale, 10 / scale)
    pentagonalPrism.GetPoints().SetPoint(4, 10 / scale, 12 / scale, 10 / scale)
    pentagonalPrism.GetPoints().SetPoint(5, 11 / scale, 10 / scale, 14 / scale)
    pentagonalPrism.GetPoints().SetPoint(6, 13 / scale, 10 / scale, 14 / scale)
    pentagonalPrism.GetPoints().SetPoint(7, 14 / scale, 12 / scale, 14 / scale)
    pentagonalPrism.GetPoints().SetPoint(8, 12 / scale, 14 / scale, 14 / scale)
    pentagonalPrism.GetPoints().SetPoint(9, 10 / scale, 12 / scale, 14 / scale)

    ug = vtk.vtkUnstructuredGrid()
    ug.SetPoints(pentagonalPrism.GetPoints())
    ug.InsertNextCell(pentagonalPrism.GetCellType(), pentagonalPrism.GetPointIds())

    return ug


def MakeHexagonalPrism():
    hexagonalPrism = vtk.vtkHexagonalPrism()
    hexagonalPrism.GetPointIds().SetId(0, 0)
    hexagonalPrism.GetPointIds().SetId(1, 1)
    hexagonalPrism.GetPointIds().SetId(2, 2)
    hexagonalPrism.GetPointIds().SetId(3, 3)
    hexagonalPrism.GetPointIds().SetId(4, 4)
    hexagonalPrism.GetPointIds().SetId(5, 5)
    hexagonalPrism.GetPointIds().SetId(6, 6)
    hexagonalPrism.GetPointIds().SetId(7, 7)
    hexagonalPrism.GetPointIds().SetId(8, 8)
    hexagonalPrism.GetPointIds().SetId(9, 9)
    hexagonalPrism.GetPointIds().SetId(10, 10)
    hexagonalPrism.GetPointIds().SetId(11, 11)

    scale = 2.0
    hexagonalPrism.GetPoints().SetPoint(0, 11 / scale, 10 / scale, 10 / scale)
    hexagonalPrism.GetPoints().SetPoint(1, 13 / scale, 10 / scale, 10 / scale)
    hexagonalPrism.GetPoints().SetPoint(2, 14 / scale, 12 / scale, 10 / scale)
    hexagonalPrism.GetPoints().SetPoint(3, 13 / scale, 14 / scale, 10 / scale)
    hexagonalPrism.GetPoints().SetPoint(4, 11 / scale, 14 / scale, 10 / scale)
    hexagonalPrism.GetPoints().SetPoint(5, 10 / scale, 12 / scale, 10 / scale)
    hexagonalPrism.GetPoints().SetPoint(6, 11 / scale, 10 / scale, 14 / scale)
    hexagonalPrism.GetPoints().SetPoint(7, 13 / scale, 10 / scale, 14 / scale)
    hexagonalPrism.GetPoints().SetPoint(8, 14 / scale, 12 / scale, 14 / scale)
    hexagonalPrism.GetPoints().SetPoint(9, 13 / scale, 14 / scale, 14 / scale)
    hexagonalPrism.GetPoints().SetPoint(10, 11 / scale, 14 / scale, 14 / scale)
    hexagonalPrism.GetPoints().SetPoint(11, 10 / scale, 12 / scale, 14 / scale)

    ug = vtk.vtkUnstructuredGrid()
    ug.SetPoints(hexagonalPrism.GetPoints())
    ug.InsertNextCell(hexagonalPrism.GetCellType(), hexagonalPrism.GetPointIds())

    return ug


if __name__ == '__main__':
    main()
