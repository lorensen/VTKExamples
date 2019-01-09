#!/usr/bin/env python

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Create a cube.
    cubeSource = vtk.vtkCubeSource()

    shrink = vtk.vtkShrinkFilter()
    shrink.SetInputConnection(cubeSource.GetOutputPort())
    shrink.SetShrinkFactor(.9)

    # Create a mapper and actor.

    mapper = vtk.vtkDataSetMapper()
    mapper.SetInputConnection(shrink.GetOutputPort())

    back = vtk.vtkProperty()
    back.SetColor(colors.GetColor3d("Tomato"))

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().EdgeVisibilityOn()
    actor.GetProperty().SetColor(colors.GetColor3d("Banana"))
    actor.SetBackfaceProperty(back)

    # Create a renderer, render window, and interactor.
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    # Add the actors to the scene
    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("Silver"))

    renderer.ResetCamera()
    renderer.GetActiveCamera().Azimuth(30)
    renderer.GetActiveCamera().Elevation(30)
    renderer.ResetCameraClippingRange()

    # Render and interact
    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == "__main__":
    main()
