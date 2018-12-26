#!/usr/bin/env python

import vtk


def main():
    InputFilename = get_program_parameters()

    colors = vtk.vtkNamedColors()

    # vtkSLCReader to read.
    reader = vtk.vtkSLCReader()
    reader.SetFileName(InputFilename)
    reader.Update()

    # Create a mapper.
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(reader.GetOutputPort())

    # Implementing Marching Cubes Algorithm to create the surface using vtkContourFilter object.
    contourFilter = vtk.vtkContourFilter()
    contourFilter.SetInputConnection(reader.GetOutputPort())
    contourFilter.SetValue(0, 72.0)

    outliner = vtk.vtkOutlineFilter()
    outliner.SetInputConnection(reader.GetOutputPort())
    outliner.Update()

    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(contourFilter.GetOutputPort())
    mapper.SetScalarVisibility(0)

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)

    # Create a rendering window and renderer.
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindow.SetSize(500, 500)

    # Create a renderwindowinteractor.
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    # Assign actor to the renderer.
    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("lemon_chiffon"))

    # Pick a good view
    renderer.GetActiveCamera().SetPosition(-382.606608, -3.308563, 223.475751)
    renderer.GetActiveCamera().SetFocalPoint(77.311562, 72.821162, 100.000000)
    renderer.GetActiveCamera().SetViewUp(0.235483, 0.137775, 0.962063)
    renderer.GetActiveCamera().SetDistance(482.25171)
    renderer.GetActiveCamera().SetClippingRange(27.933848, 677.669341)
    renderWindow.Render()

    # Enable user interface interactor.
    renderWindowInteractor.Initialize()
    renderWindow.Render()
    renderWindowInteractor.Start()


def get_program_parameters():
    import argparse
    description = 'The following example demonstrates how to read a .slc file using vtkSLCReader and how to render it with VTK.'
    epilogue = ''''''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename1', help='vw_knee.slc.')
    args = parser.parse_args()
    return args.filename1


if __name__ == '__main__':
    main()
