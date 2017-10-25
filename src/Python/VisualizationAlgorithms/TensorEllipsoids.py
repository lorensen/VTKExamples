#!/usr/bin/env python

# Translated from TenEllip.tcl

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Create the RenderWindow, Renderer and interactive renderer.
    #
    ren = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Generate the tensors.
    ptLoad = vtk.vtkPointLoad()
    ptLoad.SetLoadValue(100.0)
    ptLoad.SetSampleDimensions(6, 6, 6)
    ptLoad.ComputeEffectiveStressOn()
    ptLoad.SetModelBounds(-10, 10, -10, 10, -10, 10)

    # Extract a plane of data.
    plane = vtk.vtkImageDataGeometryFilter()
    plane.SetInputConnection(ptLoad.GetOutputPort())
    plane.SetExtent(2, 2, 0, 99, 0, 99)

    # Generate the ellipsoids.
    sphere = vtk.vtkSphereSource()
    sphere.SetThetaResolution(8)
    sphere.SetPhiResolution(8)
    tensorEllipsoids = vtk.vtkTensorGlyph()
    tensorEllipsoids.SetInputConnection(ptLoad.GetOutputPort())
    tensorEllipsoids.SetSourceConnection(sphere.GetOutputPort())
    tensorEllipsoids.SetScaleFactor(10)
    tensorEllipsoids.ClampScalingOn()

    ellipNormals = vtk.vtkPolyDataNormals()
    ellipNormals.SetInputConnection(tensorEllipsoids.GetOutputPort())

    # Map contour
    lut = vtk.vtkLookupTable()
    MakeLogLUT(lut)
    # lut.SetHueRange(.6667, 0.0)
    tensorEllipsoidsMapper = vtk.vtkPolyDataMapper()
    tensorEllipsoidsMapper.SetInputConnection(ellipNormals.GetOutputPort())
    tensorEllipsoidsMapper.SetLookupTable(lut)
    plane.Update()  # force update for scalar range
    tensorEllipsoidsMapper.SetScalarRange(plane.GetOutput().GetScalarRange())

    tensorActor = vtk.vtkActor()
    tensorActor.SetMapper(tensorEllipsoidsMapper)

    # Create an outline around the data.
    #
    outline = vtk.vtkOutlineFilter()
    outline.SetInputConnection(ptLoad.GetOutputPort())

    outlineMapper = vtk.vtkPolyDataMapper()
    outlineMapper.SetInputConnection(outline.GetOutputPort())

    outlineActor = vtk.vtkActor()
    outlineActor.SetMapper(outlineMapper)
    outlineActor.GetProperty().SetColor(colors.GetColor3d("Black"))

    # Create a cone whose apex indicates the application of load.
    #
    coneSrc = vtk.vtkConeSource()
    coneSrc.SetRadius(.5)
    coneSrc.SetHeight(2)
    coneMap = vtk.vtkPolyDataMapper()
    coneMap.SetInputConnection(coneSrc.GetOutputPort())
    coneActor = vtk.vtkActor()
    coneActor.SetMapper(coneMap)
    coneActor.SetPosition(0, 0, 11)
    coneActor.RotateY(90)
    coneActor.GetProperty().SetColor(colors.GetColor3d("Red"))

    camera = vtk.vtkCamera()
    camera.SetFocalPoint(0.113766, -1.13665, -1.01919)
    camera.SetPosition(-29.4886, -63.1488, 26.5807)
    camera.SetViewAngle(24.4617)
    camera.SetViewUp(0.17138, 0.331163, 0.927879)
    camera.SetClippingRange(1, 100)

    ren.AddActor(tensorActor)
    ren.AddActor(outlineActor)
    ren.AddActor(coneActor)
    ren.SetBackground(colors.GetColor3d("WhiteSmoke"))
    ren.SetActiveCamera(camera)

    renWin.SetSize(512, 512)

    iren.Initialize()
    renWin.Render()
    iren.Start()


def MakeLogLUT(lut):
    # Make the lookup using a Brewer palette.
    colorSeries = vtk.vtkColorSeries()
    colorSeries.SetNumberOfColors(8)
    colorSeriesEnum = colorSeries.BREWER_DIVERGING_SPECTRAL_8
    colorSeries.SetColorScheme(colorSeriesEnum)
    lut.SetScaleToLog10()
    colorSeries.BuildLookupTable(lut, colorSeries.ORDINAL)
    lut.SetNanColor(1, 0, 0, 1)
    # Original
    # lut.SetScaleToLog10()
    # lut.SetHueRange(.6667, 0.0)
    # lut.Build()


if __name__ == '__main__':
    main()
