#!/usr/bin/env python
import vtk

def main():
    # Create the first graph
    g0 = vtk.vtkMutableUndirectedGraph()

    v1 = g0.AddVertex()
    v2 = g0.AddVertex()
    v3 = g0.AddVertex()
    
    g0.AddEdge(v1, v2)
    g0.AddEdge(v2, v3)
    g0.AddEdge(v1, v3)
    
    # Create points
    points = vtk.vtkPoints()
    points.InsertNextPoint(0.0, 0.0, 0.0)
    points.InsertNextPoint(1.0, 0.0, 0.0)
    points.InsertNextPoint(0.0, 1.0, 0.0)
    
    # Add the coordinates of the points to the graph
    g0.SetPoints(points)
    
    
    # Create the second graph
    g1 = vtk.vtkMutableUndirectedGraph()
    
    v1 = g1.AddVertex()
    v2 = g1.AddVertex()
    
    g1.AddEdge(v1, v2)
    
    # Create points
    points = vtk.vtkPoints()
    points.InsertNextPoint(0.0, 0.0, 0.0)
    points.InsertNextPoint(1.0, 0.0, 0.0)
    
    # Add the coordinates of the points to the graph
    g1.SetPoints(points)
    
    # There will be one render window
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetSize(600, 300)
    
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    
    # Define viewport ranges
    # (xmin, ymin, xmax, ymax)
    leftViewport = [0.0, 0.0, 0.5, 1.0]
    rightViewport = [0.5, 0.0, 1.0, 1.0]
    
    graphLayoutView0 = vtk.vtkGraphLayoutView()
    graphLayoutView0.SetRenderWindow(renderWindow)
    graphLayoutView0.SetInteractor(renderWindowInteractor)
    graphLayoutView0.GetRenderer().SetViewport(leftViewport)
    graphLayoutView0.AddRepresentationFromInput(g0)
    graphLayoutView0.ResetCamera()
    graphLayoutView0.Render()
    
    graphLayoutView1 = vtk.vtkGraphLayoutView()
    graphLayoutView1.SetRenderWindow(renderWindow)
    graphLayoutView1.SetInteractor(renderWindowInteractor)
    graphLayoutView1.GetRenderer().SetViewport(rightViewport)
    graphLayoutView1.AddRepresentationFromInput(g1)
    graphLayoutView1.ResetCamera()
    graphLayoutView1.Render()
    
    #graphLayoutView0.GetInteractor().Start()
    renderWindowInteractor.Start()

if __name__ == '__main__':
    main()
