#!/usr/bin/env python

"""
"""

import vtk


def main():
    colors = vtk.vtkNamedColors()

    fileName = get_program_parameters()

    # Read the image.
    readerFactory = vtk.vtkImageReader2Factory()
    reader = readerFactory.CreateImageReader2(fileName)
    reader.SetFileName(fileName)
    reader.Update()

    # Pipelines
    constantPad = vtk.vtkImageConstantPad()
    constantPad.SetInputConnection(reader.GetOutputPort())
    constantPad.SetConstant(800)
    constantPad.SetOutputWholeExtent(-127, 383, -127, 383, 22, 22)

    mirrorPad = vtk.vtkImageMirrorPad()
    mirrorPad.SetInputConnection(reader.GetOutputPort())
    mirrorPad.SetOutputWholeExtent(constantPad.GetOutputWholeExtent())

    # Create actors
    constantPadColor = vtk.vtkImageMapToWindowLevelColors()
    constantPadColor.SetWindow(2000)
    constantPadColor.SetLevel(1000)
    constantPadColor.SetInputConnection(constantPad.GetOutputPort())

    constantPadActor = vtk.vtkImageActor()
    constantPadActor.GetMapper().SetInputConnection(
        constantPadColor.GetOutputPort())
    constantPadActor.GetProperty().SetInterpolationTypeToNearest()

    mirrorPadColor = vtk.vtkImageMapToWindowLevelColors()
    mirrorPadColor.SetWindow(2000)
    mirrorPadColor.SetLevel(1000)
    mirrorPadColor.SetInputConnection(mirrorPad.GetOutputPort())

    mirrorPadActor = vtk.vtkImageActor()
    mirrorPadActor.GetMapper().SetInputConnection(
        mirrorPadColor.GetOutputPort())
    mirrorPadActor.GetProperty().SetInterpolationTypeToNearest()

    # Setup the renderers.
    constantPadRenderer = vtk.vtkRenderer()
    constantPadRenderer.SetViewport(0.0, 0.0, 0.5, 1.0)
    constantPadRenderer.AddActor(constantPadActor)
    constantPadRenderer.ResetCamera()
    constantPadRenderer.SetBackground(colors.GetColor3d("SlateGray"))

    mirrorPadRenderer = vtk.vtkRenderer()
    mirrorPadRenderer.SetViewport(0.5, 0.0, 1.0, 1.0)
    mirrorPadRenderer.AddActor(mirrorPadActor)
    mirrorPadRenderer.SetActiveCamera(constantPadRenderer.GetActiveCamera())
    mirrorPadRenderer.SetBackground(colors.GetColor3d("LightSlateGray"))

    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetSize(600, 300)
    renderWindow.AddRenderer(constantPadRenderer)
    renderWindow.AddRenderer(mirrorPadRenderer)

    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    style = vtk.vtkInteractorStyleImage()

    renderWindowInteractor.SetInteractorStyle(style)

    renderWindowInteractor.SetRenderWindow(renderWindow)
    constantPadRenderer.GetActiveCamera().Dolly(1.2)
    constantPadRenderer.ResetCameraClippingRange()
    renderWindowInteractor.Initialize()

    renderWindowInteractor.Start()


def get_program_parameters():
    import argparse
    description = 'Convolution in frequency space treats the image as a periodic function.'
    epilogue = '''
     A large kernel can pick up features from both sides of the image.
     The lower-left image has been padded with zeros to eliminate wraparound during convolution.
     On the right, mirror padding has been used to remove artificial edges introduced by borders.
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='FullHead.mhd.')
    args = parser.parse_args()
    return args.filename


if __name__ == '__main__':
    main()
