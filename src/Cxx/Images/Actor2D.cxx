#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkActor2D.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkProperty2D.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(10,10,0);
  points->InsertNextPoint(100,100,0);
  points->InsertNextPoint(200,200,0);

  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);

  vtkSmartPointer<vtkVertexGlyphFilter> glyphFilter =
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
  glyphFilter->SetInputData(polydata);
  glyphFilter->Update();

  vtkSmartPointer<vtkPolyDataMapper2D> mapper =
    vtkSmartPointer<vtkPolyDataMapper2D>::New();
  mapper->SetInputConnection(glyphFilter->GetOutputPort());
  mapper->Update();

  vtkSmartPointer<vtkActor2D> actor = 
    vtkSmartPointer<vtkActor2D>::New();
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
  renderWindow->SetSize(300,300);
  actor->GetProperty()->SetColor(0,1,0);
  actor->GetProperty()->SetPointSize(3);
  
  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
