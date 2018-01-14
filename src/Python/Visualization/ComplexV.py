#!/usr/bin/env python

import vtk


def main():
    fileName = get_program_parameters()

    colors = vtk.vtkNamedColors()

    reader = vtk.vtkStructuredPointsReader()
    reader.SetFileName(fileName)

    hhog = vtk.vtkHedgeHog()
    hhog.SetInputConnection(reader.GetOutputPort())
    hhog.SetScaleFactor(0.3)

    lut = vtk.vtkLookupTable()
    # lut.SetHueRange(.667, 0.0)
    lut.Build()

    hhogMapper = vtk.vtkPolyDataMapper()
    hhogMapper.SetInputConnection(hhog.GetOutputPort())
    hhogMapper.SetScalarRange(50, 550)
    hhogMapper.SetLookupTable(lut)

    hhogActor = vtk.vtkActor()
    hhogActor.SetMapper(hhogMapper)

    outline = vtk.vtkOutlineFilter()
    outline.SetInputConnection(reader.GetOutputPort())

    outlineMapper = vtk.vtkPolyDataMapper()
    outlineMapper.SetInputConnection(outline.GetOutputPort())

    outlineActor = vtk.vtkActor()
    outlineActor.SetMapper(outlineMapper)
    outlineActor.GetProperty().SetColor(0, 0, 0)

    aRenderer = vtk.vtkRenderer()
    aRenderWindow = vtk.vtkRenderWindow()
    aRenderWindow.AddRenderer(aRenderer)
    anInteractor = vtk.vtkRenderWindowInteractor()
    anInteractor.SetRenderWindow(aRenderWindow)
    aRenderWindow.SetSize(640, 480)

    aRenderer.AddActor(outlineActor)
    aRenderer.AddActor(hhogActor)

    aRenderer.SetBackground(colors.GetColor3d("Gray"))

    # Generate an interesting view.

    aRenderer.GetActiveCamera().SetFocalPoint(0, 0, 0)
    aRenderer.GetActiveCamera().SetPosition(1, 0, 0)
    aRenderer.GetActiveCamera().SetViewUp(0, 0, 1)
    aRenderer.ResetCamera()

    aRenderer.GetActiveCamera().Azimuth(60)
    aRenderer.GetActiveCamera().Elevation(30)
    aRenderer.GetActiveCamera().Dolly(1.1)
    aRenderer.ResetCameraClippingRange()

    aRenderWindow.Render()

    # Interact with the data.
    anInteractor.Start()


def get_program_parameters():
    import argparse
    description = 'Vector visualization techniques.'
    epilogue = '''
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='carotid.vtk.')
    args = parser.parse_args()
    return args.filename


if __name__ == '__main__':
    main()
