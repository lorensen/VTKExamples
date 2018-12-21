#include <vtkCylinderSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkOpenVRRenderWindow.h>
#include <vtkOpenVRRenderer.h>
#include <vtkOpenVRRenderWindowInteractor.h>
#include <vtkNamedColors.h>

int main(int, char *argv[])
{
  // Create a sphere
  vtkSmartPointer<vtkCylinderSource> cylinderSource =
    vtkSmartPointer<vtkCylinderSource>::New();
  cylinderSource->SetCenter(0.0, 0.0, 0.0);
  cylinderSource->SetRadius(5.0);
  cylinderSource->SetHeight(7.0);
  cylinderSource->SetResolution(100);

  // Create a mapper and actor
  vtkSmartPointer<vtkNamedColors> colors = 
    vtkSmartPointer<vtkNamedColors>::New();
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(cylinderSource->GetOutputPort());
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkOpenVRRenderer> renderer =
    vtkSmartPointer<vtkOpenVRRenderer>::New();
  vtkSmartPointer<vtkOpenVRRenderWindow> renderWindow =
    vtkSmartPointer<vtkOpenVRRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkOpenVRRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkOpenVRRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actor to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("ForestGreen").GetData());
  // Render and interact
  renderWindow->SetWindowName(argv[0]);
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
