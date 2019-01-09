#!/usr/bin/env python

from __future__ import print_function

import vtk


def get_program_parameters():
    import argparse
    description = 'Add a background image at a render window.'
    epilogue = '''
        Add a background image to a render window.
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', default=None, type=str, nargs='?', help='A required filename.')
    args = parser.parse_args()
    return args.filename


def main():
    colors = vtk.vtkNamedColors()

    colors.SetColor('light_cyan', [100, 255, 255, 255])
    colors.SetColor('light_magenta', [255, 100, 255, 255])

    #  Verify input arguments
    fn = get_program_parameters()
    if fn:
        # Read the image
        jpeg_reader = vtk.vtkJPEGReader()
        if not jpeg_reader.CanReadFile(fn):
            print("Error reading file:", fn)
            return

        jpeg_reader.SetFileName(fn)
        jpeg_reader.Update()
        image_data = jpeg_reader.GetOutput()
    else:
        canvas_source = vtk.vtkImageCanvasSource2D()
        canvas_source.SetExtent(0, 100, 0, 100, 0, 0)
        canvas_source.SetScalarTypeToUnsignedChar()
        canvas_source.SetNumberOfScalarComponents(3)
        canvas_source.SetDrawColor(colors.GetColor4ub('warm_grey'))
        canvas_source.FillBox(0, 100, 0, 100)
        canvas_source.SetDrawColor(colors.GetColor4ub('light_cyan'))
        canvas_source.FillTriangle(10, 10, 25, 10, 25, 25)
        canvas_source.SetDrawColor(colors.GetColor4ub('light_magenta'))
        canvas_source.FillTube(75, 75, 0, 75, 5.0)
        canvas_source.Update()
        image_data = canvas_source.GetOutput()

    # Create an image actor to display the image
    image_actor = vtk.vtkImageActor()
    image_actor.SetInputData(image_data)

    # Create a renderer to display the image in the background
    background_renderer = vtk.vtkRenderer()

    # Create a superquadric
    superquadric_source = vtk.vtkSuperquadricSource()
    superquadric_source.SetPhiRoundness(1.1)
    superquadric_source.SetThetaRoundness(.2)

    # Create a mapper and actor
    superquadric_mapper = vtk.vtkPolyDataMapper()
    superquadric_mapper.SetInputConnection(superquadric_source.GetOutputPort())

    superquadric_actor = vtk.vtkActor()
    superquadric_actor.SetMapper(superquadric_mapper)

    scene_renderer = vtk.vtkRenderer()
    render_window = vtk.vtkRenderWindow()

    # Set up the render window and renderers such that there is
    # a background layer and a foreground layer
    background_renderer.SetLayer(0)
    background_renderer.InteractiveOff()
    scene_renderer.SetLayer(1)
    render_window.SetNumberOfLayers(2)
    render_window.AddRenderer(background_renderer)
    render_window.AddRenderer(scene_renderer)

    render_window_interactor = vtk.vtkRenderWindowInteractor()
    render_window_interactor.SetRenderWindow(render_window)

    # Add actors to the renderers
    scene_renderer.AddActor(superquadric_actor)
    background_renderer.AddActor(image_actor)

    # Render once to figure out where the background camera will be
    render_window.Render()

    # Set up the background camera to fill the renderer with the image
    origin = image_data.GetOrigin()
    spacing = image_data.GetSpacing()
    extent = image_data.GetExtent()

    camera = background_renderer.GetActiveCamera()
    camera.ParallelProjectionOn()

    xc = origin[0] + 0.5 * (extent[0] + extent[1]) * spacing[0]
    yc = origin[1] + 0.5 * (extent[2] + extent[3]) * spacing[1]
    # xd = (extent[1] - extent[0] + 1) * spacing[0]
    yd = (extent[3] - extent[2] + 1) * spacing[1]
    d = camera.GetDistance()
    camera.SetParallelScale(0.5 * yd)
    camera.SetFocalPoint(xc, yc, 0.0)
    camera.SetPosition(xc, yc, d)

    # Render again to set the correct view
    render_window.Render()

    # Interact with the window
    render_window_interactor.Start()


if __name__ == '__main__':
    main()
