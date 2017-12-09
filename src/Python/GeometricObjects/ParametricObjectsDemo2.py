#!/usr/bin/env python

import vtk


class ParametricObjects(object):
    def ParametricObjects(self):

        colors = vtk.vtkNamedColors()
        # Set the background color.
        bkg = map(lambda x: x / 256.0, [25, 51, 102])
        colors.SetColor("BkgColor", *bkg)

        parametricObjects = list()
        parametricObjects.append(vtk.vtkParametricBohemianDome())
        parametricObjects[-1].SetA(0.5)
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

        # Create a common text property.
        textProperty = vtk.vtkTextProperty()
        textProperty.SetFontSize(10)
        textProperty.SetJustificationToCentered()

        colors = vtk.vtkNamedColors()
        # Set the background color. Match those in VTKTextbook.pdf.
        bkg = map(lambda x: x / 256.0, [25, 51, 102])
        colors.SetColor("BkgColor", *bkg)

        backProperty = vtk.vtkProperty()
        backProperty.SetColor(colors.GetColor3d("Red"))

        # Create a parametric function source, renderer, mapper
        # and actor for each object.
        for idx, item in enumerate(parametricObjects):
            parametricFunctionSources.append(vtk.vtkParametricFunctionSource())
            parametricFunctionSources[idx].SetParametricFunction(item)
            parametricFunctionSources[idx].Update()

            mappers.append(vtk.vtkPolyDataMapper())
            mappers[idx].SetInputConnection(parametricFunctionSources[idx].GetOutputPort())

            actors.append(vtk.vtkActor())
            actors[idx].SetMapper(mappers[idx])
            actors[idx].GetProperty().SetColor(colors.GetColor3d("White"))
            actors[idx].SetBackfaceProperty(backProperty)

            textmappers.append(vtk.vtkTextMapper())
            textmappers[idx].SetInput(item.GetClassName())
            textmappers[idx].SetTextProperty(textProperty)

            textactors.append(vtk.vtkActor2D())
            textactors[idx].SetMapper(textmappers[idx])
            textactors[idx].SetPosition(100, 16)

            renderers.append(vtk.vtkRenderer())

        gridDimensionsX = 4
        gridDimensionsY = 2
        for idx in range(len(parametricObjects), gridDimensionsX * gridDimensionsY):
            renderers.append(vtk.vtkRenderer)

        rendererSize = 200

        # Create the RenderWindow
        renderWindow = vtk.vtkRenderWindow()
        renderWindow.SetSize(rendererSize * gridDimensionsX, rendererSize * gridDimensionsY)

        # Add and position the renders to the render window.
        viewport = list()
        for row in range(gridDimensionsY):
            for col in range(gridDimensionsX):
                idx = row * gridDimensionsX + col
                x0 = float(col) / gridDimensionsX
                y0 = float(gridDimensionsY - row - 1) / gridDimensionsY
                x1 = float(col + 1) / gridDimensionsX
                y1 = float(gridDimensionsY - row) / gridDimensionsY
                viewport[:] = []
                viewport.append(x0)
                viewport.append(y0)
                viewport.append(x1)
                viewport.append(y1)

                if idx > (len(parametricObjects) - 1):
                    continue

                renderWindow.AddRenderer(renderers[idx])
                renderers[idx].SetViewport(viewport)

                renderers[idx].AddActor(actors[idx])
                renderers[idx].AddActor(textactors[idx])
                renderers[idx].SetBackground(colors.GetColor3d("BkgColor"))
                renderers[idx].ResetCamera()
                renderers[idx].GetActiveCamera().Azimuth(30)
                renderers[idx].GetActiveCamera().Elevation(-30)
                renderers[idx].GetActiveCamera().Zoom(0.9)
                renderers[idx].ResetCameraClippingRange()

        interactor = vtk.vtkRenderWindowInteractor()
        interactor.SetRenderWindow(renderWindow)

        renderWindow.Render()

        interactor.Start()


if __name__ == "__main__":
    po = ParametricObjects()
    po.ParametricObjects()
