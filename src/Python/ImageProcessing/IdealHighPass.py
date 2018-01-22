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

    idealHighPass = vtk.vtkImageIdealHighPass()
    idealHighPass.SetInputConnection(fft.GetOutputPort())
    idealHighPass.SetXCutOff(0.1)
    idealHighPass.SetYCutOff(0.1)

    idealRfft = vtk.vtkImageRFFT()
    idealRfft.SetInputConnection(idealHighPass.GetOutputPort())

    idealReal = vtk.vtkImageExtractComponents()
    idealReal.SetInputConnection(idealRfft.GetOutputPort())
    idealReal.SetComponents(0)

    butterworthHighPass = vtk.vtkImageButterworthHighPass()
    butterworthHighPass.SetInputConnection(fft.GetOutputPort())
    butterworthHighPass.SetXCutOff(0.1)
    butterworthHighPass.SetYCutOff(0.1)

    butterworthRfft = vtk.vtkImageRFFT()
    butterworthRfft.SetInputConnection(butterworthHighPass.GetOutputPort())

    butterworthReal = vtk.vtkImageExtractComponents()
    butterworthReal.SetInputConnection(butterworthRfft.GetOutputPort())
    butterworthReal.SetComponents(0)

    # Create the actors.
    idealColor = vtk.vtkImageMapToWindowLevelColors()
    idealColor.SetWindow(500)
    idealColor.SetLevel(0)
    idealColor.SetInputConnection(idealReal.GetOutputPort())

    idealActor = vtk.vtkImageActor()
    idealActor.GetMapper().SetInputConnection(idealColor.GetOutputPort())
    idealActor.GetProperty().SetInterpolationTypeToNearest()

    butterworthColor = vtk.vtkImageMapToWindowLevelColors()
    butterworthColor.SetWindow(500)
    butterworthColor.SetLevel(0)
    butterworthColor.SetInputConnection(butterworthReal.GetOutputPort())

    butterworthActor = vtk.vtkImageActor()
    butterworthActor.GetMapper().SetInputConnection(butterworthColor.GetOutputPort())
    butterworthActor.GetProperty().SetInterpolationTypeToNearest()

    # Setup the renderers.
    idealRenderer = vtk.vtkRenderer()
    idealRenderer.SetViewport(0.0, 0.0, 0.5, 1.0)
    idealRenderer.AddActor(idealActor)
    idealRenderer.ResetCamera()
    idealRenderer.SetBackground(colors.GetColor3d("SlateGray"))

    butterworthRenderer = vtk.vtkRenderer()
    butterworthRenderer.SetViewport(0.5, 0.0, 1.0, 1.0)
    butterworthRenderer.AddActor(butterworthActor)
    butterworthRenderer.SetActiveCamera(idealRenderer.GetActiveCamera())
    butterworthRenderer.SetBackground(colors.GetColor3d("LightSlateGray"))

    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetSize(600, 300)
    renderWindow.AddRenderer(idealRenderer)
    renderWindow.AddRenderer(butterworthRenderer)

    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    style = vtk.vtkInteractorStyleImage()

    renderWindowInteractor.SetInteractorStyle(style)

    renderWindowInteractor.SetRenderWindow(renderWindow)
    idealRenderer.GetActiveCamera().Dolly(1.4)
    idealRenderer.ResetCameraClippingRange()
    renderWindowInteractor.Initialize()

    renderWindowInteractor.Start()


def get_program_parameters():
    import argparse
    description = 'This figure shows two high-pass filters in the frequency domain.'
    epilogue = '''
    The Butterworth high-pass filter has a gradual attenuation that avoids ringing
     produced by the ideal high-pass filter with an abrupt transition.
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='fullhead15.png.')
    args = parser.parse_args()
    return args.filename


if __name__ == '__main__':
    main()
