#!/usr/bin/env python

import vtk


def main():
    colors = vtk.vtkNamedColors()
    renderer = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(renderer)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    sphere = vtk.vtkSphereSource()
    sphere.SetPhiResolution(12)
    sphere.SetThetaResolution(12)

    colorIt = vtk.vtkElevationFilter()
    colorIt.SetInputConnection(sphere.GetOutputPort())
    colorIt.SetLowPoint(0, 0, -1)
    colorIt.SetHighPoint(0, 0, 1)

    mapper = vtk.vtkDataSetMapper()
    mapper.SetInputConnection(colorIt.GetOutputPort())

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)

    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("SlateGray"))
    renWin.SetSize(640, 480)

    renWin.Render()

    # Interact with the data.
    iren.Start()


if __name__ == '__main__':
    main()
