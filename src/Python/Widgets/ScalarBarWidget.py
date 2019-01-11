#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# by Panos Mavrogiorgos, email : pmav99 >a< gmail

import vtk


def get_program_parameters():
    import argparse
    description = 'Scalar bar widget.'
    epilogue = '''
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='uGridEx.vtk.')
    args = parser.parse_args()
    return args.filename


def main():
    colors = vtk.vtkNamedColors()

    colors.SetColor('bkg', [0.1, 0.2, 0.4, 1.0])

    # The source file
    file_name = get_program_parameters()

    # Create a custom lut. The lut is used both at the mapper and at the
    # scalar_bar
    lut = vtk.vtkLookupTable()
    lut.Build()

    # Read the source file.
    reader = vtk.vtkUnstructuredGridReader()
    reader.SetFileName(file_name)
    reader.Update()  # Needed because of GetScalarRange
    output = reader.GetOutput()
    scalar_range = output.GetScalarRange()

    mapper = vtk.vtkDataSetMapper()
    mapper.SetInputData(output)
    mapper.SetScalarRange(scalar_range)
    mapper.SetLookupTable(lut)

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)

    renderer = vtk.vtkRenderer()
    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d('bkg'))

    render_window = vtk.vtkRenderWindow()
    render_window.AddRenderer(renderer)
    render_window.SetSize(300, 300)

    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(render_window)

    # create the scalar_bar
    scalar_bar = vtk.vtkScalarBarActor()
    scalar_bar.SetOrientationToHorizontal()
    scalar_bar.SetLookupTable(lut)

    # create the scalar_bar_widget
    scalar_bar_widget = vtk.vtkScalarBarWidget()
    scalar_bar_widget.SetInteractor(interactor)
    scalar_bar_widget.SetScalarBarActor(scalar_bar)
    scalar_bar_widget.On()

    interactor.Initialize()
    render_window.Render()
    renderer.GetActiveCamera().SetPosition(-6.4, 10.3, 1.4)
    renderer.GetActiveCamera().SetFocalPoint(1.0, 0.5, 3.0)
    renderer.GetActiveCamera().SetViewUp(0.6, 0.4, -0.7)
    render_window.Render()
    interactor.Start()


if __name__ == '__main__':
    main()
