#!/usr/bin/env python

import vtk


def main():
    fileName = get_program_parameters()

    colors = vtk.vtkNamedColors()

    # Set the furniture colors.
    colors.SetColor("Furniture", [204, 204, 153, 255])

    scalarRange = [0.0, 0.0]
    maxTime = 0

    aren = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(aren)

    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    #
    # Read the data.
    #
    reader = vtk.vtkStructuredGridReader()
    reader.SetFileName(fileName)
    reader.Update()  # Force a read to occur.
    reader.GetOutput().GetLength()

    if reader.GetOutput().GetPointData().GetScalars():
        reader.GetOutput().GetPointData().GetScalars().GetRange(scalarRange)

    if reader.GetOutput().GetPointData().GetVectors():
        maxVelocity = reader.GetOutput().GetPointData().GetVectors().GetMaxNorm()
        maxTime = 4.0 * reader.GetOutput().GetLength() / maxVelocity

    #
    # Outline around the data.
    #
    outlineF = vtk.vtkStructuredGridOutlineFilter()
    outlineF.SetInputConnection(reader.GetOutputPort())
    outlineMapper = vtk.vtkPolyDataMapper()
    outlineMapper.SetInputConnection(outlineF.GetOutputPort())
    outline = vtk.vtkActor()
    outline.SetMapper(outlineMapper)
    outline.GetProperty().SetColor(colors.GetColor3d("LampBlack"))

    #
    # Set up shaded surfaces (i.e., supporting geometry).
    #
    doorGeom = vtk.vtkStructuredGridGeometryFilter()
    doorGeom.SetInputConnection(reader.GetOutputPort())
    doorGeom.SetExtent(27, 27, 14, 18, 0, 11)
    mapDoor = vtk.vtkPolyDataMapper()
    mapDoor.SetInputConnection(doorGeom.GetOutputPort())
    mapDoor.ScalarVisibilityOff()
    door = vtk.vtkActor()
    door.SetMapper(mapDoor)
    door.GetProperty().SetColor(colors.GetColor3d("Burlywood"))

    window1Geom = vtk.vtkStructuredGridGeometryFilter()
    window1Geom.SetInputConnection(reader.GetOutputPort())
    window1Geom.SetExtent(0, 0, 9, 18, 6, 12)
    mapWindow1 = vtk.vtkPolyDataMapper()
    mapWindow1.SetInputConnection(window1Geom.GetOutputPort())
    mapWindow1.ScalarVisibilityOff()
    window1 = vtk.vtkActor()
    window1.SetMapper(mapWindow1)
    window1.GetProperty().SetColor(colors.GetColor3d("SkyBlue"))
    window1.GetProperty().SetOpacity(.6)

    window2Geom = vtk.vtkStructuredGridGeometryFilter()
    window2Geom.SetInputConnection(reader.GetOutputPort())
    window2Geom.SetExtent(5, 12, 23, 23, 6, 12)
    mapWindow2 = vtk.vtkPolyDataMapper()
    mapWindow2.SetInputConnection(window2Geom.GetOutputPort())
    mapWindow2.ScalarVisibilityOff()
    window2 = vtk.vtkActor()
    window2.SetMapper(mapWindow2)
    window2.GetProperty().SetColor(colors.GetColor3d("SkyBlue"))
    window2.GetProperty().SetOpacity(.6)

    klower1Geom = vtk.vtkStructuredGridGeometryFilter()
    klower1Geom.SetInputConnection(reader.GetOutputPort())
    klower1Geom.SetExtent(17, 17, 0, 11, 0, 6)
    mapKlower1 = vtk.vtkPolyDataMapper()
    mapKlower1.SetInputConnection(klower1Geom.GetOutputPort())
    mapKlower1.ScalarVisibilityOff()
    klower1 = vtk.vtkActor()
    klower1.SetMapper(mapKlower1)
    klower1.GetProperty().SetColor(colors.GetColor3d("EggShell"))

    klower2Geom = vtk.vtkStructuredGridGeometryFilter()
    klower2Geom.SetInputConnection(reader.GetOutputPort())
    klower2Geom.SetExtent(19, 19, 0, 11, 0, 6)
    mapKlower2 = vtk.vtkPolyDataMapper()
    mapKlower2.SetInputConnection(klower2Geom.GetOutputPort())
    mapKlower2.ScalarVisibilityOff()
    klower2 = vtk.vtkActor()
    klower2.SetMapper(mapKlower2)
    klower2.GetProperty().SetColor(colors.GetColor3d("EggShell"))

    klower3Geom = vtk.vtkStructuredGridGeometryFilter()
    klower3Geom.SetInputConnection(reader.GetOutputPort())
    klower3Geom.SetExtent(17, 19, 0, 0, 0, 6)
    mapKlower3 = vtk.vtkPolyDataMapper()
    mapKlower3.SetInputConnection(klower3Geom.GetOutputPort())
    mapKlower3.ScalarVisibilityOff()
    klower3 = vtk.vtkActor()
    klower3.SetMapper(mapKlower3)
    klower3.GetProperty().SetColor(colors.GetColor3d("EggShell"))

    klower4Geom = vtk.vtkStructuredGridGeometryFilter()
    klower4Geom.SetInputConnection(reader.GetOutputPort())
    klower4Geom.SetExtent(17, 19, 11, 11, 0, 6)
    mapKlower4 = vtk.vtkPolyDataMapper()
    mapKlower4.SetInputConnection(klower4Geom.GetOutputPort())
    mapKlower4.ScalarVisibilityOff()
    klower4 = vtk.vtkActor()
    klower4.SetMapper(mapKlower4)
    klower4.GetProperty().SetColor(colors.GetColor3d("EggShell"))

    klower5Geom = vtk.vtkStructuredGridGeometryFilter()
    klower5Geom.SetInputConnection(reader.GetOutputPort())
    klower5Geom.SetExtent(17, 19, 0, 11, 0, 0)
    mapKlower5 = vtk.vtkPolyDataMapper()
    mapKlower5.SetInputConnection(klower5Geom.GetOutputPort())
    mapKlower5.ScalarVisibilityOff()
    klower5 = vtk.vtkActor()
    klower5.SetMapper(mapKlower5)
    klower5.GetProperty().SetColor(colors.GetColor3d("EggShell"))

    klower6Geom = vtk.vtkStructuredGridGeometryFilter()
    klower6Geom.SetInputConnection(reader.GetOutputPort())
    klower6Geom.SetExtent(17, 19, 0, 7, 6, 6)
    mapKlower6 = vtk.vtkPolyDataMapper()
    mapKlower6.SetInputConnection(klower6Geom.GetOutputPort())
    mapKlower6.ScalarVisibilityOff()
    klower6 = vtk.vtkActor()
    klower6.SetMapper(mapKlower6)
    klower6.GetProperty().SetColor(colors.GetColor3d("EggShell"))

    klower7Geom = vtk.vtkStructuredGridGeometryFilter()
    klower7Geom.SetInputConnection(reader.GetOutputPort())
    klower7Geom.SetExtent(17, 19, 9, 11, 6, 6)
    mapKlower7 = vtk.vtkPolyDataMapper()
    mapKlower7.SetInputConnection(klower7Geom.GetOutputPort())
    mapKlower7.ScalarVisibilityOff()
    klower7 = vtk.vtkActor()
    klower7.SetMapper(mapKlower7)
    klower7.GetProperty().SetColor(colors.GetColor3d("EggShell"))

    hood1Geom = vtk.vtkStructuredGridGeometryFilter()
    hood1Geom.SetInputConnection(reader.GetOutputPort())
    hood1Geom.SetExtent(17, 17, 0, 11, 11, 16)
    mapHood1 = vtk.vtkPolyDataMapper()
    mapHood1.SetInputConnection(hood1Geom.GetOutputPort())
    mapHood1.ScalarVisibilityOff()
    hood1 = vtk.vtkActor()
    hood1.SetMapper(mapHood1)
    hood1.GetProperty().SetColor(colors.GetColor3d("Silver"))

    hood2Geom = vtk.vtkStructuredGridGeometryFilter()
    hood2Geom.SetInputConnection(reader.GetOutputPort())
    hood2Geom.SetExtent(19, 19, 0, 11, 11, 16)
    mapHood2 = vtk.vtkPolyDataMapper()
    mapHood2.SetInputConnection(hood2Geom.GetOutputPort())
    mapHood2.ScalarVisibilityOff()
    hood2 = vtk.vtkActor()
    hood2.SetMapper(mapHood2)
    hood2.GetProperty().SetColor(colors.GetColor3d("Furniture"))

    hood3Geom = vtk.vtkStructuredGridGeometryFilter()
    hood3Geom.SetInputConnection(reader.GetOutputPort())
    hood3Geom.SetExtent(17, 19, 0, 0, 11, 16)
    mapHood3 = vtk.vtkPolyDataMapper()
    mapHood3.SetInputConnection(hood3Geom.GetOutputPort())
    mapHood3.ScalarVisibilityOff()
    hood3 = vtk.vtkActor()
    hood3.SetMapper(mapHood3)
    hood3.GetProperty().SetColor(colors.GetColor3d("Furniture"))

    hood4Geom = vtk.vtkStructuredGridGeometryFilter()
    hood4Geom.SetInputConnection(reader.GetOutputPort())
    hood4Geom.SetExtent(17, 19, 11, 11, 11, 16)
    mapHood4 = vtk.vtkPolyDataMapper()
    mapHood4.SetInputConnection(hood4Geom.GetOutputPort())
    mapHood4.ScalarVisibilityOff()
    hood4 = vtk.vtkActor()
    hood4.SetMapper(mapHood4)
    hood4.GetProperty().SetColor(colors.GetColor3d("Furniture"))

    hood6Geom = vtk.vtkStructuredGridGeometryFilter()
    hood6Geom.SetInputConnection(reader.GetOutputPort())
    hood6Geom.SetExtent(17, 19, 0, 11, 16, 16)
    mapHood6 = vtk.vtkPolyDataMapper()
    mapHood6.SetInputConnection(hood6Geom.GetOutputPort())
    mapHood6.ScalarVisibilityOff()
    hood6 = vtk.vtkActor()
    hood6.SetMapper(mapHood6)
    hood6.GetProperty().SetColor(colors.GetColor3d("Furniture"))

    cookingPlateGeom = vtk.vtkStructuredGridGeometryFilter()
    cookingPlateGeom.SetInputConnection(reader.GetOutputPort())
    cookingPlateGeom.SetExtent(17, 19, 7, 9, 6, 6)
    mapCookingPlate = vtk.vtkPolyDataMapper()
    mapCookingPlate.SetInputConnection(cookingPlateGeom.GetOutputPort())
    mapCookingPlate.ScalarVisibilityOff()
    cookingPlate = vtk.vtkActor()
    cookingPlate.SetMapper(mapCookingPlate)
    cookingPlate.GetProperty().SetColor(colors.GetColor3d("Tomato"))

    filterGeom = vtk.vtkStructuredGridGeometryFilter()
    filterGeom.SetInputConnection(reader.GetOutputPort())
    filterGeom.SetExtent(17, 19, 7, 9, 11, 11)
    mapFilter = vtk.vtkPolyDataMapper()
    mapFilter.SetInputConnection(filterGeom.GetOutputPort())
    mapFilter.ScalarVisibilityOff()
    sgfilter = vtk.vtkActor()
    sgfilter.SetMapper(mapFilter)
    sgfilter.GetProperty().SetColor(colors.GetColor3d("Furniture"))
    #
    # regular streamlines
    #
    line = vtk.vtkLineSource()
    line.SetResolution(39)
    line.SetPoint1(0.08, 2.50, 0.71)
    line.SetPoint2(0.08, 4.50, 0.71)
    rakeMapper = vtk.vtkPolyDataMapper()
    rakeMapper.SetInputConnection(line.GetOutputPort())
    rake = vtk.vtkActor()
    rake.SetMapper(rakeMapper)

    streamers = vtk.vtkStreamTracer()
    # streamers.DebugOn()
    streamers.SetInputConnection(reader.GetOutputPort())
    streamers.SetSourceConnection(line.GetOutputPort())
    streamers.SetMaximumPropagation(maxTime)
    streamers.SetInitialIntegrationStep(.5)
    streamers.SetMinimumIntegrationStep(.1)
    streamers.SetIntegratorType(2)
    streamers.Update()

    streamersMapper = vtk.vtkPolyDataMapper()
    streamersMapper.SetInputConnection(streamers.GetOutputPort())
    streamersMapper.SetScalarRange(scalarRange)

    lines = vtk.vtkActor()
    lines.SetMapper(streamersMapper)
    lines.GetProperty().SetColor(colors.GetColor3d("Black"))

    aren.TwoSidedLightingOn()

    aren.AddActor(outline)
    aren.AddActor(door)
    aren.AddActor(window1)
    aren.AddActor(window2)
    aren.AddActor(klower1)
    aren.AddActor(klower2)
    aren.AddActor(klower3)
    aren.AddActor(klower4)
    aren.AddActor(klower5)
    aren.AddActor(klower6)
    aren.AddActor(klower7)
    aren.AddActor(hood1)
    aren.AddActor(hood2)
    aren.AddActor(hood3)
    aren.AddActor(hood4)
    aren.AddActor(hood6)
    aren.AddActor(cookingPlate)
    aren.AddActor(sgfilter)
    aren.AddActor(lines)
    aren.AddActor(rake)

    aren.SetBackground(colors.GetColor3d("SlateGray"))

    aCamera = vtk.vtkCamera()
    aren.SetActiveCamera(aCamera)
    aren.ResetCamera()

    aCamera.SetFocalPoint(3.505, 2.505, 1.255)
    aCamera.SetPosition(3.505, 24.6196, 1.255)
    aCamera.SetViewUp(0, 0, 1)
    aCamera.Azimuth(60)
    aCamera.Elevation(30)
    aCamera.Dolly(1.5)
    aren.ResetCameraClippingRange()

    renWin.SetSize(640, 512)
    renWin.Render()

    # interact with data
    iren.Start()


def get_program_parameters():
    import argparse
    description = 'Flow velocity computed for a small kitchen (top and side view).'
    epilogue = '''
    Forty streamlines start along the rake positioned under the window.
    Some eventually travel over the hot stove and are convected upwards.
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='kitchen.vtk.')
    args = parser.parse_args()
    return args.filename


if __name__ == '__main__':
    main()
