#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    namedColors = vtk.vtkNamedColors()

    # Uncomment one of the following.
    # parametricObject = vtk.vtkParametricBoy()
    # parametricObject = vtk.vtkParametricConicSpiral()
    # parametricObject = vtk.vtkParametricCrossCap()
    # parametricObject = vtk.vtkParametricDini()
    # parametricObject = vtk.vtkParametricEllipsoid()
    # parametricObject = vtk.vtkParametricEnneper()
    # parametricObject = vtk.vtkParametricFigure8Klein()
    # parametricObject = vtk.vtkParametricKlein()
    # parametricObject = vtk.vtkParametricMobius()
    # parametricObject = vtk.vtkParametricRandomHills()
    # parametricObject = vtk.vtkParametricRoman()
    # parametricObject = vtk.vtkParametricSpline()
    # parametricObject = vtk.vtkParametricSuperEllipsoid()
    # parametricObject = vtk.vtkParametricSuperToroid()
    parametricObject = vtk.vtkParametricTorus()

    parametricFunctionSource = vtk.vtkParametricFunctionSource()
    parametricFunctionSource.SetParametricFunction(parametricObject)
    parametricFunctionSource.Update()

    # Visualize
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(parametricFunctionSource.GetOutputPort())

    # Create an actor for the contours
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetDiffuseColor(
        namedColors.GetColor3d("Burlywood"))
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("Parametric Objects")
    renderWindow.AddRenderer(renderer)
    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderWindow)

    renderer.AddActor(actor)
    renderer.SetBackground(namedColors.GetColor3d("Beige"))

    renderWindow.Render()
    interactor.Start()


if __name__ == '__main__':
    main()
