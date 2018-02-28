#!/usr/bin/env python

"""
"""

import vtk


def main():
    colors = vtk.vtkNamedColors()

    fileName1, fileName2 = get_program_parameters()

    # This example shows how to use decimation to reduce a polygonal mesh. We also
    # use mesh smoothing and generate surface normals to give a pleasing result.
    #

    # We start by reading some data that was originally captured from
    # a Cyberware laser digitizing system.
    #
    fran = vtk.vtkPolyDataReader()
    fran.SetFileName(fileName1)

    # Read the corresponding texture.
    textureReader = vtk.vtkPNGReader()
    textureReader.SetFileName(fileName2)

    texture = vtk.vtkTexture()
    texture.InterpolateOn()
    texture.SetInputConnection(textureReader.GetOutputPort())

    # We want to preserve topology (not let any cracks form). This may limit
    # the total reduction possible, which we have specified at 90%.
    #
    deci = vtk.vtkDecimatePro()
    deci.SetInputConnection(fran.GetOutputPort())
    deci.SetTargetReduction(0.9)
    deci.PreserveTopologyOn()

    decimatedNormals = vtk.vtkPolyDataNormals()
    decimatedNormals.SetInputConnection(deci.GetOutputPort())
    decimatedNormals.FlipNormalsOn()
    decimatedNormals.SetFeatureAngle(60)

    originalNormals = vtk.vtkPolyDataNormals()
    originalNormals.SetInputConnection(fran.GetOutputPort())
    originalNormals.FlipNormalsOn()
    originalNormals.SetFeatureAngle(60)

    decimatedMapper = vtk.vtkPolyDataMapper()
    decimatedMapper.SetInputConnection(decimatedNormals.GetOutputPort())

    decimatedActor = vtk.vtkActor()
    decimatedActor.SetMapper(decimatedMapper)
    decimatedActor.GetProperty().SetAmbient(.5)
    decimatedActor.GetProperty().SetDiffuse(.5)
    decimatedActor.SetTexture(texture)

    originalMapper = vtk.vtkPolyDataMapper()
    originalMapper.SetInputConnection(originalNormals.GetOutputPort())

    originalActor = vtk.vtkActor()
    originalActor.SetMapper(originalMapper)
    originalActor.GetProperty().SetAmbient(.5)
    originalActor.GetProperty().SetDiffuse(.5)
    originalActor.SetTexture(texture)

    # Create the RenderWindow, Renderer and Interactor.
    #
    renderer1 = vtk.vtkRenderer()
    renderer1.SetViewport(0., 0.0, 0.5, 1.0)

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
    cam1.SetClippingRange(0.0475572, 2.37786)
    cam1.SetFocalPoint(0.052665, -0.129454, -0.0573973)
    cam1.SetPosition(0.327637, -0.116299, -0.256418)
    cam1.SetViewUp(-0.0225386, 0.999137, 0.034901)
    renderer1.SetActiveCamera(cam1)
    renderer2.SetActiveCamera(cam1)

    renderWindow.Render()
    interactor.Start()


def get_program_parameters():
    import argparse
    description = 'Examples of the decimation algorithm.'
    epilogue = '''
    (a) Decimation of laser digitizer.
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename1', help='fran_cut.vtk.')
    parser.add_argument('filename2', help='fran_cut.png.')
    args = parser.parse_args()
    return args.filename1, args.filename2


if __name__ == '__main__':
    main()
