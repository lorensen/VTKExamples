#!/usr/bin/env python

import vtk


def main():
    xyzFilename, qFilename = get_program_parameters()

    colors = vtk.vtkNamedColors()

    aren = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(aren)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    scalarRange = [0.0] * 2
    c = [0.0] * 3
    maxTime = 0.0

    reader = vtk.vtkMultiBlockPLOT3DReader()
    reader.SetXYZFileName(xyzFilename)
    reader.SetQFileName(qFilename)
    reader.Update()  # Force a read to occur.

    pd = reader.GetOutput().GetBlock(0)
    pd.GetCenter(c)
    if pd.GetPointData().GetScalars():
        pd.GetPointData().GetScalars().GetRange(scalarRange)
    if pd.GetPointData().GetVectors():
        maxVelocity = pd.GetPointData().GetVectors().GetMaxNorm()
        maxTime = 20.0 * pd.GetLength() / maxVelocity

    outlineF = vtk.vtkStructuredGridOutlineFilter()
    outlineF.SetInputData(pd)

    outlineMapper = vtk.vtkPolyDataMapper()
    outlineMapper.SetInputConnection(outlineF.GetOutputPort())

    outline = vtk.vtkActor()
    outline.SetMapper(outlineMapper)
    outline.GetProperty().SetColor(colors.GetColor3d("Moccasin"))
    outline.GetProperty().SetLineWidth(2.0)

    #
    # Some geometry for context
    #
    wall = vtk.vtkStructuredGridGeometryFilter()
    wall.SetInputData(pd)
    wall.SetExtent(0, 100, 0, 100, 0, 0)

    wallMap = vtk.vtkPolyDataMapper()
    wallMap.SetInputConnection(wall.GetOutputPort())
    wallMap.ScalarVisibilityOff()

    wallActor = vtk.vtkActor()
    wallActor.SetMapper(wallMap)
    wallActor.GetProperty().SetColor(colors.GetColor3d("Silver"))

    fin = vtk.vtkStructuredGridGeometryFilter()
    fin.SetInputData(pd)
    fin.SetExtent(0, 100, 0, 0, 0, 100)

    finMap = vtk.vtkPolyDataMapper()
    finMap.SetInputConnection(fin.GetOutputPort())
    finMap.ScalarVisibilityOff()

    finActor = vtk.vtkActor()
    finActor.SetMapper(finMap)
    finActor.GetProperty().SetColor(colors.GetColor3d("Silver"))
    #
    # regular streamlines
    #
    line1 = vtk.vtkLineSource()
    line1.SetResolution(25)
    line1.SetPoint1(-6.36, 0.25, 0.06)
    line1.SetPoint2(-6.36, 0.25, 5.37)

    rakeMapper = vtk.vtkPolyDataMapper()
    rakeMapper.SetInputConnection(line1.GetOutputPort())

    rake1 = vtk.vtkActor()
    rake1.SetMapper(rakeMapper)
    rake1.GetProperty().SetColor(0.0, 0.0, 0.0)
    rake1.GetProperty().SetLineWidth(5)

    streamers = vtk.vtkStreamTracer()
    # streamers.DebugOn()
    streamers.SetInputConnection(reader.GetOutputPort())
    streamers.SetSourceConnection(line1.GetOutputPort())
    streamers.SetMaximumPropagation(maxTime)
    streamers.SetInitialIntegrationStep(.2)
    streamers.SetMinimumIntegrationStep(.01)
    streamers.SetIntegratorType(2)
    streamers.Update()

    streamersMapper = vtk.vtkPolyDataMapper()
    streamersMapper.SetInputConnection(streamers.GetOutputPort())
    streamersMapper.SetScalarRange(scalarRange)

    lines = vtk.vtkActor()
    lines.SetMapper(streamersMapper)

    aren.AddActor(outline)
    aren.AddActor(wallActor)
    aren.AddActor(finActor)
    aren.AddActor(rake1)
    aren.AddActor(lines)
    aren.SetBackground(0.5, 0.5, 0.5)

    aren.ResetCamera()
    aren.GetActiveCamera().Elevation(30.0)
    aren.GetActiveCamera().Azimuth(30.0)
    aren.GetActiveCamera().Dolly(1.2)
    aren.ResetCameraClippingRange()

    renWin.SetSize(640, 480)
    renWin.Render()

    # Interact with the data.
    iren.Start()


def get_program_parameters():
    import argparse
    description = 'This example shows airflow around a blunt fin.'
    epilogue = '''
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename1', help='bluntfinxyz.bin.')
    parser.add_argument('filename2', help='bluntfinq.bin.')
    args = parser.parse_args()
    return args.filename1, args.filename2


if __name__ == '__main__':
    main()
