#!/usr/bin/env python
from __future__ import print_function

import vtk

sphereSource = vtk.vtkSphereSource()
sphereSource.Update()

bounds = [0 for i in range(6)]
sphereSource.GetOutput().GetBounds(bounds)

box = vtk.vtkPoints()

box.SetNumberOfPoints(8)

xMin = bounds[0]
xMax = bounds[1]
yMin = bounds[2]
yMax = bounds[3]
zMin = bounds[4]
zMax = bounds[5]

box.SetPoint(0, xMax, yMin, zMax)
box.SetPoint(1, xMax, yMin, zMin)
box.SetPoint(2, xMax, yMax, zMin)
box.SetPoint(3, xMax, yMax, zMax)
box.SetPoint(4, xMin, yMin, zMax)
box.SetPoint(5, xMin, yMin, zMin)
box.SetPoint(6, xMin, yMax, zMin)
box.SetPoint(7, xMin, yMax, zMax)

planesIntersection = vtk.vtkPlanesIntersection()
planesIntersection.SetBounds(bounds)

intersects = planesIntersection.IntersectsRegion(box)

print("Intersects? ", intersects == 1)
