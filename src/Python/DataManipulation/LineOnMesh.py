#!/usr/bin/env python

import numpy as np
import vtk


def main():
    named_colors = vtk.vtkNamedColors()

    # Make a 32 x 32 grid.
    size = 32

    # Define z values for the topography.
    # Comment out the following line if you want a different random
    #  distribution each time the script is run.
    np.random.seed(3)
    topography = np.random.randint(0, 5, (size, size))

    # Define points, triangles and colors
    colors = vtk.vtkUnsignedCharArray()
    colors.SetNumberOfComponents(3)
    points = vtk.vtkPoints()
    triangles = vtk.vtkCellArray()

    # Build the meshgrid manually.
    count = 0
    for i in range(size - 1):
        for j in range(size - 1):
            z1 = topography[i][j]
            z2 = topography[i][j + 1]
            z3 = topography[i + 1][j]

            # Triangle 1
            points.InsertNextPoint(i, j, z1)
            points.InsertNextPoint(i, (j + 1), z2)
            points.InsertNextPoint((i + 1), j, z3)

            triangle = vtk.vtkTriangle()
            triangle.GetPointIds().SetId(0, count)
            triangle.GetPointIds().SetId(1, count + 1)
            triangle.GetPointIds().SetId(2, count + 2)

            triangles.InsertNextCell(triangle)

            z1 = topography[i][j + 1]
            z2 = topography[i + 1][j + 1]
            z3 = topography[i + 1][j]

            # Triangle 2
            points.InsertNextPoint(i, (j + 1), z1)
            points.InsertNextPoint((i + 1), (j + 1), z2)
            points.InsertNextPoint((i + 1), j, z3)

            triangle = vtk.vtkTriangle()
            triangle.GetPointIds().SetId(0, count + 3)
            triangle.GetPointIds().SetId(1, count + 4)
            triangle.GetPointIds().SetId(2, count + 5)

            count += 6

            triangles.InsertNextCell(triangle)

            # Add some color.
            r = [int(i / float(size) * 255), int(j / float(size) * 255), 0]
            colors.InsertNextTypedTuple(r)
            colors.InsertNextTypedTuple(r)
            colors.InsertNextTypedTuple(r)
            colors.InsertNextTypedTuple(r)
            colors.InsertNextTypedTuple(r)
            colors.InsertNextTypedTuple(r)

    # Create a polydata object.
    trianglePolyData = vtk.vtkPolyData()

    # Add the geometry and topology to the polydata.
    trianglePolyData.SetPoints(points)
    trianglePolyData.GetPointData().SetScalars(colors)
    trianglePolyData.SetPolys(triangles)

    # Clean the polydata so that the edges are shared!
    cleanPolyData = vtk.vtkCleanPolyData()
    cleanPolyData.SetInputData(trianglePolyData)

    # Use a filter to smooth the data (will add triangles and smooth).
    smooth_loop = vtk.vtkLoopSubdivisionFilter()
    smooth_loop.SetNumberOfSubdivisions(3)
    smooth_loop.SetInputConnection(cleanPolyData.GetOutputPort())

    # Create a mapper and actor for smoothed dataset.
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(smooth_loop.GetOutputPort())
    actor_loop = vtk.vtkActor()
    actor_loop.SetMapper(mapper)
    actor_loop.GetProperty().SetInterpolationToFlat()

    # Update the pipeline so that vtkCellLocator finds cells!
    smooth_loop.Update()

    # Define a cellLocator to be able to compute intersections between lines.
    # and the surface
    locator = vtk.vtkCellLocator()
    locator.SetDataSet(smooth_loop.GetOutput())
    locator.BuildLocator()

    maxloop = 1000
    dist = 20.0 / maxloop
    tolerance = 0.001

    # Make a list of points. Each point is the intersection of a vertical line
    # defined by p1 and p2 and the surface.
    points = vtk.vtkPoints()
    for i in range(maxloop):
        p1 = [2 + i * dist, 16, -1]
        p2 = [2 + i * dist, 16, 6]

        # Outputs (we need only pos which is the x, y, z position
        # of the intersection)
        t = vtk.mutable(0)
        pos = [0.0, 0.0, 0.0]
        pcoords = [0.0, 0.0, 0.0]
        subId = vtk.mutable(0)
        locator.IntersectWithLine(p1, p2, tolerance, t, pos, pcoords, subId)

        # Add a slight offset in z.
        pos[2] += 0.01
        # Add the x, y, z position of the intersection.
        points.InsertNextPoint(pos)

    # Create a spline and add the points
    spline = vtk.vtkParametricSpline()
    spline.SetPoints(points)
    functionSource = vtk.vtkParametricFunctionSource()
    functionSource.SetUResolution(maxloop)
    functionSource.SetParametricFunction(spline)

    # Map the spline
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(functionSource.GetOutputPort())

    # Define the line actor
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetColor(named_colors.GetColor3d("Red"))
    actor.GetProperty().SetLineWidth(3)

    # Visualize
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    # Add actors and render
    renderer.AddActor(actor)
    renderer.AddActor(actor_loop)

    renderer.SetBackground(named_colors.GetColor3d("Cornsilk"))
    renderWindow.SetSize(800, 800)
    renderWindow.Render()
    renderer.GetActiveCamera().SetPosition(-32.471276, 53.258788, 61.209332)
    renderer.GetActiveCamera().SetFocalPoint(15.500000, 15.500000, 2.000000)
    renderer.GetActiveCamera().SetViewUp(0.348057, -0.636740, 0.688055)
    renderer.ResetCameraClippingRange()
    renderWindow.Render()

    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
