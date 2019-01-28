#!/usr/bin/env python

import vtk

def main():
    colors = vtk.vtkNamedColors()
	  # Create a graph
    g = vtk.vtkMutableUndirectedGraph()
    
    # Add 4 vertices to the graph
    v1 = g.AddVertex()
    v2 = g.AddVertex()
    v3 = g.AddVertex()
    v4 = g.AddVertex()
    
    # Add 3 edges to the graph
    g.AddEdge ( v1, v2 )
    g.AddEdge ( v1, v3 )
    g.AddEdge ( v1, v4 )
    
    # Create 4 points - one for each vertex
    points = vtk.vtkPoints()
    points.InsertNextPoint(0.0, 0.0, 0.0)
    points.InsertNextPoint(1.0, 0.0, 0.0)
    points.InsertNextPoint(0.0, 1.0, 0.0)
    points.InsertNextPoint(0.0, 0.0, 1.0)
    
    # Add the coordinates of the points to the graph
    g.SetPoints(points)
    
    # Convert the graph to a polydata
    graphToPolyData = vtk.vtkGraphToPolyData()
    graphToPolyData.SetInputData(g)
    graphToPolyData.Update()
    
    # Create a mapper and actor
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(graphToPolyData.GetOutputPort())
    
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    
    # Create a renderer, render window, and interactor
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)
    
    # Add the actor to the scene
    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("green")) # Background color green
    
    # Render and interact
    renderWindow.Render()
    renderWindowInteractor.Start()

if __name__ == '__main__':
    main()
