#include <vtkSmartPointer.h>
#include <vtkIntArray.h>
#include <vtkDataSetAttributes.h>
#include <vtkGraphLayoutView.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderedGraphRepresentation.h>
#include <vtkTextProperty.h>

int main(int, char *[])
{
  // Create a graph
  vtkSmartPointer<vtkMutableDirectedGraph> graph =
    vtkSmartPointer<vtkMutableDirectedGraph>::New();
 
  vtkIdType v1 = graph->AddVertex();
  vtkIdType v2 = graph->AddVertex();
  graph->AddEdge(v1,v2);
  
  // Create an array for the vertex labels
  vtkSmartPointer<vtkIntArray> vertexIDs =
    vtkSmartPointer<vtkIntArray>::New();
  vertexIDs->SetNumberOfComponents(1);
  vertexIDs->SetName("VertexIDs");
 
  // Set the vertex labels
  vertexIDs->InsertNextValue(0);
  vertexIDs->InsertNextValue(1);
  
  // Add the array to the graph
  graph->GetVertexData()->AddArray(vertexIDs);
  
  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView =
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView->AddRepresentationFromInput(graph);
  graphLayoutView->SetVertexLabelVisibility(true);
  dynamic_cast<vtkRenderedGraphRepresentation*>(graphLayoutView->GetRepresentation())
            ->GetVertexLabelTextProperty()->SetColor(1,0,0);
  graphLayoutView->SetLayoutStrategyToSimple2D();
  graphLayoutView->SetVertexLabelArrayName("VertexIDs");
  graphLayoutView->ResetCamera();
  graphLayoutView->Render();
  graphLayoutView->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
