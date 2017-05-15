#include <vtkSmartPointer.h>

#include <vtkBoostPrimMinimumSpanningTree.h>
#include <vtkDataSetAttributes.h>
#include <vtkDoubleArray.h>
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
  
  // Create a fully connected graph
  g->AddEdge(v1, v2);
  g->AddEdge(v2, v3);
  g->AddEdge(v1, v3);
  
  // Create the edge weight array
  vtkSmartPointer<vtkDoubleArray> weights = 
    vtkSmartPointer<vtkDoubleArray>::New();
  weights->SetNumberOfComponents(1);
  weights->SetName("Weights");
  
  // Set the edge weights
  weights->InsertNextValue(1.0);
  weights->InsertNextValue(1.0);
  weights->InsertNextValue(2.0);
  
  // Add the edge weight array to the graph
  g->GetEdgeData()->AddArray(weights);
  
  // Output original graph info
  std::cout << "Number of vertices: "
            << g->GetNumberOfVertices() << std::endl;
  std::cout << "Number of edges: "
            << g->GetNumberOfEdges() << std::endl;
  g->Dump();

  // Setup the minimum spanning tree filter
  vtkSmartPointer<vtkBoostPrimMinimumSpanningTree> minimumSpanningTreeFilter = 
    vtkSmartPointer<vtkBoostPrimMinimumSpanningTree>::New();
  minimumSpanningTreeFilter->SetOriginVertex(v1);
  minimumSpanningTreeFilter->SetInput(g);
  minimumSpanningTreeFilter->SetEdgeWeightArrayName("Weights");
  
  // Compute the minimum spanning tree
  minimumSpanningTreeFilter->Update();
  
  // Get the output tree
  vtkSmartPointer<vtkTree> minimumSpanningTree = vtkSmartPointer<vtkTree>::New();
  minimumSpanningTree->ShallowCopy(minimumSpanningTreeFilter->GetOutput());
  
  // Output information about the minimum spanning tree
  std::cout << "Number of vertices: "
            << minimumSpanningTree->GetNumberOfVertices() << std::endl;
  std::cout << "Number of edges: "
            << minimumSpanningTree->GetNumberOfEdges() << std::endl;
  minimumSpanningTree->Dump();

  return EXIT_SUCCESS;
}
