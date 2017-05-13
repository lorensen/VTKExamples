[VTKExamples](/home/)/[Cxx](/Cxx)/Interaction/PickableOff

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Interaction/TestPickableOff.png?raw=true" width="256" />

**PickableOff.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballActor.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkConeSource> coneSource0 =
    vtkSmartPointer<vtkConeSource>::New();
  coneSource0->Update();
  
  vtkSmartPointer<vtkConeSource> coneSource1 =
    vtkSmartPointer<vtkConeSource>::New();
  coneSource1->SetCenter(5,0,0);
  coneSource1->Update();

  // Create mappers and actors
  vtkSmartPointer<vtkPolyDataMapper> coneMapper0 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  coneMapper0->SetInputConnection(coneSource0->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> coneMapper1 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  coneMapper1->SetInputConnection(coneSource1->GetOutputPort());

  // Create actors
  vtkSmartPointer<vtkActor> coneActor0 =
    vtkSmartPointer<vtkActor>::New();
  coneActor0->SetMapper(coneMapper0);

  vtkSmartPointer<vtkActor> coneActor1 =
    vtkSmartPointer<vtkActor>::New();
  coneActor1->SetMapper(coneMapper1);
  coneActor1->PickableOff();
  
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

  // Add the actors to the scene
  renderer->AddActor(coneActor0);
  renderer->AddActor(coneActor1);
  renderer->SetBackground(0.5,0.5,0.5);

  renderer->ResetCamera();
  renderWindow->Render();

  vtkSmartPointer<vtkInteractorStyleTrackballActor> style =
    vtkSmartPointer<vtkInteractorStyleTrackballActor>::New();

  renderWindowInteractor->SetInteractorStyle( style );

  // Begin mouse interaction
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PickableOff)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PickableOff MACOSX_BUNDLE PickableOff.cxx)
 
target_link_libraries(PickableOff ${VTK_LIBRARIES})
```

**Download and Build PickableOff**

Click [here to download PickableOff](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PickableOff.tar) and its *CMakeLists.txt* file.
Once the *tarball PickableOff.tar* has been downloaded and extracted,
```
cd PickableOff/build 
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
./PickableOff
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

