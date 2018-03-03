#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    namedColors = vtk.vtkNamedColors()

    uGrid = MakeQuadraticTetra()

    tessellate = vtk.vtkTessellatorFilter()
    tessellate.SetInputData(uGrid)
    tessellate.SetChordError(.035)
    tessellate.Update()

    cellMap = dict()

    numTets = 0
    cell = vtk.vtkGenericCell()
    it = tessellate.GetOutput().NewCellIterator()
    it.InitTraversal()
    while not it.IsDoneWithTraversal():
        it.GetCell(cell)
        cellMap[cell.GetRepresentativeCell().GetClassName()] = numTets
        numTets += 1
        it.GoToNextCell()

    mapper = vtk.vtkDataSetMapper()
    mapper.SetInputConnection(tessellate.GetOutputPort())
    mapper.ScalarVisibilityOff()

    # Create an actor for the grid
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetDiffuseColor(
        namedColors.GetColor3d("Tomato"))
    actor.GetProperty().SetEdgeColor(
        namedColors.GetColor3d("IvoryBlack"))
    actor.GetProperty().EdgeVisibilityOn()

    sphereSource = vtk.vtkSphereSource()
    sphereSource.SetRadius(0.02)

    glyph3D = vtk.vtkGlyph3D()
    glyph3D.SetInputData(uGrid)
    glyph3D.SetSourceConnection(sphereSource.GetOutputPort())
    glyph3D.ScalingOff()
    glyph3D.Update()

    glyph3DMapper = vtk.vtkDataSetMapper()
    glyph3DMapper.SetInputConnection(glyph3D.GetOutputPort())
    glyph3DMapper.ScalarVisibilityOff()

    glyph3DActor = vtk.vtkActor()
    glyph3DActor.SetMapper(glyph3DMapper)
    glyph3DActor.GetProperty().SetColor(
        namedColors.GetColor3d("Banana"))

    textProperty = vtk.vtkTextProperty()
    textProperty.SetFontSize(24)

    ss = "# of Tetras: " + str(numTets)
    textMapper = vtk.vtkTextMapper()
    textMapper.SetInput(ss)
    textMapper.SetTextProperty(textProperty)

    textActor = vtk.vtkActor2D()
    textActor.SetMapper(textMapper)
    textActor.SetPosition(10, 400)

    # Visualize
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("Quadratic Tetra Demo")
    renderWindow.AddRenderer(renderer)
    renderWindow.SetSize(640, 512)
    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderWindow)

    widget = vtk.vtkSliderWidget()
    MakeWidget(widget, tessellate, textMapper, interactor)

    renderer.AddActor(actor)
    renderer.AddActor(glyph3DActor)
    renderer.AddViewProp(textActor)
    renderer.SetBackground(namedColors.GetColor3d("SlateGray"))

    renderWindow.Render()

    interactor.Start()


class SliderCallbackChordError():
    def __init__(self, tessellate, textMapper):
        self.tessellate = tessellate
        self.textMapper = textMapper

    def __call__(self, caller, ev):
        sliderWidget = caller
        value = sliderWidget.GetRepresentation().GetValue()
        self.tessellate.SetChordError(value)
        self.tessellate.SetMaximumNumberOfSubdivisions(5)
        self.tessellate.Update()

        cellMap = dict()

        numTets = 0
        cell = vtk.vtkGenericCell()
        it = self.tessellate.GetOutput().NewCellIterator()
        it.InitTraversal()
        while not it.IsDoneWithTraversal():
            it.GetCell(cell)
            cellMap[cell.GetRepresentativeCell().GetClassName()] = numTets
            numTets += 1
            it.GoToNextCell()
        ss = "# of Tetras: " + str(numTets)
        self.textMapper.SetInput(ss)


def MakeWidget(widget, tessellate, textMapper, interactor):
    # Setup a slider widget for each varying parameter
    tubeWidth = 0.008
    sliderLength = 0.008
    titleHeight = 0.04
    labelHeight = 0.04

    sliderRepChordError = vtk.vtkSliderRepresentation2D()

    sliderRepChordError.SetMinimumValue(0.0)
    sliderRepChordError.SetMaximumValue(0.07)
    sliderRepChordError.SetValue(tessellate.GetChordError())
    sliderRepChordError.SetTitleText("Chord error")

    sliderRepChordError.GetPoint1Coordinate().SetCoordinateSystemToNormalizedDisplay()
    sliderRepChordError.GetPoint1Coordinate().SetValue(0.1, 0.1)
    sliderRepChordError.GetPoint2Coordinate().SetCoordinateSystemToNormalizedDisplay()
    sliderRepChordError.GetPoint2Coordinate().SetValue(0.9, 0.1)

    sliderRepChordError.SetTubeWidth(tubeWidth)
    sliderRepChordError.SetSliderLength(sliderLength)
    sliderRepChordError.SetTitleHeight(titleHeight)
    sliderRepChordError.SetLabelHeight(labelHeight)

    widget.SetInteractor(interactor)
    widget.SetRepresentation(sliderRepChordError)
    widget.SetAnimationModeToAnimate()
    widget.EnabledOn()

    widget.AddObserver(vtk.vtkCommand.InteractionEvent, SliderCallbackChordError(tessellate, textMapper))


def MakeQuadraticTetra():
    aTetra = vtk.vtkQuadraticTetra()
    points = vtk.vtkPoints()

    pcoords = aTetra.GetParametricCoords()
    rng = vtk.vtkMinimalStandardRandomSequence()
    points.SetNumberOfPoints(aTetra.GetNumberOfPoints())
    rng.SetSeed(5070)  # for testing
    for i in range(0, aTetra.GetNumberOfPoints()):
        perturbation = [0.0] * 3
        for j in range(0, 3):
            rng.Next()
            perturbation[j] = rng.GetRangeValue(-0.2, 0.2)
        aTetra.GetPointIds().SetId(i, i)
        points.SetPoint(i, pcoords[3 * i] + perturbation[0],
                        pcoords[3 * i + 1] + perturbation[1],
                        pcoords[3 * i + 2] + perturbation[2])

    # Add the points and tetra to an unstructured grid
    uGrid = vtk.vtkUnstructuredGrid()
    uGrid.SetPoints(points)
    uGrid.InsertNextCell(aTetra.GetCellType(), aTetra.GetPointIds())

    return uGrid


if __name__ == '__main__':
    main()
