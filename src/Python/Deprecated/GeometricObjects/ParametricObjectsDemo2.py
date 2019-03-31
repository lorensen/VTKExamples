#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    colors = vtk.vtkNamedColors()

    colors.SetColor("BkgColor", [26, 51, 102, 255])

    parametricObjects = list()
    parametricObjects.append(vtk.vtkParametricBohemianDome())
    parametricObjects[-1].SetA(5.0)
    parametricObjects[-1].SetB(1.0)
    parametricObjects[-1].SetC(2.0)
    parametricObjects.append(vtk.vtkParametricBour())
    parametricObjects.append(vtk.vtkParametricCatalanMinimal())
    parametricObjects.append(vtk.vtkParametricHenneberg())
    parametricObjects.append(vtk.vtkParametricKuen())
    parametricObjects.append(vtk.vtkParametricPluckerConoid())
    parametricObjects.append(vtk.vtkParametricPseudosphere())

    parametricFunctionSources = list()
    renderers = list()
    mappers = list()
    actors = list()
    textmappers = list()
    textactors = list()

    # Create one text property for all
    textProperty = vtk.vtkTextProperty()
    textProperty.SetFontSize(12)
    textProperty.SetJustificationToCentered()

    backProperty = vtk.vtkProperty()
    backProperty.SetColor(colors.GetColor3d("Tomato"))

    # Create a parametric function source, renderer, mapper, and actor
    # for each object
    for i in range(0, len(parametricObjects)):
        parametricFunctionSources.append(
            vtk.vtkParametricFunctionSource())
        parametricFunctionSources[i].SetParametricFunction(parametricObjects[i])
        parametricFunctionSources[i].Update()

        mappers.append(vtk.vtkPolyDataMapper())
        mappers[i].SetInputConnection(
            parametricFunctionSources[i].GetOutputPort())

        actors.append(vtk.vtkActor())
        actors[i].SetMapper(mappers[i])
        actors[i].GetProperty().SetColor(colors.GetColor3d("Banana"))
        actors[i].GetProperty().SetSpecular(.5)
        actors[i].GetProperty().SetSpecularPower(20)
        actors[i].SetBackfaceProperty(backProperty)

        textmappers.append(vtk.vtkTextMapper())
        textmappers[i].SetInput(parametricObjects[i].GetClassName())
        textmappers[i].SetTextProperty(textProperty)

        textactors.append(vtk.vtkActor2D())
        textactors[i].SetMapper(textmappers[i])
        textactors[i].SetPosition(100, 16)

        renderers.append(vtk.vtkRenderer())
        renderers[i].AddActor(actors[i])
        renderers[i].AddActor(textactors[i])
        renderers[i].SetBackground(colors.GetColor3d("BkgColor"))

    # Setup the viewports
    xGridDimensions = 4
    yGridDimensions = 2
    rendererSize = 200
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("Parametric Objects Demonstration2")
    renderWindow.SetSize(rendererSize * xGridDimensions,
                         rendererSize * yGridDimensions)
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
                ren.SetBackground(colors.GetColor3d("BkgColor"))
                ren.SetViewport(viewport)
                renderWindow.AddRenderer(ren)
                continue

            renderers[index].SetViewport(viewport)
            renderers[index].ResetCamera()
            renderers[index].GetActiveCamera().Azimuth(30)
            renderers[index].GetActiveCamera().Elevation(-30)
            renderers[index].GetActiveCamera().Zoom(0.9)
            renderers[index].ResetCameraClippingRange()
            renderWindow.AddRenderer(renderers[index])

    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderWindow)

    renderWindow.Render()
    interactor.Start()


if __name__ == '__main__':
    main()
