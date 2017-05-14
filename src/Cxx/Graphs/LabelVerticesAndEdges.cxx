#include <vtkSmartPointer.h>

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
  
  // Create an array for the vertex labels
  vtkSmartPointer<vtkIntArray> vertexIDs =
    vtkSmartPointer<vtkIntArray>::New();
  vertexIDs->SetNumberOfComponents(1);
  vertexIDs->SetName("VertexIDs");
  
  // Set the vertex labels
  vertexIDs->InsertNextValue(0);
  vertexIDs->InsertNextValue(1);
  vertexIDs->InsertNextValue(2);
  
  // Add the edge weight array to the graph
  g->GetEdgeData()->AddArray(weights);
  g->GetVertexData()->AddArray(vertexIDs);
  
  vtkSmartPointer<vtkCircularLayoutStrategy> circularLayoutStrategy = 
    vtkSmartPointer<vtkCircularLayoutStrategy>::New();
  
  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView = 
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView->AddRepresentationFromInput(g);
  
  graphLayoutView->SetLayoutStrategy(circularLayoutStrategy);
  graphLayoutView->SetVertexLabelVisibility(true);
  graphLayoutView->SetEdgeLabelVisibility(true);
  graphLayoutView->SetEdgeLabelArrayName("Weights"); //default is "labels"
  graphLayoutView->SetVertexLabelArrayName("VertexIDs"); //default is "labels"
  graphLayoutView->ResetCamera();
  graphLayoutView->Render();
  graphLayoutView->GetInteractor()->Start();
  
  return EXIT_SUCCESS;
}
