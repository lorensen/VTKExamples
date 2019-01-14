#!/usr/bin/env python

import vtk


def main():
    colors = vtk.vtkNamedColors()

    lines = vtk.vtkLineSource()
    # Create two points, P0 and P1
    p0 = [1.0, 0.0, 0.0]
    p1 = [5.0, 0.0, 0.0]

    lines.SetResolution(11)
    lines.SetPoint1(p0)
    lines.SetPoint2(p1)
    lines.Update()
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(lines.GetOutputPort())

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetLineWidth(5)
    actor.GetProperty().SetColor(colors.GetColor3d("Banana"))

    StippledLine(actor, 0xA1A1, 2)

    ren1 = vtk.vtkRenderer()
    ren1.SetBackground(colors.GetColor3d("SlateGray"))
    renWin = vtk.vtkRenderWindow()
    renWin.SetSize(640, 480)

    renWin.AddRenderer(ren1)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)
    ren1.AddActor(actor)
    renWin.Render()
    iren.Start()


def StippledLine(actor, lineStipplePattern, lineStippleRepeat):
    tcoords = vtk.vtkDoubleArray()
    image = vtk.vtkImageData()
    texture = vtk.vtkTexture()

    # Create texture
    dimension = 16 * lineStippleRepeat

    image.SetDimensions(dimension, 1, 1)
    image.AllocateScalars(vtk.VTK_UNSIGNED_CHAR, 4)
    image.SetExtent(0, dimension - 1, 0, 0, 0, 0)
    on = 255
    off = 0
    i_dim = 0
    while i_dim < dimension:
        for i in range(0, 16):
            mask = (1 << i)
            bit = (lineStipplePattern & mask) >> i
            value = bit
            if value == 0:
                for j in range(0, lineStippleRepeat):
                    image.SetScalarComponentFromFloat(i_dim, 0, 0, 0, on)
                    image.SetScalarComponentFromFloat(i_dim, 0, 0, 1, on)
                    image.SetScalarComponentFromFloat(i_dim, 0, 0, 2, on)
                    image.SetScalarComponentFromFloat(i_dim, 0, 0, 3, off)
                    i_dim += 1
            else:
                for j in range(0, lineStippleRepeat):
                    image.SetScalarComponentFromFloat(i_dim, 0, 0, 0, on)
                    image.SetScalarComponentFromFloat(i_dim, 0, 0, 1, on)
                    image.SetScalarComponentFromFloat(i_dim, 0, 0, 2, on)
                    image.SetScalarComponentFromFloat(i_dim, 0, 0, 3, on)
                    i_dim += 1
    polyData = actor.GetMapper().GetInput()
    # Create texture coordinates
    tcoords.SetNumberOfComponents(1)
    tcoords.SetNumberOfTuples(polyData.GetNumberOfPoints())
    for i in range(0, polyData.GetNumberOfPoints()):
        value = i * 0.5
        tcoords.SetTypedTuple(i, [value])
    polyData.GetPointData().SetTCoords(tcoords)
    texture.SetInputData(image)
    texture.InterpolateOff()
    texture.RepeatOn()

    actor.SetTexture(texture)


if __name__ == '__main__':
    main()
