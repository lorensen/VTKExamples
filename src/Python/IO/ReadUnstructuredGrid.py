#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def get_program_parameters():
    import argparse
    description = 'Read an unstructured grid file.'
    epilogue = ''''''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='tetra.vtu.')
    args = parser.parse_args()
    return args.filename


def main():
    colors = vtk.vtkNamedColors()

    file_name = get_program_parameters()

    # Read the source file.
    reader = vtk.vtkXMLUnstructuredGridReader()
    reader.SetFileName(file_name)
    reader.Update()  # Needed because of GetScalarRange
    output = reader.GetOutput()
    # scalar_range = output.GetScalarRange()

    # Create the mapper that corresponds the objects of the vtk.vtk file
    # into graphics elements
    mapper = vtk.vtkDataSetMapper()
    mapper.SetInputData(output)
    # mapper.SetScalarRange(scalar_range)
    mapper.ScalarVisibilityOff()

    # Create the Actor
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().EdgeVisibilityOn()
    actor.GetProperty().SetLineWidth(2.0)

    backface = vtk.vtkProperty()
    backface.SetColor(colors.GetColor3d("tomato"))
    actor.SetBackfaceProperty(backface)

    # Create the Renderer
    renderer = vtk.vtkRenderer()
    renderer.AddActor(actor)
    renderer.SetBackground(1, 1, 1)  # Set background to white
    renderer.SetBackground(colors.GetColor3d("Wheat"))

    # Create the RendererWindow
    renderer_window = vtk.vtkRenderWindow()
    renderer_window.AddRenderer(renderer)

    # Create the RendererWindowInteractor and display the vtk_file
    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderer_window)
    interactor.Initialize()
    interactor.Start()


if __name__ == '__main__':
    main()
