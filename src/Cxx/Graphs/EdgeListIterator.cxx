#include <vtkMutableUndirectedGraph.h>
#include <vtkSmartPointer.h>
#include <vtkEdgeListIterator.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkMutableUndirectedGraph> g =
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();

  // Create a graph
  vtkIdType v0 = g->AddVertex();
  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();

  g->AddEdge(v0, v1);
  g->AddEdge(v1, v2);
  g->AddEdge(v0, v2);

  vtkSmartPointer<vtkEdgeListIterator> edgeListIterator =
      vtkSmartPointer<vtkEdgeListIterator>::New();
  g->GetEdges(edgeListIterator);

  while(edgeListIterator->HasNext())
  {
    vtkEdgeType edge = edgeListIterator->Next();
    std::cout << "Edge: " << edge.Id << " is from "
	      << "Source: " << edge.Source << " to Target: " << edge.Target << std::endl;
  }

  return EXIT_SUCCESS;
}
