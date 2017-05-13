[VTKExamples](/home/)/[Cxx](/Cxx)/Visualization/LegendScaleActor

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestLegendScaleActor.png?raw=true" width="256" />

**LegendScaleActor.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkLegendScaleActor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkLegendScaleActor.h>

int main(int, char *[])
{
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
 
  vtkSmartPointer<vtkLegendScaleActor> legendScaleActor = 
    vtkSmartPointer<vtkLegendScaleActor>::New();
  
  // Add the actor to the scene
  renderer->AddActor(actor);
  renderer->AddActor(legendScaleActor);
  
  renderer->SetBackground(.3, .2, .3);
 
  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(LegendScaleActor)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(LegendScaleActor MACOSX_BUNDLE LegendScaleActor.cxx)
 
target_link_libraries(LegendScaleActor ${VTK_LIBRARIES})
```

**Download and Build LegendScaleActor**

Click [here to download LegendScaleActor](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/LegendScaleActor.tar) and its *CMakeLists.txt* file.
Once the *tarball LegendScaleActor.tar* has been downloaded and extracted,
```
cd LegendScaleActor/build 
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
./LegendScaleActor
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

