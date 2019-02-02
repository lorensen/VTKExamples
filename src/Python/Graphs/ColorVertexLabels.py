#!/usr/bin/env python

import vtk

def main():
    # Create a graph
    graph = vtk.vtkMutableDirectedGraph()
    
    v1 = graph.AddVertex()
    v2 = graph.AddVertex()
    graph.AddEdge(v1,v2)
    
    # Create an array for the vertex labels
    vertexIDs = vtk.vtkIntArray()
    vertexIDs.SetNumberOfComponents(1)
    vertexIDs.SetName("VertexIDs")
    
    # Set the vertex labels
    vertexIDs.InsertNextValue(0)
    vertexIDs.InsertNextValue(1)
    
    # Add the array to the graph
    graph.GetVertexData().AddArray(vertexIDs)
    
    graphLayoutView = vtk.vtkGraphLayoutView()
    graphLayoutView.AddRepresentationFromInput(graph)
    graphLayoutView.SetVertexLabelVisibility(1)
	
    rGraph = vtk.vtkRenderedGraphRepresentation ()
    rGraph.SafeDownCast(graphLayoutView.GetRepresentation()).GetVertexLabelTextProperty().SetColor(1,0,0)
    graphLayoutView.SetLayoutStrategyToSimple2D()
    graphLayoutView.SetVertexLabelArrayName("VertexIDs")
    graphLayoutView.ResetCamera()
    graphLayoutView.Render()
    graphLayoutView.GetInteractor().Start()

if __name__ == '__main__':
    main()
