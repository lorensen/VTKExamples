#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import print_function

import vtk

nc = vtk.vtkNamedColors()


def GetProgramParameters():
    import argparse
    description = 'Demonstrates point data subdivision with the glyphing of normals on the surface.'
    epilogue = '''
        This program takes a surface and displays three surfaces.

        The first surface is the original surface and the second and third surfaces have
         had linear and butterfly interpolation applied respectively.
        The user can control the object to use, normal generation, type of shading
         and number of points to use for the normals.
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('sourceToUse', help='The surface to use.', nargs='?', default='Cone')
    parser.add_argument('-g', '--glyphPoints', help='Number of points to be used for glyphing.', nargs='?', default=50,
                        type=int)
    parser.add_argument('--no-normals', help='Do not display normals.', dest='displayNormals', action='store_false')
    parser.add_argument('--no-gouraud', help='Use flat interpolation. Gouraud interpolation is used by default.',
                        dest='gouraudInterpolation', action='store_false')
    parser.set_defaults(displayNormals=True)
    parser.set_defaults(gouraudInterpolation=True)
    args = parser.parse_args()
    return args.sourceToUse, args.displayNormals, args.gouraudInterpolation, args.glyphPoints


class Sources(object):
    """
    This class acts as a storage vehicle for the various sources.

    If you add more sources, you may need to provide one or all of these filters:
     - A Triangle filter
     - A Normal filter
     - An elevation filter.
     - A CleanPolyData filter.
     - For parametric sources, we may need to apply one of both of JoinUOff() or JoinVOff().

    Use the representative sources provided here as templates.
    """

    def __init__(self):
        # If you add more sources update this dictionary.
        self.sources = {'ParametricTorus': self.ParametricTorusSource(), 'ParametricEllipsoid': self.EllipsoidSource(),
                        'Boy': self.BoySource(), 'Sphere': self.SphereSource(), 'Mobius': self.MobiusSource(),
                        'Cone': self.ConeSource(), 'RandomHills': self.ParametricRandomHills(),
                        'Superquadric': self.SuperquadricSource()}

    @staticmethod
    def ParametricTorusSource():
        torus = vtk.vtkParametricTorus()
        torus.JoinUOff()
        torus.JoinVOff()
        torusSource = vtk.vtkParametricFunctionSource()
        torusSource.SetParametricFunction(torus)
        torusSource.SetScalarModeToZ()
        return torusSource

    @staticmethod
    def EllipsoidSource():
        ellipsoid = vtk.vtkParametricEllipsoid()
        ellipsoid.SetXRadius(0.5)
        ellipsoid.SetYRadius(1.0)
        ellipsoid.SetZRadius(2.0)
        ellipsoid.JoinUOff()
        # ellipsoid.JoinVOff()
        ellipsoidSource = vtk.vtkParametricFunctionSource()
        ellipsoidSource.SetParametricFunction(ellipsoid)
        ellipsoidSource.SetScalarModeToZ()
        return ellipsoidSource

    @staticmethod
    def BoySource():
        boy = vtk.vtkParametricBoy()
        boy.JoinUOff()
        # boy.JoinVOff()
        boySource = vtk.vtkParametricFunctionSource()
        boySource.SetParametricFunction(boy)
        boySource.SetScalarModeToZ()
        return boySource

    @staticmethod
    def MobiusSource():
        mobius = vtk.vtkParametricMobius()
        mobius.SetRadius(2)
        mobius.SetMinimumV(-0.5)
        mobius.SetMaximumV(0.5)
        mobius.JoinUOff()
        mobiusSource = vtk.vtkParametricFunctionSource()
        mobiusSource.SetParametricFunction(mobius)
        mobiusSource.SetScalarModeToX()
        return mobiusSource

    @staticmethod
    def ParametricRandomHills():
        randomHills = vtk.vtkParametricRandomHills()
        # randomHills.AllowRandomGenerationOff()
        randomHills.SetRandomSeed(1)
        randomHills.SetNumberOfHills(30)
        randomHillsSource = vtk.vtkParametricFunctionSource()
        randomHillsSource.SetParametricFunction(randomHills)
        randomHillsSource.SetScalarModeToZ()
        randomHillsSource.SetUResolution(10)
        randomHillsSource.SetVResolution(10)
        return randomHillsSource

    @staticmethod
    def SphereSource():
        sphere = vtk.vtkSphereSource()
        sphere.SetPhiResolution(11)
        sphere.SetThetaResolution(11)
        sphere.Update()
        sphereBounds = sphere.GetOutput().GetBounds()

        elev = vtk.vtkElevationFilter()
        elev.SetInputConnection(sphere.GetOutputPort())
        elev.SetLowPoint(0, sphereBounds[2], 0)
        elev.SetHighPoint(0, sphereBounds[3], 0)
        elev.Update()
        return elev

    @staticmethod
    def SuperquadricSource():
        """
        Make a torus as the source.
        """
        source = vtk.vtkSuperquadricSource()
        source.SetCenter(0.0, 0.0, 0.0)
        source.SetScale(1.0, 1.0, 1.0)
        source.SetPhiResolution(64)
        source.SetThetaResolution(64)
        source.SetThetaRoundness(1)
        source.SetThickness(0.5)
        source.SetSize(10)
        source.SetToroidal(1)

        # The quadric is made of strips, so pass it through a triangle filter as
        # the curvature filter only operates on polys
        tri = vtk.vtkTriangleFilter()
        tri.SetInputConnection(source.GetOutputPort())

        # The quadric has nasty discontinuities from the way the edges are generated
        # so let's pass it though a CleanPolyDataFilter and merge any points which
        # are coincident, or very close
        cleaner = vtk.vtkCleanPolyData()
        cleaner.SetInputConnection(tri.GetOutputPort())
        cleaner.SetTolerance(0.005)
        cleaner.Update()
        cleanerBounds = cleaner.GetOutput().GetBounds()

        elev = vtk.vtkElevationFilter()
        elev.SetInputConnection(cleaner.GetOutputPort())
        elev.SetLowPoint(0, cleanerBounds[2], 0)
        elev.SetHighPoint(0, cleanerBounds[3], 0)
        elev.Update()
        return elev

    @staticmethod
    def ConeSource():
        cone = vtk.vtkConeSource()
        cone.SetResolution(6)
        cone.CappingOn()
        cone.Update()
        coneBounds = cone.GetOutput().GetBounds()

        coneNormals = vtk.vtkPolyDataNormals()
        coneNormals.SetInputConnection(cone.GetOutputPort())

        elev = vtk.vtkElevationFilter()
        elev.SetInputConnection(coneNormals.GetOutputPort())
        elev.SetLowPoint(coneBounds[0], 0, 0)
        elev.SetHighPoint(coneBounds[1], 0, 0)

        # vtkButterflySubdivisionFilter and vtkLinearSubdivisionFilter operate on triangles.
        tf = vtk.vtkTriangleFilter()
        tf.SetInputConnection(elev.GetOutputPort())
        tf.Update()
        return tf


def MakeLUT(scalarRange):
    """
    Make a lookup table using a predefined color series.

    :param scalarRange: The range of the scalars to be coloured.
    :return:  A lookup table.
    """
    colorSeries = vtk.vtkColorSeries()
    # Select a color scheme.
    # for i in range(0,62):
    #     colorSeries.SetColorScheme(i)
    #     print('Colour scheme {:2d}: {:s}'.format(colorSeries.GetColorScheme(), colorSeries.GetColorSchemeName()))

    # Colour scheme 61: Brewer Qualitative Set3
    colorSeries.SetColorScheme(61)
    # We use this colour series to create the transfer function.
    lut = vtk.vtkColorTransferFunction()
    lut.SetColorSpaceToHSV()
    numColors = colorSeries.GetNumberOfColors()
    for i in range(0, numColors):
        color = vtk.vtkColor3ub(colorSeries.GetColor(i))
        c = list()
        for j in range(0, 3):
            c.append(color[j] / 255.0)
        t = scalarRange[0] + (scalarRange[1] - scalarRange[0]) / (numColors - 1) * i
        lut.AddRGBPoint(t, *c)
    return lut


def GlyphActor(source, glyphPoints, scalarRange, scaleFactor, lut):
    """
    Create the actor for glyphing the normals.

    :param: source: the surface.
    :param: glyphPoints: The number of points used by the mask filter.
    :param: scalarRange: The range in terms of scalar minimum and maximum.
    :param: scaleFactor: The scaling factor for the glyph.
    :param: lut: The lookup table to use.

    :return: The glyph actor.
    """
    arrowSource = vtk.vtkArrowSource()
    # Subsample the dataset.
    maskPts = vtk.vtkMaskPoints()
    maskPts.SetInputConnection(source.GetOutputPort())
    maskPts.SetOnRatio(source.GetOutput().GetNumberOfPoints() // glyphPoints)
    maskPts.SetRandomMode(1)

    arrowGlyph = vtk.vtkGlyph3D()
    arrowGlyph.SetScaleFactor(scaleFactor)
    arrowGlyph.SetVectorModeToUseNormal()
    arrowGlyph.SetColorModeToColorByScalar()
    arrowGlyph.SetScaleModeToScaleByVector()
    arrowGlyph.OrientOn()
    arrowGlyph.SetSourceConnection(arrowSource.GetOutputPort())
    arrowGlyph.SetInputConnection(maskPts.GetOutputPort())
    arrowGlyph.Update()

    arrowGlyphMapper = vtk.vtkDataSetMapper()
    # Colour by scalars.
    arrowGlyphMapper.SetScalarRange(scalarRange)
    arrowGlyphMapper.SetColorModeToMapScalars()
    arrowGlyphMapper.ScalarVisibilityOn()
    arrowGlyphMapper.SetLookupTable(lut)
    arrowGlyphMapper.SetInputConnection(arrowGlyph.GetOutputPort())

    glyphActor = vtk.vtkActor()
    glyphActor.SetMapper(arrowGlyphMapper)
    return glyphActor


def MakeSurfaceActor(surface, scalarRange, lut):
    """
    Create the actor for a surface.

    :param: surface: The surface.
    :param: scalarRange: The range in terms of scalar minimum and maximum.
    :param: lut: The lookup table to use.

    :return: The actor for the surface.
    """
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(surface.GetOutputPort())
    mapper.SetLookupTable(lut)
    mapper.SetScalarRange(scalarRange)
    mapper.SetColorModeToMapScalars()
    mapper.ScalarVisibilityOn()
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    return actor


def MakeLabel(textLabel, renWinSize):
    """
    Create a label.

    :param textLabel: The label.
    :param renWinSize: The size of the render window. Used to set the font size.

    :return: The actor for the text label.
    """
    # Create one text property for all
    textProperty = vtk.vtkTextProperty()
    textProperty.SetJustificationToCentered()
    textProperty.SetFontSize(int(renWinSize / 20))

    mapper = vtk.vtkTextMapper()
    mapper.SetInput(textLabel)
    mapper.SetTextProperty(textProperty)

    actor = vtk.vtkActor2D()
    actor.SetMapper(mapper)
    actor.SetPosition(renWinSize / 2.0, 16)
    return actor


def MakeAxesActor():
    """
    Make an axis actor.

    :return: The axis actor.
    """
    axes = vtk.vtkAxesActor()
    axes.SetShaftTypeToCylinder()
    axes.SetXAxisLabelText('X')
    axes.SetYAxisLabelText('Y')
    axes.SetZAxisLabelText('Z')
    axes.SetTotalLength(1.0, 1.0, 1.0)
    axes.SetCylinderRadius(1.0 * axes.GetCylinderRadius())
    axes.SetConeRadius(1.75 * axes.GetConeRadius())
    axes.SetSphereRadius(1.0 * axes.GetSphereRadius())
    axes.GetXAxisCaptionActor2D().GetTextActor().GetScaledTextProperty()
    axes.GetXAxisCaptionActor2D().GetTextActor().SetTextScaleModeToNone()
    axes.GetYAxisCaptionActor2D().GetTextActor().GetScaledTextProperty()
    axes.GetYAxisCaptionActor2D().GetTextActor().SetTextScaleModeToNone()
    axes.GetZAxisCaptionActor2D().GetTextActor().GetScaledTextProperty()
    axes.GetZAxisCaptionActor2D().GetTextActor().SetTextScaleModeToNone()
    return axes


def MakeOrientationMarker(renderer, iren):
    """
    Create an orientation marker for a given renderer.

    :param renderer: The renderer.
    :param iren: The interactor.

    :return: The orientation marker.
    """
    om = vtk.vtkOrientationMarkerWidget()
    om.SetOrientationMarker(MakeAxesActor())
    # Position lower left in the viewport.
    om.SetViewport(0, 0, 0.2, 0.2)
    om.SetInteractor(iren)
    om.SetDefaultRenderer(renderer)
    om.EnabledOn()
    om.InteractiveOn()
    renderer.ResetCamera()
    return om


def WritePNG(ren, fn, magnification=1):
    """
    Save the image as a PNG
    :param: ren - the renderer.
    :param: fn - the file name.
    :param: magnification - the magnification, usually 1.
    """
    renLgeIm = vtk.vtkRenderLargeImage()
    renLgeIm.SetInput(ren)
    renLgeIm.SetMagnification(magnification)
    imgWriter = vtk.vtkPNGWriter()
    imgWriter.SetInputConnection(renLgeIm.GetOutputPort())
    imgWriter.SetFileName(fn)
    imgWriter.Write()


def main():
    def FlatInterpolation():
        for actor in actors:
            actor.GetProperty().SetInterpolationToFlat()
        renWin.Render()

    def GouraudInterpolation():
        for actor in actors:
            actor.GetProperty().SetInterpolationToGouraud()
        renWin.Render()

    sourceToUse, displayNormals, gouraudInterpolation, glyphPoints = GetProgramParameters()

    if sourceToUse in Sources().sources:
        src = Sources().sources[sourceToUse]
    else:
        print('The source {:s} is not available.'.format(sourceToUse))
        print('Available sources are:\n', ', '.join(sorted(list(Sources().sources.keys()))))
        return

    src.Update()

    # The size of the render window.
    renWinXSize = 1200
    renWinYSize = renWinXSize // 3
    minRenWinDim = min(renWinXSize, renWinYSize)

    # [xMin, xMax, yMin, yMax, zMin, zMax]
    bounds = src.GetOutput().GetBounds()
    # Use this to scale the normal glyph.
    scaleFactor = min(map(lambda x, y: x - y, bounds[1::2], bounds[::2])) * 0.2
    src.GetOutput().GetPointData().GetScalars().SetName("Elevation")
    scalarRange = src.GetOutput().GetScalarRange()

    butterfly = vtk.vtkButterflySubdivisionFilter()
    butterfly.SetInputConnection(src.GetOutputPort())
    butterfly.SetNumberOfSubdivisions(3)
    butterfly.Update()

    linear = vtk.vtkLinearSubdivisionFilter()
    linear.SetInputConnection(src.GetOutputPort())
    linear.SetNumberOfSubdivisions(3)
    linear.Update()

    lut = MakeLUT(scalarRange)

    actors = list()
    actors.append(MakeSurfaceActor(butterfly, scalarRange, lut))
    actors.append(MakeSurfaceActor(linear, scalarRange, lut))
    actors.append(MakeSurfaceActor(src, scalarRange, lut))

    # Let's visualise the normals.
    glyphActors = list()
    if displayNormals:
        glyphActors.append(GlyphActor(butterfly, glyphPoints, scalarRange, scaleFactor, lut))
        glyphActors.append(GlyphActor(linear, glyphPoints, scalarRange, scaleFactor, lut))
        glyphActors.append(GlyphActor(src, glyphPoints, scalarRange, scaleFactor, lut))

    labelActors = list()
    labelActors.append(MakeLabel('Butterfly Subdivision', minRenWinDim))
    labelActors.append(MakeLabel('Linear Subdivision', minRenWinDim))
    labelActors.append(MakeLabel('Original', minRenWinDim))

    ren = list()
    ren.append(vtk.vtkRenderer())
    ren.append(vtk.vtkRenderer())
    ren.append(vtk.vtkRenderer())
    ren[2].SetViewport(0, 0, 1.0 / 3.0, 1)  # Original
    ren[1].SetViewport(1.0 / 3.0, 0, 2.0 / 3.0, 1)  # Linear
    ren[0].SetViewport(2.0 / 3.0, 0, 1, 1)  # Butterfly

    renWin = vtk.vtkRenderWindow()
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Orientation markers.
    om = list()
    # Make the imaging pipelines.
    for i in range(0, len(ren)):
        renWin.AddRenderer(ren[i])

        ren[i].AddActor(actors[i])
        ren[i].AddActor(labelActors[i])
        ren[i].SetBackground(nc.GetColor3d('SlateGray'))

        if displayNormals:
            ren[i].AddActor(glyphActors[i])

        om.append(MakeOrientationMarker(ren[i], iren))

    if gouraudInterpolation:
        GouraudInterpolation()
    else:
        FlatInterpolation()

    renWin.SetSize(renWinXSize, renWinYSize)
    renWin.Render()
    # renWin.SetWindowName() needs to be called after renWin.Render()
    renWin.SetWindowName('Point Data Subdivision Example')

    iren.Initialize()
    # WritePNG(iren.GetRenderWindow().GetRenderers().GetFirstRenderer(), "TestPointDataSubdivision.png")
    iren.Start()


if __name__ == '__main__':
    requiredMajorVersion = 6
    # print(vtk.vtkVersion().GetVTKMajorVersion())
    if vtk.vtkVersion().GetVTKMajorVersion() < requiredMajorVersion:
        print("You need VTK Version 6 or greater.")
        print("The class vtkNamedColors is in VTK version 6 or greater.")
        exit(0)

    main()
