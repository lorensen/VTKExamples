#!/usr/bin/env python
import vtk
def main():
    graph = vtk.vtkMutableDirectedGraph()
    
    v1 = graph.AddVertex()
    v2 = graph.AddChild(v1)
    graph.AddChild(v1)
    graph.AddChild(v2)
  
    #equivalent to:
    #V1 = g.AddVertex()
    #V2 = g.AddVertex()
    #V3 = g.AddVertex()
    #V4 = g.AddVertex()
    
    #g.AddEdge ( V1, V2 )
    #g.AddEdge ( V1, V3 )
    #g.AddEdge ( V2, V4 )
    
    tree = vtk.vtkTree()
    success = tree.CheckedShallowCopy(graph)
    print ('Success?', success)
    #std::cout << "Success? " << success << std::endl
    
    treeLayoutView = vtk.vtkGraphLayoutView()
    treeLayoutView.AddRepresentationFromInput(tree)
    treeLayoutView.SetLayoutStrategyToTree()
    treeLayoutView.ResetCamera()
    treeLayoutView.Render()
    treeLayoutView.GetInteractor().Start()

if __name__ == '__main__':
    main()
