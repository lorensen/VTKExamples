#!/usr/bin/env python

import vtk


def main():
    fileName = get_program_parameters()

    colors = vtk.vtkNamedColors()

    colors.SetColor("A1Diff", [255, 204, 77, 255])
    colors.SetColor("A2Amb", [51, 51, 255, 255])
    colors.SetColor("A2Diff", [51, 255, 204, 255])
    colors.SetColor("A3Amb", [230, 230, 230, 255])
    colors.SetColor("Bkg", [128, 166, 255, 255])

    renderer = vtk.vtkRenderer()
    renderer.SetBackground(colors.GetColor3d("Bkg"))
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetSize(500, 500)
    renderWindow.AddRenderer(renderer)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renderWindow)

    reader = vtk.vtkPLYReader()
    reader.SetFileName(fileName)
    reader.Update()

    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(reader.GetOutputPort())

    # create three models

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetAmbientColor(colors.GetColor3d("Red"))
    actor.GetProperty().SetDiffuseColor(colors.GetColor3d("A1Diff"))
    actor.GetProperty().SetSpecular(0.0)
    actor.GetProperty().SetDiffuse(0.5)
    actor.GetProperty().SetAmbient(0.3)
    actor.SetPosition(-0.1, 0.0, -0.1)
    renderer.AddActor(actor)

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetAmbientColor(colors.GetColor3d("A2Amb"))
    actor.GetProperty().SetDiffuseColor(colors.GetColor3d("A2Diff"))
    actor.GetProperty().SetSpecularColor(colors.GetColor3d("Black"))
    actor.GetProperty().SetSpecular(0.2)
    actor.GetProperty().SetDiffuse(0.9)
    actor.GetProperty().SetAmbient(0.1)
    actor.GetProperty().SetSpecularPower(10.0)
    renderer.AddActor(actor)

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetDiffuseColor(colors.GetColor3d("A3Amb"))
    actor.GetProperty().SetSpecularColor(colors.GetColor3d("White"))
    actor.GetProperty().SetSpecular(0.7)
    actor.GetProperty().SetDiffuse(0.4)
    actor.GetProperty().SetSpecularPower(60.0)
    actor.SetPosition(0.1, 0.0, 0.1)
    renderer.AddActor(actor)

    renderWindow.SetMultiSamples(0)

    # create the basic VTK render steps
    basicPasses = vtk.vtkRenderStepsPass()

    motion = vtk.vtkSimpleMotionBlurPass()
    motion.SetDelegatePass(basicPasses)

    # Tell the renderer to use our render pass pipeline.
    renderer.SetPass(motion)

    numRenders = 30

    renderer.GetActiveCamera().SetPosition(0, 0, -1)
    renderer.GetActiveCamera().SetFocalPoint(0, 0, 0)
    renderer.GetActiveCamera().SetViewUp(0, 1, 0)
    renderer.ResetCamera()
    renderer.GetActiveCamera().Azimuth(15.0)
    renderer.GetActiveCamera().Zoom(1.2)

    renderWindow.Render()

    for i in range(0, numRenders):
        renderer.GetActiveCamera().Azimuth(10.0 / numRenders)
        renderer.GetActiveCamera().Elevation(10.0 / numRenders)
        renderWindow.Render()

    iren.Start()


def get_program_parameters():
    import argparse
    description = 'Example of motion blur.'
    epilogue = '''
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='Armadillo.ply.')
    args = parser.parse_args()
    return args.filename


if __name__ == '__main__':
    main()
