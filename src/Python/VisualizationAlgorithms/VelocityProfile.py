#!/usr/bin/env python

# Translated from velProf.tcl.

import vtk


def main():
    fileName1, fileName2 = get_program_parameters()

    colors = vtk.vtkNamedColors()

    # Set the background color.
    colors.SetColor("BkgColor", [65, 99, 149, 255])

    # Read a vtk file
    #
    pl3d = vtk.vtkMultiBlockPLOT3DReader()
    pl3d.SetXYZFileName(fileName1)
    pl3d.SetQFileName(fileName2)
    pl3d.SetScalarFunctionNumber(100)  # Density
    pl3d.SetVectorFunctionNumber(202)  # Momentum
    pl3d.Update()

    pl3dOutput = pl3d.GetOutput().GetBlock(0)

    # What do we know about the data?
    # Get the extent of the data: imin,imax, jmin,jmax, kmin,kmax
    extent = pl3dOutput.GetExtent()
    scalarRange = pl3dOutput.GetScalarRange()

    # Planes are specified using a imin,imax, jmin,jmax, kmin,kmax coordinate
    # specification. Min and max i,j,k values are clamped to 0 and maximum value.
    # See the variable named extent for the values.
    #
    plane = vtk.vtkStructuredGridGeometryFilter()
    plane.SetInputData(pl3dOutput)
    plane.SetExtent(10, 10, 1, extent[3], 1, extent[5])

    plane2 = vtk.vtkStructuredGridGeometryFilter()
    plane2.SetInputData(pl3dOutput)
    plane2.SetExtent(30, 30, 1, extent[3], 1, extent[5])

    plane3 = vtk.vtkStructuredGridGeometryFilter()
    plane3.SetInputData(pl3dOutput)
    plane3.SetExtent(45, 45, 1, extent[3], 1, extent[5])

    # We use an append filter because that way we can do the warping, etc. just
    # using a single pipeline and actor.
    #
    appendF = vtk.vtkAppendPolyData()
    appendF.AddInputConnection(plane.GetOutputPort())
    appendF.AddInputConnection(plane2.GetOutputPort())
    appendF.AddInputConnection(plane3.GetOutputPort())

    # Warp
    warp = vtk.vtkWarpVector()
    warp.SetInputConnection(appendF.GetOutputPort())
    warp.SetScaleFactor(0.005)
    warp.Update()

    normals = vtk.vtkPolyDataNormals()
    normals.SetInputData(warp.GetPolyDataOutput())
    normals.SetFeatureAngle(45)

    planeMapper = vtk.vtkPolyDataMapper()
    planeMapper.SetInputConnection(normals.GetOutputPort())
    planeMapper.SetScalarRange(scalarRange)

    planeActor = vtk.vtkActor()
    planeActor.SetMapper(planeMapper)

    # The outline provides context for the data and the planes.
    outline = vtk.vtkStructuredGridOutlineFilter()
    outline.SetInputData(pl3dOutput)

    outlineMapper = vtk.vtkPolyDataMapper()
    outlineMapper.SetInputConnection(outline.GetOutputPort())

    outlineActor = vtk.vtkActor()
    outlineActor.SetMapper(outlineMapper)
    outlineActor.GetProperty().SetColor(colors.GetColor3d("Black"))

    # Create the RenderWindow, Renderer and both Actors
    #
    ren = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren)

    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Add the actors to the renderer, set the background and size
    #
    ren.AddActor(planeActor)
    ren.AddActor(outlineActor)
    ren.SetBackground(colors.GetColor3d("BkgColor"))
    renWin.SetSize(512, 512)

    iren.Initialize()

    renWin.Render()

    ren.GetActiveCamera().SetPosition(19.8562, -31.8912, 47.0755)
    ren.GetActiveCamera().SetFocalPoint(8.255, 0.147815, 29.7631)
    ren.GetActiveCamera().SetViewUp(-0.0333325, 0.465756, 0.884285)
    ren.GetActiveCamera().SetClippingRange(17.3078, 64.6375)
    renWin.Render()

    iren.Start()


def get_program_parameters():
    import argparse
    description = 'Produce figure 6–14(b) Flow momentum from the VTK Textbook.'
    epilogue = '''
        Produce figure 6–14(b) Flow momentum from the VTK Textbook.

   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename1', help='combxyz.bin.')
    parser.add_argument('filename2', help='combq.bin.')
    args = parser.parse_args()
    return args.filename1, args.filename2


if __name__ == '__main__':
    main()
