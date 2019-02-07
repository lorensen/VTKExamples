#include <vtkSmartPointer.h>
#include <vtkCommand.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

class vtkTimerCallback : public vtkCommand
{
  public:
    static vtkTimerCallback *New()
    {
      vtkTimerCallback *cb = new vtkTimerCallback;
      cb->TimerCount = 0;
      return cb;
    }

    virtual void Execute(vtkObject *vtkNotUsed(caller), unsigned long eventId,
                         void *vtkNotUsed(callData))
    {
      if (vtkCommand::TimerEvent == eventId)
      {
        ++this->TimerCount;
      }
        cout << this->TimerCount << endl;
    }

  private:
    int TimerCount;

};

int main(int, char *[])
{
  // Setup renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Initialize must be called prior to creating timer events.
  renderWindow->Render();
  interactor->Initialize();

  // Sign up to receive TimerEvent
  vtkSmartPointer<vtkTimerCallback> cb =
    vtkSmartPointer<vtkTimerCallback>::New();
  interactor->AddObserver(vtkCommand::TimerEvent, cb);

  int timerId = interactor->CreateRepeatingTimer(100);
  std::cout << "timerId: " << timerId << std::endl;

  // Start the interaction and timer
  interactor->Start();

  return EXIT_SUCCESS;
}
