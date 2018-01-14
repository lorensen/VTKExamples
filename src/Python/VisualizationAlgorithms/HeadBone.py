#!/usr/bin/env python

import vtk


def main():
    fileName = get_program_parameters()

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

    reader = vtk.vtkMetaImageReader()
    reader.SetFileName(fileName)
    reader.Update()

    locator = vtk.vtkMergePoints()
    locator.SetDivisions(64, 64, 92)
    locator.SetNumberOfPointsPerBucket(2)
    locator.AutomaticOff()

    iso = vtk.vtkMarchingCubes()
    iso.SetInputConnection(reader.GetOutputPort())
    iso.ComputeGradientsOn()
    iso.ComputeScalarsOff()
    iso.SetValue(0, 1150)
    iso.SetLocator(locator)

    isoMapper = vtk.vtkPolyDataMapper()
    isoMapper.SetInputConnection(iso.GetOutputPort())
    isoMapper.ScalarVisibilityOff()

    isoActor = vtk.vtkActor()
    isoActor.SetMapper(isoMapper)
    isoActor.GetProperty().SetColor(colors.GetColor3d("Wheat"))

    outline = vtk.vtkOutlineFilter()
    outline.SetInputConnection(reader.GetOutputPort())

    outlineMapper = vtk.vtkPolyDataMapper()
    outlineMapper.SetInputConnection(outline.GetOutputPort())

    outlineActor = vtk.vtkActor()
    outlineActor.SetMapper(outlineMapper)

    # Add the actors to the renderer, set the background and size.
    #
    ren1.AddActor(outlineActor)
    ren1.AddActor(isoActor)
    ren1.SetBackground(colors.GetColor3d("SlateGray"))
    ren1.GetActiveCamera().SetFocalPoint(0, 0, 0)
    ren1.GetActiveCamera().SetPosition(0, -1, 0)
    ren1.GetActiveCamera().SetViewUp(0, 0, -1)
    ren1.ResetCamera()
    ren1.GetActiveCamera().Dolly(1.5)
    ren1.ResetCameraClippingRange()

    renWin.SetSize(640, 480)

    renWin.Render()
    iren.Start()


def get_program_parameters():
    import argparse
    description = 'Marching cubes surface of human bone.'
    epilogue = '''
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='FullHead.mhd.')
    args = parser.parse_args()
    return args.filename


if __name__ == '__main__':
    main()
