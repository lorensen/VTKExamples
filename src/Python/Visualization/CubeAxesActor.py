#!/usr/bin/env python

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Create a superquadric
    superquadricSource = vtk.vtkSuperquadricSource()
    superquadricSource.SetPhiRoundness(3.1)
    superquadricSource.SetThetaRoundness(1.0)
    superquadricSource.Update()  # needed to GetBounds later

    renderer = vtk.vtkRenderer()

    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(superquadricSource.GetOutputPort())

    superquadricActor = vtk.vtkActor()
    superquadricActor.SetMapper(mapper)

    cubeAxesActor = vtk.vtkCubeAxesActor()
    cubeAxesActor.SetBounds(superquadricSource.GetOutput().GetBounds())
    cubeAxesActor.SetCamera(renderer.GetActiveCamera())
    cubeAxesActor.GetTitleTextProperty(0).SetColor(colors.GetColor3d('Red'))
    cubeAxesActor.GetLabelTextProperty(0).SetColor(colors.GetColor3d('Red'))

    cubeAxesActor.GetTitleTextProperty(1).SetColor(colors.GetColor3d('LimeGreen'))
    cubeAxesActor.GetLabelTextProperty(1).SetColor(colors.GetColor3d('LimeGreen'))

    cubeAxesActor.GetTitleTextProperty(2).SetColor(colors.GetColor3d('Blue'))
    cubeAxesActor.GetLabelTextProperty(2).SetColor(colors.GetColor3d('Blue'))

    cubeAxesActor.DrawXGridlinesOn()
    cubeAxesActor.DrawYGridlinesOn()
    cubeAxesActor.DrawZGridlinesOn()
    cubeAxesActor.SetGridLineLocation(cubeAxesActor.VTK_GRID_LINES_FURTHEST)

    cubeAxesActor.XAxisMinorTickVisibilityOff()
    cubeAxesActor.YAxisMinorTickVisibilityOff()
    cubeAxesActor.ZAxisMinorTickVisibilityOff()

    renderer.AddActor(cubeAxesActor)
    renderer.AddActor(superquadricActor)
    renderer.GetActiveCamera().Azimuth(30)
    renderer.GetActiveCamera().Elevation(30)

    renderer.ResetCamera()

    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)

    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
