#include <vtkSmartPointer.h>
#include <vtkDataSetAttributes.h>
#include <vtkDoubleArray.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkCircularLayoutStrategy.h>
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

  // Add the edge weight array to the graph
  g->GetEdgeData()->AddArray(weights);

  std::cout << "Number of Weights: "
            << dynamic_cast<vtkDoubleArray*>(
              g->GetEdgeData()->GetArray("Weights"))->GetNumberOfTuples()
            << std::endl;

  for(vtkIdType i = 0; i < weights->GetNumberOfTuples(); i++)
  {
    double w = weights->GetValue(i);
    std::cout << "Weight " << i << " : " << w << std::endl;
  }

  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView =
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView->AddRepresentationFromInput(g);
  graphLayoutView->SetEdgeLabelVisibility(true);
  graphLayoutView->SetEdgeLabelArrayName("Weights");
  graphLayoutView->ResetCamera();
  graphLayoutView->Render();
  graphLayoutView->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
