#include <vtkSmartPointer.h>
#include <vtkCursor2D.h>

#include <vtkSphereSource.h>
#include <vtkProperty.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
 
#include <vtkNamedColors.h>

int main(int, char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(5.0);
  sphereSource->Update();

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());
 
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

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();
  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
 
  vtkSmartPointer<vtkCursor2D> cursor = 
    vtkSmartPointer<vtkCursor2D>::New();
  cursor->SetModelBounds(-10,10,-10,10,0,0);
  cursor->AllOn();
  cursor->SetFocalPoint (5.0, 5.0, 0.0);
  cursor->OutlineOn();
  cursor->Update();

  vtkSmartPointer<vtkPolyDataMapper> cursorMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cursorMapper->SetInputConnection(cursor->GetOutputPort());
  vtkSmartPointer<vtkActor> cursorActor = 
    vtkSmartPointer<vtkActor>::New();
  cursorActor->GetProperty()->SetColor(1,0,0);
  cursorActor->SetMapper(cursorMapper);
  renderer->AddActor(cursorActor);
   
  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
