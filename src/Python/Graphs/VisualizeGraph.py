#!/usr/bin/env python

import vtk

g = vtk.vtkMutableDirectedGraph()

v1 = g.AddVertex()
v2 = g.AddVertex()

g.AddGraphEdge(v1, v2)
g.AddGraphEdge(v1, v2)

graphLayoutView = vtk.vtkGraphLayoutView()
graphLayoutView.AddRepresentationFromInput(g)
graphLayoutView.SetLayoutStrategy("Simple 2D")
graphLayoutView.ResetCamera()
graphLayoutView.Render()

graphLayoutView.GetLayoutStrategy().SetRandomSeed(0)

graphLayoutView.GetInteractor().Start()
