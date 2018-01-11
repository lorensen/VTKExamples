#!/usr/bin/env python

import vtk


def main():
    colors = vtk.vtkNamedColors()
    renderer = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(renderer)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    sphere = vtk.vtkSphereSource()
    sphere.SetThetaResolution(12)
    sphere.SetPhiResolution(12)

    aTransform = vtk.vtkTransform()
    aTransform.Scale(1, 1.5, 2)

    transFilter = vtk.vtkTransformFilter()
    transFilter.SetInputConnection(sphere.GetOutputPort())
    transFilter.SetTransform(aTransform)

    colorIt = vtk.vtkElevationFilter()
    colorIt.SetInputConnection(transFilter.GetOutputPort())
    colorIt.SetLowPoint(0, 0, -1)
    colorIt.SetHighPoint(0, 0, 1)

    lut = vtk.vtkLookupTable()
    lut.SetHueRange(0.667, 0)
    lut.SetSaturationRange(1, 1)
    lut.SetValueRange(1, 1)

    mapper = vtk.vtkDataSetMapper()
    mapper.SetLookupTable(lut)
    mapper.SetInputConnection(colorIt.GetOutputPort())

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)

    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("SlateGray"))
    renderer.ResetCamera()
    renderer.GetActiveCamera().Elevation(60.0)
    renderer.GetActiveCamera().Azimuth(30.0)
    renderer.ResetCameraClippingRange()

    renWin.SetSize(640, 480)

    renWin.Render()

    # Interact with the data.
    iren.Start()


if __name__ == '__main__':
    main()
