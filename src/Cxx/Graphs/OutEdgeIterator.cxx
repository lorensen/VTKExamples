#include <vtkMutableUndirectedGraph.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkSmartPointer.h>
#include <vtkOutEdgeIterator.h>

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

  // Find all outgoing edges connected to a vertex
  vtkSmartPointer<vtkOutEdgeIterator> it =
    vtkSmartPointer<vtkOutEdgeIterator>::New();
  g->GetOutEdges(0, it); // Get the edges connected to vertex 0

  while(it->HasNext())
  {
    vtkOutEdgeType edge = it->Next();
    std::cout << "Edge id: " << edge.Id << " Target: " << edge.Target << std::endl;
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

  g->AddEdge(v1, v0);
  g->AddEdge(v2, v0);

  {
  std::cout << "Finding edges connected to vertex 0" << std::endl;
  vtkSmartPointer<vtkOutEdgeIterator> it =
    vtkSmartPointer<vtkOutEdgeIterator>::New();
  g->GetOutEdges(0, it);

  while(it->HasNext())
  {
    vtkOutEdgeType edge = it->Next();
    std::cout << "Edge id: " << edge.Id << " Target: " << edge.Target << std::endl;
  }

  std::cout << "Nothing should be output, vertex 0 has no outgoing edges!" << std::endl;
  }

  {
  std::cout << "Finding edges connected to vertex 1" << std::endl;
  vtkSmartPointer<vtkOutEdgeIterator> it =
    vtkSmartPointer<vtkOutEdgeIterator>::New();
  g->GetOutEdges(1, it);

  while(it->HasNext())
  {
    vtkOutEdgeType edge = it->Next();
    std::cout << "Edge id: " << edge.Id << " Target: " << edge.Target << std::endl;
  }
  }

}
