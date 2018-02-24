#!/usr/bin/env python
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

    uGrids.append(MakeUnstructuredGrid(
        vtk.vtkQuadraticEdge()))
    titles.append("VTK_QUADRATIC_EDGE (= 21)")

    uGrids.append(MakeUnstructuredGrid(
        vtk.vtkQuadraticTriangle()))
    titles.append("VTK_QUADRATIC_TRIANGLE (= 22)")

    uGrids.append(MakeUnstructuredGrid(
        vtk.vtkQuadraticQuad()))
    titles.append("VTK_QUADRATIC_QUAD (= 23)")

    uGrids.append(MakeQuadraticPolygon())
    titles.append("VTK_QUADRATIC_POLYGON (= 36)")

    uGrids.append(MakeUnstructuredGrid(
        vtk.vtkQuadraticTetra()))
    titles.append("VTK_QUADRATIC_TETRA (= 24)")

    uGrids.append(MakeUnstructuredGrid(
        vtk.vtkQuadraticHexahedron()))
    titles.append("VTK_QUADRATIC_HEXAHEDRON (= 25)")

    uGrids.append(MakeUnstructuredGrid(
        vtk.vtkQuadraticWedge()))
    titles.append("VTK_QUADRATIC_WEDGE (= 26)")

    uGrids.append(MakeUnstructuredGrid(
        vtk.vtkQuadraticPyramid()))
    titles.append("VTK_QUADRATIC_PYRAMID (= 27)")

    uGrids.append(MakeUnstructuredGrid(
        vtk.vtkBiQuadraticQuad()))
    titles.append("VTK_BIQUADRATIC_QUAD (= 28)")

    uGrids.append(MakeUnstructuredGrid(
        vtk.vtkTriQuadraticHexahedron()))
    titles.append("VTK_TRIQUADRATIC_HEXAHEDRON (= 29)")

    uGrids.append(MakeUnstructuredGrid(
        vtk.vtkQuadraticLinearQuad()))
    titles.append("VTK_QUADRATIC_LINEAR_QUAD (= 30)")

    uGrids.append(MakeUnstructuredGrid(
        vtk.vtkQuadraticLinearWedge()))
    titles.append("VTK_QUADRATIC_LINEAR_WEDGE (= 31)")

    uGrids.append(MakeUnstructuredGrid(
        vtk.vtkBiQuadraticQuadraticWedge()))
    titles.append("VTK_BIQUADRATIC_QUADRATIC_WEDGE (= 32)")

    uGrids.append(MakeUnstructuredGrid(
        vtk.vtkBiQuadraticQuadraticHexahedron()))
    titles.append("VTK_BIQUADRATIC_QUADRATIC_HEXAHEDRON (= 33)")

    uGrids.append(MakeUnstructuredGrid(
        vtk.vtkBiQuadraticTriangle()))
    titles.append("VTK_BIQUADRATIC_TRIANGLE (= 34)")

    uGrids.append(MakeUnstructuredGrid(
        vtk.vtkCubicLine()))
    titles.append("VTK_CUBIC_LINE (= 35)")

    colors = vtk.vtkNamedColors()

    renWin = vtk.vtkRenderWindow()
    renWin.SetSize(600, 600)
    renWin.SetWindowName("Isoparametric Cell")

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

        textMappers[i].GetTextProperty().SetFontSize(10)
        textMappers[i].GetTextProperty().ShadowOn()
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
            renderers[index].ResetCameraClippingRange()

    iRen.Initialize()
    renWin.Render()
    iRen.Start()


# These functions return a vtkUnstructured grid corresponding to the object.

def MakeUnstructuredGrid(aCell):
    pcoords = aCell.GetParametricCoords()
    for i in range(0, aCell.GetNumberOfPoints()):
        aCell.GetPointIds().SetId(i, i)
        aCell.GetPoints().SetPoint(i, (pcoords[3 * i]), (pcoords[3 * i + 1]), (pcoords[3 * i + 2]))

    ug = vtk.vtkUnstructuredGrid()
    ug.SetPoints(aCell.GetPoints())
    ug.InsertNextCell(aCell.GetCellType(), aCell.GetPointIds())
    return ug


def MakeQuadraticPolygon():
    quadraticPolygon = vtk.vtkQuadraticPolygon()

    quadraticPolygon.GetPointIds().SetNumberOfIds(8)
    quadraticPolygon.GetPointIds().SetId(0, 0)
    quadraticPolygon.GetPointIds().SetId(1, 1)
    quadraticPolygon.GetPointIds().SetId(2, 2)
    quadraticPolygon.GetPointIds().SetId(3, 3)
    quadraticPolygon.GetPointIds().SetId(4, 4)
    quadraticPolygon.GetPointIds().SetId(5, 5)
    quadraticPolygon.GetPointIds().SetId(6, 6)
    quadraticPolygon.GetPointIds().SetId(7, 7)

    quadraticPolygon.GetPoints().SetNumberOfPoints(8)
    quadraticPolygon.GetPoints().SetPoint(0, 0.0, 0.0, 0.0)
    quadraticPolygon.GetPoints().SetPoint(1, 2.0, 0.0, 0.0)
    quadraticPolygon.GetPoints().SetPoint(2, 2.0, 2.0, 0.0)
    quadraticPolygon.GetPoints().SetPoint(3, 0.0, 2.0, 0.0)
    quadraticPolygon.GetPoints().SetPoint(4, 1.0, 0.0, 0.0)
    quadraticPolygon.GetPoints().SetPoint(5, 2.0, 1.0, 0.0)
    quadraticPolygon.GetPoints().SetPoint(6, 1.0, 2.0, 0.0)
    quadraticPolygon.GetPoints().SetPoint(7, 0.0, 1.0, 0.0)
    quadraticPolygon.GetPoints().SetPoint(5, 3.0, 1.0, 0.0)

    ug = vtk.vtkUnstructuredGrid()
    ug.SetPoints(quadraticPolygon.GetPoints())
    ug.InsertNextCell(quadraticPolygon.GetCellType(), quadraticPolygon.GetPointIds())
    return ug


if __name__ == '__main__':
    main()
