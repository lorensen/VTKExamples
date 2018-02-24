#!/usr/bin/env python

import vtk


# arrow.py adapted from the C++ vtk examples and translated to python.

def main():
    colors = vtk.vtkNamedColors()

    arrowSource = vtk.vtkArrowSource()
    # arrowSource.SetShaftRadius(0.01)
    # arrowSource.SetTipLength(.9)

    # Create a mapper and actor
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(arrowSource.GetOutputPort())
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)

    # Visualize
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("Arrow")
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("MidnightBlue"))

    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == "__main__":
    main()
