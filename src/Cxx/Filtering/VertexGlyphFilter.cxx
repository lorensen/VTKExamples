#include <vtkActor.h>
#include <vtkNamedColors.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkVertexGlyphFilter.h>

int main(int, char*[])
{
  auto namedColors = vtkSmartPointer<vtkNamedColors>::New();
  namedColors->SetColor("Bkg", 0.3, 0.6, 0.3);

  auto points = vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0, 0, 0);
  points->InsertNextPoint(1, 1, 1);
  points->InsertNextPoint(2, 2, 2);

  auto polydata = vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);

  auto vertexGlyphFilter = vtkSmartPointer<vtkVertexGlyphFilter>::New();
  vertexGlyphFilter->AddInputData(polydata);
  vertexGlyphFilter->Update();

  // Create a mapper and actor
  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(vertexGlyphFilter->GetOutputPort());

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetPointSize(3);

  // Create a renderer, render window, and interactor
  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  auto renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actor to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(
      namedColors->GetColor3d("Bkg").GetData()); // Background color green

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
