#include <vtkActor.h>
#include <vtkCommand.h>
#include <vtkNamedColors.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

class vtkTimerCallback2 : public vtkCommand
{
public:
  vtkTimerCallback2() = default;

  static vtkTimerCallback2* New()
  {
    vtkTimerCallback2* cb = new vtkTimerCallback2;
    cb->TimerCount = 0;
    return cb;
  }

  virtual void Execute(vtkObject* caller, unsigned long eventId,
                       void* vtkNotUsed(callData))
  {
    if (vtkCommand::TimerEvent == eventId)
    {
      ++this->TimerCount;
    }
    std::cout << this->TimerCount << std::endl;
    actor->SetPosition(this->TimerCount, this->TimerCount, 0);
    if (this->TimerCount < this->maxCount)
    {

      vtkRenderWindowInteractor* iren =
          dynamic_cast<vtkRenderWindowInteractor*>(caller);
      iren->GetRenderWindow()->Render();
    }
    else
    {
      vtkRenderWindowInteractor* iren =
          dynamic_cast<vtkRenderWindowInteractor*>(caller);
      if (this->timerId > -1)
      {
        iren->DestroyTimer(this->timerId);
      }
    }
  }

private:
  int TimerCount = 0;

public:
  vtkActor* actor = nullptr;
  int timerId = 0;
  int maxCount = -1;
};

int main(int, char*[])
{
  auto colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Create a sphere
  auto sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(5.0);
  sphereSource->Update();

  // Create a mapper and actor
  auto mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());
  auto actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(colors->GetColor3d("Salmon").GetData());

  // Create a renderer, render window, and interactor
  auto renderer =
    vtkSmartPointer<vtkRenderer>::New();
  auto renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  auto renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actor to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("AliceBlue").GetData());

  // Render and interact
  renderWindow->Render();

  // Initialize must be called prior to creating timer events.
  renderWindowInteractor->Initialize();

  // Sign up to receive TimerEvent
  auto cb = vtkSmartPointer<vtkTimerCallback2>::New();
  cb->actor = actor;
  renderWindowInteractor->AddObserver(vtkCommand::TimerEvent, cb);

  int timerId = renderWindowInteractor->CreateRepeatingTimer(100);
  std::cout << "timerId: " << timerId << std::endl;
  // Destroy the timer when maxCount is reached.
  cb->maxCount = 7;
  cb->timerId = timerId;
  // Start the interaction and timer
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
