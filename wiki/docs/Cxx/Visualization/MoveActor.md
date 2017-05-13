[VTKExamples](/home/)/[Cxx](/Cxx)/Visualization/MoveActor

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestMoveActor.png?raw=true" width="256" />

### Description
This example creates two spheres. They can be moved/scaled/rotated independent of each other using the mouse.

**MoveActor.cxx**
```c++
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkInteractorStyleTrackballActor.h>

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
 
PROJECT(MoveActor)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(MoveActor MACOSX_BUNDLE MoveActor.cxx)
 
target_link_libraries(MoveActor ${VTK_LIBRARIES})
```

**Download and Build MoveActor**

Click [here to download MoveActor](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/MoveActor.tar) and its *CMakeLists.txt* file.
Once the *tarball MoveActor.tar* has been downloaded and extracted,
```
cd MoveActor/build 
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
./MoveActor
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

