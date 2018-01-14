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
    reader = vtk.vtkStructuredPointsReader()
    reader.SetFileName(fileName)

    iso = vtk.vtkContourFilter()
    iso.SetInputConnection(reader.GetOutputPort())
    iso.SetValue(0, 128)

    isoMapper = vtk.vtkPolyDataMapper()
    isoMapper.SetInputConnection(iso.GetOutputPort())
    isoMapper.ScalarVisibilityOff()

    isoActor = vtk.vtkActor()
    isoActor.SetMapper(isoMapper)
    isoActor.GetProperty().SetColor(colors.GetColor3d("Banana"))

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
    renWin.SetSize(640, 512)

    # Render the image.
    #
    ren1.ResetCamera()
    ren1.GetActiveCamera().Azimuth(30)
    ren1.GetActiveCamera().Elevation(30)
    renWin.Render()
    iren.Start()


def get_program_parameters():
    import argparse
    description = 'Marching cubes surface of iron-protein.'
    epilogue = '''
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='ironProt.vtk.')
    args = parser.parse_args()
    return args.filename


if __name__ == '__main__':
    main()
