#!/usr/bin/env python

#  Translated from hawaii.tcl

import vtk


def main():
    file_name, color_scheme = get_program_parameters()

    color_scheme = abs(color_scheme)
    if color_scheme > 2:
        color_scheme = 0;

    colors = vtk.vtkNamedColors()

    # Set the background color.
    colors.SetColor("BkgColor", [26, 51, 102, 255])

    # Read a vtk file
    #
    hawaii = vtk.vtkPolyDataReader()
    hawaii.SetFileName(file_name)
    hawaii.Update()
    bounds = [0.0] * 6
    hawaii.GetOutput().GetBounds(bounds)

    elevation = vtk.vtkElevationFilter()
    elevation.SetInputConnection(hawaii.GetOutputPort())
    elevation.SetLowPoint(0, 0, 0)
    elevation.SetHighPoint(0, 0, 1000)
    elevation.SetScalarRange(0, 1000)

    lut = MakeLUT(color_scheme)

    hawaiiMapper = vtk.vtkDataSetMapper()
    hawaiiMapper.SetInputConnection(elevation.GetOutputPort())
    hawaiiMapper.SetScalarRange(0, 1000)
    hawaiiMapper.ScalarVisibilityOn()
    hawaiiMapper.SetLookupTable(lut)

    hawaiiActor = vtk.vtkActor()
    hawaiiActor.SetMapper(hawaiiMapper)

    # Create the RenderWindow, Renderer and both Actors
    #
    ren = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Add the actors to the renderer, set the background and size
    #
    ren.AddActor(hawaiiActor)
    # Match the window shape to the object.
    # renWin.SetSize(500, int(500 * bounds[1] / bounds[3]))
    renWin.SetSize(500, 500)

    iren.Initialize()

    # Render the image.
    # Centered on Honolulu.
    # Diamond Head is the crater lower left.
    # Punchbowl is the crater in the centre.
    renWin.Render()
    ren.SetBackground(colors.GetColor3d("BkgColor"))
    ren.GetActiveCamera().Zoom(1.5)
    ren.GetActiveCamera().Roll(-90)

    renWin.Render()
    iren.Start()


def get_program_parameters():
    import argparse
    description = 'Produce figure 6–12 from the VTK Textbook.'
    epilogue = '''
        Produce figure 6–12 from the VTK Textbook.
        It is a translation of the original hawaii.tcl with a few additional enhancements.
        The image is centered on Honolulu, O'ahu.
        Diamond Head is the crater lower left. Punchbowl is the crater in the centre.

        The color_scheme option allows you to select a series of colour schemes.
        0: The default, a lookup using a "Brewer" palette.
        1: The original: A lookup table of 256 colours ranging from deep blue (water) to yellow-white (mountain top).
        2: A lookup table with a preset number of colours.

   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='honolulu.vtk.')
    parser.add_argument('color_scheme', default=0, type=int, nargs='?', help='The particular color scheme to use.')
    args = parser.parse_args()
    return args.filename, args.color_scheme


def MakeLUT(color_scheme=0):
    """
    Make a lookup table.
    :param color_scheme: Select the type of lookup table.
    :return: The lookup table.
    """
    colors = vtk.vtkNamedColors()
    if color_scheme == 1:
        # A lookup table of 256 colours ranging from
        #  deep blue (water) to yellow-white (mountain top)
        #  is used to color map this figure.
        lut = vtk.vtkLookupTable()
        lut.SetHueRange(0.7, 0)
        lut.SetSaturationRange(1.0, 0)
        lut.SetValueRange(0.5, 1.0)
    elif color_scheme == 2:
        # Make the lookup table with a preset number of colours.
        colorSeries = vtk.vtkColorSeries()
        colorSeries.SetNumberOfColors(8)
        colorSeries.SetColorSchemeName('Hawaii')
        colorSeries.SetColor(0, colors.GetColor3ub("turquoise_blue"))
        colorSeries.SetColor(1, colors.GetColor3ub("sea_green_medium"))
        colorSeries.SetColor(2, colors.GetColor3ub("sap_green"))
        colorSeries.SetColor(3, colors.GetColor3ub("green_dark"))
        colorSeries.SetColor(4, colors.GetColor3ub("tan"))
        colorSeries.SetColor(5, colors.GetColor3ub("beige"))
        colorSeries.SetColor(6, colors.GetColor3ub("light_beige"))
        colorSeries.SetColor(7, colors.GetColor3ub("bisque"))
        lut = vtk.vtkLookupTable()
        colorSeries.BuildLookupTable(lut, colorSeries.ORDINAL)
        lut.SetNanColor(1, 0, 0, 1)
    else:
        # Make the lookup using a Brewer palette.
        colorSeries = vtk.vtkColorSeries()
        colorSeries.SetNumberOfColors(8)
        colorSeriesEnum = colorSeries.BREWER_DIVERGING_BROWN_BLUE_GREEN_8
        colorSeries.SetColorScheme(colorSeriesEnum)
        lut = vtk.vtkLookupTable()
        colorSeries.BuildLookupTable(lut, colorSeries.ORDINAL)
        lut.SetNanColor(1, 0, 0, 1)
    return lut


if __name__ == '__main__':
    main()
