#!/usr/bin/env python

import vtk


def main():
    fileName = get_program_parameters()

    colors = vtk.vtkNamedColors()

    # Load in the texture map. A texture is any unsigned char image. If it
    # is not of this type, you will have to map it through a lookup table
    # or by using vtkImageShiftScale.
    #
    readerFactory = vtk.vtkImageReader2Factory()
    textureFile = readerFactory.CreateImageReader2(fileName)
    textureFile.SetFileName(fileName)
    textureFile.Update()

    atext = vtk.vtkTexture()
    atext.SetInputConnection(textureFile.GetOutputPort())
    atext.InterpolateOn()

    # Create a plane source and actor. The vtkPlanesSource generates
    # texture coordinates.
    #
    plane = vtk.vtkPlaneSource()

    planeMapper = vtk.vtkPolyDataMapper()
    planeMapper.SetInputConnection(plane.GetOutputPort())

    planeActor = vtk.vtkActor()
    planeActor.SetMapper(planeMapper)
    planeActor.SetTexture(atext)

    # Create the RenderWindow, Renderer and Interactor.
    renderer = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(renderer)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Add the actors to the renderer, set the background and size.
    renderer.AddActor(planeActor)
    renderer.SetBackground(colors.GetColor3d("SlateGray"))
    renWin.SetSize(640, 480)

    # render the image
    renWin.Render()

    renderer.ResetCamera()
    renderer.GetActiveCamera().Elevation(-30)
    renderer.GetActiveCamera().Roll(-20)
    renderer.ResetCameraClippingRange()
    renWin.Render()
    iren.Start()


def get_program_parameters():
    import argparse
    description = 'How to do basic texture mapping.'
    epilogue = '''
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='masonry.bmp.')
    args = parser.parse_args()
    return args.filename


if __name__ == '__main__':
    main()
