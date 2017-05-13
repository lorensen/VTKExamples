[VTKExamples](Home)/[Cxx](Cxx)/Interaction/CallData

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Interaction/TestCallData.png" width="256" />

### Description
This example demonstrates the use of 'calldata' in a vtkCallbackCommand. Here, we create a custom VTK filter to invoke an event to which we attach a value (the 'calldata'). We use a timer to modify and update the filter so that the event is triggered repeatedly, demonstrating the pass-via-calldata.

**CallData.cxx**
```c++
#include "vtkObjectFactory.h"
#include "vtkCommand.h"
#include "vtkCallbackCommand.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDataObject.h"
#include "vtkSmartPointer.h"
#include "vtkAppendPolyData.h"
#include "vtkSphereSource.h"
#include "vtkPolyDataAlgorithm.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"

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
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CallData)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CallData MACOSX_BUNDLE CallData.cxx)
 
target_link_libraries(CallData ${VTK_LIBRARIES})
```

**Download and Build CallData**

Click [here to download CallData](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CallData.tar) and its *CMakeLists.txt* file.
Once the *tarball CallData.tar* has been downloaded and extracted,
```
cd CallData/build 
```
If VTK is installed:
```
cmake ..
```
If VTK is not installed but compiled on your system, you will need to specify the path to your VTK build:
```
cmake -DVTK_DIR:PATH=/home/me/vtk_build ..
```
Build the project:
```
make
```
and run it:
```
./CallData
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

