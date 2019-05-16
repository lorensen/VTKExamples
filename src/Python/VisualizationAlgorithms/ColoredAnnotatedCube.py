#!/usr/bin/env python

import vtk


def main():
    # Basic stuff setup
    # Set up the renderer, window, and interactor
    colors = vtk.vtkNamedColors()

    ren = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren)
    renWin.SetSize(640, 480)
    iRen = vtk.vtkRenderWindowInteractor()
    iRen.SetRenderWindow(renWin)

    # Create a cone with an elliptical base whose major axis is in the
    # X-direction.
    coneSource = vtk.vtkConeSource()
    coneSource.SetCenter(0.0, 0.0, 0.0)
    coneSource.SetRadius(5.0)
    coneSource.SetHeight(15.0)
    coneSource.SetDirection(0, 1, 0)
    coneSource.SetResolution(60)
    coneSource.Update()

    transform = vtk.vtkTransform()
    transform.Scale(1.0, 1.0, 0.75)

    transF = vtk.vtkTransformPolyDataFilter()
    transF.SetInputConnection(coneSource.GetOutputPort())
    transF.SetTransform(transform)

    bounds = transF.GetOutput().GetBounds()

    elevation = vtk.vtkElevationFilter()
    elevation.SetInputConnection(transF.GetOutputPort())
    elevation.SetLowPoint(0, bounds[2], 0)
    elevation.SetHighPoint(0, bounds[3], 0)

    bandedContours = vtk.vtkBandedPolyDataContourFilter()
    bandedContours.SetInputConnection(elevation.GetOutputPort())
    bandedContours.SetScalarModeToValue()
    bandedContours.GenerateContourEdgesOn()
    bandedContours.GenerateValues(11, elevation.GetScalarRange())

    # Make a lookup table using a color series.
    colorSeries = vtk.vtkColorSeries()
    colorSeries.SetColorScheme(vtk.vtkColorSeries.BREWER_DIVERGING_SPECTRAL_11)

    lut = vtk.vtkLookupTable()
    colorSeries.BuildLookupTable(lut, vtk.vtkColorSeries.ORDINAL)

    coneMapper = vtk.vtkPolyDataMapper()
    coneMapper.SetInputConnection(bandedContours.GetOutputPort())
    coneMapper.SetScalarRange(elevation.GetScalarRange())
    coneMapper.SetLookupTable(lut)

    coneActor = vtk.vtkActor()
    coneActor.SetMapper(coneMapper)

    # Contouring
    contourLineMapper = vtk.vtkPolyDataMapper()
    contourLineMapper.SetInputData(bandedContours.GetContourEdgesOutput())
    contourLineMapper.SetScalarRange(elevation.GetScalarRange())
    contourLineMapper.SetResolveCoincidentTopologyToPolygonOffset()

    contourLineActor = vtk.vtkActor()
    contourLineActor.SetMapper(contourLineMapper)
    contourLineActor.GetProperty().SetColor(
        colors.GetColor3d('DimGray'))

    # Set up the Orientation Marker Widget.
    prop_assembly = MakeAnnotatedCubeActor(colors)
    om1 = vtk.vtkOrientationMarkerWidget()
    om1.SetOrientationMarker(prop_assembly)
    om1.SetInteractor(iRen)
    om1.SetDefaultRenderer(ren)
    om1.On()
    om1.InteractiveOn()

    xyzLabels = ['X', 'Y', 'Z']
    scale = [1.0, 1.0, 1.0]
    axes = MakeAxesActor(scale, xyzLabels)

    om2 = vtk.vtkOrientationMarkerWidget()
    om2.SetOrientationMarker(axes)
    # Position lower right in the viewport.
    om2.SetViewport(0.8, 0, 1.0, 0.2)
    om2.SetInteractor(iRen)
    om2.EnabledOn()
    om2.InteractiveOn()

    ren.AddActor(coneActor)
    ren.AddActor(contourLineActor)
    ren.SetBackground2(colors.GetColor3d('RoyalBlue'))
    ren.SetBackground(colors.GetColor3d('MistyRose'))
    ren.GradientBackgroundOn()
    ren.GetActiveCamera().Azimuth(45)
    ren.GetActiveCamera().Pitch(-22.5)
    ren.ResetCamera()

    renWin.SetSize(600, 600)
    renWin.Render()
    renWin.SetWindowName('ColoredAnnotatedCube')
    renWin.Render()
    iRen.Start()


def MakeAnnotatedCubeActor(colors):
    # Annotated Cube setup
    annotated_cube = vtk.vtkAnnotatedCubeActor()
    annotated_cube.SetFaceTextScale(0.366667)

    # Anatomic labeling
    annotated_cube.SetXPlusFaceText('X+')
    annotated_cube.SetXMinusFaceText('X-')
    annotated_cube.SetYPlusFaceText('Y+')
    annotated_cube.SetYMinusFaceText('Y-')
    annotated_cube.SetZPlusFaceText('Z+')
    annotated_cube.SetZMinusFaceText('Z-')

    # Change the vector text colors
    annotated_cube.GetTextEdgesProperty().SetColor(
        colors.GetColor3d('Black'))
    annotated_cube.GetTextEdgesProperty().SetLineWidth(1)

    annotated_cube.GetXPlusFaceProperty().SetColor(
        colors.GetColor3d('Turquoise'))
    annotated_cube.GetXMinusFaceProperty().SetColor(
        colors.GetColor3d('Turquoise'))
    annotated_cube.GetYPlusFaceProperty().SetColor(
        colors.GetColor3d('Mint'))
    annotated_cube.GetYMinusFaceProperty().SetColor(
        colors.GetColor3d('Mint'))
    annotated_cube.GetZPlusFaceProperty().SetColor(
        colors.GetColor3d('Tomato'))
    annotated_cube.GetZMinusFaceProperty().SetColor(
        colors.GetColor3d('Tomato'))
    annotated_cube.SetXFaceTextRotation(90)
    annotated_cube.SetYFaceTextRotation(180)
    annotated_cube.SetZFaceTextRotation(-90)
    # Make the annotated cube transparent
    annotated_cube.GetCubeProperty().SetOpacity(0)

    # Colored faces cube setup
    cube_source = vtk.vtkCubeSource()
    cube_source.Update()

    face_colors = vtk.vtkUnsignedCharArray()
    face_colors.SetNumberOfComponents(3)
    face_x_plus = colors.GetColor3ub('Red')
    face_x_minus = colors.GetColor3ub('Green')
    face_y_plus = colors.GetColor3ub('Blue')
    face_y_minus = colors.GetColor3ub('Yellow')
    face_z_plus = colors.GetColor3ub('Cyan')
    face_z_minus = colors.GetColor3ub('Magenta')
    face_colors.InsertNextTypedTuple(face_x_minus)
    face_colors.InsertNextTypedTuple(face_x_plus)
    face_colors.InsertNextTypedTuple(face_y_minus)
    face_colors.InsertNextTypedTuple(face_y_plus)
    face_colors.InsertNextTypedTuple(face_z_minus)
    face_colors.InsertNextTypedTuple(face_z_plus)

    cube_source.GetOutput().GetCellData().SetScalars(face_colors)
    cube_source.Update()

    cube_mapper = vtk.vtkPolyDataMapper()
    cube_mapper.SetInputData(cube_source.GetOutput())
    cube_mapper.Update()

    cube_actor = vtk.vtkActor()
    cube_actor.SetMapper(cube_mapper)

    # Assemble the colored cube and annotated cube texts into a composite prop.
    prop_assembly = vtk.vtkPropAssembly()
    prop_assembly.AddPart(annotated_cube)
    prop_assembly.AddPart(cube_actor)
    return prop_assembly


def MakeAxesActor(scale, xyzLabels):
    axes = vtk.vtkAxesActor()
    axes.SetScale(scale[0], scale[1], scale[2])
    axes.SetShaftTypeToCylinder()
    axes.SetXAxisLabelText(xyzLabels[0])
    axes.SetYAxisLabelText(xyzLabels[1])
    axes.SetZAxisLabelText(xyzLabels[2])
    axes.SetCylinderRadius(0.5 * axes.GetCylinderRadius())
    axes.SetConeRadius(1.025 * axes.GetConeRadius())
    axes.SetSphereRadius(1.5 * axes.GetSphereRadius())
    tprop = axes.GetXAxisCaptionActor2D().GetCaptionTextProperty()
    tprop.ItalicOn()
    tprop.ShadowOn()
    tprop.SetFontFamilyToTimes()
    # Use the same text properties on the other two axes.
    axes.GetYAxisCaptionActor2D().GetCaptionTextProperty().ShallowCopy(tprop)
    axes.GetZAxisCaptionActor2D().GetCaptionTextProperty().ShallowCopy(tprop)
    return axes


if __name__ == '__main__':
    main()
