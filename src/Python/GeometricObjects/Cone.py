#!/usr/bin/env python

import vtk


def main():
    colors = vtk.vtkNamedColors()
    colors.SetColor("BkgColor1", [26, 51, 77, 255])
    colors.SetColor("BkgColor2", [77, 51, 26, 255])

    coneSource = vtk.vtkConeSource()
    # coneSource.SetResolution(60)
    # coneSource.SetCenter(-2,0,0)

    # Create a mapper and actor
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(coneSource.GetOutputPort())
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)

    # Visualize
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("BkgColor1"))  # Background color dark blue
    renderer.SetBackground(colors.GetColor3d("BkgColor2"))  # Background color dark red
    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == "__main__":
    main()
