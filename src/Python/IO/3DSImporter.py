#!/usr/bin/env python

import vtk


def main():
    fileName = get_program_parameters()

    importer = vtk.vtk3DSImporter()
    importer.SetFileName(fileName)
    importer.ComputeNormalsOn()

    colors = vtk.vtkNamedColors()

    renderer = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    iren = vtk.vtkRenderWindowInteractor()

    renWin.AddRenderer(renderer)
    renderer.SetBackground2(colors.GetColor3d("Gold"))
    renderer.SetBackground(colors.GetColor3d("Wheat"))
    renderer.GradientBackgroundOn()

    iren.SetRenderWindow(renWin)
    importer.SetRenderWindow(renWin)
    importer.Update()

    # actors = vtk.vtkActorCollection()
    actors = renderer.GetActors()
    print("There are", actors.GetNumberOfItems(), "actors")

    renWin.Render()
    camera = vtk.vtkCamera()
    camera.SetPosition(0, -1, 0)
    camera.SetFocalPoint(0, 0, 0)
    camera.SetViewUp(0, 0, 1)
    camera.Azimuth(150)
    camera.Elevation(30)

    renderer.SetActiveCamera(camera)
    renderer.ResetCamera()
    renderer.ResetCameraClippingRange()

    renWin.Render()
    iren.Start()


def get_program_parameters():
    import argparse
    description = 'Importing and exporting files in VTK.'
    epilogue = '''
        Importing and exporting files in VTK.

   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='iflamingo.3ds.')
    args = parser.parse_args()
    return args.filename


if __name__ == '__main__':
    main()
