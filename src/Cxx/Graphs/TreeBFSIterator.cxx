#include <vtkSmartPointer.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkTree.h>
#include <vtkTreeBFSIterator.h>

int main(int argc, char *argv[])
{
  //create a tree
  vtkSmartPointer<vtkMutableDirectedGraph> g =
    vtkSmartPointer<vtkMutableDirectedGraph>::New();

  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();
  vtkIdType v3 = g->AddVertex();

  g->AddEdge(v1, v2);
  g->AddEdge(v1, v3);

  vtkSmartPointer<vtkTree> tree =
    vtkSmartPointer<vtkTree>::New();
  tree->CheckedShallowCopy(g);

  //setup the iterator
  vtkIdType root = 0;

  vtkSmartPointer<vtkTreeBFSIterator> bfsIterator =
      vtkSmartPointer<vtkTreeBFSIterator>::New();
  bfsIterator->SetStartVertex(root);
  bfsIterator->SetTree(tree);

  //traverse the tree in a breadth first fashion
  while(bfsIterator->HasNext())
  {
    vtkIdType nextVertex = bfsIterator->Next();
    std::cout << "Next vertex: " << nextVertex << std::endl;
  }

  return EXIT_SUCCESS;
}
