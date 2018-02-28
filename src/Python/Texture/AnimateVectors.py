#!/usr/bin/env python

import vtk


def main():
    fileNames = [""] * 2
    fileNames[0], fileNames[1] = get_program_parameters()

    # Generate the other vecAnim file names. There are 8 of them.
    tmpFn = fileNames[1][:-5]
    for i in range(2, 9):
        fileNames.append(tmpFn + str(i) + ".vtk")

    colors = vtk.vtkNamedColors()

    # Setup the render window, renderer, and interactor.
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderWindow)

    # Read the data.
    #
    # Create the pipeline.
    #
    reader = vtk.vtkStructuredPointsReader()
    reader.SetFileName(fileNames[0])

    threshold = vtk.vtkThresholdPoints()
    threshold.SetInputConnection(reader.GetOutputPort())
    threshold.ThresholdByUpper(200)

    line = vtk.vtkLineSource()
    line.SetResolution(1)

    lines = vtk.vtkGlyph3D()
    lines.SetInputConnection(threshold.GetOutputPort())
    lines.SetSourceConnection(line.GetOutputPort())
    lines.SetScaleFactor(0.005)
    lines.SetScaleModeToScaleByScalar()
    lines.Update()

    vectorMapper = vtk.vtkPolyDataMapper()
    vectorMapper.SetInputConnection(lines.GetOutputPort())
    vectorMapper.SetScalarRange(lines.GetOutput().GetScalarRange())

    vectorActor = vtk.vtkActor()
    vectorActor.SetMapper(vectorMapper)
    vectorActor.GetProperty().SetOpacity(0.99)
    vectorActor.GetProperty().SetLineWidth(1.5)

    # Outline
    outline = vtk.vtkOutlineFilter()
    outline.SetInputConnection(reader.GetOutputPort())

    outlineMapper = vtk.vtkPolyDataMapper()
    outlineMapper.SetInputConnection(outline.GetOutputPort())

    outlineActor = vtk.vtkActor()
    outlineActor.SetMapper(outlineMapper)
    outlineActor.GetProperty().SetColor(colors.GetColor3d("Black"))

    #  Texture maps.
    textureMaps = list()
    for i in range(2, len(fileNames)):
        tmap = vtk.vtkStructuredPointsReader()
        tmap.SetFileName(fileNames[i])

        texture = vtk.vtkTexture()
        texture.SetInputConnection(tmap.GetOutputPort())
        texture.InterpolateOff()
        texture.RepeatOff()
        textureMaps.append(texture)

    vectorActor.SetTexture(textureMaps[0])

    # Add the actors to the renderer, set the background and size.
    #
    renderer.AddActor(vectorActor)
    renderer.AddActor(outlineActor)

    cam1 = vtk.vtkCamera()
    cam1.SetClippingRange(17.4043, 870.216)
    cam1.SetFocalPoint(136.71, 104.025, 23)
    cam1.SetPosition(204.747, 258.939, 63.7925)
    cam1.SetViewUp(-0.102647, -0.210897, 0.972104)
    cam1.Zoom(1.5)
    renderer.SetActiveCamera(cam1)

    renderer.SetBackground(colors.GetColor3d("Wheat"))
    renderWindow.SetSize(640, 480)

    # Go into a loop.
    for j in range(0, 100):
        for i in range(0, len(textureMaps)):
            vectorActor.SetTexture(textureMaps[i])
            renderWindow.Render()
    interactor.Start()


def get_program_parameters():
    import argparse
    description = 'Texture maps can be animated as a function of time.'
    epilogue = '''
    This example uses texture map animation to simulate vector field motion.
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename1', help='carotid.vtk.')
    parser.add_argument('filename2', help='vecAnim1.vtk.')
    args = parser.parse_args()
    return args.filename1, args.filename2


if __name__ == '__main__':
    main()
