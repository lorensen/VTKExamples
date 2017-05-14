#include <vtkSmartPointer.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkMutableGraphHelper.h>
#include <vtkGraphLayoutView.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char*[])
{
  vtkSmartPointer<vtkMutableUndirectedGraph> g =
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();

  vtkSmartPointer<vtkMutableGraphHelper> graphHelper =
    vtkSmartPointer<vtkMutableGraphHelper>::New();
  graphHelper->SetGraph(g);
  vtkIdType v0 = graphHelper->AddVertex();
  vtkIdType v1 = graphHelper->AddVertex();

  graphHelper->AddEdge(v0, v1);

  // Can also do this:
  graphHelper->RemoveEdge(0);
  
  vtkSmartPointer<vtkGraphLayoutView> treeLayoutView =
    vtkSmartPointer<vtkGraphLayoutView>::New();
  treeLayoutView->AddRepresentationFromInput(graphHelper->GetGraph());
  treeLayoutView->SetLayoutStrategyToTree();
  treeLayoutView->ResetCamera();
  treeLayoutView->Render();
  treeLayoutView->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
