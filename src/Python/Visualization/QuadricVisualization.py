#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    colors = vtk.vtkNamedColors()

    renderer = vtk.vtkRenderer()

    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)

    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderWindow)
    renderWindow.SetSize(640, 480)

    #
    # Create surface of implicit function.
    #

    # Sample quadric function.
    quadric = vtk.vtkQuadric()
    quadric.SetCoefficients(1, 2, 3, 0, 1, 0, 0, 0, 0, 0)

    sample = vtk.vtkSampleFunction()
    sample.SetSampleDimensions(25, 25, 25)
    sample.SetImplicitFunction(quadric)

    isoActor = vtk.vtkActor()
    CreateIsosurface(sample, isoActor)
    outlineIsoActor = vtk.vtkActor()
    CreateOutline(sample, outlineIsoActor)

    planesActor = vtk.vtkActor()
    CreatePlanes(sample, planesActor, 3)
    outlinePlanesActor = vtk.vtkActor()
    CreateOutline(sample, outlinePlanesActor)
    planesActor.AddPosition(isoActor.GetBounds()[0] * 2.0, 0, 0)
    outlinePlanesActor.AddPosition(isoActor.GetBounds()[0] * 2.0, 0, 0)

    contourActor = vtk.vtkActor()
    CreateContours(sample, contourActor, 3, 15)
    outlineContourActor = vtk.vtkActor()
    CreateOutline(sample, outlineContourActor)
    contourActor.AddPosition(isoActor.GetBounds()[0] * 4.0, 0, 0)
    outlineContourActor.AddPosition(isoActor.GetBounds()[0] * 4.0, 0, 0)

    renderer.AddActor(planesActor)
    renderer.AddActor(outlinePlanesActor)
    renderer.AddActor(contourActor)
    renderer.AddActor(outlineContourActor)
    renderer.AddActor(isoActor)
    renderer.AddActor(outlineIsoActor)

    renderer.TwoSidedLightingOn()

    renderer.SetBackground(colors.GetColor3d("SlateGray"))

    # Try to set camera to match figure on book
    renderer.GetActiveCamera().SetPosition(0, -1, 0)
    renderer.GetActiveCamera().SetFocalPoint(0, 0, 0)
    renderer.GetActiveCamera().SetViewUp(0, 0, -1)
    renderer.ResetCamera()
    renderer.GetActiveCamera().Elevation(20)
    renderer.GetActiveCamera().Azimuth(10)
    renderer.GetActiveCamera().Dolly(1.2)
    renderer.ResetCameraClippingRange()

    renderWindow.SetSize(640, 480)
    renderWindow.Render()

    # interact with data
    interactor.Start()


def CreateIsosurface(func, actor, numberOfContours=5):
    # Generate implicit surface.
    contour = vtk.vtkContourFilter()
    contour.SetInputConnection(func.GetOutputPort())
    ranges = [1.0, 6.0]
    contour.GenerateValues(numberOfContours, ranges)

    # Map contour
    contourMapper = vtk.vtkPolyDataMapper()
    contourMapper.SetInputConnection(contour.GetOutputPort())
    contourMapper.SetScalarRange(0, 7)

    actor.SetMapper(contourMapper)
    return


def CreatePlanes(func, actor, numberOfPlanes):
    #
    # Extract planes from implicit function.
    #

    append = vtk.vtkAppendFilter()

    dims = func.GetSampleDimensions()
    sliceIncr = (dims[2] - 1) // (numberOfPlanes + 1)
    sliceNum = -4
    for i in range(0, numberOfPlanes):
        extract = vtk.vtkExtractVOI()
        extract.SetInputConnection(func.GetOutputPort())
        extract.SetVOI(0, dims[0] - 1,
                       0, dims[1] - 1,
                       sliceNum + sliceIncr, sliceNum + sliceIncr)
        append.AddInputConnection(extract.GetOutputPort())
        sliceNum += sliceIncr
    append.Update()

    # Map planes
    planesMapper = vtk.vtkDataSetMapper()
    planesMapper.SetInputConnection(append.GetOutputPort())
    planesMapper.SetScalarRange(0, 7)

    actor.SetMapper(planesMapper)
    actor.GetProperty().SetAmbient(1.)
    return


def CreateContours(func, actor, numberOfPlanes, numberOfContours):
    #
    # Extract planes from implicit function
    #

    append = vtk.vtkAppendFilter()

    dims = func.GetSampleDimensions()
    sliceIncr = (dims[2] - 1) // (numberOfPlanes + 1)

    sliceNum = -4
    for i in range(0, numberOfPlanes):
        extract = vtk.vtkExtractVOI()
        extract.SetInputConnection(func.GetOutputPort())
        extract.SetVOI(0, dims[0] - 1,
                       0, dims[1] - 1,
                       sliceNum + sliceIncr, sliceNum + sliceIncr)
        ranges = [1.0, 6.0]
        contour = vtk.vtkContourFilter()
        contour.SetInputConnection(extract.GetOutputPort())
        contour.GenerateValues(numberOfContours, ranges)
        append.AddInputConnection(contour.GetOutputPort())
        sliceNum += sliceIncr
    append.Update()

    # Map planes
    planesMapper = vtk.vtkDataSetMapper()
    planesMapper.SetInputConnection(append.GetOutputPort())
    planesMapper.SetScalarRange(0, 7)

    actor.SetMapper(planesMapper)
    actor.GetProperty().SetAmbient(1.)
    return


def CreateOutline(source, actor):
    outline = vtk.vtkOutlineFilter()
    outline.SetInputConnection(source.GetOutputPort())
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(outline.GetOutputPort())
    actor.SetMapper(mapper)
    return


if __name__ == "__main__":
    main()
