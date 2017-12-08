#!/usr/bin/env python

import vtk


def main():
    fileName, dataPoint = get_program_parameters()

    colors = vtk.vtkNamedColors()

    thickness = list()
    displacement = list()
    for i in range(0, 10):
        thickness.append('thickness' + str(i))
        displacement.append('displacement' + str(i))

    reader = list()
    warp = list()
    connect = list()
    mold = list()
    moldMapper = list()
    moldActor = list()
    connect2 = list()
    parison = list()
    normals2 = list()
    parisonMapper = list()
    parisonActor = list()
    cf = list()
    contourMapper = list()
    contours = list()
    ren = list()

    lut = vtk.vtkLookupTable()
    lut.SetHueRange(0.0, 0.66667)

    for i in range(0, 10):
        # Create the reader and warp the data vith vectors.
        reader.append(vtk.vtkDataSetReader())
        reader[i].SetFileName(fileName)
        reader[i].SetScalarsName(thickness[i])
        reader[i].SetVectorsName(displacement[i])
        reader[i].Update()

        warp.append(vtk.vtkWarpVector())
        warp[i].SetInputData(reader[i].GetUnstructuredGridOutput())

        # Extract the mold from the mesh using connectivity.
        connect.append(vtk.vtkConnectivityFilter())
        connect[i].SetInputConnection(warp[i].GetOutputPort())
        connect[i].SetExtractionModeToSpecifiedRegions()
        connect[i].AddSpecifiedRegion(0)
        connect[i].AddSpecifiedRegion(1)
        mold.append(vtk.vtkGeometryFilter())
        mold[i].SetInputConnection(connect[i].GetOutputPort())
        moldMapper.append(vtk.vtkDataSetMapper())
        moldMapper[i].SetInputConnection(mold[i].GetOutputPort())
        moldMapper[i].ScalarVisibilityOff()
        moldActor.append(vtk.vtkActor())
        moldActor[i].SetMapper(moldMapper[i])
        moldActor[i].GetProperty().SetColor(colors.GetColor3d("ivory_black"))
        moldActor[i].GetProperty().SetRepresentationToWireframe()

        # Extract the parison from the mesh using connectivity.
        connect2.append(vtk.vtkConnectivityFilter())
        connect2[i].SetInputConnection(warp[i].GetOutputPort())
        connect2[i].SetExtractionModeToSpecifiedRegions()
        connect2[i].AddSpecifiedRegion(2)
        parison.append(vtk.vtkGeometryFilter())
        parison[i].SetInputConnection(connect2[i].GetOutputPort())
        normals2.append(vtk.vtkPolyDataNormals())
        normals2[i].SetInputConnection(parison[i].GetOutputPort())
        normals2[i].SetFeatureAngle(60)
        parisonMapper.append(vtk.vtkPolyDataMapper())
        parisonMapper[i].SetInputConnection(normals2[i].GetOutputPort())
        parisonMapper[i].SetLookupTable(lut)
        parisonMapper[i].SetScalarRange(0.12, 1.0)
        parisonActor.append(vtk.vtkActor())
        parisonActor[i].SetMapper(parisonMapper[i])

        cf.append(vtk.vtkContourFilter())
        cf[i].SetInputConnection(connect2[i].GetOutputPort())
        cf[i].SetValue(0, 0.5)
        contourMapper.append(vtk.vtkPolyDataMapper())
        contourMapper[i].SetInputConnection(cf[i].GetOutputPort())
        contours.append(vtk.vtkActor())
        contours[i].SetMapper(contourMapper[i])

        ren.append(vtk.vtkRenderer())
        ren[i].AddActor(moldActor[i])
        ren[i].AddActor(parisonActor[i])
        ren[i].AddActor(contours[i])
        ren[i].SetBackground(colors.GetColor3d("AliceBlue"))
        ren[i].GetActiveCamera().SetPosition(50.973277, 12.298821, 29.102547)
        ren[i].GetActiveCamera().SetFocalPoint(0.141547, 12.298821, -0.245166)
        ren[i].GetActiveCamera().SetViewUp(-0.500000, 0.000000, 0.866025)
        ren[i].GetActiveCamera().SetClippingRange(36.640827, 78.614680)

    # Create the RenderWindow and RenderWindowInteractor.
    renWin = vtk.vtkRenderWindow()
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)
    rendererSizeX = 750
    rendererSizeY = 400
    renWinScale = 0.5
    renWin.SetWindowName("Blow")
    if 0 <= dataPoint < 10:
        renWin.AddRenderer(ren[dataPoint])
        renWin.SetSize(rendererSizeX, rendererSizeY)
    else:
        gridDimensionsX = 2
        gridDimensionsY = 5
        renWin.SetSize(int(rendererSizeX * gridDimensionsX * renWinScale),
                       int(rendererSizeY * gridDimensionsY * renWinScale))
        # Add and position the renders to the render window.
        viewPort = list()
        for row in range(0, gridDimensionsY):
            for col in range(0, gridDimensionsX):
                idx = row * gridDimensionsX + col
                x0 = float(col) / gridDimensionsX
                y0 = float(gridDimensionsY - row - 1) / gridDimensionsY
                x1 = float(col + 1) / gridDimensionsX
                y1 = float(gridDimensionsY - row) / gridDimensionsY
                viewPort[:] = []
                viewPort.append(x0)
                viewPort.append(y0)
                viewPort.append(x1)
                viewPort.append(y1)
                renWin.AddRenderer(ren[idx])
                ren[idx].SetViewport(viewPort)

    iren.Initialize()
    iren.Start()


def get_program_parameters():
    import argparse
    description = 'Produce figure 12-17 from the VTK Textbook.'
    epilogue = '''

        It is a translation of the original blow.tcl.

        data_point allows you to specify which frame is to be displayed.
        If data_point < 0 or data_point > 9 all ten frames are then displayed.

   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='blow.vtk.')
    parser.add_argument('data_point', default=-1, type=int, nargs='?', help='The particular color scheme to use.')
    args = parser.parse_args()
    return args.filename, args.data_point


if __name__ == '__main__':
    main()
