#!/usr/bin/env python

"""
"""

import vtk


def main():
    colors = vtk.vtkNamedColors()

    colors.SetColor("ActorColor", [235, 235, 235, 255])


    fileName = get_program_parameters()

    # Read the image.
    readerFactory = vtk.vtkImageReader2Factory()
    reader = readerFactory.CreateImageReader2(fileName)
    reader.SetFileName(fileName)
    reader.Update()

    # Smoothed pipeline.
    smooth = vtk.vtkImageGaussianSmooth()
    smooth.SetDimensionality(3)
    smooth.SetInputConnection(reader.GetOutputPort())
    smooth.SetStandardDeviations(1.75, 1.75, 0.0)
    smooth.SetRadiusFactor(2)

    subsampleSmoothed = vtk.vtkImageShrink3D()
    subsampleSmoothed.SetInputConnection(smooth.GetOutputPort())
    subsampleSmoothed.SetShrinkFactors(4, 4, 1)

    isoSmoothed = vtk.vtkImageMarchingCubes()
    isoSmoothed.SetInputConnection(smooth.GetOutputPort())
    isoSmoothed.SetValue(0, 1150)

    isoSmoothedMapper = vtk.vtkPolyDataMapper()
    isoSmoothedMapper.SetInputConnection(isoSmoothed.GetOutputPort())
    isoSmoothedMapper.ScalarVisibilityOff()

    isoSmoothedActor = vtk.vtkActor()
    isoSmoothedActor.SetMapper(isoSmoothedMapper)
    isoSmoothedActor.GetProperty().SetColor(colors.GetColor3d("ActorColor"))

    # Unsmoothed pipeline.
    # Sub sample the data.
    subsample = vtk.vtkImageShrink3D()
    subsample.SetInputConnection(reader.GetOutputPort())
    subsample.SetShrinkFactors(4, 4, 1)

    iso = vtk.vtkImageMarchingCubes()
    iso.SetInputConnection(subsample.GetOutputPort())
    iso.SetValue(0, 1150)

    isoMapper = vtk.vtkPolyDataMapper()
    isoMapper.SetInputConnection(iso.GetOutputPort())
    isoMapper.ScalarVisibilityOff()

    isoActor = vtk.vtkActor()
    isoActor.SetMapper(isoMapper)
    isoActor.GetProperty().SetColor(colors.GetColor3d("ActorColor"))

    # The rendering Pipeline.

    # Setup the render window, renderer, and interactor.
    leftViewport = [0.0, 0.0, 0.5, 1.0]
    rightViewport = [0.5, 0.0, 1.0, 1.0]

    rendererLeft = vtk.vtkRenderer()
    rendererLeft.SetViewport(leftViewport)

    rendererRight = vtk.vtkRenderer()
    rendererRight.SetViewport(rightViewport)

    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(rendererLeft)
    renderWindow.AddRenderer(rendererRight)

    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    rendererLeft.AddActor(isoActor)
    rendererRight.AddActor(isoSmoothedActor)

    rendererLeft.GetActiveCamera().SetFocalPoint(0.0, 0.0, 0.0)
    rendererLeft.GetActiveCamera().SetPosition(0.0, -1.0, 0.0)
    rendererLeft.GetActiveCamera().SetViewUp(0.0, 0.0, -1.0)
    rendererLeft.ResetCamera()
    rendererLeft.GetActiveCamera().Azimuth(-20.0)
    rendererLeft.GetActiveCamera().Elevation(20.0)
    rendererLeft.ResetCameraClippingRange()

    rendererLeft.SetBackground(colors.GetColor3d("SlateGray"))
    rendererRight.SetBackground(colors.GetColor3d("LightSlateGray"))
    rendererRight.SetActiveCamera(rendererLeft.GetActiveCamera())

    renderWindow.SetSize(640, 480)
    renderWindow.Render()

    renderWindowInteractor.Start()


def get_program_parameters():
    import argparse
    description = 'This figure demonstrates aliasing that occurs when a high-frequency signal is subsampled.'
    epilogue = '''
    High frequencies appear as low frequency artifacts.
    The left image is an isosurface of a skull after subsampling.
    The right image used a low-pass filter before subsampling to reduce aliasing.
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='FullHead.mhd.')
    args = parser.parse_args()
    return args.filename


if __name__ == '__main__':
    main()
