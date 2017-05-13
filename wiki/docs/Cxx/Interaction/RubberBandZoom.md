[VTKExamples](/index/)/[Cxx](/Cxx)/Interaction/RubberBandZoom

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Interaction/TestRubberBandZoom.png?raw=true" width="256" />

### Description
This example demonstrates how to select a region of the window to zoom in.

**RubberBandZoom.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkInteractorStyleRubberBandZoom.h>

int main (int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  
  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());

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

  // Add the actors to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); // Background color white

  renderWindow->Render();

  vtkSmartPointer<vtkInteractorStyleRubberBandZoom> style = 
    vtkSmartPointer<vtkInteractorStyleRubberBandZoom>::New();
  
  renderWindowInteractor->SetInteractorStyle( style );
  
  // Begin mouse interaction
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RubberBandZoom)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(RubberBandZoom MACOSX_BUNDLE RubberBandZoom.cxx)
 
target_link_libraries(RubberBandZoom ${VTK_LIBRARIES})
```

**Download and Build RubberBandZoom**

Click [here to download RubberBandZoom](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/RubberBandZoom.tar) and its *CMakeLists.txt* file.
Once the *tarball RubberBandZoom.tar* has been downloaded and extracted,
```
cd RubberBandZoom/build 
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
./RubberBandZoom
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

