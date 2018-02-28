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

    fft = vtk.vtkImageFFT()
    fft.SetInputConnection(reader.GetOutputPort())

    mag = vtk.vtkImageMagnitude()
    mag.SetInputConnection(fft.GetOutputPort())

    center = vtk.vtkImageFourierCenter()
    center.SetInputConnection(mag.GetOutputPort())

    compress = vtk.vtkImageLogarithmicScale()
    compress.SetInputConnection(center.GetOutputPort())
    compress.SetConstant(15)
    compress.Update()

    # Create the actors.
    originalActor = vtk.vtkImageActor()
    originalActor.GetMapper().SetInputConnection(reader.GetOutputPort())
    originalActor.GetProperty().SetInterpolationTypeToNearest()

    compressedActor = vtk.vtkImageActor()
    compressedActor.GetMapper().SetInputConnection(compress.GetOutputPort())
    compressedActor.GetProperty().SetInterpolationTypeToNearest()
    CreateImageActor(compressedActor, 160, 120)

    # Define the viewport ranges.
    # (xmin, ymin, xmax, ymax)
    originalViewport = [0.0, 0.0, 0.5, 1.0]
    compressedViewport = [0.5, 0.0, 1.0, 1.0]

    # Setup the renderers.
    originalRenderer = vtk.vtkRenderer()
    originalRenderer.SetViewport(originalViewport)
    originalRenderer.AddActor(originalActor)
    originalRenderer.ResetCamera()
    originalRenderer.SetBackground(colors.GetColor3d("SlateGray"))

    compressedRenderer = vtk.vtkRenderer()
    compressedRenderer.SetViewport(compressedViewport)
    compressedRenderer.AddActor(compressedActor)
    compressedRenderer.ResetCamera()
    compressedRenderer.SetBackground(colors.GetColor3d("LightSlateGray"))

    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetSize(600, 300)
    renderWindow.AddRenderer(originalRenderer)
    renderWindow.AddRenderer(compressedRenderer)

    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    style = vtk.vtkInteractorStyleImage()

    renderWindowInteractor.SetInteractorStyle(style)

    renderWindowInteractor.SetRenderWindow(renderWindow)
    renderWindowInteractor.Initialize()

    renderWindowInteractor.Start()


def get_program_parameters():
    import argparse
    description = 'The discrete Fourier transform.'
    epilogue = '''
    This changes an image from the spatial domain into the frequency domain,
     where each pixel represents a sinusoidal function.
    This figure shows an image and its power spectrum displayed using a logarithmic transfer function.
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='vtks.pgm.')
    args = parser.parse_args()
    return args.filename


def CreateImageActor(actor, colorWindow, colorLevel):
    wlut = vtk.vtkWindowLevelLookupTable()
    wlut.SetWindow(colorWindow)
    wlut.SetLevel(colorLevel)
    wlut.Build()

    # Map the image through the lookup table.
    color = vtk.vtkImageMapToColors()
    color.SetLookupTable(wlut)
    color.SetInputData(actor.GetMapper().GetInput())

    actor.GetMapper().SetInputConnection(color.GetOutputPort())
    return


if __name__ == '__main__':
    main()
