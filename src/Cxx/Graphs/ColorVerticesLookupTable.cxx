#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkDataSetAttributes.h>
#include <vtkGraphLayoutView.h>
#include <vtkIntArray.h>
#include <vtkLookupTable.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkViewTheme.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

int main(int, char *[])
{
  // Create a graph
  vtkSmartPointer<vtkMutableDirectedGraph> graph =
    vtkSmartPointer<vtkMutableDirectedGraph>::New();

  vtkIdType v1 = graph->AddVertex();
  vtkIdType v2 = graph->AddVertex();
  vtkIdType v3 = graph->AddVertex();
  graph->AddEdge(v1,v2);
  graph->AddEdge(v2,v3);
  
  // Manually set the position of the vertices
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(1,0,0);
  points->InsertNextPoint(2,0,0);

  graph->SetPoints(points);
  
  // Create the color array
  vtkSmartPointer<vtkIntArray> vertexColors =
    vtkSmartPointer<vtkIntArray>::New();
  vertexColors->SetNumberOfComponents(1);
  vertexColors->SetName("Color");

  vtkSmartPointer<vtkLookupTable> lookupTable =
    vtkSmartPointer<vtkLookupTable>::New();
  lookupTable->SetNumberOfTableValues(3);
  lookupTable->SetTableValue(0, 1.0, 0.0, 0.0); // red
  lookupTable->SetTableValue(1, 1.0, 1.0, 1.0); // white
  lookupTable->SetTableValue(2, 0.0, 1.0, 0.0); // green
  lookupTable->Build();

  vertexColors->InsertNextValue(0);
  vertexColors->InsertNextValue(1);
  vertexColors->InsertNextValue(2);

  // Add the color array to the graph
  graph->GetVertexData()->AddArray(vertexColors);

  // Visualize
  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView =
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView->AddRepresentationFromInput(graph);
  graphLayoutView->SetLayoutStrategyToPassThrough();
  graphLayoutView->SetVertexColorArrayName("Color");
  graphLayoutView->ColorVerticesOn();

  vtkSmartPointer<vtkViewTheme> theme =
    vtkSmartPointer<vtkViewTheme>::New();
  theme->SetPointLookupTable(lookupTable);

  graphLayoutView->ApplyViewTheme(theme);
  graphLayoutView->ResetCamera();
  graphLayoutView->GetInteractor()->Initialize();
  graphLayoutView->GetRenderer()->GetActiveCamera()->Zoom(0.8);
  graphLayoutView->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
