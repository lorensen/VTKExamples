#include <vtkSmartPointer.h>
#include <vtkGraphToPolyData.h>
#include <vtkDataSetAttributes.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkGraphLayoutView.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main(int, char *[])
{
  // Create the first graph
  vtkSmartPointer<vtkMutableUndirectedGraph> g0 = 
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();
  {
  vtkIdType v1 = g0->AddVertex();
  vtkIdType v2 = g0->AddVertex();
  vtkIdType v3 = g0->AddVertex();
 
  g0->AddEdge(v1, v2);
  g0->AddEdge(v2, v3);
  g0->AddEdge(v1, v3);
  
  // Create points
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0.0, 0.0, 0.0);
  points->InsertNextPoint(1.0, 0.0, 0.0);
  points->InsertNextPoint(0.0, 1.0, 0.0);
    
  // Add the coordinates of the points to the graph
  g0->SetPoints(points);
  }
  
  // Create the second graph
  vtkSmartPointer<vtkMutableUndirectedGraph> g1 = 
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();
 
  vtkIdType v1 = g1->AddVertex();
  vtkIdType v2 = g1->AddVertex();
   
  g1->AddEdge(v1, v2);
   
  // Create points
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0.0, 0.0, 0.0);
  points->InsertNextPoint(1.0, 0.0, 0.0);
      
  // Add the coordinates of the points to the graph
  g1->SetPoints(points);
  
  // There will be one render window
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
 
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  
  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};
   
  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView0 = 
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView0->SetRenderWindow(renderWindow);
  graphLayoutView0->SetInteractor(renderWindowInteractor);
  graphLayoutView0->GetRenderer()->SetViewport(leftViewport);
  graphLayoutView0->AddRepresentationFromInput(g0);
  graphLayoutView0->ResetCamera();
  graphLayoutView0->Render();
  
  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView1 = 
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView1->SetRenderWindow(renderWindow);
  graphLayoutView1->SetInteractor(renderWindowInteractor);
  graphLayoutView1->GetRenderer()->SetViewport(rightViewport);
  graphLayoutView1->AddRepresentationFromInput(g1);
  graphLayoutView1->ResetCamera();
  graphLayoutView1->Render();
    
  //graphLayoutView0->GetInteractor()->Start();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
