#include <vtkSmartPointer.h>
#include <vtkTree.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkGraphLayoutView.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkGraphToPolyData.h>
#include <vtkProperty.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkDijkstraGraphGeodesicPath.h>

/*
   O v0
  /|\
5/ |5\5
v1-v2-v3 
  1  1
  
  Shortest path between v0 and v2 should be 5
*/

int main ( int argc, char *argv[] )
{
  vtkSmartPointer<vtkMutableDirectedGraph> graph = 
      vtkSmartPointer<vtkMutableDirectedGraph>::New();
  vtkIdType v0 = graph->AddVertex();
  vtkIdType v1 = graph->AddVertex();
  vtkIdType v2 = graph->AddVertex();
  vtkIdType v3 = graph->AddVertex();

  graph->AddEdge ( v0, v1 );
  graph->AddEdge ( v0, v2 );
  graph->AddEdge ( v0, v3 );
  graph->AddEdge ( v1, v2 );
  graph->AddEdge ( v2, v3 );
  
  // Associate physical locations with the vertices
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0.0, 0.0, 0.0);
  points->InsertNextPoint(-1.0, -5.0, 0.0);
  points->InsertNextPoint(0.0, -5.0, 0.0);
  points->InsertNextPoint(1.0, -5.0, 0.0);

  graph->SetPoints(points);

  // Convert the graph to a polydata
  vtkSmartPointer<vtkGraphToPolyData> graphToPolyData = 
    vtkSmartPointer<vtkGraphToPolyData>::New();
  graphToPolyData->SetInput(graph);
  graphToPolyData->Update();
  
  vtkSmartPointer<vtkDijkstraGraphGeodesicPath> dijkstra = 
    vtkSmartPointer<vtkDijkstraGraphGeodesicPath>::New();
  dijkstra->SetInputConnection(graphToPolyData->GetOutputPort());
  dijkstra->SetStartVertex(0);
  dijkstra->SetEndVertex(2);
  dijkstra->Update();
  
  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> pathMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  pathMapper->SetInputConnection(dijkstra->GetOutputPort());
 
  vtkSmartPointer<vtkActor> pathActor = 
    vtkSmartPointer<vtkActor>::New();
  pathActor->SetMapper(pathMapper);
  pathActor->GetProperty()->SetColor(1,0,0); // Red
  pathActor->GetProperty()->SetLineWidth(4);
    
  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(graphToPolyData->GetOutputPort());
 
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
 
  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  // Add the actor to the scene
  renderer->AddActor(actor);
  renderer->AddActor(pathActor);
  renderer->SetBackground(.3, .6, .3); // Background color green
 
  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
