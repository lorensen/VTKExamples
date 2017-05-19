#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Demonstrates how to assign colors to cells in a vtkPolyData structure using
 lookup tables.
Two techniques are demonstrated:
1) Using a lookup table of predefined colors.
2) Using a lookup table generated from a color transfer function.

The resultant display shows in the left-hand column, the cells in a plane
colored by the two lookup tables and in the right-hand column, the same
polydata that has been read in from a file demonstrating that the structures
are identical.

The top row of the display uses the color transfer function to create a
 green to tan transition in a diverging color space.
 Note that the central square is white indicating the midpoint.
The bottom row of the display uses a lookup table of predefined colors.
"""

from __future__ import print_function

import vtk


def MakeLUT(tableSize):
    """
    Make a lookup table from a set of named colors.
    :param: tableSize - The table size
    :return: The lookup table.
    """
    nc = vtk.vtkNamedColors()

    lut = vtk.vtkLookupTable()
    lut.SetNumberOfTableValues(tableSize)
    lut.Build()

    # Fill in a few known colors, the rest will be generated if needed
    lut.SetTableValue(0, nc.GetColor4d("Black"))
    lut.SetTableValue(1, nc.GetColor4d("Banana"))
    lut.SetTableValue(2, nc.GetColor4d("Tomato"))
    lut.SetTableValue(3, nc.GetColor4d("Wheat"))
    lut.SetTableValue(4, nc.GetColor4d("Lavender"))
    lut.SetTableValue(5, nc.GetColor4d("Flesh"))
    lut.SetTableValue(6, nc.GetColor4d("Raspberry"))
    lut.SetTableValue(7, nc.GetColor4d("Salmon"))
    lut.SetTableValue(8, nc.GetColor4d("Mint"))
    lut.SetTableValue(9, nc.GetColor4d("Peacock"))

    return lut


def MakeLUTFromCTF(tableSize):
    """
    Use a color transfer Function to generate the colors in the lookup table.
    See: http://www.vtk.org/doc/nightly/html/classvtkColorTransferFunction.html
    :param: tableSize - The table size
    :return: The lookup table.
    """
    ctf = vtk.vtkColorTransferFunction()
    ctf.SetColorSpaceToDiverging()
    # Green to tan.
    ctf.AddRGBPoint(0.0, 0.085, 0.532, 0.201)
    ctf.AddRGBPoint(0.5, 0.865, 0.865, 0.865)
    ctf.AddRGBPoint(1.0, 0.677, 0.492, 0.093)

    lut = vtk.vtkLookupTable()
    lut.SetNumberOfTableValues(tableSize)
    lut.Build()

    for i in range(0, tableSize):
        rgb = list(ctf.GetColor(float(i) / tableSize)) + [1]
        lut.SetTableValue(i, rgb)

    return lut


def MakeCellData(tableSize, lut, colors):
    """
    Create the cell data using the colors from the lookup table.
    :param: tableSize - The table size
    :param: lut - The lookup table.
    :param: colors - A reference to a vtkUnsignedCharArray().
    """
    for i in range(1, tableSize):
        rgb = [0.0, 0.0, 0.0]
        lut.GetColor(float(i) / (tableSize - 1), rgb)
        ucrgb = list(map(int, [x * 255 for x in rgb]))
        colors.InsertNextTuple3(ucrgb[0], ucrgb[1], ucrgb[2])
        s = '[' + ', '.join(['{:0.6f}'.format(x) for x in rgb]) + ']'
        print(s, ucrgb)


def main():
    """
    :return: The render window interactor.
    """

    nc = vtk.vtkNamedColors()

    # Provide some geometry
    resolution = 3

    plane11 = vtk.vtkPlaneSource()
    plane11.SetXResolution(resolution)
    plane11.SetYResolution(resolution)

    plane12 = vtk.vtkPlaneSource()
    plane12.SetXResolution(resolution)
    plane12.SetYResolution(resolution)

    tableSize = max(resolution * resolution + 1, 10)

    #  Force an update so we can set cell data
    plane11.Update()
    plane12.Update()

    #  Get the lookup tables mapping cell data to colors
    lut1 = MakeLUT(tableSize)
    lut2 = MakeLUTFromCTF(tableSize)

    colorData1 = vtk.vtkUnsignedCharArray()
    colorData1.SetName('colors')  # Any name will work here.
    colorData1.SetNumberOfComponents(3)
    print('Using a lookup table from a set of named colors.')
    MakeCellData(tableSize, lut1, colorData1)
    # Then use SetScalars() to add it to the vtkPolyData structure,
    # this will then be interpreted as a color table.
    plane11.GetOutput().GetCellData().SetScalars(colorData1)

    colorData2 = vtk.vtkUnsignedCharArray()
    colorData2.SetName('colors')  # Any name will work here.
    colorData2.SetNumberOfComponents(3)
    print('Using a lookup table created from a color transfer function.')
    MakeCellData(tableSize, lut2, colorData2)
    plane12.GetOutput().GetCellData().SetScalars(colorData2)

    # Set up actor and mapper
    mapper11 = vtk.vtkPolyDataMapper()
    mapper11.SetInputConnection(plane11.GetOutputPort())
    # Now, instead of doing this:
    # mapper11.SetScalarRange(0, tableSize - 1)
    # mapper11.SetLookupTable(lut1)
    # We can just use the color data that we created from the lookup table and
    # assigned to the cells:
    mapper11.SetScalarModeToUseCellData()
    mapper11.Update()

    mapper12 = vtk.vtkPolyDataMapper()
    mapper12.SetInputConnection(plane12.GetOutputPort())
    mapper12.SetScalarModeToUseCellData()
    mapper12.Update()

    writer = vtk.vtkXMLPolyDataWriter()
    writer.SetFileName('pdlut.vtp')
    writer.SetInputData(mapper11.GetInput())
    # This is set so we can see the data in a text editor.
    writer.SetDataModeToAscii()
    writer.Write()
    writer.SetFileName('pdctf.vtp')
    writer.SetInputData(mapper12.GetInput())
    writer.Write()

    actor11 = vtk.vtkActor()
    actor11.SetMapper(mapper11)
    actor12 = vtk.vtkActor()
    actor12.SetMapper(mapper12)

    # Let's read in the data we wrote out.
    reader1 = vtk.vtkXMLPolyDataReader()
    reader1.SetFileName("pdlut.vtp")

    reader2 = vtk.vtkXMLPolyDataReader()
    reader2.SetFileName("pdctf.vtp")

    mapper21 = vtk.vtkPolyDataMapper()
    mapper21.SetInputConnection(reader1.GetOutputPort())
    mapper21.SetScalarModeToUseCellData()
    mapper21.Update()
    actor21 = vtk.vtkActor()
    actor21.SetMapper(mapper11)

    mapper22 = vtk.vtkPolyDataMapper()
    mapper22.SetInputConnection(reader2.GetOutputPort())
    mapper22.SetScalarModeToUseCellData()
    mapper22.Update()
    actor22 = vtk.vtkActor()
    actor22.SetMapper(mapper22)

    # Define viewport ranges.
    # (xmin, ymin, xmax, ymax)
    viewport11 = [0.0, 0.0, 0.5, 0.5]
    viewport12 = [0.0, 0.5, 0.5, 1.0]
    viewport21 = [0.5, 0.0, 1.0, 0.5]
    viewport22 = [0.5, 0.5, 1.0, 1.0]

    # Set up the renderers.
    ren11 = vtk.vtkRenderer()
    ren12 = vtk.vtkRenderer()
    ren21 = vtk.vtkRenderer()
    ren22 = vtk.vtkRenderer()

    # Setup the render windows
    renWin = vtk.vtkRenderWindow()
    renWin.SetSize(800, 800)
    renWin.AddRenderer(ren11)
    renWin.AddRenderer(ren12)
    renWin.AddRenderer(ren21)
    renWin.AddRenderer(ren22)
    ren11.SetViewport(viewport11)
    ren12.SetViewport(viewport12)
    ren21.SetViewport(viewport21)
    ren22.SetViewport(viewport22)
    ren11.SetBackground(nc.GetColor3d('MidnightBlue'))
    ren12.SetBackground(nc.GetColor3d('MidnightBlue'))
    ren21.SetBackground(nc.GetColor3d('MidnightBlue'))
    ren22.SetBackground(nc.GetColor3d('MidnightBlue'))
    ren11.AddActor(actor11)
    ren12.AddActor(actor12)
    ren21.AddActor(actor21)
    ren22.AddActor(actor22)

    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)
    renWin.Render()

    return iren


if __name__ == '__main__':
    requiredMajorVersion = 6
    print(vtk.vtkVersion().GetVTKMajorVersion())
    if vtk.vtkVersion().GetVTKMajorVersion() < requiredMajorVersion:
        print("You need VTK Version 6 or greater.")
        print("The class vtkNamedColors is in VTK version 6 or greater.")
        exit(0)
    iren = main()
    iren.Start()
