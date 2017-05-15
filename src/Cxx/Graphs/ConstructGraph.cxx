#include <vtkSmartPointer.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkCircularLayoutStrategy.h>
#include <vtkDataSetAttributes.h>
#include <vtkDoubleArray.h>
#include <vtkGraphLayoutView.h>
#include <vtkIntArray.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkMutableUndirectedGraph> g = 
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();
 
  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();
 
  g->AddEdge ( v1, v2 );
 
  std::cout << "Number of vertices: "
            << g->GetNumberOfVertices() << std::endl;
  std::cout << "Number of edges: "
            << g->GetNumberOfEdges() << std::endl;
 
  g->AddEdge ( v1, v2 );
 
  std::cout << "Number of vertices: "
            << g->GetNumberOfVertices() << std::endl;
  std::cout << "Number of edges: "
            << g->GetNumberOfEdges() << std::endl;
 
  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView = 
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView->AddRepresentationFromInput(g);
  graphLayoutView->ResetCamera();
  graphLayoutView->Render();
  graphLayoutView->GetInteractor()->Start();
  
  return EXIT_SUCCESS;
}
