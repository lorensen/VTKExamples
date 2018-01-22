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

    # Process the image.
    cast = vtk.vtkImageCast()
    cast.SetInputConnection(reader.GetOutputPort())
    cast.SetOutputScalarTypeToFloat()

    smoothing_filter = vtk.vtkImageGaussianSmooth()
    smoothing_filter.SetDimensionality(2)
    smoothing_filter.SetInputConnection(cast.GetOutputPort())
    smoothing_filter.SetStandardDeviations(4.0, 4.0)
    smoothing_filter.SetRadiusFactors(2.0, 2.0)

    # Create the actors.
    originalActor = vtk.vtkImageActor()
    originalActor.GetMapper().SetInputConnection(
        reader.GetOutputPort())

    filteredActor = vtk.vtkImageActor()
    filteredActor.GetMapper().SetInputConnection(
        smoothing_filter.GetOutputPort())

    # Define the viewport ranges.
    # (xmin, ymin, xmax, ymax)
    originalViewport = [0.0, 0.0, 0.5, 1.0]
    filteredViewport = [0.5, 0.0, 1.0, 1.0]

    # Setup the renderers.
    originalRenderer = vtk.vtkRenderer()
    originalRenderer.SetViewport(originalViewport)
    originalRenderer.AddActor(originalActor)
    originalRenderer.ResetCamera()
    originalRenderer.SetBackground(colors.GetColor3d("SlateGray"))

    filteredRenderer = vtk.vtkRenderer()
    filteredRenderer.SetViewport(filteredViewport)
    filteredRenderer.AddActor(filteredActor)
    filteredRenderer.ResetCamera()
    filteredRenderer.SetBackground(colors.GetColor3d("LightSlateGray"))

    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetSize(600, 300)
    renderWindow.AddRenderer(originalRenderer)
    renderWindow.AddRenderer(filteredRenderer)

    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    style = vtk.vtkInteractorStyleImage()

    renderWindowInteractor.SetInteractorStyle(style)

    renderWindowInteractor.SetRenderWindow(renderWindow)
    renderWindowInteractor.Initialize()

    renderWindowInteractor.Start()


def get_program_parameters():
    import argparse
    description = 'Low-pass filters can be implemented as convolution with a Gaussian kernel.'
    epilogue = '''
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='Gourds.png.')
    args = parser.parse_args()
    return args.filename


if __name__ == '__main__':
    main()
