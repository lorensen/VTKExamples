[VTKExamples](/home/)/[Cxx](/Cxx)/Interaction/RubberBandPick

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Interaction/TestRubberBandPick.png?raw=true" width="256" />

### Description
Press 'r', then make a selection with the left mouse button.

**RubberBandPick.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkInteractorStyleRubberBandPick.h>

int main (int, char *[])
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

  // Render
  renderWindow->Render();

  vtkSmartPointer<vtkInteractorStyleRubberBandPick> style = 
    vtkSmartPointer<vtkInteractorStyleRubberBandPick>::New();
  
  renderWindowInteractor->SetInteractorStyle( style );
  
  // Begin mouse interaction
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RubberBandPick)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(RubberBandPick MACOSX_BUNDLE RubberBandPick.cxx)
 
target_link_libraries(RubberBandPick ${VTK_LIBRARIES})
```

**Download and Build RubberBandPick**

Click [here to download RubberBandPick](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/RubberBandPick.tar) and its *CMakeLists.txt* file.
Once the *tarball RubberBandPick.tar* has been downloaded and extracted,
```
cd RubberBandPick/build 
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
./RubberBandPick
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

