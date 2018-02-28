#!/usr/bin/env python

"""
"""

import vtk


def main():
    # colors = vtk.vtkNamedColors()

    fileName = get_program_parameters()

    # Read the image.
    readerFactory = vtk.vtkImageReader2Factory()
    reader = readerFactory.CreateImageReader2(fileName)
    reader.SetFileName(fileName)
    reader.Update()

    scalarRange = [0] * 2
    scalarRange[0] = reader.GetOutput().GetPointData().GetScalars().GetRange()[0]
    scalarRange[1] = reader.GetOutput().GetPointData().GetScalars().GetRange()[1]
    print("Range:", scalarRange)
    middleSlice = 22

    # Work with triple images.
    cast = vtk.vtkImageCast()
    cast.SetInputConnection(reader.GetOutputPort())
    cast.SetOutputScalarTypeToDouble()
    cast.Update()

    laplacian = vtk.vtkImageLaplacian()
    laplacian.SetInputConnection(cast.GetOutputPort())
    laplacian.SetDimensionality(3)

    enhance = vtk.vtkImageMathematics()
    enhance.SetInputConnection(0, cast.GetOutputPort())
    enhance.SetInputConnection(1, laplacian.GetOutputPort())
    enhance.SetOperationToSubtract()

    colorWindow = (scalarRange[1] - scalarRange[0])
    colorLevel = colorWindow / 2

    # Map the image through the lookup table.
    originalColor = vtk.vtkImageMapToWindowLevelColors()
    originalColor.SetWindow(colorWindow)
    originalColor.SetLevel(colorLevel)
    originalColor.SetInputConnection(reader.GetOutputPort())

    originalActor = vtk.vtkImageActor()
    originalActor.GetMapper().SetInputConnection(originalColor.GetOutputPort())
    originalActor.GetProperty().SetInterpolationTypeToNearest()
    originalActor.SetDisplayExtent(
        reader.GetDataExtent()[0], reader.GetDataExtent()[1],
        reader.GetDataExtent()[2], reader.GetDataExtent()[3],
        middleSlice, middleSlice)

    laplacianColor = vtk.vtkImageMapToWindowLevelColors()
    laplacianColor.SetWindow(1000)
    laplacianColor.SetLevel(0)
    laplacianColor.SetInputConnection(laplacian.GetOutputPort())

    laplacianActor = vtk.vtkImageActor()
    laplacianActor.GetMapper().SetInputConnection(laplacianColor.GetOutputPort())
    laplacianActor.GetProperty().SetInterpolationTypeToNearest()
    laplacianActor.SetDisplayExtent(originalActor.GetDisplayExtent())

    enhancedColor = vtk.vtkImageMapToWindowLevelColors()
    enhancedColor.SetWindow(colorWindow)
    enhancedColor.SetLevel(colorLevel)
    enhancedColor.SetInputConnection(enhance.GetOutputPort())

    enhancedActor = vtk.vtkImageActor()
    enhancedActor.GetMapper().SetInputConnection(enhancedColor.GetOutputPort())
    enhancedActor.GetProperty().SetInterpolationTypeToNearest()
    enhancedActor.SetDisplayExtent(originalActor.GetDisplayExtent())

    # Setup the renderers.
    originalRenderer = vtk.vtkRenderer()
    originalRenderer.AddActor(originalActor)
    laplacianRenderer = vtk.vtkRenderer()
    laplacianRenderer.AddActor(laplacianActor)
    enhancedRenderer = vtk.vtkRenderer()
    enhancedRenderer.AddActor(enhancedActor)

    renderers = list()
    renderers.append(originalRenderer)
    renderers.append(laplacianRenderer)
    renderers.append(enhancedRenderer)

    # Setup viewports for the renderers.
    rendererSize = 400
    xGridDimensions = 3
    yGridDimensions = 1

    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetSize(rendererSize * xGridDimensions, rendererSize * yGridDimensions)
    for row in range(0, yGridDimensions):
        for col in range(xGridDimensions):
            index = row * xGridDimensions + col
            # (xmin, ymin, xmax, ymax)
            viewport = [float(col) / xGridDimensions, float(yGridDimensions - (row + 1)) / yGridDimensions,
                        float(col + 1) / xGridDimensions, float(yGridDimensions - row) / yGridDimensions]
            renderers[index].SetViewport(viewport)
            renderWindow.AddRenderer(renderers[index])

    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    style = vtk.vtkInteractorStyleImage()

    renderWindowInteractor.SetInteractorStyle(style)
    renderWindowInteractor.SetRenderWindow(renderWindow)

    # Renderers share one camera.
    renderWindow.Render()
    renderers[0].GetActiveCamera().Dolly(1.5)
    renderers[0].ResetCameraClippingRange()

    for r in range(1, len(renderers)):
        renderers[r].SetActiveCamera(renderers[0].GetActiveCamera())
    renderWindowInteractor.Initialize()
    renderWindowInteractor.Start()


def get_program_parameters():
    import argparse
    description = 'High-pass filters can extract and enhance edges in an image.'
    epilogue = '''
    Subtraction of the Laplacian (middle) from the original image (left) results
     in edge enhancement or a sharpening operation (right).
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='FullHead.mhd.')
    args = parser.parse_args()
    return args.filename


if __name__ == '__main__':
    main()
