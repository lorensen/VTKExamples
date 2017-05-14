#include <vtkSmartPointer.h>
#include <vtkWidgetCallbackMapper.h>
#include <vtkCommand.h>
#include <vtkWidgetEvent.h>
#include <vtkObjectFactory.h>
#include <vtkActor.h>
#include <vtkBorderRepresentation.h>
#include <vtkBorderWidget.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>

class vtkCustomBorderWidget : public vtkBorderWidget
{
public:
  static vtkCustomBorderWidget *New();
  vtkTypeMacro(vtkCustomBorderWidget, vtkBorderWidget);

  static void EndSelectAction(vtkAbstractWidget *w);
  
  vtkCustomBorderWidget();

};

vtkStandardNewMacro(vtkCustomBorderWidget);

vtkCustomBorderWidget::vtkCustomBorderWidget()
{
  this->CallbackMapper->SetCallbackMethod(vtkCommand::MiddleButtonReleaseEvent,
                                        vtkWidgetEvent::EndSelect,
                                        this, vtkCustomBorderWidget::EndSelectAction);
}

void vtkCustomBorderWidget::EndSelectAction(vtkAbstractWidget *w)
{
  vtkBorderWidget *borderWidget =
    vtkBorderWidget::SafeDownCast(w);

  // Get the actual box coordinates/planes
  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();

  // Get the bottom left corner
  double* lowerLeft;
  lowerLeft = static_cast<vtkBorderRepresentation*>(borderWidget->GetRepresentation())->GetPosition();
  std::cout << "Lower left: " << lowerLeft[0] << " "
            << lowerLeft[1] << std::endl;

  double* upperRight;
  upperRight = static_cast<vtkBorderRepresentation*>(borderWidget->GetRepresentation())->GetPosition2();
  std::cout << "Upper right: " << upperRight[0] << " "
            << upperRight[1] << std::endl;

  vtkBorderWidget::EndSelectAction(w);
}

int main(int, char *[])
{
  // Sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetRadius(4.0);
  sphereSource->Update();
  
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

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

  vtkSmartPointer<vtkCustomBorderWidget> borderWidget =
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
