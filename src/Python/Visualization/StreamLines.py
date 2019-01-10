#!/usr/bin/env python

# import os
# os.chdir("VTKData/Data")

import vtk


def get_program_parameters():
    import argparse
    description = 'Streamlines.'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('xyz_file', help='combxyz.bin.')
    parser.add_argument('q_file', help='combq.bin.')
    args = parser.parse_args()
    return args.xyz_file, args.q_file


def main():
    colors = vtk.vtkNamedColors()

    colors.SetColor('bkg', [0.1, 0.2, 0.4, 1.0])

    xyz_file, q_file = get_program_parameters()

    # Read the data.
    #
    pl3d = vtk.vtkMultiBlockPLOT3DReader()
    pl3d.SetXYZFileName(xyz_file)
    pl3d.SetQFileName(q_file)
    pl3d.SetScalarFunctionNumber(100)
    pl3d.SetVectorFunctionNumber(202)
    pl3d.Update()

    seeds = vtk.vtkPlaneSource()
    seeds.SetXResolution(4)
    seeds.SetYResolution(4)
    seeds.SetOrigin(2, -2, 26)
    seeds.SetPoint1(2, 2, 26)
    seeds.SetPoint2(2, -2, 32)

    streamline = vtk.vtkStreamTracer()
    streamline.SetInputData(pl3d.GetOutput().GetBlock(0))
    streamline.SetSourceConnection(seeds.GetOutputPort())
    streamline.SetMaximumPropagation(200)
    streamline.SetInitialIntegrationStep(.2)
    streamline.SetIntegrationDirectionToForward()

    streamline_mapper = vtk.vtkPolyDataMapper()
    streamline_mapper.SetInputConnection(streamline.GetOutputPort())
    streamline_actor = vtk.vtkActor()
    streamline_actor.SetMapper(streamline_mapper)
    streamline_actor.VisibilityOn()

    outline = vtk.vtkStructuredGridOutlineFilter()
    outline.SetInputData(pl3d.GetOutput().GetBlock(0))
    outline_mapper = vtk.vtkPolyDataMapper()
    outline_mapper.SetInputConnection(outline.GetOutputPort())
    outline_actor = vtk.vtkActor()
    outline_actor.SetMapper(outline_mapper)
    outline_actor.GetProperty().SetColor(colors.GetColor3d('White'))

    renderer = vtk.vtkRenderer()
    render_window = vtk.vtkRenderWindow()
    render_window.AddRenderer(renderer)
    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetInteractorStyle(vtk.vtkInteractorStyleTrackballCamera())
    render_window.SetInteractor(interactor)

    renderer.AddActor(streamline_actor)
    renderer.AddActor(outline_actor)

    renderer.SetBackground(colors.GetColor3d('bkg'))
    interactor.Initialize()
    render_window.Render()
    renderer.GetActiveCamera().SetPosition(-32.8, -12.3, 46.3)
    renderer.GetActiveCamera().SetFocalPoint(8.3, 0.03, 29.8)
    renderer.GetActiveCamera().SetViewUp(0.2, 0.5, 0.9)
    render_window.Render()
    interactor.Start()


if __name__ == '__main__':
    main()
