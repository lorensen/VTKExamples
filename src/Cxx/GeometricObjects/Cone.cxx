#include <vtkSmartPointer.h>
#include <vtkConeSource.h>

#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkNamedColors.h>

int main(int, char *[])
{
  //Create a cone
  auto coneSource =
    vtkSmartPointer<vtkConeSource>::New();
  coneSource->Update();

  //Create a mapper and actor
  auto mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(coneSource->GetOutputPort());

  auto colors =
    vtkSmartPointer<vtkNamedColors>::New();

  auto actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetDiffuseColor(colors->GetColor3d("bisque").GetData());

  //Create a renderer, render window, and interactor
  auto renderer =
    vtkSmartPointer<vtkRenderer>::New();
  auto renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);

  auto renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  //Add the actors to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("Salmon").GetData());

  //Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
