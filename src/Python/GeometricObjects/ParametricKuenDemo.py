#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    colors = vtk.vtkNamedColors()

    colors.SetColor("BkgColor", [26, 51, 102, 255])

    surface = vtk.vtkParametricKuen()
    source = vtk.vtkParametricFunctionSource()

    renderer = vtk.vtkRenderer()
    mapper = vtk.vtkPolyDataMapper()
    actor = vtk.vtkActor()

    backProperty = vtk.vtkProperty()
    backProperty.SetColor(colors.GetColor3d("Tomato"))

    # Create a parametric function source, renderer, mapper, and actor
    source.SetParametricFunction(surface)

    mapper.SetInputConnection(source.GetOutputPort())

    actor.SetMapper(mapper)
    actor.SetBackfaceProperty(backProperty)
    actor.GetProperty().SetDiffuseColor(colors.GetColor3d("Banana"))
    actor.GetProperty().SetSpecular(.5)
    actor.GetProperty().SetSpecularPower(20)

    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("Parametric Kuen Demonstration")
    renderWindow.AddRenderer(renderer)
    renderWindow.SetSize(640, 480)

    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("BkgColor"))
    renderer.ResetCamera()
    renderer.GetActiveCamera().Azimuth(30)
    renderer.GetActiveCamera().Elevation(-30)
    renderer.GetActiveCamera().Zoom(0.9)
    renderer.ResetCameraClippingRange()

    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderWindow)

    # Setup a slider widget for each varying parameter
    tubeWidth = 0.008
    sliderLength = 0.008
    titleHeight = 0.02
    labelHeight = 0.02

    sliderRepMinimumU = vtk.vtkSliderRepresentation2D()

    sliderRepMinimumU.SetMinimumValue(-4.5)
    sliderRepMinimumU.SetMaximumValue(4.5)
    sliderRepMinimumU.SetValue(-4.5)
    sliderRepMinimumU.SetTitleText("U min")

    sliderRepMinimumU.GetPoint1Coordinate().SetCoordinateSystemToNormalizedDisplay()
    sliderRepMinimumU.GetPoint1Coordinate().SetValue(.1, .1)
    sliderRepMinimumU.GetPoint2Coordinate().SetCoordinateSystemToNormalizedDisplay()
    sliderRepMinimumU.GetPoint2Coordinate().SetValue(.9, .1)

    sliderRepMinimumU.SetTubeWidth(tubeWidth)
    sliderRepMinimumU.SetSliderLength(sliderLength)
    sliderRepMinimumU.SetTitleHeight(titleHeight)
    sliderRepMinimumU.SetLabelHeight(labelHeight)

    sliderWidgetMinimumU = vtk.vtkSliderWidget()
    sliderWidgetMinimumU.SetInteractor(interactor)
    sliderWidgetMinimumU.SetRepresentation(sliderRepMinimumU)
    sliderWidgetMinimumU.SetAnimationModeToAnimate()
    sliderWidgetMinimumU.EnabledOn()

    sliderWidgetMinimumU.AddObserver('InteractionEvent', SliderCallbackMinimumU(surface))

    sliderRepMaximumU = vtk.vtkSliderRepresentation2D()

    sliderRepMaximumU.SetMinimumValue(-4.5)
    sliderRepMaximumU.SetMaximumValue(4.5)
    sliderRepMaximumU.SetValue(4.5)
    sliderRepMaximumU.SetTitleText("U max")

    sliderRepMaximumU.GetPoint1Coordinate().SetCoordinateSystemToNormalizedDisplay()
    sliderRepMaximumU.GetPoint1Coordinate().SetValue(.1, .9)
    sliderRepMaximumU.GetPoint2Coordinate().SetCoordinateSystemToNormalizedDisplay()
    sliderRepMaximumU.GetPoint2Coordinate().SetValue(.9, .9)

    sliderRepMaximumU.SetTubeWidth(tubeWidth)
    sliderRepMaximumU.SetSliderLength(sliderLength)
    sliderRepMaximumU.SetTitleHeight(titleHeight)
    sliderRepMaximumU.SetLabelHeight(labelHeight)

    sliderWidgetMaximumU = vtk.vtkSliderWidget()
    sliderWidgetMaximumU.SetInteractor(interactor)
    sliderWidgetMaximumU.SetRepresentation(sliderRepMaximumU)
    sliderWidgetMaximumU.SetAnimationModeToAnimate()
    sliderWidgetMaximumU.EnabledOn()

    sliderWidgetMaximumU.AddObserver('InteractionEvent', SliderCallbackMaximumU(surface))

    sliderRepMinimumV = vtk.vtkSliderRepresentation2D()

    sliderRepMinimumV.SetMinimumValue(0.05)
    sliderRepMinimumV.SetMaximumValue(vtk.vtkMath.Pi())
    sliderRepMinimumV.SetValue(0.0)
    sliderRepMinimumV.SetTitleText("V min")

    sliderRepMinimumV.GetPoint1Coordinate().SetCoordinateSystemToNormalizedDisplay()
    sliderRepMinimumV.GetPoint1Coordinate().SetValue(.1, .1)
    sliderRepMinimumV.GetPoint2Coordinate().SetCoordinateSystemToNormalizedDisplay()
    sliderRepMinimumV.GetPoint2Coordinate().SetValue(.1, .9)

    sliderRepMinimumV.SetTubeWidth(tubeWidth)
    sliderRepMinimumV.SetSliderLength(sliderLength)
    sliderRepMinimumV.SetTitleHeight(titleHeight)
    sliderRepMinimumV.SetLabelHeight(labelHeight)

    sliderWidgetMinimumV = vtk.vtkSliderWidget()
    sliderWidgetMinimumV.SetInteractor(interactor)
    sliderWidgetMinimumV.SetRepresentation(sliderRepMinimumV)
    sliderWidgetMinimumV.SetAnimationModeToAnimate()
    sliderWidgetMinimumV.EnabledOn()

    sliderWidgetMinimumV.AddObserver(vtk.vtkCommand.InteractionEvent, SliderCallbackMinimumV(surface))

    sliderRepMaximumV = vtk.vtkSliderRepresentation2D()

    sliderRepMaximumV.SetMinimumValue(0.05)
    sliderRepMaximumV.SetMaximumValue(vtk.vtkMath.Pi() - .05)
    sliderRepMaximumV.SetValue(vtk.vtkMath.Pi())
    sliderRepMaximumV.SetTitleText("V max")

    sliderRepMaximumV.GetPoint1Coordinate().SetCoordinateSystemToNormalizedDisplay()
    sliderRepMaximumV.GetPoint1Coordinate().SetValue(.9, .1)
    sliderRepMaximumV.GetPoint2Coordinate().SetCoordinateSystemToNormalizedDisplay()
    sliderRepMaximumV.GetPoint2Coordinate().SetValue(.9, .9)
    sliderRepMaximumV.SetTubeWidth(tubeWidth)
    sliderRepMaximumV.SetSliderLength(sliderLength)
    sliderRepMaximumV.SetTitleHeight(titleHeight)
    sliderRepMaximumV.SetLabelHeight(labelHeight)

    sliderWidgetMaximumV = vtk.vtkSliderWidget()
    sliderWidgetMaximumV.SetInteractor(interactor)
    sliderWidgetMaximumV.SetRepresentation(sliderRepMaximumV)
    sliderWidgetMaximumV.SetAnimationModeToAnimate()
    sliderWidgetMaximumV.EnabledOn()

    sliderWidgetMaximumV.AddObserver(vtk.vtkCommand.InteractionEvent, SliderCallbackMaximumV(surface))

    surface.SetMinimumU(-4.5)
    surface.SetMaximumU(4.5)
    surface.SetMinimumV(0.05)
    surface.SetMaximumV(vtk.vtkMath.Pi() - .05)

    renderer.ResetCamera()
    renderer.GetActiveCamera().Azimuth(30)
    renderer.GetActiveCamera().Elevation(-30)
    renderer.GetActiveCamera().Zoom(0.9)
    renderer.ResetCameraClippingRange()
    renderWindow.Render()

    interactor.Initialize()

    interactor.Start()


# These callbacks do the actual work.
# Callbacks for the interactions
class SliderCallbackMinimumU():
    def __init__(self, kuen):
        self.kuen = kuen

    def __call__(self, caller, ev):
        sliderWidget = caller
        value = sliderWidget.GetRepresentation().GetValue()
        if value > 0.9 * self.kuen.GetMaximumU():
            value = 0.99 * self.kuen.GetMaximumU()
            sliderWidget.GetRepresentation().SetValue(value)
        self.kuen.SetMinimumU(value)


class SliderCallbackMaximumU():
    def __init__(self, kuen):
        self.kuen = kuen

    def __call__(self, caller, ev):
        sliderWidget = caller
        value = sliderWidget.GetRepresentation().GetValue()
        if value < self.kuen.GetMinimumU() + .01:
            value = self.kuen.GetMinimumU() + .01
            sliderWidget.GetRepresentation().SetValue(value)
        self.kuen.SetMaximumU(value)


class SliderCallbackMinimumV():
    def __init__(self, kuen):
        self.kuen = kuen

    def __call__(self, caller, ev):
        sliderWidget = caller
        value = sliderWidget.GetRepresentation().GetValue()
        if value > 0.9 * self.kuen.GetMaximumV():
            value = 0.99 * self.kuen.GetMaximumV()
            sliderWidget.GetRepresentation().SetValue(value)
        self.kuen.SetMinimumV(value)


class SliderCallbackMaximumV():
    def __init__(self, kuen):
        self.kuen = kuen

    def __call__(self, caller, ev):
        sliderWidget = caller
        value = sliderWidget.GetRepresentation().GetValue()
        if value < self.kuen.GetMinimumV() + .01:
            value = self.kuen.GetMinimumV() + .01
            sliderWidget.GetRepresentation().SetValue(value)
        self.kuen.SetMaximumV(value)


if __name__ == '__main__':
    main()
