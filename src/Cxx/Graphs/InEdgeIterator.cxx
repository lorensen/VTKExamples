#include <vtkMutableUndirectedGraph.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkSmartPointer.h>
#include <vtkInEdgeIterator.h>

static void Undirected();
static void Directed();

int main(int, char *[])
{
  Undirected();
  Directed();

  return EXIT_SUCCESS;
}

void Undirected()
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

  // Find all incoming edges connected to a vertex
  vtkSmartPointer<vtkInEdgeIterator> it =
    vtkSmartPointer<vtkInEdgeIterator>::New();
  g->GetInEdges(0, it);

  while(it->HasNext())
  {
    vtkInEdgeType edge = it->Next();
    std::cout << "Edge id: " << edge.Id << " Source: " << edge.Source << std::endl;
  }
}

void Directed()
{
  vtkSmartPointer<vtkMutableDirectedGraph> g =
    vtkSmartPointer<vtkMutableDirectedGraph>::New();

  // Create a graph
  vtkIdType v0 = g->AddVertex();
  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();

  g->AddEdge(v0, v1);
  g->AddEdge(v0, v2);

  {
  std::cout << "Finding edges connected to vertex 0" << std::endl;
  vtkSmartPointer<vtkInEdgeIterator> it =
    vtkSmartPointer<vtkInEdgeIterator>::New();
  g->GetInEdges(0, it);

  while(it->HasNext())
  {
    vtkInEdgeType edge = it->Next();
    std::cout << "Edge id: " << edge.Id << " " << "Source: " << edge.Source << std::endl;
  }

  std::cout << "Nothing should be output, vertex 0 has no incoming edges!" << std::endl;
  }

  {
  std::cout << "Finding edges connected to vertex 1" << std::endl;
  vtkSmartPointer<vtkInEdgeIterator> it =
    vtkSmartPointer<vtkInEdgeIterator>::New();
  g->GetInEdges(1, it);

  while(it->HasNext())
  {
    vtkInEdgeType edge = it->Next();
    std::cout << "Edge id: " << edge.Id << " " << "Source: " << edge.Source << std::endl;
  }
  }

}
