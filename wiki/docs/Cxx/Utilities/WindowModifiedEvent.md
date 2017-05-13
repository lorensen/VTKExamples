[VTKExamples](Home)/[Cxx](Cxx)/Utilities/WindowModifiedEvent

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Utilities/TestWindowModifiedEvent.png" width="256" />

### Description
This example limits the horizontal window size to 400.

**WindowModifiedEvent.cxx**
```c++
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCallbackCommand.h>

void WindowModifiedCallback( vtkObject*
                      caller, long unsigned int vtkNotUsed(eventId), void* vtkNotUsed(clientData), void* vtkNotUsed(callData) )
{
  std::cout << "Window modified" << std::endl;
  std::cout << caller->GetClassName() << std::endl;

  vtkRenderWindow* window = static_cast<vtkRenderWindow*>(caller);
  int* windowSize = window->GetSize();
  std::cout << "Size: " << windowSize[0] << " " << windowSize[1] << std::endl;

  if(windowSize[0] > 400)
  {
    window->SetSize(400, windowSize[1]);
    window->Render();
    window->Modified();
    window->Render();

  }
}

int main(int, char *[])
{
  // Create a sphere
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

  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actor to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); // Background color white

  vtkSmartPointer<vtkCallbackCommand> m_pModifiedCallback =
    vtkSmartPointer<vtkCallbackCommand>::New();
  m_pModifiedCallback->SetCallback (WindowModifiedCallback);
  //m_pModifiedCallback->SetClientData(this);

  renderWindow->AddObserver(vtkCommand::ModifiedEvent,m_pModifiedCallback);

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(WindowModifiedEvent)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(WindowModifiedEvent MACOSX_BUNDLE WindowModifiedEvent.cxx)
 
target_link_libraries(WindowModifiedEvent ${VTK_LIBRARIES})
```

**Download and Build WindowModifiedEvent**

Click [here to download WindowModifiedEvent](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/WindowModifiedEvent.tar) and its *CMakeLists.txt* file.
Once the *tarball WindowModifiedEvent.tar* has been downloaded and extracted,
```
cd WindowModifiedEvent/build 
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
./WindowModifiedEvent
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

