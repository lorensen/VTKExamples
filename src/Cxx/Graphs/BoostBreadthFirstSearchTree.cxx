#include <vtkSmartPointer.h>

#include <vtkBoostBreadthFirstSearchTree.h>
#include <vtkDataSetAttributes.h>
#include <vtkDoubleArray.h>
#include <vtkGraphLayoutView.h>
#include <vtkIntArray.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTree.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkMutableUndirectedGraph> g = 
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();
  
  // Create 5 vertices
  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();
  vtkIdType v3 = g->AddVertex();
  vtkIdType v4 = g->AddVertex();
  vtkIdType v5 = g->AddVertex();
  
  // Create a graph
  g->AddEdge(v1, v2);
  g->AddEdge(v1, v3);
  g->AddEdge(v2, v4);
  g->AddEdge(v4, v5);
  
  vtkSmartPointer<vtkBoostBreadthFirstSearchTree> bfsTree = 
    vtkSmartPointer<vtkBoostBreadthFirstSearchTree>::New();
  bfsTree->SetOriginVertex(v5);
  bfsTree->SetInput(g);
  bfsTree->Update();
  
  {
  // Original graph
  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView = 
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView->AddRepresentationFromInput(g);
  graphLayoutView->SetLayoutStrategyToTree();
  graphLayoutView->ResetCamera();
  graphLayoutView->Render();
  graphLayoutView->GetInteractor()->Start();
  }
  
  {
  // BFS tree
  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView = 
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView->SetLayoutStrategyToTree();
  graphLayoutView->AddRepresentationFromInput(bfsTree->GetOutput());
  graphLayoutView->ResetCamera();
  graphLayoutView->Render();
  graphLayoutView->GetInteractor()->Start();
  }
  
  return EXIT_SUCCESS;
}
