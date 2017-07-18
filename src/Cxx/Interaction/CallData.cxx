#include <vtkObjectFactory.h>
#include <vtkCommand.h>
#include <vtkCallbackCommand.h>
#include <vtkStreamingDemandDrivenPipeline.h>
#include <vtkInformationVector.h>
#include <vtkInformation.h>
#include <vtkDataObject.h>
#include <vtkSmartPointer.h>
#include <vtkAppendPolyData.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataAlgorithm.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

class vtkMyTestFilter : public vtkPolyDataAlgorithm
{
public:
  vtkTypeMacro(vtkMyTestFilter,vtkPolyDataAlgorithm);
  static vtkMyTestFilter *New();

  int RefreshEvent;

protected:
  vtkMyTestFilter()
  {
    this->SetNumberOfInputPorts(0);

    this->RefreshEvent = vtkCommand::UserEvent + 1;

    this->Counter = 0;
  }

  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *)
  {
      this->InvokeEvent(this->RefreshEvent, &this->Counter);
      this->Counter++;
      return 1;
  }

private:
  vtkMyTestFilter(const vtkMyTestFilter&);  // Not implemented.
  void operator=(const vtkMyTestFilter&);  // Not implemented.

  unsigned int Counter;
};

vtkStandardNewMacro(vtkMyTestFilter);

static void CallbackFunction(vtkObject* caller,
                long unsigned int eventId,
                void* clientData,
                void* callData );

class vtkTimerCallback : public vtkCommand
{
  public:
    static vtkTimerCallback *New()
    {
      vtkTimerCallback *cb = new vtkTimerCallback;

      return cb;
    }

    virtual void Execute(vtkObject *vtkNotUsed(caller),
                         unsigned long vtkNotUsed(eventId),
                         void *vtkNotUsed(callData))
    {
        TestFilter->Modified();
        TestFilter->Update();
    }

    vtkMyTestFilter* TestFilter;

};

int main(int, char *[])
{
  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkMyTestFilter> testFilter =
    vtkSmartPointer<vtkMyTestFilter>::New();

  vtkSmartPointer<vtkCallbackCommand> callback =
    vtkSmartPointer<vtkCallbackCommand>::New();
  callback->SetCallback(CallbackFunction );
  testFilter->AddObserver(testFilter->RefreshEvent, callback);
  testFilter->Update();

  renderWindow->Render();
  renderWindowInteractor->Initialize();

  // Sign up to receive TimerEvent
  vtkSmartPointer<vtkTimerCallback> timerCallback =
    vtkSmartPointer<vtkTimerCallback>::New();
  timerCallback->TestFilter = testFilter;

  renderWindowInteractor->AddObserver(vtkCommand::TimerEvent, timerCallback);

  renderWindowInteractor->CreateRepeatingTimer(100);

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

void CallbackFunction(vtkObject* vtkNotUsed(caller),
                      long unsigned int vtkNotUsed(eventId),
                      void* vtkNotUsed(clientData),
                      void* callData )
{
  unsigned int* callDataCasted = reinterpret_cast<unsigned int*>(callData);
  std::cout << *callDataCasted << std::endl;
}
