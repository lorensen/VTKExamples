#!/usr/bin/env python

import vtk


def main():
    fileName = get_program_parameters()

    colors = vtk.vtkNamedColors()

    ren1 = vtk.vtkRenderer()

    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren1)

    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Create the pipeline.
    #
    reader = vtk.vtkStructuredPointsReader()
    reader.SetFileName(fileName)

    psource = vtk.vtkPointSource()
    psource.SetNumberOfPoints(25)
    psource.SetCenter(133.1, 116.3, 5.0)
    psource.SetRadius(2.0)

    threshold = vtk.vtkThresholdPoints()
    threshold.SetInputConnection(reader.GetOutputPort())
    threshold.ThresholdByUpper(275)

    streamers = vtk.vtkStreamTracer()
    streamers.SetInputConnection(reader.GetOutputPort())
    streamers.SetSourceConnection(psource.GetOutputPort())
    # streamers.SetMaximumPropagationUnitToTimeUnit()
    streamers.SetMaximumPropagation(100.0)
    # streamers.SetInitialIntegrationStepUnitToCellLengthUnit()
    streamers.SetInitialIntegrationStep(0.2)
    streamers.SetTerminalSpeed(.01)
    streamers.Update()
    scalarRange = [0] * 2
    scalarRange[0] = streamers.GetOutput().GetPointData().GetScalars().GetRange()[0]
    scalarRange[1] = streamers.GetOutput().GetPointData().GetScalars().GetRange()[1]
    print("range: ", scalarRange[0], ", ", scalarRange[1])

    tubes = vtk.vtkTubeFilter()
    tubes.SetInputConnection(streamers.GetOutputPort())
    tubes.SetRadius(0.3)
    tubes.SetNumberOfSides(6)
    tubes.SetVaryRadius(0)

    lut = vtk.vtkLookupTable()
    lut.SetHueRange(.667, 0.0)
    lut.Build()

    streamerMapper = vtk.vtkPolyDataMapper()
    streamerMapper.SetInputConnection(tubes.GetOutputPort())
    streamerMapper.SetScalarRange(scalarRange[0], scalarRange[1])
    streamerMapper.SetLookupTable(lut)

    streamerActor = vtk.vtkActor()
    streamerActor.SetMapper(streamerMapper)

    # Speed contours.
    iso = vtk.vtkContourFilter()
    iso.SetInputConnection(reader.GetOutputPort())
    iso.SetValue(0, 175)

    isoMapper = vtk.vtkPolyDataMapper()
    isoMapper.SetInputConnection(iso.GetOutputPort())
    isoMapper.ScalarVisibilityOff()

    isoActor = vtk.vtkActor()
    isoActor.SetMapper(isoMapper)
    isoActor.GetProperty().SetRepresentationToWireframe()
    isoActor.GetProperty().SetOpacity(0.25)

    # Outline
    outline = vtk.vtkOutlineFilter()
    outline.SetInputConnection(reader.GetOutputPort())

    outlineMapper = vtk.vtkPolyDataMapper()
    outlineMapper.SetInputConnection(outline.GetOutputPort())

    outlineActor = vtk.vtkActor()
    outlineActor.SetMapper(outlineMapper)
    outlineActor.GetProperty().SetColor(colors.GetColor3d("Black"))

    # Add the actors to the renderer, set the background and size.
    #
    ren1.AddActor(outlineActor)
    ren1.AddActor(streamerActor)
    ren1.AddActor(isoActor)
    ren1.SetBackground(colors.GetColor3d("Wheat"))
    renWin.SetSize(640, 480)

    cam1 = vtk.vtkCamera()
    cam1.SetClippingRange(17.4043, 870.216)
    cam1.SetFocalPoint(136.71, 104.025, 23)
    cam1.SetPosition(204.747, 258.939, 63.7925)
    cam1.SetViewUp(-0.102647, -0.210897, 0.972104)
    cam1.Zoom(1.6)
    ren1.SetActiveCamera(cam1)

    # Render the image.
    #
    renWin.Render()
    iren.Start()


def get_program_parameters():
    import argparse
    description = 'Visualizing blood flow in human carotid arteries.'
    epilogue = '''
    Streamtubes of blood velocity are generated. 
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='carotid.vtk.')
    args = parser.parse_args()
    return args.filename


if __name__ == '__main__':
    main()
