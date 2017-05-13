[VTKExamples](Home)/[Cxx](Cxx)/Interaction/InteractorStyleUser

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Interaction/TestInteractorStyleUser.png" width="256" />

### Description
This style is designed to NOT provide any default functionality. You must specify how to handle every event that you want handled.

**InteractorStyleUser.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkCallbackCommand.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkInteractorStyleUser.h>

static void ClickCallbackFunction ( vtkObject* caller,
                                    long unsigned int eventId,
                                    void* clientData,
                                    void* callData );

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  
  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); // Background color white

  renderWindow->Render();

  vtkSmartPointer<vtkCallbackCommand> clickCallback = 
    vtkSmartPointer<vtkCallbackCommand>::New();
  clickCallback->SetCallback(ClickCallbackFunction);

  renderWindowInteractor->AddObserver ( vtkCommand::LeftButtonPressEvent, clickCallback );
  
  vtkSmartPointer<vtkInteractorStyleUser> style = 
    vtkSmartPointer<vtkInteractorStyleUser>::New();
  renderWindowInteractor->SetInteractorStyle(style);
  
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}


void ClickCallbackFunction (vtkObject *,
                            long unsigned int,
                            void *,
                            void *)
{
  std::cout << "Click callback" << std::endl;

  // We can get the calling object like this:
  // vtkRenderWindowInteractor *iren = 
  //  static_cast<vtkRenderWindowInteractor*>(caller);
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(InteractorStyleUser)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(InteractorStyleUser MACOSX_BUNDLE InteractorStyleUser.cxx)
 
target_link_libraries(InteractorStyleUser ${VTK_LIBRARIES})
```

**Download and Build InteractorStyleUser**

Click [here to download InteractorStyleUser](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/InteractorStyleUser.tar) and its *CMakeLists.txt* file.
Once the *tarball InteractorStyleUser.tar* has been downloaded and extracted,
```
cd InteractorStyleUser/build 
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
./InteractorStyleUser
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

