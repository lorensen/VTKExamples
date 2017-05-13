[VTKExamples](/index/)/[Python](/Python)/Visualization/ElevationBandsWithGlyphs

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestElevationBandsWithGlyphs.png?raw=true" width="256" />

### Description
In this example we are coloring the surface by partitioning the elevation
into bands and using arrows to display the normals on the surface.

Rather beautiful surfaces are generated.

The banded contour filter and an indexed lookup table are used along with 
the elevation filter to generate the banding on the surface.
To further enhance the surface the surface normals are
glyphed and colored by elevation using the default lookup table. 

The example also demonstrates partitioning the pipelines into functions.

For generating surfaces, the trick here is to return vtkPolydata for surfaces
thereby hiding the particular surface properties in the implementation of the
function. This allows us to specify multiple surface types and, in this code,
to use the name of the surface to pick the one we want.

The process is as follows:

1. Use an enum to select your surface.
2. Use vtkColorSeries to make an indexed lookup table.
3. Then we use the number of colors in the lookup table and the scalar range of the surface to create a list/vector of bands.
4. This list is then used to define the labels for the scalar bar using the midpoints of the ranges in the bands as the labels.
5. Once this is done, we annotate the lookup table and then create a reversed lookup table. This will be used by the scalar bar actor.
6. The maximum values in the ranges in the bands are used to set the bands in the banded contour filter.
7. Glyphs are then created for the normals.
8. Then everything is put together for the rendering in the usual actor/mapper pipeline. The reversed lookup table is used by the scalar bar actor so that the maximum value is at the top if the actor is placed in its default orientation/position.
9. The function Display() pulls together all the components and returns a vtkRenderWindowInteractor so that you can interact with the image.

Feel free to experiment with different color schemes and/or the other
sources from the parametric function group or a cone etc.

Note that in the function `MakeParametricSurface()` we use `ClockwiseOrderingOff()` when using vtkParametricRandomHills as a source,
this ensures that the normals face in the expected direction, the default is `ClockwiseOrderingOn()`.
As an alternative, in `MakeGlyphs()`, you can set reverseNormals to True thereby invoking vtkReverseSense to achieve the same effect.

You will usually need to adjust the parameters for maskPts,
arrow and glyph for a nice appearance.
Do this in the function `MakeGlyphs()`.

You may also need to add an elevation filter to generate the scalars
as demonstrated in `MakePlane()` and `MakeSphere()`.

`PrintBands()` and `PrintFrequencies()` allow you to inspect the bands and
the number of scalars in each band. These are useful if you want to
get an idea of the distribution of the scalars in each band.

**ElevationBandsWithGlyphs.py**
```python
#!/usr/bin/env python

from __future__ import print_function
import math
import vtk

# Available surfaces are:
SURFACE_TYPE = set(["PLANE",  "SPHERE", "PARAMETRIC_SURFACE"])

def WritePMG(ren, fn, magnification = 1):
    '''
    Save the image as a PNG
    :param: ren - the renderer.
    :param: fn - the file name.
    :param: magnification - the magnification, usually 1.
    '''
    renLgeIm = vtk.vtkRenderLargeImage()
    imgWriter = vtk.vtkPNGWriter()
    renLgeIm.SetInput(ren)
    renLgeIm.SetMagnification(magnification)
    imgWriter.SetInputConnection(renLgeIm.GetOutputPort())
    imgWriter.SetFileName(fn)
    imgWriter.Write()

def MakeBands(dR, numberOfBands, nearestInteger):
    '''
    Divide a range into bands
    :param: dR - [min, max] the range that is to be covered by the bands.
    :param: numberOfBands - the number of bands, a positive integer.
    :param: nearestInteger - if True then [floor(min), ceil(max)] is used.
    :return: A List consisting of [min, midpoint, max] for each band.
    '''
    bands = list()
    if (dR[1] < dR[0]) or (numberOfBands <= 0):
        return bands
    x = list(dR)
    if nearestInteger:
        x[0] = math.floor(x[0])
        x[1] = math.ceil(x[1])
    dx = (x[1] - x[0])/float(numberOfBands)
    b = [x[0], x[0] + dx / 2.0, x[0] + dx]
    i = 0
    while i < numberOfBands:
        bands.append(b)
        b = [b[0] + dx, b[1] + dx, b[2] + dx]
        i += 1
    return bands

def MakeIntegralBands(dR):
    '''
    Divide a range into integral bands
    :param: dR - [min, max] the range that is to be covered by the bands.
    :return: A List consisting of [min, midpoint, max] for each band.
    '''
    bands = list()
    if (dR[1] < dR[0]):
        return bands
    x = list(dR)
    x[0] = math.floor(x[0])
    x[1] = math.ceil(x[1])
    numberOfBands = int(abs(x[1]) + abs(x[0]))
    return MakeBands(x,numberOfBands, False)

def MakeElevations(src):
    '''
    Generate elevations over the surface.
    :param: src - the vtkPolyData source.
    :return: - vtkPolyData source with elevations.
    '''
    bounds = [ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 ]
    src.GetBounds(bounds)
    elevFilter = vtk.vtkElevationFilter()
    elevFilter.SetInputData(src)
    elevFilter.SetLowPoint(0, bounds[2], 0)
    elevFilter.SetHighPoint(0, bounds[3], 0)
    elevFilter.SetScalarRange(bounds[2], bounds[3])
    elevFilter.Update()
    return elevFilter.GetPolyDataOutput()


def MakePlane():
    '''
    Make a plane as the source.
    :return: vtkPolyData with normal and scalar data.
    '''
    source = vtk.vtkPlaneSource()
    source.SetOrigin(-10.0, -10.0, 0.0)
    source.SetPoint2(-10.0, 10.0, 0.0)
    source.SetPoint1(10.0, -10.0, 0.0)
    source.SetXResolution(20)
    source.SetYResolution(20)
    source.Update()
    return MakeElevations(source.GetOutput())

def MakeSphere():
    '''
    Make a sphere as the source.
    :return: vtkPolyData with normal and scalar data.
    '''
    source = vtk.vtkSphereSource()
    source.SetCenter(0.0, 0.0, 0.0)
    source.SetRadius(10.0)
    source.SetThetaResolution(32)
    source.SetPhiResolution(32)
    source.Update()
    return MakeElevations(source.GetOutput())

def MakeParametricSource():
    '''
    Make a parametric surface as the source.
    :return: vtkPolyData with normal and scalar data.
    '''
    fn = vtk.vtkParametricRandomHills()
    fn.AllowRandomGenerationOn()
    fn.SetRandomSeed(1)
    fn.SetNumberOfHills(30)
    if fn.GetClassName() == 'vtkParametricRandomHills':
        # Make the normals face out of the surface.
        fn.ClockwiseOrderingOff()

    source = vtk.vtkParametricFunctionSource()
    source.SetParametricFunction(fn)
    source.SetUResolution(50)
    source.SetVResolution(50)
    source.SetScalarModeToZ()
    source.Update()
    # Name the arrays (not needed in VTK 6.2+ for vtkParametricFunctionSource)
    source.GetOutput().GetPointData().GetNormals().SetName('Normals')
    source.GetOutput().GetPointData().GetScalars().SetName('Scalars')
    return source.GetOutput()

def MakeLUT():
    '''
    Make a lookup table using vtkColorSeries.
    :return: An indexed lookup table.
    '''
    # Make the lookup table.
    colorSeries = vtk.vtkColorSeries()
    # Select a color scheme.
    #colorSeriesEnum = colorSeries.BREWER_DIVERGING_BROWN_BLUE_GREEN_9
    #colorSeriesEnum = colorSeries.BREWER_DIVERGING_SPECTRAL_10
    #colorSeriesEnum = colorSeries.BREWER_DIVERGING_SPECTRAL_3
    #colorSeriesEnum = colorSeries.BREWER_DIVERGING_PURPLE_ORANGE_9
    #colorSeriesEnum = colorSeries.BREWER_SEQUENTIAL_BLUE_PURPLE_9
    #colorSeriesEnum = colorSeries.BREWER_SEQUENTIAL_BLUE_GREEN_9
    colorSeriesEnum = colorSeries.BREWER_QUALITATIVE_SET3
    #colorSeriesEnum = colorSeries.CITRUS
    colorSeries.SetColorScheme(colorSeriesEnum)
    lut = vtk.vtkLookupTable()
    colorSeries.BuildLookupTable(lut)
    lut.SetNanColor(1,0,0,1)
    return lut

def ReverseLUT(lut):
    '''
    Create a lookup table with the colors reversed.
    :param: lut - An indexed lookup table.
    :return: The reversed indexed lookup table.
    '''
    lutr = vtk.vtkLookupTable()
    lutr.DeepCopy(lut)
    t = lut.GetNumberOfTableValues() - 1
    revList = reversed(list(range(t + 1)))
    for i in revList:
        rgba = [0,0,0]
        v = float(i)
        lut.GetColor(v,rgba)
        rgba.append(lut.GetOpacity(v))
        lutr.SetTableValue(t - i,rgba)
    t = lut.GetNumberOfAnnotatedValues() - 1
    for i in revList:
        lutr.SetAnnotation(t - i, lut.GetAnnotation(i))
    return lutr

def Frequencies(bands, src):
    '''
    Count the number of scalars in each band.
    :param: bands - the bands.
    :param: src - the vtkPolyData source.
    :return: The frequencies of the scalars in each band.
    '''
    freq = dict()
    for i in range(len(bands)):
        freq[i] = 0;
    tuples = src.GetPointData().GetScalars().GetNumberOfTuples()
    for i in range(tuples):
        x = src.GetPointData().GetScalars().GetTuple1(i)
        for j in range(len(bands)):
            if x <= bands[j][2]:
                freq[j] = freq[j] + 1
                break
    return freq

def MakeGlyphs(src, reverseNormals):
    '''
    Glyph the normals on the surface.

    You may need to adjust the parameters for maskPts, arrow and glyph for a
    nice appearance.

    :param: src - the surface to glyph.
    :param: reverseNormals - if True the normals on the surface are reversed.
    :return: The glyph object.

    '''
    # Sometimes the contouring algorithm can create a volume whose gradient
    # vector and ordering of polygon (using the right hand rule) are
    # inconsistent. vtkReverseSense cures this problem.
    reverse = vtk.vtkReverseSense()

    # Choose a random subset of points.
    maskPts = vtk.vtkMaskPoints()
    maskPts.SetOnRatio(5)
    maskPts.RandomModeOn()
    if reverseNormals:
        reverse.SetInputData(src)
        reverse.ReverseCellsOn()
        reverse.ReverseNormalsOn()
        maskPts.SetInputConnection(reverse.GetOutputPort())
    else:
        maskPts.SetInputData(src)

    # Source for the glyph filter
    arrow = vtk.vtkArrowSource()
    arrow.SetTipResolution(16)
    arrow.SetTipLength(0.3)
    arrow.SetTipRadius(0.1)

    glyph = vtk.vtkGlyph3D()
    glyph.SetSourceConnection(arrow.GetOutputPort())
    glyph.SetInputConnection(maskPts.GetOutputPort())
    glyph.SetVectorModeToUseNormal()
    glyph.SetScaleFactor(1)
    glyph.SetColorModeToColorByVector()
    glyph.SetScaleModeToScaleByVector()
    glyph.OrientOn()
    glyph.Update()
    return glyph

def DisplaySurface(st):
    '''
    Make and display the surface.
    :param: st - the surface to display.
    :return The vtkRenderWindowInteractor.
    '''
    surface = st.upper()
    if  (not(surface in SURFACE_TYPE) ):
        print(st, "is not a surface.")
        iren = vtk.vtkRenderWindowInteractor()
        return iren
    # ------------------------------------------------------------
    # Create the surface, lookup tables, contour filter etc.
    # ------------------------------------------------------------
    src = vtk.vtkPolyData()
    if (surface == "PLANE"):
        src = MakePlane()
    elif (surface == "SPHERE"):
        src = MakeSphere()
    elif (surface == "PARAMETRIC_SURFACE"):
        src = MakeParametricSource()
        # The scalars are named "Scalars"by default
        # in the parametric surfaces, so change the name.
        src.GetPointData().GetScalars().SetName("Elevation");
    scalarRange = src.GetScalarRange()

    lut = MakeLUT()
    lut.SetTableRange(scalarRange)
    numberOfBands = lut.GetNumberOfTableValues()
    # bands = MakeIntegralBands(scalarRange)
    bands = MakeBands(scalarRange, numberOfBands, False)

    # Let's do a frequency table.
    # The number of scalars in each band.
    #print Frequencies(bands, src)

    # We will use the midpoint of the band as the label.
    labels = []
    for i in range(len(bands)):
        labels.append('{:4.2f}'.format(bands[i][1]))

    # Annotate
    values = vtk.vtkVariantArray()
    for i in range(len(labels)):
        values.InsertNextValue(vtk.vtkVariant(labels[i]))
    for i in range(values.GetNumberOfTuples()):
        lut.SetAnnotation(i, values.GetValue(i).ToString());

    # Create a lookup table with the colors reversed.
    lutr = ReverseLUT(lut)

    # Create the contour bands.
    bcf = vtk.vtkBandedPolyDataContourFilter()
    bcf.SetInputData(src)
    # Use either the minimum or maximum value for each band.
    for i in range(0, numberOfBands):
        bcf.SetValue(i, bands[i][2])
    # We will use an indexed lookup table.
    bcf.SetScalarModeToIndex()
    bcf.GenerateContourEdgesOn()

    # Generate the glyphs on the original surface.
    glyph = MakeGlyphs(src,False)

    # ------------------------------------------------------------
    # Create the mappers and actors
    # ------------------------------------------------------------
    srcMapper = vtk.vtkPolyDataMapper()
    srcMapper.SetInputConnection(bcf.GetOutputPort())
    srcMapper.SetScalarRange(scalarRange)
    srcMapper.SetLookupTable(lut)
    srcMapper.SetScalarModeToUseCellData()

    srcActor = vtk.vtkActor()
    srcActor.SetMapper(srcMapper)
    srcActor.RotateX(-45)
    srcActor.RotateZ(45)

    # Create contour edges
    edgeMapper = vtk.vtkPolyDataMapper()
    edgeMapper.SetInputData(bcf.GetContourEdgesOutput())
    edgeMapper.SetResolveCoincidentTopologyToPolygonOffset()

    edgeActor = vtk.vtkActor()
    edgeActor.SetMapper(edgeMapper)
    edgeActor.GetProperty().SetColor(0, 0, 0)
    edgeActor.RotateX(-45)
    edgeActor.RotateZ(45)

    glyphMapper = vtk.vtkPolyDataMapper()
    glyphMapper.SetInputConnection(glyph.GetOutputPort())
    glyphMapper.SetScalarModeToUsePointFieldData()
    glyphMapper.SetColorModeToMapScalars()
    glyphMapper.ScalarVisibilityOn()
    glyphMapper.SelectColorArray('Elevation')
    # Colour by scalars.
    glyphMapper.SetScalarRange(scalarRange)

    glyphActor = vtk.vtkActor()
    glyphActor.SetMapper(glyphMapper)
    glyphActor.RotateX(-45)
    glyphActor.RotateZ(45)

    # Add a scalar bar.
    scalarBar = vtk.vtkScalarBarActor()
    # scalarBar.SetLookupTable(lut)
    # Use this LUT if you want the highest value at the top.
    scalarBar.SetLookupTable(lutr)
    scalarBar.SetTitle('Elevation (m)')

    # ------------------------------------------------------------
    # Create the RenderWindow, Renderer and Interactor
    # ------------------------------------------------------------
    ren = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    iren = vtk.vtkRenderWindowInteractor()

    renWin.AddRenderer(ren)
    iren.SetRenderWindow(renWin)

    # add actors
    ren.AddViewProp(srcActor)
    ren.AddViewProp(edgeActor)
    ren.AddViewProp(glyphActor)
    ren.AddActor2D(scalarBar)

    ren.SetBackground(0.7, 0.8, 1.0)
    renWin.SetSize(800, 800)
    renWin.Render()

    ren.GetActiveCamera().Zoom(1.5)

    return iren

if __name__ == '__main__':
    #iren = DisplaySurface("PLANE")
    #iren = DisplaySurface("SPHERE")
    iren = DisplaySurface("PARAMETRIC_SURFACE")
    iren.Render()
    iren.Start()
#     WritePMG(iren.GetRenderWindow().GetRenderers().GetFirstRenderer(),
#               "ElevationBandsWithGlyphs.png")
```
