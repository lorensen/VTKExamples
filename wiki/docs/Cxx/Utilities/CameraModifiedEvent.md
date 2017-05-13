[VTKExamples](Home)/[Cxx](Cxx)/Utilities/CameraModifiedEvent

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Utilities/TestCameraModifiedEvent.png" width="256" />

**CameraModifiedEvent.cxx**
```c++
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCamera.h>
#include <vtkCallbackCommand.h>

static void CameraModifiedCallback(vtkObject* caller,
                                   long unsigned int vtkNotUsed(eventId),
                                   void* vtkNotUsed(clientData),
                                   void* vtkNotUsed(callData) )
{
  std::cout << caller->GetClassName() << " modified" << std::endl;
  
  vtkCamera* camera = static_cast<vtkCamera*>(caller);
  // print the interesting stuff
  std::cout << "\tPosition: "
            << camera->GetPosition()[0] << ", "
            << camera->GetPosition()[1] << ", "
            << camera->GetPosition()[2] << std::endl;
  std::cout << "\tFocal point: "
            << camera->GetFocalPoint()[0] << ", "
            << camera->GetFocalPoint()[1] << ", "
            << camera->GetFocalPoint()[2] << std::endl;
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
  renderer->SetBackground(.1, .3, .5);
  
  vtkSmartPointer<vtkCallbackCommand> modifiedCallback =
    vtkSmartPointer<vtkCallbackCommand>::New();
  modifiedCallback->SetCallback (CameraModifiedCallback);

  renderer->ResetCamera();
  renderer->GetActiveCamera()->AddObserver(vtkCommand::ModifiedEvent,modifiedCallback);
  
  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CameraModifiedEvent)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CameraModifiedEvent MACOSX_BUNDLE CameraModifiedEvent.cxx)
 
target_link_libraries(CameraModifiedEvent ${VTK_LIBRARIES})
```

**Download and Build CameraModifiedEvent**

Click [here to download CameraModifiedEvent](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CameraModifiedEvent.tar) and its *CMakeLists.txt* file.
Once the *tarball CameraModifiedEvent.tar* has been downloaded and extracted,
```
cd CameraModifiedEvent/build 
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
./CameraModifiedEvent
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

