#!/usr/bin/env python

import vtk

def main():
    # Create a graph
    graph = vtk.vtkMutableDirectedGraph()
    
    v1 = graph.AddVertex()
    v2 = graph.AddVertex()
    v3 = graph.AddVertex()
    graph.AddEdge(v1,v2)
    graph.AddEdge(v2,v3)
    
    # Manually set the position of the vertices
    points = vtk.vtkPoints()
    points.InsertNextPoint(0,0,0)
    points.InsertNextPoint(1,0,0)
    points.InsertNextPoint(2,0,0)
    
    graph.SetPoints(points)
    
    # Create the color array
    vertexColors = vtk.vtkIntArray()
    vertexColors.SetNumberOfComponents(1)
    vertexColors.SetName("Color")
    
    lookupTable = vtk.vtkLookupTable()
    lookupTable.SetNumberOfTableValues(3)
    lookupTable.SetTableValue(0, 1.0, 0.0, 0.0) # red
    lookupTable.SetTableValue(1, 1.0, 1.0, 1.0) # white
    lookupTable.SetTableValue(2, 0.0, 1.0, 0.0) # green
    lookupTable.Build()
    
    vertexColors.InsertNextValue(0)
    vertexColors.InsertNextValue(1)
    vertexColors.InsertNextValue(2)
    
    # Add the color array to the graph
    graph.GetVertexData().AddArray(vertexColors)
    
    # Visualize
    graphLayoutView = vtk.vtkGraphLayoutView()
    graphLayoutView.AddRepresentationFromInput(graph)
    graphLayoutView.SetLayoutStrategyToPassThrough()
    graphLayoutView.SetVertexColorArrayName("Color")
    graphLayoutView.ColorVerticesOn()
    
    theme = vtk.vtkViewTheme()
    theme.SetPointLookupTable(lookupTable)
    
    graphLayoutView.ApplyViewTheme(theme)
    graphLayoutView.ResetCamera()
    graphLayoutView.GetInteractor().Initialize()
    graphLayoutView.GetRenderer().GetActiveCamera().Zoom(0.8)
    graphLayoutView.GetInteractor().Start()

if __name__ == '__main__':
    main()
