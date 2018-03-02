#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Set the background color.
    colors.SetColor("BkgColor", [26, 51, 102, 255])

    # The following lines create a sphere represented by polygons.
    sphere = vtk.vtkSphereSource()
    sphere.SetThetaResolution(100)
    sphere.SetPhiResolution(50)

    # The mapper is responsible for pushing the geometry into the graphics
    # library. It may also do color mapping, if scalars or other attributes
    # are defined.
    #
    sphereMapper = vtk.vtkPolyDataMapper()
    sphereMapper.SetInputConnection(sphere.GetOutputPort())

    # The actor is a grouping mechanism: besides the geometry (mapper), it
    # also has a property, transformation matrix, and/or texture map.
    # In this example we create eight different spheres (two rows of four
    # spheres) and set the specular lighting coefficients. A little ambient
    # is turned on so the sphere is not completely black on the back side.
    #
    sphere1 = vtk.vtkActor()
    sphere1.SetMapper(sphereMapper)
    sphere1.GetProperty().SetColor(colors.GetColor3d("Red"))
    sphere1.GetProperty().SetAmbient(0.3)
    sphere1.GetProperty().SetDiffuse(0.0)
    sphere1.GetProperty().SetSpecular(1.0)
    sphere1.GetProperty().SetSpecularPower(5.0)

    sphere2 = vtk.vtkActor()
    sphere2.SetMapper(sphereMapper)
    sphere2.GetProperty().SetColor(colors.GetColor3d("Red"))
    sphere2.GetProperty().SetAmbient(0.3)
    sphere2.GetProperty().SetDiffuse(0.0)
    sphere2.GetProperty().SetSpecular(1.0)
    sphere2.GetProperty().SetSpecularPower(10.0)
    sphere2.AddPosition(1.25, 0, 0)

    sphere3 = vtk.vtkActor()
    sphere3.SetMapper(sphereMapper)
    sphere3.GetProperty().SetColor(colors.GetColor3d("Red"))
    sphere3.GetProperty().SetAmbient(0.3)
    sphere3.GetProperty().SetDiffuse(0.0)
    sphere3.GetProperty().SetSpecular(1.0)
    sphere3.GetProperty().SetSpecularPower(20.0)
    sphere3.AddPosition(2.5, 0, 0)

    sphere4 = vtk.vtkActor()
    sphere4.SetMapper(sphereMapper)
    sphere4.GetProperty().SetColor(colors.GetColor3d("Red"))
    sphere4.GetProperty().SetAmbient(0.3)
    sphere4.GetProperty().SetDiffuse(0.0)
    sphere4.GetProperty().SetSpecular(1.0)
    sphere4.GetProperty().SetSpecularPower(40.0)
    sphere4.AddPosition(3.75, 0, 0)

    sphere5 = vtk.vtkActor()
    sphere5.SetMapper(sphereMapper)
    sphere5.GetProperty().SetColor(colors.GetColor3d("Red"))
    sphere5.GetProperty().SetAmbient(0.3)
    sphere5.GetProperty().SetDiffuse(0.0)
    sphere5.GetProperty().SetSpecular(0.5)
    sphere5.GetProperty().SetSpecularPower(5.0)
    sphere5.AddPosition(0.0, 1.25, 0)

    sphere6 = vtk.vtkActor()
    sphere6.SetMapper(sphereMapper)
    sphere6.GetProperty().SetColor(colors.GetColor3d("Red"))
    sphere6.GetProperty().SetAmbient(0.3)
    sphere6.GetProperty().SetDiffuse(0.0)
    sphere6.GetProperty().SetSpecular(0.5)
    sphere6.GetProperty().SetSpecularPower(10.0)
    sphere6.AddPosition(1.25, 1.25, 0)

    sphere7 = vtk.vtkActor()
    sphere7.SetMapper(sphereMapper)
    sphere7.GetProperty().SetColor(colors.GetColor3d("Red"))
    sphere7.GetProperty().SetAmbient(0.3)
    sphere7.GetProperty().SetDiffuse(0.0)
    sphere7.GetProperty().SetSpecular(0.5)
    sphere7.GetProperty().SetSpecularPower(20.0)
    sphere7.AddPosition(2.5, 1.25, 0)

    sphere8 = vtk.vtkActor()
    sphere8.SetMapper(sphereMapper)
    sphere8.GetProperty().SetColor(colors.GetColor3d("Red"))
    sphere8.GetProperty().SetAmbient(0.3)
    sphere8.GetProperty().SetDiffuse(0.0)
    sphere8.GetProperty().SetSpecular(0.5)
    sphere8.GetProperty().SetSpecularPower(40.0)
    sphere8.AddPosition(3.75, 1.25, 0)

    # Create the graphics structure. The renderer renders into the
    # render window. The render window interactor captures mouse events
    # and will perform appropriate camera or actor manipulation
    # depending on the nature of the events.
    #
    ren = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Add the actors to the renderer, set the background and size.
    #
    ren.AddActor(sphere1)
    ren.AddActor(sphere2)
    ren.AddActor(sphere3)
    ren.AddActor(sphere4)
    ren.AddActor(sphere5)
    ren.AddActor(sphere6)
    ren.AddActor(sphere7)
    ren.AddActor(sphere8)
    ren.SetBackground(colors.GetColor3d("BkgColor"))
    renWin.SetSize(640, 480)

    # Set up the lighting.
    #
    light = vtk.vtkLight()
    light.SetFocalPoint(1.875, 0.6125, 0)
    light.SetPosition(0.875, 1.6125, 1)
    ren.AddLight(light)

    # We want to eliminate perspective effects on the apparent lighting.
    # Parallel camera projection will be used. To zoom in parallel projection
    # mode, the ParallelScale is set.
    #
    ren.GetActiveCamera().SetFocalPoint(0, 0, 0)
    ren.GetActiveCamera().SetPosition(0, 0, 1)
    ren.GetActiveCamera().SetViewUp(0, 1, 0)
    ren.GetActiveCamera().ParallelProjectionOn()
    ren.ResetCamera()
    ren.GetActiveCamera().SetParallelScale(1.5)

    # This starts the event loop and invokes an initial render.
    #
    iren.Initialize()
    iren.Start()


if __name__ == "__main__":
    main()
