#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function, division
import vtk

def main(filename, curvature=0, scalarRange=None, scheme=None):
    print("Loading", filename)
    reader = vtk.vtkXMLPolyDataReader()
    reader.SetFileName(filename)

    curvaturesFilter = vtk.vtkCurvatures()
    curvaturesFilter.SetInputConnection(reader.GetOutputPort())
    if curvature == 0:
        curvaturesFilter.SetCurvatureTypeToMinimum()
    elif curvature == 1:
        curvaturesFilter.SetCurvatureTypeToMaximum()
    elif curvature == 2:
        curvaturesFilter.SetCurvatureTypeToGaussian()
    else:
        curvaturesFilter.SetCurvatureTypeToMean()
    curvaturesFilter.Update()

    # Get scalar range from command line if present, otherwise use
    # range of computed curvature
    if scalarRange is None:
        scalarRange = curvaturesFilter.GetOutput().GetScalarRange()

    # Build a lookup table
    if scheme is None:
        scheme = 16
    colorSeries = vtk.vtkColorSeries()
    colorSeries.SetColorScheme(scheme)
    print("Using color scheme #:", colorSeries.GetColorScheme(), \
        "is", colorSeries.GetColorSchemeName())

    lut = vtk.vtkColorTransferFunction()
    lut.SetColorSpaceToHSV()

    # Use a color series to create a transfer function
    numColors = colorSeries.GetNumberOfColors()
    for i in range(numColors):
        color = colorSeries.GetColor(i)
        dColor = [color[0]/255.0, color[1]/255.0, color[2]/255.0]
        t = scalarRange[0] + (scalarRange[1] - scalarRange[0]) / (numColors - 1) * i
        lut.AddRGBPoint(t, dColor[0], dColor[1], dColor[2])

    # Create a mapper and actor
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(curvaturesFilter.GetOutputPort())
    mapper.SetLookupTable(lut)
    mapper.SetScalarRange(scalarRange)

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)

    # Create a scalar bar
    print("Displaying", curvaturesFilter.GetOutput().GetPointData().GetScalars().GetName())
    scalarBarActor = vtk.vtkScalarBarActor()
    scalarBarActor.SetLookupTable(mapper.GetLookupTable())
    scalarBarActor.SetTitle(
        curvaturesFilter.GetOutput().GetPointData().GetScalars().GetName())
    
    scalarBarActor.SetNumberOfLabels(5)

    # Create a renderer, render window, and interactor
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    # Add the actors to the scene
    renderer.AddActor(actor)
    renderer.AddActor2D(scalarBarActor)

    renderer.SetBackground(.1, .2, .3) # Background color blue

    # Render and interact
    renderWindow.Render()
    renderWindowInteractor.Start()


def get_program_parameters():
    import argparse
    description = 'Computes the curvature of a polydata surface.'
    epilogue = '''
    filename=./src/Testing/Data/cowHead.vtp
    curvature: 0=Min, 1=Max, 2=Gauss, 3=Mean
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='Filename.vtp')
    parser.add_argument('curvature', type=int, help='Int value')
    parser.add_argument('scalarRangeLow', nargs='?', type=float, help='Float value')
    parser.add_argument('scalarRangeHigh', nargs='?', type=float, help='Float value')
    parser.add_argument('colorScheme', nargs='?', type=int, help='Int value')
    args = parser.parse_args()
    scalarRange = None
    if args.scalarRangeLow and args.scalarRangeHigh:
        scalarRange = (args.scalarRangeLow, args.scalarRangeHigh)
    return args.filename, args.curvature, scalarRange, args.colorScheme

if __name__ == "__main__":
    main(*get_program_parameters())
