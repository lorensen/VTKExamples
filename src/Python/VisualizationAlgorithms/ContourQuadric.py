#!/usr/bin/env python

import vtk


def main():
    colors = vtk.vtkNamedColors()

    aren = vtk.vtkRenderer()

    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(aren)

    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    #
    # Create surfaces F(x,y,z) = constant
    #
    # Sample quadric function
    quadric = vtk.vtkQuadric()
    quadric.SetCoefficients(.5, 1, .2, 0, .1, 0, 0, .2, 0, 0)
    sample = vtk.vtkSampleFunction()
    sample.SetSampleDimensions(50, 50, 50)
    sample.SetImplicitFunction(quadric)

    contour = vtk.vtkContourFilter()
    contour.SetInputConnection(sample.GetOutputPort())
    contour.GenerateValues(5, 0, 1.2)

    contourMapper = vtk.vtkPolyDataMapper()
    contourMapper.SetInputConnection(contour.GetOutputPort())
    contourMapper.SetScalarRange(0, 1.2)

    contourActor = vtk.vtkActor()
    contourActor.SetMapper(contourMapper)

    # Create outline
    outline = vtk.vtkOutlineFilter()
    outline.SetInputConnection(sample.GetOutputPort())

    outlineMapper = vtk.vtkPolyDataMapper()
    outlineMapper.SetInputConnection(outline.GetOutputPort())

    outlineActor = vtk.vtkActor()
    outlineActor.SetMapper(outlineMapper)
    outlineActor.GetProperty().SetColor(colors.GetColor3d("Brown"))
    outlineActor.GetProperty().SetLineWidth(3.0)

    #
    # Rendering stuff
    #
    aren.SetBackground(colors.GetColor3d("SlateGray"))
    aren.AddActor(contourActor)
    aren.AddActor(outlineActor)

    aren.ResetCamera()
    aren.GetActiveCamera().Azimuth(30)
    aren.GetActiveCamera().Elevation(30)

    renWin.SetSize(640, 512)
    renWin.Render()

    # interact with data
    iren.Start()


if __name__ == '__main__':
    main()
