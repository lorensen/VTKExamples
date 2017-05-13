#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballActor.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkConeSource> coneSource0 =
    vtkSmartPointer<vtkConeSource>::New();
  coneSource0->Update();
  
  vtkSmartPointer<vtkConeSource> coneSource1 =
    vtkSmartPointer<vtkConeSource>::New();
  coneSource1->SetCenter(5,0,0);
  coneSource1->Update();

  // Create mappers and actors
  vtkSmartPointer<vtkPolyDataMapper> coneMapper0 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  coneMapper0->SetInputConnection(coneSource0->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> coneMapper1 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  coneMapper1->SetInputConnection(coneSource1->GetOutputPort());

  // Create actors
  vtkSmartPointer<vtkActor> coneActor0 =
    vtkSmartPointer<vtkActor>::New();
  coneActor0->SetMapper(coneMapper0);

  vtkSmartPointer<vtkActor> coneActor1 =
    vtkSmartPointer<vtkActor>::New();
  coneActor1->SetMapper(coneMapper1);
  coneActor1->PickableOff();
  
  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actors to the scene
  renderer->AddActor(coneActor0);
  renderer->AddActor(coneActor1);
  renderer->SetBackground(0.5,0.5,0.5);

  renderer->ResetCamera();
  renderWindow->Render();

  vtkSmartPointer<vtkInteractorStyleTrackballActor> style =
    vtkSmartPointer<vtkInteractorStyleTrackballActor>::New();

  renderWindowInteractor->SetInteractorStyle( style );

  // Begin mouse interaction
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
