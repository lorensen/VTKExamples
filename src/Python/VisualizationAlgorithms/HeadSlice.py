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

    extractVOI = vtk.vtkExtractVOI()
    extractVOI.SetInputConnection(reader.GetOutputPort())
    extractVOI.SetVOI(0, 255, 0, 255, 45, 45)

    iso = vtk.vtkContourFilter()
    iso.SetInputConnection(extractVOI.GetOutputPort())
    iso.GenerateValues(12, 500, 1150)

    isoMapper = vtk.vtkPolyDataMapper()
    isoMapper.SetInputConnection(iso.GetOutputPort())
    isoMapper.ScalarVisibilityOff()

    isoActor = vtk.vtkActor()
    isoActor.SetMapper(isoMapper)
    isoActor.GetProperty().SetColor(colors.GetColor3d("Wheat"))

    outline = vtk.vtkOutlineFilter()
    outline.SetInputConnection(extractVOI.GetOutputPort())

    outlineMapper = vtk.vtkPolyDataMapper()
    outlineMapper.SetInputConnection(outline.GetOutputPort())

    outlineActor = vtk.vtkActor()
    outlineActor.SetMapper(outlineMapper)

    # Add the actors to the renderer, set the background and size.
    #
    ren1.AddActor(outlineActor)
    ren1.AddActor(isoActor)
    ren1.SetBackground(colors.GetColor3d("SlateGray"))
    ren1.ResetCamera()
    ren1.GetActiveCamera().Dolly(1.5)
    ren1.ResetCameraClippingRange()

    renWin.SetSize(640, 480)

    renWin.Render()
    iren.Start()


def get_program_parameters():
    import argparse
    description = 'Marching squares are used to generate contour lines.'
    epilogue = '''
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='FullHead.mhd.')
    args = parser.parse_args()
    return args.filename


if __name__ == '__main__':
    main()
