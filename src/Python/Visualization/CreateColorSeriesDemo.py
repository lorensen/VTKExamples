#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'how to create a custom vtkColorSeries.'
    epilogue = '''
A vtkLookupTable is explicitly produced, it is populated with colors from the vtkColorSeries
   using GetColorRepeating, since the size of the vtkLookupTable may be larger than the
   colors in the vtkColorSeries.
   
Nine different color series are generated from VTK color names in vtkNamedColors.
Choose from one of: Blue, Brown, Red, Orange, White, Grey, Magenta, Cyan, and Yellow.
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('seriesName', default='Red', nargs='?',
                        help='The name of the color series to use (default is Red).')
    args = parser.parse_args()
    return args.seriesName


def CreateLookupTableVTKBlue(size):
    nc = vtk.vtkNamedColors()
    myColors = vtk.vtkColorSeries()
    myColors.SetColorSchemeByName('VTKBlueColors')

    myColors.AddColor(nc.GetColor3ub('alice_blue'))
    myColors.AddColor(nc.GetColor3ub('blue'))
    myColors.AddColor(nc.GetColor3ub('blue_light'))
    myColors.AddColor(nc.GetColor3ub('blue_medium'))
    myColors.AddColor(nc.GetColor3ub('cadet'))
    myColors.AddColor(nc.GetColor3ub('cobalt'))
    myColors.AddColor(nc.GetColor3ub('cornflower'))
    myColors.AddColor(nc.GetColor3ub('cerulean'))
    myColors.AddColor(nc.GetColor3ub('dodger_blue'))
    myColors.AddColor(nc.GetColor3ub('indigo'))
    myColors.AddColor(nc.GetColor3ub('manganese_blue'))
    myColors.AddColor(nc.GetColor3ub('midnight_blue'))
    myColors.AddColor(nc.GetColor3ub('navy'))
    myColors.AddColor(nc.GetColor3ub('peacock'))
    myColors.AddColor(nc.GetColor3ub('powder_blue'))
    myColors.AddColor(nc.GetColor3ub('royal_blue'))
    myColors.AddColor(nc.GetColor3ub('slate_blue'))
    myColors.AddColor(nc.GetColor3ub('slate_blue_dark'))
    myColors.AddColor(nc.GetColor3ub('slate_blue_light'))
    myColors.AddColor(nc.GetColor3ub('slate_blue_medium'))
    myColors.AddColor(nc.GetColor3ub('sky_blue'))
    myColors.AddColor(nc.GetColor3ub('sky_blue_deep'))
    myColors.AddColor(nc.GetColor3ub('sky_blue_light'))
    myColors.AddColor(nc.GetColor3ub('steel_blue'))
    myColors.AddColor(nc.GetColor3ub('steel_blue_light'))
    myColors.AddColor(nc.GetColor3ub('turquoise_blue'))
    myColors.AddColor(nc.GetColor3ub('ultramarine'))

    numberOfColors = myColors.GetNumberOfColors()
    print('Number of colors:', numberOfColors)

    lut = vtk.vtkLookupTable()
    if size == 0:
        lut.SetNumberOfTableValues(numberOfColors)
    else:
        lut.SetNumberOfTableValues(size)
    lut.SetTableRange(0, lut.GetNumberOfTableValues())
    for i in range(lut.GetNumberOfTableValues()):
        color = myColors.GetColorRepeating(i)
        c = [color.GetRed(), color.GetGreen(), color.GetBlue(), 255]
        lut.SetTableValue(i, [x / 255.0 for x in c])
    return lut


def CreateLookupTableVTKBrown(size):
    nc = vtk.vtkNamedColors()
    myColors = vtk.vtkColorSeries()
    myColors.SetColorSchemeByName('VTKBrownColors')

    myColors.AddColor(nc.GetColor3ub('beige'))
    myColors.AddColor(nc.GetColor3ub('brown'))
    myColors.AddColor(nc.GetColor3ub('brown_madder'))
    myColors.AddColor(nc.GetColor3ub('brown_ochre'))
    myColors.AddColor(nc.GetColor3ub('burlywood'))
    myColors.AddColor(nc.GetColor3ub('burnt_sienna'))
    myColors.AddColor(nc.GetColor3ub('burnt_umber'))
    myColors.AddColor(nc.GetColor3ub('chocolate'))
    myColors.AddColor(nc.GetColor3ub('deep_ochre'))
    myColors.AddColor(nc.GetColor3ub('flesh'))
    myColors.AddColor(nc.GetColor3ub('flesh_ochre'))
    myColors.AddColor(nc.GetColor3ub('gold_ochre'))
    myColors.AddColor(nc.GetColor3ub('greenish_umber'))
    myColors.AddColor(nc.GetColor3ub('khaki'))
    myColors.AddColor(nc.GetColor3ub('khaki_dark'))
    myColors.AddColor(nc.GetColor3ub('light_beige'))
    myColors.AddColor(nc.GetColor3ub('peru'))
    myColors.AddColor(nc.GetColor3ub('rosy_brown'))
    myColors.AddColor(nc.GetColor3ub('raw_sienna'))
    myColors.AddColor(nc.GetColor3ub('raw_umber'))
    myColors.AddColor(nc.GetColor3ub('sepia'))
    myColors.AddColor(nc.GetColor3ub('sienna'))
    myColors.AddColor(nc.GetColor3ub('saddle_brown'))
    myColors.AddColor(nc.GetColor3ub('sandy_brown'))
    myColors.AddColor(nc.GetColor3ub('tan'))
    myColors.AddColor(nc.GetColor3ub('van_dyke_brown'))

    numberOfColors = myColors.GetNumberOfColors()
    print('Number of colors:', numberOfColors)

    lut = vtk.vtkLookupTable()
    if size == 0:
        lut.SetNumberOfTableValues(numberOfColors)
    else:
        lut.SetNumberOfTableValues(size)
    lut.SetTableRange(0, lut.GetNumberOfTableValues())
    for i in range(lut.GetNumberOfTableValues()):
        color = myColors.GetColorRepeating(i)
        c = [color.GetRed(), color.GetGreen(), color.GetBlue(), 255]
        lut.SetTableValue(i, [x / 255.0 for x in c])
    return lut


def CreateLookupTableVTKRed(size):
    nc = vtk.vtkNamedColors()
    myColors = vtk.vtkColorSeries()
    myColors.SetColorSchemeByName('VTKRedColors')

    myColors.AddColor(nc.GetColor3ub('alizarin_crimson'))
    myColors.AddColor(nc.GetColor3ub('brick'))
    myColors.AddColor(nc.GetColor3ub('cadmium_red_deep'))
    myColors.AddColor(nc.GetColor3ub('coral'))
    myColors.AddColor(nc.GetColor3ub('coral_light'))
    myColors.AddColor(nc.GetColor3ub('deep_pink'))
    myColors.AddColor(nc.GetColor3ub('english_red'))
    myColors.AddColor(nc.GetColor3ub('firebrick'))
    myColors.AddColor(nc.GetColor3ub('geranium_lake'))
    myColors.AddColor(nc.GetColor3ub('hot_pink'))
    myColors.AddColor(nc.GetColor3ub('indian_red'))
    myColors.AddColor(nc.GetColor3ub('light_salmon'))
    myColors.AddColor(nc.GetColor3ub('madder_lake_deep'))
    myColors.AddColor(nc.GetColor3ub('maroon'))
    myColors.AddColor(nc.GetColor3ub('pink'))
    myColors.AddColor(nc.GetColor3ub('pink_light'))
    myColors.AddColor(nc.GetColor3ub('raspberry'))
    myColors.AddColor(nc.GetColor3ub('red'))
    myColors.AddColor(nc.GetColor3ub('rose_madder'))
    myColors.AddColor(nc.GetColor3ub('salmon'))
    myColors.AddColor(nc.GetColor3ub('tomato'))
    myColors.AddColor(nc.GetColor3ub('venetian_red'))

    numberOfColors = myColors.GetNumberOfColors()
    print('Number of colors:', numberOfColors)

    lut = vtk.vtkLookupTable()
    if size == 0:
        lut.SetNumberOfTableValues(numberOfColors)
    else:
        lut.SetNumberOfTableValues(size)
    lut.SetTableRange(0, lut.GetNumberOfTableValues())
    for i in range(lut.GetNumberOfTableValues()):
        color = myColors.GetColorRepeating(i)
        c = [color.GetRed(), color.GetGreen(), color.GetBlue(), 255]
        lut.SetTableValue(i, [x / 255.0 for x in c])
    return lut


def CreateLookupTableVTKOrange(size):
    nc = vtk.vtkNamedColors()
    myColors = vtk.vtkColorSeries()
    myColors.SetColorSchemeByName('VTKOrangeColors')

    myColors.AddColor(nc.GetColor3ub('cadmium_orange'))
    myColors.AddColor(nc.GetColor3ub('cadmium_red_light'))
    myColors.AddColor(nc.GetColor3ub('carrot'))
    myColors.AddColor(nc.GetColor3ub('dark_orange'))
    myColors.AddColor(nc.GetColor3ub('mars_orange'))
    myColors.AddColor(nc.GetColor3ub('mars_yellow'))
    myColors.AddColor(nc.GetColor3ub('orange'))
    myColors.AddColor(nc.GetColor3ub('orange_red'))
    myColors.AddColor(nc.GetColor3ub('yellow_ochre'))

    numberOfColors = myColors.GetNumberOfColors()
    print('Number of colors:', numberOfColors)

    lut = vtk.vtkLookupTable()
    if size == 0:
        lut.SetNumberOfTableValues(numberOfColors)
    else:
        lut.SetNumberOfTableValues(size)
    lut.SetTableRange(0, lut.GetNumberOfTableValues())
    for i in range(lut.GetNumberOfTableValues()):
        color = myColors.GetColorRepeating(i)
        c = [color.GetRed(), color.GetGreen(), color.GetBlue(), 255]
        lut.SetTableValue(i, [x / 255.0 for x in c])
    return lut


def CreateLookupTableVTKWhite(size):
    nc = vtk.vtkNamedColors()
    myColors = vtk.vtkColorSeries()
    myColors.SetColorSchemeByName('VTKWhiteColors')

    myColors.AddColor(nc.GetColor3ub('antique_white'))
    myColors.AddColor(nc.GetColor3ub('azure'))
    myColors.AddColor(nc.GetColor3ub('bisque'))
    myColors.AddColor(nc.GetColor3ub('blanched_almond'))
    myColors.AddColor(nc.GetColor3ub('cornsilk'))
    myColors.AddColor(nc.GetColor3ub('eggshell'))
    myColors.AddColor(nc.GetColor3ub('floral_white'))
    myColors.AddColor(nc.GetColor3ub('gainsboro'))
    myColors.AddColor(nc.GetColor3ub('ghost_white'))
    myColors.AddColor(nc.GetColor3ub('honeydew'))
    myColors.AddColor(nc.GetColor3ub('ivory'))
    myColors.AddColor(nc.GetColor3ub('lavender'))
    myColors.AddColor(nc.GetColor3ub('lavender_blush'))
    myColors.AddColor(nc.GetColor3ub('lemon_chiffon'))
    myColors.AddColor(nc.GetColor3ub('linen'))
    myColors.AddColor(nc.GetColor3ub('mint_cream'))
    myColors.AddColor(nc.GetColor3ub('misty_rose'))
    myColors.AddColor(nc.GetColor3ub('moccasin'))
    myColors.AddColor(nc.GetColor3ub('navajo_white'))
    myColors.AddColor(nc.GetColor3ub('old_lace'))
    myColors.AddColor(nc.GetColor3ub('papaya_whip'))
    myColors.AddColor(nc.GetColor3ub('peach_puff'))
    myColors.AddColor(nc.GetColor3ub('seashell'))
    myColors.AddColor(nc.GetColor3ub('snow'))
    myColors.AddColor(nc.GetColor3ub('thistle'))
    myColors.AddColor(nc.GetColor3ub('titanium_white'))
    myColors.AddColor(nc.GetColor3ub('wheat'))
    myColors.AddColor(nc.GetColor3ub('white'))
    myColors.AddColor(nc.GetColor3ub('white_smoke'))
    myColors.AddColor(nc.GetColor3ub('zinc_white'))

    numberOfColors = myColors.GetNumberOfColors()
    print('Number of colors:', numberOfColors)

    lut = vtk.vtkLookupTable()
    if size == 0:
        lut.SetNumberOfTableValues(numberOfColors)
    else:
        lut.SetNumberOfTableValues(size)
    lut.SetTableRange(0, lut.GetNumberOfTableValues())
    for i in range(lut.GetNumberOfTableValues()):
        color = myColors.GetColorRepeating(i)
        c = [color.GetRed(), color.GetGreen(), color.GetBlue(), 255]
        lut.SetTableValue(i, [x / 255.0 for x in c])
    return lut


def CreateLookupTableVTKGrey(size):
    nc = vtk.vtkNamedColors()
    myColors = vtk.vtkColorSeries()
    myColors.SetColorSchemeByName('VTKGreyColors')

    myColors.AddColor(nc.GetColor3ub('cold_grey'))
    myColors.AddColor(nc.GetColor3ub('dim_grey'))
    myColors.AddColor(nc.GetColor3ub('grey'))
    myColors.AddColor(nc.GetColor3ub('light_grey'))
    myColors.AddColor(nc.GetColor3ub('slate_grey'))
    myColors.AddColor(nc.GetColor3ub('slate_grey_dark'))
    myColors.AddColor(nc.GetColor3ub('slate_grey_light'))
    myColors.AddColor(nc.GetColor3ub('warm_grey'))

    numberOfColors = myColors.GetNumberOfColors()
    print('Number of colors:', numberOfColors)

    lut = vtk.vtkLookupTable()
    if size == 0:
        lut.SetNumberOfTableValues(numberOfColors)
    else:
        lut.SetNumberOfTableValues(size)
    lut.SetTableRange(0, lut.GetNumberOfTableValues())
    for i in range(lut.GetNumberOfTableValues()):
        color = myColors.GetColorRepeating(i)
        c = [color.GetRed(), color.GetGreen(), color.GetBlue(), 255]
        lut.SetTableValue(i, [x / 255.0 for x in c])
    return lut


def CreateLookupTableVTKMagenta(size):
    nc = vtk.vtkNamedColors()
    myColors = vtk.vtkColorSeries()
    myColors.SetColorSchemeByName('VTKMagentaColors')

    myColors.AddColor(nc.GetColor3ub('blue_violet'))
    myColors.AddColor(nc.GetColor3ub('cobalt_violet_deep'))
    myColors.AddColor(nc.GetColor3ub('magenta'))
    myColors.AddColor(nc.GetColor3ub('orchid'))
    myColors.AddColor(nc.GetColor3ub('orchid_dark'))
    myColors.AddColor(nc.GetColor3ub('orchid_medium'))
    myColors.AddColor(nc.GetColor3ub('permanent_red_violet'))
    myColors.AddColor(nc.GetColor3ub('plum'))
    myColors.AddColor(nc.GetColor3ub('purple'))
    myColors.AddColor(nc.GetColor3ub('purple_medium'))
    myColors.AddColor(nc.GetColor3ub('ultramarine_violet'))
    myColors.AddColor(nc.GetColor3ub('violet'))
    myColors.AddColor(nc.GetColor3ub('violet_dark'))
    myColors.AddColor(nc.GetColor3ub('violet_red'))
    myColors.AddColor(nc.GetColor3ub('violet_red_medium'))
    myColors.AddColor(nc.GetColor3ub('violet_red_pale'))
    numberOfColors = myColors.GetNumberOfColors()
    print('Number of colors:', numberOfColors)

    lut = vtk.vtkLookupTable()
    if size == 0:
        lut.SetNumberOfTableValues(numberOfColors)
    else:
        lut.SetNumberOfTableValues(size)
    lut.SetTableRange(0, lut.GetNumberOfTableValues())
    for i in range(lut.GetNumberOfTableValues()):
        color = myColors.GetColorRepeating(i)
        c = [color.GetRed(), color.GetGreen(), color.GetBlue(), 255]
        lut.SetTableValue(i, [x / 255.0 for x in c])
    return lut


def CreateLookupTableVTKCyan(size):
    nc = vtk.vtkNamedColors()
    myColors = vtk.vtkColorSeries()
    myColors.SetColorSchemeByName('VTKCyanColors')

    myColors.AddColor(nc.GetColor3ub('aquamarine'))
    myColors.AddColor(nc.GetColor3ub('aquamarine_medium'))
    myColors.AddColor(nc.GetColor3ub('cyan'))
    myColors.AddColor(nc.GetColor3ub('cyan_white'))
    myColors.AddColor(nc.GetColor3ub('turquoise'))
    myColors.AddColor(nc.GetColor3ub('turquoise_dark'))
    myColors.AddColor(nc.GetColor3ub('turquoise_medium'))
    myColors.AddColor(nc.GetColor3ub('turquoise_pale'))

    numberOfColors = myColors.GetNumberOfColors()
    print('Number of colors:', numberOfColors)

    lut = vtk.vtkLookupTable()
    if size == 0:
        lut.SetNumberOfTableValues(numberOfColors)
    else:
        lut.SetNumberOfTableValues(size)
    lut.SetTableRange(0, lut.GetNumberOfTableValues())
    for i in range(lut.GetNumberOfTableValues()):
        color = myColors.GetColorRepeating(i)
        c = [color.GetRed(), color.GetGreen(), color.GetBlue(), 255]
        lut.SetTableValue(i, [x / 255.0 for x in c])
    return lut


def CreateLookupTableVTKYellow(size):
    nc = vtk.vtkNamedColors()
    myColors = vtk.vtkColorSeries()
    myColors.SetColorSchemeByName('VTKYellowColors')

    myColors.AddColor(nc.GetColor3ub('aureoline_yellow'))
    myColors.AddColor(nc.GetColor3ub('banana'))
    myColors.AddColor(nc.GetColor3ub('cadmium_lemon'))
    myColors.AddColor(nc.GetColor3ub('cadmium_yellow'))
    myColors.AddColor(nc.GetColor3ub('cadmium_yellow_light'))
    myColors.AddColor(nc.GetColor3ub('gold'))
    myColors.AddColor(nc.GetColor3ub('goldenrod'))
    myColors.AddColor(nc.GetColor3ub('goldenrod_dark'))
    myColors.AddColor(nc.GetColor3ub('goldenrod_light'))
    myColors.AddColor(nc.GetColor3ub('goldenrod_pale'))
    myColors.AddColor(nc.GetColor3ub('light_goldenrod'))
    myColors.AddColor(nc.GetColor3ub('melon'))
    myColors.AddColor(nc.GetColor3ub('naples_yellow_deep'))
    myColors.AddColor(nc.GetColor3ub('yellow'))
    myColors.AddColor(nc.GetColor3ub('yellow_light'))

    numberOfColors = myColors.GetNumberOfColors()
    print('Number of colors:', numberOfColors)

    lut = vtk.vtkLookupTable()
    if size == 0:
        lut.SetNumberOfTableValues(numberOfColors)
    else:
        lut.SetNumberOfTableValues(size)
    lut.SetTableRange(0, lut.GetNumberOfTableValues())
    for i in range(lut.GetNumberOfTableValues()):
        color = myColors.GetColorRepeating(i)
        c = [color.GetRed(), color.GetGreen(), color.GetBlue(), 255]
        lut.SetTableValue(i, [x / 255.0 for x in c])
    return lut


def main():
    seriesName = get_program_parameters()
    seriesName = seriesName.capitalize()
    available_color_series = ['Blue', 'Brown', 'Red', 'Orange', 'White', 'Grey', 'Magenta', 'Cyan', 'Yellow']
    if seriesName not in available_color_series:
        print('Available color maps are:',", ".join(available_color_series))
        return

    colors = vtk.vtkNamedColors()

    # Provide some geometry.
    xResolution = 6
    yResolution = 6
    aPlane = vtk.vtkPlaneSource()
    aPlane.SetXResolution(xResolution)
    aPlane.SetYResolution(yResolution)
    size = xResolution * yResolution + 1

    # Create cell data.
    cellData = vtk.vtkFloatArray()
    for i in range(0, xResolution * yResolution):
        cellData.InsertNextValue(i)
    aPlane.Update()  # Force an update so we can set cell data.
    aPlane.GetOutput().GetCellData().SetScalars(cellData)

    # Get the lookup table.
    lut = eval('CreateLookupTableVTK' + seriesName + '(size)')

    # Set up the actor and mapper.
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetLookupTable(lut)
    mapper.SetInputConnection(aPlane.GetOutputPort())
    mapper.SetScalarModeToUseCellData()
    mapper.SetScalarRange(0, size)

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().EdgeVisibilityOn()

    # Setup render window, renderer, and interactor.
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d('SlateGray'))
    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
