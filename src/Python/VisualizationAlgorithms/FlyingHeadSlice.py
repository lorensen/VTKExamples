#!/usr/bin/env python

import vtk


def main():
    fileName, useContouring = get_program_parameters()
    if useContouring:
        print('Using vtkContourFilter.')
    else:
        print('Using vtkFlyingEdges2D.')

    colors = vtk.vtkNamedColors()

    # Create the RenderWindow, Renderer and Interactor.
    ren1 = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren1)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Create the pipeline.
    reader = vtk.vtkMetaImageReader()
    reader.SetFileName(fileName)
    reader.Update()

    extractVOI = vtk.vtkExtractVOI()
    extractVOI.SetInputConnection(reader.GetOutputPort())
    extractVOI.SetVOI(0, 255, 0, 255, 45, 45)
    # scalarRange = extractVOI.GetOutput().GetScalarRange()
    scalarRange = [500, 1150]
    # print(scalarRange)

    contour = vtk.vtkContourFilter()
    flyingEdges = vtk.vtkFlyingEdges2D()
    isoMapper = vtk.vtkPolyDataMapper()
    if useContouring:
        contour.SetInputConnection(extractVOI.GetOutputPort())
        contour.GenerateValues(12, scalarRange)
        isoMapper.SetInputConnection(contour.GetOutputPort())
    else:
        flyingEdges.SetInputConnection(extractVOI.GetOutputPort())
        flyingEdges.GenerateValues(12, scalarRange)
        isoMapper.SetInputConnection(flyingEdges.GetOutputPort())

    isoMapper.ScalarVisibilityOn()
    isoMapper.SetScalarRange(scalarRange)

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
    ren1.AddActor(outlineActor)
    ren1.AddActor(isoActor)
    ren1.SetBackground(colors.GetColor3d("SlateGray"))
    ren1.ResetCamera()
    ren1.GetActiveCamera().Dolly(1.5)
    ren1.ResetCameraClippingRange()

    renWin.SetSize(640, 480)
    renWin.SetWindowName('Full Head')
    renWin.Render()

    iren.Start()


def get_program_parameters():
    import argparse
    description = 'Either vtkFlyingEdges2D or vtkContourFilter is used to generate contour lines.'
    epilogue = '''
    Generate 2D contour lines, corresponding to tissue density, on one CT slice through the head.
    The contour lines are colored by the tissue density.
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='FullHead.mhd.')
    parser.add_argument('-useContouring', '--useContouring', action='store_true',
                        help='Use vtkContourFilter instead of vtkFlyingEdges2D.')
    args = parser.parse_args()
    return args.filename, args.useContouring


if __name__ == '__main__':
    main()
