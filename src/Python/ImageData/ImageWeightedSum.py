#!/usr/bin/env python

import vtk


def main():
    colors = vtk.vtkNamedColors()

    colors.SetColor('leftBkg', [0.6, 0.5, 0.4, 1.0])
    colors.SetColor('centreBkg', [0.1, 0.5, 0.4, 1.0])
    colors.SetColor('rightBkg', [0.4, 0.5, 0.6, 1.0])

    # Create image 1
    source1 = vtk.vtkImageMandelbrotSource()
    source1.SetWholeExtent(0, 255, 0, 255, 0, 0)
    source1.Update()

    source1Double = vtk.vtkImageCast()
    source1Double.SetInputConnection(0, source1.GetOutputPort())
    source1Double.SetOutputScalarTypeToDouble()

    # Create image 2
    source2 = vtk.vtkImageSinusoidSource()
    source2.SetWholeExtent(0, 255, 0, 255, 0, 0)
    source2.Update()

    # Do the sum
    sumFilter = vtk.vtkImageWeightedSum()
    sumFilter.SetWeight(0, 0.8)
    sumFilter.SetWeight(1, 0.2)
    sumFilter.AddInputConnection(source1Double.GetOutputPort())
    sumFilter.AddInputConnection(source2.GetOutputPort())
    sumFilter.Update()

    # Display the images
    source1CastFilter = vtk.vtkImageCast()
    source1CastFilter.SetInputConnection(source1.GetOutputPort())
    source1CastFilter.SetOutputScalarTypeToUnsignedChar()
    source1CastFilter.Update()

    source2CastFilter = vtk.vtkImageCast()
    source2CastFilter.SetInputConnection(source2.GetOutputPort())
    source2CastFilter.SetOutputScalarTypeToUnsignedChar()
    source2CastFilter.Update()

    summedCastFilter = vtk.vtkImageCast()
    summedCastFilter.SetInputConnection(sumFilter.GetOutputPort())
    summedCastFilter.SetOutputScalarTypeToUnsignedChar()
    summedCastFilter.Update()

    # Create actors
    source1Actor = vtk.vtkImageActor()
    source1Actor.GetMapper().SetInputConnection(source1CastFilter.GetOutputPort())

    source2Actor = vtk.vtkImageActor()
    source2Actor.GetMapper().SetInputConnection(source2CastFilter.GetOutputPort())

    summedActor = vtk.vtkImageActor()
    summedActor.GetMapper().SetInputConnection(summedCastFilter.GetOutputPort())

    # There will be one render window
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetSize(600, 300)

    # And one interactor
    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderWindow)

    # Define viewport ranges
    # (xmin, ymin, xmax, ymax)
    leftViewport = [0.0, 0.0, 0.33, 1.0]
    centerViewport = [0.33, 0.0, .66, 1.0]
    rightViewport = [0.66, 0.0, 1.0, 1.0]

    # Setup renderers
    leftRenderer = vtk.vtkRenderer()
    renderWindow.AddRenderer(leftRenderer)
    leftRenderer.SetViewport(leftViewport)
    leftRenderer.SetBackground(colors.GetColor3d('leftBkg'))

    centerRenderer = vtk.vtkRenderer()
    renderWindow.AddRenderer(centerRenderer)
    centerRenderer.SetViewport(centerViewport)
    centerRenderer.SetBackground(colors.GetColor3d('centreBkg'))

    rightRenderer = vtk.vtkRenderer()
    renderWindow.AddRenderer(rightRenderer)
    rightRenderer.SetViewport(rightViewport)
    rightRenderer.SetBackground(colors.GetColor3d('rightBkg'))

    leftRenderer.AddActor(source1Actor)
    centerRenderer.AddActor(source2Actor)
    rightRenderer.AddActor(summedActor)

    leftRenderer.ResetCamera()
    centerRenderer.ResetCamera()
    rightRenderer.ResetCamera()

    renderWindow.Render()
    interactor.Start()


if __name__ == '__main__':
    main()
