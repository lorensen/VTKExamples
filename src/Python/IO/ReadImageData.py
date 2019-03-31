#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def get_program_parameters():
    import argparse
    description = 'Read a VTK image data file.'
    epilogue = ''''''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='vase.vti')
    args = parser.parse_args()
    return args.filename


def main():
    colors = vtk.vtkNamedColors()

    file_name = get_program_parameters()

    # Read the source file.
    reader = vtk.vtkXMLImageDataReader()
    reader.SetFileName(file_name)

    # Create the mapper that creates graphics elements
    mapper = vtk.vtkDataSetMapper()
    mapper.SetInputConnection(reader.GetOutputPort())

    # Create the Actor
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    # show the edges of the image grid
    actor.GetProperty().SetRepresentationToWireframe()

    # Create the Renderer
    renderer = vtk.vtkRenderer()
    renderer.AddActor(actor)
    renderer.ResetCamera()
    renderer.SetBackground(1, 1, 1)  # Set background to white

    # Create the RendererWindow
    renderer_window = vtk.vtkRenderWindow()
    renderer_window.AddRenderer(renderer)

    # Create the RendererWindowInteractor and display the vti file
    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderer_window)
    interactor.Initialize()
    interactor.Start()


if __name__ == '__main__':
    main()
