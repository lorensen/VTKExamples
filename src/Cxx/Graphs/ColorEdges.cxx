#include <vtkSmartPointer.h>
#include <vtkDataSetAttributes.h>
#include <vtkGraphLayoutView.h>
#include <vtkIntArray.h>
#include <vtkLookupTable.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkViewTheme.h>
 
int main(int, char *[])
{
  vtkSmartPointer<vtkMutableDirectedGraph> graph = 
    vtkSmartPointer<vtkMutableDirectedGraph>::New();
 
  // Create a graph
  vtkIdType v1 = graph->AddVertex();
  vtkIdType v2 = graph->AddVertex();
  vtkIdType v3 = graph->AddVertex();
  graph->AddEdge(v1,v2);
  graph->AddEdge(v2,v3);
  
  // Create the color array
  vtkSmartPointer<vtkIntArray> edgeColors = 
    vtkSmartPointer<vtkIntArray>::New();
  edgeColors->SetNumberOfComponents(1);
  edgeColors->SetName("Color");
 
  vtkSmartPointer<vtkLookupTable> lookupTable = 
    vtkSmartPointer<vtkLookupTable>::New();
  lookupTable->SetNumberOfTableValues(2);
  lookupTable->SetTableValue(0, 1.0, 0.0, 0.0); // red
  lookupTable->SetTableValue(1, 0.0, 1.0, 0.0); // green
  lookupTable->Build();
 
  edgeColors->InsertNextValue(0);
  edgeColors->InsertNextValue(1);
     
  // Add the color array to the graph
  graph->GetEdgeData()->AddArray(edgeColors);
 
  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView = 
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView->AddRepresentationFromInput(graph);
  graphLayoutView->SetLayoutStrategyToTree();
 
  graphLayoutView->SetEdgeColorArrayName("Color");
  graphLayoutView->ColorEdgesOn();
 
  vtkSmartPointer<vtkViewTheme> theme = 
    vtkSmartPointer<vtkViewTheme>::New();
  theme->SetCellLookupTable(lookupTable);
 
  graphLayoutView->ApplyViewTheme(theme);
  graphLayoutView->ResetCamera();
  graphLayoutView->GetInteractor()->Initialize();
  graphLayoutView->GetInteractor()->Start();
 
  return EXIT_SUCCESS;
}
