#!/usr/bin/env python

import vtk


def main():
    colors = vtk.vtkNamedColors()

    renderer = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(renderer)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    vol = vtk.vtkStructuredPoints()
    vol.SetDimensions(26, 26, 26)
    vol.SetOrigin(-0.5, -0.5, -0.5)
    sp = 1.0 / 25.0
    vol.SetSpacing(sp, sp, sp)

    scalars = vtk.vtkDoubleArray()
    scalars.SetNumberOfComponents(1)
    scalars.SetNumberOfTuples(26 * 26 * 26)
    for k in range(0, 26):
        z = -0.5 + k * sp
        kOffset = k * 26 * 26
        for j in range(0, 26):
            y = -0.5 + j * sp
            jOffset = j * 26
            for i in range(0, 26):
                x = -0.5 + i * sp
                s = x * x + y * y + z * z - (0.4 * 0.4)
                offset = i + jOffset + kOffset
                scalars.InsertTuple1(offset, s)
    vol.GetPointData().SetScalars(scalars)

    contour = vtk.vtkContourFilter()
    contour.SetInputData(vol)
    contour.SetValue(0, 0.0)

    volMapper = vtk.vtkPolyDataMapper()
    volMapper.SetInputConnection(contour.GetOutputPort())
    volMapper.ScalarVisibilityOff()
    volActor = vtk.vtkActor()
    volActor.SetMapper(volMapper)
    volActor.GetProperty().EdgeVisibilityOn()
    volActor.GetProperty().SetColor(colors.GetColor3d("Salmon"))
    renderer.AddActor(volActor)
    renderer.SetBackground(colors.GetColor3d("SlateGray"))
    renWin.SetSize(512, 512)

    # Interact with the data.
    renWin.Render()

    iren.Start()


if __name__ == "__main__":
    main()
