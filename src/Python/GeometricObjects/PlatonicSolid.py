#!/usr/bin/env python

import vtk


class PlatonicSolids():

    def PlatonicSolids(self):
        colors = vtk.vtkNamedColors()

        # Each face has a different cell scalar
        # So create a lookup table with a different colour
        # for each face.
        lut = vtk.vtkLookupTable()
        lut.SetNumberOfTableValues(20)
        lut.SetTableRange(0.0, 19.0)
        lut.Build()
        lut.SetTableValue(0, 0, 0, 0)
        lut.SetTableValue(1, 0, 0, 1)
        lut.SetTableValue(2, 0, 1, 0)
        lut.SetTableValue(3, 0, 1, 1)
        lut.SetTableValue(4, 1, 0, 0)
        lut.SetTableValue(5, 1, 0, 1)
        lut.SetTableValue(6, 1, 1, 0)
        lut.SetTableValue(7, 1, 1, 1)
        lut.SetTableValue(8, 0.7, 0.7, 0.7)
        lut.SetTableValue(9, 0, 0, 0.7)
        lut.SetTableValue(10, 0, 0.7, 0)
        lut.SetTableValue(11, 0, 0.7, 0.7)
        lut.SetTableValue(12, 0.7, 0, 0)
        lut.SetTableValue(13, 0.7, 0, 0.7)
        lut.SetTableValue(14, 0.7, 0.7, 0)
        lut.SetTableValue(15, 0, 0, 0.4)
        lut.SetTableValue(16, 0, 0.4, 0)
        lut.SetTableValue(17, 0, 0.4, 0.4)
        lut.SetTableValue(18, 0.4, 0, 0)
        lut.SetTableValue(19, 0.4, 0, 0.4)

        PlatonicSolids = list()
        # There are five Platonic solids.
        for i in range(0, 5):
            PlatonicSolids.append(vtk.vtkPlatonicSolidSource())
        # Specify the Platonic Solid to create.
        for idx, item in enumerate(PlatonicSolids):
            PlatonicSolids[idx].SetSolidType(idx)
            names = ["Tetrahedron", "Cube", "Octahedron", "Icosahedron", "Dodecahedron"]

        renderers = list()
        mappers = list()
        actors = list()
        textmappers = list()
        textactors = list()

        # Create a common text property.
        textProperty = vtk.vtkTextProperty()
        textProperty.SetFontSize(10)
        textProperty.SetJustificationToCentered()

        # Create the RenderWindow
        #
        renWin = vtk.vtkRenderWindow()
        renWin.SetWindowName("Platonic Solids")

        iRen = vtk.vtkRenderWindowInteractor()
        iRen.SetRenderWindow(renWin)

        # Create a parametric function source, renderer, mapper
        # and actor for each object.
        for idx, item in enumerate(PlatonicSolids):
            PlatonicSolids[idx].Update()

            mappers.append(vtk.vtkPolyDataMapper())
            mappers[idx].SetInputConnection(PlatonicSolids[idx].GetOutputPort())
            mappers[idx].SetLookupTable(lut)
            mappers[idx].SetScalarRange(0, 20)

            actors.append(vtk.vtkActor())
            actors[idx].SetMapper(mappers[idx])

            textmappers.append(vtk.vtkTextMapper())
            textmappers[idx].SetInput(names[idx])
            textmappers[idx].SetTextProperty(textProperty)

            textactors.append(vtk.vtkActor2D())
            textactors[idx].SetMapper(textmappers[idx])
            textactors[idx].SetPosition(120, 16)

            renderers.append(vtk.vtkRenderer())
            renderers[idx].AddActor(actors[idx])
            renderers[idx].AddViewProp(textactors[idx])

            renWin.AddRenderer(renderers[idx])

        rowDimensions = 3
        colDimensions = 2

        for idx in range(rowDimensions * colDimensions):
            if idx >= len(PlatonicSolids):
                renderers.append(vtk.vtkRenderer)

        # Setup the viewports
        xGridDimensions = 3
        yGridDimensions = 2
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
                    ren.SetBackground(colors.GetColor3d("SaddleBrown"))
                    ren.SetViewport(viewport)
                    renWin.AddRenderer(ren)
                    continue

                renderers[index].SetViewport(viewport)
                renderers[index].SetBackground(colors.GetColor3d("SaddleBrown"))
                renderers[index].ResetCamera()
                # renderers[index].GetActiveCamera().Azimuth(30)
                # renderers[index].GetActiveCamera().Elevation(-30)
                renderers[index].ResetCameraClippingRange()

        iRen.Initialize()
        renWin.Render()
        iRen.Start()

        # # Add and position the renders to the render window.
        # viewport = list()
        # idx = -1
        # for row in range(rowDimensions):
        #     for col in range(colDimensions):
        #         idx += 1
        #         viewport[:] = []
        #         viewport.append(float(col) * rendererSize / (colDimensions * rendererSize))
        #         viewport.append(float(rowDimensions - (row + 1)) * rendererSize / (rowDimensions * rendererSize))
        #         viewport.append(float(col + 1) * rendererSize / (colDimensions * rendererSize))
        #         viewport.append(float(rowDimensions - row) * rendererSize / (rowDimensions * rendererSize))
        #
        #         if idx > (len(PlatonicSolids) - 1):
        #             continue
        #
        #         renderers[idx].SetViewport(viewport)
        #         renderWindow.AddRenderer(renderers[idx])
        #
        #         renderers[idx].AddActor(actors[idx])
        #         renderers[idx].AddActor(textactors[idx])
        #         renderers[idx].SetBackground(0.4, 0.3, 0.2)
        #
        # interactor = vtk.vtkRenderWindowInteractor()
        # interactor.SetRenderWindow(renderWindow)
        #
        # renderWindow.Render()
        #
        # interactor.Start()


if __name__ == "__main__":
    po = PlatonicSolids()
    po.PlatonicSolids()
