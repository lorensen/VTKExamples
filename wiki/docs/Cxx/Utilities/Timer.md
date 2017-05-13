[VTKExamples](Home)/[Cxx](Cxx)/Utilities/Timer

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Utilities/TestTimer.png" width="256" />

### Description
This example demonstrates how to use a timer with an interactor. It outputs a count every specified interval.

**Timer.cxx**
```c++
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
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Timer)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Timer MACOSX_BUNDLE Timer.cxx)
 
target_link_libraries(Timer ${VTK_LIBRARIES})
```

**Download and Build Timer**

Click [here to download Timer](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Timer.tar) and its *CMakeLists.txt* file.
Once the *tarball Timer.tar* has been downloaded and extracted,
```
cd Timer/build 
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
./Timer
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

