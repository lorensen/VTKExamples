#!/usr/bin/env python

import vtk


def main():
    colors = vtk.vtkNamedColors()

    renderer = vtk.vtkRenderer()
    renderer.GetCullers().RemoveAllItems()

    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(renderer)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    sphere = vtk.vtkSphereSource()
    sphere.SetThetaResolution(12)
    sphere.SetPhiResolution(12)

    shrink = vtk.vtkShrinkFilter()
    shrink.SetInputConnection(sphere.GetOutputPort())
    shrink.SetShrinkFactor(0.9)

    colorIt = vtk.vtkElevationFilter()
    colorIt.SetInputConnection(shrink.GetOutputPort())
    colorIt.SetLowPoint(0, 0, -.5)
    colorIt.SetHighPoint(0, 0, .5)

    mapper = vtk.vtkDataSetMapper()
    mapper.SetInputConnection(colorIt.GetOutputPort())

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)

    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("White"))
    renWin.SetSize(640, 480)

    renWin.Render()

    #  Interact with the data.
    iren.Start()


if __name__ == '__main__':
    main()
