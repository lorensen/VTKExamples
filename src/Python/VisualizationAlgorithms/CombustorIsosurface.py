#!/usr/bin/env python

import vtk


def main():
    xyzFile, qFile = get_program_parameters()

    colors = vtk.vtkNamedColors()

    # Create the RenderWindow, Renderer and Interactor.
    #

    ren1 = vtk.vtkRenderer()

    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren1)

    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Create the pipeline.
    #

    pl3d = vtk.vtkMultiBlockPLOT3DReader()
    pl3d.SetXYZFileName(xyzFile)
    pl3d.SetQFileName(qFile)
    pl3d.SetScalarFunctionNumber(100)
    pl3d.SetVectorFunctionNumber(202)
    pl3d.Update()

    iso = vtk.vtkContourFilter()
    iso.SetInputData(pl3d.GetOutput().GetBlock(0))
    iso.SetValue(0, 0.38)

    normals = vtk.vtkPolyDataNormals()
    normals.SetInputConnection(iso.GetOutputPort())
    normals.SetFeatureAngle(45)

    isoMapper = vtk.vtkPolyDataMapper()
    isoMapper.SetInputConnection(normals.GetOutputPort())
    isoMapper.ScalarVisibilityOff()

    isoActor = vtk.vtkActor()
    isoActor.SetMapper(isoMapper)
    isoActor.GetProperty().SetColor(colors.GetColor3d("bisque"))

    outline = vtk.vtkStructuredGridOutlineFilter()
    outline.SetInputConnection(pl3d.GetOutputPort())

    outlineMapper = vtk.vtkPolyDataMapper()
    outlineMapper.SetInputConnection(outline.GetOutputPort())

    outlineActor = vtk.vtkActor()
    outlineActor.SetMapper(outlineMapper)

    # Add the actors to the renderer, set the background and size.
    #
    ren1.AddActor(outlineActor)
    ren1.AddActor(isoActor)
    ren1.SetBackground(colors.GetColor3d("SlateGray"))
    renWin.SetSize(640, 480)

    ren1.GetActiveCamera().SetFocalPoint(9.71821, 0.458166, 29.3999)
    ren1.GetActiveCamera().SetPosition(2.7439, -37.3196, 38.7167)
    ren1.GetActiveCamera().SetViewUp(-0.16123, 0.264271, 0.950876)
    ren1.ResetCameraClippingRange()

    # Render the image.
    #
    renWin.Render()
    iren.Start()


def get_program_parameters():
    import argparse
    description = 'Marching cubes surface of flow density.'
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
