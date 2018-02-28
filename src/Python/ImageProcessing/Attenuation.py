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

    cast = vtk.vtkImageCast()
    cast.SetInputConnection(reader.GetOutputPort())
    cast.SetOutputScalarTypeToDouble()

    # Get rid of the discrete scalars.
    smooth = vtk.vtkImageGaussianSmooth()
    smooth.SetInputConnection(cast.GetOutputPort())
    smooth.SetStandardDeviations(0.8, 0.8, 0)

    m1 = vtk.vtkSphere()
    m1.SetCenter(310, 130, 0)
    m1.SetRadius(0)

    m2 = vtk.vtkSampleFunction()
    m2.SetImplicitFunction(m1)
    m2.SetModelBounds(0, 264, 0, 264, 0, 1)
    m2.SetSampleDimensions(264, 264, 1)

    m3 = vtk.vtkImageShiftScale()
    m3.SetInputConnection(m2.GetOutputPort())
    m3.SetScale(0.000095)

    div = vtk.vtkImageMathematics()
    div.SetInputConnection(0, smooth.GetOutputPort())
    div.SetInputConnection(1, m3.GetOutputPort())
    div.SetOperationToMultiply()

    # Create the actors.
    colorWindow = 256.0
    colorLevel = 127.5
    originalActor = vtk.vtkImageActor()
    originalActor.GetMapper().SetInputConnection(cast.GetOutputPort())
    originalActor.GetProperty().SetColorWindow(colorWindow)
    originalActor.GetProperty().SetColorLevel(colorLevel)

    filteredActor = vtk.vtkImageActor()
    filteredActor.GetMapper().SetInputConnection(div.GetOutputPort())

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
    description = 'This MRI image illustrates attenuation that can occur due to sensor position.'
    epilogue = '''
    The artifact is removed by dividing by the attenuation profile determined manually.
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='AttenuationArtifact.pgm.')
    args = parser.parse_args()
    return args.filename


if __name__ == '__main__':
    main()
