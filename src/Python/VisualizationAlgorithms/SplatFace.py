#!/usr/bin/env python

"""
"""

import vtk


def main():
    colors = vtk.vtkNamedColors()

    fileName = get_program_parameters()

    # Create the RenderWindow, Renderer and Interactor.
    #
    ren1 = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren1)

    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Read cyberware file.
    #
    cyber = vtk.vtkPolyDataReader()
    cyber.SetFileName(fileName)

    normals = vtk.vtkPolyDataNormals()
    normals.SetInputConnection(cyber.GetOutputPort())

    mask = vtk.vtkMaskPoints()
    mask.SetInputConnection(normals.GetOutputPort())
    mask.SetOnRatio(8)
    # mask.RandomModeOn()

    splatter = vtk.vtkGaussianSplatter()
    splatter.SetInputConnection(mask.GetOutputPort())
    splatter.SetSampleDimensions(100, 100, 100)
    splatter.SetEccentricity(2.5)
    splatter.NormalWarpingOn()
    splatter.SetScaleFactor(1.0)
    splatter.SetRadius(0.025)

    contour = vtk.vtkContourFilter()
    contour.SetInputConnection(splatter.GetOutputPort())
    contour.SetValue(0, 0.25)

    splatMapper = vtk.vtkPolyDataMapper()
    splatMapper.SetInputConnection(contour.GetOutputPort())
    splatMapper.ScalarVisibilityOff()

    splatActor = vtk.vtkActor()
    splatActor.SetMapper(splatMapper)
    splatActor.GetProperty().SetColor(colors.GetColor3d("Flesh"))

    cyberMapper = vtk.vtkPolyDataMapper()
    cyberMapper.SetInputConnection(cyber.GetOutputPort())
    cyberMapper.ScalarVisibilityOff()

    cyberActor = vtk.vtkActor()
    cyberActor.SetMapper(cyberMapper)
    cyberActor.GetProperty().SetRepresentationToWireframe()
    cyberActor.GetProperty().SetColor(colors.GetColor3d("Turquoise"))

    # Add the actors to the renderer, set the background and size.
    #
    ren1.AddActor(cyberActor)
    ren1.AddActor(splatActor)
    ren1.SetBackground(colors.GetColor3d("Wheat"))
    renWin.SetSize(640, 480)

    camera = vtk.vtkCamera()
    camera.SetClippingRange(0.0332682, 1.66341)
    camera.SetFocalPoint(0.0511519, -0.127555, -0.0554379)
    camera.SetPosition(0.516567, -0.124763, -0.349538)
    camera.SetViewAngle(18.1279)
    camera.SetViewUp(-0.013125, 0.99985, -0.0112779)
    ren1.SetActiveCamera(camera)

    # Render the image.
    #
    renWin.Render()
    iren.Start()


def get_program_parameters():
    import argparse
    description = 'Elliptical splatting.'
    epilogue = '''
    b) Surface reconstructed using elliptical splats into 100^3 volume followed by isosurface extraction.
       Points regularly subsampled and overlaid on original mesh.
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='fran_cut.vtk.')
    args = parser.parse_args()
    return args.filename


if __name__ == '__main__':
    main()
