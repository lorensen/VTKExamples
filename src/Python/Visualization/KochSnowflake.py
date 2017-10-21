#!/usr/bin/env python
# ----------------------------------------------------------------------------- #
#                                   Imports                                     #
# ----------------------------------------------------------------------------- #
from math import pi, cos, sin, sqrt
import vtk

LEVEL = 6


# ----------------------------------------------------------------------------- #
#                        Koch Snowflake as vtkPolyLine                          #
# ----------------------------------------------------------------------------- #
def as_polyline(points, level):
    # Use the points from the previous iteration to create the points of the next
    # level. There is an assumption on my part that the curve is traversed in a
    # counterclockwise fashion. If the initial triangle above is written to
    # describe clockwise motion, the points will face inward instead of outward.
    for i in range(level):
        temp = vtk.vtkPoints()
        # The first point of the previous vtkPoints is the first point of the next vtkPoints.
        temp.InsertNextPoint(*points.GetPoint(0))

        # Iterate over "edges" in the vtkPoints
        for i in range(1, points.GetNumberOfPoints()):
            x0, y0, z0 = points.GetPoint(i - 1)
            x1, y1, z1 = points.GetPoint(i)
            t = sqrt((x1 - x0)**2 + (y1 - y0)**2)
            nx = (x1 - x0) / t  # x-component of edge unit tangent
            ny = (y1 - y0) / t  # y-component of edge unit tangent

            # the points describing the Koch snowflake edge
            temp.InsertNextPoint(x0 + nx * t / 3, y0 + ny * t / 3, 0.)
            temp.InsertNextPoint(x0 + nx * t / 2 + ny * t * sqrt(3) / 6, y0 + ny * t / 2 - nx * t * sqrt(3) / 6, 0.)
            temp.InsertNextPoint(x0 + nx * 2 * t / 3, y0 + ny * 2 * t / 3, 0.)
            temp.InsertNextPoint(x0 + nx * t, y0 + ny * t, 0.)

        points = temp

    # draw the outline
    lines = vtk.vtkCellArray()
    pl = vtk.vtkPolyLine()
    pl.GetPointIds().SetNumberOfIds(points.GetNumberOfPoints())
    for i in range(points.GetNumberOfPoints()):
        pl.GetPointIds().SetId(i, i)
    lines.InsertNextCell(pl)

    # complete the polydata
    polydata = vtk.vtkPolyData()
    polydata.SetLines(lines)
    polydata.SetPoints(points)

    return polydata


# ----------------------------------------------------------------------------- #
#                  Koch Snowflake as collection of vtkTriangles                 #
# ----------------------------------------------------------------------------- #
def as_triangles(indices, cellarray, level, data):
    if len(indices) >= 3:
        stride = len(indices) // 4
        indices.append(indices[-1] + 1)

        triangle = vtk.vtkTriangle()
        triangle.GetPointIds().SetId(0, indices[stride])
        triangle.GetPointIds().SetId(1, indices[2 * stride])
        triangle.GetPointIds().SetId(2, indices[3 * stride])

        cellarray.InsertNextCell(triangle)
        data.InsertNextValue(level)

        as_triangles(indices[0: stride], cellarray, level + 1, data)
        as_triangles(indices[stride: 2 * stride], cellarray, level + 1, data)
        as_triangles(indices[2 * stride: 3 * stride], cellarray, level + 1, data)
        as_triangles(indices[3 * stride: -1], cellarray, level + 1, data)


# ----------------------------------------------------------------------------- #
#                                 Main Method                                   #
# ----------------------------------------------------------------------------- #
if __name__ == "__main__":
    # Initially, set up the points to be an equilateral triangle. Note that the
    # first point is the same as the last point to make this a closed curve when
    # I create the vtkPolyLine.
    points = vtk.vtkPoints()
    for i in range(4):
        points.InsertNextPoint(cos(2. * pi * i / 3), sin(2 * pi * i / 3.), 0.)

    outline_pd = as_polyline(points, LEVEL)
    # You have already gone through the trouble of putting the points in the
    # right places - so "all" you need todo now is to create polygons from the
    # points that are in the vtkPoints.

    # The points that are passed in, have an overlap of the beginning and the
    # end. For this next trick, I will need a list of the indices in the
    # vtkPoints. They're consecutive, so thats pretty straightforward.

    indices = [i for i in range(outline_pd.GetPoints().GetNumberOfPoints() + 1)]
    triangles = vtk.vtkCellArray()

    # Set this up for each of the initial sides, then call the recursive function.
    stride = (len(indices) - 1) // 3

    # The cell data will allow us to color the triangles based on the level of
    # the iteration of the Koch snowflake.
    data = vtk.vtkIntArray()
    data.SetNumberOfComponents(0)
    data.SetName("Iteration Level")

    # This is the starting triangle.
    t = vtk.vtkTriangle()
    t.GetPointIds().SetId(0, 0)
    t.GetPointIds().SetId(1, stride)
    t.GetPointIds().SetId(2, 2 * stride)
    triangles.InsertNextCell(t)
    data.InsertNextValue(0)

    as_triangles(indices[0: stride + 1], triangles, 1, data)
    as_triangles(indices[stride: 2 * stride + 1], triangles, 1, data)
    as_triangles(indices[2 * stride: -1], triangles, 1, data)

    triangle_pd = vtk.vtkPolyData()
    triangle_pd.SetPoints(outline_pd.GetPoints())
    triangle_pd.SetPolys(triangles)
    triangle_pd.GetCellData().SetScalars(data)

    # ---------------- #
    # rendering stuff  #
    # ---------------- #
    outline_mapper = vtk.vtkPolyDataMapper()
    outline_mapper.SetInputData(outline_pd)

    lut = vtk.vtkLookupTable()
    lut.SetNumberOfTableValues(256)
    lut.SetHueRange(0.6, 0.6)
    lut.SetSaturationRange(0., 1.)
    lut.Build()

    triangle_mapper = vtk.vtkPolyDataMapper()
    triangle_mapper.SetInputData(triangle_pd)
    triangle_mapper.SetScalarRange(0.0, LEVEL)
    triangle_mapper.SetLookupTable(lut)

    outline_actor = vtk.vtkActor()
    outline_actor.SetMapper(outline_mapper)

    triangle_actor = vtk.vtkActor()
    triangle_actor.SetMapper(triangle_mapper)

    outline_ren = vtk.vtkRenderer()
    outline_ren.AddActor(outline_actor)
    outline_ren.SetViewport(0.0, 0.0, 0.5, 1.0)

    triangle_ren = vtk.vtkRenderer()
    triangle_ren.AddActor(triangle_actor)
    triangle_ren.SetViewport(0.5, 0.0, 1.0, 1.0)
    triangle_ren.SetActiveCamera(outline_ren.GetActiveCamera())

    renw = vtk.vtkRenderWindow()
    renw.AddRenderer(outline_ren)
    renw.AddRenderer(triangle_ren)
    renw.SetSize(800, 400)

    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renw)

    outline_ren.ResetCamera()
    renw.Render()
    iren.Start()
