[VTKExamples](/index/)/[Cxx](/Cxx)/Interaction/KeypressObserver

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Interaction/TestKeypressObserver.png?raw=true" width="256" />

**KeypressObserver.cxx**
```c++
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkCallbackCommand.h>
#include <vtkCommand.h>

void KeypressCallbackFunction (
  vtkObject* caller,
  long unsigned int eventId,
  void* clientData,
  void* callData );

int main(int, char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource = 
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(5.0);
  sphereSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());

  // Create an actor
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  
  vtkSmartPointer<vtkCallbackCommand> keypressCallback = 
    vtkSmartPointer<vtkCallbackCommand>::New();
  keypressCallback->SetCallback ( KeypressCallbackFunction );
  renderWindowInteractor->AddObserver ( vtkCommand::KeyPressEvent, keypressCallback );
  
  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); // Background color white
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

void KeypressCallbackFunction ( vtkObject* caller, long unsigned int vtkNotUsed(eventId), void* vtkNotUsed(clientData), void* vtkNotUsed(callData) )
{
  std::cout << "Keypress callback" << std::endl;
  
  vtkRenderWindowInteractor *iren = 
    static_cast<vtkRenderWindowInteractor*>(caller);

  std::cout << "Pressed: " << iren->GetKeySym() << std::endl;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(KeypressObserver)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(KeypressObserver MACOSX_BUNDLE KeypressObserver.cxx)
 
target_link_libraries(KeypressObserver ${VTK_LIBRARIES})
```

**Download and Build KeypressObserver**

Click [here to download KeypressObserver](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/KeypressObserver.tar) and its *CMakeLists.txt* file.
Once the *tarball KeypressObserver.tar* has been downloaded and extracted,
```
cd KeypressObserver/build 
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
./KeypressObserver
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

