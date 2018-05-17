#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    colors = vtk.vtkNamedColors()

    camera = vtk.vtkCamera()
    camera.SetClippingRange(0.1, 0.4)
    planesArray = [0] * 24

    camera.GetFrustumPlanes(1.0, planesArray)

    planes = vtk.vtkPlanes()
    planes.SetFrustumPlanes(planesArray)

    frustumSource = vtk.vtkFrustumSource()
    frustumSource.ShowLinesOff()
    frustumSource.SetPlanes(planes)

    shrink = vtk.vtkShrinkPolyData()
    shrink.SetInputConnection(frustumSource.GetOutputPort())
    shrink.SetShrinkFactor(.9)

    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(shrink.GetOutputPort())

    back = vtk.vtkProperty()
    back.SetColor(colors.GetColor3d("Tomato"))

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().EdgeVisibilityOn()
    actor.GetProperty().SetColor(colors.GetColor3d("Banana"))
    actor.SetBackfaceProperty(back)

    # a renderer and render window
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("Frustum")
    renderWindow.AddRenderer(renderer)

    # an interactor
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    # add the actors to the scene
    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("Silver"))

    # Position the camera so that we can see the frustum
    renderer.GetActiveCamera().SetPosition(1, 0, 0)
    renderer.GetActiveCamera().SetFocalPoint(0, 0, 0)
    renderer.GetActiveCamera().SetViewUp(0, 1, 0)
    renderer.GetActiveCamera().Azimuth(30)
    renderer.GetActiveCamera().Elevation(30)
    renderer.ResetCamera()

    # render an image (lights and cameras are created automatically)
    renderWindow.Render()

    # begin mouse interaction
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
