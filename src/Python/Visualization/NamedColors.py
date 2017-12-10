#!/usr/bin/env python
# -*- coding: utf-8 -*-

'''
    This example demonstrates the usage of the vtNamedColor class.
'''
from __future__ import print_function

import vtk


def FindSynonyms(nc, colorName):
    '''
    Find any synonyms for a specified color.
    :param: nc: The vtkNamedColor class
    :param: colorName: the name of the color to find the synonyms for.
    :return: The synonyms for colorName.
    '''
    availableColors = nc.GetColorNames()
    # Make a list
    availableColors = availableColors.split('\n')
    synonyms = []
    # We use lower case for comparison and
    # just the red, green, and blue components
    # of the color.
    myColor = nc.GetColor3ub(colorName)
    for color in availableColors:
        rgb = nc.GetColor3ub(color)
        if list(myColor) == list(rgb):
            synonyms.append(color)
    return synonyms


def DisplayCone(nc):
    '''
    Create a cone, contour it using the banded contour filter and
        color it with the primary additive and subtractive colors.
    :param: nc: The vtkNamedColor class
    :return: The render window interactor.
    '''
    # Create a cone
    coneSource = vtk.vtkConeSource()
    coneSource.SetCenter(0.0, 0.0, 0.0)
    coneSource.SetRadius(5.0)
    coneSource.SetHeight(10)
    coneSource.SetDirection(0, 1, 0)
    coneSource.Update()

    bounds = [1.0, -1.0, 1.0, -1.0, 1.0, -1.0]
    coneSource.GetOutput().GetBounds(bounds)

    elevation = vtk.vtkElevationFilter()
    elevation.SetInputConnection(coneSource.GetOutputPort())
    elevation.SetLowPoint(0, bounds[2], 0)
    elevation.SetHighPoint(0, bounds[3], 0)

    bcf = vtk.vtkBandedPolyDataContourFilter()
    bcf.SetInputConnection(elevation.GetOutputPort())
    bcf.SetScalarModeToValue()
    bcf.GenerateContourEdgesOn()
    bcf.GenerateValues(7, elevation.GetScalarRange())

    # Build a simple lookup table of
    # primary additive and subtractive colors.
    lut = vtk.vtkLookupTable()
    lut.SetNumberOfTableValues(7)
    # Test setting and getting a color here.
    # We are also modifying alpha.

    # Convert to a list so that
    # SetColor(name,rgba) works.
    rgba = list(nc.GetColor4d("Red"))
    rgba[3] = 0.5
    nc.SetColor("My Red", rgba)
    rgba = nc.GetColor4d("My Red")
    lut.SetTableValue(0, rgba)
    # Does "My Red" match anything?
    match = FindSynonyms(nc, "My Red")
    print("Matching colors to My Red:", match)

    rgba = nc.GetColor4d("DarkGreen")
    rgba[3] = 0.3
    lut.SetTableValue(1, rgba)
    #  Alternatively we can use our wrapper functions:
    lut.SetTableValue(2, nc.GetColor4d("Blue"))
    lut.SetTableValue(3, nc.GetColor4d("Cyan"))
    lut.SetTableValue(4, nc.GetColor4d("Magenta"))
    lut.SetTableValue(5, nc.GetColor4d("Yellow"))
    lut.SetTableValue(6, nc.GetColor4d("White"))
    lut.SetTableRange(elevation.GetScalarRange())
    lut.Build()

    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(bcf.GetOutputPort())
    mapper.SetLookupTable(lut)
    mapper.SetScalarModeToUseCellData()

    contourLineMapper = vtk.vtkPolyDataMapper()
    contourLineMapper.SetInputData(bcf.GetContourEdgesOutput())
    contourLineMapper.SetScalarRange(elevation.GetScalarRange())
    contourLineMapper.SetResolveCoincidentTopologyToPolygonOffset()

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)

    contourLineActor = vtk.vtkActor()
    actor.SetMapper(mapper)
    contourLineActor.SetMapper(contourLineMapper)
    contourLineActor.GetProperty().SetColor(
        nc.GetColor3d("black"))

    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    renderer.AddActor(actor)
    renderer.AddActor(contourLineActor)
    renderer.SetBackground(
        nc.GetColor3d("SteelBlue"))

    renderWindow.Render()

    fnsave = "TestNamedColorsIntegration.png"
    renLgeIm = vtk.vtkRenderLargeImage()
    imgWriter = vtk.vtkPNGWriter()
    renLgeIm.SetInput(renderer)
    renLgeIm.SetMagnification(1)
    imgWriter.SetInputConnection(renLgeIm.GetOutputPort())
    imgWriter.SetFileName(fnsave)
    # imgWriter.Write()

    return renderWindowInteractor


def main():
    nc = vtk.vtkNamedColors()
    colorNames = nc.GetColorNames().split('\n')
    print("There are", len(colorNames), "colors:")
    print(colorNames)
    syn = nc.GetSynonyms().split('\n\n')
    synonyms = []
    for ele in syn:
        synonyms.append(ele.split('\n'))
    print("There are", len(synonyms), "synonyms:")
    print(synonyms)
    iren = DisplayCone(nc)
    iren.Start()


if __name__ == "__main__":
    requiredMajorVersion = 6
    print(vtk.vtkVersion().GetVTKMajorVersion())
    if vtk.vtkVersion().GetVTKMajorVersion() < requiredMajorVersion:
        print("You need VTK Version 6 or greater.")
        print("The class vtkNamedColors is in VTK version 6 or greater.")
        exit(0)
    main()
