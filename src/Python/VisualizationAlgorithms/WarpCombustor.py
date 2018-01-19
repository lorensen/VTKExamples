#!/usr/bin/env python

"""
"""

import vtk


def main():
    colors = vtk.vtkNamedColors()

    fileName1, fileName2 = get_program_parameters()

    # Here we read data from a annular combustor. A combustor burns fuel and air
    # in a gas turbine (e.g., a jet engine) and the hot gas eventually makes its
    # way to the turbine section.
    #
    pl3d = vtk.vtkMultiBlockPLOT3DReader()
    pl3d.SetXYZFileName(fileName1)
    pl3d.SetQFileName(fileName2)
    pl3d.SetScalarFunctionNumber(100)
    pl3d.SetVectorFunctionNumber(202)
    pl3d.Update()

    pl3dOutput = pl3d.GetOutput().GetBlock(0)

    # Planes are specified using a imin,imax, jmin,jmax, kmin,kmax coordinate
    # specification. Min and max i,j,k values are clamped to 0 and maximum value.
    #
    plane = vtk.vtkStructuredGridGeometryFilter()
    plane.SetInputData(pl3dOutput)
    plane.SetExtent(10, 10, 1, 100, 1, 100)

    plane2 = vtk.vtkStructuredGridGeometryFilter()
    plane2.SetInputData(pl3dOutput)
    plane2.SetExtent(30, 30, 1, 100, 1, 100)
    plane3 = vtk.vtkStructuredGridGeometryFilter()
    plane3.SetInputData(pl3dOutput)
    plane3.SetExtent(45, 45, 1, 100, 1, 100)

    # We use an append filter because that way we can do the warping, etc. just
    # using a single pipeline and actor.
    #
    appendF = vtk.vtkAppendPolyData()
    appendF.AddInputConnection(plane.GetOutputPort())
    appendF.AddInputConnection(plane2.GetOutputPort())
    appendF.AddInputConnection(plane3.GetOutputPort())

    warp = vtk.vtkWarpScalar()
    warp.SetInputConnection(appendF.GetOutputPort())
    warp.UseNormalOn()
    warp.SetNormal(1.0, 0.0, 0.0)
    warp.SetScaleFactor(2.5)

    normals = vtk.vtkPolyDataNormals()
    normals.SetInputConnection(warp.GetOutputPort())
    normals.SetFeatureAngle(60)

    planeMapper = vtk.vtkPolyDataMapper()
    planeMapper.SetInputConnection(normals.GetOutputPort())
    planeMapper.SetScalarRange(pl3dOutput.GetScalarRange())

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

    # Create the usual graphics stuff.
    #
    ren1 = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren1)

    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    ren1.AddActor(outlineActor)
    ren1.AddActor(planeActor)
    ren1.SetBackground(colors.GetColor3d("Silver"))
    renWin.SetSize(640, 480)

    # Create an initial view.
    ren1.GetActiveCamera().SetClippingRange(3.95297, 50)
    ren1.GetActiveCamera().SetFocalPoint(8.88908, 0.595038, 29.3342)
    ren1.GetActiveCamera().SetPosition(-12.3332, 31.7479, 41.2387)
    ren1.GetActiveCamera().SetViewUp(0.060772, -0.319905, 0.945498)
    iren.Initialize()

    # Render the image.
    #
    renWin.Render()
    iren.Start()


def get_program_parameters():
    import argparse
    description = 'Extract "computational planes" from a structured dataset. '
    epilogue = '''

   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename1', help='combxyz.bin.')
    parser.add_argument('filename2', help='combq.bin.')
    args = parser.parse_args()
    return args.filename1, args.filename2


if __name__ == '__main__':
    main()
