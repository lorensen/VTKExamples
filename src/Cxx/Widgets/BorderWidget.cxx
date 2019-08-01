#include <vtkActor.h>
#include <vtkBorderRepresentation.h>
#include <vtkBorderWidget.h>
#include <vtkCommand.h>
#include <vtkObjectFactory.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkWidgetCallbackMapper.h>
#include <vtkWidgetEvent.h>

class vtkCustomBorderWidget : public vtkBorderWidget
{
public:
  static vtkCustomBorderWidget* New();
  vtkTypeMacro(vtkCustomBorderWidget, vtkBorderWidget);

  static void EndSelectAction(vtkAbstractWidget* w);

  vtkCustomBorderWidget();
};

vtkStandardNewMacro(vtkCustomBorderWidget);

vtkCustomBorderWidget::vtkCustomBorderWidget()
{
  this->CallbackMapper->SetCallbackMethod(
      vtkCommand::MiddleButtonReleaseEvent, vtkWidgetEvent::EndSelect, this,
      vtkCustomBorderWidget::EndSelectAction);
}

void vtkCustomBorderWidget::EndSelectAction(vtkAbstractWidget* w)
{
  vtkBorderWidget* borderWidget = dynamic_cast<vtkBorderWidget*>(w);

  // Get the actual box coordinates/planes
  // vtkSmartPointer<vtkPolyData> polydata =
  //  vtkSmartPointer<vtkPolyData>::New();

  // Get the bottom left corner
  auto lowerLeft =
      static_cast<vtkBorderRepresentation*>(borderWidget->GetRepresentation())
          ->GetPosition();
  std::cout << "Lower left: " << lowerLeft[0] << " " << lowerLeft[1]
            << std::endl;

  auto upperRight =
      static_cast<vtkBorderRepresentation*>(borderWidget->GetRepresentation())
          ->GetPosition2();
  std::cout << "Upper right: " << upperRight[0] << " " << upperRight[1]
            << std::endl;

  vtkBorderWidget::EndSelectAction(w);
}

int main(int, char*[])
{
  // Sphere
  auto sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetRadius(4.0);
  sphereSource->Update();

  auto mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());

  auto actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // A renderer and render window
  auto renderer =
    vtkSmartPointer<vtkRenderer>::New();
  auto renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // An interactor
  auto renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  auto borderWidget =
    vtkSmartPointer<vtkCustomBorderWidget>::New();
  borderWidget->SetInteractor(renderWindowInteractor);
  borderWidget->CreateDefaultRepresentation();
  borderWidget->SelectableOff();

  // Add the actors to the scene
  renderer->AddActor(actor);

  // Render an image (lights and cameras are created automatically)
  renderWindowInteractor->Initialize();
  renderWindow->Render();
  borderWidget->On();

  // Begin mouse interaction
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
