#include <vtkSmartPointer.h>

#include <vtkMutableUndirectedGraph.h>
#include <vtkPoints.h>
#include <vtkRemoveIsolatedVertices.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkMutableUndirectedGraph> g = 
      vtkSmartPointer<vtkMutableUndirectedGraph>::New();
  
  // Create 3 vertices
  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();
  g->AddVertex();
  
  g->AddEdge ( v1, v2 );
  
  std::cout << "Graph has "
            << g->GetNumberOfVertices()
            << " vertices and " 
            << g->GetNumberOfEdges() << " edge before." << std::endl;
  
  vtkSmartPointer<vtkRemoveIsolatedVertices> filter = 
    vtkSmartPointer<vtkRemoveIsolatedVertices>::New();
  filter->SetInputConnection(g->GetProducerPort());
  filter->Update();
  
  std::cout << "Graph has "
            << filter->GetOutput()->GetNumberOfVertices() 
            << " vertices and "
            << filter->GetOutput()->GetNumberOfEdges()
            << " edge after." << std::endl;
  
  return EXIT_SUCCESS;
}
