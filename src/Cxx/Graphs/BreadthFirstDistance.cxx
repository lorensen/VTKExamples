#include <vtkSmartPointer.h>

#include <vtkBoostBreadthFirstSearch.h>
#include <vtkDataSetAttributes.h>
#include <vtkDoubleArray.h>
#include <vtkIntArray.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkTree.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkMutableUndirectedGraph> g =
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();

  // Create 3 vertices
  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();
  vtkIdType v3 = g->AddVertex();
  vtkIdType v4 = g->AddVertex();

  // Create a graph
  g->AddEdge(v1, v2);
  g->AddEdge(v1, v3);
  g->AddEdge(v2, v4);

  vtkSmartPointer<vtkBoostBreadthFirstSearch> BFS =
    vtkSmartPointer<vtkBoostBreadthFirstSearch>::New();
  BFS->SetOriginVertex(v1);
  BFS->SetInput(g);
  BFS->Update();

  vtkIntArray* level = dynamic_cast<vtkIntArray*>(
    BFS->GetOutput()->GetVertexData()->GetArray("BFS"));
  for(vtkIdType i = 0; i < level->GetNumberOfTuples(); i++)
  {
    std::cout << "id " << i << " : " << level->GetValue(i) << std::endl;
  }
  return EXIT_SUCCESS;
}
