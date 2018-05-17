#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Set the colors.
    colors.SetColor("CubeColor", [250, 128, 114, 255])
    colors.SetColor("BkgColor", [230, 230, 230, 255])

    # Create the rendering windows and three renderers.

    ren1 = vtk.vtkRenderer()
    ren2 = vtk.vtkRenderer()
    renWindow1 = vtk.vtkRenderWindow()
    renWindow1.AddRenderer(ren1)
    renWindow1.AddRenderer(ren2)
    iren1 = vtk.vtkRenderWindowInteractor()
    iren1.SetRenderWindow(renWindow1)
    ren3 = vtk.vtkRenderer()
    renWindow2 = vtk.vtkRenderWindow()
    renWindow2.AddRenderer(ren3)
    iren2 = vtk.vtkRenderWindowInteractor()
    iren2.SetRenderWindow(renWindow2)

    # Create an actor and give it cone geometry.
    cone = vtk.vtkConeSource()
    cone.SetResolution(8)

    coneMapper = vtk.vtkPolyDataMapper()
    coneMapper.SetInputConnection(cone.GetOutputPort())

    coneActor = vtk.vtkActor()
    coneActor.SetMapper(coneMapper)
    coneActor.GetProperty().SetColor(colors.GetColor3d("Peacock"))

    # Create an actor and give it cube geometry.
    cube = vtk.vtkCubeSource()

    cubeMapper = vtk.vtkPolyDataMapper()
    cubeMapper.SetInputConnection(cube.GetOutputPort())

    cubeActor = vtk.vtkActor()
    cubeActor.SetMapper(cubeMapper)
    cubeActor.GetProperty().SetColor(colors.GetColor3d("CubeColor"))

    # Create an actor and give it sphere geometry.
    sphere = vtk.vtkSphereSource()
    sphere.SetThetaResolution(16)
    sphere.SetPhiResolution(16)

    sphereMapper = vtk.vtkPolyDataMapper()
    sphereMapper.SetInputConnection(sphere.GetOutputPort())

    sphereActor = vtk.vtkActor()
    sphereActor.SetMapper(sphereMapper)
    sphereActor.GetProperty().SetColor(colors.GetColor3d("Melon"))

    # Assign our actors to both renderers.
    ren1.AddActor(coneActor)
    ren2.AddActor(sphereActor)
    ren3.AddActor(cubeActor)

    # set the size of our window
    renWindow1.SetSize(300, 150)
    renWindow1.SetPosition(0, 50)
    renWindow2.SetSize(300, 300)
    renWindow2.SetPosition(0, 300)

    # Set the viewports and backgrounds of the renderers.
    ren1.SetViewport(0, 0, 0.5, 1)
    ren1.SetBackground(colors.GetColor3d("BkgColor"))
    ren2.SetViewport(0.5, 0, 1, 1)
    ren2.SetBackground(colors.GetColor3d("White"))
    ren3.SetBackground(colors.GetColor3d("White"))

    # Draw the resulting scene.
    renWindow1.Render()
    renWindow2.Render()

    iren1.Start()


if __name__ == "__main__":
    main()
