#!/usr/bin/env python

"""
"""

import vtk


def main():
    colors = vtk.vtkNamedColors()

    fileName = get_program_parameters()

    # Now create the RenderWindow, Renderer and Interactor.
    #
    ren1 = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren1)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    imageIn = vtk.vtkPNMReader()
    imageIn.SetFileName(fileName)

    gaussian = vtk.vtkImageGaussianSmooth()
    gaussian.SetStandardDeviations(2, 2)
    gaussian.SetDimensionality(2)
    gaussian.SetRadiusFactors(1, 1)
    gaussian.SetInputConnection(imageIn.GetOutputPort())

    geometry = vtk.vtkImageDataGeometryFilter()
    geometry.SetInputConnection(gaussian.GetOutputPort())

    aClipper = vtk.vtkClipPolyData()
    aClipper.SetInputConnection(geometry.GetOutputPort())
    aClipper.SetValue(127.5)
    aClipper.GenerateClipScalarsOff()
    aClipper.InsideOutOn()
    aClipper.GetOutput().GetPointData().CopyScalarsOff()
    aClipper.Update()

    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(aClipper.GetOutputPort())
    mapper.ScalarVisibilityOff()

    letter = vtk.vtkActor()
    letter.SetMapper(mapper)

    ren1.AddActor(letter)
    letter.GetProperty().SetDiffuseColor(colors.GetColor3d("LampBlack"))
    letter.GetProperty().SetRepresentationToWireframe()

    ren1.SetBackground(colors.GetColor3d("WhiteSmoke"))
    ren1.ResetCamera()
    ren1.GetActiveCamera().Dolly(1.2)
    ren1.ResetCameraClippingRange()

    renWin.SetSize(640, 480)

    # Render the image.
    #
    renWin.Render()
    iren.Start()


def get_program_parameters():
    import argparse
    description = 'A scanned image clipped with a scalar value.'
    epilogue = '''
    A scanned image clipped with a scalar value of 1/2 its maximum intensity
     produces a mixture of quadrilaterals and triangles.
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='B.pgm.')
    args = parser.parse_args()
    return args.filename


if __name__ == '__main__':
    main()
