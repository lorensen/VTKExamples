#include <vtkPointHandleRepresentation2D.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty2D.h> // For setting the color in the handles
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSeedRepresentation.h>
#include <vtkSeedWidget.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

int main(int vtkNotUsed(argc), char* vtkNotUsed(argv)[])
{
  auto sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  // Create a mapper and actor
  auto mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());
  auto actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  auto renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);

  auto window =
    vtkSmartPointer<vtkRenderWindow>::New();
  window->AddRenderer(renderer);

  auto interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(window);

  // Create the representation for the seed widget and for its handles
  auto handleRep =
    vtkSmartPointer<vtkPointHandleRepresentation2D>::New();
  handleRep->GetProperty()->SetColor(1, 1, 0); // Make the handles yellow
  auto widgetRep =
    vtkSmartPointer<vtkSeedRepresentation>::New();
  widgetRep->SetHandleRepresentation(handleRep);

  // Create the seed widget
  auto seedWidget =
    vtkSmartPointer<vtkSeedWidget>::New();
  seedWidget->SetInteractor(interactor);
  seedWidget->SetRepresentation(widgetRep);

  seedWidget->On();
  window->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
