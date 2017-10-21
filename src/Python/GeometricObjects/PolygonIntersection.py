#!/usr/bin/env python
from __future__ import print_function

import vtk

# Create a square in the x-y plane.
points = vtk.vtkPoints()
points.InsertNextPoint(0.0, 0.0, 0.0)
points.InsertNextPoint(1.0, 0.0, 0.0)
points.InsertNextPoint(1.0, 1.0, 0.0)
points.InsertNextPoint(0.0, 1.0, 0.0)

# Create the polygon
polygon = vtk.vtkPolygon()
polygon.GetPoints().DeepCopy(points)
polygon.GetPointIds().SetNumberOfIds(4)  # The 4 corners of the square
for i in range(4):
    polygon.GetPointIds().SetId(i, i)

# Inputs
p1 = [0.1, 0, -1.0]
p2 = [0.1, 0, 1.0]
tolerance = 0.001

# Outputs
t = vtk.mutable(0)  # Parametric coordinate of intersection (0 (corresponding to p1) to 1 (corresponding to p2))
x = [0.0, 0.0, 0.0]
pcoords = [0.0, 0.0, 0.0]
subId = vtk.mutable(0)
iD = polygon.IntersectWithLine(p1, p2, tolerance, t, x, pcoords, subId)

print("intersected? ", iD)
print("intersection: ", x)
