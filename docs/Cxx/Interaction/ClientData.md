[VTKExamples](/index/)/[Cxx](/Cxx)/Interaction/ClientData

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Interaction/TestClientData.png?raw=true" width="256" />

**ClientData.cxx**
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

static void KeypressCallbackFunction ( vtkObject* caller, long unsigned int eventId,
          void* clientData, void* callData );

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

  // Allow the observer to access the sphereSource
  keypressCallback->SetClientData(sphereSource);
  keypressCallback->SetCallback(KeypressCallbackFunction );
  renderWindowInteractor->AddObserver(vtkCommand::KeyPressEvent, keypressCallback);

  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); // Background color white
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

void KeypressCallbackFunction(vtkObject*, long unsigned int vtkNotUsed(eventId), void* clientData, void* vtkNotUsed(callData) )
{
  // Prove that we can access the sphere source
  vtkSphereSource* sphereSource =
    static_cast<vtkSphereSource*>(clientData);
  std::cout << "Radius is " << sphereSource->GetRadius() << std::endl;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ClientData)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ClientData MACOSX_BUNDLE ClientData.cxx)
 
target_link_libraries(ClientData ${VTK_LIBRARIES})
```

**Download and Build ClientData**

Click [here to download ClientData](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ClientData.tar) and its *CMakeLists.txt* file.
Once the *tarball ClientData.tar* has been downloaded and extracted,
```
cd ClientData/build 
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
./ClientData
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

