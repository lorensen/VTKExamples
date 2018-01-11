#!/usr/bin/env python

import vtk


def main():
    fileName = get_program_parameters()

    colors = vtk.vtkNamedColors()
    
    # Create lines which serve as the "seed" geometry. The lines spell the
    # word "hello".
    #
    reader= vtk.vtkPolyDataReader()
    reader.SetFileName(fileName)

    lineMapper= vtk.vtkPolyDataMapper()
    lineMapper.SetInputConnection(reader.GetOutputPort())

    lineActor= vtk.vtkActor()
    lineActor.SetMapper(lineMapper)
    lineActor.GetProperty().SetColor(colors.GetColor3d("Tomato"))
    lineActor.GetProperty().SetLineWidth(3.0)

    # Create implicit model with vtkImplicitModeller. This computes a scalar
    # field which is the distance from the generating geometry. The contour
    # filter then extracts the geometry at the distance value 0.25 from the
    # generating geometry.
    #
    imp= vtk.vtkImplicitModeller()
    imp.SetInputConnection(reader.GetOutputPort())
    imp.SetSampleDimensions(110, 40, 20)
    imp.SetMaximumDistance(0.25)
    imp.SetModelBounds(-1.0, 10.0, -1.0, 3.0, -1.0, 1.0)

    contour= vtk.vtkContourFilter()
    contour.SetInputConnection(imp.GetOutputPort())
    contour.SetValue(0, 0.25)

    impMapper= vtk.vtkPolyDataMapper()
    impMapper.SetInputConnection(contour.GetOutputPort())
    impMapper.ScalarVisibilityOff()

    impActor= vtk.vtkActor()
    impActor.SetMapper(impMapper)
    impActor.GetProperty().SetColor(colors.GetColor3d("Peacock"))
    impActor.GetProperty().SetOpacity(0.5)

    # Create the usual graphics stuff.
    # Create the RenderWindow, Renderer and Interactor.
    #
    ren1= vtk.vtkRenderer()

    renWin= vtk.vtkRenderWindow()
    renWin.AddRenderer(ren1)

    iren= vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Add the actors to the renderer, set the background and size
    #
    ren1.AddActor(lineActor)
    ren1.AddActor(impActor)
    ren1.SetBackground(colors.GetColor3d("Wheat"))
    renWin.SetSize(640, 480)

    camera= vtk.vtkCamera()
    camera.SetFocalPoint(4.5, 1,  0)
    camera.SetPosition(4.5, 1.0, 6.73257)
    camera.SetViewUp(0,  1,  0)

    ren1.SetActiveCamera(camera)
    ren1.ResetCamera()
    camera.Dolly(1.3)
    camera.SetClippingRange(1.81325, 90.6627)

    renWin.Render()
    iren.Start()


def get_program_parameters():
    import argparse
    description = 'Implicit modelling is used to thicken a stroked font.'
    epilogue = '''
    Implicit modelling is used to thicken a stroked font.
     The original lines can be seen within the translucent implicit surface. 
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='hello.vtk.')
    args = parser.parse_args()
    return args.filename


if __name__ == '__main__':
    main()
