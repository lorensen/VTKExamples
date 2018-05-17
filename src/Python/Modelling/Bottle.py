#!/usr/bin/env python

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Create the RenderWindow, Renderer and Interactor.
    #
    renderer = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(renderer)

    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Create the bottle profile.
    #
    points = vtk.vtkPoints()
    points.InsertPoint(0, 0.01, 0.0, 0.0)
    points.InsertPoint(1, 1.5, 0.0, 0.0)
    points.InsertPoint(2, 1.5, 0.0, 3.5)
    points.InsertPoint(3, 1.25, 0.0, 3.75)
    points.InsertPoint(4, 0.75, 0.0, 4.00)
    points.InsertPoint(5, 0.6, 0.0, 4.35)
    points.InsertPoint(6, 0.7, 0.0, 4.65)
    points.InsertPoint(7, 1.0, 0.0, 4.75)
    points.InsertPoint(8, 1.0, 0.0, 5.0)
    points.InsertPoint(9, 0.2, 0.0, 5.0)

    lines = vtk.vtkCellArray()
    lines.InsertNextCell(10)  # The number of points.
    lines.InsertCellPoint(0)
    lines.InsertCellPoint(1)
    lines.InsertCellPoint(2)
    lines.InsertCellPoint(3)
    lines.InsertCellPoint(4)
    lines.InsertCellPoint(5)
    lines.InsertCellPoint(6)
    lines.InsertCellPoint(7)
    lines.InsertCellPoint(8)
    lines.InsertCellPoint(9)

    profile = vtk.vtkPolyData()
    profile.SetPoints(points)
    profile.SetLines(lines)

    # Extrude the profile to make the bottle.
    #
    extrude = vtk.vtkRotationalExtrusionFilter()
    extrude.SetInputData(profile)
    extrude.SetResolution(60)

    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(extrude.GetOutputPort())

    bottle = vtk.vtkActor()
    bottle.SetMapper(mapper)
    bottle.GetProperty().SetColor(colors.GetColor3d("Mint"))

    # Sisplay the profile.
    stripper = vtk.vtkStripper()
    stripper.SetInputData(profile)

    tubes = vtk.vtkTubeFilter()
    tubes.SetInputConnection(stripper.GetOutputPort())
    tubes.SetNumberOfSides(11)
    tubes.SetRadius(.05)

    profileMapper = vtk.vtkPolyDataMapper()
    profileMapper.SetInputConnection(tubes.GetOutputPort())

    profileActor = vtk.vtkActor()
    profileActor.SetMapper(profileMapper)
    profileActor.GetProperty().SetColor(colors.GetColor3d("Tomato"))

    # Add the actors to the renderer, set the background and size.
    #
    renderer.AddActor(bottle)
    renderer.AddActor(profileActor)
    renderer.SetBackground(colors.GetColor3d("Burlywood"))

    renWin.SetSize(640, 480)
    renWin.Render()

    renderer.GetActiveCamera().SetPosition(1, 0, 0)
    renderer.GetActiveCamera().SetFocalPoint(0, 0, 0)
    renderer.GetActiveCamera().SetViewUp(0, 0, 1)
    renderer.ResetCamera()
    renderer.GetActiveCamera().Azimuth(30)
    renderer.GetActiveCamera().Elevation(30)

    # Render the image.
    #
    renWin.Render()
    iren.Start()


if __name__ == '__main__':
    main()
