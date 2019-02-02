#!/usr/bin/env python

import vtk

def main():
    g = vtk.vtkMutableUndirectedGraph()
    
    v1 = g.AddVertex()
    v2 = g.AddVertex()
    
    g.AddEdge ( v1, v2 )
    print ('Number of vertices:', g.GetNumberOfVertices())
    print ("Number of edges:", g.GetNumberOfEdges())
       
    g.AddEdge ( v1, v2 )
    print ('Number of vertices:', g.GetNumberOfVertices())
    print ('Number of edges:', g.GetNumberOfEdges())
    graphLayoutView = vtk.vtkGraphLayoutView()
    graphLayoutView.AddRepresentationFromInput(g)
    graphLayoutView.ResetCamera()
    graphLayoutView.Render()
    graphLayoutView.GetInteractor().Start()

if __name__ == '__main__':
    main()
