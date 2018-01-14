#!/usr/bin/env python

import vtk


def main():
    xyzFile, qFile = get_program_parameters()

    colors = vtk.vtkNamedColors()

    # Create pipeline. Read structured grid data.
    #
    pl3d = vtk.vtkMultiBlockPLOT3DReader()
    pl3d.SetXYZFileName(xyzFile)
    pl3d.SetQFileName(qFile)
    pl3d.SetScalarFunctionNumber(100)
    pl3d.SetVectorFunctionNumber(202)
    pl3d.Update()

    pl3dOutput = pl3d.GetOutput().GetBlock(0)

    # A convenience, use this filter to limit data for experimentation.
    extract = vtk.vtkExtractGrid()
    extract.SetVOI(1, 55, -1000, 1000, -1000, 1000)
    extract.SetInputData(pl3dOutput)

    # The (implicit) plane is used to do the cutting
    plane = vtk.vtkPlane()
    plane.SetOrigin(0, 4, 2)
    plane.SetNormal(0, 1, 0)

    # The cutter is set up to process each contour value over all cells
    # (SetSortByToSortByCell). This results in an ordered output of polygons
    # which is key to the compositing.
    cutter = vtk.vtkCutter()
    cutter.SetInputConnection(extract.GetOutputPort())
    cutter.SetCutFunction(plane)
    cutter.GenerateCutScalarsOff()
    cutter.SetSortByToSortByCell()

    clut = vtk.vtkLookupTable()
    clut.SetHueRange(0, 0.67)
    clut.Build()

    cutterMapper = vtk.vtkPolyDataMapper()
    cutterMapper.SetInputConnection(cutter.GetOutputPort())
    cutterMapper.SetScalarRange(0.18, 0.7)
    cutterMapper.SetLookupTable(clut)

    cut = vtk.vtkActor()
    cut.SetMapper(cutterMapper)

    # Add in some surface geometry for interest.
    iso = vtk.vtkContourFilter()
    iso.SetInputData(pl3dOutput)
    iso.SetValue(0, .22)

    normals = vtk.vtkPolyDataNormals()
    normals.SetInputConnection(iso.GetOutputPort())
    normals.SetFeatureAngle(60)

    isoMapper = vtk.vtkPolyDataMapper()
    isoMapper.SetInputConnection(normals.GetOutputPort())
    isoMapper.ScalarVisibilityOff()

    isoActor = vtk.vtkActor()
    isoActor.SetMapper(isoMapper)
    isoActor.GetProperty().SetDiffuseColor(colors.GetColor3d("Tomato"))
    isoActor.GetProperty().SetSpecularColor(colors.GetColor3d("White"))
    isoActor.GetProperty().SetDiffuse(0.8)
    isoActor.GetProperty().SetSpecular(0.5)
    isoActor.GetProperty().SetSpecularPower(30)

    outline = vtk.vtkStructuredGridOutlineFilter()
    outline.SetInputData(pl3dOutput)

    outlineStrip = vtk.vtkStripper()
    outlineStrip.SetInputConnection(outline.GetOutputPort())

    outlineTubes = vtk.vtkTubeFilter()
    outlineTubes.SetInputConnection(outline.GetOutputPort())
    outlineTubes.SetInputConnection(outlineStrip.GetOutputPort())
    outlineTubes.SetRadius(0.1)

    outlineMapper = vtk.vtkPolyDataMapper()
    outlineMapper.SetInputConnection(outlineTubes.GetOutputPort())

    outlineActor = vtk.vtkActor()
    outlineActor.SetMapper(outlineMapper)

    # Create the RenderWindow, Renderer and Interactor.
    #
    ren1 = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren1)
    iren = vtk.vtkRenderWindowInteractor()

    iren.SetRenderWindow(renWin)

    # Add the actors to the renderer, set the background and size.
    #
    ren1.AddActor(outlineActor)
    outlineActor.GetProperty().SetColor(colors.GetColor3d("Banana"))
    ren1.AddActor(isoActor)
    isoActor.VisibilityOn()
    ren1.AddActor(cut)

    n = 20
    opacity = 1.0 / float(n) * 5.0
    cut.GetProperty().SetOpacity(1)
    ren1.SetBackground(colors.GetColor3d("SlateGray"))
    renWin.SetSize(640, 480)

    ren1.GetActiveCamera().SetClippingRange(3.95297, 50)
    ren1.GetActiveCamera().SetFocalPoint(9.71821, 0.458166, 29.3999)
    ren1.GetActiveCamera().SetPosition(2.7439, -37.3196, 38.7167)
    ren1.GetActiveCamera().ComputeViewPlaneNormal()
    ren1.GetActiveCamera().SetViewUp(-0.16123, 0.264271, 0.950876)

    # Cut: generates n cut planes normal to camera's view plane.
    #
    plane.SetNormal(ren1.GetActiveCamera().GetViewPlaneNormal())
    plane.SetOrigin(ren1.GetActiveCamera().GetFocalPoint())
    cutter.GenerateValues(n, -5, 5)
    clut.SetAlphaRange(opacity, opacity)
    renWin.Render()

    iren.Start()


def get_program_parameters():
    import argparse
    description = 'Perform psuedo volume rendering in a structured grid by compositing translucent cut planes.'
    epilogue = '''
    This same trick can be used for unstructured grids.
    Note that for better results, more planes can be created.
    Also, if your data is vtkImageData, there are much faster
     methods for volume rendering.
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename1', help='combxyz.bin.')
    parser.add_argument('filename2', help='combq.bin.')
    args = parser.parse_args()
    return args.filename1, args.filename2


if __name__ == '__main__':
    main()
