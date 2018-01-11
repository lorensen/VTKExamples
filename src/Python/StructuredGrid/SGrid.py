#!/usr/bin/env python

"""
This example shows how to manually create a structured grid.
The basic idea is to instantiate vtkStructuredGrid, set its dimensions,
 and then assign points defining the grid coordinate. The number of
 points must equal the number of points implicit in the dimensions
 (i.e., dimX*dimY*dimZ). Also, data attributes (either point or cell)
 can be added to the dataset.
"""

import math

import vtk


def main():
    colors = vtk.vtkNamedColors()

    rMin = 0.5
    rMax = 1.0
    dims = [13, 11, 11]

    # Create the structured grid.
    sgrid = vtk.vtkStructuredGrid()
    sgrid.SetDimensions(dims)

    # We also create the points and vectors. The points
    # form a hemi-cylinder of data.
    vectors = vtk.vtkDoubleArray()
    vectors.SetNumberOfComponents(3)
    vectors.SetNumberOfTuples(dims[0] * dims[1] * dims[2])
    points = vtk.vtkPoints()
    points.Allocate(dims[0] * dims[1] * dims[2])

    deltaZ = 2.0 / (dims[2] - 1)
    deltaRad = (rMax - rMin) / (dims[1] - 1)
    x = [0.0] * 3
    v = [0.0] * 3
    for k in range(0, dims[2]):
        x[2] = -1.0 + k * deltaZ
        kOffset = k * dims[0] * dims[1]
        for j in range(0, dims[1]):
            radius = rMin + j * deltaRad
            jOffset = j * dims[0]
            for i in range(0, dims[0]):
                theta = i * vtk.vtkMath.RadiansFromDegrees(15.0)
                x[0] = radius * math.cos(theta)
                x[1] = radius * math.sin(theta)
                v[0] = -x[1]
                v[1] = x[0]
                offset = i + jOffset + kOffset
                points.InsertPoint(offset, x)
                vectors.InsertTuple(offset, v)
    sgrid.SetPoints(points)
    sgrid.GetPointData().SetVectors(vectors)

    # We create a simple pipeline to display the data.
    hedgehog = vtk.vtkHedgeHog()
    hedgehog.SetInputData(sgrid)
    hedgehog.SetScaleFactor(0.1)

    sgridMapper = vtk.vtkPolyDataMapper()
    sgridMapper.SetInputConnection(hedgehog.GetOutputPort())
    sgridActor = vtk.vtkActor()
    sgridActor.SetMapper(sgridMapper)
    sgridActor.GetProperty().SetColor(colors.GetColor3d("Peacock"))

    # Create the usual rendering stuff
    renderer = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(renderer)

    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    renderer.AddActor(sgridActor)
    renderer.SetBackground(colors.GetColor3d("Beige"))
    renderer.ResetCamera()
    renderer.GetActiveCamera().Elevation(60.0)
    renderer.GetActiveCamera().Azimuth(30.0)
    renderer.GetActiveCamera().Dolly(1.25)
    renWin.SetSize(640, 480)

    # Interact with the data.
    renWin.Render()
    iren.Start()


if __name__ == "__main__":
    main()
