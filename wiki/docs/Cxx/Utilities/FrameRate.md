[VTKExamples](/home/)/[Cxx](/Cxx)/Utilities/FrameRate

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Utilities/TestFrameRate.png?raw=true" width="256" />

**FrameRate.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkCallbackCommand.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMath.h>
#include <vtkRenderWindow.h>
#include <vtkTimerLog.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>

static void CallbackFunction ( vtkObject* caller, long unsigned int eventId,
          void* clientData, void* callData );

int main(int, char *[])
{
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();

  for(unsigned int i = 0; i < 10; i++)
  {
    // Create a sphere
    vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetCenter(i, 0, 0);

    // Create a mapper and actor
    vtkSmartPointer<vtkPolyDataMapper> mapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());

    vtkSmartPointer<vtkActor> actor =
      vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    renderer->AddActor(actor);
  }

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkCallbackCommand> callback =
    vtkSmartPointer<vtkCallbackCommand>::New();

  callback->SetCallback(CallbackFunction);
  renderer->AddObserver(vtkCommand::EndEvent, callback);

  renderer->SetBackground(.3, .6, .3); // Background color green

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  return EXIT_SUCCESS;
}

void CallbackFunction(vtkObject* caller, long unsigned int vtkNotUsed(eventId), void* vtkNotUsed(clientData), void* vtkNotUsed(callData) )
{
  vtkRenderer* renderer = static_cast<vtkRenderer*>(caller);

  double timeInSeconds = renderer->GetLastRenderTimeInSeconds();
  double fps = 1.0/timeInSeconds;
  std::cout << "FPS: " << fps << std::endl;

  std::cout << "Callback" << std::endl;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(FrameRate)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(FrameRate MACOSX_BUNDLE FrameRate.cxx)
 
target_link_libraries(FrameRate ${VTK_LIBRARIES})
```

**Download and Build FrameRate**

Click [here to download FrameRate](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/FrameRate.tar) and its *CMakeLists.txt* file.
Once the *tarball FrameRate.tar* has been downloaded and extracted,
```
cd FrameRate/build 
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
./FrameRate
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

