[VTKExamples](Home)/[Cxx](Cxx)/Visualization/ColorActorEdges

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Visualization/TestColorActorEdges.png" width="256" />

### Description
This example colors the edges of a actor.

**ColorActorEdges.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
 
int main(int, char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(5.0);
  sphereSource->Update();
  
  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  
  // Flat shading
  actor->GetProperty()->SetInterpolationToFlat();

  // Set the color for edges of the sphere
  actor->GetProperty()->SetEdgeColor(1.0, 0.0, 0.0); //(R,G,B)
  actor->GetProperty()->EdgeVisibilityOn();

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
 
  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ColorActorEdges)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ColorActorEdges MACOSX_BUNDLE ColorActorEdges.cxx)
 
target_link_libraries(ColorActorEdges ${VTK_LIBRARIES})
```

**Download and Build ColorActorEdges**

Click [here to download ColorActorEdges](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ColorActorEdges.tar) and its *CMakeLists.txt* file.
Once the *tarball ColorActorEdges.tar* has been downloaded and extracted,
```
cd ColorActorEdges/build 
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
./ColorActorEdges
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

