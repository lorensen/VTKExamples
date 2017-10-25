#!/usr/bin/env python

# Translated from TenAxes.tcl

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

    # Generate the tensor axes.
    axes = vtk.vtkAxes()
    axes.SetScaleFactor(0.5)

    tubeAxes = vtk.vtkTubeFilter()
    tubeAxes.SetInputConnection(axes.GetOutputPort())
    tubeAxes.SetRadius(0.1)
    tubeAxes.SetNumberOfSides(6)

    tensorAxes = vtk.vtkTensorGlyph()
    tensorAxes.SetInputConnection(ptLoad.GetOutputPort())
    tensorAxes.SetSourceConnection(axes.GetOutputPort())
    tensorAxes.SetScaleFactor(10)
    tensorAxes.ClampScalingOn()

    # Map contour
    lut = vtk.vtkLookupTable()
    MakeLogLUT(lut)
    # lut.SetHueRange(.6667, 0.0)
    tensorAxesMapper = vtk.vtkPolyDataMapper()
    tensorAxesMapper.SetInputConnection(tensorAxes.GetOutputPort())
    tensorAxesMapper.SetLookupTable(lut)
    plane.Update()  # force update for scalar range
    # This is deprecated from vtk 8.1 onwards.
    # tensorAxesMapper.ImmediateModeRenderingOn()
    tensorAxesMapper.SetScalarRange(plane.GetOutput().GetScalarRange())

    tensorActor = vtk.vtkActor()
    tensorActor.SetMapper(tensorAxesMapper)

    # Create an outline around the data.
    #
    outline = vtk.vtkOutlineFilter()
    outline.SetInputConnection(ptLoad.GetOutputPort())

    outlineMapper = vtk.vtkPolyDataMapper()
    outlineMapper.SetInputConnection(outline.GetOutputPort())

    outlineActor = vtk.vtkActor()
    outlineActor.SetMapper(outlineMapper)
    outlineActor.GetProperty().SetColor(colors.GetColor3d("Black"))

    #
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
    coneActor.GetProperty().SetColor(colors.GetColor3d("BurlyWood"))

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
    # Original
    lut.SetScaleToLog10()
    lut.SetHueRange(.6667, 0.0)
    lut.Build()


if __name__ == '__main__':
    main()
