#!/usr/bin/env python

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Set the background color.
    colors.SetColor("BkgColor", [51, 77, 102, 255])

    sphere = vtk.vtkSphere()

    # Sample the function
    sample = vtk.vtkSampleFunction()
    sample.SetSampleDimensions(50,50,50)
    sample.SetImplicitFunction(sphere)
    value = 2.0
    xmin = -value; xmax = value
    ymin = -value; ymax = value
    zmin = -value; zmax = value
    sample.SetModelBounds(xmin, xmax, ymin, ymax, zmin, zmax)

    # Create the 0 isosurface
    contours = vtk.vtkContourFilter()
    contours.SetInputConnection(sample.GetOutputPort())
    contours.GenerateValues(1, 1, 1)

    # Map the contours to graphical primitives
    contourMapper =  vtk.vtkPolyDataMapper()
    contourMapper.SetInputConnection(contours.GetOutputPort())
    contourMapper.ScalarVisibilityOff()

    # Create an actor for the contours
    contourActor = vtk.vtkActor()
    contourActor.SetMapper(contourMapper)

    # Visualize
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderWindow)

    renderer.AddActor(contourActor)
    renderer.SetBackground(colors.GetColor3d("BkgColor"))

    renderWindow.Render()
    interactor.Start()

if __name__ == '__main__':
    main()


