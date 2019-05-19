#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
    This example demonstrates the usage of the vtNamedColor class.
"""
from __future__ import print_function

import vtk


def main():
    nc = vtk.vtkNamedColors()
    # We can print out the variables.
    # The color name and RGBA values are displayed.
    print(nc)

    # Here we just print out the colors and any
    # synonyms.
    PrintColors(nc)
    PrintSynonyms(nc)

    """
    Create a cone, contour it using the banded contour filter and
        color it with the primary additive and subtractive colors.
    """
    # Create a cone
    coneSource = vtk.vtkConeSource()
    coneSource.SetCenter(0.0, 0.0, 0.0)
    coneSource.SetRadius(5.0)
    coneSource.SetHeight(10)
    coneSource.SetDirection(0, 1, 0)
    coneSource.SetResolution(6)
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

    # Test setting and getting a color here.
    # We are also modifying alpha.
    # Convert to a list so that
    # SetColor(name,rgba) works.
    rgba = list(nc.GetColor4d("Red"))
    rgba[3] = 0.5
    nc.SetColor("My Red", rgba)
    # Does "My Red" match anything?
    match = FindSynonyms(nc, "My Red")
    print("Matching colors to My Red:", ', '.join(match))
    # Build a simple lookup table of
    # primary additive and subtractive colors.
    lut = vtk.vtkLookupTable()
    lut.SetNumberOfTableValues(7)
    lut.SetTableValue(0, nc.GetColor4d("My Red"))
    # Let's make the dark green one partially transparent.
    rgba = nc.GetColor4d("Lime")
    rgba[3] = 0.3
    lut.SetTableValue(1, rgba)
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
    renderer.SetBackground2(nc.GetColor3d('RoyalBlue'))
    renderer.SetBackground(nc.GetColor3d('MistyRose'))
    renderer.GradientBackgroundOn()
    renderWindow.SetSize(600, 600)
    renderWindow.Render()
    renderWindow.SetWindowName('NamedColors')
    renderWindow.Render()
    renderWindow.Render()

    renderWindowInteractor.Start()


def FindSynonyms(nc, colorName):
    """
    Find any synonyms for a specified color.
    :param: nc: The vtkNamedColor class
    :param: colorName: the name of the color to find the synonyms for.
    :return: The synonyms for colorName.
    """
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


def PrintColors(nc):
    colorNames = nc.GetColorNames().split('\n')
    print("There are", len(colorNames), "colors:")
    max_str_len = len(max(colorNames, key=len))
    n = 0
    s = ''
    for p in colorNames:
        n += 1
        if n % 5 == 0:
            s += '{:s}\n'.format(p)
        else:
            s += '{:s} '.format(p.ljust(max_str_len))
    s = s.strip() + '\n'
    print(s)


def PrintSynonyms(nc):
    syn = nc.GetSynonyms().split('\n\n')
    print("There are", len(syn), "synonyms:")
    synonyms = []
    for ele in syn:
        synonyms.append(ele.split('\n'))
    max_str_len = 0
    for p in synonyms:
        max_len = len(max(p, key=len))
        if max_len > max_str_len:
            max_str_len = max_len
    s = ''
    for p in synonyms:
        n = 0
        for q in p:
            n += 1
            if n < len(p):
                s += '{:s} '.format(q.ljust(max_str_len))
            else:
                s += '{:s}\n'.format(q)
    s = s.strip() + '\n'
    print(s)


if __name__ == "__main__":
    main()
