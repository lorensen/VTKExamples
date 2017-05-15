#include <vtkSmartPointer.h>

#include <vtkGraphLayoutView.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTree.h>

int main (int, char *[] )
{

  vtkSmartPointer<vtkMutableDirectedGraph> graph = 
    vtkSmartPointer<vtkMutableDirectedGraph>::New();
  
  vtkIdType v1 = graph->AddVertex();
  vtkIdType v2 = graph->AddChild(v1);
  graph->AddChild(v1);
  graph->AddChild(v2);
  
  /*
  //equivalent to:
  
  vtkIdType V1 = g->AddVertex();
  vtkIdType V2 = g->AddVertex();
  vtkIdType V3 = g->AddVertex();
  vtkIdType V4 = g->AddVertex();

  g->AddEdge ( V1, V2 );
  g->AddEdge ( V1, V3 );
  g->AddEdge ( V2, V4 );
  */
  
  vtkSmartPointer<vtkTree> tree = 
    vtkSmartPointer<vtkTree>::New();
  bool success = tree->CheckedShallowCopy(graph);
  std::cout << "Success? " << success << std::endl;
  
  vtkSmartPointer<vtkGraphLayoutView> treeLayoutView = 
    vtkSmartPointer<vtkGraphLayoutView>::New();
  treeLayoutView->AddRepresentationFromInput(tree);
  treeLayoutView->SetLayoutStrategyToTree();
  treeLayoutView->ResetCamera();
  treeLayoutView->Render();
  treeLayoutView->GetInteractor()->Start();
  
  return EXIT_SUCCESS;
}
