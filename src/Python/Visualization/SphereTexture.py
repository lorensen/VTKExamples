#!/usr/bin/env python

##
# This example shows how to apply an vtkImageData texture to an sphere
# vtkPolyData object.
# Note: Input jpg file can be located in the VTKData repository.
#
# @author JBallesteros
##

import vtk


def get_program_parameters():
    import argparse
    description = 'Texture an object with an image.'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='masonry-wide.jpg.')
    args = parser.parse_args()
    return args.filename


def main():
    colors = vtk.vtkNamedColors()

    jpegfile = get_program_parameters()

    # Create a render window
    ren = vtk.vtkRenderer()
    ren.SetBackground(.1, .2, .5)
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren)
    renWin.SetSize(480, 480)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Generate an sphere polydata
    sphere = vtk.vtkSphereSource()
    sphere.SetThetaResolution(12)
    sphere.SetPhiResolution(12)

    # Read the image data from a file
    reader = vtk.vtkJPEGReader()
    reader.SetFileName(jpegfile)

    # Create texture object
    texture = vtk.vtkTexture()
    texture.SetInputConnection(reader.GetOutputPort())

    # Map texture coordinates
    map_to_sphere = vtk.vtkTextureMapToSphere()
    map_to_sphere.SetInputConnection(sphere.GetOutputPort())
    map_to_sphere.PreventSeamOn()

    # Create mapper and set the mapped texture as input
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(map_to_sphere.GetOutputPort())

    # Create actor and set the mapper and the texture
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.SetTexture(texture)

    ren.AddActor(actor)
    ren.SetBackground(colors.GetColor3d('RosyBrown'))

    iren.Initialize()
    renWin.Render()
    iren.Start()


if __name__ == '__main__':
    main()
