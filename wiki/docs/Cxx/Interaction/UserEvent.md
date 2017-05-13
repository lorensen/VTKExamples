[VTKExamples](Home)/[Cxx](Cxx)/Interaction/UserEvent

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Interaction/TestUserEvent.png" width="256" />

**UserEvent.cxx**
```c++
#include <vtkSphereSource.h>
#include <vtkCallbackCommand.h>
#include <vtkCommand.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

#include "vtkTestFilter.h"

static void CallbackFunction(vtkObject* caller,
                long unsigned int eventId,
                void* clientData,
                void* callData );

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

  vtkSmartPointer<vtkTestFilter> filter =
    vtkSmartPointer<vtkTestFilter>::New();

  vtkSmartPointer<vtkCallbackCommand> callback =
    vtkSmartPointer<vtkCallbackCommand>::New();
  callback->SetCallback(CallbackFunction );
  filter->AddObserver(filter->RefreshEvent, callback);

  filter->Update();
  
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

void CallbackFunction(vtkObject* caller,
                long unsigned int eventId,
                void* clientData, void* callData )
{
  std::cout << "CallbackFunction called." << std::endl;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(UserEvent)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(UserEvent MACOSX_BUNDLE UserEvent.cxx)
 
target_link_libraries(UserEvent ${VTK_LIBRARIES})
```

**Download and Build UserEvent**

Click [here to download UserEvent](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/UserEvent.tar) and its *CMakeLists.txt* file.
Once the *tarball UserEvent.tar* has been downloaded and extracted,
```
cd UserEvent/build 
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
./UserEvent
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

