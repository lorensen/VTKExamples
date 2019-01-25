# !/usr/bin/env python

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Set the background color.
    colors.SetColor("bkg", [26, 51, 102, 255])

    # The following lines create a sphere represented by polygons.
    #
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
    numberOfSpheres = 8
    spheres = list()
    ambient = 0.3
    diffuse = 0.5
    specular = 1.0
    spBase = 5.0
    spScale = 1.0
    position = [0, 0, 0]
    for i in range(0, numberOfSpheres):
        specularPower = spBase * spScale
        spheres.append(vtk.vtkActor())
        spheres[i].SetMapper(sphereMapper)
        spheres[i].GetProperty().SetColor(colors.GetColor3d("Red"))
        spheres[i].GetProperty().SetAmbient(ambient)
        spheres[i].GetProperty().SetDiffuse(diffuse)
        spheres[i].GetProperty().SetSpecular(specular)
        spheres[i].GetProperty().SetSpecularPower(specularPower)
        spheres[i].GetProperty().SetSpecularColor(colors.GetColor3d("White"))
        spheres[i].AddPosition(position)
        spScale = spScale * 2.0
        position[0] += 1.25
        if i == 3:
            specular = 0.5
            spScale = 1.0
            position[0] = 0
            position[1] = 1.25

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
    for i in range(0, numberOfSpheres):
        ren.AddActor(spheres[i])

    ren.SetBackground(colors.GetColor3d("bkg"))
    renWin.SetSize(640, 480)
    renWin.SetWindowName("Specular Spheres")

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
    ren.GetActiveCamera().SetParallelScale(2.0)
    # This starts the event loop and invokes an initial render.
    #
    iren.Initialize()
    renWin.Render()
    iren.Start()


if __name__ == "__main__":
    main()
