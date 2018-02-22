#!/usr/bin/env python

import vtk


def main():
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

    mappers = list()
    actors = list()
    textmappers = list()
    textactors = list()
    renderers = list()

    # Create a common text property.
    textProperty = vtk.vtkTextProperty()
    textProperty.SetFontSize(16)
    textProperty.SetJustificationToCentered()

    # Create the render window and interactor.
    renWin = vtk.vtkRenderWindow()
    renWin.SetWindowName("Platonic Solids")

    iRen = vtk.vtkRenderWindowInteractor()
    iRen.SetRenderWindow(renWin)

    # Create the source, renderer, mapper
    # and actor for each object.
    PlatonicSolids = list()
    # There are five Platonic solids.
    names = ["Tetrahedron", "Cube", "Octahedron", "Icosahedron", "Dodecahedron"]
    for i in range(0, len(names)):
        PlatonicSolids.append(vtk.vtkPlatonicSolidSource())
        PlatonicSolids[i].SetSolidType(i)

        mappers.append(vtk.vtkPolyDataMapper())
        mappers[i].SetInputConnection(PlatonicSolids[i].GetOutputPort())
        mappers[i].SetLookupTable(lut)
        mappers[i].SetScalarRange(0, 19)

        actors.append(vtk.vtkActor())
        actors[i].SetMapper(mappers[i])

        textmappers.append(vtk.vtkTextMapper())
        textmappers[i].SetInput(names[i])
        textmappers[i].SetTextProperty(textProperty)

        textactors.append(vtk.vtkActor2D())
        textactors[i].SetMapper(textmappers[i])
        textactors[i].SetPosition(120, 16)

        renderers.append(vtk.vtkRenderer())
        renderers[i].AddActor(actors[i])
        renderers[i].AddViewProp(textactors[i])

        renWin.AddRenderer(renderers[i])

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


if __name__ == "__main__":
    main()
