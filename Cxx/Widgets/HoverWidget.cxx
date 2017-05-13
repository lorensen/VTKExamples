#include <vtkActor.h>
#include <vtkCommand.h>
#include <vtkHoverWidget.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

class vtkHoverCallback : public vtkCommand
{
  public:
    static vtkHoverCallback *New()
    {
      return new vtkHoverCallback;
    }

    vtkHoverCallback() {}

    virtual void Execute(vtkObject*, unsigned long event, void *vtkNotUsed(calldata))
    {
      switch (event)
      {
        case vtkCommand::TimerEvent:
          std::cout << "TimerEvent -> the mouse stopped moving and the widget hovered" << std::endl;
          break;
        case vtkCommand::EndInteractionEvent:
          std::cout << "EndInteractionEvent -> the mouse started to move" << std::endl;
          break;
      }
    }
};

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  // Create a mapper and actor
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
  renderer->AddActor(actor);

  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Create the widget
  vtkSmartPointer<vtkHoverWidget> hoverWidget =
    vtkSmartPointer<vtkHoverWidget>::New();
  hoverWidget->SetInteractor(renderWindowInteractor);
  hoverWidget->SetTimerDuration(1000);

  // Create a callback to listen to the widget's two VTK events
  vtkSmartPointer<vtkHoverCallback> hoverCallback =
    vtkSmartPointer<vtkHoverCallback>::New();
  hoverWidget->AddObserver(vtkCommand::TimerEvent,hoverCallback);
  hoverWidget->AddObserver(vtkCommand::EndInteractionEvent,hoverCallback);

  renderWindow->Render();

  renderWindowInteractor->Initialize();
  renderWindow->Render();
  hoverWidget->On();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
