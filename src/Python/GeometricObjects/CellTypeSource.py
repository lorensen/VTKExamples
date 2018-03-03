# !/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    cellName = get_program_parameters()

    # Store the cell class names in a dictionary.
    cellMap = dict()
    cellMap[vtk.vtkCellTypes.GetClassNameFromTypeId(vtk.VTK_LINE)] = vtk.VTK_LINE
    cellMap[vtk.vtkCellTypes.GetClassNameFromTypeId(vtk.VTK_QUADRATIC_EDGE)] = vtk.VTK_QUADRATIC_EDGE
    cellMap[vtk.vtkCellTypes.GetClassNameFromTypeId(vtk.VTK_CUBIC_LINE)] = vtk.VTK_CUBIC_LINE

    cellMap[vtk.vtkCellTypes.GetClassNameFromTypeId(vtk.VTK_TRIANGLE)] = vtk.VTK_TRIANGLE
    cellMap[vtk.vtkCellTypes.GetClassNameFromTypeId(vtk.VTK_QUADRATIC_TRIANGLE)] = vtk.VTK_QUADRATIC_TRIANGLE
    cellMap[vtk.vtkCellTypes.GetClassNameFromTypeId(vtk.VTK_QUAD)] = vtk.VTK_QUAD
    cellMap[vtk.vtkCellTypes.GetClassNameFromTypeId(vtk.VTK_QUADRATIC_QUAD)] = vtk.VTK_QUADRATIC_QUAD

    cellMap[vtk.vtkCellTypes.GetClassNameFromTypeId(vtk.VTK_TETRA)] = vtk.VTK_TETRA
    cellMap[vtk.vtkCellTypes.GetClassNameFromTypeId(vtk.VTK_HEXAHEDRON)] = vtk.VTK_HEXAHEDRON
    cellMap[vtk.vtkCellTypes.GetClassNameFromTypeId(vtk.VTK_WEDGE)] = vtk.VTK_WEDGE
    cellMap[vtk.vtkCellTypes.GetClassNameFromTypeId(vtk.VTK_PYRAMID)] = vtk.VTK_PYRAMID
    cellMap[vtk.vtkCellTypes.GetClassNameFromTypeId(vtk.VTK_QUADRATIC_WEDGE)] = vtk.VTK_QUADRATIC_WEDGE
    cellMap[vtk.vtkCellTypes.GetClassNameFromTypeId(vtk.VTK_QUADRATIC_PYRAMID)] = vtk.VTK_QUADRATIC_PYRAMID
    cellMap[vtk.vtkCellTypes.GetClassNameFromTypeId(vtk.VTK_QUADRATIC_HEXAHEDRON)] = vtk.VTK_QUADRATIC_HEXAHEDRON
    cellMap[vtk.vtkCellTypes.GetClassNameFromTypeId(vtk.VTK_QUADRATIC_TETRA)] = vtk.VTK_QUADRATIC_TETRA

    if cellName not in cellMap:
        print("Cell type ", cellName, " is not supported.")
        return
    source = vtk.vtkCellTypeSource()
    source.SetCellType(cellMap[cellName])
    source.Update()
    print("Cell: ", cellName)

    originalPoints = source.GetOutput().GetPoints()
    points = vtk.vtkPoints()
    points.SetNumberOfPoints(source.GetOutput().GetNumberOfPoints())
    rng = vtk.vtkMinimalStandardRandomSequence()
    rng.SetSeed(5070)  # for testing
    vtk.vtkMath.RandomSeed(5070)  # for testing
    for i in range(0, points.GetNumberOfPoints()):
        perturbation = [0.0] * 3
        for j in range(0, 3):
            rng.Next()
            perturbation[j] = rng.GetRangeValue(-0.1, 0.1)
        currentPoint = [0.0] * 3
        originalPoints.GetPoint(i, currentPoint)
        points.SetPoint(i, currentPoint[0] + perturbation[0],
                        currentPoint[1] + perturbation[1],
                        currentPoint[2] + perturbation[2])
    source.GetOutput().SetPoints(points)

    numCells = source.GetOutput().GetNumberOfCells()
    print("Number of cells: ", numCells)
    idArray = vtk.vtkIntArray()
    idArray.SetNumberOfTuples(numCells)
    for i in range(0, numCells):
        idArray.InsertTuple1(i, i + 1)
    idArray.SetName("Ids")
    source.GetOutput().GetCellData().AddArray(idArray)
    source.GetOutput().GetCellData().SetActiveScalars("Ids")

    shrink = vtk.vtkShrinkFilter()
    shrink.SetInputConnection(source.GetOutputPort())
    shrink.SetShrinkFactor(.8)

    tessellate = vtk.vtkTessellatorFilter()
    tessellate.SetInputConnection(shrink.GetOutputPort())
    tessellate.SetMaximumNumberOfSubdivisions(3)

    # Create a lookup table to map cell data to colors.
    lut = vtk.vtkLookupTable()

    colorSeries = vtk.vtkColorSeries()
    seriesEnum = colorSeries.BREWER_QUALITATIVE_SET3
    colorSeries.SetColorScheme(seriesEnum)
    colorSeries.BuildLookupTable(lut, colorSeries.ORDINAL)

    # Fill in a few known colors, the rest will be generated if needed.
    colors = vtk.vtkNamedColors()

    # Create a mapper and actor.
    mapper = vtk.vtkDataSetMapper()
    mapper.SetInputConnection(source.GetOutputPort())
    mapper.SetInputConnection(shrink.GetOutputPort())
    mapper.SetScalarRange(0, numCells + 1)
    mapper.SetLookupTable(lut)
    mapper.SetScalarModeToUseCellData()
    mapper.SetResolveCoincidentTopologyToPolygonOffset()
    if (source.GetCellType() == vtk.VTK_QUADRATIC_PYRAMID or
            source.GetCellType() == vtk.VTK_QUADRATIC_WEDGE):
        mapper.SetInputConnection(shrink.GetOutputPort())
    else:
        mapper.SetInputConnection(tessellate.GetOutputPort())
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().EdgeVisibilityOn()
    #  actor.GetProperty().SetLineWidth(3)

    textProperty = vtk.vtkTextProperty()
    textProperty.SetFontSize(20)
    textProperty.SetJustificationToCentered()
    textProperty.SetColor(colors.GetColor3d("Lamp_Black"))

    textMapper = vtk.vtkTextMapper()
    textMapper.SetInput(cellName)
    textMapper.SetTextProperty(textProperty)

    textActor = vtk.vtkActor2D()
    textActor.SetMapper(textMapper)
    textActor.SetPosition(320, 20)

    # Create a renderer, render window, and interactor.
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("Cell Type Source")
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    # Add the actors to the scene.
    renderer.AddViewProp(textActor)
    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("Silver"))

    renderer.ResetCamera()
    renderer.GetActiveCamera().Azimuth(30)
    renderer.GetActiveCamera().Elevation(30)
    renderer.ResetCameraClippingRange()

    # Render and interact.
    renderWindow.SetSize(640, 480)
    renderWindow.Render()
    renderWindowInteractor.Start()


def get_program_parameters():
    import argparse
    description = 'Cell Type Source.'
    epilogue = '''
    You can supply an optional argument consisting of a vtkCell name e.g: vtkTriangle.
    The default is vtkTetra.
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('cell_name', nargs='?', const="vtkTetra", default="vtkTetra", type=str, help="The cell name.")
    args = parser.parse_args()
    return args.cell_name


if __name__ == '__main__':
    main()
