[VTKExamples](/home/)/[Cxx](/Cxx)/Visualization/MoveCamera

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestMoveCamera.png?raw=true" width="256" />

### Description
This example creates two spheres. They will move together when the mouse is used to interact with the scene because the camera is actually what is moving causing the view of the spheres to change.

**MoveCamera.cxx**
```c++
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkInteractorStyleTrackballCamera.h>

int main (int, char *[])
{
  // Sphere 1
  vtkSmartPointer<vtkSphereSource> sphereSource1 =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource1->SetCenter(0.0, 0.0, 0.0);
  sphereSource1->SetRadius(4.0);
  sphereSource1->Update();
  
  vtkSmartPointer<vtkPolyDataMapper> mapper1 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper1->SetInputConnection(sphereSource1->GetOutputPort());
  
  vtkSmartPointer<vtkActor> actor1 =
    vtkSmartPointer<vtkActor>::New();
  actor1->SetMapper(mapper1);
  
  // Sphere 2
  vtkSmartPointer<vtkSphereSource> sphereSource2 =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource2->SetCenter(10.0, 0.0, 0.0);
  sphereSource2->SetRadius(3.0);
  sphereSource2->Update();

  // Create a mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper2 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper2->SetInputConnection(sphereSource2->GetOutputPort());

  // Create an actor
  vtkSmartPointer<vtkActor> actor2 =
    vtkSmartPointer<vtkActor>::New();
  actor2->SetMapper(mapper2);

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
  renderer->AddActor(actor1);
  renderer->AddActor(actor2);
  renderer->SetBackground(1,1,1); // Background color white

  // Render an image (lights and cameras are created automatically)
  renderWindow->Render();

  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
   
  renderWindowInteractor->SetInteractorStyle( style );
  
  // Begin mouse interaction
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(MoveCamera)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(MoveCamera MACOSX_BUNDLE MoveCamera.cxx)
 
target_link_libraries(MoveCamera ${VTK_LIBRARIES})
```

**Download and Build MoveCamera**

Click [here to download MoveCamera](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/MoveCamera.tar) and its *CMakeLists.txt* file.
Once the *tarball MoveCamera.tar* has been downloaded and extracted,
```
cd MoveCamera/build 
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
./MoveCamera
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

