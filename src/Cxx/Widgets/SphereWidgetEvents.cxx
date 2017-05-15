#include <vtkCallbackCommand.h>
#include <vtkCommand.h>
#include <vtkObjectFactory.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereWidget.h>
#include <vtkSphereRepresentation.h>

class MySphereWidget : public vtkSphereWidget
{
 public:
  static MySphereWidget* New();
  vtkTypeMacro(MySphereWidget, vtkSphereWidget);

  // Handles the events
  static void ProcessEvents(vtkObject* object,
                            unsigned long event,
                            void* clientdata,
                            void* calldata);

protected:
  MySphereWidget();

  // Create a new callback command rather than using the one defined in
  // vtkSphereWidget. This prevents problems with unexpected behavior due
  // to the AbortFlag being manipulated.
  vtkSmartPointer<vtkCallbackCommand> MyEventCallbackCommand;

};


MySphereWidget::MySphereWidget()
{

  this->MyEventCallbackCommand = vtkSmartPointer<vtkCallbackCommand>::New();

  // Connect our own callback command to our own ProcessEvents function.
  // This way we do not have to deal with side effects of SphereWidget::ProcessEvents
  this->MyEventCallbackCommand->SetCallback( MySphereWidget::ProcessEvents );

  // Connect our callback function to a few events.
  this->AddObserver(vtkCommand::StartInteractionEvent,
                    this->MyEventCallbackCommand);

  this->AddObserver(vtkCommand::InteractionEvent,
                    this->MyEventCallbackCommand);

  this->AddObserver(vtkCommand::EndInteractionEvent,
                    this->MyEventCallbackCommand);

}

void MySphereWidget::ProcessEvents( vtkObject *vtkNotUsed(object),
                                    unsigned long event,
                                    void *vtkNotUsed(clientdata),
                                    void *vtkNotUsed(calldata) )
{
  switch(event)
  {
    case vtkCommand::StartInteractionEvent:
      std::cout << "StartInteractionEvent" << std::endl;
      break;
    case vtkCommand::EndInteractionEvent:
      std::cout << "EndInteractionEvent" << std::endl;
      break;
    case vtkCommand::InteractionEvent:
      std::cout << "InteractionEvent" << std::endl;
      break;
  }
}

vtkStandardNewMacro(MySphereWidget);

int main(int, char *[])
{
  // Create  a renderer and render window
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // Create an interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  vtkSmartPointer<MySphereWidget> sphereWidget =
    vtkSmartPointer<MySphereWidget>::New();
  sphereWidget->SetInteractor(renderWindowInteractor);
  sphereWidget->SetRepresentationToSurface();
  sphereWidget->HandleVisibilityOn();

  renderWindow->Render();
  renderWindowInteractor->Initialize();
  renderWindow->Render();
  sphereWidget->On();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
