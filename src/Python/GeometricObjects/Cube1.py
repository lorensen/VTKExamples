#!/usr/bin/env python

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Create a rendering window and renderer.
    ren = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.SetWindowName("Cube1")
    renWin.AddRenderer(ren)

    # Create a renderwindowinteractor.
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Create cube.
    cube = vtk.vtkCubeSource()
    cube.Update()

    # mapper
    cubeMapper = vtk.vtkPolyDataMapper()
    cubeMapper.SetInputData(cube.GetOutput())

    # Actor.
    cubeActor = vtk.vtkActor()
    cubeActor.SetMapper(cubeMapper)
    cubeActor.GetProperty().SetColor(colors.GetColor3d("Cornsilk"))

    # Assign actor to the renderer.
    ren.AddActor(cubeActor)

    ren.ResetCamera()
    ren.GetActiveCamera().Azimuth(30)
    ren.GetActiveCamera().Elevation(30)
    ren.ResetCameraClippingRange()
    ren.SetBackground(colors.GetColor3d("DarkGreen"))

    # Enable user interface interactor.
    iren.Initialize()
    renWin.Render()
    iren.Start()


if __name__ == "__main__":
    main()
