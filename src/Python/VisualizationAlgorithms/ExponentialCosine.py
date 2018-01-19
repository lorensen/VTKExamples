#!/usr/bin/env python

import math

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Create the RenderWindow, Renderer and Interactor.
    #
    ren = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren)

    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # create plane to warp
    plane = vtk.vtkPlaneSource()
    plane.SetResolution(300, 300)

    transform = vtk.vtkTransform()
    transform.Scale(10.0, 10.0, 1.0)

    transF = vtk.vtkTransformPolyDataFilter()
    transF.SetInputConnection(plane.GetOutputPort())
    transF.SetTransform(transform)
    transF.Update()

    # Compute the Bessel function and derivatives. This portion could be
    # encapsulated into source or filter object.
    #
    inputPd = transF.GetOutput()
    numPts = inputPd.GetNumberOfPoints()

    newPts = vtk.vtkPoints()
    newPts.SetNumberOfPoints(numPts)

    derivs = vtk.vtkDoubleArray()
    derivs.SetNumberOfTuples(numPts)

    bessel = vtk.vtkPolyData()
    bessel.CopyStructure(inputPd)
    bessel.SetPoints(newPts)
    bessel.GetPointData().SetScalars(derivs)

    x = [0.0] * 3
    for i in range(0, numPts):
        inputPd.GetPoint(i, x)
        r = math.sqrt(float(x[0] * x[0]) + x[1] * x[1])
        x[2] = math.exp(-r) * math.cos(10.0 * r)
        newPts.SetPoint(i, x)
        deriv = -math.exp(-r) * (math.cos(10.0 * r) + 10.0 * math.sin(10.0 * r))
        derivs.SetValue(i, deriv)

    # Warp the plane.
    warp = vtk.vtkWarpScalar()
    warp.SetInputData(bessel)
    warp.XYPlaneOn()
    warp.SetScaleFactor(0.5)

    # Mapper and actor.
    mapper = vtk.vtkDataSetMapper()
    mapper.SetInputConnection(warp.GetOutputPort())
    tmp = bessel.GetScalarRange()
    mapper.SetScalarRange(tmp[0], tmp[1])

    carpet = vtk.vtkActor()
    carpet.SetMapper(mapper)

    # Assign our actor to the renderer.
    ren.AddActor(carpet)
    ren.SetBackground(colors.GetColor3d("Beige"))
    renWin.SetSize(640, 480)

    # draw the resulting scene
    ren.ResetCamera()
    ren.GetActiveCamera().Zoom(1.4)
    ren.GetActiveCamera().Elevation(-55)
    ren.GetActiveCamera().Azimuth(25)
    ren.ResetCameraClippingRange()

    renWin.Render()
    iren.Start()


if __name__ == '__main__':
    main()
