#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    colors = vtk.vtkNamedColors()

    planes = list()
    titles = list()

    # Using frustum planes.
    titles.append('Using frustum planes')
    camera = vtk.vtkCamera()
    planesArray = [0] * 24
    camera.GetFrustumPlanes(1, planesArray)
    planes.append(vtk.vtkPlanes())
    planes[0].SetFrustumPlanes(planesArray)

    # Using bounds.
    titles.append('Using bounds')
    sphereSource = vtk.vtkSphereSource()
    sphereSource.Update()
    bounds = [0] * 6
    sphereSource.GetOutput().GetBounds(bounds)
    planes.append(vtk.vtkPlanes())
    planes[1].SetBounds(bounds)

    # At this point we have the planes created by both of the methods above.
    # You can do whatever you want with them.

    # For visualisation we will produce an n-sided convex hull
    # and visualise it.

    # Create a common text property.
    textProperty = vtk.vtkTextProperty()
    textProperty.SetFontSize(16)
    textProperty.SetJustificationToCentered()

    renWin = vtk.vtkRenderWindow()
    renWin.SetSize(600, 600)
    renWin.SetWindowName("Planes")

    iRen = vtk.vtkRenderWindowInteractor()
    iRen.SetRenderWindow(renWin)

    hulls = list()
    pds = list()
    mappers = list()
    actors = list()
    renderers = list()
    textMappers = list()
    textActors = list()
    for i in range(0, len(planes)):
        hulls.append(vtk.vtkHull())
        hulls[i].SetPlanes(planes[i])

        pds.append(vtk.vtkPolyData())

        # To generate the convex hull we supply a vtkPolyData object and a bounding box.
        # We define the bounding box to be where we expect the resulting polyhedron to lie.
        # Make it a generous fit as it is only used to create the initial
        # polygons that are eventually clipped.
        hulls[i].GenerateHull(pds[i], -200, 200, -200, 200, -200, 200)

        mappers.append(vtk.vtkPolyDataMapper())
        mappers[i].SetInputData(pds[i])

        actors.append(vtk.vtkActor())
        actors[i].SetMapper(mappers[i])
        actors[i].GetProperty().SetColor(colors.GetColor3d("Moccasin"))
        actors[i].GetProperty().SetSpecular(0.8)
        actors[i].GetProperty().SetSpecularPower(30)

        renderers.append(vtk.vtkRenderer())
        renderers[i].AddActor(actors[i])

        textMappers.append(vtk.vtkTextMapper())
        textMappers[i].SetInput(titles[i])
        textMappers[i].SetTextProperty(textProperty)

        textActors.append(vtk.vtkActor2D())
        textActors[i].SetMapper(textMappers[i])
        textActors[i].SetPosition(100, 10)
        renderers[i].AddViewProp(textActors[i])

        renWin.AddRenderer(renderers[i])

    # Setup the viewports
    xGridDimensions = 2
    yGridDimensions = 1
    rendererSize = 300
    renWin.SetSize(rendererSize * xGridDimensions, rendererSize * yGridDimensions)
    for row in range(0, yGridDimensions):
        for col in range(0, xGridDimensions):
            index = row * xGridDimensions + col

            # (xmin, ymin, xmax, ymax)
            viewport = [float(col) / xGridDimensions,
                        float(yGridDimensions - (row + 1)) / yGridDimensions,
                        float(col + 1) / xGridDimensions,
                        float(yGridDimensions - row) / yGridDimensions]

            if index > (len(actors) - 1):
                # Add a renderer even if there is no actor.
                # This makes the render window background all the same color.
                ren = vtk.vtkRenderer()
                ren.SetBackground(colors.GetColor3d("DarkSlateGray"))
                ren.SetViewport(viewport)
                renWin.AddRenderer(ren)
                continue

            renderers[index].SetViewport(viewport)
            renderers[index].SetBackground(colors.GetColor3d("DarkSlateGray"))
            renderers[index].ResetCamera()
            renderers[index].GetActiveCamera().Azimuth(30)
            renderers[index].GetActiveCamera().Elevation(-30)
            renderers[index].ResetCameraClippingRange()

    iRen.Initialize()
    renWin.Render()
    iRen.Start()


if __name__ == '__main__':
    main()
