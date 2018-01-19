#!/usr/bin/env python

"""
"""

import vtk


def main():
    colors = vtk.vtkNamedColors()

    fileName = get_program_parameters()

    # This example shows how to use decimation to reduce a polygonal mesh. We also
    # use mesh smoothing and generate surface normals to give a pleasing result.
    #

    hawaii = vtk.vtkPolyDataReader()
    hawaii.SetFileName(fileName)

    # We want to preserve topology (not let any cracks form). This may limit
    # the total reduction possible, which we have specified at 90%.
    #
    deci = vtk.vtkDecimatePro()
    deci.SetInputConnection(hawaii.GetOutputPort())
    deci.SetTargetReduction(0.9)
    deci.PreserveTopologyOn()

    decimatedNormals = vtk.vtkPolyDataNormals()
    decimatedNormals.SetInputConnection(deci.GetOutputPort())
    decimatedNormals.FlipNormalsOn()
    decimatedNormals.SetFeatureAngle(60)

    decimatedMapper = vtk.vtkPolyDataMapper()
    decimatedMapper.SetInputConnection(decimatedNormals.GetOutputPort())

    decimatedActor = vtk.vtkActor()
    decimatedActor.SetMapper(decimatedMapper)
    decimatedActor.GetProperty().SetColor(colors.GetColor3d("Aqua"))
    decimatedActor.GetProperty().SetRepresentationToWireframe()

    originalMapper = vtk.vtkPolyDataMapper()
    originalMapper.SetInputConnection(decimatedNormals.GetOutputPort())

    originalActor = vtk.vtkActor()
    originalActor.SetMapper(originalMapper)
    originalActor.GetProperty().SetColor(colors.GetColor3d("Aqua"))

    # Create the RenderWindow, Renderer and Interactor.
    #
    renderer1 = vtk.vtkRenderer()
    renderer1.SetViewport(0.0, 0.0, 0.5, 1.0)

    renderer2 = vtk.vtkRenderer()
    renderer2.SetViewport(0.5, 0.0, 1.0, 1.0)

    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer1)
    renderWindow.AddRenderer(renderer2)

    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderWindow)

    # Add the actors to the renderer, set the background and size.
    #
    renderer1.AddActor(originalActor)
    renderer2.AddActor(decimatedActor)
    renderer1.SetBackground(colors.GetColor3d("Wheat"))
    renderer2.SetBackground(colors.GetColor3d("Papaya_Whip"))
    renderWindow.SetSize(800, 400)

    # Render the image.
    #
    cam1 = vtk.vtkCamera()
    cam1.SetFocalPoint(0, 0, 0)
    cam1.SetPosition(0, 0, 1)
    cam1.SetViewUp(0, 1, 0)
    renderer1.SetActiveCamera(cam1)
    renderer2.SetActiveCamera(cam1)
    renderer1.ResetCamera()
    cam1.Azimuth(30)
    cam1.Elevation(30)
    cam1.Dolly(1.3)
    renderer1.ResetCameraClippingRange()
    renderWindow.Render()
    interactor.Start()


def get_program_parameters():
    import argparse
    description = 'Examples of decimation algorithm.'
    epilogue = '''
    (b) Decimation of terrain data.
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename1', help='honolulu.vtk.')
    args = parser.parse_args()
    return args.filename1


if __name__ == '__main__':
    main()
