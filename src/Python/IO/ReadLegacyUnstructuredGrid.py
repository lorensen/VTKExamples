#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    colors = vtk.vtkNamedColors()

    filename = get_program_parameters()

    # Create the reader for the data.
    print("Loading ", filename)
    reader = vtk.vtkUnstructuredGridReader()
    reader.SetFileName(filename)
    reader.Update()

    extractEdges = vtk.vtkExtractEdges()
    extractEdges.SetInputConnection(reader.GetOutputPort())

    legendValues = vtk.vtkVariantArray()
    it = reader.GetOutput().NewCellIterator()
    it.InitTraversal()
    while not it.IsDoneWithTraversal():
        cell = vtk.vtkGenericCell()
        it.GetCell(cell)
        cellName = vtk.vtkCellTypes.GetClassNameFromTypeId(cell.GetCellType())
        print(cellName, "NumberOfPoints:", cell.GetNumberOfPoints(), "CellDimension:", cell.GetCellDimension())
        legendValues.InsertNextValue(cellName)
        it.GoToNextCell()

    # Tube the edges
    tubes = vtk.vtkTubeFilter()
    tubes.SetInputConnection(extractEdges.GetOutputPort())
    tubes.SetRadius(.05)
    tubes.SetNumberOfSides(21)

    edgeMapper = vtk.vtkPolyDataMapper()
    edgeMapper.SetInputConnection(tubes.GetOutputPort())
    edgeMapper.SetScalarRange(0, 26)

    edgeActor = vtk.vtkActor()
    edgeActor.SetMapper(edgeMapper)
    edgeActor.GetProperty().SetSpecular(.6)
    edgeActor.GetProperty().SetSpecularPower(30)

    # Glyph the points
    sphere = vtk.vtkSphereSource()
    sphere.SetPhiResolution(21)
    sphere.SetThetaResolution(21)
    sphere.SetRadius(.08)

    pointMapper = vtk.vtkGlyph3DMapper()
    pointMapper.SetInputConnection(reader.GetOutputPort())
    pointMapper.SetSourceConnection(sphere.GetOutputPort())
    pointMapper.ScalingOff()
    pointMapper.ScalarVisibilityOff()

    pointActor = vtk.vtkActor()
    pointActor.SetMapper(pointMapper)
    pointActor.GetProperty().SetDiffuseColor(colors.GetColor3d("Banana"))
    pointActor.GetProperty().SetSpecular(.6)
    pointActor.GetProperty().SetSpecularColor(1.0, 1.0, 1.0)
    pointActor.GetProperty().SetSpecularPower(100)

    # Label the points
    labelMapper = vtk.vtkLabeledDataMapper()
    labelMapper.SetInputConnection(reader.GetOutputPort())
    labelActor = vtk.vtkActor2D()
    labelActor.SetMapper(labelMapper)

    # The geometry
    geometryShrink = vtk.vtkShrinkFilter()
    geometryShrink.SetInputConnection(reader.GetOutputPort())
    geometryShrink.SetShrinkFactor(.8)

    # NOTE: We must copy the originalLut because the CategoricalLegend
    # needs an indexed lookup table, but the geometryMapper uses a
    # non-index lookup table
    categoricalLut = vtk.vtkLookupTable()
    originalLut = reader.GetOutput().GetCellData().GetScalars().GetLookupTable()

    categoricalLut.DeepCopy(originalLut)
    categoricalLut.IndexedLookupOn()

    geometryMapper = vtk.vtkDataSetMapper()
    geometryMapper.SetInputConnection(geometryShrink.GetOutputPort())
    geometryMapper.SetScalarModeToUseCellData()
    geometryMapper.SetScalarRange(0, 11)

    geometryActor = vtk.vtkActor()
    geometryActor.SetMapper(geometryMapper)
    geometryActor.GetProperty().SetLineWidth(3)
    geometryActor.GetProperty().EdgeVisibilityOn()
    geometryActor.GetProperty().SetEdgeColor(0, 0, 0)

    # Legend
    for v in range(0, legendValues.GetNumberOfTuples()):
        categoricalLut.SetAnnotation(legendValues.GetValue(v), legendValues.GetValue(v).ToString())
    legend = vtk.vtkCategoryLegend()
    legend.SetScalarsToColors(categoricalLut)
    legend.SetValues(legendValues)
    legend.SetTitle("Cell Type")
    legend.GetBrush().SetColor(colors.GetColor4ub("Silver"))

    placeLegend = vtk.vtkContextTransform()
    placeLegend.AddItem(legend)
    placeLegend.Translate(640 - 20, 480 - 12 * 16)

    contextView = vtk.vtkContextView()
    contextView.GetScene().AddItem(placeLegend)

    renderer = contextView.GetRenderer()

    renderWindow = contextView.GetRenderWindow()

    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    renderer.AddActor(geometryActor)
    renderer.AddActor(labelActor)
    renderer.AddActor(edgeActor)
    renderer.AddActor(pointActor)
    renderer.SetBackground(colors.GetColor3d("SlateGray"))

    aCamera = vtk.vtkCamera()
    aCamera.Azimuth(-40.0)
    aCamera.Elevation(50.0)

    renderer.SetActiveCamera(aCamera)
    renderer.ResetCamera()

    renderWindow.SetSize(640, 480)
    renderWindow.Render()

    renderWindowInteractor.Start()


def get_program_parameters():
    import argparse
    description = 'Display a vtkUnstructuredGrid that contains eleven linear cells.'
    epilogue = '''
    This example also shows how to add a vtkCategoryLegend to a visualization.
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='VTKCellTypes.vtk.')
    args = parser.parse_args()
    return args.filename


if __name__ == '__main__':
    main()
