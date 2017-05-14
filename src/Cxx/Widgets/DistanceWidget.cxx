#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkDistanceWidget.h>
#include <vtkDistanceRepresentation.h>

int main(int, char *[])
{
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

  vtkSmartPointer<vtkDistanceWidget> distanceWidget =
    vtkSmartPointer<vtkDistanceWidget>::New();
  distanceWidget->SetInteractor(renderWindowInteractor);
  distanceWidget->CreateDefaultRepresentation();
  static_cast<vtkDistanceRepresentation *>(distanceWidget->GetRepresentation())
    ->SetLabelFormat("%-#6.3g mm");
  
  // Render an image (lights and cameras are created automatically)
  renderWindow->Render();
  
  renderWindowInteractor->Initialize();
  renderWindow->Render();
  distanceWidget->On();
  
  // Begin mouse interaction
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
